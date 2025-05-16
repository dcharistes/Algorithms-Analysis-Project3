#include <stdio.h>
#include <stdlib.h>
#include "prim_graph_funcs.h"

Node* createNode(int dest, int cost) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->dest = dest;
    newNode->cost = cost;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int nodeCount) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->n = nodeCount;
    graph->adjList = (Node**)malloc(nodeCount * sizeof(Node*));
    for (int i = 0; i < nodeCount; i++) {
        graph->adjList[i] = NULL;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest, int cost) {
    Node* newNode = createNode(dest, cost);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;
}

void displayEdges(Graph* graph, int* totalCost) {
    *totalCost = 0;
    for (int i = 0; i < graph->n; i++) {
        Node* temp = graph->adjList[i];
        while (temp) {
            if (i < temp->dest) { // avoid duplicate printing
                printf("(%d)---(%d|%d)\n", i, temp->dest, temp->cost);
                *totalCost += temp->cost;
            }
            temp = temp->next;
        }
    }
}
