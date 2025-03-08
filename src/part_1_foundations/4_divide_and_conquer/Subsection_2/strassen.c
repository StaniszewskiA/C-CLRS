#include <stdio.h>
#include <stdlib.h>
#include "strassen.h"

#define MAX 64

double** allocate_matrix(int size) {
    double** matrix = (double**)malloc(size * sizeof(double*));
    for (int i = 0; i < size; i++) {
        matrix[i] = (double*)malloc(size * sizeof(double));
    }
    return matrix;
}

void input_matrix(double** matrix, int size, const char* name) {
    printf("Enter elements of matrix %s:\n", name);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            scanf("%lf", &matrix[i][j]);
        }
    }
}

void free_matrix(double** matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void add_matrices(double** A, double** B, double** C, int size, int multiplier) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = A[i][j] + multiplier* B[i][j];
        }
    }
}

void strassen(double** A, double** B, double** C, int size) {
    if (size == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = size / 2;
    double** A11 = allocate_matrix(newSize);
    double** A12 = allocate_matrix(newSize);
    double** A21 = allocate_matrix(newSize);
    double** A22 = allocate_matrix(newSize);
    double** B11 = allocate_matrix(newSize);
    double** B12 = allocate_matrix(newSize);
    double** B21 = allocate_matrix(newSize);
    double** B22 = allocate_matrix(newSize);

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    double** S1 = allocate_matrix(newSize);
    double** S2 = allocate_matrix(newSize);
    double** S3 = allocate_matrix(newSize);
    double** S4 = allocate_matrix(newSize);
    double** S5 = allocate_matrix(newSize);
    double** S6 = allocate_matrix(newSize);
    double** S7 = allocate_matrix(newSize);
    double** S8 = allocate_matrix(newSize);
    double** S9 = allocate_matrix(newSize);
    double** S10 = allocate_matrix(newSize);
    double** P1 = allocate_matrix(newSize);
    double** P2 = allocate_matrix(newSize);
    double** P3 = allocate_matrix(newSize);
    double** P4 = allocate_matrix(newSize);
    double** P5 = allocate_matrix(newSize);
    double** P6 = allocate_matrix(newSize);
    double** P7 = allocate_matrix(newSize);

    // S1 = B12 - B22
    add_matrices(B12, B22, S1, newSize, -1);
    // S2 = A11 + A12
    add_matrices(A11, A12, S2, newSize, 1);
    // S3 = A21 + A22
    add_matrices(A21, A22, S3, newSize, 1);
    // S4 = B21 + B11
    add_matrices(B21, B11, S4, newSize, -1);
    // S5 = A11 + A22
    add_matrices(A11, A22, S5, newSize, 1);
    // S6 = B11 + B22
    add_matrices(B11, B22, S6, newSize, 1);
    // S7 = A12 - A22
    add_matrices(A12, A22, S7, newSize, -1);
    // S8 = B21 + B22
    add_matrices(B21, B22, S8, newSize, 1);
    // S9 = A11 - A21
    add_matrices(A11, A21, S9, newSize, -1);
    // S10 = B11 + B11
    add_matrices(B11, B11, S10, newSize, 1);

    // P1 = A11 * S1
    strassen(A11, S1, P1, newSize);
    // P2 = S2 * B22
    strassen(S2, B22, P2, newSize);
    // P3 = S3 * B11
    strassen(S3, B11, P3, newSize);
    // P4 = A22 * S4
    strassen(A22, S4, P4, newSize);
    // P5 = S5 * S6
    strassen(S5, S6, P5, newSize);
    // P6 = S7 * S8
    strassen(S7, S8, P6, newSize);
    // P7 = S9 * S10
    strassen(S9, S10, P7, newSize);

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = P1[i][j] + P4[i][j] - P5[i][j] + P6[i][j]; // C11
            C[i][j + newSize] = P2[i][j] + P4[i][j]; // C12
            C[i + newSize][j] = P3[i][j] + P5[i][j]; // C21
            C[i + newSize][j + newSize] = P1[i][j] - P2[i][j] + P3[i][j] + P4[i][j]; // C22
        }
    }

    free_matrix(A11, newSize);
    free_matrix(A12, newSize);
    free_matrix(A21, newSize);
    free_matrix(A22, newSize);
    free_matrix(B11, newSize);
    free_matrix(B12, newSize);
    free_matrix(B21, newSize);
    free_matrix(B22, newSize);
    free_matrix(S1, newSize);
    free_matrix(S2, newSize);
    free_matrix(S3, newSize);
    free_matrix(S4, newSize);
    free_matrix(S5, newSize);
    free_matrix(S6, newSize);
    free_matrix(S7, newSize);
    free_matrix(S8, newSize);
    free_matrix(S9, newSize);
    free_matrix(S10, newSize);
    free_matrix(P1, newSize);
    free_matrix(P2, newSize);
    free_matrix(P3, newSize);
    free_matrix(P4, newSize);
    free_matrix(P5, newSize);
    free_matrix(P6, newSize);
    free_matrix(P7, newSize);
}

void print_matrix(double** matrix, int size, const char* name) {
    printf("Matrix %s:\n", name);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%lf ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n;
    printf("Enter the size of the matrices (must be a power of 2): ");
    scanf("%d", &n);

    double** A = allocate_matrix(n);
    double** B = allocate_matrix(n);
    double** C = allocate_matrix(n);

    input_matrix(A, n, "A");
    print_matrix(A, n, "A");

    input_matrix(B, n, "B");
    print_matrix(B, n, "B");

    strassen(A, B, C, n);
    print_matrix(C, n, "C");
}