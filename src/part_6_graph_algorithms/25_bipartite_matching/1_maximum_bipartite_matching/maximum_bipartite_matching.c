#include "part_6_graph_algorithms/25_bipartite_matching/bipartite_matching.h"

#pragma region Hopcroft-Karp

BipartiteGraph* bipartite_graph_init(int leftSize, int rightSize) {
    BipartiteGraph* g = (BipartiteGraph*)safe_malloc(sizeof(BipartiteGraph));

    g->leftSize = leftSize;
    g->rightSize = rightSize;

    for (int i = 0; i <= leftSize; i++) {
        g->adjSize[i] = 0;
    }
    printf("Bipartite graph initialized\n");
    return g;
}

void bipartite_graph_add_edge(BipartiteGraph* g, int u, int v) {
    if (!g || u < 1 || u > g->leftSize || v < 1 || v > g->rightSize) return;
    g->adj[u][g->adjSize[u]++] = v;
}

void print_bipartite_graph(BipartiteGraph* g) {
    if (!g) return;

    printf("Bipartite Graph: (Left: %d, Right: %d):\n",
        g->leftSize, g->rightSize);
    for (int u = 1; u <= g->leftSize; u++) {
        printf("U%d -> ", u);
        for (int i = 0; i < g->adjSize[u]; i++) {
            printf("V%d ", g->adj[u][i]);
        }
        printf("\n");
    }
}

void print_matching(int pairU[], int leftSize) {
    printf("Matching edges:\n");
    for (int u = 1; u <= leftSize; u++) {
        if (pairU[u] != NIL) {
            printf("  U%d -- V%d\n", u, pairU[u]);
        }
    }
}

int bfs_build_layers(
    BipartiteGraph* g, 
    int pairU[], 
    int pairV[], 
    int dist[]
) {
    int queue[MAX_GRAPH_VERTICES];
    int front = 0;
    int rear = 0;

    // Init distances
    for (int u = 1; u <= g->leftSize; u++) {
        if (pairU[u] == NIL) {
            // Free vertex
            dist[u] = 0;
            queue[rear++] = u;
        } else {
            // Already matched
            dist[u] = INF;
        }
    }

    dist[NIL] = INF;

    while (front != rear) {
        int u = queue[front++];
        // Skip already processed
        if (dist[u] > dist[NIL]) continue;
        for (int i = 0; i < g->adjSize[u]; i++) {
            int v = g->adj[u][i];
            // Skip matched vertices
            if (dist[pairV[v]] != INF) continue;
            dist[pairV[v]] = dist[u] + 1;
            queue[rear++] = pairV   [v];
        }
    }

    // Have we found a path to a unmatched right vertex? 
    return dist[NIL] != INF;
}

int dfs_find_augmenting_path(
    BipartiteGraph* g, 
    int u, 
    int pairU[], 
    int pairV[], 
    int dist[]
) {
    /*
        Find augmenting paths in the layered graph.
    */
    if (u == NIL) return 1;

    for (int i = 0; i < g->adjSize[u]; i++) {
        int v = g->adj[u][i];
        if (dist[pairV[v]] != dist[u] + 1) continue;
        if (dfs_find_augmenting_path(g, pairV[v], pairU, pairV, dist)) {
            pairV[v] = u;
            pairU[u] = v;
            return 1;
        }
    }

    dist[u] = INF;
    return 0;
}

int hopcroft_karp(BipartiteGraph* g) {
    if (!g) return 0;

    int pairU[MAX_GRAPH_VERTICES];
    int pairV[MAX_GRAPH_VERTICES];
    int dist[MAX_GRAPH_VERTICES];

    // M = ∅
    for (int u = 1; u < g->leftSize; u++) 
        pairU[u] = NIL;

    for (int v = 1; v < g->rightSize; v++)
        pairV[v] = NIL;

    pairU[NIL] = NIL;
    pairV[NIL] = NIL;

    int matchingSize = 0;
    int currPhase = 1;

    while (bfs_build_layers(g, pairU, pairV, dist)) {
        for (int u = 1; u <= g->leftSize; u++) {
            if (pairU[u] != NIL) continue;
            if (dfs_find_augmenting_path(g, u, pairU, pairV, dist)) {
                matchingSize++;
                printf("  Found augmenting path from U%d\n", u);
            }
        }
        printf("  Matching size after phase %d: %d\n", 
            currPhase, matchingSize);
        currPhase++;
    }

    printf("\nAlgorithm completed in %d phases\n", currPhase - 1);
    print_matching(pairU, g->leftSize);

    return matchingSize;
}

void test_hopcroft_karp_algorithm(void) {
    const char* title = "Hopcroft-Karp algorithm";
    print_separator(title);
    int n1 = 4;
    BipartiteGraph* g1 = bipartite_graph_init(n1, n1);
    
    int edges[][2] = {
        {1, 1},
        {1, 2},
        {2, 1},
        {3, 2},
        {4, 2},
        {4, 4}
    };
    int numEdges = ARRAY_SIZE(edges);

    for (int i = 0; i < numEdges; i++)
        bipartite_graph_add_edge(g1, edges[i][0], edges[i][1]);

    print_bipartite_graph(g1);
    int maxMatching1 = hopcroft_karp(g1);
    printf("Maximum matching size: %d\n\n", maxMatching1);
    free(g1);
}

int earky_stopping_hopcroft_karp(BipartiteGraph* g) {
    if (!g) return 0;

    int pairU[MAX_GRAPH_VERTICES];
    int pairV[MAX_GRAPH_VERTICES];
    int dist[MAX_GRAPH_VERTICES];

    // M = ∅
    for (int u = 1; u < g->leftSize; u++) 
        pairU[u] = NIL;

    for (int v = 1; v < g->rightSize; v++)
        pairV[v] = NIL;

    pairU[NIL] = NIL;
    pairV[NIL] = NIL;

    int matchingSize = 0;
    int currPhase = 1;
    int n = MAX(g->leftSize, g->rightSize);
    int maxPhases = (int)ceil(3 * sqrt(n) / 2.0);

    while (bfs_build_layers(g, pairU, pairV, dist) && currPhase <= maxPhases) {
        for (int u = 1; u <= g->leftSize; u++) {
            if (pairU[u] != NIL) continue;
            if (dfs_find_augmenting_path(g, u, pairU, pairV, dist)) {
                matchingSize++;
                printf("  Found augmenting path from U%d\n", u);
            }
        }
        printf("  Matching size after phase %d: %d\n", 
            currPhase, matchingSize);
        currPhase++;
    }

    printf("\nAlgorithm completed in %d phases\n", currPhase - 1);
    print_matching(pairU, g->leftSize);

    return matchingSize;
}

void test_early_stopping_hopcroft_karp_algorithm(void) {
    const char* title = "Hopcroft-Karp algorithm";
    print_separator(title);
    int n1 = 4;
    BipartiteGraph* g1 = bipartite_graph_init(n1, n1);
    
    int edges[][2] = {
        {1, 1},
        {1, 2},
        {2, 1},
        {3, 2},
        {4, 2},
        {4, 4}
    };
    int numEdges = ARRAY_SIZE(edges);

    for (int i = 0; i < numEdges; i++)
        bipartite_graph_add_edge(g1, edges[i][0], edges[i][1]);

    print_bipartite_graph(g1);
    int maxMatching1 = hopcroft_karp(g1);
    printf("Maximum matching size: %d\n\n", maxMatching1);
    free(g1);
}

#pragma endregion Hopcroft-Karp
