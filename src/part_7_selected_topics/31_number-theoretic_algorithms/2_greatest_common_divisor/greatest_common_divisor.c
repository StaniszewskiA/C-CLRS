#include "part_7_selected_topics/31_number-theoretic_algorithms/31_number-theoretic_algorithms.h"

uint64_t euclid_gcd(uint64_t a, uint64_t b) {
    while (b != 0) {
        uint64_t tmp = b;
        b = a % b;
        a = tmp;
    }

    return a;
}

void test_euclid_gcd(void) {
    uint64_t a = 30;
    uint64_t b = 27;

    printf("gcd(%llu, %llu) = %llu\n", a, b, euclid_gcd(a, b));
}


uint64_t extended_euclid_gcd(uint64_t a, uint64_t b, int64_t* x, int64_t* y) {
    if (b == 0) {
        if (x) *x = 1;
        if (y) *y = 0;
        return a;
    }

    int64_t xPrime, yPrime;
    uint64_t gcd = extended_euclid_gcd(b, a % b, &xPrime, &yPrime);

    if (x) *x = yPrime;
    if (x) *y = xPrime - (a / b) * yPrime;

    return gcd;
}

void test_extended_euclid_gcd(void) {
    uint64_t a = 30;
    uint64_t b = 27;
    int64_t x, y;
    
    uint64_t gcd = extended_euclid_gcd(a, b, &x, &y);

    printf("gcd(%llu, %llu) = %llu\n", a, b, gcd);
    printf("Coefficients: x = %lld, y = %lld\n", x, y);
    printf("Check: %llu*%lld + %llu*%lld = %lld\n", a, x, b, y, a*x + b*y);
}

/*
    31.2-4
*/

uint64_t euclid_gcd_recursive(uint64_t a, uint64_t b) {
    if (b == 0) return a;
    return euclid_gcd_recursive(b, a % b);
}

void test_euclid_gcd_recursive(void) {
    uint64_t a = 30;
    uint64_t b = 27;

    printf("gcd(%llu, %llu) = %llu\n", a, b, euclid_gcd_recursive(a, b));
}

/*
    31.2-7
*/

void extended_euclid_gcd_multiple(
    const int64_t* a, 
    int n, 
    int64_t* g, 
    int64_t* xs
) {
    if (n == 1) {
        *g = a[0];
        xs[0] = 1;
        return;
    }

    int64_t ys[n];
    for (int i = 0; i < n; ++i) {
        xs[i] = 1;
        ys[i] = 0;
    }
    
    int64_t gTemp = a[n - 1];
    for (int i = n - 2; i >= 0; --i) {
        int64_t x, y;
        gTemp = extended_euclid_gcd(a[i], gTemp, &x, &y);
        xs[i] = x;
        ys[i + 1] = y;
    }

    int64_t m = 1;
    for (int i = 1; i < n; ++i) {
        m *= ys[i];
        xs[i] *= m;
    }

    *g = gTemp;
}

void test_extended_euclid_gcd_multiple(void) {
    int64_t a[] = {30, 27, 12};
    int n = ARRAY_SIZE(a);
    int64_t g;
    int64_t xs[3];

    extended_euclid_gcd_multiple(a, n, &g, xs);

    printf("gcd = %lld\n", g);
    printf("Coefficients: ");
    for (int i = 0; i < n; ++i) printf("%lld ", xs[i]);
}

/*
    31.2-8
*/

uint64_t lcm(uint64_t a, uint64_t b) {
    return a / euclid_gcd(a, b) * b;
}

void  test_lcm(void) {
    uint64_t a = 30;
    uint64_t b = 27;

    printf("lcm(%llu, %llu) = %llu\n", a, b, lcm(a, b));
}

uint64_t lcm_multiple(const int64_t* a, int n) {
    uint64_t l = a[0];
    for (int i = 1; i < n; ++i) l = lcm(l, a[i]);
    return l;
}

void test_lcm_multiple(void) {
    int64_t a[] = {30, 27, 12};
    int n = ARRAY_SIZE(a);
    uint64_t result = lcm_multiple(a, n);
    printf("lcm_multiple = %llu\n", result);
}
