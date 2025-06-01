#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TASK 5

#pragma region Graph utils

#define MAX_VERTICES 10

typedef struct MatGraph {
    /*
        Flow network represented as
        adjacency matrix graph.
    */
    int adjMat[MAX_VERTICES][MAX_VERTICES]; // capacity
    int flow[MAX_VERTICES][MAX_VERTICES]; // flow 
    int numVertices;
} MatGraph;

MatGraph* mat_graph_create(int numVertices) {
    MatGraph* g = malloc(sizeof(MatGraph));
    g->numVertices = numVertices;
    for (int i = 0; i < numVertices; i++)
        for (int j = 0; j < numVertices; j++) {
            g->adjMat[i][j] = 0;
            g->flow[i][j] = 0;
        }
    return g;
}
void mat_graph_free(MatGraph* g) {
    free(g);
}

void mat_graph_add_directed_edge(MatGraph* g, int u, int v, int capacity) {
    g->adjMat[u][v] = capacity;
}

void mat_graph_add_undirected_edge(MatGraph* g, int u, int v) {
    g->adjMat[u][v] = 1;
    g->adjMat[v][u] = 1; 
}

void print_flow_matrix(MatGraph* g, const char* name) {
    printf("%s", name);
    int n = g->numVertices;
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            printf("%d ", g->flow[u][v]);
        }
        printf("\n");
    }    
}

void copy_graph(MatGraph* dest, MatGraph* src, int copyFlow) {
    for (int u = 0; u < src->numVertices; u++) {
        for (int v = 0; v < src->numVertices; v++) {
            if (copyFlow) dest->adjMat[u][v] = src->flow[u][v];
            else dest->adjMat[u][v] = src->adjMat[u][v];
        }
    }
}

#pragma endregion Graph utils

#pragma region Basic Ford-Fulkerson implementation

int dfs(MatGraph* g, int u, int t, int parent[], int visited[]) {
    visited[u] = 1;
    if (u == t) return 1;

    for (int v = 0; v < g->numVertices; v++) {
        if (visited[v] || g->adjMat[u][v] <= 0) continue;
        parent[v] = u;
        if (dfs(g, v, t, parent, visited)) return 1;
    }

    return 0;
}

int ford_fulkerson(MatGraph* g, int s, int t) {
    /*
        DFS-based approach.
        O(E|f*|)
    */
    int u, v;
    MatGraph* residual = mat_graph_create(g->numVertices);

    for (u = 0; u < g->numVertices; u++) {
        for (v = 0; v < g->numVertices; v++) {
            residual->adjMat[u][v] = g->adjMat[u][v];
            g->flow[u][v] = 0;
        }
    }

    int parent[MAX_VERTICES];
    int visited[MAX_VERTICES];
    int maxFlow = 0;

    while (
        memset(visited, 0, sizeof(visited)),
        memset(parent, 0, sizeof(parent)),
        dfs(residual, s, t, parent, visited)
    ) {
        int pathFlow = INT_MAX;
        printf("Augmenting path edges:\n");
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            printf(" %d -> %d (residual capacity: %d)\n", 
                u, v, residual->adjMat[u][v]);
            pathFlow = fmin(pathFlow, residual->adjMat[u][v]);
        }

        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            residual->adjMat[u][v] -= pathFlow;
            residual->adjMat[v][u] += pathFlow;

            if (g->adjMat[u][v] > 0) g->flow[u][v] += pathFlow;
            else g->flow[v][u] -= pathFlow;
        }

        maxFlow += pathFlow;
        printf("Current max flow: %d\n", maxFlow);
    }

    mat_graph_free(residual);
    return maxFlow;
}

#pragma endregion Basic Ford-Fulkerson implementation

#pragma region Edmonds-Karp algorithm

int bfs(MatGraph* graph, int s, int t, int parent[]) {
    int visited[MAX_VERTICES] = {0};
    int queue[MAX_VERTICES];
    int front = 0;
    int rear = 0;

    queue[rear++] = s;
    visited[s] = 1;
    parent[s] = -1;

    while (front != rear) {
        int u = queue[front++];
        for (int v = 0; v < graph->numVertices; v++) {
            if (visited[v] || graph->adjMat[u][v] <= 0) continue;
            queue[rear++] = v;
            parent[v] = u;
            visited[v] = 1;
            if (v == t) return 1;
        }
    }

    return 0;
}

int edmonds_karp(MatGraph* g, int s, int t) {
    /*
        BFS-based approach.
        O(VE^2)
    */
    int u, v;
    MatGraph* residual = mat_graph_create(g->numVertices);

    for (u = 0; u < g->numVertices; u++) {
        for (v = 0; v < g->numVertices; v++) {
            residual->adjMat[u][v] = g->adjMat[u][v];
            g->flow[u][v] = 0;
        }
    }

    int parent[MAX_VERTICES];
    int visited[MAX_VERTICES];
    int maxFlow = 0;

    while (bfs(residual, s, t, parent)) {
        int pathFlow = INT_MAX;
        printf("Augmenting path edges:\n");
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            printf(" %d -> %d (residual capacity: %d)\n", 
                u, v, residual->adjMat[u][v]);
            pathFlow = fmin(pathFlow, residual->adjMat[u][v]);
        }

        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            residual->adjMat[u][v] -= pathFlow;
            residual->adjMat[v][u] += pathFlow;

            if (g->adjMat[u][v] > 0) g->flow[u][v] += pathFlow;
            else g->flow[v][u] -= pathFlow;
        }

        maxFlow += pathFlow;
        printf("Current max flow: %d\n", maxFlow);
    }

    mat_graph_free(residual);
    return maxFlow;
}

#pragma endregion Edmonds-Karp algorithm

#pragma region 24.2-10

void decompose_flow(MatGraph* g, int s, int t) {
    MatGraph* flowGraph = mat_graph_create(g->numVertices);
    for (int u = 0; u < g->numVertices; u++)
        for (int v = 0; v < g->numVertices; v++)
            flowGraph->adjMat[u][v] = g->flow[u][v];

    int parent[MAX_VERTICES];
    int pathCnt = 0;

    printf("Decomposition into augmenting paths:\n");
    while (bfs(flowGraph, s, t, parent)) {
        int pathFlow = INT_MAX;
        int v;

        for (v = t; v != s; v = parent[v]) {
            int u = parent[v];
            if (flowGraph->adjMat[u][v] < pathFlow)
                pathFlow = flowGraph->adjMat[u][v];
        }

        printf("Path %d, (flow %d): ", ++pathCnt, pathFlow);
        int path[MAX_VERTICES];
        int pathLen = 0;

        for (v = t; v != s; v = parent[v]) path[pathLen++] = v;
        path[pathLen++] = s;

        for (int i = pathLen - 1; i > 0; i--) printf("%d -> ", path[i]);
        printf("%d\n", path[0]);

        for (v = t; v != s; v = parent[v]) {
            int u = parent[v];
            flowGraph->adjMat[u][v] -= pathFlow;
            if (flowGraph->adjMat[u][v] == 0) 
                printf("Deleted edge (%d, %d)\n", v, u);
        }
    }

    mat_graph_free(flowGraph);
}

#pragma endregion 24.2-10

#pragma region 24.2-11

int edge_connectivity(MatGraph* g) {
    int n = g->numVertices;
    int minFlow = INT_MAX;
    int sink = 0;

    for (int src = 0; src < n; src++) {
        if (src == sink) continue;
        MatGraph* flowGraph = mat_graph_create(n);
        for (int u = 0; u < n; u++)
            for (int v = 0; v < n; v++)
                if (g->adjMat[u][v]) flowGraph->adjMat[u][v] = 1;

        int flow = edmonds_karp(flowGraph, src, sink);
        minFlow = fmin(flow, minFlow);
        mat_graph_free(flowGraph);
    }

    return minFlow;
}

#pragma endregion 24.2-11

#pragma region 24.2-12

void cancel_out_src_inflow(MatGraph* g, int src) {
    int n = g->numVertices;

    for (int v = 0; v < n; v++) {
        if (v == src || g->flow[v][src] == 0) continue;
        
        MatGraph* flowGraph = mat_graph_create(n);
        copy_graph(flowGraph, g, 1);

        int parent[MAX_VERTICES];
        int visited[MAX_VERTICES] = {0};

        if (!dfs(flowGraph, src, v, parent, visited)) {
            g->flow[v][src] = 0;
            mat_graph_free(flowGraph);
            continue;
        }

        int pathFlow = g->flow[v][src];
        int curr = v;

        // min flow along the path
        while (parent[curr] != src) {
            int prev = parent[curr];
            pathFlow = fmin(pathFlow, g->flow[prev][curr]);
            curr = prev;
        }

        // consider src
        pathFlow = fmin(pathFlow, g->flow[src][curr]);

        // reduce
        curr = v;
        while (parent[curr] != src) {
            int prev = parent[curr];
            g->flow[prev][curr] -= pathFlow;
            curr = prev;
        }

        g->flow[src][curr] -= pathFlow;
        g->flow[v][src] -= pathFlow;

        mat_graph_free(flowGraph);

        if (g->flow[v][src] > 0) v--;
    }
}

#pragma endregion 24.2-12

int main(void) {
    switch (TASK)
    {
        case 1: {
            // Basic Ford-Fulkerson
            int n = 6;
            MatGraph* g = mat_graph_create(n);
            mat_graph_add_directed_edge(g, 0, 1, 16);
            mat_graph_add_directed_edge(g, 0, 2, 13);
            mat_graph_add_directed_edge(g, 1, 2, 10);
            mat_graph_add_directed_edge(g, 2, 1, 4);
            mat_graph_add_directed_edge(g, 1, 3, 12);
            mat_graph_add_directed_edge(g, 2, 4, 14);
            mat_graph_add_directed_edge(g, 3, 2, 9);
            mat_graph_add_directed_edge(g, 4, 3, 7);
            mat_graph_add_directed_edge(g, 3, 5, 20);
            mat_graph_add_directed_edge(g, 4, 5, 4);

            int maxFlow = edmonds_karp(g, 0, 5);
            printf("Maximum flow: %d\n", maxFlow);

            decompose_flow(g, 0, 5);

            mat_graph_free(g);
            break;
        }

        case 2: {
            // Edmonds-Karp
            int n = 3;
            MatGraph* g = mat_graph_create(n);
            mat_graph_add_directed_edge(g, 0, 1, 3);
            mat_graph_add_directed_edge(g, 1, 2, 2);
            mat_graph_add_directed_edge(g, 0, 2, 1);

            int maxFlow = edmonds_karp(g, 0, 2);
            printf("Maximum flow: %d\n", maxFlow);

            mat_graph_free(g);
            break;
        }

        case 3: {
            // 24.2-10
            int n = 3;
            MatGraph* g = mat_graph_create(n);
            mat_graph_add_directed_edge(g, 0, 1, 3);
            mat_graph_add_directed_edge(g, 1, 2, 2);
            mat_graph_add_directed_edge(g, 0, 2, 1);

            int maxFlow = edmonds_karp(g, 0, 2);
            printf("Maximum flow: %d\n", maxFlow);

            decompose_flow(g, 0, 2);

            mat_graph_free(g);

            break;
        }

        case 4: {
            // 24.2-11
            int n = 5;
            MatGraph* g = mat_graph_create(n);
            mat_graph_add_undirected_edge(g, 0, 1);
            mat_graph_add_undirected_edge(g, 1, 2);
            mat_graph_add_undirected_edge(g, 2, 3);
            mat_graph_add_undirected_edge(g, 3, 4);
            mat_graph_add_undirected_edge(g, 4, 0); // cycle

            int k = edge_connectivity(g);
            printf("Edge connectivity of the passed graph: %d\n", k);

            mat_graph_free(g);
            break;
        }

        case 5: {
            // 24.2-12
            int n = 4;
            MatGraph* g = mat_graph_create(n);
            
            mat_graph_add_directed_edge(g, 0, 1, 3);
            mat_graph_add_directed_edge(g, 1, 2, 2);
            mat_graph_add_directed_edge(g, 2, 3, 2);
            mat_graph_add_directed_edge(g, 2, 0, 1);

            int maxFlow = edmonds_karp(g, 0, 3);
            printf("Maximum flow: %d\n", maxFlow);

            printf("Adding artificial inflow to source for testing...\n");
            g->flow[2][0] = 1;
            g->flow[0][1] = 1;

            print_flow_matrix(g, "Flow matrix before cancelling the source inflow:\n");

            cancel_out_src_inflow(g, 0);

            print_flow_matrix(g, "Flow matrix after cancelling the source inflow:\n");

            mat_graph_free(g);
            break;
        }
        
        default:
            break;
    }
    
    return 0;
}