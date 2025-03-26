#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define TASK 3

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
    15-2 a: Scheduling to minize average completion time.

    O(n*log(n))
*/
typedef struct {
    int id;
    int pTime; // Abb. for processing time
} Task;

int compare(const void* a, const void* b) {
    return ((Task*)a)->pTime - ((Task*)b)->pTime;
}

void schedule_tasks(Task tasks[], int n) {
    qsort(tasks, n, sizeof(Task), compare);
    
    unsigned totalCompletionTime = 0;
    int i;

    for (i = 0; i < n; i++) totalCompletionTime += tasks[i].pTime;

    double avgCompletionTime = (double) totalCompletionTime / n;
    printf("Average Completion Time: %.2f\n", avgCompletionTime);
}

/*
    15-2 b: Scheduling to minize average completion time of online tasks.

    O(n^2) (?)
*/
typedef struct {
    int id;
    int pTime;
    int rTime; // Abb. for release time
} OnlineTask;

int compare_online_p_times(const void* a, const void* b) {
    return ((OnlineTask*)a)->pTime - ((OnlineTask*)b)->pTime;
}

int compare_online_r_times(const void* a, const void* b) {
    return ((OnlineTask*)a)->rTime - ((OnlineTask*)b)->rTime;
}

void schedule_online_tasks(OnlineTask tasks[], int n) {
    qsort(tasks, n, sizeof(OnlineTask), compare_online_r_times);

    unsigned totalCompletionTime = 0;
    unsigned completedTasks = 0;
    unsigned currTime = 0;

    OnlineTask* q = malloc(n * sizeof(OnlineTask));
    int qSize = 0;
    int i;

    while (completedTasks < n) {
        while (completedTasks < n && tasks[completedTasks].rTime <= currTime) {
            q[qSize++] = tasks[completedTasks];
            completedTasks++;
        }

        if (qSize > 0) {
            qsort(q, qSize, sizeof(OnlineTask), compare_online_p_times);
            OnlineTask currTask = q[0];

            // Execute
            currTime += currTask.pTime;
            totalCompletionTime += currTime;

            // Deque task
            for (i = 1; i < qSize; i++) q[i - 1] = q[i];
            qSize--;
        } else {
            // No executable tasks.
            currTime++;
        }
    }

    double avgCompletionTime = (double) totalCompletionTime / n;
    printf("Average Completion Time: %.2f\n", avgCompletionTime);

    free(q);
}

int main(void) {
    switch (TASK)
    {
        case 1: {
            // 15-1
            // int n = 110;
            // make_change_greedy(n);

            int denoms[] = {1, 2, 3};
            int k1 = sizeof(denoms) / sizeof(denoms[0]);
            int n1 = 6;

            make_change_optimal(denoms, k1, n1);

            break;
        }

        case 2: {
            // 15-2 a
            Task tasks[] = {
                {1, 3},  
                {2, 5},  
                {3, 2}
            };
            int n2 = sizeof(tasks) / sizeof(tasks[0]);

            schedule_tasks(tasks, n2);

            break;
        }

        case 3: {
            // 15-2 b
            OnlineTask tasks[] = {
                {1, 6, 1}, 
                {2, 5, 2},  
                {3, 2, 1} 
            };
            int n3 = sizeof(tasks) / sizeof(tasks[0]);

            schedule_online_tasks(tasks, n3);

            break;
        }
        
        default:
            break;
    }

    return 0;
}