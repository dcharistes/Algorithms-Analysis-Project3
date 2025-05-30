#ifndef TASK3_H
#define TASK3_h
#include "../data_structure/task.h"

void removeEdge(Graph* g, int u, int v);
int isConnected(Graph* g);
void dfs(Graph* g, int v, int *visited);

Graph* reverseDeleteMST(Graph* g);

#endif
