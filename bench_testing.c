#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "task2.h"

#define V 10
#define N 4
#define E 2*V

int main() {
    srand(time(NULL));

    Graph* graphs[N];
    Graph* msts[N];

    for (int i = 0; i < N; i++){
        graphs[i] = (Graph*) malloc(sizeof(Graph));
        initGraph(graphs[i], V);

        bool edgeExists[V][V] = { 0 };

        for (int u = 0; u < V; u++) {
            int v;
            do {
                v = rand() % V;
            } while (v == u || edgeExists[u][v]);

            int w = rand() % (2*V);

            addEdge(graphs[i], u, v, w);
            addEdge(graphs[i], v, u, w);
            edgeExists[u][v] = edgeExists[v][u] = 1;
        }

        int addedEdges = V; // Already added V edges in step 1
        while (addedEdges < E) {
            int u = rand() % V;
            int v = rand() % V;
            if (u == v || edgeExists[u][v])
                continue;

            int w = rand() % (2*V);

            addEdge(graphs[i], u, v, w);
            addEdge(graphs[i], v, u, w);
            edgeExists[u][v] = edgeExists[v][u] = 1;
            addedEdges++;
        }

    }

    for (int j = 0; j < N; j++){

        printf("\n==Original Graph %d Edges ==\n", j + 1);
        displayGraph(graphs[j]);

        //prim run

        printf("Minimum Spanning Tree %d Edges, using Prim:\n", j + 1);
        displayGraph(msts[j]);
        printf("\n");

        msts[j] = kruskalMST(graphs[j]);

        printf("Minimum Spanning Tree %d Edges, using Kruskal:\n", j + 1);
        displayGraph(msts[j]);
        printf("\n");
    }
}
