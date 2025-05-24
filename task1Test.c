#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

/* -------------------- ΔΟΜΕΣ ΓΡΑΦΟΥ -------------------- */
typedef struct Node {
    int dest;
    int cost;
    struct Node* next;
} Node;

typedef struct {
    int n;
    Node** adjList;
} Graph;

// Δημιουργεί κόμβο λίστας γειτνίασης
Node* createNode(int dest, int cost) {
    Node* newNode = malloc(sizeof(Node));
    newNode->dest = dest;
    newNode->cost = cost;
    newNode->next = NULL;
    return newNode;
}

// Δημιουργεί γράφο με n κορυφές, λίστες γειτνίασης κενές
Graph* createGraph(int n) {
    Graph* g = malloc(sizeof(Graph));
    g->n = n;
    g->adjList = malloc(n * sizeof(Node*));
    for (int i = 0; i < n; i++)
        g->adjList[i] = NULL;
    return g;
}

// Προσθήκη κατευθυνόμενης ακμής src→dest
void addEdge(Graph* g, int src, int dest, int cost) {
    Node* node = createNode(dest, cost);
    node->next = g->adjList[src];
    g->adjList[src] = node;
}

// Προσθήκη αμφοτερόδρομης ακμής (undirected)
void addUndirectedEdge(Graph* g, int u, int v, int cost) {
    addEdge(g, u, v, cost);
    addEdge(g, v, u, cost);
}

// Εκτυπώνει τις ακμές ενός MST-γραφου και αθροίζει κόστος
void displayEdges(Graph* tree, int* totalCost) {
    *totalCost = 0;
    for (int u = 0; u < tree->n; u++) {
        for (Node* cur = tree->adjList[u]; cur; cur = cur->next) {
            if (u < cur->dest) {
                printf("(%d)---(%d|%d)\n", u, cur->dest, cur->cost);
                *totalCost += cur->cost;
            }
        }
    }
}

/* -------------------- MIN-HEAP ΔΟΜΕΣ -------------------- */
typedef struct {
    int v;     // κορυφή
    int key;   // τρέχον ελάχιστο βάρος ακμής
} HeapNode;

typedef struct {
    int size;       // τρέχων αριθμός κόμβων στο heap
    int capacity;   // μέγιστη χωρητικότητα (ιδανικά = V)
    int *pos;       // pos[v] = θέση της κορυφής v μέσα στο heap array
    HeapNode **arr; // δυναμικός πίνακας δεικτών σε HeapNode
} MinHeap;

// Ανταλλαγή δύο κόμβων στο heap και ενημέρωση pos[]
void swapHeapNode(HeapNode **a, HeapNode **b, int *pos) {
    HeapNode *tmp = *a;
    int pv = (*a)->v, qv = (*b)->v;
    *a = *b;  *b = tmp;
    pos[pv] = pos[qv];
    pos[qv] = pos[pv] == pos[qv] ? pos[pv] : pos[qv]; // μετά swap
}

// Δημιουργία min-heap για V κόμβους
MinHeap* createMinHeap(int capacity) {
    MinHeap* mh = malloc(sizeof(MinHeap));
    mh->size = 0;
    mh->capacity = capacity;
    mh->pos = malloc(capacity * sizeof(int));
    mh->arr = malloc(capacity * sizeof(HeapNode*));
    return mh;
}

bool isEmpty(MinHeap* mh) {
    return mh->size == 0;
}

// Φυτρώνει προς τα κάτω (heapify) από index i
void minHeapify(MinHeap* mh, int i) {
    int smallest = i;
    int l = 2*i + 1, r = 2*i + 2;
    if (l < mh->size && mh->arr[l]->key < mh->arr[smallest]->key)
        smallest = l;
    if (r < mh->size && mh->arr[r]->key < mh->arr[smallest]->key)
        smallest = r;
    if (smallest != i) {
        swapHeapNode(&mh->arr[i], &mh->arr[smallest], mh->pos);
        minHeapify(mh, smallest);
    }
}

// Εξάγει (και αφαιρεί) τον κόμβο με το ελάχιστο key
HeapNode* extractMin(MinHeap* mh) {
    if (isEmpty(mh)) return NULL;
    HeapNode* root = mh->arr[0];
    HeapNode* last = mh->arr[mh->size - 1];
    mh->arr[0] = last;
    mh->pos[last->v] = 0;
    mh->size--;
    minHeapify(mh, 0);
    return root;
}

// Μειώνει το key της κορυφής v σε new_key (decrease-key)
void decreaseKey(MinHeap* mh, int v, int new_key) {
    int i = mh->pos[v];
    mh->arr[i]->key = new_key;
    while (i && mh->arr[i]->key < mh->arr[(i-1)/2]->key) {
        swapHeapNode(&mh->arr[i], &mh->arr[(i-1)/2], mh->pos);
        i = (i-1)/2;
    }
}

// Εισάγει νέο HeapNode στη δομή
void insertHeapNode(MinHeap* mh, HeapNode* hn) {
    mh->arr[mh->size] = hn;
    mh->pos[hn->v] = mh->size;
    mh->size++;
    // φυτρώνει προς τα πάνω
    int i = mh->size - 1;
    while (i && mh->arr[i]->key < mh->arr[(i-1)/2]->key) {
        swapHeapNode(&mh->arr[i], &mh->arr[(i-1)/2], mh->pos);
        i = (i-1)/2;
    }
}

bool isInMinHeap(MinHeap *mh, int v) {
    return mh->pos[v] < mh->size;
}

/* -------------------- PRIM’s MST -------------------- */
Graph* primsMST(Graph* g, int start) {
    int V = g->n;
    int *parent = malloc(V * sizeof(int));
    int *key    = malloc(V * sizeof(int));
    bool *inMST = malloc(V * sizeof(bool));

    // 1) Αρχικοποίηση
    MinHeap* mh = createMinHeap(V);
    for (int v = 0; v < V; v++) {
        parent[v] = -1;
        key[v]    = INT_MAX;
        inMST[v]  = false;
        HeapNode* hn = malloc(sizeof(HeapNode));
        hn->v   = v;
        hn->key = key[v];
        insertHeapNode(mh, hn);
    }

    // 2) Ο σπόρος
    decreaseKey(mh, start, 0);
    key[start] = 0;

    // 3) Κύριος βρόχος
    while (!isEmpty(mh)) {
        HeapNode* hn = extractMin(mh);
        int u = hn->v;
        inMST[u] = true;
        free(hn);

        // Εξετάζουμε κάθε γειτονικό v
        for (Node* nbr = g->adjList[u]; nbr; nbr = nbr->next) {
            int v = nbr->dest;
            if (isInMinHeap(mh, v) && nbr->cost < key[v]) {
                key[v]    = nbr->cost;
                parent[v] = u;
                decreaseKey(mh, v, nbr->cost);
            }
        }
    }

    // 4) Συναρμολόγηση MST-γράφου
    Graph* tree = createGraph(V);
    for (int v = 0; v < V; v++) {
        if (parent[v] != -1) {
            addUndirectedEdge(tree, parent[v], v, key[v]);
        }
    }

    // 5) Έλεγχος συνεκτικότητας
    for (int v = 0; v < V; v++) {
        if (v != start && parent[v] == -1) {
            fprintf(stderr, "Ο γράφος ΔΕΝ είναι συνεκτικός – δεν υπάρχει MST για όλες τις κορυφές.\n");
            exit(EXIT_FAILURE);
        }
    }

    // 6) Καθαρισμός μνήμης βοηθητικών δομών
    for (int i = 0; i < mh->capacity; i++)
        if (mh->pos[i] < mh->capacity) ; // δεν χρειαζόμαστε τα υπόλοιπα HeapNode
    free(mh->arr);
    free(mh->pos);
    free(mh);
    free(parent);
    free(key);
    free(inMST);

    return tree;
}

// Απελευθέρωση γράφου
void freeGraph(Graph* g) {
    for (int i = 0; i < g->n; i++) {
        Node* cur = g->adjList[i];
        while (cur) {
            Node* tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }
    free(g->adjList);
    free(g);
}

/* -------------------- MAIN & TEST -------------------- */
int main() {
    Graph* g = createGraph(4);

    // Παραδειγματικός γράφος 4 κορυφών
    addUndirectedEdge(g, 0, 1, 10);
    addUndirectedEdge(g, 0, 2, 6);
    addUndirectedEdge(g, 0, 3, 5);
    addUndirectedEdge(g, 1, 3, 15);
    addUndirectedEdge(g, 2, 3, 4);

    Graph* mst = primsMST(g, 0);

    printf("Minimum Spanning Tree Edges:\n");
    int totalCost;
    displayEdges(mst, &totalCost);
    printf("Total cost: %d\n", totalCost);

    freeGraph(g);
    freeGraph(mst);
    return 0;
}
