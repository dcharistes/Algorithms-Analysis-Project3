#include <stdio.h>
#include <stdlib.h>
#include "task3.h"

// Remove edge (undirected)
void removeEdge(Graph* g, int u, int v) {
    Node** curr = &g->adjList[u];
    while (*curr && (*curr)->dest != v) {
        curr = &(*curr)->next;
    }
    if (*curr) {
        Node* temp = *curr;
        *curr = temp->next;
        free(temp);
    }

    Node** curr2 = &g->adjList[v];
    while (*curr2 && (*curr2)->dest != u) {
        curr2 = &(*curr2)->next;
    }
    if (*curr2) {
        Node* temp = *curr2;
        *curr2 = temp->next;
        free(temp);
    }
}

// DFS traversal
void dfs(Graph* g, int v, int* visited) {
    visited[v] = 1;
    Node* curr = g->adjList[v];
    while (curr) {
        if (!visited[curr->dest]) {
            dfs(g, curr->dest, visited);
        }
        curr = curr->next;
    }
}

// Check connectivity
int isConnected(Graph* g) {
    int visited[MAX_NODES] = {0};
    dfs(g, 0, visited);
    for (int i = 0; i < g->V; i++) {
        if (!visited[i]) return 0;
    }
    return 1;
}

Graph* reverseDeleteMST(Graph* g){
    Edge edges[MAX_NODES * MAX_NODES];
    int edgeCount;

    extractEdges(g, edges, &edgeCount);
    qsort(edges, edgeCount, sizeof(Edge), compEdges);

    int totalWeight = 0;

    for (int i = edgeCount - 1; i >= 0; i--){
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].weight;

        removeEdge(g, u, v);

        if (!isConnected(g)){

            addEdge(g, u, v, w);
            totalWeight += w;
        }
    }
    printf("Total MST Weight = %d\n", totalWeight);

    return g;
}
