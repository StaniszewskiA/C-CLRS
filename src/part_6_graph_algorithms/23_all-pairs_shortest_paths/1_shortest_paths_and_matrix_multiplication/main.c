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
    int L1[MAX_MAT_SIZE][MAX_MAT_SIZE];

    switch (TASK)
    {
        case 1: {
            // Slow-APSP
            slow_apsp(W, L1);
            print_named_mat(L1, "Slow APSP result");

            break;
        }

        case 2: {
            // Faster-APSP
            faster_apsp(W, L1);
            print_named_mat(L1, "Faster APSP result");

            break;
        }

        case 3: {
            // 23.1-5
            int dist[MAX_MAT_SIZE];
            int src = 0;
            pseudo_bellman_ford(W, src, dist);
            break;
        }

        case 4: {
            // 23.1-6 slow
            space_optimized_slow_apsp(W, L1);
            print_named_mat(L1, "Slow APSP result");
            break;
        }

        case 5: {
            // 23.1-6 faster
            space_optimized_faster_apsp(W, L1);
            print_named_mat(L1, "Faster APSP result");
            break;
        }

        case 6: {
            // 23.1-7
            space_optimized_faster_apsp(W, L1);
            int pred[MAX_MAT_SIZE][MAX_MAT_SIZE];
            compute_pred_mat(L1, W, pred);
            print_pred_mat(pred, "Predecessor matrix from L");
            break;
        }

        case 7: {
            // 23.1-8
            int pred[MAX_MAT_SIZE][MAX_MAT_SIZE];
            space_optimized_slow_apsp_mod(W, L1, pred);
            print_named_mat(L1, "Slow APSP MOD result");
            print_pred_mat(pred, "Predecessor matrix");
            break;
        }

        case 8: {
            // 23.1-9
            faster_apsp_neg_cycle(W, L1);
            break;
        }

        case 9: {
            // 23.1-10
            int len = min_length_neg_cycle(W);
            if (len) 
                printf("Minimum-length negative-weight cycle has %d edges.\n", len);
            else 
                printf("No negative-weight cycle found.\n");
            break;
        }
        
        default:
            break;
    }

    return 0;
}