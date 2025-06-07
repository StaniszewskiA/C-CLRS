#ifndef COMMON_H
#define COMMON_H

// Libs
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include <float.h>

// Constants
#define MAX_SIZE 1000
#define MAX_VALUE 10000
#define MIX_VALUE -10000
#define INF INT_MAX
#define NEG_INF INT_MIN

// Macros
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ABS(x) ((x) < 0 ? -(x) : x)
#define SWAP(a, b, temp) do { temp = a; a = b; b = temp; } while(0)
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr)[0])

// Color flags
#define RED 0
#define BLACK 1

// Error codes
typedef enum {
    SUCCESS = 0,
    ERROR_NULL_POINTER = -1,
    ERROR_OUT_OF_MEMORY = -2,
    ERROR_INVALID_INPUT = -3,
    ERROR_INDEX_OUT_OF_BOUND = -4,
    ERROR_EMPTY_STRUCTURE = -5,
    ERROR_FULL_STORAGE = -6,
} error_code_t;

// Comparisons
typedef int (*compare_func_t)(const void* a, const void* b);

// Memory allocation
void* safe_malloc(size_t size);
void* safe_calloc(size_t num, size_t size);
void* safe_realloc(void* ptr, size_t size);
void safe_free(void* ptr);

// Other

#define NARRAY 10

void print_separator(const char* title);
void print_error(const char* msg);
double get_time_ms(void);
int random_int(int min, int max);
void print_arr(int arr[], int size);
void print_arr_slice(int arr[], int left, int right);
void print_arr_double(double arr[], int size);
void print_arr_float(float A[]);

// Matrix utils

#define MAX_MATRIX_SIZE 100

void print_matrix(int matrix[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE], int n);
double** allocate_matrix(int size);
void input_matrix(double** matrix, int size, const char* name);
void free_matrix(double** matrix, int size);
void add_matrices(
    double** A, 
    double** B, 
    double** C, 
    int size, 
    int multiplier
);

// Intervals
typedef struct {
    int low;
    int high;
} Interval;

void interval_swap(Interval *a, Interval *b );
void print_intervals(Interval A[], int size);

// System conversions
#define MAX_BASE_DIGITS 3

void convert_to_base_n(
    int A[],
    int n,
    int base,
    int converted[][MAX_BASE_DIGITS]
);
void convert_back_from_base_n(
    int converted[][MAX_BASE_DIGITS], 
    int n, 
    int base, 
    int A[]
);

// Array utils
int find_max(int A[], int n);

// Counting
int count_digits(int num);

// Debug
#ifdef DEBUG
#define DEBUG_PRINT(fmt, ...) \
    do { fprintf(stderr, "DEBUG: %s:%d:%s(): " fmt "\n", \
                __FILE__, __LINE__, __func__, ##__VA_ARGS__); } while(0)
#else
#define DEBUG_PRINT(fmt, ...) do {} while(0)
#endif

#endif // COMMON_H