#ifndef MULTITHREADED_ALGORITHMS_H
#define MULTITHREADED_ALGORITHMS_H

#include "../../common.h"
#include "../part_7_commons.h"
#include "part_1_foundations/part_1_commons.h" // Sorting utils
#include "part_2_sorting_and_order_statistics/7_quicksort/quicksort.h" // Quicksort

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

void p_matrix_multiply(int** A, int** B, int** C, int n);
void s_matrix_multiply(int** A, int** B, int** C, int n);
int verify_matrix_multiplication(int** A, int** B, int n);
void test_p_matrix_multiply(void);

void p_matrix_multiply_recursive(int** A, int** B, int** C, int n);
void test_p_matrix_multiply_recursive(void);

void p_strassen_algorithm(int** A, int** B, int** C, int n);
void test_p_strassen_algorithm(void);

void test_all_matrix_multiplication_methods(void);

void p_fast_matrix_multiply(int** A, int** B, int** C, int n);
void test_p_fast_matrix_multiply(void);

void p_fast_matrix_multiply_optimized(int** A, int** B, int** C, int n);
void test_p_fast_matrix_multiply_optimized(void);

void p_gen_matrix_multiply(int** A, int** B, int** C, int p, int q, int r);
void test_p_get_matrix_multiply(void);

void p_floyd_warshall(int** w, int** D, int n);
void test_p_floyd_warshall(void);

// ============================================================================
// CHAPTER 26.3: MULTITHREADED MERGE SORT
// ============================================================================

void p_naive_merge_sort(int* A, int p, int r);
void p_merge_sort(int* A, int p, int q, int r);
void test_p_merge_sort(void);

typedef struct {
    int pos;
    int arr;
} median_res_t;

void p_median_merge(int* T,
    int p1,
    int r1,
    int p2,
    int r2,
    int* A,
    int p3
);
void test_p_median_merge(void);

typedef struct {
    int lessCnt;
    int greaterCnt;
    int equalCnt;
} partition_cnts_t;

typedef struct {
    int lessStart;
    int equalStart;
    int greaterStart;
} partition_positions_t;

void p_partition(int* A, int n, int* res, int pivot, int* pivotIdx);
void test_p_partition(void);

void p_recursive_fft(complex_t* a, int n, complex_t* res);
void test_p_recursive_fft(void);

// ============================================================================
// PROBLEMS
// ============================================================================

#endif 
