#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma region Graph utils

#define MAX_VERTICES 10

typedef struct MatGraph {
    int adjMat[MAX_VERTICES][MAX_VERTICES];
    int flow[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
} MatGraph;

MatGraph* mat_graph_create(int numVertices) {
    MatGraph* g = malloc(sizeof(MatGraph));
    g->numVertices = numVertices;
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            g->adjMat[i][j] = 0;
            g->flow[i][j] = 0;
        }
    }
    return g;
}

void mat_graph_free(MatGraph* g) {
    free(g);
}

void mat_graph_add_directed_edge(MatGraph* g, int u, int v, int capacity) {
    g->adjMat[u][v] = capacity;
}

int bfs(MatGraph* g, int src, int sink, int parent[]) {
    int visited[MAX_VERTICES] = {0};
    int queue[MAX_VERTICES];
    int front = 0;
    int rear = 0;

    queue[rear++] = src;
    visited[src] = 1;
    parent[src] = -1;

    while (front != rear) {
        int u = queue[front++];

        for (int v = 0; v < g->numVertices; v++) {
            if (visited[v] || (g->adjMat[u][v] - g->flow[u][v]) <= 0) continue;
            if (v == sink) {
                parent[v] = u;
                return 1;
            }
            queue[rear++] = v;
            visited[v] = 1;
            parent[v] = u;
        }
    }

    return 0;
}

#pragma endregion Graph utils

#pragma region Edmonds-Karp

int edmonds_karp(MatGraph* g, int src, int sink) {
    int u, v;
    int parent[MAX_VERTICES];
    int maxFlow = 0;

    // Initialize flow to 0
    for (u = 0; u < g->numVertices; u++) {
        for (v = 0; v < g->numVertices; v++) {
            g->flow[u][v] = 0;
        }
    }

    while (bfs(g, src, sink, parent)) {
        int pathFlow = __INT_MAX__;
        for (int v = sink; v != src; v = parent[v]) {
            u = parent[v];
            pathFlow = fmin(pathFlow, g->adjMat[u][v] - g->flow[u][v]); 
        }

        for (v = sink; v != src; v = parent[v]) {
            u = parent[v];
            g->flow[u][v] += pathFlow;
            g->flow[v][u] -= pathFlow;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}

#pragma endregion Edmonds-Karp

#pragma region Maximum bipartite matching

MatGraph* create_bipartite_flow_graph(
    int leftSize,
    int rightSize,
    int bipartiteEdges[][2],
    int numEdges
) {
    int totalVertices = 2 + leftSize + rightSize; // both parts, sink, source
    MatGraph* g = mat_graph_create(totalVertices);
    int src = 0;
    int sink = totalVertices - 1;

    // src to left
    for (int i = 0; i < leftSize; i++) {
        int leftVertex = i + 1;
        mat_graph_add_directed_edge(g, src, leftVertex, 1);
    }

    // right to sink
    for (int i = 0; i < rightSize; i++) {
        int rightVertex = 1 + leftSize + i;
        mat_graph_add_directed_edge(g, rightVertex, sink, 1);
    }

    for (int i = 0; i < numEdges; i++) {
        int leftIdx = bipartiteEdges[i][0];
        int rightIdx = bipartiteEdges[i][1];

        int leftVertex = 1 + leftIdx;
        int rightVertex = 1 + leftSize + rightIdx;

        mat_graph_add_directed_edge(g, leftVertex, rightVertex, 1);
    }

    return g;
}

void print_bipartite_matching(MatGraph* g, int leftSize, int rightSize) {
    printf("Maximum Bipartite Matching:\n");
    int matchingCnt;

    for (int i = 1; i <= leftSize; i++) {
        for (int j = 1 + leftSize; j < 1 + leftSize + rightSize; j++) {
            if (g->flow[i][j] == 1) 
                printf("Left vertex %d matched with vertex %d\n", 
                    i - 1, j - 1 - leftSize);
                matchingCnt++;
        }
    }
    printf("Total matching size: %d\n", matchingCnt);
}

#pragma endregion Maximum bipartite matching

int main(void) {
    int leftSize = 3;
    int rightSize = 3;
    int edges[][2] = {
        {0, 0}, {0, 1}, 
        {1, 1}, {1, 2}, 
        {2, 0}, {2, 2} 
    };
    int numEdges = 6;

    MatGraph* g = create_bipartite_flow_graph(
        leftSize, rightSize, edges, numEdges);

    int src = 0;
    int sink = g->numVertices - 1;

    int maxMatching = edmonds_karp(g, src, sink);

    printf("Maximum matching size: %d\n", maxMatching);
    print_bipartite_matching(g, leftSize, rightSize);

    mat_graph_free(g);
    return 0;
}