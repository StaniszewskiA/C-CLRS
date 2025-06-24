#include "part_6_graph_algorithms/21_minimum_spanning_trees/minimum_spanning_trees.h"

int main(void) {
    MatGraph* mst = mat_graph_create(5, INF);

    mat_graph_add_undirected_weighted_edge(mst, 0, 1, 4);
    mat_graph_add_undirected_weighted_edge(mst, 1, 2, 3);
    mat_graph_add_undirected_weighted_edge(mst, 2, 3, 5);
    mat_graph_add_undirected_weighted_edge(mst, 3, 4, 6);

    update_mst(mst, 0, 4, 2);

    mat_graph_free(mst);

    return 0;
}