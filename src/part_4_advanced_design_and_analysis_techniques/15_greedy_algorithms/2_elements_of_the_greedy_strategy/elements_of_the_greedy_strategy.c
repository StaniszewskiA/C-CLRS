#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define TASK 3

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

int min_intervals(double points[], int n) {
    if (n == 0) return 0;

    qsort(points, n, sizeof(double), compare);

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
#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct FracItem {
    // Item with fractional values
    double value;
    double weight;
} FracItem;

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

int partition(FracItem arr[], int low, int high, int pivot) {
    int i = low, j = high;

    while (i <= j) {
        while (vw_ratio(arr[i]) < pivot) i++;
        while (vw_ratio(arr[j]) > pivot) j--;

        if (i <= j) {
            FracItem temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }

    return i;
} 

FracItem select_median(FracItem arr[], int low, int high) {
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

    return select_median(arr, low, high);
}

double fractional_knapsack(FracItem items[], int n, int W) {
    if (n == 0 || W == 0) return 0;

    FracItem medianItem = select_median(items, 0, n - 1);
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

int main(void) {
    int W1 = 50;
    Item items[] = {{10, 60}, {20, 10}, {30, 120}};
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
                fractional_knapsack(items, n1, W1));

            break;
        }
        
        default:
            break;
    }

    return 0;
}