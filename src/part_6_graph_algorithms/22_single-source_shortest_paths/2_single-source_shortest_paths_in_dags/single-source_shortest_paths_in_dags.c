#include "part_6_graph_algorithms/22_single-source_shortest_paths/single-source_shortest_paths.h"

#pragma region Topo sort utils

void weighted_list_graph_topo_sort_helper(
    WeightedNodeListGraph* g, 
    int v, 
    int visited[], 
    int* stack, 
    int* stackIdx
) {
    visited[v] = 1;
    WeightedNode* tmp = g->adjList[v];
    while (tmp) {
        if (!visited[tmp->vertex]) {
            weighted_list_graph_topo_sort_helper(g, tmp->vertex, visited, stack, stackIdx);
        }
        tmp = tmp->next;
    }
    stack[(*stackIdx)++] = v;
}

void weighted_list_graph_topo_sort(WeightedNodeListGraph* g, int* stack) {
    int visited[MAX_GRAPH_VERTICES] = {0};
    int stackIdx = 0;

    for (int i = 0; i < g->numVertices; i++) {
        if (!visited[i]) weighted_list_graph_topo_sort_helper(g, i, visited, stack, &stackIdx);
    }

    for (int i = 0; i < stackIdx / 2; i++) {
        int temp = stack[i];
        stack[i] = stack[stackIdx - i - 1];
        stack[stackIdx - i - 1] = temp;
    }
}

#pragma endregion Topo sort utils

void dag_shortest_path(
    WeightedNodeListGraph* g, 
    int src, 
    int dist[], 
    int pred[]
) {
    int numVertices = g->numVertices;
    int stack[MAX_GRAPH_VERTICES];
    weighted_list_graph_topo_sort(g, stack);
    init_single_source(dist, pred, numVertices, src);

    for (int i = 0; i < numVertices; i++) {
        int u = stack[i];
        WeightedNode* tmp = g->adjList[u];
        while (tmp) {
            relax_edge(u, tmp->vertex, tmp->weight, dist, pred);
            tmp = tmp->next;
        }
    }
}

void print_solution_22_2(int dist[], int pred[], int numVertices, int src) {
    printf("Shortest paths from source %d:\n", src);
    for (int i = 0; i < numVertices; i++) {
        printf("To vertex %d: ", i);
        if (dist[i] == INT_MAX) printf("No path exists\n");
        else {
            printf("Distance = %d", dist[i]);
            if (pred[i] != -1) printf(", Predecessor = %d", pred[i]);
            printf("\n");
        }
    }
}

#pragma region 22.2-3

void split_weighted_vertices(
    WeightedNodeListGraph* g, 
    WeightedNodeListGraph* transformed, 
    int vertexWeights[]
) {
    int offset = g->numVertices;
    for (int v = 0; v < g->numVertices; v++) {
        printf("Creating a new vertex with weight %d\n", vertexWeights[v]);
        weighted_node_list_graph_add_edge(transformed, v, v + offset, vertexWeights[v]);
        WeightedNode* tmp = g->adjList[v];
        while (tmp) {
            weighted_node_list_graph_add_edge(transformed, v + offset, tmp->vertex, tmp->weight);
            tmp = tmp->next;
        }
        
    }
}

#pragma endregion 22.2-3

#pragma region 22.2-4

int weighted_node_list_graph_count_paths(WeightedNodeListGraph* g) {
    /*
        Time complexity: O(V + E)
    */
    int stack[MAX_GRAPH_VERTICES];
    int paths[MAX_GRAPH_VERTICES] = {0};

    weighted_list_graph_topo_sort(g, stack);

    for (int i = 0; i < g->numVertices; i++) {
        int u = stack[i];
        WeightedNode* tmp = g->adjList[u];
        while (tmp) {
            int v = tmp->vertex;
            paths[v] += paths[u] + 1;
            tmp = tmp->next;
        }
    }
    int res = 0;
    for (int i = 0; i < g->numVertices; i++) res += paths[i];
    return res;
}

#pragma endregion 22.2-4
