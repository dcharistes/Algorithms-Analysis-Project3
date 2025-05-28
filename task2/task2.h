#ifndef TASK2_H
#define TASK2_H
#include "../data_structure/task.h"

//kruskal functions defined task2.c
void initDisjointSet(DisjointSet* ds, int n);
void freeDisjointSet(DisjointSet* ds);
void extractEdges(Graph* g, Edge* edgeList, int* edgeCount);
int find(DisjointSet* ds, int v);
int unionSet(DisjointSet* ds, int u, int v);
int compEdges(const void* a, const void* b);
Graph* kruskalMST(Graph* g); //kruskal algorithm

#endif
