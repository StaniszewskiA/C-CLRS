#include <stdio.h>
#include <stdlib.h>

#define TASK 3

#pragma region Graph utils

#define MAX_VERTICES 1000

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
    printf("Freeing graph...\n");
    free(g);
    printf("Graph freed\n");
}

void mat_graph_add_directed_edge(MatGraph* g, int u, int v) {
    g->adjMat[u][v] = 1;
}

void mat_graph_add_undirected_edge(MatGraph* g, int u, int v) {
    g->adjMat[u][v] = 1;
    g->adjMat[v][u] = 1;
}

int has_cycle(MatGraph* g, int v, int visited[], int recursionStack[]) {
    if (!visited[v]) {
        visited[v] = 1;
        recursionStack[v] = 1;
        for (int i = 0; i < g->numVertices; i++) {
            if (g->adjMat[v][i]) {
                if (!visited[i] && has_cycle(g, i, visited, recursionStack)) return 1;
                else if (recursionStack[i]) return 1;
            }
        }
    }
    recursionStack[v] = 0;
    return 0;
}

int is_dag(MatGraph* g) {
    int visited[MAX_VERTICES] = {0};
    int recursionStack[MAX_VERTICES] = {0};

    for (int i = 0; i < g->numVertices; i++) 
        if (has_cycle(g, i, visited, recursionStack)) return 0;
    return 1;
}

#pragma endregion Graph utils

#pragma region Topological sort utils

void topo_sort_helper(
    MatGraph* g, 
    int v, 
    int visited[], 
    int stack[], 
    int *stackIdx
) {
    visited[v] = 1;
    for (int i = 0; i < g->numVertices; i++) {
        if (g->adjMat[v][i] && !visited[i]) topo_sort_helper(g, i, visited, stack, stackIdx);
    }
    stack[(*stackIdx)++] = v;
}

void topo_sort(MatGraph* g, int stack[]) {
    int visited[MAX_VERTICES] = {0};
    int stackIdx = 0;

    for (int i = 0; i < g->numVertices; i++) {
        if (!visited[i]) topo_sort_helper(g, i, visited, stack, &stackIdx);
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

int count_simple_paths(MatGraph* g, int s, int t) {
    int stack[MAX_VERTICES];
    topo_sort(g, stack);
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

int dfs_cycle_check(MatGraph* g, int v, int visited[], int parent) {
    visited[v] = 1;

    for (int u = 0; u < g->numVertices; u++) {
        if (g->adjMat[v][u] && !visited[u]) 
            if (dfs_cycle_check(g, u, visited, v)) return 1;
        else if (u != parent) return 1;
    }

    return 0;
}

int is_acyclic(MatGraph* g) {
    int visited[MAX_VERTICES] = {0};
    for (int v = 0; v < g->numVertices; v++) {
        if (!visited[v]) {
            if (dfs_cycle_check(g, v, visited, -1)) return 0;
        }
    }
    return 1;
}

#pragma endregion 20.4-3

#pragma region 20.4-5

int indeg_topo_sort(MatGraph* g, int result[]) {
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

int main(void) {
    switch (TASK)
    {
        case 1: {
            // 20.4-2
            int numVertices = 5;
            MatGraph* g = mat_graph_create(numVertices);

            mat_graph_add_directed_edge(g, 0, 1);
            mat_graph_add_directed_edge(g, 0, 2);
            mat_graph_add_directed_edge(g, 1, 3);
            mat_graph_add_directed_edge(g, 2, 3);
            mat_graph_add_directed_edge(g, 3, 4);

            if (is_dag(g)) {
                int s = 0, t = 4;
                int res = count_simple_paths(g, s, t);
                printf("Number of simple paths from %d to %d: %d\n", s, t, res);
            } else printf("Passed graph is not a DAG");

            mat_graph_free(g);
            break;
        }

        case 2: {
            // 20.4-2
            int numVertices = 5;
            MatGraph* g = mat_graph_create(numVertices);

            mat_graph_add_undirected_edge(g, 0, 1);
            mat_graph_add_undirected_edge(g, 0, 2);
            mat_graph_add_undirected_edge(g, 1, 3);
            mat_graph_add_undirected_edge(g, 2, 3);
            mat_graph_add_undirected_edge(g, 3, 4);

            if (is_acyclic(g)) printf("The graph is acyclic\n");
            else printf("The graph contains a cycle\n");

            mat_graph_free(g);
            break;
        }

        case 3: {
            // 20.4-5
            int numVertices = 5;
            MatGraph* g = mat_graph_create(numVertices);

            mat_graph_add_directed_edge(g, 0, 1);
            mat_graph_add_directed_edge(g, 0, 2);
            mat_graph_add_directed_edge(g, 1, 3);
            mat_graph_add_directed_edge(g, 2, 3);
            mat_graph_add_directed_edge(g, 3, 4);


            int result[MAX_VERTICES];
            if (!is_dag(g)) printf("Passed graph is not a DAG\n");
            else if (!indeg_topo_sort(g, result)) printf("Graph could not be sorted\n");
            else {
                printf("Topological order: ");
                for (int i = 0; i < numVertices; i++) printf("%d ", result[i]);
                printf("\n");
            }

            mat_graph_free(g);
            break;

            break;
        }
        
        default:
            break;
    }
    return 0;
}