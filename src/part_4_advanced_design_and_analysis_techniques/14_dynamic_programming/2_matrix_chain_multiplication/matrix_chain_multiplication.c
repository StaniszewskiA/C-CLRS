#include "part_4_advanced_design_and_analysis_techniques/14_dynamic_programming/dynamic_programming.h"

#define TASK 1

int matrix_chain_order(int p[], int n, int s[][MAX_MATRIX_SIZE]) {  
    int m[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE]; 
    for (int i = 1; i <= n; i++) {
        m[i][i] = 0;
    }
    
    for (int l = 2; l <= n; l++) {
        for (int i = 1; i <= n - l + 1; i++) {  
            int j = i + l - 1;
            m[i][j] = INT_MAX;
            
            for (int k = i; k <= j - 1; k++) { 
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;  
                }
            }
        }
    }

    return m[1][n];
}

void print_optimal_parens(int s[][MAX_MATRIX_SIZE], int i, int j) {  
    if (i == j) {
        printf("A%d", i); 
    } else {
        printf("(");
        print_optimal_parens(s, i, s[i][j]);
        print_optimal_parens(s, s[i][j] + 1, j);
        printf(")");
    }
}


int matrix_chain_multiply(int* A[], int s[][MAX_MATRIX_SIZE], int i, int j) {
    if (i == j) return *A[i];
    if (i + 1 == j) return *A[i] * *A[j];

    int b = matrix_chain_multiply(A, s, i, s[i][j]);
    int c = matrix_chain_multiply(A, s, s[i][j] + 1, j);

    return b * c;
}
