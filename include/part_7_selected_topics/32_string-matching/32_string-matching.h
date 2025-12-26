#ifndef STRING_MATCHING_H
#define STRING_MATCHING_H

#include "../../common.h"
#include "../part_7_commons.h"
#include "part_7_selected_topics/31_number-theoretic_algorithms/31_number-theoretic_algorithms.h"

// ============================================================================
// CHAPTER 32.1: THE NAIVE STRING-MATCHING ALGORITHM
// ============================================================================

void naive_string_matcher(char* T, char* P, int n, int m);
void test_naive_string_matcher(void);

void naive_string_matcher_distinct(char* T, char* P, int n, int m);
void test_naive_string_matcher_distinct(void);

int gap_string_matcher(const char* T, const char* P, int n, int m);
void test_gap_string_matcher(void);

// ============================================================================
// CHAPTER 32.2: THE RABIN-KARP ALGORITHM 
// ============================================================================

int rabin_karp_matcher(char* T, char* P, int n, int m, int d, int q);
void test_rabin_karp_matcher(void);

typedef struct {
    char* pattern;
    int length;
    int hash;
} PatternHash;

int rabin_karp_multi_matcher(
    char* T, 
    PatternHash* patterns, 
    int patternCnt, 
    int n, 
    int d, 
    int q
);
void test_rabin_karp_multi_matcher(void);

int rabin_karp_2d_matcher(char** T, char** P, int n, int m, int d, int q);
void test_rabin_karp_2d_matcher(void);

// ============================================================================
// CHAPTER 32.3: STRING MATCHING WITH FINITE AUTOMATA
// ============================================================================

#define ALPHABET_SIZE 256
void compute_transition_function(char* P, int m, int delta[][ALPHABET_SIZE]);
void finite_automaton_matcher(char* T, int n, char* P, int m, int delta[][ALPHABET_SIZE]);
void test_finite_automaton_matcher(void);

#define MAX_SUBS 16
#define MAX_SUB_LEN 128
void finite_automaton_gap_matcher(char* T, int m, char* P);
void test_finite_automaton_gap_matcher(void);


// ============================================================================
// CHAPTER 32.4: THE KNUTH-MORRIS-PRATT ALGORITHM
// ============================================================================

int* compute_prefix_function(const char* P, int m);
void kmp_matching(const char* T, const char* P, int n, int m);
void test_kmp_matching(void);

void concat_kmp_matching(const char* T, const char* P, int m, int n);
void test_concat_kmp_matching(void);

int* compute_prime_prefix_function(const char* P, int m, const int* pi);
void kmp_matching_prime_prefix(const char* T, const char* P, int n, int m);
void test_kmp_matching_prime_prefix(void);

bool is_cyclic_rotation(
    const char* T, 
    const char* TPrime, 
    int n, 
    int m
);
void test_is_cyclic_rotation(void);

void compute_transition_function_kmp(
    const char* P,
    int m,
    const char* Sigma,
    int sigmaSize,
    int** delta
);
void test_compute_transition_function_kmp(void);

// ============================================================================
// CHAPTER 32.5: SUFFIX TABLES
// ============================================================================



// ============================================================================
// PROBLEMS
// ============================================================================



#endif 
