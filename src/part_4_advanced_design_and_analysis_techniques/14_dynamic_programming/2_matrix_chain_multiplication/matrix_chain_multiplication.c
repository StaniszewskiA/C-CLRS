#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define TASK 2
//----------Matrix Chain Multiply----------
int matrix_chain_order(int p[], int n) {
    int m[n][n];
    int i, j, k, l, q;

    for (int i = 1; i < n; i++) m[i][i] = 0;

    for (l = 2; l < n; l++) {
        for (i = 1; i < - l + 1; i++) {
            j = i + l - 1;
            m[i][j] = INT_MAX;
            for (k = i; k <= j; k++) {
                q = m[i][k] + m[k + 1][j]
                    + p[i - 1] * p[k] * p[j];
                if (q < m[i][j]) m[i][j] = q;
            }
        }
    }

    return m[1][n - 1];
}

void print_optimal_parens(int **s, int i, int j) {
    if (i == j) printf("A%d", i); 
    else {
        printf("(");
        print_optimal_parens(s, i, s[i][j]);
        print_optimal_parens(s, s[i][j] + 1, j);
        printf(")");
    }
}

//----------14.2-2----------
int matrix_chain_multiply(int* A[], int s[][100], int i, int j) {
    if (i == j) return *A[j];
    if (i + 1 == j) return *A[i] * *A[j];

    int b = matrix_chain_multiply(A, s, i, s[i][j]);
    int c = matrix_chain_multiply(A, s, s[i][j] + 1, j);

    return b * c;
}

int main(void) {
    // p[i-1] x p[i] is the dimension of matrix i (1 ≤ i ≤ n-1)
    int p[] = {5, 10, 3, 12, 5, 50, 6};
    int n = sizeof(p) / sizeof(p[0]) - 1; // Number of matrices
    int s[100][100] = {0};

    switch (TASK)
    {
        case 1: {
            // 14.2-1
            printf("Minimum number of multiplications is %d ",
                matrix_chain_order(p, n));
            printf("Optimal parenthesization is: ");
            print_optimal_parens(s, 1, n - 1);
            break;
        }
        case 2: {
            // 14.2-2
            int* A[100];
            for (int i = 0; i < n; i++) {
                A[i] = (int*)malloc(sizeof(int));
                *A[i] = p[i];
            }

            printf("Result of matrix chain multiplication is %d ",
                matrix_chain_multiply(A, s, 1, n - 1));

            for (int i = 0; i < n; i++) free(A[i]);

            break;
        }
        default:
            break;
    }
}
