#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

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
    int* parent; //stores the root of aset containing i. parent[i]
    int* rank; //rank[i] stores the depth of the tree  with root i. node i is the parent representing the set of child nodes
    int size; //size in the n of elements in the ds
} DisjointSet;


void initGraph(Graph* g, int vertices);
Node* createNode(int dest, int weight);
void addEdge(Graph* g, int u, int v, int weight);
void initDisjointSet(DisjointSet* ds, int n);
void freeDisjointSet(DisjointSet* ds);
void extractEdges(Graph* g, Edge* edgeList, int* edgeCount);
int find(DisjointSet* ds, int v);
int unionSet(DisjointSet* ds, int u, int v);
int compEdges(const void* a, const void* b);
Graph* kruskalMST(Graph* g);
void displayGraph(Graph* g);
