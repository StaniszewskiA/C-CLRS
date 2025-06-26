#include "part_2_sorting_and_order_statistics/7_quicksort/quicksort.h"

#define TASK 1

void fuzzy_partition(
    Interval A[],
    int p,
    int r,
    int *q1,
    int *q2
) {
    Interval x = A[r];
    int i = p - 1;
    int j = p;
    int k = r;

    while (j <= k) {
        if (A[j].high < x.low) {
            i++;
            SWAP_INTERVAL(A[i], A[j]);
            j++;
        } else if (A[j].low > x.high) {
            SWAP_INTERVAL(A[j], A[k]);
            k--;
        } else {
            j++;
        }
    }

    *q1 = i;
    *q2 = j;
}

void fuzzy_quicksort(Interval A[], int p, int r) {
    if (p < r) {
        int q1, q2;
        fuzzy_partition(A, p, r, &q1, &q2);
        fuzzy_quicksort(A, p, q1);
        fuzzy_quicksort(A, q2, r);
    }
}

int hoare_partition(int A[], int p, int r) {
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

        SWAP_INT(A[i], A[j]);
    }
}

PartitionIndices partition_prim(int A[], int p, int r) {
    int x = A[r];
    int i = p - 1;
    int j = p;
    int k = r;

    while (j < k) {
        if (A[j] < x) {
            i++;
            SWAP_INT(A[i], A[j]);
            j++;
        } else if (A[j] > x) {
            k--;
            SWAP_INT(A[j], A[k]);
        } else {
            j++;
        }
    }
    SWAP_INT(A[k], A[r]);

    return (PartitionIndices){i + 1, k};
}

PartitionIndices randomized_partition(
    int A[],
    int p,
    int r
) {
    int i = p + rand() % (r - p + 1);
    SWAP_INT(A[r], A[i]);
    return partition_prim(A, p, r);
}

void randomized_quicksort(int A[], int p, int r) {
    if (p < r) {
        PartitionIndices pi = randomized_partition(A, p, r);
        randomized_quicksort(A, p, pi.q - 1);
        randomized_quicksort(A, pi.t + 1, r);
    }
}

void quicksort_prim(int A[], int p, int r) {
    if (p < r) {
        int x = A[p];
        int q = hoare_partition(A, p, r);

        int i = 0;
        while (A[i] != x) {
            i++;
        }

        if (i <= q) {
            SWAP_INT(A[i], A[q]);
        } else {
            SWAP_INT(A[i], A[q+ 1]);
            q = q + 1;
        }

        randomized_quicksort(A, p, q - 1);
        randomized_quicksort(A, q + 1, r);
    }
}

void stooge_sort(int A[], int p, int r) {
    if (A[p] > A[r]) {
        SWAP_INT(A[p], A[r]);
    }

    if (p + 1 < r) {
        int k = (r - p + 1) / 3;
        stooge_sort(A, p, r - k);
        stooge_sort(A, p + k, r);
        stooge_sort(A, p, r - k);
    }
}

void tre_quicksort(int A[], int p, int r) {
    while (p < r) {
        int q = partition(A, p, r);
        tre_quicksort(A, p, q - 1);
        p = q + 1;
    }
}

void tre_quicksort_prim(int A[], int p, int r) {
    while (p < r) {
        int q = partition(A, p, r);
        if (q < (r - p) / 2) {
            tre_quicksort_prim(A, p, q - 1);
            p = q + 1;
        } else {
            tre_quicksort_prim(A, q + 1, r);
            r = q - 1;
        }
    }
}

int main(void) {
    switch (TASK) {
        case 1: {
            Interval data[] = {{1, 5}, {3, 7}, {8, 12}, {6, 10}, {15, 20}, {11, 13}};
            int size = sizeof(data) / sizeof(data[0]);
            
            fuzzy_quicksort(data, 0, size - 1);
            
            print_intervals(data, size);

            break;
        }

        case 2: {
            int A[] = {10, 7, 8, 9, 1, 5};
            int n = sizeof(A) / sizeof(A[0]);
            
            printf("Unsorted array: \n");
            print_arr(A, n);
            
            int pi = hoare_partition(A, 0, n - 1);
            printf("Pivot index: %d\n", pi);

            quicksort_prim(A, 0, n - 1);
            
            print_arr(A, n);

            break;
        }

        case 3: {
            int arr[] = {5, 3, 8, 2, 1, 4};
            int n = sizeof(arr) / sizeof(arr[0]);
            
            printf("Original array: ");
            print_arr(arr, n);
            
            stooge_sort(arr, 0, n - 1);
            
            printf("Sorted array: ");
            print_arr(arr, n);

            break;
        }

        case 4: {
            int A[] = {10, 7, 8, 9, 1, 5};
            int n = sizeof(A) / sizeof(A[0]);
            
            printf("Unsorted array: \n");
            print_arr(A, n);
            
            tre_quicksort_prim(A, 0, n - 1);
            print_arr(A, n);

            break;
        }

        default:
            break;
    }

    return 0;
}