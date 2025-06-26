#include "part_4_advanced_design_and_analysis_techniques/14_dynamic_programming/dynamic_programming.h"

#define TASK 2

int main(void) {
    int p[] = {
        2, 3, 5, 7, 11, 13, 17, 
        19, 23, 29, 31, 37, 41, 
        43, 47, 53, 59, 61, 67, 
        71, 73, 79, 83, 89, 97,
    };
    int n = sizeof(p) / sizeof(p[0]);
    int cost = 2;

    switch (TASK)
    {
        case 1: {
            // Brute-Force
            clock_t start = clock();
            int max_val = rod_cutting_brute_force(p ,n);
            clock_t end = clock();

            double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC; 

            printf("Maximum Obtainable Value: %d\n", max_val);
            printf("Execution Time: %.6f seconds\n", time_taken);
            break;
        }
        case 2: {
            // Top-Down
            clock_t start = clock();
            init_memo(n);
            int max_val = rod_cutting_top_down(p ,n);
            clock_t end = clock();

            double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC; 

            printf("Maximum Obtainable Value: %d\n", max_val);
            printf("Execution Time: %.6f seconds\n", time_taken);
            break;
        }
        case 3: {
            // Bottom-Up
            clock_t start = clock();
            int max_value = rod_cutting_bottom_up(p, n);
            clock_t end = clock();

            double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC; 
            printf("Maximum Obtainable Value: %d\n", max_value);
            printf("Execution Time: %.6f seconds\n", time_taken);
            break;
        }
        case 4: {
            // Bottom-Up with actual solution
            clock_t start = clock();
            rod_cutting_extended_bottom_up(p, n);
            clock_t end = clock();

            double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC; 
            printf("Execution Time: %.6f seconds\n", time_taken);
            break;
        }
        case 5: {
            // 14.1-3
            clock_t start = clock();
            int max_value = rod_cutting_bottom_up_with_cost(p, n, cost);
            clock_t end = clock();

            double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC; 
            printf("Maximum Obtainable Value: %d\n", max_value);
            printf("Execution Time: %.6f seconds\n", time_taken);
            break;
        }
        case 6: {
            // 14.1-4
            memoized_cut_rod_2(p, n);
            break;
        }
        case 7: {
            // 14.1-5
            init_memo(n);
            rod_cutting_extended_top_down(p, n);
            break;
        }
        case 8: {
            // 14.1-6
            int target = 10;
            printf("Fibonacci number at position %d is: %d\n", target, dp_fibonacci(target));
            break;
        }
        default:
            break;
    }

    return 0;
}
