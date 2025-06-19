#include "part_6_graph_algorithms/25_bipartite_matching/bipartite_matching.h"

#define TASK 3

int main(void) {
    switch (TASK)
    {
        case 1: {
            // Basic Gale-Shapley algorithm
            test_gale_shapley_algorithm();
            break;
        }

        case 2: {
            // NRMP problem
            test_nrmp_solver();
            break;
        }

        case 3: {
            // Stable roommates problem
            test_stable_roommates_solver();
            break;
        }
        
        default:
            break;
    }
}