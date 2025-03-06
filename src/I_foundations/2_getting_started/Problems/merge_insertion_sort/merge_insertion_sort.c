#include "merge_insertion_sort.h"

void insertionSort(int arr[], int left, int right) {
    printf("Called insertion sort on aaray: \n");
    printArray(arr + left, right - left + 1);
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

void merge(int arr[], int left, int right, int mid) {
    printf("Called merge sort on aaray: \n");
    printArray(arr + left, right - left + 1);
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *leftArr = (int*) malloc(n1 * sizeof(int));
    int *rightArr = (int*) malloc(n2 * sizeof(int));

    if (leftArr == NULL || rightArr == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }


    for (i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2)
    {
        if (leftArr[i] <= rightArr[j])
        {
            arr[k] = leftArr[i];
            i++;
        }
        else
        {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = leftArr[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = rightArr[j];
        j++;
        k++;
    }

    free(leftArr);
    free(rightArr);
}

void mergeInsertionSort(int arr[], int left, int right, int k) {
    if (left < right) {
        if ((right - left + 1) <= k) {
            insertionSort(arr, left, right);
        } else {
            int mid = left + (right - left) / 2;
            mergeInsertionSort(arr, left, mid, k);
            mergeInsertionSort(arr, mid + 1, right, k);
            merge(arr, left, right, mid);
        }
    }
}

void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main()
{
    srand(time(0));

    int N = 50;
    int k = 2;

    int arr[N];
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 100;
    }

    printf("Starting array: \n");
    printArray(arr, N);

    mergeInsertionSort(arr, 0, N - 1, k);    

    printf("Sorted array: \n");
    printArray(arr, N);

    return 0;
}