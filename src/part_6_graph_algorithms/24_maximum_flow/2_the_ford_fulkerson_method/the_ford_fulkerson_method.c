#include "part_6_graph_algorithms/24_maximum_flow/maximum_flow.h"

#pragma region Basic Ford-Fulkerson implementation

int flow_dfs(FlowMatGraph* g, int u, int t, int parent[], int visited[]) {
    visited[u] = 1;
    if (u == t) return 1;

    for (int v = 0; v < g->numVertices; v++) {
        if (visited[v] || g->adjMat[u][v] <= 0) continue;
        parent[v] = u;
        if (flow_dfs(g, v, t, parent, visited)) return 1;
    }

    return 0;
}

int ford_fulkerson(FlowMatGraph* g, int s, int t) {
    /*
        DFS-based approach.
        O(E|f*|)
    */
    int u, v;
    FlowMatGraph* residual = flow_mat_graph_create(g->numVertices);

    for (u = 0; u < g->numVertices; u++) {
        for (v = 0; v < g->numVertices; v++) {
            residual->adjMat[u][v] = g->adjMat[u][v];
            g->flow[u][v] = 0;
        }
    }

    int parent[MAX_GRAPH_VERTICES];
    int visited[MAX_GRAPH_VERTICES];
    int maxFlow = 0;

    while (
        memset(visited, 0, sizeof(visited)),
        memset(parent, 0, sizeof(parent)),
        flow_dfs(residual, s, t, parent, visited)
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

    flow_mat_graph_free(residual);
    return maxFlow;
}

#pragma endregion Basic Ford-Fulkerson implementation

#pragma region Edmonds-Karp algorithm

int flow_bfs(FlowMatGraph* graph, int s, int t, int parent[]) {
    int visited[MAX_GRAPH_VERTICES] = {0};
    int queue[MAX_GRAPH_VERTICES];
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

int edmonds_karp(FlowMatGraph* g, int s, int t) {
    /*
        BFS-based approach.
        O(VE^2)
    */
    int u, v;
    FlowMatGraph* residual = flow_mat_graph_create(g->numVertices);

    for (u = 0; u < g->numVertices; u++) {
        for (v = 0; v < g->numVertices; v++) {
            residual->adjMat[u][v] = g->adjMat[u][v];
            g->flow[u][v] = 0;
        }
    }

    int parent[MAX_GRAPH_VERTICES];
    int maxFlow = 0;

    while (flow_bfs(residual, s, t, parent)) {
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

    flow_mat_graph_free(residual);
    return maxFlow;
}

#pragma endregion Edmonds-Karp algorithm

#pragma region 24.2-10

void decompose_flow(FlowMatGraph* g, int s, int t) {
    FlowMatGraph* flowGraph = flow_mat_graph_create(g->numVertices);
    for (int u = 0; u < g->numVertices; u++)
        for (int v = 0; v < g->numVertices; v++)
            flowGraph->adjMat[u][v] = g->flow[u][v];

    int parent[MAX_GRAPH_VERTICES];
    int pathCnt = 0;

    printf("Decomposition into augmenting paths:\n");
    while (flow_bfs(flowGraph, s, t, parent)) {
        int pathFlow = INT_MAX;
        int v;

        for (v = t; v != s; v = parent[v]) {
            int u = parent[v];
            if (flowGraph->adjMat[u][v] < pathFlow)
                pathFlow = flowGraph->adjMat[u][v];
        }

        printf("Path %d, (flow %d): ", ++pathCnt, pathFlow);
        int path[MAX_GRAPH_VERTICES];
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

    flow_mat_graph_free(flowGraph);
}

#pragma endregion 24.2-10

#pragma region 24.2-11

int flow_graph_edge_connectivity(FlowMatGraph* g) {
    int n = g->numVertices;
    int minFlow = INT_MAX;
    int sink = 0;

    for (int src = 0; src < n; src++) {
        if (src == sink) continue;
        FlowMatGraph* flowGraph = flow_mat_graph_create(n);
        for (int u = 0; u < n; u++)
            for (int v = 0; v < n; v++)
                if (g->adjMat[u][v]) flowGraph->adjMat[u][v] = 1;

        int flow = edmonds_karp(flowGraph, src, sink);
        minFlow = fmin(flow, minFlow);
        flow_mat_graph_free(flowGraph);
    }

    return minFlow;
}

#pragma endregion 24.2-11

#pragma region 24.2-12

void cancel_out_src_inflow(FlowMatGraph* g, int src) {
    int n = g->numVertices;

    for (int v = 0; v < n; v++) {
        if (v == src || g->flow[v][src] == 0) continue;
        
        FlowMatGraph* flowGraph = flow_mat_graph_create(n);
        flow_graph_copy(flowGraph, g, 1);

        int parent[MAX_GRAPH_VERTICES];
        int visited[MAX_GRAPH_VERTICES] = {0};

        if (!flow_dfs(flowGraph, src, v, parent, visited)) {
            g->flow[v][src] = 0;
            flow_mat_graph_free(flowGraph);
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

        flow_mat_graph_free(flowGraph);

        if (g->flow[v][src] > 0) v--;
    }
}

#pragma endregion 24.2-12
