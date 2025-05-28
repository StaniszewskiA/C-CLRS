#include <stdio.h>
#include <string.h>
#include <limits.h>

#define TASK 5
#define N 4

#pragma region Transitive closure of a dynamic graph

void print_bool_mat(int mat[N][N], const char* name) {
    printf("%s:\n", name);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) printf("%2d", mat[i][j]);
        printf("\n");
    }
    printf("\n");
}

void update_transitive_closure(int T[N][N], int n, int x, int y) {
    if (T[x][y]) return;
    T[x][y] = 1;
    for (int u = 0; u < n; u++) {
        if (!T[u][x] && u != x) continue;
        for (int v = 0; v < n; v++) {
            if (T[y][v] || v == y) T[u][v] = 1;
        }
    }
}

void update_transitive_closure_prime(int T[N][N], int n, int x, int y) {
    if (T[x][y]) return;
    T[x][y] = 1;

    int uQueue[N], vQueue[N];
    int pred[N], succ[N];
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

#define MAX_HEAP_SIZE 64
#define INF INT_MAX

typedef struct {
    int key;
    int val;
} HeapNode;

typedef struct {
    HeapNode data[MAX_HEAP_SIZE];
    int pos[MAX_HEAP_SIZE];
    int size;
    int d;
} DAryHeap;

void heap_init(DAryHeap* heap, int d) {
    heap->size = 0;
    heap->d = d;
    for (int i = 0; i < MAX_HEAP_SIZE; i++) heap->pos[i] = -1;
}

int heap_is_empty(DAryHeap* heap) {
    return heap->size == 0;
}

void heap_swap(DAryHeap* heap, int i, int j) {
    HeapNode tmp = heap->data[i];
    heap->data[i] = heap->data[j];
    heap->data[j] = tmp;
    heap->pos[heap->data[i].val] = i;
    heap->pos[heap->data[j].val] = j;
}

void heapify_up(DAryHeap* heap, int i) {
    while (i > 0) {
        int parent = (i - 1) / heap->d;
        if (heap->data[i].key >= heap->data[parent].key) break;
        heap_swap(heap, i, parent);
        i = parent;
    }
}

void heapify_down(DAryHeap* heap, int i) {
    while (1) {
        int min = i;
        for (int j = 1; j <= heap->d; j++) {
            int child = heap->d * i + j;
            if (child < heap->size && 
                heap->data[child].key < heap->data[min].key)
                min = child;
        }
        if (min == i) break;
        heap_swap(heap, i, min);
        i = min;
    }
}

void heap_insert(DAryHeap* heap, int key, int val) {
    int i = heap->size++;
    heap->data[i].key = key;
    heap->data[i].val = val;
    heap->pos[val] = i;
    heapify_up(heap, i);
}

void heap_dec_key(DAryHeap* heap, int val, int newKey) {
    int i = heap->pos[val];
    if (i == -1) return;
    if (newKey >= heap->data[i].key) return;
    heap->data[i].key = newKey;
    heapify_up(heap, i);
}

HeapNode heap_extract_min(DAryHeap* heap) {
    HeapNode min = heap->data[0];
    heap->pos[min.val] = -1;
    heap->data[0] = heap->data[--heap->size];
    heap->pos[heap->data[0].val] = 0;
    heapify_down(heap, 0);
    return min;
}

void print_mat(int mat[N][N], const char* name) {
    printf("%s:\n", name);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (mat[i][j] == INF) printf("%5s", "INF");
            else printf("%5d", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void dijkstra_eps_dense(int n, int W[N][N], int src, int dist[N], int d) {
    DAryHeap heap;
    heap_init(&heap, d);
    int visited[N] = {0};
    for (int i = 0; i < n; i++) dist[i] = INF;
    dist[src] = 0;
    heap_insert(&heap, 0, src);

    while (!heap_is_empty(&heap)) {
        HeapNode node = heap_extract_min(&heap);
        int u = node.val;
        if (visited[u]) continue;
        visited[u] = 1;
        for (int v = 0; v < n; v++) {
            if (W[u][v] >= INF || dist[v] <= dist[u] + W[u][v]) continue;
            dist[v] = dist[u] + W[u][v];
            if (heap.pos[v] == -1) heap_insert(&heap, dist[v], v);
            else heap_dec_key(&heap, v, dist[v]);
        }
    }
}

void apsp_eps_dense(int n, int W[N][N], int D[N][N], int d) {
    for (int src = 0; src < n; src++) dijkstra_eps_dense(n, W, src, D[src], d);
}

int bellman_ford(int n, int W[N][N], int h[N + 1]) {
    for (int i = 0; i <= n; i++) h[i] = INF;
    h[n] = 0;
    for (int k = 0; k < n; k++) {
        int updated = 0;
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                if (W[u][v] == INF || h[u] == INF) continue;
                if (h[u] + W[u][v] >= h[v]) continue;
                h[v] = h[v] + W[u][v];
                updated = 1;
            }
        }
        if (!updated) break;
    }

    for (int v = 0; v < n; v++) {
        for (int u = 0; u < n; u++) {
            if (W[u][v] == INF || h[u] == INF) continue;;
            if (h[u] + W[u][v] < h[v]) return 0;
        }
    }

    return 1;
}

void johnson(int n, int W[N][N], int D[N][N], int d) {
    int h[N + 1];
    if (!bellman_ford(n, W, h)) {
        printf("Negative-weight cycle detected.\n");
        return;
    }
    int WHat[N][N];

    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (W[u][v] != INF) WHat[u][v] = W[u][v] + h[u] - h[v];
            else WHat[u][v] = INF;
        }
    }

    for (int src = 0; src < n; src++) {
        dijkstra_eps_dense(n, WHat, src, D[src], d);
        for (int v = 0; v < n; v++) {
            if (D[src][v] != INF) D[src][v] = D[src][v] - h[src] + h[v];
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
            int T[N][N];
            memset(T, 0, sizeof(T));

            update_transitive_closure(T, n, 0, 1);
            print_bool_mat(T, "Transitive closure after adding vertex (0,1)");

            update_transitive_closure(T, n, 1, 2);
            print_bool_mat(T, "Transitive closure after adding vertex (1,2)");

            update_transitive_closure(T, n, 2, 3);
            print_bool_mat(T, "Transitive closure after adding vertex (2,3)");

            update_transitive_closure(T, n, 0, 3);
            print_bool_mat(T, "Transitive closure after adding vertex (0,3)");

            break;
        }

        case 2: {
            // Transitive closure of a dynamic graph C
            int n = 4;
            int T[N][N];
            memset(T, 0, sizeof(T));

            update_transitive_closure_prime(T, n, 0, 1);
            print_bool_mat(T, "Transitive closure after adding vertex (0,1)");

            update_transitive_closure_prime(T, n, 1, 2);
            print_bool_mat(T, "Transitive closure after adding vertex (1,2)");

            update_transitive_closure_prime(T, n, 2, 3);
            print_bool_mat(T, "Transitive closure after adding vertex (2,3)");

            update_transitive_closure_prime(T, n, 0, 3);
            print_bool_mat(T, "Transitive closure after adding vertex (0,3)");

            break;
        }

        case 3: {
            // Shortest paths in epsilon-dense graphs B
            int n = 4;
            int W[N][N] = {
                {0, 1, INF, 4},
                {INF, 0, 2, INF},
                {INF, INF, 0, 3},
                {INF, INF, INF, 0}
            };
            int dist[N];
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
            int W[N][N] = {
                {0, 1, INF, 4},
                {INF, 0, 2, INF},
                {INF, INF, 0, 3},
                {INF, INF, INF, 0}
            };
            int D[N][N];
            int d = 2;
            apsp_eps_dense(n, W, D, d);
            print_mat(D, "APSP (no negative weights)");
            break;
        }

        case 5: {
            // Shortest paths in epsilon-dense graphs D
            int n = 4;
            int W[N][N] = {
                {0, 1, INF, 4},
                {INF, 0, 2, INF},
                {INF, INF, 0, 3},
                {INF, INF, INF, 0}
            };
            int D[N][N];
            int d = 2;
            johnson(n, W, D, d);
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