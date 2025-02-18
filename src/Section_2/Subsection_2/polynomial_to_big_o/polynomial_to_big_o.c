#include "polynomial_to_big_o.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int findHighestDegree(const char *polynomial) {
    int i = 0, maxExponent = 0;

    while (polynomial[i] != '\0') {
        int exponent = 0;
        while (polynomial[i] != 'x' && polynomial[i] != '\0') {
            i++;
        }

        if (polynomial[i] == 'x') {
            i++;
            if (polynomial[i] == '^') {
                i++;
                while (isdigit(polynomial[i])) {
                    exponent = exponent * 10 + (polynomial[i] - '0');
                    i++;
                }
            }
            else {
                exponent = 1;
            }
        }

        if (exponent > maxExponent) {
            maxExponent = exponent;
        }

        while (polynomial[i] != '+' && polynomial[i] != '-' && polynomial[i] != '\0') {
            i++;
        }
    }

    return maxExponent;
}

void determinBigO(int maxExponent) {
    if (maxExponent == 0) {
        printf("O(1)\n");
    }
    else {
        printf("O(n^%d)\n", maxExponent);
    }
}

int main() {
    const char *polynomial = "3x^7 + 2x^3 - 7x + 10";
    int maxExponent = findHighestDegree(polynomial);
    determinBigO(maxExponent);

    return 0;
}
