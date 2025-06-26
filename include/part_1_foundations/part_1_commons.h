#ifndef PART_1_COMMONS_H
#define PART_1_COMMONS_H

#include "../common.h"

// ============================================================================
// PART 1 FOUNDATIONS - COMMON UTILITIES
// ============================================================================

// Array validation functions
int is_sorted_asc(const int arr[], int size);
int is_sorted_desc(const int arr[], int size);

// Array manipulation functions
void copy_arr(const int source[], int dest[], int size);
void reverse_arr(int* arr, int len);

// Mathematical functions
int sum_arr(int arr[], int size);

// Search functions
int linear_search(int* arr, int n, int target);

// Binary operations
int* add_binary_numbers(const int* A, int lenA, const int* B, int lenB, int* resultLen);
void remove_leading_zeros(int* arr, int* len);
void print_binary_arr(const int* arr, int len);

#endif // PART_1_COMMONS_H