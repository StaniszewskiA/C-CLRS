#include <stdio.h>
#include "recursive_binary_search.h"

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

int recursiveBinarySearch(int arr[], int left, int right, int target)
{
    printArraySlice(arr, left, right);

    if (left <= right)
    {
        int mid = left + (right - left) / 2;
        printf("Mid element: %d\n", arr[mid]);

        if (arr[mid] == target)
            return mid;
        
        if (arr[mid] > target)
            return recursiveBinarySearch(arr, left, mid - 1, target);

        return recursiveBinarySearch(arr, mid + 1, right, target);
    }

    return -1;
}

int main()
{
    int arr[] = {2, 5, 8, 12, 16, 32, 41, 53, 120, 234, 665, 1021, 43212};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 234;

    printf("Target: %d\n", target);
    printf("Array: \n");
    printArray(arr, size);

    int result = recursiveBinarySearch(arr, 0, size - 1, target);

    if (result != -1)
        printf("Element is present at index %d\n", result);
    else
        printf("Element is not present in array\n");

    return 0;
}