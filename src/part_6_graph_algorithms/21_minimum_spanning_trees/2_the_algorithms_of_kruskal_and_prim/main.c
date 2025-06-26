#include "part_6_graph_algorithms/21_minimum_spanning_trees/minimum_spanning_trees.h"

#define TASK 3

Edge testEdges[MAX_EDGES];
int testEdgeCnt = 0;

int main(void) {
    switch (TASK)
    {
        case 1: {
            // Kruskal
            int n = 4;
            make_set(n, 0);

            mst_add_edge(0, 1, 10);
            mst_add_edge(0, 2, 6);
            mst_add_edge(0, 3, 5);
            mst_add_edge(1, 3, 15);
            mst_add_edge(2, 3, 4);

            ExplicitAdjListGraph* mst = kruskal(n, testEdges, testEdgeCnt);

            printf("\nMST adjacency list:\n");
            for (int i = 0; i < mst->numVertices; i++) {
                printf("%d:", i);
                for (int j = 0; j < mst->adjList[i].neiCnt; j++) {
                    printf(" %d", mst->adjList[i].neis[j]);
                }
                printf("\n");
            }

            explicit_adj_list_graph_free(mst);
            break;
        }

        case 2: {
            // Prim
            int n = 4;
            ExplicitAdjListGraph* g = explicit_adj_list_graph_create(n);

            explicit_adj_list_graph_add_undirected_weighted_edge(g, 0, 1, 10);
            explicit_adj_list_graph_add_undirected_weighted_edge(g, 0, 2, 6);
            explicit_adj_list_graph_add_undirected_weighted_edge(g, 0, 3, 5);
            explicit_adj_list_graph_add_undirected_weighted_edge(g, 1, 3, 15);
            explicit_adj_list_graph_add_undirected_weighted_edge(g, 2, 3, 4);

            printf("Running Prim's algorithm starting from vertex 0:\n");
            prim(g, 0);

            explicit_adj_list_graph_free(g);
            break;
        }

        case 3: {
            // Adjacency matrix Prim
            int adjMat[GRAPH_SIZE][GRAPH_SIZE] = {
                {0, 2, 0, 6, 0},
                {2, 0, 3, 8, 5},
                {0, 3, 0, 0, 7},
                {6, 8, 0, 0, 9},
                {0, 5, 7, 9, 0}
            };
            int root = 0;
            adj_mat_prim(adjMat, root);

            break;
        }
    
        default:
            break;
    }
}
