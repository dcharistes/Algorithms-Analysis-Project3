#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int dest;
    int cost;
    struct Node* next;
} Node;

typedef struct {
    int n;
    Node** adjList;
} Graph;

Graph* createGraph(int nodeCount);
void addEdge(Graph* graph, int src, int dest, int cost);
void displayEdges(Graph* graph, int* totalCost);
