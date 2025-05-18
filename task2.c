#include <stdio.h>
#include <stdlib.h>
//#include "./graph_funcs/kruskal_graph_funcs.h"

#define MAX_NODES 100

typedef struct Node {
    int dest;
    int weight;
    struct Node* next;
} Node;

typedef struct {
    int u, v, weight;
} Edge;

typedef struct {
    int V;
    Node* adjList[MAX_NODES];
} Graph;

void initGraph(Graph* g, int vertices) {
    g->V = vertices;
    for (int i = 0; i < MAX_NODES; i++) {
        g->adjList[i] = NULL;
    }
}

Node* createNode(int dest, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

void addEdge(Graph* g, int u, int v, int weight) {
    Node* newNode = createNode(v, weight);
    newNode->next = g->adjList[u];
    g->adjList[u] = newNode;
}

int countEdges(Graph* g) {
    int count = 0;
    for (int i = 0; i < g->V; i++) {
        Node* curr = g->adjList[i];
        while (curr) {
            count++;
            curr = curr->next;
        }
    }
    return count;
}

void extractEdges(Graph* g, Edge* edgeList, int* edgeCount) {
    *edgeCount = 0;
    for (int i = 0; i < g->V; i++) {
        Node* curr = g->adjList[i];
        while (curr) {
            if (i < curr->dest) { // avoid duplicates
                edgeList[*edgeCount].u = i;
                edgeList[*edgeCount].v = curr->dest;
                edgeList[*edgeCount].weight = curr->weight;
                (*edgeCount)++;
            }
            curr = curr->next;
        }
    }
}

void sortEdges(Edge* edges, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (edges[i].weight > edges[j].weight) {
                Edge temp = edges[i];
                edges[i] = edges[j];
                edges[j] = temp;
            }
        }
    }
}

int find(int* parent, int v) {
    if (parent[v] == v)
        return v;
    return find(parent, parent[v]);
}


int unionSet(int* parent, int u, int v) {
    int rootU = find(parent, u);
    int rootV = find(parent, v);
    if (rootU == rootV) return 0;
    parent[rootV] = rootU;
    return 1;
}

Graph* kruskalMST(Graph* g) {
    Edge edges[2 * MAX_NODES];
    int edgeCount;

    extractEdges(g, edges, &edgeCount);
    sortEdges(edges, edgeCount);

    Graph* mst = (Graph*)malloc(sizeof(Graph));
    initGraph(mst, g->V);

    int parent[MAX_NODES];
    for (int i = 0; i < g->V; i++) {
        parent[i] = i;
    }

    int totalWeight = 0;
    for (int i = 0; i < edgeCount; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].weight;

        if (unionSet(parent, u, v)) {
            addEdge(mst, u, v, w);
            addEdge(mst, v, u, w);
            totalWeight += w;
        }
    }

    printf("Total MST cost: %d\n", totalWeight);
    return mst;
}

void displayGraph(Graph* g) {
    for (int i = 0; i < g->V; i++) {
        Node* curr = g->adjList[i];
        while (curr) {
            if (i < curr->dest)
                printf("(%d)---(%d|%d)\n", i, curr->dest, curr->weight);
            curr = curr->next;
        }
    }
}

int main() {
    Graph* g = (Graph*)malloc(sizeof(Graph));
    initGraph(g, 7); // vertices numbered 0 to 6

    // Undirected graph
    addEdge(g, 1, 2, 6); addEdge(g, 2, 1, 6);
    addEdge(g, 1, 3, 1); addEdge(g, 3, 1, 1);
    addEdge(g, 1, 4, 3); addEdge(g, 4, 1, 3);
    addEdge(g, 1, 5, 2); addEdge(g, 5, 1, 2);
    addEdge(g, 1, 6, 1); addEdge(g, 6, 1, 1);

    addEdge(g, 2, 6, 3); addEdge(g, 6, 2, 3);
    addEdge(g, 2, 3, 4); addEdge(g, 3, 2, 4);
    addEdge(g, 2, 5, 5); addEdge(g, 5, 2, 5);
    addEdge(g, 2, 4, 7); addEdge(g, 4, 2, 7);

    addEdge(g, 3, 4, 1); addEdge(g, 4, 3, 1);
    addEdge(g, 3, 5, 2); addEdge(g, 5, 3, 2);

    addEdge(g, 4, 5, 4); addEdge(g, 5, 4, 4);
    addEdge(g, 4, 6, 2); addEdge(g, 6, 4, 2);

    addEdge(g, 5, 6, 5); addEdge(g, 6, 5, 5);

    printf("Original Graph Edges:\n");
    displayGraph(g);

    Graph* mst = kruskalMST(g);

    printf("\nMinimum Spanning Tree Edges:\n");
    displayGraph(mst);

    return 0;
}
