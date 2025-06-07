#include "part_2_sorting_and_order_statistics/7_quicksort/quicksort.h"

void swap4(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int A[], int p, int r) {
    int x = A[r];
    int i = p - 1;

    for (int j = p; j < r; j++) {
        if (A[j] <= x) {
                        i++;
            swap4(&A[i], &A[j]);
        }
    swap4(&A[i + 1], &A[r]);
    }

    printf("Value at pivot idx: %d\n", x);
    return (i + 1);
}

void quicksort(int A[], int p, int r) {
    if (p < r) {
        int q = partition(A, p, r);
        quicksort(A, p, q - 1);
        quicksort(A, q + 1, r);
    }
}