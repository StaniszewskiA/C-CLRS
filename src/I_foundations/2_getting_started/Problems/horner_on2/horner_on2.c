#include "horner_on2.h"

int horner_on2(int A[], int n, int x) {
    int p = 0;

    for (int i = 0; i <= n; i++) {
        int s = A[i];

        for (int j = 1; j <= i; j++) {
            s = s * x;
        }

        p = p + s;
    }

    return p;
}

int main() {
    int A[] = {-1, 2, -6, 2};
    int x = 3;
    int n = sizeof(A) / sizeof(A[0]) - 1;

    printf("Value of the polynomial is %d\n", horner_on2(A, n, x));

    return 0;
}