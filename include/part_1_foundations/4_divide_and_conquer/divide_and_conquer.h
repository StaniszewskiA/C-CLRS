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

void cleanup_strassen_matrices(double** A11, double** A12, double** A21, double** A22,
                            double** B11, double** B12, double** B21, double** B22,
                            double** S1, double** S2, double** S3, double** S4, double** S5,
                            double** S6, double** S7, double** S8, double** S9, double** S10,
                            double** P1, double** P2, double** P3, double** P4, double** P5,
                            double** P6, double** P7, int newSize);
void strassen_algorithm(double** A, double** B, double** C, int size);

#endif // DIVIDE_AND_CONQUER_H