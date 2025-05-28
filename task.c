#include <stdio.h>
#include <stdlib.h>
#include "task.h"

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
