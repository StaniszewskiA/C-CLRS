#include <stdio.h>
#include "iterative_binary_search.h"

int iterativeBinarySearch(int arr[], int size, int target)
{
    int left = 0;
    int right = size - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        printf("Mid element: %d\n", arr[mid]);
        if (arr[mid] == target)
            return mid;

        if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

int main()
{
    int arr[] = {2, 5, 8, 12, 16, 32, 41, 53, 120, 234, 665, 1021, 43212};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 234;
    int result = iterativeBinarySearch(arr, size, target);

    if (result != -1)
        printf("Element is present at index %d\n", result);
    else
        printf("Element is not present in array\n");

    return 0;
}
