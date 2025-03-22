#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define TASK 2

/*
    15.2-2

    O(nW)

    n - number of items
    W - maximum weight
*/
typedef struct Item {
    int value;
    int weight;
} Item;

int discrete_knapsack(int W, Item items[], int n) {
    int dp[n + 1][W + 1];
    int i, j;

    // DP init
    for (i = 1; i < n; i++) dp[i][0] = 0;
    for (j = 1; j < W; j++) dp[0][j] = 0;

    for (i = 0; i < n; i++) {
        for (j = 0; j < W; j++) {
            if (i == 0 || j == 0) dp[i][j] = 0;
            else if (items[i - 1].weight <= j) {
                /*
                    Recursive formula:
                    
                    dp[i][j] = max(dp[i - 1][j], v_1 + dp[i - 1][j - w_i])
                */
                return fmax(
                    items[i - 1].value + dp[i - 1][j - items[i - 1].weight], 
                    dp[i - 1][j]
                );
            }
            else dp[i][j] = dp[i - 1][j];
        }
    }

    return dp[n][W];
}

/*
    15.2-5

    O(n*log(n))

    n - number of points in the input set.
*/
int compare(const void* a, const void* b) {
    return (*(double*)a > *(double*)b) - (*(double*)a < *(double*)b);
}

size_t min_intervals(double points[], int n) {
    if (n == 0) return 0;

    qsort(points, n, sizeof(double), compare);

    size_t count = 0;
    int i = 0;

    while (i < n) {
        count++;
        double leftmost = points[i];
        while (i < n && points[i] <= leftmost + 1.0) i++;
    }

    return count;
}

int main(void) {
    switch (TASK)
    {
        case 1: {
            // 15.2-2
            int W1 = 50;
            Item items[] = {{10, 60}, {20, 10}, {30, 120}};
            int n1 = sizeof(items) / sizeof(items[0]);

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
        
        default:
            break;
    }

    return 0;
}