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

// 31-4

int main(void) {
    switch (TASK)
    {
        case 1: {
            int a = 222;
            int b = 333;
            printf("GCD(%d, %d) = %d", a, b, stein_gcd(a, b));
            break;
        }

        default:
            break;
    }
}