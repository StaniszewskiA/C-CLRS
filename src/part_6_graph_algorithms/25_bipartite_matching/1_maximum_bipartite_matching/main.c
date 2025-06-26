#include "part_6_graph_algorithms/25_bipartite_matching/bipartite_matching.h"

#define TASK 2

int main(void) {
    switch (TASK)
    {
        case 1: {
            test_hopcroft_karp_algorithm();
            break;
        }

        case 2: {
            test_early_stopping_hopcroft_karp_algorithm();
            break;
        }
        
        default:
            break;
    }

    return 0;
}