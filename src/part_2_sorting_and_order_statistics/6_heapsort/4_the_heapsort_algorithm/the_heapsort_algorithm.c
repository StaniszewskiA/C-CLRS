#include "part_2_sorting_and_order_statistics/6_heapsort/heapsort.h"

void heapsort(int A[], int n) {
    build_max_heap(A, n);

    for (int i = n - 1; i > 0; i--) {
        SWAP_INT(A[0], A[i]);
        max_heapify_iterative(A, i, 0);
    }
}