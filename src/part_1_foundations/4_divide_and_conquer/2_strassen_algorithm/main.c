#include "../../../../include/part_1_foundations/4_divide_and_conquer/divide_and_conquer.h"

int main() {
    int n = 2;
    
    int** A = allocate_matrix(n);
    int** B = allocate_matrix(n);
    int** C = allocate_matrix(n);

    
    A[0][0] = 1; A[0][1] = 2;
    A[1][0] = 3; A[1][1] = 4;
    
    B[0][0] = 5; B[0][1] = 6;
    B[1][0] = 7; B[1][1] = 8;
    
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
    printf("   19    22\n");
    printf("   43    50\n");
    printf("\n");

    free_matrix(A, n);
    free_matrix(B, n);
    free_matrix(C, n);

    return 0;
}