#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(
    int *a,
    int *b 
) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int hoare_partition(
    int A[],
    int p,
    int r
) {
    int x = A[p];
    int i = p - 1;
    int j = r + 1;

    while (1) {
        do {
            j--;
        } while (A[j] > x);

        do {
            i++;
        } while (A[i] < x);

        if (i >= j) {
            return j;
        }

        swap(&A[i], &A[j]);
    }
}

typedef struct {
    int q;
    int t;
} PartitionIndices;

PartitionIndices partition_prim(
    int A[],
    int p,
    int r
) {
    int x = A[r];
    int i = p - 1;
    int j = p;
    int k = r;

    while (j < k) {
        if (A[j] < x) {
            i++;
            swap(&A[i], &A[j]);
            j++;
        } else if (A[j] > x) {
            k--;
            swap(&A[j], &A[k]);
        } else {
            j++;
        }
    }
    swap(&A[k], &A[r]);

    return (PartitionIndices){i + 1, k};
}

PartitionIndices randomized_partition(
    int A[],
    int p,
    int r
) {
    int i = p + rand() % (r - p + 1);
    swap(&A[r], &A[i]);
    return partition_prim(A, p, r);
}

void quicksort(
    int A[],
    int p,
    int r
) {
    if (p < r) {
        PartitionIndices pi = randomized_partition(A, p, r);
        quicksort(A, p, pi.q - 1);
        quicksort(A, pi.t + 1, r);
    }
}

void quicksort_prim(
    int A[],
    int p,
    int r
) {
    if (p < r) {
        int x = A[p];
        int q = hoare_partition(A, p, r);

        int i = 0;
        while (A[i] != x) {
            i++;
        }

        if (i <= q) {
            swap(&A[i], &A[q]);
        } else {
            swap(&A[i], &A[q + 1]);
            q = q + 1;
        }

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
    
    int pi = hoare_partition(A, 0, n - 1);
    printf("Pivot index: %d\n", pi);

    quicksort_prim(A, 0, n - 1);
    
    print_arr(A, n);
    
    return 0;
}