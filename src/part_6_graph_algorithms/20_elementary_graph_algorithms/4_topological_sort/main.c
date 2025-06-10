#include "part_6_graph_algorithms/20_elementary_graph_algorithms/elementary_graph_algorithms.h"

#define TASK 3


int main(void) {
    switch (TASK)
    {
        case 1: {
            // 20.4-2
            int numVertices = 5;
            MatGraph* g = mat_graph_create(numVertices);

            mat_graph_add_directed_edge(g, 0, 1);
            mat_graph_add_directed_edge(g, 0, 2);
            mat_graph_add_directed_edge(g, 1, 3);
            mat_graph_add_directed_edge(g, 2, 3);
            mat_graph_add_directed_edge(g, 3, 4);

            if (mat_graph_is_dag(g)) {
                int s = 0, t = 4;
                int res = mat_graph_count_simple_paths(g, s, t);
                printf("Number of simple paths from %d to %d: %d\n", s, t, res);
            } else printf("Passed graph is not a DAG");

            mat_graph_free(g);
            break;
        }

        case 2: {
            // 20.4-2
            int numVertices = 5;
            MatGraph* g = mat_graph_create(numVertices);

            mat_graph_add_undirected_edge(g, 0, 1);
            mat_graph_add_undirected_edge(g, 0, 2);
            mat_graph_add_undirected_edge(g, 1, 3);
            mat_graph_add_undirected_edge(g, 2, 3);
            mat_graph_add_undirected_edge(g, 3, 4);

            if (mat_graph_is_acyclic(g)) printf("The graph is acyclic\n");
            else printf("The graph contains a cycle\n");

            mat_graph_free(g);
            break;
        }

        case 3: {
            // 20.4-5
            int numVertices = 5;
            MatGraph* g = mat_graph_create(numVertices);

            mat_graph_add_directed_edge(g, 0, 1);
            mat_graph_add_directed_edge(g, 0, 2);
            mat_graph_add_directed_edge(g, 1, 3);
            mat_graph_add_directed_edge(g, 2, 3);
            mat_graph_add_directed_edge(g, 3, 4);


            int result[MAX_VERTICES];
            if (!mat_graph_is_dag(g)) printf("Passed graph is not a DAG\n");
            else if (!mat_graph_indeg_topo_sort(g, result)) printf("Graph could not be sorted\n");
            else {
                printf("Topological order: ");
                for (int i = 0; i < numVertices; i++) printf("%d ", result[i]);
                printf("\n");
            }

            mat_graph_free(g);
            break;

            break;
        }
        
        default:
            break;
    }
    return 0;
}