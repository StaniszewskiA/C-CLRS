#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_DIGITS 3

void convert_to_base_n(
    int A[],
    int n,
    int base,
    int converted[][MAX_DIGITS]
) {
    for (int i = 0; i < n; i++) {
        int num = A[i];
        for (int j = MAX_DIGITS - 1; j >= 0; j--) {
            converted[i][j] = num % base;
            num /= base;
        }
    }
}

void convert_back_from_base_n(
    int converted[][MAX_DIGITS], 
    int n, 
    int base, 
    int A[]
) {
    for (int i = 0; i < n; i++) {
        int num = 0;
        for (int j = 0; j < MAX_DIGITS; j++) {
            num = num * base + converted[i][j];
        }
        A[i] = num;
    }
}

void count_sort(
    int A[][MAX_DIGITS],
    int n,
    int idx,
    int base
) {
    int output[n][MAX_DIGITS];
    int count[base];

    for (int i = 0; i < base; i++) count[i] = 0;
    for (int i = 0; i < n; i++) count[A[i][idx]]++;
    for (int i = 1; i < base; i++) count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        int pos = --count[A[i][idx]];
        for (int j = 0; j < MAX_DIGITS; j++) {
            output[pos][j] = A[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < MAX_DIGITS; j++)
            A[i][j] = output[i][j]; 
    }
}

void radix_sort(
    int A[][MAX_DIGITS],
    int n,
    int base
) {
    for (int idx = MAX_DIGITS - 1; idx >= 0; idx--)
        count_sort(A, n, idx, base);
}

void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {12, 4, 15, 8, 3, 10, 6, 14, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int base = n;
    
    int converted[n][MAX_DIGITS];
    convert_to_base_n(arr, n, base, converted);
    
    radix_sort(converted, n, base);
    
    convert_back_from_base_n(converted, n, base, arr); 
    
    printf("Sorted array: ");
    print_array(arr, n);
    
    return 0;
}