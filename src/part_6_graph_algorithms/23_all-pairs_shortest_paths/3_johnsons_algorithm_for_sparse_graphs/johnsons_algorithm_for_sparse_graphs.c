#include "part_6_graph_algorithms/23_all-pairs_shortest_paths/all-pairs_shortest_paths.h"

#pragma region Bellman-Ford

int bellman_ford_johnson(WeightedNodeListGraph* g, int src, int* h) {
    int n = g->numVertices;
    for (int i = 0; i < n; i++) h[i] = INF;
    h[src] = 0;

    for (int k = 0; k < n - 1; k++) {
        int updated = 0;
        for (int u = 0; u < n; u++) {
            for (WeightedNode* node = g->adjList[u]; node; node = node->next) {
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
        for (WeightedNode* node = g->adjList[u]; node; node = node->next) {
            int v = node->vertex;
            int w = node->weight;
            if (h[u] != INF && h[u] + w < h[v]) return 0;
        }
    }

    return 1;
}

#pragma endregion Bellman-Ford

#pragma region Dijkstra

void dijkstra_johnson(
    WeightedNodeListGraph* g, 
    int src, 
    int* dist, 
    int* h, 
    int reweight
) {
    int n = g->numVertices;
    FibHeap* heap = fib_heap_create();
    FibNode* nodes[MAX_GRAPH_VERTICES] = {0};
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
        for (WeightedNode* node = g->adjList[u]; node; node = node->next) {
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

void print_w_hat(WeightedNodeListGraph* g, const int* h) {
    printf("w_hat edges (reweighted):\n");
    for (int u = 0; u < g->numVertices; u++) {
        for (WeightedNode* node = g->adjList[u]; node; node = node->next) {
            int v = node->vertex;
            int wHat = node->weight + h[u] - h[v];
            printf("  %d -> %d : %d (w_hat)\n", u, v, wHat);
        }
    }
}

int johnson(
    WeightedNodeListGraph* g, 
    int D[MAX_GRAPH_VERTICES][MAX_GRAPH_VERTICES]
) {
    int n = g->numVertices;
    WeightedNodeListGraph* g2 = weighted_node_list_graph_create(n + 1);

    for (int u = 0; u < n; u++)
        for (WeightedNode* node = g->adjList[u]; node; node = node->next)
            weighted_node_list_graph_add_edge(g2, u, node->vertex, node->weight);

    for (int v = 0; v < n; v++) weighted_node_list_graph_add_edge(g2, n, v, 0);

    int h[MAX_GRAPH_VERTICES + 1];
    if (!bellman_ford_johnson(g2, n, h)) {
        printf("Negative-weight cycle detected!\n");
        weighted_node_list_graph_free(g2);
        return 0;
    }

    printf("Bellman-Ford h vector:\n");
    print_h_vector(h, n);

    WeightedNodeListGraph* gHat = weighted_node_list_graph_create(n);
    for (int u = 0; u < n; u++) {
        for (WeightedNode* node = g->adjList[u]; node; node = node->next) {
            int v = node->vertex;
            int wHat = node->weight + h[u] - h[v];
            weighted_node_list_graph_add_edge(gHat, u, v, wHat);
        }
    }

    printf("w_hat (reweighted) edges:\n");
    print_w_hat(gHat, h);

    for (int u = 0; u < n; u++) {
        int dist[MAX_GRAPH_VERTICES];
        dijkstra_johnson(gHat, u, dist, h, 0);
        for (int v = 0; v < n; v++) {
            if (dist[v] < INF) D[u][v] = dist[v] + h[v] - h[u];
            else D[u][v] = INF;
        }
    }

    weighted_node_list_graph_free(g2);
    weighted_node_list_graph_free(gHat);
    return 1;
}

#pragma endregion Johnson
