#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define TASK 1

#pragma region Graph utils

#define MAX_VERTICES 200

typedef struct FlowGraph {
    int adjMat[MAX_VERTICES][MAX_VERTICES];
    int flow[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
} FlowGraph;

FlowGraph* flow_graph_create(int numVertices) {
    FlowGraph* g = malloc(sizeof(FlowGraph));
    g->numVertices = numVertices;
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            g->adjMat[i][j] = 0;
            g->flow[i][j] = 0;
        }
    }

    return g;
}

void flow_graph_add_edge(FlowGraph* g, int u, int v, int capacity) {
    g->adjMat[u][v] = capacity;
}

void flow_graph_free(FlowGraph* g) {
    free(g);
}

int bfs(FlowGraph* g, int src, int sink, int parent[]) {
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

int edmonds_karp(FlowGraph* g, int src, int sink) {
    int u, v;
    int parent[MAX_VERTICES];
    int maxFlow = 0;

    for (u = 0; u < g->numVertices; u++)
        for (v = 0; v < g->numVertices; v++)
            g->flow[u][v] = 0;

    while (bfs(g, src, sink, parent)) {
        int pathFlow = INT_MAX;
        for (v = sink; v != src; v = parent[v]) {
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

#pragma endregion Graph utils

#pragma region Escape problem

int grid_to_vertex(int row, int col, int n) {
    return row * n + col;
}

int is_boundary(int row, int col, int n) {
    return (row == 0 || row == n - 1 || col == 0 || col == n - 1);
}

FlowGraph* create_escape_flow_network(int n, int startingPoints[][2], int m) {
    const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int totalVertices = 2 * n * n + 2;
    int src = totalVertices - 2;
    int sink = totalVertices - 1;
    int i, j;

    FlowGraph* g = flow_graph_create(totalVertices);

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            int vertexIdx = grid_to_vertex(i, j, n);
            int vIn = 2 * vertexIdx;
            int vOut = 2 * vertexIdx + 1;
            flow_graph_add_edge(g, vIn, vOut, 1);
        }
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            int vertexIdx = grid_to_vertex(i, j, n);
            int vOut = 2 * vertexIdx + 1;

            for (int d = 0; d < 4; d++) {
                int ni = i + dirs[d][0]; 
                int nj = j + dirs[d][1];
                
                if (ni < 0 || ni >= n || nj < 0 || nj >= n) continue;

                int neiIdx = grid_to_vertex(ni, nj, n);
                int neiIn = 2 * neiIdx;

                flow_graph_add_edge(g, vOut, neiIn, 1);
            }
        }
    }

    // src to starting points
    for (i = 0; i < m; i++) {
        int startRow = startingPoints[i][0];
        int startCol = startingPoints[i][1];
        int vertexIdx = grid_to_vertex(startRow, startCol, n);
        int vIn = 2 * vertexIdx;
        flow_graph_add_edge(g, src, vIn, 1);
    }

    // boundary to sink
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (!is_boundary(i, j, n)) continue;
            int vertexIdx = grid_to_vertex(i, j, n);
            int vOut = 2 * vertexIdx + 1;
            flow_graph_add_edge(g, vOut, sink, 1);
        }
    }

    return g;
}

int can_escape(int n, int startingPoints[][2], int m) {
    FlowGraph* g = create_escape_flow_network(n, startingPoints, m);
    int src = g->numVertices - 2;
    int sink = g->numVertices - 1;

    int maxFlow = edmonds_karp(g, src, sink);

    printf("Maximum flow found: %d\n", maxFlow);
    printf("Number of starting points: %d\n", m);

    int canEscape = (maxFlow == m);
    flow_graph_free(g);

    return canEscape;
}

#pragma endregion Escape problem

int main(void) {
    switch (TASK)
    {
        case 1: {
            // Escape problem
            int n1 = 6;
            int m1 = 10;
            int startingPoints1[][2] = {
                {0, 2},
                {1, 1},
                {1, 2},
                {1, 3},
                {3, 1},
                {3, 2},
                {3, 3},
                {5, 1},
                {5, 2}, 
                {5, 3}
            };

            printf("Example A. Expected to succeed.\n");

            int result1 = can_escape(n1, startingPoints1, m1);
            if (result1) printf("Escape is possible\n");
            else printf("Escape is impossible.\n");

            printf("\n");

            int n2 = 6;
            int m2 = 11;
            int startingPoints2[][2] = {
                {0, 2},
                {1, 1},
                {1, 2},
                {1, 3},
                {3, 1},
                {3, 2},
                {3, 3},
                {4, 2},
                {5, 1},
                {5, 2}, 
                {5, 3}
            };
            
            printf("Example B. Expected to fail.\n");

            int result2 = can_escape(n2, startingPoints2, m2);      
            if (result2) printf("Escape is possible\n");
            else printf("Escape is impossible.\n");

            break;
        }
        
        default:
            break;
    }

    return 0;
}