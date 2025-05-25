#include <stdio.h>
#include <stdlib.h>
//#include "./graph_funcs/kruskal_graph_funcs.h"

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

int countEdges(Graph* g) {
    int count = 0;
    for (int i = 0; i < g->V; i++) {
        Node* curr = g->adjList[i];
        while (curr) {
            count++;
            curr = curr->next;
        }
    }
    return count;
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

void sortEdges(Edge* edges, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (edges[i].weight > edges[j].weight) {
                Edge temp = edges[i];
                edges[i] = edges[j];
                edges[j] = temp;
            }
        }
    }
}

int find(int* parent, int v) {
    if (parent[v] == v)
        return v;
    return find(parent, parent[v]);
}

int compEdges(const void* a, const void* b) {
    Edge* e1 = (Edge*)a;
    Edge* e2 = (Edge*)b;
    return (e1->weight < e2->weight) ? -1 : (e1->weight > e2->weight) ? 1 : 0;
}

int unionSet(int* parent, int u, int v) {
    int rootU = find(parent, u);
    int rootV = find(parent, v);
    if (rootU == rootV)
        return 0;
    parent[rootV] = rootU;
    return 1;
}

Graph* kruskalMST(Graph* g) {
    Edge edges[2 * MAX_NODES];
    int edgeCount;

    extractEdges(g, edges, &edgeCount);
    qsort(edges, edgeCount, sizeof(Edge), compEdges);
    //sortEdges(edges, edgeCount);

    Graph* mst = (Graph*)malloc(sizeof(Graph));
    initGraph(mst, g->V);

    int parent[MAX_NODES];
    for (int i = 0; i < g->V; i++) {
        parent[i] = i;
    }

    int totalWeight = 0;
    for (int i = 0; i < edgeCount; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].weight;

        if (unionSet(parent, u, v)) {
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

int main() {
    int N = 4;
    Graph* graphs[N];
    Graph* msts[N];

    graphs[0] = (Graph*)malloc(sizeof(Graph));
    initGraph(graphs[0], 5); // vertices numbered 0 to 4
    // Undirected graph
    addEdge(graphs[0],0,1,2);  addEdge(graphs[0],1,0,2);
    addEdge(graphs[0],0,3,6);  addEdge(graphs[0],3,0,6);
    addEdge(graphs[0],1,2,3);  addEdge(graphs[0],2,1,3);
    addEdge(graphs[0],1,3,8);  addEdge(graphs[0],3,1,8);
    addEdge(graphs[0],1,4,5);  addEdge(graphs[0],4,1,5);
    addEdge(graphs[0],2,4,7);  addEdge(graphs[0],4,2,7);
    addEdge(graphs[0],3,4,9);  addEdge(graphs[0],4,3,9);

    graphs[1] = (Graph*)malloc(sizeof(Graph));
    initGraph(graphs[1], 5); // vertices numbered 0 to 4
    // Undirected graph
    addEdge(graphs[1], 0, 1, 2);  addEdge(graphs[1], 1, 0, 2);
    addEdge(graphs[1], 1, 2, 3);  addEdge(graphs[1], 2, 1, 3);
    addEdge(graphs[1], 2, 3, 4);  addEdge(graphs[1], 3, 2, 4);
    addEdge(graphs[1], 3, 4, 5);  addEdge(graphs[1], 4, 3, 5);
    addEdge(graphs[1], 4, 0, 1);  addEdge(graphs[1], 0, 4, 1);

    graphs[2] = (Graph*)malloc(sizeof(Graph));
    initGraph(graphs[2], 5); // vertices numbered 0 to 4
    // Undirected graph
    addEdge(graphs[2],0,1,7);  addEdge(graphs[2],1,0,7);
    addEdge(graphs[2],0,2,9);  addEdge(graphs[2],2,0,9);
    addEdge(graphs[2],1,3,10); addEdge(graphs[2],3,1,10);
    addEdge(graphs[2],2,3,2);  addEdge(graphs[2],3,2,2);
    addEdge(graphs[2],3,4,1);  addEdge(graphs[2],4,3,1);

    graphs[3] = (Graph*)malloc(sizeof(Graph));
    initGraph(graphs[3], 5); // vertices numbered 0 to 4
    // Undirected graph
    addEdge(graphs[3], 0, 1, 1);  addEdge(graphs[3], 1, 0, 1);
    addEdge(graphs[3], 1, 2, 1);  addEdge(graphs[3], 2, 1, 1);
    addEdge(graphs[3], 2, 3, 1);  addEdge(graphs[3], 3, 2, 1);
    addEdge(graphs[3], 3, 4, 1);  addEdge(graphs[3], 4, 3, 1);

    for (int i = 0; i < 4; i++) {
        printf("\n==Original Graph %d Edges ==\n", i + 1);
        displayGraph(graphs[i]);

        msts[i] = kruskalMST(graphs[i]);

        printf("Minimum Spanning Tree %d Edges:\n", i + 1);
        displayGraph(msts[i]);
        printf("\n");
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < msts[i]->V; j++) {
            Node* curr = msts[i]->adjList[j];
            while (curr) {
                Node* temp = curr;
                curr = curr->next;
                free(temp);
            }
        }
        free(msts[i]);

        for (int j = 0; j < graphs[i]->V; j++) {
            Node* curr = graphs[i]->adjList[j];
            while (curr) {
                Node* temp = curr;
                curr = curr->next;
                free(temp);
            }
        }
        free(graphs[i]);
    }

    return 0;
}
