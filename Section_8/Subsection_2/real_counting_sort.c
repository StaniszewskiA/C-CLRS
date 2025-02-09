#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void count_sort_real(
    double A[],
    int n,
    int k,
    int d
) {
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

void print_arr(double arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%.2f ", arr[i]);
    }
    printf("\n");
}

int main() {
    double A[] = {3.14, 1.41, 2.72, 1.62, 2.46, 0.99, 3.01};
    int n = sizeof(A) / sizeof(A[0]);
    int k = 3;
    int d = 2;

    printf("Before: \n");
    print_arr(A, n);

    count_sort_real(A, n, k, d);
    printf("After: \n");
    print_arr(A, n);

    return 0;
}