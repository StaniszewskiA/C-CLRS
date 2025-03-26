#include <stdio.h>
#include <limits.h>

#define TASK 1

/*
    15-1: Coin changing.
*/
void make_change_greedy(int n) {
    int quarters = 0, dimes = 0, nickels = 0, pennies = 0;
    int coins[] = {25, 10, 5, 1};
    int* coinCounts[] = {&quarters, &dimes, &nickels, &pennies};
    int original_n = n;
    int i;

    for (i = 0; i < 4; i++) {
        while (n >= coins[i]) {
            n -= coins[i];
            (*coinCounts[i])++;
        }
    }

    printf("Change for %d cents:\n", original_n);
    printf("Quarters: %d\n", quarters);
    printf("Dimes: %d\n", dimes);
    printf("Nickels: %d\n", nickels);
    printf("Pennies: %d\n", pennies);

}

// O(nk) DP solution.
void make_change_optimal(int denoms[], int k, int n) {
    int i, j;
    int dp[n + 1];
    int coinsUsed[n + 1];

    // Base cases
    dp[0] = 0;
    coinsUsed[0] = -1;
    for (i = 1; i <= n; i++) dp[i] = INT_MAX;

    for (i = 0; i < k; i++) {
        for (j = denoms[i]; j <= n; j++) {
            if (dp[j - denoms[i]] != INT_MAX && dp[j] > dp[j - denoms[i]] + 1) {
                dp[j] = dp[j - denoms[i]] + 1;
                coinsUsed[j] = i;
            }
        }
    }

    if (dp[n] == INT_MAX) printf("Can't change coins.");
    else {
        printf("Minimum coins neede to make change for %d cents: %d\n",
            n, dp[n]);
        printf("Coins used:\n");
        int amount = n;
        while (amount > 0) {
            int coinIdx = coinsUsed[amount];
            printf("%d cent coin\n", denoms[coinIdx]);
            amount -= denoms[coinIdx];
        }
    }
}

/*
    15-2: Scheduling to minize average completion time.
*/

int main(void) {
    switch (TASK)
    {
        case 1: {
            // 15-1
            // int n = 110;
            // make_change_greedy(n);

            int denoms[] = {1, 2, 3};
            int k = sizeof(denoms) / sizeof(denoms[0]);
            int n = 6;

            make_change_optimal(denoms, k, n);

            break;
        }

        case 2: {
            // 15-2
            break;
        }
        
        default:
            break;
    }

    return 0;
}