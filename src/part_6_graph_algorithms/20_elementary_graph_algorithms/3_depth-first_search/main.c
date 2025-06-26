#include "part_6_graph_algorithms/20_elementary_graph_algorithms/elementary_graph_algorithms.h"

#define TASK 6

int main(void) {
    switch (TASK)
    {
        case 1: {
            int numVertices = 5;
            ListGraph* g = list_graph_create(numVertices);

            list_graph_add_edge(g, 2, 0);
            list_graph_add_edge(g, 0, 2);
            list_graph_add_edge(g, 1, 2);
            list_graph_add_edge(g, 0, 1);
            list_graph_add_edge(g, 3, 3);
            list_graph_add_edge(g, 1, 3);
            list_graph_add_edge(g, 3, 4);

            int order[] = {2, 0, 1, 3};
            int orderSize = sizeof(order) / sizeof(order[0]);

            printf("DFS: \n");
            dfs(g, order, orderSize);

            list_graph_free(g);

            break;
        }

        case 2: {
            // 20.3-6
            int numVertices = 5;
            ListGraph* g = list_graph_create(numVertices);

            list_graph_add_edge(g, 2, 0);
            list_graph_add_edge(g, 0, 2);
            list_graph_add_edge(g, 1, 2);
            list_graph_add_edge(g, 0, 1);
            list_graph_add_edge(g, 3, 3);
            list_graph_add_edge(g, 1, 3);
            list_graph_add_edge(g, 3, 4);

            int order[] = {2, 0, 1, 3};
            int orderSize = sizeof(order) / sizeof(order[0]);

            printf("DFS: \n");
            iterative_dfs(g, order, orderSize);

            list_graph_free(g);

            break;
        }

        case 3: {
            // 20.3-9
            int numVertices = 5;
            struct ColoredGraph* g = colored_graph_create(numVertices);

            colored_graph_add_edge(g, 2, 0);
            colored_graph_add_edge(g, 0, 2);
            colored_graph_add_edge(g, 1, 2);
            colored_graph_add_edge(g, 0, 1);
            colored_graph_add_edge(g, 3, 3);
            colored_graph_add_edge(g, 1, 3);
            colored_graph_add_edge(g, 3, 4);

            colored_graph_free(g);

            break;
        }

        case 4: {
            // 20.3-11
            int numVertices = 5;
            ListGraph* g = list_graph_create(numVertices);

            list_graph_add_undirected_edge(g, 2, 0);
            list_graph_add_undirected_edge(g, 0, 2);
            list_graph_add_undirected_edge(g, 1, 2);
            list_graph_add_undirected_edge(g, 0, 1);
            list_graph_add_undirected_edge(g, 3, 3);
            list_graph_add_undirected_edge(g, 1, 3);
            list_graph_add_undirected_edge(g, 3, 4);

            dfs_both_dirs(g);

            list_graph_free(g);
            
            break;
        }

        case 5: {
            // 20.3-12
            int numVertices = 7;
            CCGraph* g = cc_graph_create(numVertices);

            cc_graph_add_undirected_edge(g, 0, 1);
            cc_graph_add_undirected_edge(g, 1, 2);
            cc_graph_add_undirected_edge(g, 3, 4);
            cc_graph_add_undirected_edge(g, 5, 6);

            cc_dfs(g);
            cc_graph_free(g);

            break;
        }

        case 6: {
            // 20.3.13
            int numVertices = 6;
            ListGraph* g = list_graph_create(numVertices);

            list_graph_add_edge(g, 0, 1);
            list_graph_add_edge(g, 0, 2);
            list_graph_add_edge(g, 1, 3);
            list_graph_add_edge(g, 2, 3);
            list_graph_add_edge(g, 3, 4);
            list_graph_add_edge(g, 4, 5);

            if (list_graph_is_singly_connected(g)) printf("The graph is singly connected.\n");
            else printf("The graph is not singly connected.\n");

            list_graph_free(g);

            break;
        }
        
        default:
            break;
    }

    return 0;
}