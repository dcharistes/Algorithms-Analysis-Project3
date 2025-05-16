#include <stdio.h>
#include <stdlib.h>
#include "kruskal_graph_funcs.h"

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
