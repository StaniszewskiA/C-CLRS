#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TASK 4

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
    // printf("Freeing graph...\n");
    free(g);
    // printf("Graph freed\n");
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

void dfs(MatGraph* g, int v, int visited[], int stack[], int* stackIdx) {
    visited[v] = 1;
    for (int u = 0; u < g->numVertices; u++) {
        if (g->adjMat[v][u] && !visited[u]) 
            dfs(g, u, visited, stack, stackIdx);
    }
    stack[(*stackIdx)++] = v;
}

MatGraph* transpose_graph(MatGraph* g) {
    /*
        We need both G and GT, hence we return 
        the transposed graph.
    */
    MatGraph* gt = mat_graph_create(g->numVertices);
    for (int u = 0; u < g->numVertices; u++) {
        for (int v = 0; v < g->numVertices; v++) {
            if (g->adjMat[u][v]) mat_graph_add_directed_edge(gt, v, u);
        }
    }
    return gt;
}

void assign_scc(
    MatGraph* gt, 
    int v, 
    int visited[], 
    int component[], 
    int compId
) {
    visited[v] = 1;
    component[v] = compId;
    for (int u = 0; u < gt->numVertices; u++) {
        if (gt->adjMat[v][u] && !visited[u])
            assign_scc(gt, u, visited, component, compId);
    } 
}

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

#pragma endregion Graph utils

#pragma region 20.5-5

int kosaraju(MatGraph* g, int component[]) {
    int stack[MAX_VERTICES];
    int stackIdx = 0;
    int visited[MAX_VERTICES] = {0};

    // DFS
    for (int v = 0; v < g->numVertices; v++) {
        if (!visited[v]) dfs(g, v, visited, stack, &stackIdx);
    }

    // Transposition
    MatGraph* gt = transpose_graph(g);

    // Assignment
    memset(visited, 0, sizeof(visited));
    int compId = 0;
    for (int i = stackIdx - 1; i >= 0; i--) {
        int v = stack[i];
        if (!visited[v]) {
            assign_scc(gt, v, visited, component, compId);
            compId++;
        }
    }

    mat_graph_free(gt);
    return compId;
}

MatGraph* build_component_graph(
    MatGraph* g, 
    int component[], 
    int numComponents
) {
    MatGraph* cg = mat_graph_create(numComponents);

    for (int u = 0; u < g->numVertices; u++) {
        for (int v = 0; v < g->numVertices; v++) {
            if (g->adjMat[u][v] && component[u] != component[v])
                mat_graph_add_directed_edge(cg, component[u], component[v]);
        }
    }

    return cg;
}

#pragma endregion 20.5-5

#pragma region 20.5-6

MatGraph* create_minimal_scc_graph(
    MatGraph* g, 
    int component[], 
    int numComponents
) {
    MatGraph* gPrime = mat_graph_create(g->numVertices);

    // Minimal edges within each SCC
    for (int compId = 0; compId < numComponents; compId++) {
        int firstVertex = -1;
        int prevVertex = -1;

        for (int v = 0; v < g->numVertices; v++) {
            if (component[v] == compId) {
                if (firstVertex == -1) firstVertex = v;
                if (prevVertex != -1) 
                    mat_graph_add_directed_edge(gPrime, prevVertex, v);
                prevVertex = v;
            }
        }

        // Close the cycle
        if (firstVertex != -1 && prevVertex != -1)
            mat_graph_add_directed_edge(gPrime, prevVertex, firstVertex);
    }

    // Edges between SCCs
    for (int u = 0; u < g->numVertices; u++) {
        for (int v = 0; v < g->numVertices; v++) {
            if (g->adjMat[u][v] && component[u] != component[v])
                mat_graph_add_directed_edge(gPrime, u, v);
        }
    }

    return gPrime;
}

#pragma endregion 20.5-6

#pragma region 20.5-7

int is_semiconnected(MatGraph* g) {
    int component[MAX_VERTICES];
    int numComponents = kosaraju(g, component);

    // Component graph G'
    MatGraph* gPrime = build_component_graph(g, component, numComponents);

    // Topo sort on G'
    int sorted[MAX_VERTICES];
    topo_sort(gPrime, sorted);

    /*
        Is there an edge between all consecutive vertices
        in the topological order?
    */
    for (int i = 0; i < numComponents - 1; i++) {
        int u = sorted[i];
        int v = sorted[i + 1];
        if (!gPrime->adjMat[u][v]) {
            mat_graph_free(gPrime);
            return 0;
        }
    }

    mat_graph_free(gPrime);
    return 1;
}

#pragma endregion 20.5-7

#pragma region 20.5-8

void find_max_delta_l(MatGraph* g, double labels[]) {
    int component[MAX_VERTICES];
    int numComponents = kosaraju(g, component);

    MatGraph* gPrime = build_component_graph(g, component, numComponents);

    int sorted[MAX_VERTICES];
    topo_sort(gPrime, sorted);

    int firstSCC = sorted[0];
    int lastSCC = sorted[numComponents - 1];

    double minLabel = __DBL_MAX__;
    int s = -1;
    for (int v = 0; v < g->numVertices; v++) {
        if (component[v] == firstSCC && labels[v] < minLabel) {
            minLabel = labels[v];
            s = v;
        }
    }

    double maxLabel = __DBL_MIN__;
    int t = -1;
    for (int v = 0; v < g->numVertices; v++) {
        if (component[v] == lastSCC && labels[v] > maxLabel) {
            maxLabel = labels[v];
            t = v;
        }
    }

    printf("Vertex s: %d, Vertex t: %d\n", s, t);
    printf("Max delta l(s, t): %f\n", maxLabel - minLabel);

    mat_graph_free(gPrime);
}

#pragma endregion 20.5-8

int main(void) {
    switch (TASK)
    {
        case 1: {
            // 20.5-5
            int numVertices = 8;
            MatGraph* g = mat_graph_create(numVertices);

            mat_graph_add_directed_edge(g, 0, 1);
            mat_graph_add_directed_edge(g, 1, 2);
            mat_graph_add_directed_edge(g, 2, 0);
            mat_graph_add_directed_edge(g, 3, 4);
            mat_graph_add_directed_edge(g, 4, 5);
            mat_graph_add_directed_edge(g, 5, 3);
            mat_graph_add_directed_edge(g, 6, 7);
            mat_graph_add_directed_edge(g, 7, 6);
            mat_graph_add_directed_edge(g, 2, 3);
            mat_graph_add_directed_edge(g, 5, 6);

            int component[MAX_VERTICES];
            int numComponents = kosaraju(g, component);

            printf("Number of strongly connected components: %d\n", numComponents);
            for (int v = 0; v < numVertices; v++) {
                printf("Vertex %d is in component %d\n", v, component[v]);
            }

            MatGraph* cg = build_component_graph(g, component, numComponents);
            printf("Component graph adjacency matrix:\n");
            for (int u = 0; u < numComponents; u++) {
                for (int v = 0; v < numComponents; v++) {
                    printf("%d ", cg->adjMat[u][v]);
                }
                printf("\n");
            }

            mat_graph_free(g);
            mat_graph_free(cg);
            break;
        }

        case 2: {
            // 20.5-6
            int numVertices = 8;
            MatGraph* g = mat_graph_create(numVertices);

            mat_graph_add_directed_edge(g, 0, 1);
            mat_graph_add_directed_edge(g, 1, 2);
            mat_graph_add_directed_edge(g, 2, 0);
            mat_graph_add_directed_edge(g, 3, 4);
            mat_graph_add_directed_edge(g, 4, 5);
            mat_graph_add_directed_edge(g, 5, 3);
            mat_graph_add_directed_edge(g, 6, 7);
            mat_graph_add_directed_edge(g, 7, 6);
            mat_graph_add_directed_edge(g, 2, 3);
            mat_graph_add_directed_edge(g, 5, 6);

            int component[MAX_VERTICES];
            int numComponents = kosaraju(g, component);

            MatGraph* gPrime = create_minimal_scc_graph(g, component, numComponents);

            printf("Minimal SCC graph adjacency matrix:\n");
            for (int u = 0; u < g->numVertices; u++) {
                for (int v = 0; v < g->numVertices; v++) {
                    printf("%d ", gPrime->adjMat[u][v]);
                }
                printf("\n");
            }

            mat_graph_free(g);
            mat_graph_free(gPrime);
            break;
        }

        case 3: {
            // 20.5-7
            int numVertices = 8;
            MatGraph* g = mat_graph_create(numVertices);

            mat_graph_add_directed_edge(g, 0, 1);
            mat_graph_add_directed_edge(g, 1, 2);
            mat_graph_add_directed_edge(g, 2, 0);
            mat_graph_add_directed_edge(g, 3, 4);
            mat_graph_add_directed_edge(g, 4, 5);
            mat_graph_add_directed_edge(g, 5, 3);
            mat_graph_add_directed_edge(g, 6, 7);
            mat_graph_add_directed_edge(g, 7, 6);
            mat_graph_add_directed_edge(g, 2, 3);
            mat_graph_add_directed_edge(g, 5, 6);

            printf("The graph is %ssemiconnected.\n", 
                is_semiconnected(g) ? "" : "not ");

            mat_graph_free(g);
            break;
        }

        case 4: {
            // 20.5-8
            int numVertices = 8;
            MatGraph* g = mat_graph_create(numVertices);

            mat_graph_add_directed_edge(g, 0, 1);
            mat_graph_add_directed_edge(g, 1, 2);
            mat_graph_add_directed_edge(g, 2, 0);
            mat_graph_add_directed_edge(g, 3, 4);
            mat_graph_add_directed_edge(g, 4, 5);
            mat_graph_add_directed_edge(g, 5, 3);
            mat_graph_add_directed_edge(g, 6, 7);
            mat_graph_add_directed_edge(g, 7, 6);
            mat_graph_add_directed_edge(g, 2, 3);
            mat_graph_add_directed_edge(g, 5, 6);

            double labels[] = {1.5, 2.3, 0.7, 4.8, 3.1, 5.6, 2.0, 6.4};

            find_max_delta_l(g, labels);

            mat_graph_free(g);
            break;
        }
        
        default:
            break;
    }

    return 0;
}