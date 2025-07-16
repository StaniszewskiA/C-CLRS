#include "../../../../include/part_1_foundations/4_divide_and_conquer/divide_and_conquer.h"

void cleanup_strassen_matrices(int** A11, int** A12, int** A21, int** A22,
                              int** B11, int** B12, int** B21, int** B22,
                              int** S1, int** S2, int** S3, int** S4, int** S5,
                              int** S6, int** S7, int** S8, int** S9, int** S10,
                              int** P1, int** P2, int** P3, int** P4, int** P5,
                              int** P6, int** P7, int newSize) {
    int** A_matrices[] = {A11, A12, A21, A22};
    int** B_matrices[] = {B11, B12, B21, B22};
    int** S_matrices[] = {S1, S2, S3, S4, S5, S6, S7, S8, S9, S10};
    int** P_matrices[] = {P1, P2, P3, P4, P5, P6, P7};

    for (int i = 0; i < 4; i++) {
        free_matrix(A_matrices[i], newSize);
        free_matrix(B_matrices[i], newSize);
    }

    for (int i = 0; i < 10; i++) {
        free_matrix(S_matrices[i], newSize);
    }

    for (int i = 0; i < 7; i++) {
        free_matrix(P_matrices[i], newSize);
    }
}

void strassen_algorithm(int** A, int** B, int** C, int size) {
    if (size == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = size / 2;
    
    int** A11 = allocate_matrix(newSize, newSize);
    int** A12 = allocate_matrix(newSize, newSize);
    int** A21 = allocate_matrix(newSize, newSize);
    int** A22 = allocate_matrix(newSize, newSize);
    int** B11 = allocate_matrix(newSize, newSize);
    int** B12 = allocate_matrix(newSize, newSize);
    int** B21 = allocate_matrix(newSize, newSize);
    int** B22 = allocate_matrix(newSize, newSize);

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

    int** S1 = allocate_matrix(newSize, newSize);
    int** S2 = allocate_matrix(newSize, newSize);
    int** S3 = allocate_matrix(newSize, newSize);
    int** S4 = allocate_matrix(newSize, newSize);
    int** S5 = allocate_matrix(newSize, newSize);
    int** S6 = allocate_matrix(newSize, newSize);
    int** S7 = allocate_matrix(newSize, newSize);
    int** S8 = allocate_matrix(newSize, newSize);
    int** S9 = allocate_matrix(newSize, newSize);
    int** S10 = allocate_matrix(newSize, newSize);
    int** P1 = allocate_matrix(newSize, newSize);
    int** P2 = allocate_matrix(newSize, newSize);
    int** P3 = allocate_matrix(newSize, newSize);
    int** P4 = allocate_matrix(newSize, newSize);
    int** P5 = allocate_matrix(newSize, newSize);
    int** P6 = allocate_matrix(newSize, newSize);
    int** P7 = allocate_matrix(newSize, newSize);

    add_matrices(B12, B22, S1, newSize, -1);   // S1 = B12 - B22
    add_matrices(A11, A12, S2, newSize, 1);    // S2 = A11 + A12
    add_matrices(A21, A22, S3, newSize, 1);    // S3 = A21 + A22
    add_matrices(B21, B11, S4, newSize, -1);   // S4 = B21 - B11
    add_matrices(A11, A22, S5, newSize, 1);    // S5 = A11 + A22
    add_matrices(B11, B22, S6, newSize, 1);    // S6 = B11 + B22
    add_matrices(A12, A22, S7, newSize, -1);   // S7 = A12 - A22
    add_matrices(B21, B22, S8, newSize, 1);    // S8 = B21 + B22
    add_matrices(A11, A21, S9, newSize, -1);   // S9 = A11 - A21
    add_matrices(B11, B12, S10, newSize, 1);   // S10 = B11 + B12

    strassen_algorithm(A11, S1, P1, newSize);    // P1 = A11 * S1
    strassen_algorithm(S2, B22, P2, newSize);    // P2 = S2 * B22
    strassen_algorithm(S3, B11, P3, newSize);    // P3 = S3 * B11
    strassen_algorithm(A22, S4, P4, newSize);    // P4 = A22 * S4
    strassen_algorithm(S5, S6, P5, newSize);     // P5 = S5 * S6
    strassen_algorithm(S7, S8, P6, newSize);     // P6 = S7 * S8
    strassen_algorithm(S9, S10, P7, newSize);    // P7 = S9 * S10

    // Combine results to form the final matrix C
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            // C11 = P5 + P4 - P2 + P6
            C[i][j] = P5[i][j] + P4[i][j] - P2[i][j] + P6[i][j];
            
            // C12 = P1 + P2
            C[i][j + newSize] = P1[i][j] + P2[i][j];
            
            // C21 = P3 + P4
            C[i + newSize][j] = P3[i][j] + P4[i][j];
            
            // C22 = P5 + P1 - P3 - P7
            C[i + newSize][j + newSize] = P5[i][j] + P1[i][j] - P3[i][j] - P7[i][j];
        }
    }

    cleanup_strassen_matrices(A11, A12, A21, A22, B11, B12, B21, B22,
                             S1, S2, S3, S4, S5, S6, S7, S8, S9, S10,
                             P1, P2, P3, P4, P5, P6, P7, newSize);
}