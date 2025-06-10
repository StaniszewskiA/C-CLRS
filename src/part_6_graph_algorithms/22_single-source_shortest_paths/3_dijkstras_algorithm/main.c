#include "part_6_graph_algorithms/22_single-source_shortest_paths/single-source_shortest_paths.h"

#define TASK 6

int main(void) {
    switch (TASK)
    {
        case 1: {
            // Basic Dijkstra's
            int numVertices = 6;
            MatGraph* g = mat_graph_create(numVertices);

            mat_graph_add_directed_weighted_edge(g, 0, 1, 4);
            mat_graph_add_directed_weighted_edge(g, 0, 2, 1);
            mat_graph_add_directed_weighted_edge(g, 2, 1, 2);
            mat_graph_add_directed_weighted_edge(g, 1, 3, 1);
            mat_graph_add_directed_weighted_edge(g, 2, 3, 5);
            mat_graph_add_directed_weighted_edge(g, 3, 4, 3);
            mat_graph_add_directed_weighted_edge(g, 4, 5, 2);

            int dist[MAX_GRAPH_VERTICES];
            int pred[MAX_GRAPH_VERTICES];
            int src = 0;

            dijkstra(g, src, dist, pred);
            print_dijkstra_solution(dist, pred, numVertices, src);

            mat_graph_free(g);
            break;
        }

        case 2: {
            // 22.3-4 and 22.3-5
            int numVertices = 6;
            MatGraph* g = mat_graph_create(numVertices);

            mat_graph_add_directed_weighted_edge(g, 0, 1, 4);
            mat_graph_add_directed_weighted_edge(g, 0, 2, 1);
            mat_graph_add_directed_weighted_edge(g, 2, 1, 2);
            mat_graph_add_directed_weighted_edge(g, 1, 3, 1);
            mat_graph_add_directed_weighted_edge(g, 2, 3, 5);
            mat_graph_add_directed_weighted_edge(g, 3, 4, 3);
            mat_graph_add_directed_weighted_edge(g, 4, 5, 2);

            int dist[MAX_GRAPH_VERTICES];
            int pred[MAX_GRAPH_VERTICES];
            int src = 0;

            pq_dijkstra(g, src, dist, pred);
            print_dijkstra_solution(dist, pred, numVertices, src);

            if (verify_dijkstra_output(g, dist, pred, src)) 
                printf("The output is valid");
            else printf("The output is invalid");

            mat_graph_free(g);
            break;
        }

        case 3: {
            // 22.3-7
            int numVertices = 6;
            MatGraph* g = mat_graph_create(numVertices);

            mat_graph_add_directed_reliability_edge(g, 0, 1, 0.4);
            mat_graph_add_directed_reliability_edge(g, 0, 2, 0.1);
            mat_graph_add_directed_reliability_edge(g, 2, 1, 0.2);
            mat_graph_add_directed_reliability_edge(g, 1, 3, 0.1);
            mat_graph_add_directed_reliability_edge(g, 2, 3, 0.5);
            mat_graph_add_directed_reliability_edge(g, 3, 4, 0.3);
            mat_graph_add_directed_reliability_edge(g, 4, 5, 0.2);

            int dist[MAX_GRAPH_VERTICES];
            int pred[MAX_GRAPH_VERTICES];
            int src = 0;

            pq_dijkstra(g, src, dist, pred);
            print_dijkstra_solution(dist, pred, numVertices, src);

            if (verify_dijkstra_output(g, dist, pred, src)) 
                printf("The output is valid");
            else printf("The output is invalid");

            mat_graph_free(g);
            break;
        }

        case 4: {
            // 22.3-9
            int numVertices = 6;
            MatGraph* g = mat_graph_create(numVertices);

            mat_graph_add_directed_reliability_edge(g, 0, 1, 0.4);
            mat_graph_add_directed_reliability_edge(g, 0, 2, 0.1);
            mat_graph_add_directed_reliability_edge(g, 2, 1, 0.2);
            mat_graph_add_directed_reliability_edge(g, 1, 3, 0.1);
            mat_graph_add_directed_reliability_edge(g, 2, 3, 0.5);
            mat_graph_add_directed_reliability_edge(g, 3, 4, 0.3);
            mat_graph_add_directed_reliability_edge(g, 4, 5, 0.2);

            int dist[MAX_GRAPH_VERTICES];
            int pred[MAX_GRAPH_VERTICES];
            int src = 0;

            dial(g, src, dist, pred);
            print_dijkstra_solution(dist, pred, numVertices, src);

            if (verify_dijkstra_output(g, dist, pred, src)) 
                printf("The output is valid");
            else printf("The output is invalid");

            break;
        }

        case 5: {
            // 22.3.10
            int numVertices = 6;
            MatGraph* g = mat_graph_create(numVertices);

            mat_graph_add_directed_reliability_edge(g, 0, 1, 0.4);
            mat_graph_add_directed_reliability_edge(g, 0, 2, 0.1);
            mat_graph_add_directed_reliability_edge(g, 2, 1, 0.2);
            mat_graph_add_directed_reliability_edge(g, 1, 3, 0.1);
            mat_graph_add_directed_reliability_edge(g, 2, 3, 0.5);
            mat_graph_add_directed_reliability_edge(g, 3, 4, 0.3);
            mat_graph_add_directed_reliability_edge(g, 4, 5, 0.2);

            int dist[MAX_GRAPH_VERTICES];
            int pred[MAX_GRAPH_VERTICES];
            int src = 0;

            heap_dial(g, src, dist, pred);
            print_dijkstra_solution(dist, pred, numVertices, src);

            if (verify_dijkstra_output(g, dist, pred, src)) 
                printf("The output is valid");
            else printf("The output is invalid");

            break;
        }

        case 6: {
            // 22.3.12
            int numVertices = 6;
            MatGraph* g = mat_graph_create(numVertices);

            mat_graph_add_directed_reliability_edge(g, 0, 1, 0.4);
            mat_graph_add_directed_reliability_edge(g, 0, 2, 0.1);
            mat_graph_add_directed_reliability_edge(g, 2, 1, 0.2);
            mat_graph_add_directed_reliability_edge(g, 1, 3, 0.1);
            mat_graph_add_directed_reliability_edge(g, 2, 3, 0.5);
            mat_graph_add_directed_reliability_edge(g, 3, 4, 0.3);
            mat_graph_add_directed_reliability_edge(g, 4, 5, 0.2);

            int dist[MAX_GRAPH_VERTICES];
            int pred[MAX_GRAPH_VERTICES];
            int src = 0;
            int C = 2;

            bucket_dijkstra(g, src, dist, pred, C);
            print_dijkstra_solution(dist, pred, numVertices, src);

            if (verify_dijkstra_output(g, dist, pred, src)) 
                printf("The output is valid");
            else printf("The output is invalid");

            break;
        }
        
        default:
            break;
    }
    return 0;
}