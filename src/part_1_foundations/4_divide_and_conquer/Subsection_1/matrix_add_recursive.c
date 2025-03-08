#include "matrix_add_recursive.h"

void matrix_add_recursive(int A[100][100], int B[100][100], int C[100][100], int n) {
    if (n == 1) {
        C[0][0] = C[0][0] + A[0][0] + B[0][0];
        return; 
    }

    int half = n / 2;
    int A11[50][50], A12[50][50], A21[50][50], A22[50][50];
    int B11[50][50], B12[50][50], B21[50][50], B22[50][50];
    int C11[50][50], C12[50][50], C21[50][50], C22[50][50];

    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + half];
            A21[i][j] = A[i + half][j];
            A22[i][j] = A[i + half][j + half];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + half];
            B21[i][j] = B[i + half][j];
            B22[i][j] = B[i + half][j + half];

            C11[i][j] = C[i][j];
            C12[i][j] = C[i][j + half];
            C21[i][j] = C[i + half][j];
            C22[i][j] = C[i + half][j + half];
        }
    }

    matrix_add_recursive(&A[0][0], &B[0][0], &C[0][0], half);
    matrix_add_recursive(&A[0][half], &B[0][half], &C[0][half], half);
    matrix_add_recursive(&A[half][0], &B[half][0], &C[half][0], half);
    matrix_add_recursive(&A[half][half], &B[half][half], &C[half][half], half);
}

void print_matrix(int matrix[100][100], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n = 4;

    int A[100][100] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    int B[100][100] = {
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 1}
    };

    int C[100][100] = {0};

    matrix_add_recursive(A, B, C, n);

    printf("Result matrix: \n");
    print_matrix(C, n);

    return 0;
}