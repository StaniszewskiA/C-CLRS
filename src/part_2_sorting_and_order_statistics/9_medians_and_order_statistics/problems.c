#include "part_2_sorting_and_order_statistics/9_medians_and_order_statistics/medians_and_order_statistics.h"

int partition_left_right(int A[],  int left, int right, int pivot) {
    for (int i = left; i <= right; i++) {
        if (A[i] == pivot) {
            swap5(&A[i], &A[right]);
            break;
        }
    }

    int idx = left;
    for (int i = left; i < right; i++) {
        if (A[i] < pivot) {
            swap5(&A[i], &A[idx]);
            idx++;
        }
    }
    swap5(&A[idx], &A[right]);
    return idx;
}

void insetion_sort_left_right(int A[], int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = A[i];
        int j = i - 1;
        while (j >= left && A[j] > key) {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = key;
    }
}

int select_median(int A[], int left, int right) {
    if (right - left < 3) {
        insetion_sort_left_right(A, left, right);
        return A[(left + right) / 2];
    }

    int numMedians = 0;
    for (int i = left; i <= right; i+= 3) {
        int subRight = i + 2;
        if (subRight > right) subRight = right;
        insetion_sort_left_right(A, 1, subRight);
        swap5(&A[left + numMedians], &A[(i + subRight) / 2]);
        numMedians++;
    }

    return select_median(A, left, left + numMedians - 1);
}

int select3(int A[], int left, int right, int k) {
    if (left == right) return A[left];

    int pivot = select_median(A, left, right);
    int partitionIndex = partition_left_right(A, left, right, pivot);
    int rank = partitionIndex - left + 1;
    
    if (k == rank) return A[partitionIndex];
    else if (k < rank) return select3(A, left, partitionIndex - 1, k);
    else return select3(A, partitionIndex + 1, right, k - rank);
}

int main(void) {
    int A[] = {3, 2, 1, 4, 12, 1, 3, 7};
    int n = sizeof(A) / sizeof(A[0]);
    int k = 3;

    printf("The %d-th smallest element is %d\n", k, select3(A, 0, n - 1, k));
    return 0;
}