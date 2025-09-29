#include "part_7_selected_topics/30_polynomials_and_the_fft/polynomials_and_the_fft.h"

/*
    30-1a
*/

void multiply_deq1_polynomials(
    const double a,
    const double b,
    const double c,
    const double d,
    double* res
) {
    double ac = a * c;
    double bd = b * d;
    double ab_cd = (a + b) * (c + d);
    double middle = ab_cd - ac - bd;

    res[0] = ac;
    res[1] = middle;
    res[2] = bd;
}

void test_multiply_deq1_polynomials(void) {
    double a = 2;
    double b = 3;
    double c = 4;
    double d = 5;
    double res[3];

    printf("Input: (%.2fx+%.2f)*(%.2fx+%.2f)\n", a, b, c, d);
    multiply_deq1_polynomials(a, b, c, d, res);
    printf("Output: %.2fdx^2+%.2fdx+%.2fd", res[0], res[1], res[2]);
}

/*
    30-1b
*/

void multiply_polynomials_hili(
    const double* a1,
    const double* a2,
    int n,
    double* res
) {
    // Low index-high index
    if (n == 1) {
        res[0] = a1[0] * a2[0];
        return;
    }

    int m = n / 2;
    double* hi1 = safe_malloc(m * sizeof(double));
    double* lo1 = safe_malloc(m * sizeof(double));
    double* hi2 = safe_malloc(m * sizeof(double));
    double* lo2 = safe_malloc(m * sizeof(double));
    memcpy(lo1, a1, m * sizeof(double));
    memcpy(hi1, a1 + m, m * sizeof(double));
    memcpy(lo2, a2, m * sizeof(double));
    memcpy(hi2, a2 + m, m * sizeof(double));

    double* hi_product = safe_calloc(2 * m - 1, sizeof(double));
    double* cross_product = safe_calloc(2 * m - 1, sizeof(double));
    double* lo_product = safe_calloc(2 * m - 1, sizeof(double));

    multiply_polynomials_hili(hi1, hi2, m, hi_product);
    multiply_polynomials_hili(lo1, lo2, m, lo_product);

    double* sum1 = safe_malloc(m * sizeof(double));
    double* sum2 = safe_malloc(m * sizeof(double));
    for (int i = 0; i < m; ++i) {
        sum1[i] = hi1[i] + lo1[i];
        sum2[i] = hi2[i] + lo2[i];
    }
    multiply_polynomials_hili(sum1, sum2, m, cross_product);

    for (int i = 0; i < 2 * m - 1; ++i)
        cross_product[i] -= hi_product[i] + lo_product[i];

    memset(res, 0, (2 * n - 1) * sizeof(double));
    for (int i = 0; i < 2 * m - 1; ++i) {
        res[i + n] += hi_product[i];
        res[i + m] += cross_product[i];
        res[i] += lo_product[i];
    }

    free(hi1); 
    free(lo1); 
    free(hi2); 
    free(lo2);
    free(hi_product); 
    free(cross_product); 
    free(lo_product);
    free(sum1); 
    free(sum2);
}

void test_multiply_polynomials_hili(void) {
    int n = 4;
    double a1[4] = {1, 2, 3, 4};
    double a2[4] = {5, 6, 7, 8};
    double res[7];

    multiply_polynomials_hili(a1, a2, n, res);

    printf("Hi/Lo method result:\n");
    for (int i = 0; i < 2 * n - 1; ++i) printf("%.2f ", res[i]);
}

void multiply_polynomials_oiei(
    const double* a1,
    const double* a2,
    int n,
    double* res
) {
    // Odd index-even index
    if (n == 1) {
        res[0] = a1[0] * a2[0];
        return;
    }

    int m = n / 2;
    double* odd1 = safe_malloc(m * sizeof(double));
    double* even1 = safe_malloc(m * sizeof(double));
    double* odd2 = safe_malloc(m * sizeof(double));
    double* even2 = safe_malloc(m * sizeof(double));

    for (int i = 0; i < m; ++i) {
        odd1[i] = a1[2 * i + 1];
        even1[i] = a1[2 * i];
        odd2[i] = a2[2 * i + 1];
        even2[i] = a2[2 * i];
    }

    double* oddProduct = safe_calloc(2 * m - 1, sizeof(double));
    double* evenProduct = safe_calloc(2 * m - 1, sizeof(double));
    double* crossProduct = safe_calloc(2 * m - 1, sizeof(double));

    multiply_polynomials_oiei(odd1, odd2, m, oddProduct);
    multiply_polynomials_oiei(even1, even2, m, evenProduct);

    double* sum1 = safe_malloc(m * sizeof(double));
    double* sum2 = safe_malloc(m * sizeof(double));
    for (int i = 0; i < m; ++i) {
        sum1[i] = odd1[i] + even1[i];
        sum2[i] = odd2[i] + even2[i];
    }

    multiply_polynomials_oiei(sum1, sum2, m, crossProduct);

    for (int i = 0; i < 2 * m - 1; ++i)
        crossProduct[i] -= oddProduct[i] + evenProduct[i];

    memset(res, 0, (2 * n - 1) * sizeof(double));
    for (int i = 0; i < 2 * m - 1; ++i) {
        res[i + 2] += oddProduct[i];
        res[i + 1] += crossProduct[i];
        res[i] += evenProduct[i];
    }

    free(odd1);
    free(even1);
    free(odd2);
    free(even2);
    free(oddProduct);
    free(evenProduct);
    free(crossProduct);
    free(sum1);
    free(sum2);
}

void test_multiply_polynomials_oiei(void) {
    int n = 4;
    double a1[4] = {1, 2, 3, 4};
    double a2[4] = {5, 6, 7, 8};
    double res[7];

    multiply_polynomials_oiei(a1, a2, n, res);

    printf("Oi/Ei method result:\n");
    for (int i = 0; i < 2 * n - 1; ++i) printf("%.2f ", res[i]);
}

/*
    30.1c - Karatsuba algorithm
*/

static int bit_length(uint32_t x) {
    int len = 0;
    while (x > 0) {
        x >>= 1;
        len++;
    }

    return len > 0 ? len : 1;
}

uint32_t karatsuba(uint32_t x, uint32_t y) {
    if (x < 10 || y < 10) return x * y;

    int n = (bit_length(x) > bit_length(y)) ? bit_length(x) : bit_length(y);
    int m = n / 2;

    uint32_t lowerHalfMask = (1U << m) - 1;

    uint32_t lowX = x & lowerHalfMask;
    uint32_t highX = x >> m;
    uint32_t lowY = y & lowerHalfMask;
    uint32_t highY = y >> m;

    uint32_t z0 = karatsuba(lowX, lowY);
    uint32_t z1 = karatsuba(lowX + highX, lowY + highY);
    uint32_t z2 = karatsuba(highX, highY);

    return (z2 << (2 * m)) + ((z1 - z2 - z0) << m) + z0; 
}

void test_karatsuba(void) {
    uint32_t x = 13; // 1101
    uint32_t y = 11; // 1011

    uint32_t res = karatsuba(x, y);
    printf("Karatsuba's algorithm result: %u * %u = %u\n", x, y, res);
}

#define TASK 4

int main(void) {
    switch (TASK)
    {
        case 1: {
            test_multiply_deq1_polynomials();
            break;
        }

        case 2: {
            test_multiply_polynomials_hili();
            break;
        }

        case 3: {
            test_multiply_polynomials_oiei();
            break;
        }

        case 4: {
            test_karatsuba();
            break;
        }

        default:
            break;
    }
}
