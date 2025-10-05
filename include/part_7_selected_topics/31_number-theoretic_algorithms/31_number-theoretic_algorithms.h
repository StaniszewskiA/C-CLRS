#ifndef NUMBER_THEORETIC_ALGORITHMS_H
#define NUMBER_THEORETIC_ALGORITHMS_H

#include "../../common.h"
#include "../part_7_commons.h"

// ============================================================================
// CHAPTER 31.1: REPRESENTING POLYNOMIALS
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
// PROBLEMS
// ============================================================================


#endif 
