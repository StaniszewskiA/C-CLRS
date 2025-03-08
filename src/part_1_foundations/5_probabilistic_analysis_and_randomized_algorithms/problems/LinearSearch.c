#include <stdio.h>

int linearSearch(
    int A[],
    int n,
    int x
) {
    for (int i = 0; i < n; i++) {
        if (A[i] == x) {
            return i;
        }
    }

    return -1;
}

int main() {
    int A[] = {4, 2, 7, 1, 9, 3, 5};
    int n = sizeof(A) / sizeof(A[0]);
    int x = 3;

    int result = linearSearch(A, n, x);

    if (result != -1)
        printf("Element %d found at index %d\n", x, result);
    else
        printf("Element %d not found\n", x);

    return 0;
}