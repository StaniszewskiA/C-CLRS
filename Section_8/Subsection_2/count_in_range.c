#include <stdio.h>
#include <stdlib.h>

void preprocess(
    int A[],
    int n,
    int k,
    int P[]
) {
    int* C = (int*)calloc(k + 1, sizeof(int));

    for (int i = 0; i < n; i++)
        C[A[i]]++;

    P[0] = C[0];
    for (int i = 1; i <= k; i++)
        P[i] = P[i - 1] + C[i];

    free(C);
}

int count_in_range(
    int P[],
    int a,
    int b
) {
    if (a > b) return 0;
    if (a == 0) return P[b];
    return P[b] - P[a - 1];
}

int main() {
    int A[] = {0, 1, 2, 3, 6, 4, 5};
    int n = sizeof(A) / sizeof(A[0]);
    int k = 6;

    int* P = (int*)malloc((k + 1) * sizeof(int));
    preprocess(A, n, k, P);

    printf("Number in range [0, 4]: %d\n", count_in_range(P, 0, 3));

    free(P);
    return 0;
}