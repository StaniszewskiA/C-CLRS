#include "part_7_selected_topics/26_multithreaded_algorithms/multithreaded_algorithms.h"

#define TASK 7

int main(void) {
    switch (TASK) {
        case 1: {
            // Naive parallel matrix multiply
            test_p_matrix_multiply();
            break;
        }

        case 2:{
            // Parallel recurisve matrix multiply
            test_p_matrix_multiply_recursive();
            break;
        }
        
        case 3: {
            // Parallel Strassen algorithm
            test_p_strassen_algorithm();
            break;
        }
        
        case 4: {
            // Test all matrix multiplication methods
            test_all_matrix_multiplication_methods();
            break;
        }

        case 5: {
            // Fast parallel matrix multiplication
            test_p_fast_matrix_multiply();
            break;
        }

        case 6: {
            // Parallel multiplication of non-square matrices
            test_p_get_matrix_multiply();
            break;
        }

        case 7: {
            // Parallel Floyd-Warshall algorithm
            test_p_floyd_warshall();
            break;
        }
    }
}
