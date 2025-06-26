#include "part_2_sorting_and_order_statistics/9_medians_and_order_statistics/medians_and_order_statistics.h"

int main(void) {
    srand(time(NULL));

    int A[] = {12, 3, 5, 7, 19, 26, 4, 2};
    int n = sizeof(A) / sizeof(A[0]);
    int i = 1; 

    int result = randomized_select_iter(A, 0, n - 1, i);
    printf("The %d-th smallest element is %d\n", i, result);

    return 0;
}