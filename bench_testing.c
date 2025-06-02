#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "./task1/task1.h"
#include "./task2/task2.h"
#include "./task3/task3.h"

#define V 10
#define N 4
#define manual 0
//#define E (2*V - rand() % 5)
float time_function(Graph* (*func)(Graph*), Graph* graph, Graph** mst, const char* label, int j);
int main() {
    srand(time(NULL));

    FILE* log_prim = fopen("./logs/log_prim.csv", "w");
    FILE* log_kruskal = fopen("./logs/log_kruskal.csv", "w");
    FILE* log_re_del = fopen("./logs/log_re_del.csv", "w");

    const char* label[3] = {"Prim", "Kruskal", "Reverse-Delete"};

    fprintf(log_prim,"n,time\n");
    fprintf(log_kruskal,"n,time\n");
    fprintf(log_re_del,"n,time\n");

    Graph* graphs[N];
    Graph* msts[N];
    int max_edges = V*(V-1)/2;
    int E = V - 1 + rand() % (max_edges - V); //number of edges between min edges (so that a vertex is not disconnected forom the graph) and max possible. [minE, maxE]
    float density = (float) E / max_edges;
    printf("V = %d, E = %d\n", V, E);

    if (!manual){
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
                //printf("u = %d, v = %d, w = %d\n", u, v, w);
                addEdge(graphs[i], u, v, w);        //add edge u, v and v, u
                edgedIn[u][v] = edgedIn[v][u] = 1;  //update edgeIn for the two edges added
            }
            //printf("\n");
            int addedEdges = V;                     // Already added V edges in step 1
            while (addedEdges < E) {                // add the remaining E - V edges.
                int u = rand() % V;                 //u is now also selected randomly
                //printf("u = %d\n", u);
                int v = rand() % V;
                //printf("v = %d\n", v);
                if (u == v || edgedIn[u][v])        //exclude same vertex ends and already added edges
                    continue;

                int w = rand() % V;
                //printf("u = %d, v = %d, w = %d\n", u, v, w);
                addEdge(graphs[i], u, v, w);
                edgedIn[u][v] = edgedIn[v][u] = 1;
                addedEdges++;                       //increment addedEdges for the while condition termination
            }
        }
    }
    else {
        graphs[0] = (Graph*) malloc(sizeof(Graph));
        initGraph(graphs[0], V);
        //addEdge(graphs[0], 0, 5, 7); //manually input edges
        addEdge(graphs[0], 0, 1, 9);
        addEdge(graphs[0], 1, 5, 6);
        addEdge(graphs[0], 1, 6, 2);
        addEdge(graphs[0], 2, 6, 8);
        addEdge(graphs[0], 3, 7, 2);
        addEdge(graphs[0], 4, 6, 7);
        addEdge(graphs[0], 4, 7, 1);
        addEdge(graphs[0], 5, 6, 5);
        addEdge(graphs[0], 7, 5, 7);
        addEdge(graphs[0], 6, 7, 8);
    }
    for (int j = 0; j < N; j++){
        int k = 0;
        printf("\n==== Original Graph %d ====\n", j + 1);
        displayGraph(graphs[j]);

        //prim
        printf("\nPrim - Minimum Spanning Tree %d\n", j + 1);
        float time_prim = time_function(primMST, graphs[j], &msts[j], label[k], j);
        displayGraph(msts[j]);
        printf("\n");
        fprintf(log_prim,"%d, %.6f\n",j, time_prim);
        k++;

        //kruskal
        printf("Kruskal - Minimum Spanning Tree %d\n", j + 1);
        float time_kruskal = time_function(kruskalMST, graphs[j], &msts[j], label[k], j);
        displayGraph(msts[j]);
        printf("\n");
        fprintf(log_kruskal,"%d,%.6f\n", j, time_kruskal);
        k++;

        //reverse-delete
        printf("Reverse-Delete - Minimum Spanning Tree %d\n", j + 1);
        float time_re_del = time_function(reverseDeleteMST, graphs[j], &msts[j], label[k], j); // = time_function(...)
        displayGraph(msts[j]);
        printf("\n");
        fprintf(log_re_del,"%d,%.6f\n", j, time_re_del);
    }

    fclose(log_prim);
    fclose(log_kruskal);
    fclose(log_re_del);

    printf("V = %d, E = %d\n", V, E);

    if (density >= 0.5)
        printf("Dense Graph\n");
    else
        printf("Sparse Graph\n");
    printf("density = %.6f\n", density);
}

float time_function(Graph* (*func)(Graph*), Graph* graph, Graph** mst, const char* label, int j){
    clock_t start = clock();
    *mst = func(graph);
    clock_t end =  clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%s found the minimum spanning tree of %d graph in %.6f seconds\n", label, j, time_spent);
    return time_spent;
}
