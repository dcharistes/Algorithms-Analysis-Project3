#include <stdio.h>
#include <stdlib.h>

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

void initGraph(Graph* g, int vertices);
Node* createNode(int dest, int weight);
void addEdge(Graph* g, int u, int v, int weight);
int countEdges(Graph* g);
void extractEdges(Graph* g, Edge* edgeList, int* edgeCount);
void sortEdges(Edge* edges, int count);
int find(int* parent, int v);
