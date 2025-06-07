#include "part_2_sorting_and_order_statistics/6_heapsort/heapsort.h"

int main() {
    int arr[] = {5, 13, 2, 25, 7, 17, 20, 8, 4};
    int n = sizeof(arr) / sizeof(arr[0]);

    print_arr(arr, n);

    heapsort(arr, n);

    print_arr(arr, n);

    return 0;
}