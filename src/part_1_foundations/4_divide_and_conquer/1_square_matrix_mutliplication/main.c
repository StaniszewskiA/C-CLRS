#include "part_1_foundations/4_divide_and_conquer/divide_and_conquer.h"

int main() {
    int n = 4;

    int A[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    int B[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE] = {
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 1}
    };

    int C[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE] = {0};

    matrix_add_recursive(A, B, C, n);

    printf("Result matrix: \n");
    print_matrix(C, n);

    return 0;
}