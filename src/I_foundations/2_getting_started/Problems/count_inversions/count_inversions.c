#include "count_inversions.h"

int mergeAndCount(int A[], int left, int mid, int right) {
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

int countInversions(int A[], int left, int right) {
    int inversions = 0;

    if (left < right) {
        int mid = left + (right - left) / 2;

        inversions += countInversions(A, left, mid);
        inversions += countInversions(A, mid + 1, right);
        inversions += mergeAndCount(A, left, mid, right);
    }

    return inversions;
}

int main() {
    int A[] = {2, 3, 8, 6, 1};
    int n = sizeof(A) / sizeof(A[0]);

    int inversionsCount = countInversions(A, 0, n - 1);
    printf("Number of inversions: %d\n", inversionsCount);

    return 0;
}