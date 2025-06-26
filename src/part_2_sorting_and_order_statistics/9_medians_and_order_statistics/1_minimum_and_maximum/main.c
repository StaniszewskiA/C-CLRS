#include "part_2_sorting_and_order_statistics/9_medians_and_order_statistics/medians_and_order_statistics.h"

int main() {
    int arr[] = {5, 1, 0, -3, 7, 9, 8, 6};
    int size = sizeof(arr) / sizeof(arr[0]);
    int min, max;

    min_max(arr, size, &min, &max);

    printf("Min: %d, Max: %d\n", min, max);
    
    return 0;
}