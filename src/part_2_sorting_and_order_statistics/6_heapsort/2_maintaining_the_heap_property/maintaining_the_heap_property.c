#include "part_2_sorting_and_order_statistics/6_heapsort/heapsort.h"

void max_heapify_iterative(int A[], int n, int i) {
    int largest = i;
    int left, right;

    while (1) {
        left = 2 * largest + 1;
        right = 2 * largest + 2;

        if (left < n && A[left] > A[largest]) {
            printf("Swapping %d and %d", A[left], A[largest]);
            printf("\n");
            largest = left;
        }

        if (right < n && A[right] > A[largest]) {
            printf("Swapping %d and %d", A[right], A[largest]);
            printf("\n");
            largest = right;
        }

        if (largest == i)
            break;

        printf("Swapping %d and %d", A[i], A[largest]);
        SWAP_INT(A[i], A[largest]);

        i = largest;
    }
}

void build_max_heap(int A[],int n) {
    for (int i = n / 2 - 1; i >= 0; i--) max_heapify_iterative(A, n, i);
}

void max_heapify_recursive(int A[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && A[left] > A[largest]) {
        printf("Swapping %d and %d", A[left], A[largest]);
        printf("\n");
        largest = left;
    }

    if (right < n && A[right] > A[largest]) {
        printf("Swapping %d and %d", A[right], A[largest]);
        printf("\n");
        largest = right;
    }

    if (largest != i) {
        printf("Swapping %d and %d", A[i], A[largest]);
        SWAP_INT(A[i], A[largest]);
        max_heapify_recursive(A, n, largest);
    }
}

void build_max_heap_recursive(int A[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) max_heapify_recursive(A, n, i);
}

void min_heapify_recursive(int A[], int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && A[left] < A[smallest]) {
        printf("Swapping %d and %d", A[left], A[smallest]);
        printf("\n");
        smallest = left;
    }

    if (right < n && A[right] < A[smallest]) {
        printf("Swapping %d and %d", A[right], A[smallest]);
        printf("\n");
        smallest = right;
    }

    if (smallest != i) {
        printf("Swapping %d and %d", A[i], A[smallest]);
        SWAP_INT(A[i], A[smallest]);
        min_heapify_recursive(A, n, smallest);
    }
}

void build_min_heap_recursive(int A[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) min_heapify_recursive(A, n, i);
}

void min_heapify_iterative(int A[], int n, int i) {
    int smallest = i;
    int left, right;

    while (1) {
        left = 2 * smallest + 1;
        right = 2 * smallest + 2;

        if (left < n && A[left] < A[smallest]) {
            printf("Swapping %d and %d", A[left], A[smallest]);
            printf("\n");
            smallest = left;
        }

        if (right < n && A[right] < A[smallest]) {
            printf("Swapping %d and %d", A[right], A[smallest]);
            printf("\n");
            smallest = right;
        }

        if (smallest == i)
            break;

        printf("Swapping %d and %d", A[i], A[smallest]);
        SWAP_INT(A[i], A[smallest]);

        i = smallest;
    }
}

void build_min_heap_iterative(int A[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) min_heapify_iterative(A, n, i);
}