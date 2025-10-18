#ifndef NUMBER_THEORETIC_ALGORITHMS_H
#define NUMBER_THEORETIC_ALGORITHMS_H

#include "../../common.h"
#include "../part_7_commons.h"

// ============================================================================
// CHAPTER 31.1: ELEMENTARY NUMBER-THEORET NOTIONS
// ============================================================================

int is_perfect_kth_power(uint64_t n, uint64_t k, uint64_t* root);
void test_is_perfect_kth_power(void);

void long_division(
    uint64_t n,
    uint64_t d,
    uint64_t* quotient,
    uint64_t* remainder 
);
void test_long_division(void);

uint64_t bin_to_dec(const char* bin, int len, const uint64_t* powers);
void test_bin_to_dec(void);

void print_on_bulbs(int n);
void test_print_on_bulbs(void);

// ============================================================================
// CHAPTER 31.2: GREATEST COMMON DIVISOR
// ============================================================================

uint64_t euclid_gcd(uint64_t a, uint64_t b);
void test_euclid_gcd(void);

uint64_t extended_euclid_gcd(uint64_t a, uint64_t b, int64_t* x, int64_t* y);
void test_extended_euclid_gcd(void);

uint64_t euclid_gcd_recursive(uint64_t a, uint64_t b);
void test_euclid_gcd_recursive(void);

void extended_euclid_gcd_multiple(
    const int64_t* a, 
    int n, 
    int64_t* g, 
    int64_t* xs
);
void test_extended_euclid_gcd_multiple(void);

uint64_t lcm(uint64_t a, uint64_t b);
void test_lcm(void);

uint64_t lcm_multiple(const int64_t* a, int n);
void test_lcm_multiple(void);

// ============================================================================
// CHAPTER 31.4: SOLVING MODULAR LINEAR EQUATIONS
// ============================================================================

void modular_linear_equation_solver(int a, int b, int n);
void test_modular_linear_equation_solver(void);

void modular_linear_equation_solver_modified(int a, int b, int n);
void test_modular_linear_equation_solver_modified(void);

// ============================================================================
// PROBLEMS
// ============================================================================


#endif 
