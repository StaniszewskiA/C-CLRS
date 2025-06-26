#include "part_6_graph_algorithms/20_elementary_graph_algorithms/elementary_graph_algorithms.h"

#pragma region Topological sort utils

void mat_graph_topo_sort_helper(
    MatGraph* g, 
    int v, 
    int visited[], 
    int stack[], 
    int *stackIdx
) {
    visited[v] = 1;
    for (int i = 0; i < g->numVertices; i++) {
        if (g->adjMat[v][i] && !visited[i]) mat_graph_topo_sort_helper(g, i, visited, stack, stackIdx);
    }
    stack[(*stackIdx)++] = v;
}

void mat_graph_topo_sort(MatGraph* g, int stack[]) {
    int visited[MAX_VERTICES] = {0};
    int stackIdx = 0;

    for (int i = 0; i < g->numVertices; i++) {
        if (!visited[i]) mat_graph_topo_sort_helper(g, i, visited, stack, &stackIdx);
    }

    // Get the topological order
    for (int i = 0; i < stackIdx / 2; i++) {
        int temp = stack[i];
        stack[i] = stack[stackIdx - i - 1];
        stack[stackIdx - i - 1] = temp;
    }
}

#pragma endregion Topological sort utils

#pragma region 20.4-2

int mat_graph_count_simple_paths(MatGraph* g, int s, int t) {
    int stack[MAX_VERTICES];
    mat_graph_topo_sort(g, stack);
    int paths[MAX_VERTICES] = {0};
    paths[t] = 1;

    for (int i = g->numVertices - 1; i >= 0; i--) {
        int u = stack[i];
        for (int v = 0; v < g->numVertices; v++) {
            if (g->adjMat[u][v]) paths[u] += paths[v];
        }
    }

    return paths[s];
}

#pragma endregion 20.4-2

#pragma region 20.4-3

int mat_graph_dfs_cycle_check(MatGraph* g, int v, int visited[], int parent) {
    visited[v] = 1;

    for (int u = 0; u < g->numVertices; u++) {
        if (g->adjMat[v][u] && !visited[u]) {
            if (mat_graph_dfs_cycle_check(g, u, visited, v)) return 1;
        } else if (u != parent) return 1;
    }

    return 0;
}

int mat_graph_is_acyclic(MatGraph* g) {
    int visited[MAX_VERTICES] = {0};
    for (int v = 0; v < g->numVertices; v++) {
        if (!visited[v]) {
            if (mat_graph_dfs_cycle_check(g, v, visited, -1)) return 0;
        }
    }
    return 1;
}

#pragma endregion 20.4-3

#pragma region 20.4-5

int mat_graph_indeg_topo_sort(MatGraph* g, int result[]) {
    int inDegs[MAX_VERTICES] = {0};
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    // Get in-degrees
    for (int u = 0; u < g->numVertices; u++) {
        for (int v = 0; v < g->numVertices; v++) {
            if (g->adjMat[u][v]) inDegs[v]++;
        }
    }

    // Queue up vertices with inDeg = 0
    for (int i = 0; i < g->numVertices; i++)
        if (inDegs[i] == 0) queue[rear++] = i;

    // Topo
    int idx = 0;
    while (front < rear) {
        int u = queue[front++];
        result[idx++] = u;

        // Remove outgoing edges
        for (int v = 0; v < g->numVertices; v++) {
            if (g->adjMat[u][v]) {
                inDegs[v]--;
                if (inDegs[v] == 0) queue[rear++] = v;
            }
        }  
    }

    if (idx < g->numVertices) return 0; // Cycle spotted
    return 1;
}

#pragma endregion 20.4-5
