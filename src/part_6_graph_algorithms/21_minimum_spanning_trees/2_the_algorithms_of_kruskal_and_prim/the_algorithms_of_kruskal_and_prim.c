#include "part_6_graph_algorithms/21_minimum_spanning_trees/minimum_spanning_trees.h"

#pragma region Union find utils

int kruskalParents[MAX_VERTICES];
int kruskalRanks[MAX_VERTICES];

#pragma endregion Union find utils

#pragma region Graph utils

ExplicitAdjListGraph* explicit_adj_list_graph_create(int numVertices) {
    ExplicitAdjListGraph* g = malloc(sizeof(ExplicitAdjListGraph));
    g->numVertices = numVertices;
    for (int i = 0; i < numVertices; i++)
        g->adjList[i].neiCnt = 0;
    return g;
}

void explicit_adj_list_graph_free(ExplicitAdjListGraph* g) {
    free(g);
}

void explicit_adj_list_graph_add_undirected_weighted_edge(
    ExplicitAdjListGraph* g, 
    int u, 
    int v, 
    int weight
) {
    g->adjList[u].neis[g->adjList[u].neiCnt] = v;
    g->adjList[u].weights[g->adjList[u].neiCnt] = weight;
    g->adjList[u].neiCnt++;

    g->adjList[v].neis[g->adjList[v].neiCnt] = u;
    g->adjList[v].weights[g->adjList[v].neiCnt] = weight;
    g->adjList[v].neiCnt++;
}

Edge edges[MAX_EDGES];
int edgeCnt = 0;

void mst_add_edge(int u, int v, int weight) {
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

ExplicitAdjListGraph* kruskal(int numVertices, Edge* edges, int edgeCnt) {
    make_set(numVertices);
    qsort(edges, edgeCnt, sizeof(Edge), compare_edges);

    ExplicitAdjListGraph* mst = explicit_adj_list_graph_create(numVertices);

    for (int i = 0; i < edgeCnt; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].weight;

        if (!is_same_component(u, v)) {
            union_sets(u, v);
            explicit_adj_list_graph_add_undirected_weighted_edge(mst, u, v, w);
            printf("MST edge: %d - %d (weight %d)\n", u, v, w);
        }
    }

    return mst;
}

#pragma endregion Kruskal

#pragma region Min heap utils
PrimMinHeap* prim_min_heap_create() {
    PrimMinHeap* heap = malloc(sizeof(PrimMinHeap));
    heap->size = 0;
    return heap;
}

void prim_min_heap_swap(PrimMinHeap* heap, int i, int j) {
    PrimMinHeapNode* tmp = heap->nodes[i];
    heap->nodes[i] = heap->nodes[j];
    heap->nodes[j] = tmp;
}

void prim_min_heap_insert(PrimMinHeap* heap, int vertex, int weight) {
    PrimMinHeapNode* node = malloc(sizeof(PrimMinHeapNode));
    node->vertex = vertex;
    node->weight = weight;
    heap->nodes[heap->size++] = node;

    int i = heap->size - 1;
    while (i > 0 && heap->nodes[i]->weight < heap->nodes[(i - 1) / 2]->weight) {
        prim_min_heap_swap(heap, i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

PrimMinHeapNode* prim_min_heap_extract_min(PrimMinHeap* heap) {
    if (heap->size == 0) return NULL;

    PrimMinHeapNode* minNode = heap->nodes[0];
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
            prim_min_heap_swap(heap, i, smallest);
            i = smallest;
        } else {
            break;
        }
    }

    return minNode;
}

void prim_min_heap_decrease_key(PrimMinHeap* heap, int vertex, int newWeight) {
    for (int i = 0; i < heap->size; i++) {
        if (heap->nodes[i]->vertex == vertex) {
            heap->nodes[i]->weight = newWeight;
            int j = i;
            while (j > 0 && heap->nodes[j]->weight < heap->nodes[(j - 1) / 2]->weight) {
                prim_min_heap_swap(heap, j, (j - 1) / 2);
                j = (j - 1) / 2;
            }
            break;
        }
    }
}

#pragma endregion Min heap utils

#pragma region Prim

void prim(ExplicitAdjListGraph* g, int source) {
    int parent[MAX_VERTICES];
    int key[MAX_VERTICES];
    int inMST[MAX_VERTICES] = {0};

    PrimMinHeap* heap = prim_min_heap_create();

    for (int i = 0; i < g->numVertices; i++) {
        key[i] = INT_MAX;
        parent[i] = -1;
    }
    key[source] = 0;
    prim_min_heap_insert(heap, source, 0);

    while (heap->size > 0) {
        PrimMinHeapNode* node = prim_min_heap_extract_min(heap);
        int u = node->vertex;
        free(node);

        inMST[u] = 1;

        for (int i = 0; i < g->adjList[u].neiCnt; i++) {
            int v = g->adjList[u].neis[i];
            int weight = g->adjList[u].weights[i];

            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                prim_min_heap_decrease_key(heap, v, key[v]);
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
