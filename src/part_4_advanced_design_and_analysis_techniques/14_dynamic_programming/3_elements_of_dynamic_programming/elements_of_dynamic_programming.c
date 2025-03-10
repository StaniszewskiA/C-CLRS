#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int lookup_chain(int **m, int *p, int i, int j);
int memoized_matrix_chain(int *p, int n);

int main(void) {
    int p[] = {30, 35, 15, 5, 10, 20, 25};
    int n = sizeof(p) / sizeof(p[0]) - 1;

    printf("Minimum number of multiplications: %d\n", 
        memoized_matrix_chain(p, n));

    return 0;
}

int memoized_matrix_chain(int *p, int n) {
    int **m = (int**)malloc((n + 1) * sizeof(int*));
    for (int i = 0; i <= n; i++) {
        m[i] = (int*)malloc((n + 1) * sizeof(int));
        for (int j = i; j <= n; j++) m[i][j] = INT_MAX;
    }

    int cost = lookup_chain(m, p, 1, n);

    for (int i = 0; i <= n; i++) free(m[i]);
    free(m);

    return cost;
}

int lookup_chain(int **m, int *p, int i, int j) {
    if (m[i][j] != INT_MAX) return m[i][j];
    int min_cost = INT_MAX;

    if (i == j) m[i][j] = 0;
    else 
    {
        for (int k = i; k < j; k++) {
            int q = lookup_chain(m, p, i, k) 
                + lookup_chain(m, p, k + 1, j) 
                + p[i - 1] * p[k] * p[j];
            
                if (q < min_cost) min_cost = q;
        }
    }

    m[i][j] = min_cost; 
    return min_cost;
}