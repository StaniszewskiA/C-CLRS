#include "part_2_sorting_and_order_statistics/9_medians_and_order_statistics/medians_and_order_statistics.h"

int simple_min(int A[], int size) {
    int min = A[0];
    for (int i = 1; i < size; i++) {
        if (A[i] < min)
            min = A[i];
    }
    return min;
}

int simple_max(int A[], int size) {
    int max = A[0];
    for (int i = 1; i < size; i++) {
        if (A[i] > max)
            max = A[i];
    }
    return max;
}

void min_max(int A[], int size, int *min, int *max) {
    if (size == 0) return;
    int i;

    if (size % 2 == 0) {
        if (A[0] < A[1]) {
            *min = A[0];
            *max = A[1];
        } else {
            *min = A[1];
            *max = A[0];
        }
        i = 2;
    } else {
        *min = *max = A[0];
        i = 1;
    }

    for (; i < size - 1; i+= 2) {
        int localMin, localMax;

        if (A[i] < A[i + 1]) {
            localMin = A[i];
            localMax = A[i + 1];
        } else {
            localMin = A[i + 1];
            localMax = A[i];
        }

        if (localMin < * min) *min = localMin;
        if (localMax > * max) *max = localMax;
    }
}