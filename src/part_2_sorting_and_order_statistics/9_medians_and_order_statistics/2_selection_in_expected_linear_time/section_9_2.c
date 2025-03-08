#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
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
            swap(&A[i], &A[j]);
        }
    }
    swap(&A[i + 1], &A[r]);
    return i + 1;
}

int randomized_partition(int A[], int p, int r) {
    int random_index = p + rand() % (r - p + 1);
    swap(&A[random_index], &A[r]);  
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

int main(void) {
    srand(time(NULL));

    int A[] = {12, 3, 5, 7, 19, 26, 4, 2};
    int n = sizeof(A) / sizeof(A[0]);
    int i = 1; 

    int result = randomized_select_iter(A, 0, n - 1, i);
    printf("The %d-th smallest element is %d\n", i, result);

    return 0;
}