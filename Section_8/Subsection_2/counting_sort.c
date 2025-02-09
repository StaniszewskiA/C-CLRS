#include <stdio.h>
#include <stdlib.h>

void count_sort(
    int A[],
    int n
) {
    int M = 0;
    for (int i = 0; i < n; i++)
        if (A[i] > M)
            M = A[i];

    int* C = (int*)calloc(M + 1, sizeof(int));

    for (int i = 0; i < n; i++)
        C[A[i]]++;

    for (int i = 1; i <= M; i++)
        C[i] += C[i - 1];

    int* B = (int*)malloc(n * sizeof(int));
    for (int i = n - 1; i >= 0; i--) {
        B[C[A[i]] - 1] = A[i];
        C[A[i]]--;
    }

    for (int i = 0; i < n; i++)
        A[i] = B[i];

    free(C);
    free(B);
}

void count_sort_prim(
    int A[],
    int n,
    int k
) {
    int* C = (int*)calloc(k + 1, sizeof(int));

    for (int i = 0; i < n; i++)
        C[A[i]]++;

    int idx = 0;
    for (int i = 0; i <= k; i++) {
        while (C[i] > 0) {
            A[idx++] = i;
            C[i]--;
        }
    }

    free(C);
}

void print_arr(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int A[] = {6, 0, 2, 0, 1, 3, 4, 6, 1, 3, 2};
    int N = sizeof(A) / sizeof(A[0]);
    int K = 6;

    count_sort_prim(A, N, K);

    print_arr(A, N);

    return 0;
}