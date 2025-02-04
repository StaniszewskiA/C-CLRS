#include <stdio.h>

typedef struct {
    int low;
    int high;
} Interval;

void swap(
    Interval *a,
    Interval *b 
) {
    Interval temp = *a;
    *a = *b;
    *b = temp;
}

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
            swap(&A[i], &A[j]);
            j++;
        } else if (A[j].low > x.high) {
            swap(&A[j], &A[k]);
            k--;
        } else {
            j++;
        }
    }

    *q1 = i;
    *q2 = j;
}

void fuzzy_quicksort(
    Interval A[],
    int p,
    int r
) {
    if (p < r) {
        int q1, q2;
        fuzzy_partition(A, p, r, &q1, &q2);
        fuzzy_quicksort(A, p, q1);
        fuzzy_quicksort(A, q2, r);
    }
}

void print_intervals(
    Interval A[],
    int size
) {
    for (int i = 0; i < size; i++) {
        printf("(%d, %d) ", A[i].low, A[i].high);
    }
    printf("\n");
}

int main() {
    Interval data[] = {{1, 5}, {3, 7}, {8, 12}, {6, 10}, {15, 20}, {11, 13}};
    int size = sizeof(data) / sizeof(data[0]);
    
    fuzzy_quicksort(data, 0, size - 1);
    
    print_intervals(data, size);
    return 0;
}