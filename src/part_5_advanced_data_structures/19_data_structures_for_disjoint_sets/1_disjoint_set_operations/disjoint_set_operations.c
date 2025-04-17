#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef unsigned int uint;

typedef struct {
    int numVertices;
    int edges[MAX_VERTICES][MAX_VERTICES];
} Graph;

int parents[MAX_VERTICES];
int ranks[MAX_VERTICES];

void make_set(int n);
void union_sets(int u, int v);
int find(int u);
int same_component(int u, int v);
void connected_components(Graph* g);
void add_edge(Graph* g, int u, int v);

void make_set(int n) {
    for (int i = 0; i < n; i++) {
        parents[i] = i;
        ranks[i] = 0;
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

int same_component(int u, int v) {
    return find(u) == find(v);
}

void connected_components(Graph* g) {
    int numVerts = g->numVertices;
    make_set(numVerts);
    int i, j;

    for (i = 0; i < numVerts; i++) {
        for (j = 0; j < numVerts; j++) {
            if (g->edges[i][j] && !same_component(i, j)) union_sets(i, j);
        }
    }

    int printed[MAX_VERTICES] = {0};
    uint compNum = 1;

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

int main(void) {
    Graph* g = malloc(sizeof(Graph));
    g->numVertices = 6;

    // Init adj mat
    for (int i = 0; i < g->numVertices; i++)
        for (int j = 0; j < g->numVertices; j++)
            g->edges[i][j] = 0;

    add_edge(g, 0, 1);
    add_edge(g, 1, 2);
    add_edge(g, 3, 4);

    connected_components(g);

    printf("\nAre 0 and 2 in the same component? %s\n", same_component(0, 2) ? "Yes" : "No");
    printf("Are 0 and 5 in the same component? %s\n", same_component(0, 5) ? "Yes" : "No");

    free(g);
    return 0;
}