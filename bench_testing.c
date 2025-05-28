#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "task.h"

#define V 100
#define N 4
#define E 2*V
float time_function(Graph* (*func)(Graph*), Graph* graph, Graph** mst, const char* label, int j);
int main() {
    srand(time(NULL));

    FILE* log_prim = fopen("log_prim.csv", "w");
    FILE* log_kruskal = fopen("log_kruskal.csv", "w");
    FILE* log_re_del = fopen("log_re_del.csv", "w");

    const char* label[3] = {"Prim", "Kruskal", "Reverse-Delete"};

    fprintf(log_prim,"n,time\n");
    fprintf(log_kruskal,"n,time\n");
    fprintf(log_re_del,"n,time\n");

    Graph* graphs[N];
    Graph* msts[N];

    for (int i = 0; i < N; i++){
        graphs[i] = (Graph*) malloc(sizeof(Graph));
        initGraph(graphs[i], V);                //has to be the same for all three algorithms

        bool edgedIn[V][V] = { 0 };             //function to hold already added u, v edges

        for (int u = 0; u < V; u++) {           //select every u in (0, V-1)
            int v;
            do {
                v = rand() % V;                 //select a random v from (0, V-1)
            } while (v == u || edgedIn[u][v]);  //v != u and not already added in the graph

            int w = rand() % 20;             //weight of the u, v edge

            addEdge(graphs[i], u, v, w);        //add edge u, v
            addEdge(graphs[i], v, u, w);        //add edge v, u (undirected graph)
            edgedIn[u][v] = edgedIn[v][u] = 1;  //update edgeIn for the two edges added
        }

        int addedEdges = V;                     // Already added E/2 edges in step 1
        while (addedEdges < E) {                // add the remaining E/2 = V edges.
            int u = rand() % V;                 //u is now also selected randomly
            int v = rand() % V;
            if (u == v || edgedIn[u][v])        //exclude same vertex ends and already added edges
                continue;

            int w = rand() % (2*V);

            addEdge(graphs[i], u, v, w);
            addEdge(graphs[i], v, u, w);
            edgedIn[u][v] = edgedIn[v][u] = 1;
            addedEdges++;                       //increment addedEdges for the while condition termination
        }
    }
    for (int j = 0; j < N; j++){
        int k = 0;
        printf("\n==== Original Graph %d Edges ====\n", j + 1);
        displayGraph(graphs[j]);

        //prim
        float time_prim = time_function(primMST, graphs[j], &msts[j], label[k], j);
        printf("Prim - Minimum Spanning Tree %d Edges:\n", j + 1);
        displayGraph(msts[j]);
        printf("\n");
        fprintf(log_prim,"%d, %.6f\n",j, time_prim);

        k++;

        //kruskal
        float time_kruskal = time_function(kruskalMST, graphs[j], &msts[j], label[k], j);
        printf("Kruskal - Minimum Spanning Tree %d Edges:\n", j + 1);
        displayGraph(msts[j]);
        printf("\n");
        fprintf(log_kruskal,"%d,%.6f\n", j, time_kruskal);
        k++;

        //reverse-delete
        float time_re_del = 0; // = time_function(...)
        printf("Reverse-Delete - Minimum Spanning Tree %d Edges:\n", j + 1);
        displayGraph(msts[j]);
        printf("\n");
        fprintf(log_re_del,"%d,%.6f\n", j, time_re_del);
    }
}

float time_function(Graph* (*func)(Graph*), Graph* graph, Graph** mst, const char* label, int j){
    clock_t start = clock();
    *mst = func(graph);
    clock_t end =  clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%s found the minimum spanning tree of %d graph in %.6f seconds\n", label, j, time_spent);
    return time_spent;
}
