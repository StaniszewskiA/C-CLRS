#include "part_6_graph_algorithms/22_single-source_shortest_paths/single-source_shortest_paths.h"

#define TASK 6

int main(void) {
    switch (TASK)
    {
        case 1: {
            // Basic Bellman-Ford
            int numVertices = 5;
            WeightedNodeListGraph* g = weighted_node_list_graph_create(numVertices);

            weighted_node_list_graph_add_edge(g, 0, 1, 6);
            weighted_node_list_graph_add_edge(g, 0, 3, 7);
            weighted_node_list_graph_add_edge(g, 1, 2, 5);
            weighted_node_list_graph_add_edge(g, 1, 3, 8);
            weighted_node_list_graph_add_edge(g, 1, 4, -4);
            weighted_node_list_graph_add_edge(g, 2, 1, -2);
            weighted_node_list_graph_add_edge(g, 3, 2, -3);
            weighted_node_list_graph_add_edge(g, 3, 4, 9);
            weighted_node_list_graph_add_edge(g, 4, 0, 2);
            weighted_node_list_graph_add_edge(g, 4, 2, 7);

            int dist[MAX_GRAPH_VERTICES];
            int pred[MAX_GRAPH_VERTICES];

            int src = 4;
            if (bellman_ford(g, src, dist, pred)) {
                printf("No negative weight cycle detected\n");
                bellman_ford_print_solution(dist, pred, numVertices, src);
            } else printf("Graph contains a negative weight cycle\n");
            
            weighted_node_list_graph_free(g);
            break;
        }

        case 2: {
            // 22.1-3
            int numVertices = 5;
            WeightedNodeListGraph* g = weighted_node_list_graph_create(numVertices);

            weighted_node_list_graph_add_edge(g, 0, 1, 6);
            weighted_node_list_graph_add_edge(g, 0, 3, 7);
            weighted_node_list_graph_add_edge(g, 1, 2, 5);
            weighted_node_list_graph_add_edge(g, 1, 3, 8);
            weighted_node_list_graph_add_edge(g, 1, 4, -4);
            weighted_node_list_graph_add_edge(g, 2, 1, -2);
            weighted_node_list_graph_add_edge(g, 3, 2, -3);
            weighted_node_list_graph_add_edge(g, 3, 4, 9);
            weighted_node_list_graph_add_edge(g, 4, 0, 2);
            weighted_node_list_graph_add_edge(g, 4, 2, 7);

            int dist[MAX_GRAPH_VERTICES];
            int pred[MAX_GRAPH_VERTICES];

            int src = 4;
            if (early_stopped_bellman_ford(g, src, dist, pred)) {
                printf("No negative weight cycle detected\n");
                bellman_ford_print_solution(dist, pred, numVertices, src);
            } else printf("Graph contains a negative weight cycle\n");
            
            
            weighted_node_list_graph_free(g);
            break;
        }

        case 3: {
            // 22.1-4
            int numVertices = 6;
            WeightedNodeListGraph* g = weighted_node_list_graph_create(numVertices);
            
            weighted_node_list_graph_add_edge(g, 0, 1, 6);
            weighted_node_list_graph_add_edge(g, 0, 3, 7);
            weighted_node_list_graph_add_edge(g, 1, 2, 5);
            weighted_node_list_graph_add_edge(g, 1, 3, 8);
            weighted_node_list_graph_add_edge(g, 1, 4, -4);
            weighted_node_list_graph_add_edge(g, 2, 1, -2);
            weighted_node_list_graph_add_edge(g, 3, 2, -3);
            weighted_node_list_graph_add_edge(g, 3, 4, 9);
            weighted_node_list_graph_add_edge(g, 4, 0, 2);
            weighted_node_list_graph_add_edge(g, 4, 2, 7);

            int dist[MAX_GRAPH_VERTICES];
            int pred[MAX_GRAPH_VERTICES];

            int src = 4;
            if (bellman_ford_negative_mark(g, src, dist, pred)) 
                printf("No negative weight cycle detected\n");
            else printf("Graph contains negative weight cycle(s)\n");
            
            bellman_ford_print_modified_solution(dist, numVertices, src);
            
            weighted_node_list_graph_free(g);
            break;
        }

        case 4: {
            // 22.1-5
            int numVertices = 6;
            WeightedNodeListGraph* g = weighted_node_list_graph_create(numVertices);
            
            weighted_node_list_graph_add_edge(g, 0, 1, 6);
            weighted_node_list_graph_add_edge(g, 0, 3, 7);
            weighted_node_list_graph_add_edge(g, 1, 2, 5);
            weighted_node_list_graph_add_edge(g, 1, 3, 8);
            weighted_node_list_graph_add_edge(g, 1, 4, -4);
            weighted_node_list_graph_add_edge(g, 2, 1, -2);
            weighted_node_list_graph_add_edge(g, 3, 2, -3);
            weighted_node_list_graph_add_edge(g, 3, 4, 9);
            weighted_node_list_graph_add_edge(g, 4, 0, 2);
            weighted_node_list_graph_add_edge(g, 4, 2, 7);

            int dist[MAX_GRAPH_VERTICES];
            int pred[MAX_GRAPH_VERTICES];

            int src = 4;
            if (bellman_ford_optimized(g, src, dist, pred)) 
                printf("No negative weight cycle detected\n");
            else printf("Graph contains negative weight cycle(s)\n");
            
            bellman_ford_print_solution(dist, pred, numVertices, src);
            
            weighted_node_list_graph_free(g);
            break;
        }

        case 5: {
            // 22.1-6
            int numVertices = 5;
            WeightedNodeListGraph* g = weighted_node_list_graph_create(numVertices);

            weighted_node_list_graph_add_edge(g, 0, 1, 6);
            weighted_node_list_graph_add_edge(g, 0, 3, 7);
            weighted_node_list_graph_add_edge(g, 1, 2, 5);
            weighted_node_list_graph_add_edge(g, 1, 3, 8);
            weighted_node_list_graph_add_edge(g, 1, 4, -4);
            weighted_node_list_graph_add_edge(g, 2, 1, -2);
            weighted_node_list_graph_add_edge(g, 3, 2, -3);
            weighted_node_list_graph_add_edge(g, 3, 4, 9);
            weighted_node_list_graph_add_edge(g, 4, 0, 2);
            weighted_node_list_graph_add_edge(g, 4, 2, 7);

            int dist[MAX_GRAPH_VERTICES];
            int pred[MAX_GRAPH_VERTICES];

            if (modified_relax_bellman_ford(g, dist, pred)) {
                printf("No negative weight cycle detected\n");
                bellman_ford_print_modified_solution_prim(dist, pred, numVertices);
            } else printf("Graph contains a negative weight cycle\n");
            
            weighted_node_list_graph_free(g);
            break;
        }

        case 6: {
            // 22.1-7
            int numVertices = 6;
            WeightedNodeListGraph* g = weighted_node_list_graph_create(numVertices);
            
            weighted_node_list_graph_add_edge(g, 0, 1, 6);
            weighted_node_list_graph_add_edge(g, 0, 3, 7);
            weighted_node_list_graph_add_edge(g, 1, 2, 5);
            weighted_node_list_graph_add_edge(g, 1, 3, 8);
            weighted_node_list_graph_add_edge(g, 1, 4, -4);
            weighted_node_list_graph_add_edge(g, 2, 1, -2);
            weighted_node_list_graph_add_edge(g, 3, 2, -3);
            weighted_node_list_graph_add_edge(g, 3, 4, 9);
            weighted_node_list_graph_add_edge(g, 4, 0, -5);
            weighted_node_list_graph_add_edge(g, 4, 2, 7);

            print_negative_cycle(g);
            
            weighted_node_list_graph_free(g);
            break;
        }
        
        default:
            break;
    }
}