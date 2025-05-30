#ifndef TASK2_H
#define TASK2_H
#include "../data_structure/task.h"

typedef struct {
    int* parent;            //stores the root of aset containing i. parent[i]
    int* rank;              //rank[i] stores the depth of the tree  with root i. node i is the parent representing the set of child nodes
    int size;               //size in the n of elements in the ds
} DisjointSet;

//disjoint set functions
void initDisjointSet(DisjointSet* ds, int n);
void freeDisjointSet(DisjointSet* ds);
//union functions
int find(DisjointSet* ds, int v);
int unionSet(DisjointSet* ds, int u, int v);

Graph* kruskalMST(Graph* g); //kruskal algorithm

#endif
