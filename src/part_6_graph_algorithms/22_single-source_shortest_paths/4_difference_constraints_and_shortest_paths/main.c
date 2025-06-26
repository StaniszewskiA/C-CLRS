#include "part_6_graph_algorithms/22_single-source_shortest_paths/single-source_shortest_paths.h"

int main(void) {
    int numVertices = 4;
    WeightedNodeListGraph* g = weighted_node_list_graph_create(numVertices);

    weighted_node_list_graph_add_edge(g, 1, 2, 4);  // x1 - x2 <= 4
    weighted_node_list_graph_add_edge(g, 2, 3, 3);  // x2 - x3 <= 3
    weighted_node_list_graph_add_edge(g, 3, 1, -2); // x3 - x1 <= -2
    weighted_node_list_graph_add_edge(g, 1, 4, 5);  // x1 - x4 <= 5
    weighted_node_list_graph_add_edge(g, 4, 3, 1);  // x4 - x3 <= 1

    for (int i = 1; i <= numVertices; i++) weighted_node_list_graph_add_edge(g, 0, i, 0);

    int dist[MAX_GRAPH_VERTICES];
    int pred[MAX_GRAPH_VERTICES];

    int src = 0;
    if (bellman_ford(g, src, dist, pred)) {
        printf("No negative weight cycle detected\n");
        print_solution_20_4(dist, pred, numVertices, src);
    } else {
        printf("Graph contains a negative weight cycle\n");
    }

    weighted_node_list_graph_free(g);
    return 0;
}