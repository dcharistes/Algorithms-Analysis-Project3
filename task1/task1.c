#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "task1.h"  // Χρησιμοποιούμε τις δομές και συναρτήσεις από task2.h

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
