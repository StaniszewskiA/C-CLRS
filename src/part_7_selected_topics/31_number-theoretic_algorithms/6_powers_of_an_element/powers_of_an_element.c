#include "part_7_selected_topics/31_number-theoretic_algorithms/31_number-theoretic_algorithms.h"

int64_t modular_exponentation(int64_t a, int64_t b, int64_t n) {
    if (b == 0) return 1;
    int64_t d = modular_exponentation(a, b >> 1, n);
    if (b & 1)
        return (a * d * d) % n;
    else
        return (d * d) % n;
}

void test_modular_exponentation(void) {
    int64_t a = 7, b = 4, n = 13;
    int64_t result = modular_exponentation(a, b, n);
    printf("%lld^%lld mod %lld = %lld\n", a, b, n, result);
}

/*
    31.6-4
*/

int64_t modular_exponentation_iterative(int64_t a, int64_t b, int64_t n) {
    int64_t res = 1;

    a = a % n;
    while (b > 0) {
        if (b & 1) res = (res * a) % n;
        a = (a * a) % n;
        b >>= 1;
    }

    return res;
}

void test_modular_exponentation_iterative(void) {
    int64_t a = 7, b = 4, n = 13;
    int64_t result = modular_exponentation_iterative(a, b, n);
    printf("%lld^%lld mod %lld = %lld\n", a, b, n, result);
}
