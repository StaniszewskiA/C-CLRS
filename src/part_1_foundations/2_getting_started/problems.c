#include "part_1_foundations/2_getting_started/getting_started.h"

#define TASK 1

void bubble_sort(int arr[], int n) {
    int i, j;
    int swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = 0;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                            printf("Sorting: \n");
            print_arr(arr, n);
            int temp = arr[j];
            arr[j] = arr[j + 1];
            arr[j + 1] = temp;
            swapped = 1;
            }
        }

        if (swapped == 0)
            break;
    }
}

int merge_and_count(int A[], int left, int mid, int right) {
    int i, j ,k;
    int inversions = 0;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int leftArr[n1], rightArr[n2];

    for (i = 0; i < n1; i++)
        leftArr[i] = A[left + i];
    for (j = 0; j < n2; j++)
        rightArr[j] = A[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            A[k] = leftArr[i];
            i++;
        } else {
            A[k] = rightArr[j];
            j++;
            inversions += (n1 - i);
        }
        k++;
    }

    while (i < n1) {
        A[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        A[k] = rightArr[j];
        j++;
        k++;
    }

    return inversions;
}

int count_inversions(int A[], int left, int right) {
    int inversions = 0;

    if (left < right) {
        int mid = left + (right - left) / 2;

        inversions += count_inversions(A, left, mid);
        inversions += count_inversions(A, mid + 1, right);
        inversions += merge_and_count(A, left, mid, right);
    }

    return inversions;
}

int horner_on(int A[], int n, int x) {
    int result = A[n];

    for (int i = n - 1; i >= 0; i--) {
        result = A[i] + x * result;
    }

    return result;
}

int horner_on2(int A[], int n, int x) {
    int p = 0;

    for (int i = 0; i <= n; i++) {
        int s = A[i];

        for (int j = 1; j <= i; j++) {
            s = s * x;
        }

        p = p + s;
    }

    return p;
}

void insertion_sort2(int arr[], int left, int right) {
    printf("Called insertion sort on aaray: \n");
    print_arr(arr + left, right - left + 1);
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

void merge2(int arr[], int left, int right, int mid) {
    printf("Called merge sort on array: \n");
    print_arr(arr + left, right - left + 1);
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

void merge_insertion_sort(int arr[], int left, int right, int k) {
    if (left < right) {
        if ((right - left + 1) <= k) {
            insertion_sort2(arr, left, right);
        } else {
            int mid = left + (right - left) / 2;
            merge_insertion_sort(arr, left, mid, k);
            merge_insertion_sort(arr, mid + 1, right, k);
            merge2(arr, left, right, mid);
        }
    }
}

int main(void) {
    switch (TASK) {
        case 1: {
            int arr[] = { 64, 34, 25, 12, 22, 11, 90 };
            int n = sizeof(arr) / sizeof(arr[0]);
            printf("Array before sorting: \n");
            print_arr(arr, n);

            bubble_sort(arr, n);

            printf("Array after sorting: \n");
            print_arr(arr, n);
            break;
        }

        case 2: {
            int A[] = {2, 3, 8, 6, 1};
            int n = sizeof(A) / sizeof(A[0]);

            int inversionsCount = count_inversions(A, 0, n - 1);
            printf("Number of inversions: %d\n", inversionsCount);
            break;
        }

        case 3: {
            int A[] = {-1, 2, -6, 2};
            int x = 3;
            int n = sizeof(A) / sizeof(A[0]) - 1;

            printf("Value of the polynomial is %d\n", horner_on(A, n, x));
            break;
        }

        case 4: {
            int A[] = {-1, 2, -6, 2};
            int x = 3;
            int n = sizeof(A) / sizeof(A[0]) - 1;

            printf("Value of the polynomial is %d\n", horner_on2(A, n, x));
            break;
        }

        case 5: {
            srand(time(NULL));

            int N = 50;
            int k = 2;

            int arr[N];
            for (int i = 0; i < N; i++) {
                arr[i] = rand() % 100;
            }

            printf("Starting array: \n");
            print_arr(arr, N);

            merge_insertion_sort(arr, 0, N - 1, k);    

            printf("Sorted array: \n");
            print_arr(arr, N);
            break;
        }
        
        default:
            break;
    }

    return 0;
}