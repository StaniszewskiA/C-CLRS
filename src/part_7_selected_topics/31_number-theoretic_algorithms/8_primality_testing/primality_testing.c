#include "part_7_selected_topics/31_number-theoretic_algorithms/31_number-theoretic_algorithms.h"

int pseudoprime(int n, int basis) {
    return modular_exponentation(basis, n - 1, n) == 1;
}

static int witness(int a, int n) {
    int u = n - 1;
    int t = 0;

    while (u % 2 == 0) {
        u /= 2;
        t++;
    }

    int64_t x = modular_exponentation(a, u, n);
    int64_t prev = x;

    if (x == 1 || x == n - 1) return 0;

    for (int i = 1; i < t; i++) {
        x = modular_exponentation(prev, 2, n);
        if (x == n - 1) return 0;
        prev = x;
    }

    if (x != 1) return 1;

    return 0;
}

int miller_rabin(int n, int s) {
    for (int j = 1; j < s; j++) {
        int a = random_int(2, n - 2);
        if (witness(a, n)) return 0;
    }
    return 1;
}
