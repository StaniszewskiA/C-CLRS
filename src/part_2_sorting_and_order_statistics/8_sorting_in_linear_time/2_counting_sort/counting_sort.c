#include "part_2_sorting_and_order_statistics/8_sorting_in_linear_time/sorting_in_linear_time.h"

void preprocess(int A[], int n, int k, int P[]) {
    int* C = (int*)calloc(k + 1, sizeof(int));

    for (int i = 0; i < n; i++)
        C[A[i]]++;

    P[0] = C[0];
    for (int i = 1; i <= k; i++)
        P[i] = P[i - 1] + C[i];

    free(C);
}

int count_in_range(int P[], int a, int b) {
    if (a > b) return 0;
    if (a == 0) return P[b];
    return P[b] - P[a - 1];
}

void count_sort(int A[], int n) {
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

void count_sort_prim(int A[], int n, int k) {
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

void count_sort_real(double A[], int n, int d) {
    int factor = pow(10, d);
    int max_val = 0;
    int* int_A = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        int_A[i] = (int)round(A[i] * factor);
        if (int_A[i] > max_val)
            max_val = int_A[i]; 
    }

    int* C = (int*)calloc(max_val + 1, sizeof(int));

    for (int i = 0; i < n; i++)
        C[int_A[i]]++;

    for (int i = 1; i <= max_val; i++)
        C[i] += C[i - 1];

    double* output = (double*)malloc(n * sizeof(double));
    for (int i = n - 1; i >= 0; i--) {
        output[C[int_A[i]] - 1] = (double)int_A[i] / factor;
        C[int_A[i]]--;
    }

    for (int i = 0; i < n; i++)
        A[i] = output[i];

    free(C);
    free(int_A);
    free(output);
}