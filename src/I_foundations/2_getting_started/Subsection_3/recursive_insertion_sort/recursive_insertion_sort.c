#include <stdio.h>
#include "recursive_insertion_sort.h"

void recursiveInsertionSort(int arr[], int n)
{
    if (n <= 1)
        return;

    recursiveInsertionSort(arr, n - 1);

    int last = arr[n - 1];
    int j = n - 2;

    while (j >= 0 && arr[j] > last)
    {
        arr[j + 1] = arr[j];
        j--;
    }

    arr[j + 1] = last;
}

void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {12, 11, 13, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: \n");
    printArray(arr, n);

    recursiveInsertionSort(arr, n);

    printf("Sorted array: \n");
    printArray(arr, n);

    return 0;
}