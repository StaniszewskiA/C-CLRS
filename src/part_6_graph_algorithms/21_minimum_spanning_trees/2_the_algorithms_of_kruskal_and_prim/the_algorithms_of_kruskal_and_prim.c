#include <stdio.h>
#include <stdlib.h>

#define TASK 3
#define MAX_VERTICES 10

#pragma region Union find utils

int parents[MAX_VERTICES];
int ranks[MAX_VERTICES];

void make_set(int n) {
    for (int i = 0; i < n; i++) {
        parents[i] = i;
        ranks[i] = 1;
    }
}

int find(int u) {
    if (u != parents[u]) parents[u] = find(parents[u]);
    return parents[u];
}

int same_component(int u, int v) {
    return find(u) == find(v);
}

void union_sets(int u, int v) {
    int uRoot = find(u);
    int vRoot = find(v);

    if (ranks[uRoot] < ranks[vRoot]) parents[uRoot] = vRoot;
    else if (ranks[uRoot] > ranks[vRoot]) parents[vRoot] = uRoot;
    else {
        parents[vRoot] = uRoot;
        ranks[uRoot]++;
    }
}

#pragma endregion Union find utils

#pragma region Graph utils

#define MAX_NEIS 10
#define MAX_EDGES 100

typedef struct AdjList {
    int neis[MAX_NEIS];
    int weights[MAX_NEIS];
    int neiCnt;
} AdjList;

typedef struct ListGraph {
    AdjList adjList[MAX_VERTICES];
    int numVertices;
} ListGraph;

ListGraph* list_graph_create(int numVertices) {
    ListGraph* g = malloc(sizeof(ListGraph));
    g->numVertices = numVertices;
    for (int i = 0; i < numVertices; i++)
        g->adjList[i].neiCnt = 0;
    return g;
}

void list_graph_free(ListGraph* g) {
    free(g);
}

void list_graph_add_undirected_edge(ListGraph* g, int u, int v, int weight) {
    g->adjList[u].neis[g->adjList[u].neiCnt] = v;
    g->adjList[u].weights[g->adjList[u].neiCnt] = weight;
    g->adjList[u].neiCnt++;

    g->adjList[v].neis[g->adjList[v].neiCnt] = u;
    g->adjList[v].weights[g->adjList[v].neiCnt] = weight;
    g->adjList[v].neiCnt++;
}

typedef struct Edge {
    int u, v, weight;
} Edge;

Edge edges[MAX_EDGES];
int edgeCnt = 0;

void add_edge(int u, int v, int weight) {
    edges[edgeCnt].u = u;
    edges[edgeCnt].v = v;
    edges[edgeCnt].weight = weight;
    edgeCnt++;
    printf("Added edge from %d to %d with a weight of %d\n",
        u, v, weight);
}

int compare_edges(const void* a, const void* b) {
    Edge* ea = (Edge*)a;
    Edge* eb = (Edge*)b;
    return ea->weight - eb->weight;
}

#pragma endregion Graph utils

#pragma region Kruskal

ListGraph* kruskal(int numVertices, Edge* edges, int edgeCnt) {
    make_set(numVertices);
    qsort(edges, edgeCnt, sizeof(Edge), compare_edges);

    ListGraph* mst = list_graph_create(numVertices);

    for (int i = 0; i < edgeCnt; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].weight;

        if (!same_component(u, v)) {
            union_sets(u, v);
            list_graph_add_undirected_edge(mst, u, v, w);
            printf("MST edge: %d - %d (weight %d)\n", u, v, w);
        }
    }

    return mst;
}

#pragma endregion Kruskal

#pragma region Min heap utils

typedef struct MinHeapNode {
    int vertex;
    int weight;
} MinHeapNode;

typedef struct MinHeap {
    MinHeapNode* nodes[MAX_VERTICES];
    int size;
} MinHeap;

MinHeap* min_heap_create() {
    MinHeap* heap = malloc(sizeof(MinHeap));
    heap->size = 0;
    return heap;
}

void min_heap_swap(MinHeap* heap, int i, int j) {
    MinHeapNode* tmp = heap->nodes[i];
    heap->nodes[i] = heap->nodes[j];
    heap->nodes[j] = tmp;
}

void min_heap_insert(MinHeap* heap, int vertex, int weight) {
    MinHeapNode* node = malloc(sizeof(MinHeapNode));
    node->vertex = vertex;
    node->weight = weight;
    heap->nodes[heap->size++] = node;

    int i = heap->size - 1;
    while (i > 0 && heap->nodes[i]->weight < heap->nodes[(i - 1) / 2]->weight) {
        min_heap_swap(heap, i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

MinHeapNode* min_heap_extract_min(MinHeap* heap) {
    if (heap->size == 0) return NULL;

    MinHeapNode* minNode = heap->nodes[0];
    heap->nodes[0] = heap->nodes[--heap->size];

    // Min heapify
    int i = 0;
    while (i * 2 + 1 < heap->size) {
        int left = i * 2 + 1;
        int right = i * 2 + 2;
        int smallest = i;

        if (left < heap->size 
            && heap->nodes[left]->weight < heap->nodes[smallest]->weight) {
            smallest = left;
        }
        if (right < heap->size 
            && heap->nodes[right]->weight < heap->nodes[smallest]->weight) {
            smallest = right;
        }

        if (smallest != i) {
            min_heap_swap(heap, i, smallest);
            i = smallest;
        } else {
            break;
        }
    }

    return minNode;
}

void min_heap_decrease_key(MinHeap* heap, int vertex, int newWeight) {
    for (int i = 0; i < heap->size; i++) {
        if (heap->nodes[i]->vertex == vertex) {
            heap->nodes[i]->weight = newWeight;
            int j = i;
            while (j > 0 && heap->nodes[j]->weight < heap->nodes[(j - 1) / 2]->weight) {
                min_heap_swap(heap, j, (j - 1) / 2);
                j = (j - 1) / 2;
            }
            break;
        }
    }
}

#pragma endregion Min heap utils

#pragma region Prim

void prim(ListGraph* g, int source) {
    int parent[MAX_VERTICES];
    int key[MAX_VERTICES];
    int inMST[MAX_VERTICES] = {0};

    MinHeap* heap = min_heap_create();

    for (int i = 0; i < g->numVertices; i++) {
        key[i] = INT_MAX;
        parent[i] = -1;
    }
    key[source] = 0;
    min_heap_insert(heap, source, 0);

    while (heap->size > 0) {
        MinHeapNode* node = min_heap_extract_min(heap);
        int u = node->vertex;
        free(node);

        inMST[u] = 1;

        for (int i = 0; i < g->adjList[u].neiCnt; i++) {
            int v = g->adjList[u].neis[i];
            int weight = g->adjList[u].weights[i];

            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                min_heap_decrease_key(heap, v, key[v]);
            }
        }
    }

    printf("MST edges:\n");
    for (int i = 0; i < g->numVertices; i++) {
        if (parent[i] != -1) {
            printf("%d - %d (weight %d)\n", parent[i], i, key[i]);
        }
    }

    free(heap);
}

#pragma endregion Prim

#pragma region 21.2-2

#define GRAPH_SIZE 5

typedef struct {
    int parent;
    int weight;
} Pair;

void adj_mat_prim(int adjMat[GRAPH_SIZE][GRAPH_SIZE], int root) {
    int inMST[GRAPH_SIZE] = {0};
    Pair A[GRAPH_SIZE];

    for (int i = 0; i < GRAPH_SIZE; i++) {
        A[i].parent = -1;
        A[i].weight = INT_MAX;
    }

    A[root].weight = 0;
    inMST[root] = 1;

    for (int i = 0; i < GRAPH_SIZE; i++) {
        if (adjMat[root][i] != 0) {
            A[i].parent = root;
            A[i].weight = adjMat[root][i];
        }
    }

    while (1) {
        int min = INT_MAX;
        int k = -1;

        for (int v = 0; v < GRAPH_SIZE; v++) {
            if (!inMST[v] && A[v].weight < min) {
                min = A[v].weight;
                k = v;
            }
        }

        if (k == -1) break;

        inMST[k] = 1;
        printf("Add edge (%d, %d) with weight %d\n",
            A[k].parent, k, A[k].weight);

        for (int i = 0; i < GRAPH_SIZE; i++) {
            if (!inMST[i] && adjMat[k][i] != 0 && adjMat[k][i] < A[i].weight) {
                A[i].parent = k;
                A[i].weight = adjMat[k][i];
            }
        }
    }

    printf("Edge\tWeight\n");
    for (int i = 0; i < GRAPH_SIZE; i++) {
        if (A[i].parent != -1)
            printf("%d - %d\t%d\n", A[i].parent, i, A[i].weight);
    }
}

#pragma endregion 21.2-2

int main(void) {
    switch (TASK)
    {
        case 1: {
            // Kruskal
            int n = 4;
            make_set(n);

            add_edge(0, 1, 10);
            add_edge(0, 2, 6);
            add_edge(0, 3, 5);
            add_edge(1, 3, 15);
            add_edge(2, 3, 4);

            ListGraph* mst = kruskal(n, edges, edgeCnt);

            printf("\nMST adjacency list:\n");
            for (int i = 0; i < mst->numVertices; i++) {
                printf("%d:", i);
                for (int j = 0; j < mst->adjList[i].neiCnt; j++) {
                    printf(" %d", mst->adjList[i].neis[j]);
                }
                printf("\n");
            }

            list_graph_free(mst);
            break;
        }

        case 2: {
            // Prim
            int n = 4;
            ListGraph* g = list_graph_create(n);

            list_graph_add_undirected_edge(g, 0, 1, 10);
            list_graph_add_undirected_edge(g, 0, 2, 6);
            list_graph_add_undirected_edge(g, 0, 3, 5);
            list_graph_add_undirected_edge(g, 1, 3, 15);
            list_graph_add_undirected_edge(g, 2, 3, 4);

            printf("Running Prim's algorithm starting from vertex 0:\n");
            prim(g, 0);

            list_graph_free(g);
            break;
        }

        case 3: {
            // Adjacency matrix Prim
            int adjMat[GRAPH_SIZE][GRAPH_SIZE] = {
                {0, 2, 0, 6, 0},
                {2, 0, 3, 8, 5},
                {0, 3, 0, 0, 7},
                {6, 8, 0, 0, 9},
                {0, 5, 7, 9, 0}
            };
            int root = 0;
            adj_mat_prim(adjMat, root);

            break;
        }
    
        default:
            break;
    }
}
