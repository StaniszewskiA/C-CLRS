#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define TASK 1
#define MAX_VERTICES 10
#define INF INT_MAX

#pragma region Graph utils

typedef struct LGNode {
    int vertex;
    int weight;
    struct LGNode* next;
} LGNode;

typedef struct ListGraph {
    int numVertices;
    LGNode* adjList[MAX_VERTICES];
} ListGraph;

LGNode* lg_node_create(int vertex, int weight) {
    LGNode* newNode = malloc(sizeof(LGNode));
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

ListGraph* list_graph_create(int numVertices) {
    ListGraph* g = malloc(sizeof(ListGraph));
    g->numVertices = numVertices;
    for (int i = 0; i < numVertices; i++) g->adjList[i] = NULL;
    return g;
}

void list_graph_free(ListGraph* g) {
    for (int i = 0; i < g->numVertices; i++) {
        LGNode* temp = g->adjList[i];
        while (temp) {
            LGNode* toDelete = temp;
            temp = temp->next;
            free(toDelete);
        }
    }
    free(g);
}

void list_graph_add_edge(ListGraph* g, int u, int v, int weight) {
    LGNode* newNode = lg_node_create(v, weight);
    newNode->next = g->adjList[u];
    g->adjList[u] = newNode;
}

#pragma endregion Graph utils

#pragma region Fibonacci heap utils

typedef struct FibNode {
    int vertex;
    int key;
    struct FibNode* parent;
    struct FibNode* child;
    struct FibNode* left;
    struct FibNode* right;
    int degree;
    int mark;
} FibNode;

typedef struct FibHeap {
    FibNode* min;
    int size;
} FibHeap;

FibNode* fib_node_create(int vertex, int key) {
    FibNode* node = (FibNode*)malloc(sizeof(FibNode));
    node->vertex = vertex;
    node->key = key;
    node->parent = node->child = NULL;
    node->left = node->right = node;
    node->degree = 0;
    node->mark = 0;
    return node;
}

FibHeap* fib_heap_create() {
    FibHeap* heap = (FibHeap*)malloc(sizeof(FibHeap));
    heap->min = NULL;
    heap->size = 0;
    return heap;
}

void fib_insert(FibHeap* heap, FibNode* node) {
    if (!heap->min) {
        heap->min = node;
        node->left = node->right = node;
    } else {
        node->left = heap->min;
        node->right = heap->min->right;
        heap->min->right->left = node;
        heap->min->right = node;
        if (node->key < heap->min->key) heap->min = node;
    }
    heap->size++;
}

void fib_link(FibHeap* heap, FibNode* y, FibNode* x) {
    y->left->right = y->right;
    y->right->left = y->left;
    y->parent = x;
    if (!x->child) {
        x->child = y;
        y->left = y->right = y;
    } else {
        y->left = x->child;
        y->right = x->child->right;
        x->child->right->left = y;
        x->child->right = y;
    }
    x->degree++;
    y->mark = 0;
}

void fib_consolidate(FibHeap* heap) {
    int D = 16;
    FibNode* A[16] = {0};
    FibNode* w = heap->min;
    if (!w) return;
    int rootCnt = 0;
    FibNode* x = w;

    do {
        rootCnt++;
        x = x->right;
    } while (x != w);

    while (rootCnt--) {
        x = heap->min;
        FibNode* next = x->right;
        int d = x->degree;
        while (A[d]) {
            FibNode* y = A[d];
            if (x->key > y->key) {
                FibNode* temp = x;
                x = y;
                y = temp;
            }
            fib_link(heap, y, x);
            A[d] = NULL;
            d++;
        }
        A[d] = x;
        heap->min = next;
    }
    heap->min = NULL;
    for (int i = 0; i < D; i++) {
        if (!A[i]) continue;
        if (!heap->min) {
            heap->min = A[i];
            A[i]->left = A[i]->right = A[i];
        } else {
            A[i]->left = heap->min;
            A[i]->right = heap->min->right;
            heap->min->right->left = A[i];
            heap->min->right = A[i];
            if (A[i]->key < heap->min->key)
                heap->min = A[i];
        }
    }
}

FibNode* fib_extract_min(FibHeap* heap) {
    FibNode* z = heap->min;
    if (!z) return NULL;
    if (z->child) {
        FibNode* x = z->child;
        do {
            FibNode* next = x->right;
            x->left = heap->min;
            x->right = heap->min->right;
            heap->min->right->left = x;
            heap->min->right = x;
            x->parent = NULL;
            x = next;
        } while (x != z->child);
    }
    z->left->right = z->right;
    z->right->left = z->left;
    if (z == z->right) heap->min = NULL;
    else {
        heap->min = z->right;
        fib_consolidate(heap);
    }
    heap->size--;

    return z;
}

void fib_cut(FibHeap* heap, FibNode* x, FibNode* y) {
    if (y->child == x) {
        if (x->right != x) y->child = x->right;
        else y->child = NULL;
    }
     x->left->right = x->right;
    x->right->left = x->left;
    y->degree--;
    x->left = heap->min;
    x->right = heap->min->right;
    heap->min->right->left = x;
    heap->min->right = x;
    x->parent = NULL;
    x->mark = 0;
}

void fib_cascading_cut(FibHeap* heap, FibNode* y) {
    FibNode* z = y->parent;
    if (!z) return;
    if (!y->mark) y->mark = 1;
    else {
        fib_cut(heap, y, z);
        fib_cascading_cut(heap, z);
    }
}

void fib_dec_key(FibHeap* heap, FibNode* x, int k) {
    if (k > x->key) return;
    x->key = k;
    FibNode* y = x->parent;
    if (!y || x->key >= y->key) return;
    fib_cut(heap, x, y);
    fib_cascading_cut(heap, y);
    if (x->key < heap->min->key) heap->min = x;
}

void fib_free(FibNode* node) {
    if (!node) return;
    FibNode* start = node;
    do {
        FibNode* next = node->right;
        if (node->child) fib_free(node->child);
        free(node);
        node = next;
    } while (node != start);
}

#pragma endregion Fibonacci heap utils

#pragma region Bellman-Ford

int bellman_ford(ListGraph* g, int src, int* h) {
    int n = g->numVertices;
    for (int i = 0; i < n; i++) h[i] = INF;
    h[src] = 0;

    for (int k = 0; k < n - 1; k++) {
        int updated = 0;
        for (int u = 0; u < n; u++) {
            for (LGNode* node = g->adjList[u]; node; node = node->next) {
                int v = node->vertex;
                int w = node->weight;
                if (h[u] == INF || h[u] + w >= h[v]) continue;
                h[v] = h[u] + w;
                updated = 1;
            }
        }
        if (!updated) break;
    }

    // Find negative cycles
    for (int u = 0; u < n; u++) {
        for (LGNode* node = g->adjList[u]; node; node = node->next) {
            int v = node->vertex;
            int w = node->weight;
            if (h[u] != INF && h[u] + w < h[v]) return 0;
        }
    }

    return 1;
}

#pragma endregion Bellman-Ford

#pragma region Dijkstra

void dijkstra(ListGraph* g, int src, int* dist, int* h, int reweight) {
    int n = g->numVertices;
    FibHeap* heap = fib_heap_create();
    FibNode* nodes[MAX_VERTICES] = {0};
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        nodes[i] = fib_node_create(i, INF);
        fib_insert(heap, nodes[i]);
    }
    dist[src] = 0;
    fib_dec_key(heap, nodes[src], 0);

    while (heap->size > 0) {
        FibNode* min = fib_extract_min(heap);
        int u = min->vertex;
        for (LGNode* node = g->adjList[u]; node; node = node->next) {
            int v = node->vertex;
            int w = node->weight;
            if (reweight && h) w = w + h[u] - h[v];
            if (dist[u] == INF || dist[u] + w >= dist[v]) continue;
            dist[v] = dist[u] + w;
            fib_dec_key(heap, nodes[v], dist[v]);
        }
        free(min);
    }
    if (!reweight || !h) return;
    for (int v = 0; v < n; v++) {
        if (dist[v] == INF) continue;
        dist[v] = dist[v] + h[v] - h[src];
    }

    free(heap);
}

#pragma endregion Dijkstra

#pragma region Johnson

void print_h_vector(const int* h, int n) {
    printf("h vector: ");
    for (int i = 0; i < n; i++) {
        if (h[i] == INF) printf(" INF");
        else printf("%4d", h[i]);
    }
    printf("\n");
}

void print_w_hat(ListGraph* g, const int* h) {
    printf("w_hat edges (reweighted):\n");
    for (int u = 0; u < g->numVertices; u++) {
        for (LGNode* node = g->adjList[u]; node; node = node->next) {
            int v = node->vertex;
            int wHat = node->weight + h[u] - h[v];
            printf("  %d -> %d : %d (w_hat)\n", u, v, wHat);
        }
    }
}

int johnson(ListGraph* g, int D[MAX_VERTICES][MAX_VERTICES]) {
    int n = g->numVertices;
    ListGraph* g2 = list_graph_create(n + 1);

    for (int u = 0; u < n; u++)
        for (LGNode* node = g->adjList[u]; node; node = node->next)
            list_graph_add_edge(g2, u, node->vertex, node->weight);

    for (int v = 0; v < n; v++) list_graph_add_edge(g2, n, v, 0);

    int h[MAX_VERTICES + 1];
    if (!bellman_ford(g2, n, h)) {
        printf("Negative-weight cycle detected!\n");
        list_graph_free(g2);
        return 0;
    }

    printf("Bellman-Ford h vector:\n");
    print_h_vector(h, n);

    ListGraph* gHat = list_graph_create(n);
    for (int u = 0; u < n; u++) {
        for (LGNode* node = g->adjList[u]; node; node = node->next) {
            int v = node->vertex;
            int wHat = node->weight + h[u] - h[v];
            list_graph_add_edge(gHat, u, v, wHat);
        }
    }

    printf("w_hat (reweighted) edges:\n");
    print_w_hat(gHat, h);

    for (int u = 0; u < n; u++) {
        int dist[MAX_VERTICES];
        dijkstra(gHat, u, dist, h, 0);
        for (int v = 0; v < n; v++) {
            if (dist[v] < INF) D[u][v] = dist[v] + h[v] - h[u];
            else D[u][v] = INF;
        }
    }

    list_graph_free(g2);
    list_graph_free(gHat);
    return 1;
}

#pragma endregion Johnson

int main(void) {
    int numVertices = 6;
    int W[6][6] = {
        {0, INF, INF, INF, -1, INF},
        {1, 0, INF, 2, INF, INF},
        {INF, 2, 0, INF, INF, -8},
        {-4, INF, INF, 0, 3, INF},
        {INF, 7, INF, INF, 0, INF},
        {INF, 5, 10, INF, INF, 0}
    };
    ListGraph* g = list_graph_create(numVertices);
    for (int u = 0; u < numVertices; u++) {
        for (int v = 0; v < numVertices; v++) {
            if (W[u][v] != INF && u != v) {
                list_graph_add_edge(g, u, v, W[u][v]);
            }
        }
    }

    int D[MAX_VERTICES][MAX_VERTICES];
    if (!johnson(g, D)) {
        printf("Negative cycle detected. Returning.\n");
        list_graph_free(g);
        return 0;
    }

    printf("Johnson's all-pairs shortest paths:\n");
    for (int u = 0; u < numVertices; u++) {
        for (int v = 0; v < numVertices; v++) {
            if (D[u][v] == INF) printf(" INF");
            else  printf("%4d", D[u][v]);
        }
        printf("\n");
    }

    return 0;
}