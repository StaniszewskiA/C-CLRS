#include "bubble_sort.h"

void swap(int* xp, int* yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(int arr[], int n) {
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                            printf("Sorting: \n");
            printArray(arr, n);
            swap(&arr[j], &arr[j + 1]);
            swapped = true;
            }
        }

        if (swapped == false)
            break;
    }
}

void printArray(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = { 64, 34, 25, 12, 22, 11, 90 };
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Array before sorting: \n");
    printArray(arr, n);

    bubbleSort(arr, n);

    printf("Array after sorting: \n");
    printArray(arr, n);

    return 0;
}