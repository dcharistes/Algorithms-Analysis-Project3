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

    Node* newNode2 = createNode(u, weight);
    newNode2->next = g->adjList[v];
    g->adjList[v] = newNode2;
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

void freeGraph(Graph* g){
    for (int v = 0; v < g->V; v++) {
        Node* curr = g->adjList[v];
        while (curr) {
            Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(g);
}

int compEdges(const void* a, const void* b) {
    Edge* e1 = (Edge*)a;
    Edge* e2 = (Edge*)b;
    return e1->weight - e2->weight;                     //sort edges based on weight. if (> 0) ? e2 has a smaller weight : e1. and so on the edges list is sorted
}
