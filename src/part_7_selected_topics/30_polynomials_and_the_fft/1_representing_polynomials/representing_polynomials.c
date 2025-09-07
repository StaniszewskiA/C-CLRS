#include "part_7_selected_topics/30_polynomials_and_the_fft/polynomials_and_the_fft.h"

void naive_polynomial_multiply(
    const double* a,
    int n,
    const double* b,
    int m,
    double* c
) {
    for (int i = 0; i < n + m - 1; ++i) c[i] = 0.0;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) c[i + j] += a[i] * b[j];

    print_arr_double(c, n + m - 1);
}

void test_naive_polynomial_multiply(void) {
    double a[] = {2, 3, 1}; 
    double b[] = {1, 4};  
    int n = 3, m = 2;
    double c[4]; 

    print_arr_double(a, n);
    print_arr_double(b, m);

    naive_polynomial_multiply(a, n, b, m, c);
}
