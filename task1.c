#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "./data_structure/task.h"  // Χρησιμοποιούμε τις δομές και συναρτήσεις από task2.h

// minCost αναζητά την κορυφή με ελάχιστο κόστος
int minCost(int cost[], bool known[], int n) {
    int min = INT_MAX, idx = -1;
    for (int i = 0; i < n; i++) {
        if (!known[i] && cost[i] < min) {
            min = cost[i];
            idx = i;
        }
    }
    return idx;
}

// Prim’s MST χρησιμοποιεί Graph από task2.h
Graph* primMST(Graph* g) {
    int n = g->V;
    int path[n], cost[n];
    bool known[n];

    for (int i = 0; i < n; i++) {
        cost[i] = INT_MAX;
        known[i] = false;
        path[i] = -1;
    }
    cost[0] = 0;

    for (int k = 0; k < n - 1; k++) {
        int u = minCost(cost, known, n);
        known[u] = true;
        for (Node* p = g->adjList[u]; p; p = p->next) {
            int v = p->dest, w = p->weight;
            if (!known[v] && w < cost[v]) {
                cost[v] = w;
                path[v] = u;
            }
        }
    }

    Graph* mst = (Graph*)malloc(sizeof(Graph));
    initGraph(mst, g->V);
    for (int v = 1; v < n; v++) {
        int u = path[v];
        if (u != -1) {
            // Εισαγωγή της ακμής και στις δύο κατευθύνσεις αν είναι μη κατευθυνόμενο γράφημα
            addEdge(mst, u, v, cost[v]);
            addEdge(mst, v, u, cost[v]);
        }
    }
    return mst;

}

/*
int main(void) {
    // Γράφος 1 (V=5)
    Graph* g1 = malloc(sizeof(Graph));
    initGraph(g1, 5);
    addEdge(g1,0,1,2);  addEdge(g1,1,0,2);
    addEdge(g1,0,3,6);  addEdge(g1,3,0,6);
    addEdge(g1,1,2,3);  addEdge(g1,2,1,3);
    addEdge(g1,1,3,8);  addEdge(g1,3,1,8);
    addEdge(g1,1,4,5);  addEdge(g1,4,1,5);
    addEdge(g1,2,4,7);  addEdge(g1,4,2,7);
    addEdge(g1,3,4,9);  addEdge(g1,4,3,9);
    printf("=== Graph 1 ===");
    primMST(g1);

    // Γράφος 2 (V=5)
    Graph* g2 = malloc(sizeof(Graph));
    initGraph(g2, 5);
    addEdge(g2,0,1,2);  addEdge(g2,1,0,2);
    addEdge(g2,1,2,3);  addEdge(g2,2,1,3);
    addEdge(g2,2,3,4);  addEdge(g2,3,2,4);
    addEdge(g2,3,4,5);  addEdge(g2,4,3,5);
    addEdge(g2,4,0,1);  addEdge(g2,0,4,1);
    printf("\n=== Graph 2 ===");
    primMST(g2);

    // Γράφος 3 (V=5)
    Graph* g3 = malloc(sizeof(Graph));
    initGraph(g3, 5);
    addEdge(g3,0,1,7);  addEdge(g3,1,0,7);
    addEdge(g3,0,2,9);  addEdge(g3,2,0,9);
    addEdge(g3,1,3,10); addEdge(g3,3,1,10);
    addEdge(g3,2,3,2);  addEdge(g3,3,2,2);
    addEdge(g3,3,4,1);  addEdge(g3,4,3,1);
    printf("\n=== Graph 3 ===");
    primMST(g3);

    // Γράφος 4 (V=5)
    Graph* g4 = malloc(sizeof(Graph));
    initGraph(g4, 5);
    addEdge(g4,0,1,1);  addEdge(g4,1,0,1);
    addEdge(g4,1,2,1);  addEdge(g4,2,1,1);
    addEdge(g4,2,3,1);  addEdge(g4,3,2,1);
    addEdge(g4,3,4,1);  addEdge(g4,4,3,1);
    printf("\n=== Graph 4 ===");
    primMST(g4);

    return 0;
}*/
