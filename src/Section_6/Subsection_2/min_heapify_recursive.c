#include <stdio.h>

void swap(
    int A[],
    int i,
    int j
) {
    int temp = A[i];
    A[i] = A[j];
    A[j] = temp; 
}

void minHeapifyRecursive(
    int A[],
    int n,
    int i
) {
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
        printf("\n");
        swap(A, i, smallest);
        minHeapifyRecursive(A, n, smallest);
    }
}

void buildMinHeap(
    int A[],
    int n
) {
    for (int i = n / 2 - 1; i >= 0; i--)
        minHeapifyRecursive(A, n, i);
}

void printArr(
    int A[],
    int n
) {
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);
    printf("\n");
}

int main() {
    int arr[] = {27, 17, 3, 16, 13, 10, 1, 5, 7, 12, 4, 8, 9, 0};
    int n = sizeof(arr) / sizeof(arr[0]);

    printArr(arr, n);

    buildMinHeap(arr, n);

    printArr(arr, n);

    return 0;
}