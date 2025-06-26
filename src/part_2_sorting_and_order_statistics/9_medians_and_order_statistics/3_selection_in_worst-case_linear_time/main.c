#include "part_2_sorting_and_order_statistics/9_medians_and_order_statistics/medians_and_order_statistics.h"

int main(void) {
    int X[] = {1, 3, 5, 7, 9};
    int Y[] = {0, 2, 4, 6, 8};
    int n = sizeof(X) / sizeof(X[0]);

    printf("Median: %d\n", median(X, Y, n));
    return 0;
}