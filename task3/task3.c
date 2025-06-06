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

// DFS traversal O(V+E)
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

// Check connectivity O(V+E) + O(V)
int isConnected(Graph* g) {
    int visited[MAX_NODES] = {0};
    dfs(g, 0, visited);
    for (int i = 0; i < g->V; i++) {
        if (!visited[i]) return 0;
    }
    return 1;
}

Graph* reverseDeleteMST(Graph* g){
    Edge* edges = malloc(sizeof(Edge) * MAX_NODES * MAX_NODES / 2);
    if (!edges) {
        printf("Memory allocation failed\n");
        return 0;
    }
    int edge_count;

    extractEdges(g, edges, &edge_count); //O(V+E)
    qsort(edges, edge_count, sizeof(Edge), compEdges); //O(ElogE)

    for (int i = edge_count - 1; i >= 0; i--){
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].weight;

        removeEdge(g, u, v); //O(deg(u)+dega(v)) deg(n) number of n neighbors'

        if (!isConnected(g)){
            addEdge(g, u, v, w);
        }
    }

    int total_weight = 0;
    for (int u = 0; u < g->V; u++) {
        Node* curr = g->adjList[u];
        while (curr) {
            if (u < curr->dest) // counts each edge once. if u > curr-> dest, this edge was counted in the previous loop
                total_weight += curr->weight;
            curr = curr->next;
        }
    }

    free(edges);
    printf("Total MST Weight = %d\n", total_weight);

    return g;
}
