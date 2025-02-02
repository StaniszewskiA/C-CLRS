#include <stdio.h>
#include <stdlib.h>

#define MAX_K 100

typedef struct {
    int value;
    int listIdx;
    int nextIdx;
} HeapNode;

void swap(
    HeapNode *x,
    HeapNode *y
) {
    HeapNode temp = *x;
    *x = *y;
    *y = temp;
}

void min_heapify(
    HeapNode A[],
    int n,
    int i
) {
    int smallest = i;
    int left, right;

    while (1) {
        left = 2 * i + 1;
        right = 2 * i + 2;

        if (left < n && A[left].value < A[smallest].value) {
            smallest = left;
        }

        if (right < n && A[right].value < A[smallest].value) {
            smallest = right;
        }

        if (smallest == i)  
            break;

        swap(&A[i], &A[smallest]);
        i = smallest; 
    }
}

void build_min_heap(
    HeapNode A[],
    int n
) {
    for (int i = n / 2 - 1; i >= 0; i--)
        min_heapify(A, n, i);
}

void print_arr(
    int A[], 
    int n
) {
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);
    printf("\n");
}

void merge_k_sorted_lists(
    int *lists[],
    int listSizes[],
    int k,
    int *result
) {
    HeapNode heap[MAX_K];
    int heapSize = k;
    int resultIdx = 0;

    for (int i = 0; i < k; i++) {
        if (listSizes[i] > 0) {
            heap[i].value = lists[i][0];
            heap[i].listIdx = i;
            heap[i].nextIdx = 1;
        }
    }

    build_min_heap(heap, heapSize);

    while (heapSize > 0) {
        // Extract root
        result[resultIdx++] = heap[0].value;

        int listIdx = heap[0].listIdx;
        int nextIdx = heap[0].nextIdx;

        if (nextIdx < listSizes[listIdx]) {
            heap[0].value = lists[listIdx][nextIdx];
            heap[0].nextIdx++;
        } else {
            heap[0] = heap[heapSize - 1];
            heapSize--;
        }

        min_heapify(heap, heapSize, 0);
    }
}

int main() {
    int list1[] = {1, 2, 3};
    int list2[] = {4, 5, 6, 7};
    int list3[] = {8, 9};

    int *lists[] = {
        list1,
        list2,
        list3
    };
    int listSizes[] = {3, 4, 2};
    int k = 3;

    int n = listSizes[0] + listSizes[1] + listSizes[2];
    int result[n];
    
    merge_k_sorted_lists(lists, listSizes, k, result);

    printf("Merged list: ");
    print_arr(result, n);

    return 0;
}