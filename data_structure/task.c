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
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->dest = dest;
    new_node->weight = weight;
    new_node->next = NULL;
    return new_node;
}

void addEdge(Graph* g, int u, int v, int weight) {
    Node* new_node = createNode(v, weight);
    new_node->next = g->adjList[u];
    g->adjList[u] = new_node;

    Node* new_node2 = createNode(u, weight);
    new_node2->next = g->adjList[v];
    g->adjList[v] = new_node2;
}

void extractEdges(Graph* g, Edge* edges, int* edge_count) {
    *edge_count = 0;
    for (int i = 0; i < g->V; i++) {
        Node* curr = g->adjList[i];
        while (curr) {
            if (i < curr->dest) { // avoid duplicates
                edges[*edge_count].u = i;
                edges[*edge_count].v = curr->dest;
                edges[*edge_count].weight = curr->weight;
                (*edge_count)++;
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
