#include "part_4_advanced_design_and_analysis_techniques/15_greedy_algorithms/greedy_algorithms.h"

/*
    15.2-2

    O(nW)

    n - number of items
    W - maximum weight
*/
int discrete_knapsack(int W, KnapsackItem items[], int n) {
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
int compare2(const void* a, const void* b) {
    return (*(double*)a > *(double*)b) - (*(double*)a < *(double*)b);
}

int min_intervals(double points[], int n) {
    if (n == 0) return 0;

    qsort(points, n, sizeof(double), compare2);

    int count = 0, i = 0;

    while (i < n) {
        count++;
        double leftmost = points[i];
        while (i < n && points[i] <= leftmost + 1.0) i++;
    }

    return count;
}

/*
    15.2-6

    Fractional knapsack problem solved with 
    the median of medians algorithms.

    Recurrence: T(n) = T(n/2) + cn

    Time complexity: O(n)
    Space complexity: O(n)?
*/
double vw_ratio(FracItem item) {
    // printf("%.2f\n", item.value);
    // printf("%.2f\n", item.weight);
    return item.value / item.weight;
}

int compare_wv(const void* a, const void* b) {
    FracItem *itemA = (FracItem*)a;
    FracItem *itemB = (FracItem*)b;

    double ratioA = vw_ratio(*itemA);
    double ratioB = vw_ratio(*itemB);

    if (ratioA < ratioB) return -1;
    if (ratioA > ratioB) return 1;
    return 0;
}

FracItem select_median_frac(FracItem arr[], int low, int high) {
    if (high - low <= 5) {
        qsort(&arr[low], high - low + 1, sizeof(FracItem), compare_wv);
        return arr[(low + high) /  2];
    }

    int i;

    for (i = low; i < high; i += 5) {
        int subHigh = MAX(i + 4, high);
        qsort(&arr[i], subHigh - i + 1, sizeof(FracItem), compare_wv);
        arr[(low + high) / 2] = arr[(i + subHigh) / 2];
    }

    return select_median_frac(arr, low, high);
}

double fractional_knapsack(FracItem items[], int n, int W) {
    if (n == 0 || W == 0) return 0;

    FracItem medianItem = select_median_frac(items, 0, n - 1);
    double medianVW = vw_ratio(medianItem);

    printf("Median item's VW ratio: %.2f\n", medianVW);

    FracItem *highRatioItems = malloc(n * sizeof(FracItem));
    FracItem *lowRatioItems = malloc(n * sizeof(FracItem));

    if (!highRatioItems || !lowRatioItems) {
        printf("Malloc failed");
        free(highRatioItems);
        free(lowRatioItems);
        return 0.0;
    }

    int i;
    int highCnt = 0, lowCnt = 0;
    double highWeight = 0;
    double res;

    for (i = 0; i < n; i++) {
        if (vw_ratio(items[i]) > medianVW) {
            highRatioItems[highCnt++] = items[i];
            highWeight += items[i].weight;
        } 
        else if (vw_ratio(items[i]) < medianVW) 
            lowRatioItems[lowCnt++] = items[i];
    }

    /*
        Case 1: If high-value items' weight exceeds W,
                solve for high-value items.
    */
    if (highWeight > W) {
        res = fractional_knapsack(highRatioItems, highCnt, W);
        free(highRatioItems);
        free(lowRatioItems);
        return res;
    }

    /*
        Case 2: Solve for low-value items.
    */
    res = 0;
    for (i = 0; i < highCnt; i++) res += highRatioItems[i].value;

    double remainingCap = W - highWeight;
    res += fractional_knapsack(lowRatioItems, lowCnt, remainingCap);

    free(highRatioItems);
    free(lowRatioItems);
    return res;
}
