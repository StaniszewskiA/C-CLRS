#include <math.h>
#include <stdio.h>

#define TASK 1

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

int main(void) {
    int W = 50;
    Item items[] = {{10, 60}, {20, 10}, {30, 120}};
    int n = sizeof(items) / sizeof(items[0]);

    switch (TASK)
    {
        case 1: {
            // 15.2-2
            printf("Maximum value in Knapsack = %d\n", 
                discrete_knapsack(W, items, n));
            
            break;
        }
        
        default:
            break;
    }

    return 0;
}