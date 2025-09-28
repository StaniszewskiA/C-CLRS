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



#endif 
