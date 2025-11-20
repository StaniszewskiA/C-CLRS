#include "part_7_selected_topics/31_number-theoretic_algorithms/31_number-theoretic_algorithms.h"

#define TASK 4

// 31-1
// https://www.geeksforgeeks.org/dsa/steins-algorithm-for-finding-gcd/
int stein_gcd(int a, int b) {
    if (a == 0) return b;
    if ((a == b) || (b == 0)) return a;

    if (!(a & 1)) { // a is even
        if (b & 1) return stein_gcd(a >> 1, b);
        else return stein_gcd(a >> 1, b >> 1) << 1;
    }

    if (!(b & 1)) return stein_gcd(a, b >> 1);

    if (a > b) return stein_gcd((a - b) >> 1, b);
    
    return stein_gcd((b - a) >> 1, a);
}

void test_stein_gcd(void) {
    int a = 222;
    int b = 333;
    printf("GCD(%d, %d) = %d\n", a, b, stein_gcd(a, b));
}

// 31-2

// 31-3
static void mat_mult(int res[2][2], int X[2][2], int Y[2][2]) {
    int tmp[2][2];
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            tmp[i][j] = 0;
            for (int k = 0; k < 2; ++k) tmp[i][j] += X[i][k] * Y[k][j];
        }
    }

    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j) res[i][j] = tmp[i][j];
}

static void mat_copy(int dest[2][2], int src[2][2]) {
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            dest[i][j] = src[i][j];
}

void mat_pow(int res[2][2], int A[2][2], int n) {
    int tmp[2][2];
    int A2[2][2];

    if (n == 1) {
        mat_copy(res, A);
        return;
    }

    mat_mult(A2, A, A);
    if (n & 1) {
        mat_pow(tmp, A2, (n - 1) / 2);
        mat_mult(res, A, tmp);
    } else {
        mat_pow(res, A2, n / 2);
    }
}

void test_mat_pow(void) {
    int n = 5;
    int A[2][2] = {{1, 1}, {1, 0}};
    int result[2][2];
    mat_pow(result, A, n);
    printf("A^%d =\n", n);
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) printf("%d ", result[i][j]);
        printf("\n");
    }
}

// 31-4
int is_quadratic_residue(int64_t a, int64_t p) {
    if (p <= 2) return 0;

    a %= p;
    if (a < 0) a += p;

    int64_t exp = (p - 1) / 2;
    int64_t res = modular_exponentation(a, exp, p);

    if (res == 0) return 0;         // Trivial residue
    else if (res == 1) return 1;    // Quadratic residue
    else return -1;    // Not a quadratic residue
}

void test_is_quadratic_residue(void) {
    int64_t p = 13;
    printf("Testing quadratic residues modulo %lld:\n", p);
    for (int64_t a = 1; a < p; ++a) {
        int res = is_quadratic_residue(a, p);
        if (res == 1) printf("%2lld is a quadratic residue\n", a);
        else if (res == -1) printf("%2lld is a non-residue\n", a);
        else printf("%2lld: invalid or error\n", a);
    }
}

int find_non_quadratic_residue(int64_t p, int64_t* aFound, int* trials) {
    if (p <= 2) return 0;
    int trialCnt = 0;
    int64_t a;

    do {
        a = random_int(1, p - 1);
        trialCnt++;
    } while (is_quadratic_residue(a, p) == 1);

    if (aFound) *aFound = a;
    if (trials) *trials = trialCnt;

    return a;
}

void test_find_non_quadratic_residue(void) {
    int64_t p = 13;
    int64_t a;
    int trials;
    find_non_quadratic_residue(p, &a, &trials);
    printf("Found non-quadratic residue %lld modulo %lld after %d trials.", 
        a, p, trials);
}

int main(void) {
    switch (TASK)
    {
        case 1: {
            test_stein_gcd();
            break;
        }
        case 2: {
            test_mat_pow();
            break;
        }
        case 3: {
            test_is_quadratic_residue();
            break;
        }
        case 4: {
            test_find_non_quadratic_residue();
            break;
        }
        default:
            break;
    }
    
    return 0;
}