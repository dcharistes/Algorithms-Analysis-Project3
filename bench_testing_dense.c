#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "./task1/task1.h"
#include "./task2/task2.h"
#include "./task3/task3.h"

#define V 1000
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
    int weight_th = V;

    typedef struct {
        int u, v;
    } EdgePair;

    float density = (float) E / max_edges;
    printf("V = %d, E = %d\n", V, E);

    for (int i = 0; i < N; i++){
        graphs[i] = (Graph*) malloc(sizeof(Graph));
        initGraph(graphs[i], V);                //has to be the same for all three algorithms

        //this method works fine for dense graphs only.
        //as it does not ensure connectivity, for sparse graphs the probability of a disconnected graph is high
        //and prim won't be executed. for sparse graphs the first method is appropriate as it ensures connectivity enabling execution times comparison.
        // generate all possible edges (max_edges)
        EdgePair* all_edges = malloc(max_edges * sizeof(EdgePair));
        int idx = 0;
        for (int u = 0; u < V; u++) {
            for (int v = u + 1; v < V; v++) {
                all_edges[idx].u = u;
                all_edges[idx].v = v;
                idx++;
            }
        }

        // shuffle edges
        for (int j = max_edges - 1; j > 0; j--) {
            int k = rand() % (j + 1);
            EdgePair tmp = all_edges[j];
            all_edges[j] = all_edges[k];
            all_edges[k] = tmp;
        }

        // add E edges
        for (int j = 0; j < E; j++) {
            int u = all_edges[j].u;
            int v = all_edges[j].v;
            int w = 1 + rand() % weight_th;
            addEdge(graphs[i], u, v, w);
        }
        free(all_edges);
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
