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

void maxHeapifyIterative(
    int A[],
    int n,
    int i
) {
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
        printf("\n");
        swap(A, i, largest);

        i = largest;
    }
}

void buildMaxHeap(
    int A[],
    int n
) {
    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapifyIterative(A, n, i);
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

    buildMaxHeap(arr, n);

    printArr(arr, n);

    return 0;
}