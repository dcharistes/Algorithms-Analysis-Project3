#include <stdio.h>
#include <stdlib.h>
#include "task2.h"

// Initializes the disjoint set with n elements.
void initDisjointSet(DisjointSet* ds, int n) {
    ds->size = n;
    ds->parent = (int*)malloc(n * sizeof(int));
    ds->rank = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        ds->parent[i] = i;                              //initialize every V vertex to parent of itself (root),
        ds->rank[i] = 0;                                //and the rank to 0 before applying a join with another vertex.
    }
}

void freeDisjointSet(DisjointSet* ds) {
    free(ds->parent);
    free(ds->rank);
}

// Uses path compression to find the representative of the set containing v.
// the tree formed with the vertices of the set is always flattened acieving optimization.
//each node on the path points directly to the root minimizing the depth
int find(DisjointSet* ds, int v) {
    if (ds->parent[v] != v)
        ds->parent[v] = find(ds, ds->parent[v]);        //finds the path to the root of the initial v vertex through recursion. after finding it, path compresion is applied assigning the parent node to to v
    return ds->parent[v];
}

// Joins the sets that contain u and v using union by rank. avoid making tall trees
int unionSet(DisjointSet* ds, int u, int v) {
    int rootU = find(ds, u);
    int rootV = find(ds, v);

    if (rootU == rootV)
        return 0;                                       //avoid forming a cycle in MST. non edge is added to the mst as the nodes traversed, have the same root

    //the tree with the smallest rank (depth) is attached to the higher one achieving minimum tree depth
    if (ds->rank[rootU] < ds->rank[rootV]) {
        ds->parent[rootU] = rootV;
    } else if (ds->rank[rootU] > ds->rank[rootV]) {
        ds->parent[rootV] = rootU;
    } else {
        ds->parent[rootV] = rootU;
        ds->rank[rootU]++;                              //Increase rank by 1 only if both have the same rank. Having the same rank increases the depth of the united tree by 1 layer.
    }

    return 1;                                           //successful union
}

Graph* kruskalMST(Graph* g) {
    Edge edges[MAX_NODES * MAX_NODES];
    int edgeCount;

    extractEdges(g, edges, &edgeCount);                 //we extracted all the edges from the given graph. Also extract the size of the edgeList after it is filled . with u, v, and weight and
    qsort(edges, edgeCount, sizeof(Edge), compEdges);   //sort the edges List in ascending form

    Graph* mst = (Graph*)malloc(sizeof(Graph));         //create the graph that will hold the mst
    initGraph(mst, g->V);                               //initialize the head to NULL

    DisjointSet ds;
    initDisjointSet(&ds, g->V);

    int totalWeight = 0;

    for (int i = 0; i < edgeCount; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].weight;

        if (unionSet(&ds, u, v)) {
            addEdge(mst, u, v, w);
            addEdge(mst, v, u, w);
            totalWeight += w;
        }
    }

    printf("Total MST cost: %d\n", totalWeight);
    return mst;
}
