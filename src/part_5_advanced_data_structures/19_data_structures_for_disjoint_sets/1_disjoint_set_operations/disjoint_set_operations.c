#include "part_5_advanced_data_structures/19_data_structures_for_disjoint_sets/data_structures_for_disjoint_sets.h"

int parents[MAX_VERTICES];
int ranks[MAX_VERTICES];

void make_set(int n, int initRanks) {
    for (int i = 0; i < n; i++) {
        parents[i] = i;
        ranks[i] = initRanks;
    }
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

int find(int u) {
    if (u != parents[u]) parents[u] = find(parents[u]);
    return parents[u];
}

int is_same_component(int u, int v) {
    return find(u) == find(v);
}

void connected_components(Graph* g) {
    int numVerts = g->numVertices;
    make_set(numVerts, 0);
    int i, j;

    for (i = 0; i < numVerts; i++) {
        for (j = 0; j < numVerts; j++) {
            if (g->edges[i][j] && !is_same_component(i, j)) union_sets(i, j);
        }
    }

    int printed[MAX_VERTICES] = {0};
    int compNum = 1;

    for (i = 0; i < numVerts; i++) {
        int root = find(i);
        if (!printed[root]) {
            printf("Component %d:", compNum++);
            for (j = 0; j < numVerts; j++) {
                if (find(j) == root) printf("%d ", j);
            }
            printf("\n");
            printed[root] = 1;
        }
    }
}

void add_edge(Graph* g, int u, int v) {
    g->edges[u][v] = 1;
    g->edges[v][u] = 1;
}
