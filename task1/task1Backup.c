#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define V 5   // στατικό μέγεθος γράφου

/* ——— Δομή λίστας γειτνίασης (Εργ.4) ——— */
typedef struct Node {
    int dest, weight;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
} AdjList;

typedef struct {
    AdjList *adjList;   // πίνακας λιστών, μήκους V
} Graph;

Node* newNode(int dest, int weight) {
    Node* node = malloc(sizeof *node);
    node->dest   = dest;
    node->weight = weight;
    node->next   = NULL;
    return node;
}

// πια δεν δέχεται παράμετρο V, γιατί το V είναι στατικό
Graph* createGraph() {
    Graph* g = malloc(sizeof *g);
    g->adjList = calloc(V, sizeof *g->adjList);
    return g;
}

void addEdge(Graph* g, int u, int v, int w) {
    Node* n = newNode(v, w);
    n->next = g->adjList[u].head;
    g->adjList[u].head = n;
}

/* ——— εύρεση κορυφής με ελάχιστο cost ——— */
int minCost(int cost[], bool known[]) {
    int min = INT_MAX, idx = -1;
    for (int i = 0; i < V; i++) {
        if (!known[i] && cost[i] < min) {
            min = cost[i];
            idx = i;
        }
    }
    return idx;
}

/* ——— Prim’s MST ——— */
void primMST(Graph* g) {
    int path[V];
    int cost[V];
    bool known[V];

    for (int i = 0; i < V; i++) {
        cost[i]  = INT_MAX;
        known[i] = false;
        path[i]  = -1;
    }
    cost[0] = 0;

    for (int k = 0; k < V-1; k++) {
        int u = minCost(cost, known);
        known[u] = true;
        for (Node* p = g->adjList[u].head; p; p = p->next) {
            int v = p->dest, w = p->weight;
            if (!known[v] && w < cost[v]) {
                cost[v]  = w;
                path[v]  = u;
            }
        }
    }

    printf("\nPrim MST\n");
    for (int i = 1; i < V; i++) {
        printf("%d -> %d    %d\n", path[i], i, cost[i]);
    }
}

int main(void) {
    /* ——— Graph 1: ίδιος με Εργ.5 (V=5) ——— */
    Graph* g1 = createGraph();
    addEdge(g1,0,1,2);  addEdge(g1,1,0,2);
    addEdge(g1,0,3,6);  addEdge(g1,3,0,6);
    addEdge(g1,1,2,3);  addEdge(g1,2,1,3);
    addEdge(g1,1,3,8);  addEdge(g1,3,1,8);
    addEdge(g1,1,4,5);  addEdge(g1,4,1,5);
    addEdge(g1,2,4,7);  addEdge(g1,4,2,7);
    addEdge(g1,3,4,9);  addEdge(g1,4,3,9);
    printf("=== Graph 1 ===");
    primMST(g1);

    /* ——— Graph 2: 5-κορυφών κύκλος ——— */
    Graph* g2 = createGraph();
    addEdge(g2, 0, 1, 2);  addEdge(g2, 1, 0, 2);
    addEdge(g2, 1, 2, 3);  addEdge(g2, 2, 1, 3);
    addEdge(g2, 2, 3, 4);  addEdge(g2, 3, 2, 4);
    addEdge(g2, 3, 4, 5);  addEdge(g2, 4, 3, 5);
    addEdge(g2, 4, 0, 1);  addEdge(g2, 0, 4, 1);
    printf("\n=== Graph 2 ===");
    primMST(g2);

    /* ——— Graph 3: custom 5-κορυφών ——— */
    Graph* g3 = createGraph();
    addEdge(g3,0,1,7);  addEdge(g3,1,0,7);
    addEdge(g3,0,2,9);  addEdge(g3,2,0,9);
    addEdge(g3,1,3,10); addEdge(g3,3,1,10);
    addEdge(g3,2,3,2);  addEdge(g3,3,2,2);
    addEdge(g3,3,4,1);  addEdge(g3,4,3,1);
    printf("\n=== Graph 3 ===");
    primMST(g3);

    /* ——— Graph 4: αλυσίδα (path graph V=5) ——— */
    Graph* g4 = createGraph();
    addEdge(g4, 0, 1, 1);  addEdge(g4, 1, 0, 1);
    addEdge(g4, 1, 2, 1);  addEdge(g4, 2, 1, 1);
    addEdge(g4, 2, 3, 1);  addEdge(g4, 3, 2, 1);
    addEdge(g4, 3, 4, 1);  addEdge(g4, 4, 3, 1);
    printf("\n=== Graph 4 ===");
    primMST(g4);

    return 0;
}
