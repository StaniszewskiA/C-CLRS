#include "part_1_foundations/5_probabilistic_analysis_and_randomized_algorithms/probabilistic_analysis_and_randomized_algorithms.h"

#define TASK 1

int linear_search2(int A[], int n, int x) {
    for (int i = 0; i < n; i++) 
        if (A[i] == x) return i;

    return -1;
}

int random_search(int A[], int n, int x) {
    int* picked = (int *)calloc(n, sizeof(int));
    int k = 0;

    while (k < n) {
        int i = rand() % n;

        if (A[i] == x) {
            free(picked);
            return i;
        }

        if (!picked[i]) {
            picked[i] = 1;
            k++;
        }
    }

    free(picked);
    return -1;
}

void scramble(int A[], int n) {
    srand(time(NULL));
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        SWAP_INT(A[i], A[j]);
    }
}

int scramble_search(int A[], int n, int x) {
    scramble(A, n);
    for (int i = 0; i < n; i++) 
        if (A[i] == x) return i;
        
    return -1;
}

int main(void) {
    int A[] = {4, 2, 7, 1, 9, 3, 5};
    int n = sizeof(A) / sizeof(A[0]);
    int x = 3;

    switch (TASK) {
        case 1: {
            int result = linear_search2(A, n, x);
            if (result != -1) 
                printf("Element %d found at index %d\n", x, result);
            else
                printf("Element %d not found\n", x);
            break;
        }

        case 2: {
            int result = random_search(A, n, x);
            if (result != -1)
                printf("Element %d found at index %d\n", x, result);
            else
                printf("Element %d not found\n", x);
            break;
        }

        case 3: {
            printf("Original array: ");
            for (int i = 0; i < n; i++) {
                printf("%d ", A[i]);
            }
            printf("\n");

            int result = scramble_search(A, n, x);  

            printf("Shuffled array (searched in this order): ");
            for (int i = 0; i < n; i++) {
                printf("%d ", A[i]);
            }
            printf("\n");

            if (result != -1)
                printf("Element %d found at index %d\n", x, result);
            else
                printf("Element %d not found\n", x);
            break;
        }
        
        default:
            break;
    }

    return 0;
}