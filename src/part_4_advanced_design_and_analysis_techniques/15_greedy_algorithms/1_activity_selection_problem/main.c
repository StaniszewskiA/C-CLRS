#include "part_4_advanced_design_and_analysis_techniques/15_greedy_algorithms/greedy_algorithms.h"

#define TASK 5

int main(void) {
    int s[] = {0, 1, 3, 5, 8, 5};  
    int f[] = {0, 2, 4, 7, 9, 9};  
    int n = sizeof(s) / sizeof(s[0]) - 1;

    switch (TASK)
    {
        case 1: {
            recursive_activity_selector(s, f, 0, n);
            break;
        }

        case 2: {
            greedy_activity_selector(s, f, n);
            break;
        }

        case 3: {
            // 15.1-1
            dynamic_activity_selector(s, f, n);
            break;
        }

        case 4: {
            // 15.1-4
            Activity activities[] = {
                {30, 75}, {0, 50}, {60, 150}, {10, 20}, {80, 120}
            };
            int n4 = sizeof(activities) / sizeof(activities[0]);
            max_halls(activities, n4);

            break;
        }

        case 5: {
            // 15.1-5
            ValuedActivity activity[] = {
                {1, 3, 50}, {2, 5, 20}, {6, 9, 100}, {3, 8, 200}, {9, 10, 150}
            };
            int n = sizeof(activity) / sizeof(activity[0]);

            printf("Max total value: %d\n",
                max_activity_value(activity, n));

            break;
        }
        
        default:
            break;
    }
}