#include "part_7_selected_topics/31_number-theoretic_algorithms/31_number-theoretic_algorithms.h"

#define TASK 1

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

// 31-4

int main(void) {
    switch (TASK)
    {
        case 1: {
            int a = 222;
            int b = 333;
            printf("GCD(%d, %d) = %d\n", a, b, stein_gcd(a, b));
            break;
        }
        case 2: {
            int n = 5;
            int A[2][2] = {{1, 1}, {1, 0}};
            int result[2][2];
            mat_pow(result, A, n);
            printf("A^%d =\n", n);
            for (int i = 0; i < 2; ++i) {
                for (int j = 0; j < 2; ++j) printf("%d ", result[i][j]);
                printf("\n");
            }
            break;
        }
        default:
            break;
    }
    
    return 0;
}