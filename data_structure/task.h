#ifndef TASK_H
#define TASK_H

#define MAX_NODES 10000

//structs
typedef struct Node {
    int dest, weight;
    struct Node* next;
} Node;

typedef struct {
    int u, v, weight;
} Edge;

typedef struct {
    int V;
    Node* adjList[MAX_NODES];
} Graph;

//data structure defined in task.c
Node* createNode(int dest, int weight);
void addEdge(Graph* g, int u, int v, int weight);
void extractEdges(Graph* g, Edge* edgeList, int* edgeCount);
void initGraph(Graph* g, int vertices);
void displayGraph(Graph* g);
//sort
int compEdges(const void* a, const void* b);

#endif
