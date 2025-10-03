#ifndef POLYNOMIALS_AND_THE_FFT_H
#define POLYNOMIALS_AND_THE_FFT_H

#include "../../common.h"
#include "../part_7_commons.h"

// ============================================================================
// CHAPTER 30.1: REPRESENTING POLYNOMIALS
// ============================================================================

void naive_polynomial_multiply(
    const double* a,
    int n,
    const double* b,
    int m,
    double* c
);
void test_naive_polynomial_multiply(void);

// ============================================================================
// CHAPTER 30.2: THE DFT AND FFT
// ============================================================================

void fft(const complex double* a, complex double* y, int n, int invert);
void test_fft(void);
void fft_radix3(const complex double* a, complex double* y, int n, int invert);
void test_fft_radix3(void);
void z_transform(
    const double* a, 
    int n, 
    complex double* z, 
    int m, 
    complex double* y
);
void test_z_transform(void);

// ============================================================================
// CHAPTER 30.3: EFFICIENT FFT IMPLEMENTATIONS
// ============================================================================

int bit_reverse(int k, int b);
void bit_reverse_permutation(complex double* a, int n);
void test_bit_reverse_permutation(void);

// ============================================================================
// PROBLEMS
// ============================================================================

void multiply_deq1_polynomials(
    const double a,
    const double b,
    const double c,
    const double d,
    double* res
);
void test_multiply_deq1_polynomials(void);
void multiply_polynomials_hili(
    const double* a1,
    const double* a2,
    int n,
    double* res
);
void test_multiply_polynomials_hili(void);
void multiply_polynomials_oiei(
    const double* a1,
    const double* a2,
    int n,
    double* res
);
void test_multiply_polynomials_oiei(void);
uint karatsuba(uint x, uint y);
void test_karatsuba(void);

void dft_1d(complex double* x, int n);
void dft_along_axis(
    complex double* data,
    const int* dims,
    int d,
    int axis
);
void dfs_nd_iterative(complex double* data, const int* dims, int d);
void test_dft_nd_iterative(void);

void compute_derivatives_fft(
    const double* a, 
    int n, 
    double x0, 
    double* derivatives
);
void test_compute_derivatives_fft(void);

void multipoint_eval(
    const double* a,
    int deg,
    const double* x,
    int leftIdx,
    int rightIdx,
    double* res
);
void test_multipoint_eval(void);

#endif 
