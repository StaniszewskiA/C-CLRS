#include "part_2_sorting_and_order_statistics/8_sorting_in_linear_time/sorting_in_linear_time.h"

int main(void) {
    int arr1[] = {0, 1, 2, 3, 6, 4, 5};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int k1 = 6;

    printf("Original array: ");
    print_arr(arr1, n1);

    int* P = (int*)malloc((k1 + 1) * sizeof(int));
    preprocess(arr1, n1, k1, P);

    printf("Number in range [0, 3]: %d\n", count_in_range(P, 0, 3));
    free(P);
    
    int arr2[] = {6, 0, 2, 0, 1, 3, 4, 6, 1, 3, 2};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int k2 = 6;

    printf("Before sorting: ");
    print_arr(arr2, n2);

    count_sort_prim(arr2, n2, k2);

    printf("After sorting:  ");
    print_arr(arr2, n2);
    
    double arr3[] = {3.14, 1.41, 2.72, 1.62, 2.46, 0.99, 3.01};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    int d = 2;

    printf("Before sorting: ");
    print_arr_double(arr3, n3);

    count_sort_real(arr3, n3, d);
    
    printf("After sorting:  ");
    print_arr_double(arr3, n3);

    return 0;
}