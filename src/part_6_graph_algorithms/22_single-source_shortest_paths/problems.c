#include <stdio.h>
#include <stdlib.h>

#define TASK 1

#pragma region Graph utils

#define MAX_VERTICES 10
#define MAX_EDGES 100

typedef struct MatGraph {
    int adjMat[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
} MatGraph;

MatGraph* mat_graph_create(int numVertices) {
    MatGraph* g = malloc(sizeof(MatGraph));
    g->numVertices = numVertices;

    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) g->adjMat[i][j] = 0;
    }

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

void mat_graph_add_directed_edge(MatGraph* g, int u, int v, int weight) {
    g->adjMat[u][v] = weight;
}

void mat_graph_remove_directed_edge(MatGraph* g, int u, int v, int weight) {
    g->adjMat[u][v] = 0;
}

void print_path(int pred[], int dest) {
    if (dest == -1) return;
    if (pred[dest] != -1) {
        print_path(pred, pred[dest]);
        printf(" -> ");
    }
    printf("%d", dest);
}

void print_solution(int dist[], int pred[], int numVertices, int src) {
    printf("Shortest paths from source %d:\n", src);
    for (int i = 0; i < numVertices; i++) {
        if (i != src) {
            printf("To vertex %d: ", i);
            if (dist[i] == INT_MAX) {
                printf("No path exists\n");
            } else {
                printf("Distance = %d, Path: ", dist[i]);
                print_path(pred, i);
                printf("\n");
            }
        }
    }
}

#pragma endregion Graph utils

#pragma region 22-1 Yens improvement to Bellman-Ford

#define INF INT_MAX 

void init_single_source(int dist[], int pred[], int numVertices, int src) {
    for (int i = 0; i < numVertices; i++) {
        dist[i] = INF;
        pred[i] = -1;
    }
    dist[src] = 0;
}

void relax_edge(int u, int v, int weight, int dist[], int pred[]) {
    if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
        dist[v] = dist[u] + weight;
        pred[v] = u;
    }
}

void yens_bellman_ford(MatGraph* g, int src, int dist[], int pred[]) {
    int n = g->numVertices;
    init_single_source(dist, pred, n, src);

    int passes = (n + 1) / 2;

    for (int pass = 0; pass < passes; pass++) {
        // Forward pass
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (g->adjMat[i][j] != 0) 
                    relax_edge(i, j, g->adjMat[i][j], dist, pred);
            }
        }

        // Backward pass
        for (int i = n - 1; i >= 0; i--) {
            for (int j = 0; j < i; j++) {
                if (g->adjMat[i][j] != 0)
                    relax_edge(i, j, g->adjMat[i][j], dist, pred);
            }
        }
    }
}

#pragma endregion 22-1 Yens improvement to Bellman-Ford

int main(void) {
    switch (TASK)
    {
        case 1: {
            // 22-1
            int numVertices = 6;
            MatGraph* g = mat_graph_create(numVertices);

            mat_graph_add_directed_edge(g, 0, 1, 10);
            mat_graph_add_directed_edge(g, 1, 2, 5);
            mat_graph_add_directed_edge(g, 2, 3, 7);
            mat_graph_add_directed_edge(g, 3, 1, -8); 
            mat_graph_add_directed_edge(g, 4, 3, 4);
            mat_graph_add_directed_edge(g, 0, 4, 3);
            mat_graph_add_directed_edge(g, 5, 0, 2);

            int dist[MAX_VERTICES];
            int pred[MAX_VERTICES];
            int src = 0;

            yens_bellman_ford(g, src, dist, pred);

            print_solution(dist, pred, numVertices, src);
            mat_graph_free(g);
            break;
        }
        
        default:
            break;
    }
}