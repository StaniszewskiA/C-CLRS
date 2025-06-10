#include "part_6_graph_algorithms/20_elementary_graph_algorithms/elementary_graph_algorithms.h"

#pragma region 20.5-5

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

int mat_graph_is_semiconnected(MatGraph* g) {
    int component[MAX_VERTICES];
    int numComponents = kosaraju(g, component);

    // Component graph G'
    MatGraph* gPrime = build_component_graph(g, component, numComponents);

    // Topo sort on G'
    int sorted[MAX_VERTICES];
    mat_graph_topo_sort(gPrime, sorted);

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
    mat_graph_topo_sort(gPrime, sorted);

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
