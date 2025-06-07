#include "part_2_sorting_and_order_statistics/9_medians_and_order_statistics/medians_and_order_statistics.h"

void swap5(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int A[], int p, int r) {
    int pivot = A[r];
    int i = p - 1;

    for (int j = p; j < r; j++) {
        if (A[j] < pivot) {
            i++;
            swap5(&A[i], &A[j]);
        }
    }
    swap5(&A[i + 1], &A[r]);
    return i + 1;
}

int randomized_partition(int A[], int p, int r) {
    int random_index = p + rand() % (r - p + 1);
    swap5(&A[random_index], &A[r]);  
    return partition(A, p, r);
}

int randomized_select(int A[], int p, int r, int i) {
    if (p == r) return A[p];

    int q = randomized_partition(A, p, r);
    int k = q - p + 1;

    if (i == k) return A[q];
    else if (i < k) return randomized_select(A, p, q - 1, i);
    else return randomized_select(A, q + 1, r, i - k);
}

int randomized_select_iter(int A[], int p, int r, int i) {
    while (p <= r) {
        int q = randomized_partition(A, p, r);
        int k = q - p + 1;
        if (i == k) return A[q];
        else if (i < k)  r = q - 1;
        else {
            p = q + 1;
            i = i - k;
        }
    }
    return -1;
}