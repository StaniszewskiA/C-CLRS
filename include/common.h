#ifndef COMMON_H
#define COMMON_H

// Libs
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
void print_separator(const char* title);
void print_error(const char* msg);
double get_time_ms(void);
int random_int(int min, int max);

// Debug
#ifdef DEBUG
#define DEBUG_PRINT(fmt, ...) \
    do { fprintf(stderr, "DEBUG: %s:%d:%s(): " fmt "\n", \
                __FILE__, __LINE__, __func__, ##__VA_ARGS__); } while(0)
#else
#define DEBUG_PRINT(fmt, ...) do {} while(0)
#endif

#endif // COMMON_H