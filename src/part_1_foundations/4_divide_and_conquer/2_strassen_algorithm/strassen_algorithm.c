#include "../../../../include/part_1_foundations/4_divide_and_conquer/divide_and_conquer.h"

void cleanup_strassen_matrices(double** A11, double** A12, double** A21, double** A22,
                              double** B11, double** B12, double** B21, double** B22,
                              double** S1, double** S2, double** S3, double** S4, double** S5,
                              double** S6, double** S7, double** S8, double** S9, double** S10,
                              double** P1, double** P2, double** P3, double** P4, double** P5,
                              double** P6, double** P7, int newSize) {
    double** A_matrices[] = {A11, A12, A21, A22};
    double** B_matrices[] = {B11, B12, B21, B22};
    double** S_matrices[] = {S1, S2, S3, S4, S5, S6, S7, S8, S9, S10};
    double** P_matrices[] = {P1, P2, P3, P4, P5, P6, P7};

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

void strassen_algorithm(double** A, double** B, double** C, int size) {
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