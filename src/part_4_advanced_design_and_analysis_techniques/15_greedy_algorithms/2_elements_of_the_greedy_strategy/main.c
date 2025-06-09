#include "part_4_advanced_design_and_analysis_techniques/15_greedy_algorithms/greedy_algorithms.h"

#define TASK 3

int main(void) {
    int W1 = 50;
    KnapsackItem items[] = {{10, 60}, {20, 10}, {30, 120}};
    int n1 = sizeof(items) / sizeof(items[0]);

    switch (TASK)
    {
        case 1: {
            // 15.2-2

            printf("Maximum value in Knapsack = %d\n", 
                discrete_knapsack(W1, items, n1));
            
            break;
        }

        case 2: {
            // 15.2-5
            double points[] = {0.1, 1.2, 1.0, 0.75};
            int n2 = sizeof(points) / sizeof(points[0]);
            
            printf("Minimum num of intervals: %d",
                min_intervals(points, n2));

            break;
        }

        case 3: {
            // 15.2-6
            double W3 = 50.0;
            FracItem items[] = {{10.0, 60.0}, {20.0, 10.0}, {30.0, 120.0}};
            int n1 = sizeof(items) / sizeof(items[0]);

            // FracItem item1;
            // item1.value = 1;
            // item1.weight = 2; 

            // printf("Test ratio: %.2f\n", vw_ratio(item1));

            printf("Maximum value in the knapsack: %.2f\n", 
                fractional_knapsack(items, n1, W3));

            break;
        }
        
        default:
            break;
    }

    return 0;
}