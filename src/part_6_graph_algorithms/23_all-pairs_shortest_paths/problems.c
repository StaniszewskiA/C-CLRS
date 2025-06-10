#include "part_6_graph_algorithms/23_all-pairs_shortest_paths/all-pairs_shortest_paths.h"

#define TASK 5

#pragma region Transitive closure of a dynamic graph

void update_transitive_closure(
    int T[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int n, 
    int x, 
    int y
) {
    if (T[x][y]) return;
    T[x][y] = 1;
    for (int u = 0; u < n; u++) {
        if (!T[u][x] && u != x) continue;
        for (int v = 0; v < n; v++) {
            if (T[y][v] || v == y) T[u][v] = 1;
        }
    }
}

void update_transitive_closure_prime(
    int T[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int n, 
    int x, 
    int y
) {
    if (T[x][y]) return;
    T[x][y] = 1;

    int uQueue[MAX_MAT_SIZE], vQueue[MAX_MAT_SIZE];
    int predCnt = 0;
    int succCnt = 0; 

    for (int u = 0; u < n; u++) {
        if (!T[u][x] && u != x) continue;
        uQueue[predCnt++] = u;
    }

    for (int v = 0; v < n; v++) {
        if (!T[y][v] && v != y) continue;
        vQueue[succCnt++] = v;
    }

    for (int i = 0; i < predCnt; i++) {
        int u = uQueue[i];
        for (int j = 0; j < succCnt; j++) {
            int v = vQueue[j];
            if (T[u][v]) continue;
            T[u][v] = 1;
        }
    }
}

#pragma endregion Transitive closure of a dynamic graph

#pragma region Shortest paths in epsilon-dense graphs

void dary_heap_init(DAryHeap* heap, int d) {
    heap->size = 0;
    heap->d = d;
    for (int i = 0; i < MAX_HEAP_SIZE; i++) heap->pos[i] = -1;
}

int dary_heap_is_empty(DAryHeap* heap) {
    return heap->size == 0;
}

void dary_heap_swap(DAryHeap* heap, int i, int j) {
    DaryHeapNode tmp = heap->data[i];
    heap->data[i] = heap->data[j];
    heap->data[j] = tmp;
    heap->pos[heap->data[i].val] = i;
    heap->pos[heap->data[j].val] = j;
}

void dary_heapify_up(DAryHeap* heap, int i) {
    while (i > 0) {
        int parent = (i - 1) / heap->d;
        if (heap->data[i].key >= heap->data[parent].key) break;
        dary_heap_swap(heap, i, parent);
        i = parent;
    }
}

void dary_heapify_down(DAryHeap* heap, int i) {
    while (1) {
        int min = i;
        for (int j = 1; j <= heap->d; j++) {
            int child = heap->d * i + j;
            if (child < heap->size && 
                heap->data[child].key < heap->data[min].key)
                min = child;
        }
        if (min == i) break;
        dary_heap_swap(heap, i, min);
        i = min;
    }
}

void dary_heap_insert(DAryHeap* heap, int key, int val) {
    int i = heap->size++;
    heap->data[i].key = key;
    heap->data[i].val = val;
    heap->pos[val] = i;
    dary_heapify_up(heap, i);
}

void dary_heap_dec_key(DAryHeap* heap, int val, int newKey) {
    int i = heap->pos[val];
    if (i == -1) return;
    if (newKey >= heap->data[i].key) return;
    heap->data[i].key = newKey;
    dary_heapify_up(heap, i);
}

DaryHeapNode dary_heap_extract_min(DAryHeap* heap) {
    DaryHeapNode min = heap->data[0];
    heap->pos[min.val] = -1;
    heap->data[0] = heap->data[--heap->size];
    heap->pos[heap->data[0].val] = 0;
    dary_heapify_down(heap, 0);
    return min;
}

void dijkstra_eps_dense(
    int n, 
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int src, 
    int dist[MAX_MAT_SIZE], 
    int d
) {
    DAryHeap heap;
    dary_heap_init(&heap, d);
    int visited[MAX_MAT_SIZE] = {0};
    for (int i = 0; i < n; i++) dist[i] = INF;
    dist[src] = 0;
    dary_heap_insert(&heap, 0, src);

    while (!dary_heap_is_empty(&heap)) {
        DaryHeapNode node = dary_heap_extract_min(&heap);
        int u = node.val;
        if (visited[u]) continue;
        visited[u] = 1;
        for (int v = 0; v < n; v++) {
            if (W[u][v] >= INF || dist[v] <= dist[u] + W[u][v]) continue;
            dist[v] = dist[u] + W[u][v];
            if (heap.pos[v] == -1) dary_heap_insert(&heap, dist[v], v);
            else dary_heap_dec_key(&heap, v, dist[v]);
        }
    }
}

void apsp_eps_dense(
    int n, 
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int D[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int d
) {
    for (int src = 0; src < n; src++) dijkstra_eps_dense(n, W, src, D[src], d);
}

void eps_dense_johnson(
    int n,
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE],
    int D[MAX_MAT_SIZE][MAX_MAT_SIZE],
    int d
) {
    WeightedNodeListGraph* g_prime = weighted_node_list_graph_create(n + 1);
    if (!g_prime) {
        perror("Failed to create graph for Bellman-Ford in eps_dense_johnson");
        return;
    }

    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (W[u][v] != INF) {
                weighted_node_list_graph_add_edge(g_prime, u, v, W[u][v]);
            }
        }
    }

    int new_source_s = n; 
    for (int v_orig = 0; v_orig < n; v_orig++) {
        weighted_node_list_graph_add_edge(g_prime, new_source_s, v_orig, 0);
    }

    int h[MAX_MAT_SIZE + 1]; 
    if (!bellman_ford_johnson(g_prime, new_source_s, h)) {
        printf("Negative-weight cycle detected by Bellman-Ford in Johnson's.\n");
        weighted_node_list_graph_free(g_prime);
        return;
    }

    weighted_node_list_graph_free(g_prime); 
    int WHat[MAX_MAT_SIZE][MAX_MAT_SIZE];
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (W[u][v] != INF) {
                if (h[u] == INF || h[v] == INF) {
                    WHat[u][v] = INF;
                } else {
                    WHat[u][v] = W[u][v] + h[u] - h[v];
                }
            } else {
                WHat[u][v] = INF;
            }
        }
    }

    for (int src_orig = 0; src_orig < n; src_orig++) {
        dijkstra_eps_dense(n, WHat, src_orig, D[src_orig], d);

        for (int v_dest = 0; v_dest < n; v_dest++) {
            if (D[src_orig][v_dest] != INF) {
                if (h[src_orig] == INF || h[v_dest] == INF) {
                    D[src_orig][v_dest] = INF;
                } else {
                    D[src_orig][v_dest] = D[src_orig][v_dest] - h[src_orig] + h[v_dest];
                }
            }
        }
    }
}

#pragma endregion Shortest paths in epsilon-dense graphs

int main(void) {
    switch (TASK)
    {
        case 1: {
            // Transitive closure of a dynamic graph A
            int n = 4;
            int T[MAX_MAT_SIZE][MAX_MAT_SIZE];
            memset(T, 0, sizeof(T));

            update_transitive_closure(T, n, 0, 1);
            print_named_bool_mat(T, "Transitive closure after adding vertex (0,1)");

            update_transitive_closure(T, n, 1, 2);
            print_named_bool_mat(T, "Transitive closure after adding vertex (1,2)");

            update_transitive_closure(T, n, 2, 3);
            print_named_bool_mat(T, "Transitive closure after adding vertex (2,3)");

            update_transitive_closure(T, n, 0, 3);
            print_named_bool_mat(T, "Transitive closure after adding vertex (0,3)");

            break;
        }

        case 2: {
            // Transitive closure of a dynamic graph C
            int n = 4;
            int T[MAX_MAT_SIZE][MAX_MAT_SIZE];
            memset(T, 0, sizeof(T));

            update_transitive_closure_prime(T, n, 0, 1);
            print_named_bool_mat(T, "Transitive closure after adding vertex (0,1)");

            update_transitive_closure_prime(T, n, 1, 2);
            print_named_bool_mat(T, "Transitive closure after adding vertex (1,2)");

            update_transitive_closure_prime(T, n, 2, 3);
            print_named_bool_mat(T, "Transitive closure after adding vertex (2,3)");

            update_transitive_closure_prime(T, n, 0, 3);
            print_named_bool_mat(T, "Transitive closure after adding vertex (0,3)");

            break;
        }

        case 3: {
            // Shortest paths in epsilon-dense graphs B
            int n = 4;
            int W[MAX_MAT_SIZE][MAX_MAT_SIZE] = {
                {0, 1, INF, 4},
                {INF, 0, 2, INF},
                {INF, INF, 0, 3},
                {INF, INF, INF, 0}
            };
            int dist[MAX_MAT_SIZE];
            int d = 2;

            dijkstra_eps_dense(n, W, 0, dist, d);
            printf("Single-source shortest paths from 0:\n");
            for (int i = 0; i < n;i ++) printf("%d ", dist[i]);
            printf("\n");

            break;
        }

        case 4: {
            // Shortest paths in epsilon-dense graphs C
            int n = 4;
            int W[MAX_MAT_SIZE][MAX_MAT_SIZE] = {
                {0, 1, INF, 4},
                {INF, 0, 2, INF},
                {INF, INF, 0, 3},
                {INF, INF, INF, 0}
            };
            int D[MAX_MAT_SIZE][MAX_MAT_SIZE];
            int d = 2;
            apsp_eps_dense(n, W, D, d);
            print_named_mat(D, "APSP (no negative weights)");
            break;
        }

        case 5: {
            // Shortest paths in epsilon-dense graphs D
            int n = 4;
            int W[MAX_MAT_SIZE][MAX_MAT_SIZE] = {
                {0, 1, INF, 4},
                {INF, 0, 2, INF},
                {INF, INF, 0, 3},
                {INF, INF, INF, 0}
            };
            int D[MAX_MAT_SIZE][MAX_MAT_SIZE];
            int d = 2;
            eps_dense_johnson(n, W, D, d);
            printf("All-pairs shortest paths (Johnson):\n");
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    printf("%2d ", D[i][j] == INF ? -1 : D[i][j]);
                }
                printf("\n");
            }

            break;
        }
        
        default:
            break;
    }

    return 0;
}
