#ifndef GETTING_STARTED_H
#define GETTING_STARTED_H

#include "../../common.h"

// ============================================================================
// CHAPTER 2.1: INSERTION SORT
// ============================================================================

void insertion_sort(int arr[], int N);
void insertion_sort_desc(int arr[], int N);
void insertion_sort_step_by_step(int arr[], int N);
void recursive_insertion_sort(int arr[], int n);

int is_sorted_asc(const int arr[], int size);
int is_sorted_desc(const int arr[], int size);

int linear_search(int* arr, int n, int target);

int sum_arr(int arr[], int size);

int* add_binary_numbers(
    const int* A, 
    int lenA, 
    const int* B, 
    int lenB, 
    int* resultLen
);
void remove_leading_zeros(int* arr, int* len);
void reverse_arr(int* arr, int len);
void print_binary_arr(const int* arr, int len);

// ============================================================================
// CHAPTER 2.2: ANALYZING ALGORITHMS
// ============================================================================

#define MAX_TERMS 100

typedef struct {
    int coefficient;
    int exponent;
} Term;

int find_highest_degree(const char *polynomial);
void determine_big_o(int maxExponent);

void swap(int *x, int *y);
void selection_sort(int arr[], int n);

#endif // GETTING_STARTED_H