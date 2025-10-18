#include "part_7_selected_topics/31_number-theoretic_algorithms/31_number-theoretic_algorithms.h"

void modular_linear_equation_solver(int a, int b, int n) {
    int64_t xPrime, yPrime;
    uint64_t d = extended_euclid_gcd(a, n, &xPrime, &yPrime);

    if (b % d) {
        printf("No solutions\n");
        return;
    }

    int64_t x_0 = ((xPrime * ((int64_t)b / (int64_t)d)) % (int64_t)n + (int64_t)n) % (int64_t)n;

    if (d == 1) {
        printf("Only one solution found\n");
        printf("%d * %lld ≡ %d (mod %d)\n", a, x_0, b, n);
        return;
    }

    printf("Solutions:\n");
    for (int i = 0; i < (int)d; ++i) {
        int64_t solution = (x_0 + i * (n / d)) % n;
        printf("%lld ", solution);
    }
    printf("\n");
}

void test_modular_linear_equation_solver(void) {
    int a = 35;
    int b = 10;
    int n = 50;
    modular_linear_equation_solver(a, b, n);
}

/*
    31.4-3
*/

void modular_linear_equation_solver_modified(int a, int b, int n) {
    int64_t xPrime, yPrime;
    uint64_t d = extended_euclid_gcd(a, n, &xPrime, &yPrime);

    if (b % d) {
        printf("No solutions\n");
        return;
    }

    int64_t x_0 = ((xPrime * ((int64_t)b / (int64_t)d)) % ((int64_t)n / (int64_t)d) + (int64_t)n) % (int64_t)n;

    if (d == 1) {
        printf("Only one solution found\n");
        printf("%d * %lld ≡ %d (mod %d)\n", a, x_0, b, n);
        return;
    }

    printf("Solutions:\n");
    for (int i = 0; i < (int)d; ++i) {
        int64_t solution = (x_0 + i * (n / d)) % n;
        printf("%lld ", solution);
    }
    printf("\n");
}

void test_modular_linear_equation_solver_modified(void) {
    int a = 35;
    int b = 10;
    int n = 50;
    modular_linear_equation_solver_modified(a, b, n);
}
