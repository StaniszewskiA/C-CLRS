#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int scramble(int A[], int n) {
    srand(time(NULL));
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(&A[i], &A[j]);
    }
}

int scrambleSearch(
    int A[],
    int n,
    int x
) {
    scramble(A, n);
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

    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");

    int result = scrambleSearch(A, n, x);  // Search in shuffled array

    printf("Shuffled array (searched in this order): ");
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");

    if (result != -1)
        printf("Element %d found at index %d\n", x, result);
    else
        printf("Element %d not found\n", x);

    return 0;
}