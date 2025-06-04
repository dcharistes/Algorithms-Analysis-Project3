#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "./task1/task1.h"
#include "./task2/task2.h"
#include "./task3/task3.h"

#define V 100
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
    int E[N];
    int max_edges = V * (V - 1) / 2;
    int weight_th = V;
    float density_fix = 0;
    float density[N];
    //int E = V - 1 + rand() % (max_edges - V + 2); //number of edges between min edges (so that a vertex is not disconnected forom the graph) and max possible. [minE, maxE]

    for (int i = 0; i < N; i++){
        graphs[i] = (Graph*) malloc(sizeof(Graph));
        initGraph(graphs[i], V);                //has to be the same for all three algorithms

        bool **edgedIn = calloc(V, sizeof(bool*)); //array to hold already added u, v edges init to 0 (false) with calloc
        for (int l = 0; l < V; l++) {
            edgedIn[l] = calloc(V, sizeof(bool));
        }

        for (int u = 1; u < V; u++) {          //select every u in (1, V-1) and 0 through rand%
            int w = 1 + rand() % weight_th;     //this makes sure that the graph won't be disconnected by forming a connection only with previous vertices
            int v = rand() % u;                 //
            addEdge(graphs[i], u, v, w);        //add edge u, v and v, u. 
            edgedIn[u][v] = edgedIn[v][u] = 1;  //update edgedIn for the two edges added
        }

        int addedEdges = V - 1;                     // Already added V - 1 edges in step 1
        
        density_fix = (i < 2) ? 0.04 : 1;           //sparse or dense graph
        E[i] = V - 1 + rand() % ((int)(density_fix * max_edges - (V - 1) + 1));                     
        density[i] = (float)E[i] /(float) max_edges; //actual density

        if (i > 0) {
            while (density[i] <= density [i - 1] && density[i - 1] < 1){
                E[i] = V - 1 + rand() % ((int)(density_fix * max_edges - (V - 1) + 1));                     
                density[i] = (float) E[i] / max_edges;
            }
        }

        while (addedEdges < E[i]) {                    // add the remaining E - (V - 1) edges.
            int u = rand() % V;                     //u and v is now also selected randomly as we guaranteed in the previous step the connectivity
            int v = rand() % V;
            if (u == v || edgedIn[u][v])            //exclude same vertex ends and already added edges
                continue;
            int w = 1 + rand() % weight_th;
            addEdge(graphs[i], u, v, w);
            edgedIn[u][v] = edgedIn[v][u] = 1;  //update edgedIn for the edge (undirected) added
            addedEdges++;                       //increment addedEdges for the while condition termination
        }

        for (int m = 0; m < V; m++)
            free(edgedIn[m]);
        free(edgedIn);
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

    printf("V = %d,\n", V);

    for (int i = 0; i < N; i++){
        printf("density[%d] = %.6f, E[%d] = %d\n", i, density[i], i, E[i]);
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
