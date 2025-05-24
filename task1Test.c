#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* ——— Γράφος με λίστες γειτνίασης ——— */
typedef struct Node {
    int v, w;
    struct Node *next;
} Node;

typedef struct {
    int n;
    Node **adj;
} Graph;

Graph *newGraph(int n){
    Graph *g = malloc(sizeof *g);
    g->n = n;
    g->adj = calloc(n, sizeof *g->adj);
    return g;
}

Node *newNode(int v, int w){
    Node *x = malloc(sizeof *x);
    x->v = v; x->w = w; x->next = NULL;
    return x;
}

void addEdge(Graph *g, int u, int v, int w){
    Node *x = newNode(v,w);
    x->next = g->adj[u];
    g->adj[u] = x;
}

/* ——— Min-heap για Prim ——— */
typedef struct { int v, key; } HNode;
typedef struct {
    int size, cap, *pos;
    HNode **h;
} Heap;

Heap *newHeap(int cap){
    Heap *H = malloc(sizeof *H);
    H->size = 0;
    H->cap = cap;
    H->pos = malloc(cap * sizeof *H->pos);
    H->h   = malloc(cap * sizeof *H->h);
    return H;
}

static inline int LEFT(int i){ return 2*i+1; }
static inline int RIGHT(int i){ return 2*i+2; }

void swapNode(HNode **a, HNode **b, int *pos){
    int va = (*a)->v, vb = (*b)->v;
    HNode *t = *a; *a = *b; *b = t;
    int tmp = pos[va]; pos[va] = pos[vb]; pos[vb] = tmp;
}

void heapify(Heap *H, int i){
    int l = LEFT(i), r = RIGHT(i), small = i;
    if (l < H->size && H->h[l]->key < H->h[small]->key) small = l;
    if (r < H->size && H->h[r]->key < H->h[small]->key) small = r;
    if (small != i){
        swapNode(&H->h[i], &H->h[small], H->pos);
        heapify(H, small);
    }
}

HNode *extractMin(Heap *H){
    if (H->size == 0) return NULL;
    HNode *root = H->h[0];
    HNode *last = H->h[--H->size];
    H->h[0] = last;
    H->pos[last->v] = 0;
    heapify(H, 0);
    return root;
}

void decreaseKey(Heap *H, int v, int newKey){
    int i = H->pos[v];
    H->h[i]->key = newKey;
    while (i > 0 && H->h[i]->key < H->h[(i-1)/2]->key) {
        swapNode(&H->h[i], &H->h[(i-1)/2], H->pos);
        i = (i-1)/2;
    }
}

int inHeap(Heap *H, int v){
    return H->pos[v] < H->size;
}

/* ——— Prim’s MST ——— */
Graph *prim(Graph *g, int src){
    int V = g->n;
    int *key = malloc(V * sizeof *key);
    int *par = malloc(V * sizeof *par);

    Heap *H = newHeap(V);
    for (int i = 0; i < V; i++){
        par[i] = -1;
        key[i] = INT_MAX;
        H->h[i] = malloc(sizeof *H->h[i]);
        H->h[i]->v = i;
        H->h[i]->key = key[i];
        H->pos[i] = i;
        H->size++;
    }

    decreaseKey(H, src, 0);
    key[src] = 0;

    while (H->size){
        HNode *hn = extractMin(H);
        int u = hn->v;
        free(hn);
        for (Node *p = g->adj[u]; p; p = p->next){
            int v = p->v;
            if (inHeap(H, v) && p->w < key[v]){
                key[v] = p->w;
                par[v] = u;
                decreaseKey(H, v, p->w);
            }
        }
    }

    /* Έλεγχος συνεκτικότητας: αν κάποια κορυφή πέρασε αλώβητη, τερματίζουμε */
    for (int i = 0; i < V; i++){
        if (i != src && par[i] < 0){
            fprintf(stderr, "Graph not connected\n");
            exit(1);
        }
    }

    /* Φτιάχνουμε το MST-γράφο */
    Graph *T = newGraph(V);
    for (int v = 0; v < V; v++){
        if (par[v] >= 0){
            addEdge(T, par[v], v, key[v]);
            addEdge(T, v, par[v], key[v]);
        }
    }

    return T;
}

/* ——— Εμφάνιση αποτελέσματος ——— */
void showMST(Graph *T){
    int cost = 0;
    for (int u = 0; u < T->n; u++){
        for (Node *p = T->adj[u]; p; p = p->next){
            if (u < p->v){
                printf("%d - %d (%d)\n", u, p->v, p->w);
                cost += p->w;
            }
        }
    }
    printf("Total cost = %d\n", cost);
}

int main(void){
    Graph *g = newGraph(4);

    addEdge(g, 0, 1, 10); addEdge(g, 1, 0, 10);
    addEdge(g, 0, 2, 6);  addEdge(g, 2, 0, 6);
    addEdge(g, 0, 3, 5);  addEdge(g, 3, 0, 5);
    addEdge(g, 1, 3, 15); addEdge(g, 3, 1, 15);
    addEdge(g, 2, 3, 4);  addEdge(g, 3, 2, 4);

    Graph *mst = prim(g, 0);
    showMST(mst);

    return 0;
}