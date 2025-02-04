#include <stdio.h>

void swap(
    int *a,
    int *b
) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void stooge_sort(
    int A[],
    int p,
    int r
) {
    if (A[p] > A[r]) {
        swap(&A[p], &A[r]);
    }

    if (p + 1 < r) {
        int k = (r - p + 1) / 3;
        stooge_sort(A, p, r - k);
        stooge_sort(A, p + k, r);
        stooge_sort(A, p, r - k);
    }
}

void print_arr(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {5, 3, 8, 2, 1, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Original array: ");
    print_arr(arr, n);
    
    stooge_sort(arr, 0, n - 1);
    
    printf("Sorted array: ");
    print_arr(arr, n);
    
    return 0;
}