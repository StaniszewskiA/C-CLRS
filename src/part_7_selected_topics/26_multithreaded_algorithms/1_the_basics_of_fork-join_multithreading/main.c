#include "part_7_selected_topics/26_multithreaded_algorithms/multithreaded_algorithms.h"

#define TASK 7

int main(void) {
    switch (TASK) {
        case 1: {
            // Multithreaded Fibonacci
            test_p_fib();
            break;
        }

        case 2: {
            // Multithreaded matrix x vector
            test_p_mat_vec();
            break;
        }

        case 3: {
            // Recursive multithreaded matrix x vector
            test_p_mat_vec_recursive();
            break;
        }

        case 4: {
            // Race example
            test_race_example();
            break;
        }

        case 5: {
            // Parallel matrix x vector with race condition
            test_p_mat_vec_wrong();
            break;
        }

        case 6: {
            // 26.1-7
            test_p_mat_vec_dc();
            break;
        }

        case 7: {
            // 26.1-8
            test_p_transpose();
            break;
        }
    }
}
