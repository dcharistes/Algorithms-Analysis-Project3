#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int dest;
    int cost;
    struct Node* next;
} Node;

typedef struct {
    int n;
    Node** adjList;
} Graph;

Graph* createGraph(int nodeCount);
void addEdge(Graph* graph, int src, int dest, int cost);
void displayEdges(Graph* graph, int* totalCost);
Graph* primsMST(Graph* g, int start);

int main() {
    Graph* g = createGraph(4);
    Graph* tree;
    int totalCost;

    // Undirected graph with 4 nodes
    addEdge(g, 0, 1, 10);
    addEdge(g, 1, 0, 10);
    addEdge(g, 0, 2, 6);
    addEdge(g, 2, 0, 6);
    addEdge(g, 0, 3, 5);
    addEdge(g, 3, 0, 5);
    addEdge(g, 1, 3, 15);
    addEdge(g, 3, 1, 15);
    addEdge(g, 2, 3, 4);
    addEdge(g, 3, 2, 4);

    tree = primsMST(g, 0);
    printf("Minimum Spanning Tree Edges:\n");
    displayEdges(tree, &totalCost);
    printf("Total cost: %d\n", totalCost);

    return 0;
}

Node* createNode(int dest, int cost) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->dest = dest;
    newNode->cost = cost;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int nodeCount) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->n = nodeCount;
    graph->adjList = (Node**)malloc(nodeCount * sizeof(Node*));
    for (int i = 0; i < nodeCount; i++) {
        graph->adjList[i] = NULL;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest, int cost) {
    Node* newNode = createNode(dest, cost);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;
}

void displayEdges(Graph* graph, int* totalCost) {
    *totalCost = 0;
    for (int i = 0; i < graph->n; i++) {
        Node* temp = graph->adjList[i];
        while (temp) {
            if (i < temp->dest) { // avoid duplicate printing
                printf("(%d)---(%d|%d)\n", i, temp->dest, temp->cost);
                *totalCost += temp->cost;
            }
            temp = temp->next;
        }
    }
}

Graph* primsMST(Graph* g, int start) {
    int n = g->n;
    Graph* tree = createGraph(n);
    int B[n], Bsize = 0;
    int visited[n];
    for (int i = 0; i < n; i++) visited[i] = 0;
    B[Bsize++] = start;
    visited[start] = 1;

    while (Bsize < n) {
        int min = 9999;
        int v = -1, par = -1;

        for (int i = 0; i < Bsize; i++) {
            int u = B[i];
            Node* temp = g->adjList[u];
            while (temp) {
                if (!visited[temp->dest] && temp->cost < min) {
                    min = temp->cost;
                    par = u;
                    v = temp->dest;
                }
                temp = temp->next;
            }
        }

        if (v != -1) {
            B[Bsize++] = v;
            visited[v] = 1;
            addEdge(tree, par, v, min);
            addEdge(tree, v, par, min);
        }
    }

    return tree;
}
