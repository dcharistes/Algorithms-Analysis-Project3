#include <stdio.h>
#include <stdlib.h>
#include "task2.h"

void initGraph(Graph* g, int vertices) {
    g->V = vertices;
    for (int i = 0; i < MAX_NODES; i++) {
        g->adjList[i] = NULL;
    }
}

Node* createNode(int dest, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

void addEdge(Graph* g, int u, int v, int weight) {
    Node* newNode = createNode(v, weight);
    newNode->next = g->adjList[u];
    g->adjList[u] = newNode;
}

// Initializes the disjoint set with n elements.
void initDisjointSet(DisjointSet* ds, int n) {
    ds->size = n;
    ds->parent = (int*)malloc(n * sizeof(int));
    ds->rank = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        ds->parent[i] = i;              //initialize every V vertex to parent of itself (root),
        ds->rank[i] = 0;                //and the rank to 0 before applying a join with another vertex.
    }
}

void freeDisjointSet(DisjointSet* ds) {
    free(ds->parent);
    free(ds->rank);
}


void extractEdges(Graph* g, Edge* edgeList, int* edgeCount) {
    *edgeCount = 0;
    for (int i = 0; i < g->V; i++) {
        Node* curr = g->adjList[i];
        while (curr) {
            if (i < curr->dest) { // avoid duplicates
                edgeList[*edgeCount].u = i;
                edgeList[*edgeCount].v = curr->dest;
                edgeList[*edgeCount].weight = curr->weight;
                (*edgeCount)++;
            }
            curr = curr->next;
        }
    }
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

int compEdges(const void* a, const void* b) {
    Edge* e1 = (Edge*)a;
    Edge* e2 = (Edge*)b;
    return e1->weight - e2->weight;                     //sort edges based on weight. if (> 0) ? e2 has a smaller weight : e1. and so on the edges list is sorted
}

Graph* kruskalMST(Graph* g) {
    Edge edges[2 * MAX_NODES];
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

void displayGraph(Graph* g) {
    for (int i = 0; i < g->V; i++) {
        Node* curr = g->adjList[i];
        while (curr) {
            if (i < curr->dest)
                printf("(%d)---(%d|%d)\n", i, curr->dest, curr->weight);
            curr = curr->next;
        }
    }
}

// int main() {
//     int V = 4;
//     Graph* graphs[V];
//     Graph* msts[V];

//     graphs[0] = (Graph*)malloc(sizeof(Graph));
//     initGraph(graphs[0], 5); // vertices numbered 0 to 4
//     // Undirected graph
//     addEdge(graphs[0],0,1,2);  addEdge(graphs[0],1,0,2);
//     addEdge(graphs[0],0,3,6);  addEdge(graphs[0],3,0,6);
//     addEdge(graphs[0],1,2,3);  addEdge(graphs[0],2,1,3);
//     addEdge(graphs[0],1,3,8);  addEdge(graphs[0],3,1,8);
//     addEdge(graphs[0],1,4,5);  addEdge(graphs[0],4,1,5);
//     addEdge(graphs[0],2,4,7);  addEdge(graphs[0],4,2,7);
//     addEdge(graphs[0],3,4,9);  addEdge(graphs[0],4,3,9);

//     graphs[1] = (Graph*)malloc(sizeof(Graph));
//     initGraph(graphs[1], 5); // vertices numbered 0 to 4
//     // Undirected graph
//     addEdge(graphs[1], 0, 1, 2);  addEdge(graphs[1], 1, 0, 2);
//     addEdge(graphs[1], 1, 2, 3);  addEdge(graphs[1], 2, 1, 3);
//     addEdge(graphs[1], 2, 3, 4);  addEdge(graphs[1], 3, 2, 4);
//     addEdge(graphs[1], 3, 4, 5);  addEdge(graphs[1], 4, 3, 5);
//     addEdge(graphs[1], 4, 0, 1);  addEdge(graphs[1], 0, 4, 1);

//     graphs[2] = (Graph*)malloc(sizeof(Graph));
//     initGraph(graphs[2], 5); // vertices numbered 0 to 4
//     // Undirected graph
//     addEdge(graphs[2],0,1,7);  addEdge(graphs[2],1,0,7);
//     addEdge(graphs[2],0,2,9);  addEdge(graphs[2],2,0,9);
//     addEdge(graphs[2],1,3,10); addEdge(graphs[2],3,1,10);
//     addEdge(graphs[2],2,3,2);  addEdge(graphs[2],3,2,2);
//     addEdge(graphs[2],3,4,1);  addEdge(graphs[2],4,3,1);

//     graphs[3] = (Graph*)malloc(sizeof(Graph));
//     initGraph(graphs[3], 5); // vertices numbered 0 to 4
//     // Undirected graph
//     addEdge(graphs[3], 0, 1, 1);  addEdge(graphs[3], 1, 0, 1);
//     addEdge(graphs[3], 1, 2, 1);  addEdge(graphs[3], 2, 1, 1);
//     addEdge(graphs[3], 2, 3, 1);  addEdge(graphs[3], 3, 2, 1);
//     addEdge(graphs[3], 3, 4, 1);  addEdge(graphs[3], 4, 3, 1);

//     for (int i = 0; i < 4; i++) {
//         printf("\n==Original Graph %d Edges ==\n", i + 1);
//         displayGraph(graphs[i]);

//         msts[i] = kruskalMST(graphs[i]);

//         printf("Minimum Spanning Tree %d Edges:\n", i + 1);
//         displayGraph(msts[i]);
//         printf("\n");
//     }

//     for (int i = 0; i < 4; i++) {
//         for (int j = 0; j < msts[i]->V; j++) {
//             Node* curr = msts[i]->adjList[j];
//             while (curr) {
//                 Node* temp = curr;
//                 curr = curr->next;
//                 free(temp);
//             }
//         }
//         free(msts[i]);

//         for (int j = 0; j < graphs[i]->V; j++) {
//             Node* curr = graphs[i]->adjList[j];
//             while (curr) {
//                 Node* temp = curr;
//                 curr = curr->next;
//                 free(temp);
//             }
//         }
//         free(graphs[i]);
//     }

//     return 0;
// }
