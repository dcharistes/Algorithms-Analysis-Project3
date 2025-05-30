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


    Graph* mst = (Graph*)malloc(sizeof(Graph));
    initGraph(mst, g->V);

    int totalWeight = 0;

    for (int i = edgeCount - 1; i >= 0; i--){
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].weight;

        removeEdge(g, u, v);
        removeEdge(g, v, u);

        if (!isConnected(g)){
            addEdge(g, u, v, w);
            addEdge(g, v, u, w);

            addEdge(mst, u, v, w);
            addEdge(mst, v, u, w);

            totalWeight += w;
        }
    }
    printf("Total MST Weight = %d", totalWeight);

    return mst;
}
