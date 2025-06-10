#include "part_6_graph_algorithms/20_elementary_graph_algorithms/elementary_graph_algorithms.h"

#define TASK 3

int main(void) {
    // ListGraph* listG = list_graph_create(4);
    // list_graph_add_edge(listG, 0, 1);
    // list_graph_add_edge(listG, 0, 2);
    // list_graph_add_edge(listG, 1, 2);
    // list_graph_add_edge(listG, 2, 0);
    // list_graph_add_edge(listG, 2, 3);
    // list_graph_add_edge(listG, 3, 3);

    // printf("BFS with source 2\n");
    // list_graph_bfs(listG, 2);
    // list_graph_free(listG);

    switch (TASK)
    {
        case 1: {
            // 20.2-4
            MatGraph* matG = mat_graph_create(4);
            mat_graph_add_undirected_edge(matG, 0, 1);
            mat_graph_add_undirected_edge(matG, 0, 2);
            mat_graph_add_undirected_edge(matG, 1, 2);
            mat_graph_add_undirected_edge(matG, 2, 0);
            mat_graph_add_undirected_edge(matG, 2, 3);
            mat_graph_add_undirected_edge(matG, 3, 3);

            printf("BFS with source 2\n");
            mat_graph_bfs(matG, 2);
            mat_graph_free(matG);

            break;
        }

        case 2: {
            // 20.2-7
            int n = 6;
            int rivalries[][2] = {
                {0, 1},
                {1, 2},
                {2, 3},
                {3, 4},
                {4, 5},
                {5, 0}
            };
            int r = sizeof(rivalries) / sizeof(rivalries[0]);

            ListGraph* g = list_graph_create(n);
            Role roles[MAX_VERTICES];
            for (int i = 0; i < n; i++) roles[i] = UNCOLORED;

            for (int i = 0; i < r; i++) 
                list_graph_add_edge(g, rivalries[i][0], rivalries[i][1]);

            if (can_assign_wrestlers(g, roles)) printf("Wrestlers can be assigned");
            else printf("Wrestlers can't be assigned.");
            
            list_graph_free(g);

            break;
        }

        case 3: {
            // 20.2-8
            ListGraph* g = list_graph_create(6);
            list_graph_add_edge(g, 0, 1);
            list_graph_add_edge(g, 1, 2);
            list_graph_add_edge(g, 1, 3);
            list_graph_add_edge(g, 3, 4);
            list_graph_add_edge(g, 4, 5);

            int diameter = tree_diameter(g);
            printf("Diameter of the tree: %d\n", diameter);

            break;
        }
        
        default:
            break;
    }

    return 0;
}