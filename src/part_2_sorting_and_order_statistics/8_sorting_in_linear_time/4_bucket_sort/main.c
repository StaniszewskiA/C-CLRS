#include "part_2_sorting_and_order_statistics/8_sorting_in_linear_time/sorting_in_linear_time.h"


int main(void) {
    float A[NARRAY] = {
        0.79, 
        0.13, 
        0.16, 
        0.64, 
        0.30, 
        0.20, 
        0.89, 
        0.53, 
        0.71, 
        0.42
    };

    printf("Initial array: ");
    print_arr_float(A);
    printf("-------------\n");

    bucket_sort(A);
    printf("-------------\n");
    printf("Sorted array: ");
    print_arr_float(A);
    return 0;
}