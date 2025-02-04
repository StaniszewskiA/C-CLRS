#include <stdio.h>

void swap(
    int *a,
    int *b 
) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(
    int A[],
    int p,
    int r
) {
    int x = A[r];
    int i = p - 1;

    for (int j = p; j < r; j++) {
        if (A[j] <= x) {
                        i++;
            swap(&A[i], &A[j]);
        }
    swap(&A[i + 1], &A[r]);
    }

    printf("Value at pivot idx: %d\n", x);
    return (i + 1);
}

void quicksort(
    int A[],
    int p,
    int r
) {
    if (p < r) {
        int q = partition(A, p, r);
        quicksort(A, p, q - 1);
        quicksort(A, q + 1, r);
    }
}

void print_arr(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int A[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(A) / sizeof(A[0]);
    
    printf("Unsorted array: \n");
    print_arr(A, n);
    
    int pi = partition(A, 0, n - 1);
    printf("Pivot index: %d\n", pi);

    quicksort(A, 0, n - 1);
    
    print_arr(A, n);
    
    return 0;
}