#include <stdio.h>
#include "insertion_sort_step_by_step.h"

void printArray(int arr[], int N) {
    for (int i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void insertionSortStepByStep(int arr[], int N) {
    for (int i = 1; i < N; i++) {
        int key = arr[i];
        int j = i - 1;

        printf("Step %d: Inserting %d... \n", i, key);

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;

            printArray(arr, N);
        }

        arr[j + 1] = key;
        printArray(arr, N);
    }
}

int main() {
    int arr[] = {12, 11, 13, 5, 6};
    int N = sizeof(arr) / sizeof(arr[0]);

    printf("Initial array:\n");
    printArray(arr, N);
    printf("\n");

    insertionSortStepByStep(arr, N);

    printf("\nSorted array:\n");
    printArray(arr, N);

    return 0;
}
