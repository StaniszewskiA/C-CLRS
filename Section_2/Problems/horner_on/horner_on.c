#include "horner_on.h"

int horner_on(int A[], int n, int x) {
    int result = A[n];

    for (int i = n - 1; i >= 0; i--) {
        result = A[i] + x * result;
    }

    return result;
}

int main() {
    int A[] = {-1, 2, -6, 2};
    int x = 3;
    int n = sizeof(A) / sizeof(A[0]) - 1;

    printf("Value of the polynomial is %d\n", horner_on(A, n, x));

    return 0;
}