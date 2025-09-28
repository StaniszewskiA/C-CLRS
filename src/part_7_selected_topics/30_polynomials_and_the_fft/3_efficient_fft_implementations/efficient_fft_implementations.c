#include "part_7_selected_topics/30_polynomials_and_the_fft/polynomials_and_the_fft.h"

int bit_reverse(int k, int b) {
    int res = 0;

    for (int i = 0; i < b; ++i) {
        res = (res << 1) | (k & 1);
        k >>= 1;
    }

    return res;
}

void bit_reverse_permutation(complex double* a, int n) {
    int b = 0;
    int temp = n - 1;

    while (temp > 0) {
        b++;
        temp >>= 1;
    }

    for (int k = 0; k < n; ++k) {
        int r = bit_reverse(k, b);
        if (r <= k) continue;
        complex double temp = a[k];
        a[k] = a[r];
        a[r] = temp;
    }
}

void test_bit_reverse_permutation(void) {
    int n = 8;
    complex double a[8] = {0, 1, 2, 3, 4, 5, 6, 7};
    
    printf("Input:\n");
    for (int i = 0; i < n; ++i) printf("%.0f ", creal(a[i]));
    printf("\n");
    
    bit_reverse_permutation(a, n);
    
    printf("Permutation:\n");
    for (int i = 0; i < n; ++i) printf("%.0f ", creal(a[i]));
    printf("\n");
}
