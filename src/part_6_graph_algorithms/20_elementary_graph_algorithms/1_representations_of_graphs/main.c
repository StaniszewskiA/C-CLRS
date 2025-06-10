#include "part_6_graph_algorithms/20_elementary_graph_algorithms/elementary_graph_algorithms.h"

#define TASK 6

int main(void) {
    int numVertices = 5;
 
    switch (TASK)
    {
        case 1: {
            // 20.1-3 with adjList
            Node* adjList[numVertices];
            init_adj_list(adjList, numVertices);

            int edges[][2] = {
                {0, 1},
                {0, 2},
                {1, 2},
                {2, 0},
                {3, 4}
            };
            int numEdges = sizeof(edges) / sizeof(edges[0]);

            insert_edges(adjList, edges, numEdges);

            printf("Original Graph (Adjacency List):\n");
            print_adj_list(adjList, numVertices);

            Node* adjListT[numVertices];
            init_adj_list(adjListT, numVertices);

            list_graph_transpose(adjList, adjListT, numVertices);

            printf("Transposed Graph (Adjacency List):\n");
            print_adj_list(adjListT, numVertices);

            free_adj_list(adjList, numVertices);
            free_adj_list(adjListT, numVertices);

            break;
        }

        case 2: {
            // 20.1-3 with adjMat
            int** matrix = graph_allocate_matrix(numVertices);
            init_matrix(matrix, numVertices);
            mat_set_edges(matrix);

            printf("\nOriginal Graph (Adjacency Matrix):\n");
            graph_print_matrix(matrix, numVertices);

            int** matrixT = graph_allocate_matrix(numVertices);
            mat_graph_transpose(matrix, matrixT, numVertices);

            printf("\nTransposed Graph (Adjacency Matrix):\n");
            graph_print_matrix(matrixT, numVertices);


            graph_free_matrix(matrix, numVertices);
            graph_free_matrix(matrixT, numVertices);

            break;
        }

        case 3:{
            // 20.1-4
            Node* adjList[numVertices];
            init_adj_list(adjList, numVertices);

            int edges[][2] = {
                {0, 1},
                {0, 2},
                {1, 2},
                {0, 2}, // duplicate
                {3, 4},
                {3, 4}, // duplicate
                {1, 1}  // self-loop
            };
            int numEdges = sizeof(edges) / sizeof(edges[0]);

            insert_edges(adjList, edges, numEdges);

            printf("Original Graph (Adjacency List):\n");
            print_adj_list(adjList, numVertices);

            Node* result[numVertices];
            init_adj_list(result, numVertices);

            demultify_graph(adjList, result, numVertices);
            printf("Demultified Graph (Adjacency List):\n");
            print_adj_list(result, numVertices);

            free_adj_list(adjList, numVertices);
            free_adj_list(result, numVertices);

            break;
        }

        case 4: {
            // 20.1-5 with adjList
            Node* adjList[numVertices];
            init_adj_list(adjList, numVertices);

            int edges[][2] = {
                {0, 1},
                {0, 2},
                {1, 2},
                {2, 4},
                {0, 4}
            };
            int numEdges = sizeof(edges) / sizeof(edges[0]);

            insert_edges(adjList, edges, numEdges);

            printf("Original Graph (Adjacency List):\n");
            print_adj_list(adjList, numVertices);

            Node* result[numVertices];
            init_adj_list(result, numVertices);

            adj_square_graph(adjList, result, numVertices);
            printf("Squared Graph (Adjacency List):\n");
            print_adj_list(result, numVertices);

            free_adj_list(adjList, numVertices);
            free_adj_list(result, numVertices);

            break;
        }

        case 5: {
            // 20.1-5 with adjMat
            int** matrix = graph_allocate_matrix(numVertices);
            init_matrix(matrix, numVertices);
            mat_set_edges(matrix);

            printf("\nOriginal Graph (Adjacency Matrix):\n");
            graph_print_matrix(matrix, numVertices);

            int** res = graph_allocate_matrix(numVertices);

            mat_square_graph(matrix, res, numVertices);
            printf("\nSquared Graph (Adjacency Matrix):\n");
            graph_print_matrix(res, numVertices);

            graph_free_matrix(matrix, numVertices);
            graph_free_matrix(res, numVertices);

            break;
        }

        case 6: {
            // 20.1-6
            int** matrix = graph_allocate_matrix(numVertices);
            init_matrix(matrix, numVertices);
            mat_set_edges(matrix);

            find_universal_sink(matrix, numVertices);
            graph_free_matrix(matrix, numVertices);

            break;
        }
        
        default:
            break;
    }

    return 0;
}