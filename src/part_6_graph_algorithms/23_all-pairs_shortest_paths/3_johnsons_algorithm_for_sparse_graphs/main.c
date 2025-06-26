#include "part_6_graph_algorithms/23_all-pairs_shortest_paths/all-pairs_shortest_paths.h"

#define TASK 1

int main(void) {
    int numVertices = 6;
    int W[6][6] = {
        {0, INF, INF, INF, -1, INF},
        {1, 0, INF, 2, INF, INF},
        {INF, 2, 0, INF, INF, -8},
        {-4, INF, INF, 0, 3, INF},
        {INF, 7, INF, INF, 0, INF},
        {INF, 5, 10, INF, INF, 0}
    };
    WeightedNodeListGraph* g = weighted_node_list_graph_create(numVertices);
    for (int u = 0; u < numVertices; u++) {
        for (int v = 0; v < numVertices; v++) {
            if (W[u][v] != INF && u != v) {
                weighted_node_list_graph_add_edge(g, u, v, W[u][v]);
            }
        }
    }

    int D[MAX_GRAPH_VERTICES][MAX_GRAPH_VERTICES];
    if (!johnson(g, D)) {
        printf("Negative cycle detected. Returning.\n");
        weighted_node_list_graph_free(g);
        return 0;
    }

    printf("Johnson's all-pairs shortest paths:\n");
    for (int u = 0; u < numVertices; u++) {
        for (int v = 0; v < numVertices; v++) {
            if (D[u][v] == INF) printf(" INF");
            else  printf("%4d", D[u][v]);
        }
        printf("\n");
    }

    return 0;
}