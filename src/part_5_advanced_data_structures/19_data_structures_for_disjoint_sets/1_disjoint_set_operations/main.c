#include "part_5_advanced_data_structures/19_data_structures_for_disjoint_sets/data_structures_for_disjoint_sets.h"

int main(void) {
    Graph* g = malloc(sizeof(Graph));
    g->numVertices = 6;

    // Init adj mat
    for (int i = 0; i < g->numVertices; i++)
        for (int j = 0; j < g->numVertices; j++)
            g->edges[i][j] = 0;

    add_edge(g, 0, 1);
    add_edge(g, 1, 2);
    add_edge(g, 3, 4);

    connected_components(g);

    printf("\nAre 0 and 2 in the same component? %s\n", is_same_component(0, 2) ? "Yes" : "No");
    printf("Are 0 and 5 in the same component? %s\n", is_same_component(0, 5) ? "Yes" : "No");

    free(g);
    return 0;
}