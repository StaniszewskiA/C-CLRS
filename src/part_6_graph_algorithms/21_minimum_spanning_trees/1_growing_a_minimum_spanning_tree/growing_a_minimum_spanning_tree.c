#include <stdio.h>
#include <stdlib.h>

#pragma region Graph utils

#define MAX_VERTICES 10

typedef struct MatGraph {
    // Graph represented by adjacency matrix
    int adjMat[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
} MatGraph;

MatGraph* mat_graph_create(int numVertices) {
    MatGraph* g = malloc(sizeof(MatGraph));
    g->numVertices = numVertices;

    for (int i = 0; i < numVertices; i++) 
        for (int j = 0; j < numVertices; j++) g->adjMat[i][j] = 0;

    return g;
}

void mat_graph_free(MatGraph* g) {
    free(g);
}

void mat_graph_add_undirected_edge(MatGraph* g, int u, int v, int weight) {
    g->adjMat[u][v] = weight;
    g->adjMat[v][u] = weight;
}

void mat_graph_remove_undirected_edge(MatGraph* g, int u, int v) {
    g->adjMat[u][v] = 0;
    g->adjMat[v][u] = 0;
}

#pragma endregion Graph utils

#pragma region 21.1-11

int dfs_find_path(
    MatGraph* g,
    int u,
    int v,
    int* visited,
    int* parent,
    int* maxU,
    int* maxV,
    int* maxW
) {
    visited[u] = 1;
    if (u == v) return 1;

    for (int i = 0; i < g->numVertices; i++) {
        if (g->adjMat[u][i] != 0 && !visited[i]) {
            parent[i] = u;
            if (dfs_find_path(g, i, v, visited, parent, maxU, maxV, maxW)) {
                if (g->adjMat[u][i] > *maxW) {
                    *maxW = g->adjMat[u][i];
                    *maxU = u;
                    *maxV = i;
                }
                return 1;
            }
        }
    }

    return 0;
}

void update_mst(MatGraph* mst, int u, int v, int newWeight) {
    int visited[MAX_VERTICES] = {0};
    int parent[MAX_VERTICES];
    for (int i = 0; i < mst->numVertices; i++) parent[i] = -1;

    int maxU = -1, maxV = -1, maxW = -1;

    if (!dfs_find_path(mst, u, v, visited, parent, &maxU, &maxV, &maxW)) {
        printf("No path found from %d to %d in MST\n", u, v);
        return;
    }

    printf("Heaviest edge in path from %d to %d is (%d, %d) with weight %d\n", 
        u, v, maxU, maxV, maxW);

        if (newWeight < maxW) {
            printf("Replacing edge (%d, %d) with (%d, %d) of weight %d\n", 
                maxU, maxV, u, v, newWeight);
            mat_graph_remove_undirected_edge(mst, maxU, maxV);
            mat_graph_add_undirected_edge(mst, u, v, newWeight);
        } else {
            printf("No need to update the MST.\n");
        }
}

#pragma endregion 21.1-11

int main(void) {
    MatGraph* mst = mat_graph_create(5);

    mat_graph_add_undirected_edge(mst, 0, 1, 4);
    mat_graph_add_undirected_edge(mst, 1, 2, 3);
    mat_graph_add_undirected_edge(mst, 2, 3, 5);
    mat_graph_add_undirected_edge(mst, 3, 4, 6);

    update_mst(mst, 0, 4, 2);

    mat_graph_free(mst);

    return 0;
}