#ifndef NP_COMPLETENESS_H
#define NP_COMPLETENESS_H

#include "../../common.h"
#include "../part_7_commons.h"

// ============================================================================
// CHAPTER 34.1: Polynomial time
// ============================================================================

#define ENC_N_VERTICES 8

char* convert_matrix_to_lists(const char* x);
char* convert_lists_to_matrix(const char* y);
void test_encoding_conversion(void);


// ============================================================================
// CHAPTER 34.2: Polynomial-time verification
// ============================================================================

#define GI_N_VERTICES 4

int verify_graph_isomorphism(
    const int* adjMat1,
    int n1,
    const int* adjMat2,
    int n2,
    const int* f
);
void test_verify_graph_isomorphism(void);

#define HC_MAX_VERTICES 10

typedef int (*HamCycleDecider)(const int* adjMat, int n);

int ham_cycle(const int* adjMat, int n);
int ham_cycle_order(
    HamCycleDecider decide,
    const int* adjMat,
    int n,
    int* order,
    int* calls
);
void test_ham_cycle_order(void);

#define DS_MAX_CERTIFICATE 32

typedef int (*Verifier)(const char* x, const char* y);
typedef int (*CertificateBound)(int n);

int decide_by_search(
    Verifier verify,
    CertificateBound p,
    const char* x,
    char* certificate,
    long long* checked
);
void test_decide_by_search(void);

int ham_path(
    const int* adjMat,
    int n,
    int u,
    int v,
    int* path
);
void test_ham_path(void);

int ham_path_dag(
    const int* adjMat,
    int n,
    int u,
    int v,
    int* path
);
void test_ham_path_dag(void);

int verify_not_tautology(
    const char* x,
    const char* y
);
void test_verify_not_tautology(void);


// ============================================================================
// CHAPTER 34.3: NP-completeness and reducibility
// ============================================================================



// ============================================================================
// CHAPTER 34.4: NP-completeness proofs
// ============================================================================



// ============================================================================
// CHAPTER 34.5: NP-complete problems
// ============================================================================



// ============================================================================
// PROBLEMS
// ============================================================================

#endif
