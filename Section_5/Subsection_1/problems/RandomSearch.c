#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int randomSearch(
    int A[],
    int n,
    int x
) {
    bool *picked = (bool *)calloc(n, sizeof(bool));
    int k = 0;

    while (k < n) {
        int i = rand() % n;

        if (A[i] == x) {
            free(picked);
            return i;
        }

        if (!picked[i]) {
            picked[i] = true;
            k++;
        }
    }

    free(picked);
    return -1;
}

int main() {
    int A[] = {4, 2, 7, 1, 9, 3, 5};
    int n = sizeof(A) / sizeof(A[0]);
    int x = 3;

    int result = randomSearch(A, n, x);

    if (result != -1)
        printf("Element %d found at index %d\n", x, result);
    else
        printf("Element %d not found\n", x);

    return 0;   
}