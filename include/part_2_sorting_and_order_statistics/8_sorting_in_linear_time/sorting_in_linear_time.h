#ifndef SORTING_IN_LINEAR_TIME_H
#define SORTING_IN_LINEAR_TIME_H

#include "../../common.h"
#include "../part_2_commons.h"

// ============================================================================
// CHAPTER 8.2: COUNTING SORT
// ============================================================================

void preprocess(int A[], int n, int k, int P[]);
int count_in_range(int P[], int a, int b);

void count_sort(int A[], int n);
void count_sort_prim(int A[], int n, int k);

void count_sort_real(double A[], int n, int d);

// ============================================================================
// CHAPTER 8.3: RADIX SORT
// ============================================================================

#define MAX_LEN 100  
#define ALPHABET_SIZE 256

void count_sort2(
    char src[][MAX_LEN], 
    char dest[][MAX_LEN],
    int n,
    int idx
);
void radix_sort(int A[][MAX_BASE_DIGITS], int n, int base);
void radix_sort_char(char A[][MAX_LEN], int n);

// ============================================================================
// CHAPTER 8.3: BUCKET SORT
// ============================================================================

#define NBUCKET 6

struct Node {
    float data;
    struct Node *next;
};

void bucket_sort(float A[]);
struct Node* insertion_sort(struct Node *list);
void print_buckets(struct Node* list);
int get_bucket_idx(float value);
void free_buckets(struct Node** buckets);

// ============================================================================
// PROBLEMS
// ============================================================================

#define MAX_DIGITS 10
#define ALPHABET_SIZE_2 26
#define MAX_WORDS 1000
#define MAX_LENGTH 50

void ex2a(int A[], int n, int C[]);
void ex2b(int A[], int n);
void ex2e(int A[], int n);
void radix_sort2(int A[], int n);
void ex3a(int A[], int n);

#endif // SORTING_IN_LINEAR_TIME_H