#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "./task1/task1.h"
#include "./task2/task2.h"
#include "./task3/task3.h"

#define V 50
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

            bool **edgedIn = malloc(V * sizeof(bool*)); //array to hold already added u, v edges
            for (int l = 0; l < V; l++) {
                edgedIn[l] = malloc(V * sizeof(bool));
            }

            // for (int u = 0; u < V; u++) {           //select every u in (0, V-1)
            //     int v;
            //     do {
            //         v = rand() % V;                 //select a random v from (0, V-1)
            //     } while (v == u || edgedIn[u][v]);  //v != u and not already added in the graph

            //     int w = 1 + rand() % 20;             //weight of the u, v edge
            //     addEdge(graphs[i], u, v, w);        //add edge u, v and v, u
            //     edgedIn[u][v] = edgedIn[v][u] = 1;  //update edgeIn for the two edges added
            // }

            // int addedEdges = V; lines (46-57)//randomly select a connection with u.
                                   //this might produce an unconnected graph. i.e. 1->5, 2->1, 3->6, 4->6, 5->2 (v = 6, e = v-1=5).
                                   //Prim will return a segmentation fault,
                                   //as it can not operate with unconnected graphs.
                                   //as we approach the minimum number of edges e = v-1. the probability of unconnected graph increases.

            for (int u = 0; u < V - 1; u++) {           //select every u in (0, V-1)
                int w = 1 + rand() % 20;                //weight of the u, v edge
                addEdge(graphs[i], u, u + 1, w);        //add edge u, u+1 and u+1, u. this makes sure that the graph won't be disconnected by forming a chain
                edgedIn[u][u+1] = edgedIn[u+1][u] = 1;  //update edgedIn for the two edges added
            }

            int addedEdges = V - 1;                     // Already added V - 1 edges in step 1
            while (addedEdges < E) {                    // add the remaining E - (V - 1) edges.
                int u = rand() % V;                     //u and v is now also selected randomly as we guaranteed in the previous step the connectivity
                int v = rand() % V;
                if (u == v || edgedIn[u][v])            //exclude same vertex ends and already added edges
                    continue;

                int w = 1 + rand() % 20;
                addEdge(graphs[i], u, v, w);
                edgedIn[u][v] = edgedIn[v][u] = 1;  //update edgedIn for the edge (undirected) added
                addedEdges++;                       //increment addedEdges for the while condition termination
            }

            for (int m = 0; m < V; m++)
                free(edgedIn[m]);
            free(edgedIn);
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

    for (int n = 0; n < N; n++){
        freeGraph(graphs[n]);
    }

    fclose(log_prim);
    fclose(log_kruskal);
    fclose(log_re_del);

    printf("V = %d, E = %d\n", V, E);

    if (density >= 0.04)
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
