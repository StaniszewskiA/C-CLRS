#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TASK 3

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

MatGraph* transpose_graph(MatGraph* g) {
    MatGraph* gt = mat_graph_create(g->numVertices);
    for (int u = 0; u < g->numVertices; u++) {
        for (int v = 0; v < g->numVertices; v++) {
            if (g->adjMat[u][v]) mat_graph_add_directed_edge(gt, v, u);
        }
    }
    return gt;
}


#pragma endregion Graph utils

#pragma region 20.2

void compute_low_values(
    MatGraph* g,
    int u,
    int parent,
    int* visited,
    int* discovery,
    int* low,
    int* time
) {
    // Using DFS
    visited[u] = 1;
    discovery[u] = low[u] = ++(*time);

    for (int v = 0; v < g->numVertices; v++) {
        if (g->adjMat[v][u]) {
            if (!visited[v]) {
                compute_low_values(g, v, u, visited, discovery, low, time);
                low[u] = fmin(low[u], low[v]);
            } else if (v != parent) {
                low[u] = fmin(low[u], discovery[v]);
            }
        }
    }
}

void find_low_values(MatGraph* g) {
    int visited[MAX_VERTICES] = {0};
    int discovery[MAX_VERTICES] = {0};
    int low[MAX_VERTICES] = {0};
    int time = 0;

    for (int i = 0; i < g->numVertices; i++) {
        if (!visited[i]) {
            compute_low_values(g, i, -1, visited, discovery, low, &time);
        }
    }

    printf("Vertex\tLow Value\n");
    for (int i = 0; i < g->numVertices; i++) {
        printf("%d\t%d\n", i, low[i]);
    }
}

void compute_articulation_points(
    MatGraph* g,
    int* visited,
    int* discovery,
    int* low,
    int* articulationPoints
) {
    int time = 0;
    for (int i = 0; i < g->numVertices; i++) {
        if (!visited[i]) {
            compute_low_values(g, i, -1, visited, discovery, low, &time);
        }
    }

    for (int u = 0; u < g->numVertices; u++) {
        int children = 0;
        for (int v = 0; v < g->numVertices; v++) {
            if (g->adjMat[u][v]) {
                if (discovery[v] > discovery[u]) {
                    children++;
                    if (low[v] >= discovery[u] && u != 0) {
                        articulationPoints[u] = 1;
                    }
                }
            }
        }
        // Root
        if (discovery[u] == 0 && children > 1) {
            articulationPoints[u] = 1;
        }
    }
}

void find_articulation_points(MatGraph* g) {
    int visited[MAX_VERTICES] = {0};
    int discovery[MAX_VERTICES] = {0};
    int low[MAX_VERTICES] = {0};
    int articulationPoints[MAX_VERTICES] = {0};
    int time = 0;

    compute_articulation_points(g, visited, discovery, low, articulationPoints);

    printf("Articulation Points:\n");
    for (int i = 0; i < g->numVertices; i++) {
        if (articulationPoints[i]) {
            printf("%d\n", i);
        }
    }
} 

void compute_bridges(
    MatGraph* g,
    int u,
    int parent,
    int* visited,
    int* discovery,
    int* low,
    int* articulationPoints,
    int* degree,
    int* time,
    int bridges[MAX_VERTICES][MAX_VERTICES]
) {
    visited[u] = 1;
    discovery[u] = low[u] = ++(*time);
    for (int v = 0; v < g->numVertices; v++) {
        if (g->adjMat[u][v]) {
            if (!visited[v]) {
                compute_bridges(g, v, u, visited, discovery, 
                    low, articulationPoints, degree, time, bridges);
                low[u] = fmin(low[u], low[v]);
                if (discovery[u] < low[v]) printf("%d - %d\n", u, v); 
            } else if (v != parent) {
                low[u] = fmin(low[u], discovery[v]);
            }
        }
    }
}

void find_bridges(MatGraph* g) {
    int visited[MAX_VERTICES] = {0};
    int discovery[MAX_VERTICES] = {0};
    int low[MAX_VERTICES] = {0};
    int articulationPoints[MAX_VERTICES] = {0};
    int degree[MAX_VERTICES] = {0};
    int time = 0;
    int bridges[MAX_VERTICES][MAX_VERTICES] = {0};
    printf("Detected bridges: \n");
    for (int u = 0; u < g->numVertices; u++) {
        if (!visited[u]) {
            compute_bridges(g, u, -1, visited, discovery, low, 
                articulationPoints, degree, &time, bridges);
        }
    }
}

void label_bcc_edges(
    MatGraph* g, 
    int u, 
    int bccId,
    int* visited,
    int bccLabels[MAX_VERTICES][MAX_VERTICES]
) {
    visited[u] = 1;
    for (int v = 0; v < g->numVertices; v++) {
        if (g->adjMat[u][v] && bccLabels[u][v] == -1) {
            bccLabels[u][v] = bccLabels[v][u] = bccId;
            if (!visited[v]) label_bcc_edges(g, v, bccId, visited, bccLabels);
        }
    }
}

void find_bccs(MatGraph* g) {
    int visited[MAX_VERTICES] = {0};
    int discovery[MAX_VERTICES] = {0};
    int low[MAX_VERTICES] = {0};
    int articulationPoints[MAX_VERTICES] = {0};
    int degree[MAX_VERTICES] = {0};
    int time = 0;

    // Initialize bridges array
    int bridges[MAX_VERTICES][MAX_VERTICES] = {0};

    // Compute bridges
    memset(visited, 0, sizeof(visited));
    for (int u = 0; u < g->numVertices; u++) {
        if (!visited[u]) {
            compute_bridges(g, u, -1, visited, discovery, low, articulationPoints, degree, &time, bridges);
        }
    }

    // Debug: Print bridges
    printf("Bridges:\n");
    for (int u = 0; u < g->numVertices; u++) {
        for (int v = u + 1; v < g->numVertices; v++) {
            if (bridges[u][v]) {
                printf("Bridge between %d and %d\n", u, v);
            }
        }
    }

    // Remove bridge edges
    for (int u = 0; u < g->numVertices; u++) {
        for (int v = u + 1; v < g->numVertices; v++) {
            if (bridges[u][v]) {
                g->adjMat[u][v] = g->adjMat[v][u] = 0; // Remove bridge edge
            }
        }
    }

    // Debug: Print adjacency matrix after bridge removal
    printf("Adjacency Matrix after Bridge Removal:\n");
    for (int u = 0; u < g->numVertices; u++) {
        for (int v = 0; v < g->numVertices; v++) {
            printf("%d ", g->adjMat[u][v]);
        }
        printf("\n");
    }

    // Label edges
    int bccLabels[MAX_VERTICES][MAX_VERTICES];
    memset(bccLabels, -1, sizeof(bccLabels));
    memset(visited, 0, sizeof(visited));

    int bccId = 0;
    for (int u = 0; u < g->numVertices; u++) {
        if (!visited[u]) {
            label_bcc_edges(g, u, bccId++, visited, bccLabels);
        }
    }

    // Print BCCs
    printf("Biconnected Components (BCC IDs):\n");
    for (int u = 0; u < g->numVertices; u++) {
        for (int v = u + 1; v < g->numVertices; v++) {
            if (bccLabels[u][v] != -1) {
                printf("Edge %d-%d: BCC ID %d\n", u, v, bccLabels[u][v]);
            }
        }
    }
}

#pragma endregion 20.2

#pragma region 20.3

void find_euler_tour(MatGraph* g, int source) {
    int edgeColor[MAX_VERTICES][MAX_VERTICES];
    memset(edgeColor, 0, sizeof(edgeColor));
    int currPathStack[MAX_VERTICES * MAX_VERTICES];
    int top = -1;
    int circuit[MAX_VERTICES * MAX_VERTICES];
    int circuitIdx = 0;

    currPathStack[++top] = source;

    while (top >= 0) {
        int v = currPathStack[top];
        int foundWhite = 0;

        for (int w = 0; w < g->numVertices; w++) {
            if (g->adjMat[v][w] && edgeColor[v][w] == 0) {
                edgeColor[v][w] = edgeColor[w][v] = 1;
                currPathStack[++top] = w;
                foundWhite = 1;
                break;
            }
        }

        if (!foundWhite) {
            circuit[circuitIdx++] = v;
            top--;
        }
    }

    printf("Euler Circuit:\n");
    for (int i = circuitIdx - 1; i >= 0; i--)
        printf("%d ", circuit[i]);
    printf("\n");
}

#pragma endregion 20.3

#pragma region 20.4

void dfs(MatGraph* g, int u, int visited[], int stack[], int* stackIdx) {
    visited[u] = 1;
    for (int v = 0; v < g->numVertices; v++) {
        if (g->adjMat[u][v] && !visited[v]) {
            dfs(g, v, visited, stack, stackIdx);
        }
    }
    stack[(*stackIdx)++] = u;
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

    printf("SCCs:\n");
    for (int v = 0; v < g->numVertices; v++) {
        printf("Vertex %d -> Component %d\n", v, component[v]);
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

    printf("Component Graph Adjacency Matrix:\n");
    for (int u = 0; u < numComponents; u++) {
        for (int v = 0; v < numComponents; v++) {
            printf("%d ", cg->adjMat[u][v]);
        }
        printf("\n");
    }

    return cg;
}

int reachability(
    MatGraph* gSCC, 
    int u, 
    int* minValues, 
    int* visited, 
    int* sccMinLabels
) {
    if (visited[u]) return minValues[u];
    visited[u] = 1;
    int minVal = sccMinLabels[u];
    
    for (int v = 0; v < gSCC->numVertices; v++) {
        if (gSCC->adjMat[u][v]) {
            int reachableMin = reachability(gSCC, v, minValues, visited, sccMinLabels);
            if (reachableMin < minVal) minVal = reachableMin;
        }
    }

    minValues[u] = minVal; 
    printf("Reachability: Component %d -> Min Value %d\n", u, minVal);

    return minVal;
}

void compute_min_labels(MatGraph* g, int* labels) {
    int components[MAX_VERTICES];
    int numComponents = kosaraju(g, components);

    // Label SCCs
    int sccMinLabels[MAX_VERTICES];
    for (int i = 0; i < numComponents; i++) sccMinLabels[i] = INT_MAX;
    for (int v = 0; v < g->numVertices; v++)
        sccMinLabels[components[v]] = fmin(sccMinLabels[components[v]], labels[v]);

    // Component graph
    MatGraph* gSCC = build_component_graph(g, components, numComponents);

    // Reachability on the component graph
    int minValues[MAX_VERTICES];
    int visited[MAX_VERTICES] = {0};
    memset(minValues, -1, sizeof(minValues));
    for (int u = 0; u < numComponents; u++) {
        if (!visited[u]) reachability(gSCC, u, minValues, visited, sccMinLabels);
    }

    // Map to the original graph
    for (int u = 0; u < g->numVertices; u++)
        printf("min(%d) = %d\n", u, minValues[components[u]]);

    mat_graph_free(gSCC);
}

#pragma endregion 20.4

int main(void) {
    switch (TASK)
    {
        case 1: {
            // 20.2
            int numVertices = 6;
            MatGraph* g = mat_graph_create(numVertices);

            mat_graph_add_undirected_edge(g, 0, 1);

            mat_graph_add_undirected_edge(g, 1, 2);
            mat_graph_add_undirected_edge(g, 2, 0);
            mat_graph_add_undirected_edge(g, 3, 1);
            mat_graph_add_undirected_edge(g, 3, 4);
            mat_graph_add_undirected_edge(g, 4, 5);

            find_low_values(g);
            find_articulation_points(g);
            find_bridges(g);
            find_bccs(g);

            mat_graph_free(g);
            break;
        }

        case 2: {
            // 20.3
            int numVertices = 6;
            MatGraph* g = mat_graph_create(numVertices);

            mat_graph_add_undirected_edge(g, 0, 1);

            mat_graph_add_undirected_edge(g, 1, 2);
            mat_graph_add_undirected_edge(g, 2, 0);
            mat_graph_add_undirected_edge(g, 3, 1);
            mat_graph_add_undirected_edge(g, 3, 4);
            mat_graph_add_undirected_edge(g, 4, 5);

            find_euler_tour(g, 5);
            mat_graph_free(g);
            break;
        }

        case 3: {
            // 20.4
            int numVertices = 8;
            MatGraph* g = mat_graph_create(numVertices);

            mat_graph_add_directed_edge(g, 0, 1);
            mat_graph_add_directed_edge(g, 1, 2);
            mat_graph_add_directed_edge(g, 2, 0);
            mat_graph_add_directed_edge(g, 3, 4);
            mat_graph_add_directed_edge(g, 4, 5);
            mat_graph_add_directed_edge(g, 5, 3);
            mat_graph_add_directed_edge(g, 2, 3);
            mat_graph_add_directed_edge(g, 5, 6);
            mat_graph_add_directed_edge(g, 6, 7);

            int labels[MAX_VERTICES] = {8, 7, 6, 5, 4, 3, 2, 1};

            compute_min_labels(g, labels);
            mat_graph_free(g);

            break;
        }
        
        default:
            break;
    }

    return 0;
}