#ifndef DIVIDE_AND_CONQUER_H
#define DIVIDE_AND_CONQUER_H

#include "../../common.h"
#include "../part_1_commons.h"

// ============================================================================
// CHAPTER 4.1: SQUARE MATRIX MULTIPLICATION
// ============================================================================

#define MAX_MATRIX_SIZE 100

void matrix_add_recursive(
    int A[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE], 
    int B[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE], 
    int C[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE], 
    int n
);

// ============================================================================
// CHAPTER 4.2: STRASSEN ALGORITHM
// ============================================================================

void cleanup_strassen_matrices(int** A11, int** A12, int** A21, int** A22,
                            int** B11, int** B12, int** B21, int** B22,
                            int** S1, int** S2, int** S3, int** S4, int** S5,
                            int** S6, int** S7, int** S8, int** S9, int** S10,
                            int** P1, int** P2, int** P3, int** P4, int** P5,
                            int** P6, int** P7, int newSize);
void strassen_algorithm(int** A, int** B, int** C, int size);

#endif // DIVIDE_AND_CONQUER_H