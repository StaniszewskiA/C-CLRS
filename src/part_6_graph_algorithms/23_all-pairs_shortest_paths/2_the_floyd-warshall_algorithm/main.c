#include "part_6_graph_algorithms/23_all-pairs_shortest_paths/all-pairs_shortest_paths.h"

#define TASK 9

int main(void) {
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE] = {
        {0, INF, INF, INF, -1, INF},
        {1, 0, INF, 2, INF, INF},
        {INF, 2, 0, INF, INF, -8},
        {-4, INF, INF, 0, 3, INF},
        {INF, 7, INF, INF, 0, INF},
        {INF, 5, 10, INF, INF, 0}
    };
    int D[MAX_MAT_SIZE][MAX_MAT_SIZE];

    switch (TASK)
    {
        case 1: {
            // Basic FW
            floyd_warshall(W, D);
            print_named_mat(D, "Floyd-Warshall result");
            break;
        }

        case 2: {
            // Transitive closure
            int T[MAX_MAT_SIZE][MAX_MAT_SIZE];
            transitive_closure(W, T);
            print_named_bool_mat(T, "Transitive closure of graph W");
            break;
        }

        case 3: {
            // 23.2-2
            int T[MAX_MAT_SIZE][MAX_MAT_SIZE];
            slow_apsp_transitive_closure(W, T);
            print_named_bool_mat(T, "Transitive closure with slow APSP");
            break;
        }

        case 4: {
            // 23.2-3
            int D[MAX_MAT_SIZE][MAX_MAT_SIZE], pred[MAX_MAT_SIZE][MAX_MAT_SIZE];
            floyd_warshall_with_pred(W, D, pred);
            print_named_mat(D, "Floyd-Warshall result");
            print_pred_mat(pred, "Predecessor matrix");
            break;
        }

        case 5: {
            // 23.2-4
            space_optimized_floyd_warshall(W, D);
            print_named_mat(D, "Floyd-Warshall result");
            break;
        }

        case 6: {
            // 23.2-6
            floyd_warshall_neg_cycle_detect(W, D);
            break;
        }

        case 7: {
            // 23.2-7
            int phi[MAX_MAT_SIZE][MAX_MAT_SIZE];
            floyd_warshall_phi(W, D, phi);
            print_named_mat(D, "Floyd-Warshall result");
            printf("Shortest path from 0 to 3: ");
            print_path_phi(phi, 0, 3);
            printf("\n");
            break;
        }

        case 8: {
            // 23.2-8
            int T[MAX_MAT_SIZE][MAX_MAT_SIZE];
            transitive_closure_bfs(W, T);
            print_named_bool_mat(T, "Transitive closure of graph W");
            break;
        }

        case 9: {
            // 23.2-9
            int T[MAX_MAT_SIZE][MAX_MAT_SIZE];
            scc_transitive_closure(W, T);
            print_named_bool_mat(T, "Transitive closure of graph W with SCCs");
            break;
        }
        
        default:
            break;
    }

    return 0;
}