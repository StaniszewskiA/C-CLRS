#include "part_6_graph_algorithms/20_elementary_graph_algorithms/elementary_graph_algorithms.h"

#define TASK 4

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
    // Using mat_graph_dfs
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

#pragma region 20.5

PlanarGraph* planar_graph_create() {
    PlanarGraph* pg = safe_malloc(sizeof(PlanarGraph));
    for (int i = 0; i < MAX_VERTICES; i++) {
        pg->adjSize[i] = 0;
        pg->newestNei[i] = -1;
    }
    pg->stackTop = -1;
    return pg;
}

void planar_graph_insert(PlanarGraph* pg, int v, int* neis, int numNeis) {
    pg->stack[++pg->stackTop] = v;

    for (int i = 0; i < numNeis; i++) {
        int nei = neis[i];
        pg->adjList[v][pg->adjSize[v]++] = nei;
        pg->adjList[nei][pg->adjSize[nei]++] = v;
        pg->newestNei[nei] = v;
    }

    if (numNeis > 0) pg->newestNei[v] = neis[numNeis - 1];
    else pg->newestNei[v] = -1;
}

int planar_graph_newest_nei(PlanarGraph* pg, int v) {
    return pg->newestNei[v];
}

void planar_graph_free(PlanarGraph* pg) {
    free(pg);
}

#pragma endregion 20.5

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

        case 4: {
            // 20.5
            PlanarGraph* g = planar_graph_create();

            int neighbors1[] = {0};
            planar_graph_insert(g, 1, neighbors1, 1);

            int neighbors2[] = {1};
            planar_graph_insert(g, 2, neighbors2, 1);

            printf("Newest neighbor of 1: %d\n", planar_graph_newest_nei(g, 1));
            printf("Newest neighbor of 2: %d\n", planar_graph_newest_nei(g, 2));

            planar_graph_free(g);
            break;
        }
        
        default:
            break;
    }

    return 0;
}