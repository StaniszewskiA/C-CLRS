#include "part_1_foundations/2_getting_started/getting_started.h"

int iterative_binary_search(int arr[], int size, int target)
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

void merge(int arr[], int left, int mid, int right)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int leftArr[n1], rightArr[n2];

    for (i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        } k++;
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

    print_arr(arr + left, right - left + 1);
}

void merge_sort(int arr[], int left, int right)
{
    if (left < right) {
        int mid = left + (right - left) / 2;

        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int recursive_binary_search(int arr[], int left, int right, int target)
{
    print_arr_slice(arr, left, right);

    if (left <= right)
    {
        int mid = left + (right - left) / 2;
        printf("Mid element: %d\n", arr[mid]);

        if (arr[mid] == target)
            return mid;
        
        if (arr[mid] > target)
            return recursive_binary_search(arr, left, mid - 1, target);

        return recursive_binary_search(arr, mid + 1, right, target);
    }

    return -1;
}

void recursive_insertionSort(int arr[], int n)
{
    if (n <= 1) return;

    recursive_insertionSort(arr, n - 1);

    int last = arr[n - 1];
    int j = n - 2;

    while (j >= 0 && arr[j] > last) {
        arr[j + 1] = arr[j];
        j--;
    }

    arr[j + 1] = last;
}

int binary_search(int arr[], int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        printf("Mid element for binary search: %d\n", arr[mid]);

        if (arr[mid] == target) return 1;

        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }

    return 0;
}

int sum_search(int arr[], int size, int target) {
    merge_sort(arr, 0, size - 1);
    printf("Sorted array: ");
    print_arr(arr, size);

    for (int i = 0; i < size - 1; i++) {
        int complement = target - arr[i];
        if (complement <= arr[i]) continue;
        printf("Checking if complement %d of element %d exists.\n", 
            complement, arr[i]);
        if (binary_search(arr, i + 1, size - 1, complement))
            return 1;
    }

    return 0;
}