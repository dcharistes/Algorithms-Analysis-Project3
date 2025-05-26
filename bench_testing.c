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
        initGraph(graphs[i], V);                //has to be the same for all three algorithms

        bool edgedIn[V][V] = { 0 };             //function to hold already added u, v edges

        for (int u = 0; u < V; u++) {           //select every u in (0, V-1)
            int v;
            do {
                v = rand() % V;                 //select a random v from (0, V-1)
            } while (v == u || edgedIn[u][v]);  //v != u and not already added in the graph

            int w = rand() % (2*V);             //weight of the u, v edge

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

        printf("\n==Original Graph %d Edges ==\n", j + 1);
        displayGraph(graphs[j]);

        //prim

        printf("Minimum Spanning Tree %d Edges, using Prim:\n", j + 1);
        printf("\n");

        //kruskal
        msts[j] = kruskalMST(graphs[j]);

        printf("Minimum Spanning Tree %d Edges, using Kruskal:\n", j + 1);
        displayGraph(msts[j]);
        printf("\n");

        //reverse-delete

        printf("Minimum Spanning Tree %d Edges, using Reverse-Delete:\n", j + 1);
        printf("\n");
    }
}
