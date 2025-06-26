#include "part_6_graph_algorithms/22_single-source_shortest_paths/single-source_shortest_paths.h"

void print_solution_20_4(int dist[], int pred[], int numVertices, int src) {
    printf("Shortest paths from source %d:\n", src);
    for (int i = 0; i < numVertices; i++) {
        if (i != src) {
            printf("to vertex %d: ", i);
            if (dist[i] == INF) printf("No path exists\n");
            else {
                printf("Distance = %d, Path: ", dist[i]);
                print_path(pred, i);
                printf("\n");
            }
        }
    }
}
