#include <stdio.h>
#include <stdbool.h>
#include "sum_search.h"

bool binarySearch(int arr[], int left, int right, int target)
{
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        printf("Mid element for binary search: %d\n", arr[mid]);

        if (arr[mid] == target)
            return true;

        if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return false;
}

bool sumSearch(int arr[], int size, int target)
{
    mergeSort(arr, 0, size - 1);
    printf("Sorted array: ");
    printArray(arr, size);

    for (int i = 0; i < size - 1; i++)
    {
        int complement = target - arr[i];
        if (complement > arr[i])
        {
            printf("Checking if complement %d of element %d exists.\n", complement, arr[i]);
            if (binarySearch(arr, i + 1, size - 1, complement))
                return true;
        }
    }

    return false;
}

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int leftArr[n1], rightArr[n2];

    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void printArraySlice(int arr[], int left, int right)
{
    printf("Array slice: ");
    for (int i = left; i <= right; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main()
{
    int arr[] = {3, 7, 1, 2, 8, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 11;

    if (sumSearch(arr, n, target)) {
        printf("There are two distinct elements that sum up to %d.\n", target);
    } else {
        printf("There are no two distinct elements that sum up to %d.\n", target);
    }

    return 0;
}