#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

#include "../../common.h"
#include "../part_7_commons.h"

// ============================================================================
// CHAPTER 28.1: SOLVING SYSTEMS OF LINEAR EQUATIONS
// ============================================================================

void lu_decomposition(double** A, double** L, double** U, int n);
void lu_solve(double** A, double* x, double* b, int n);
void test_lu_decomposition(void);

int lup_decomposition(double** A, int* pi, int n);
void lup_solve(double** A, double* x, double* b, int n);
void test_lup_decomposition(void);

// ============================================================================
// CHAPTER 28.2: INVERTING MATRICS
// ============================================================================



// ============================================================================
// CHAPTER 28.3: SYMMETRIC POSITIVE-DEFINITE MATRICES AND LEST-SQUARES
//               APPROXIMATION
// ============================================================================



// ============================================================================
// PROBLEMS
// ============================================================================



#endif 
