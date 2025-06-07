#include "../../include/part_1_foundations/part_1_commons.h"

int is_sorted_asc(const int arr[], int size) {
    for (int i = 1; i < size; i++) 
        if (arr[i] < arr[i - 1]) return 0; 
        
    return 1; 
}

int is_sorted_desc(const int arr[], int size) {
    for (int i = 1; i < size; i++) 
        if (arr[i] > arr[i - 1]) return 0;
        
    return 1; 
}

void copy_arr(const int source[], int dest[], int size) {
    for (int i = 0; i < size; i++) dest[i] = source[i];
}

void reverse_arr(int* arr, int len) {
    int start = 0;
    int end = len - 1;
    while (start < end) {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

int sum_arr(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) sum += arr[i];
    
    return sum;
}

int linear_search(int *arr, int n, int target) {
    for (int i = 0; i < n; i++) 
        if (arr[i] == target) return i;

    return -1;
}

int* add_binary_numbers(
    const int* A, 
    int lenA, 
    const int* B, 
    int lenB, 
    int* resultLen
) {
    int maxLen = (lenA > lenB) ? lenA : lenB;
    int* result = (int*)malloc((maxLen + 1) * sizeof(int));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        *resultLen = 0;
        return NULL;
    }

    int carry = 0;

    for (int i = 0; i < maxLen; i++) {
        int bitA = (i < lenA) ? A[lenA - 1 - i] : 0; 
        int bitB = (i < lenB) ? B[lenB - 1 - i] : 0;

        int sum = bitA + bitB + carry;
        result[i] = sum % 2;
        carry = sum / 2;
    }

    if (carry) {
        result[maxLen] = carry;
        *resultLen = maxLen + 1;
    } else {
        *resultLen = maxLen;
    }

    reverse_arr(result, *resultLen);
    remove_leading_zeros(result, resultLen);

    return result;
}

void remove_leading_zeros(int* arr, int* len) {
    int startIndex = 0;
    while (startIndex < *len - 1 && arr[startIndex] == 0) 
        startIndex++;

    *len -= startIndex;

    if (*len > 0) memmove(arr, arr + startIndex, *len * sizeof(int));
}

void print_binary_arr(const int* arr, int len) {
    if (arr == NULL || len <= 0) {
        printf("(empty binary array)\n");
        return;
    }
    
    for (int i = 0; i < len; i++) printf("%d", arr[i]);
    printf("\n");
}