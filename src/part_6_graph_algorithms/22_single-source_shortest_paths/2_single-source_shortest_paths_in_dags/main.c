#include "part_6_graph_algorithms/22_single-source_shortest_paths/single-source_shortest_paths.h"

#define TASK 3

int main(void) {
    switch (TASK)
    {
        case 1: {
            // DAG shorted paths
            int numVertices = 6;
            WeightedNodeListGraph* g = weighted_node_list_graph_create(numVertices);

            weighted_node_list_graph_add_edge(g, 0, 1, 5);
            weighted_node_list_graph_add_edge(g, 0, 2, 3);
            weighted_node_list_graph_add_edge(g, 1, 3, 6);
            weighted_node_list_graph_add_edge(g, 1, 2, 2);
            weighted_node_list_graph_add_edge(g, 2, 4, 4);
            weighted_node_list_graph_add_edge(g, 2, 5, 2);
            weighted_node_list_graph_add_edge(g, 2, 3, 7);
            weighted_node_list_graph_add_edge(g, 3, 4, -1);
            weighted_node_list_graph_add_edge(g, 4, 5, -2);

            int dist[MAX_GRAPH_VERTICES];
            int pred[MAX_GRAPH_VERTICES];
            int src = 1;

            dag_shortest_path(g, src, dist, pred);
            print_solution_22_2(dist, pred, numVertices, src);

            weighted_node_list_graph_free(g);
            break;
        }

        case 2: {
            // 22.2-3
            int numVertices = 6;
            WeightedNodeListGraph* g = weighted_node_list_graph_create(numVertices);
            int vertexWeights[] = {2, 3, 6, 1, 4, 5};

            weighted_node_list_graph_add_edge(g, 0, 1, 0);
            weighted_node_list_graph_add_edge(g, 0, 2, 0);
            weighted_node_list_graph_add_edge(g, 1, 3, 0);
            weighted_node_list_graph_add_edge(g, 1, 2, 0);
            weighted_node_list_graph_add_edge(g, 2, 4, 0);
            weighted_node_list_graph_add_edge(g, 2, 5, 0);
            weighted_node_list_graph_add_edge(g, 3, 4, 0);
            weighted_node_list_graph_add_edge(g, 4, 5, 0);

            WeightedNodeListGraph* gPrime = weighted_node_list_graph_create(2 * numVertices);
            split_weighted_vertices(g, gPrime, vertexWeights);

            int dist[MAX_GRAPH_VERTICES];
            int pred[MAX_GRAPH_VERTICES];
            int src = 1;

            dag_shortest_path(g, src, dist, pred);
            print_solution_22_2(dist, pred, numVertices, src);

            weighted_node_list_graph_free(g);
            break;
        }

        case 3: {
            // 22.2-4
            int numVertices = 6;
            WeightedNodeListGraph* g = weighted_node_list_graph_create(numVertices);

            weighted_node_list_graph_add_edge(g, 0, 1, 0);
            weighted_node_list_graph_add_edge(g, 0, 2, 0);
            weighted_node_list_graph_add_edge(g, 1, 3, 0);
            weighted_node_list_graph_add_edge(g, 1, 2, 0);
            weighted_node_list_graph_add_edge(g, 2, 4, 0);
            weighted_node_list_graph_add_edge(g, 2, 5, 0);
            weighted_node_list_graph_add_edge(g, 3, 4, 0);
            weighted_node_list_graph_add_edge(g, 4, 5, 0);

            int totalPaths = weighted_node_list_graph_count_paths(g);
            printf("Total number of paths in the DAG: %d\n", totalPaths);

            weighted_node_list_graph_free(g);
            break;
        }
        
        default:
            break;
    }
}