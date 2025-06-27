#ifndef MULTITHREADED_ALGORITHMS_H
#define MULTITHREADED_ALGORITHMS_H

#include "../../common.h"
#include "../part_7_commons.h"

#include <pthread.h>
#include <omp.h>

/*
    Note that these could be vastly improved with a proper thread pool.
    Fibonacci is implemented in a suboptimal way on purpose.
*/

#define THREAD_LIMIT 16

// ============================================================================
// CHAPTER 26.1: THE BASICS OF FORK-JOIN MULTITHREADING
// ============================================================================

#define SEQ_THRESHOLD 10

typedef struct {
    int n;
    int res;
} fib_args_t;

int try_spawn_thread();
void release_thread_slot();
void* p_fib_thread(void* arg);
int p_fib(int n);
void test_p_fib(void);

void p_mat_vec(int** a, int* x, int* y, int n);
void test_p_mat_vec(void);

void p_mat_vec_recursive(int** A, int* x, int* y, int n, int i, int iPrime);
void test_p_mat_vec_recursive(void);

void race_example(void);
void test_race_example(void);

void p_mat_vec_wrong(int** A, int* x, int* y, int n);
void test_p_mat_vec_wrong(void);

int sum_row_dc(int* row, int* x, int left, int right);
void p_mat_vec_dc(int** A, int* x, int* y, int n);
void test_p_mat_vec_dc(void);

void p_transpose(int** A, int n);
void test_p_transpose(void);

// ============================================================================
// CHAPTER 26.2: MULTITHREADED MATRIX MULTIPLICATION
// ============================================================================

// ============================================================================
// CHAPTER 26.3: MULTITHREADED MERGE SORT
// ============================================================================

// ============================================================================
// PROBLEMS
// ============================================================================

#endif 
