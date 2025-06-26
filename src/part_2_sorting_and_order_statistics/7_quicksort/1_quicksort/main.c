#include "part_2_sorting_and_order_statistics/7_quicksort/quicksort.h"

int main(void) {
    int A[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(A) / sizeof(A[0]);
    
    printf("Unsorted array: \n");
    print_arr(A, n);
    
    int pi = partition(A, 0, n - 1);
    printf("Pivot index: %d\n", pi);

    quicksort(A, 0, n - 1);
    
    print_arr(A, n);
    
    return 0;
}