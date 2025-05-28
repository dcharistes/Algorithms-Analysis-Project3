#ifndef TASK_H
#define TASK_H

#define MAX_NODES 100

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

typedef struct {
    int* parent;            //stores the root of aset containing i. parent[i]
    int* rank;              //rank[i] stores the depth of the tree  with root i. node i is the parent representing the set of child nodes
    int size;               //size in the n of elements in the ds
} DisjointSet;


//data structure defined in task.c
void initGraph(Graph* g, int vertices);
Node* createNode(int dest, int weight);
void addEdge(Graph* g, int u, int v, int weight);
void displayGraph(Graph* g);

#endif
