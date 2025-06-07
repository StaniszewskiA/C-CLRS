#include "../../../../include/part_1_foundations/4_divide_and_conquer/divide_and_conquer.h"

int main() {
    int n = 2;
    
    double** A = allocate_matrix(n);
    double** B = allocate_matrix(n);
    double** C = allocate_matrix(n);

    
    A[0][0] = 1.0; A[0][1] = 2.0;
    A[1][0] = 3.0; A[1][1] = 4.0;
    
    B[0][0] = 5.0; B[0][1] = 6.0;
    B[1][0] = 7.0; B[1][1] = 8.0;
    
    printf("Matrix A:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%8.2f ", A[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("Matrix B:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%8.2f ", B[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("Computing A by B using Strassen's algorithm...\n");
    strassen_algorithm(A, B, C, n);
    
    printf("Result Matrix C = A by B:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%8.2f ", C[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("Expected result should be:\n");
    printf("   19.00    22.00\n");
    printf("   43.00    50.00\n");
    printf("\n");

    free_matrix(A, n);
    free_matrix(B, n);
    free_matrix(C, n);

    return 0;
}