#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

#include "../../common.h"
#include "../part_7_commons.h"

// ============================================================================
// CHAPTER 28.1: SOLVING SYSTEMS OF LINEAR EQUATIONS
// ============================================================================

void lu_decomposition(double** A, double** L, double** U, int n);
void forward_substitution(double** L, double* y, double* b, int n);
void backward_substitution(double** U, double* x, double* y, int n);
void lu_solve(double** A, double* x, double* b, int n);
void extract_lu_from_lup(double** A, double** L, double** U, int n);
void test_lu_decomposition(void);

int lup_decomposition(double** A, int* pi, int n);
void lup_solve(double** A, double* x, double* b, int n);
void test_lup_decomposition(void);

// ============================================================================
// CHAPTER 28.2: INVERTING MATRICES
// ============================================================================

void lup_invert_matrix(double** A, double** invA, int n);
void test_matrix_inversion(void);

void conjugate_transpose(complex double** A, complex double** B, int n);
void multiply_matrix_complex(
    complex double** A, 
    complex double** B, 
    complex double** C, 
    int n
);
void forward_substitution_complex(
    complex double** L, 
    complex double* y, 
    complex double* b, 
    int n
);
void backward_substitution_complex(
    complex double** U, 
    complex double* x,
    complex double* y,
    int n
);
int lup_decomposition_complex(complex double** A, int* pi, int n);
void extract_lu_from_lup_complex(
    complex double** A, 
    complex double** L, 
    complex double** U, 
    int n
);
void lup_invert_matrix_complex(
    complex double** A,
    complex double** invA,
    int n
);
void test_complex_matrix_inversion(void);

// ============================================================================
// CHAPTER 28.3: SYMMETRIC POSITIVE-DEFINITE MATRICES AND LEAST-SQUARES
//               APPROXIMATION
// ============================================================================

void compute_pseudoinverse(double** A, double** Ap, int rows, int cols);
void polynomial_least_squares_pseudoinverse(
    const double* x, 
    const double* y, 
    int n, 
    int degree, 
    double* coeffs
);
void test_polynomial_least_squares_pseudoinverse(void);

// ============================================================================
// PROBLEMS
// ============================================================================

void solve_tridiagonal(
    int n, 
    double* a, 
    double* b, 
    double* c, 
    double* d, 
    double* x
);
void cubic_spline(int n, double* x, double* y, double* D);
double eval_cubic_spline(
    double x0,
    double x1,
    double y0,
    double y1,
    double D0,
    double D1,
    double x
);
void test_cubic_spline(void);

#endif 
