#include <stdio.h>
#include <limits.h>

#define min_SIZE 100

void swap(
    int A[],
    int i,
    int j
) {
    int temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}

void min_heapify(
    int A[], 
    int n, 
    int i
) {
    int smallest = i;
    int left, right;

    while (1) {
        left = 2 * i + 1;
        right = 2 * i + 2;

        if (left < n && A[left] < A[smallest]) {
            smallest = left;
        }

        if (right < n && A[right] < A[smallest]) {
            smallest = right;
        }

        if (smallest == i)  
            break;

        swap(A, i, smallest);
        i = smallest; 
    }
}


void build_min_heap(
    int A[],
    int n
) {
    for (int i = n / 2 - 1; i >= 0; i--)
        min_heapify(A, n, i);
}

void heap_sort(
    int A[],
    int n
) {
    build_min_heap(A, n);

    for (int i = n - 1; i > 0; i--) {
        swap(A, 0, i);
        min_heapify(A, i, 0);
    }
}

void print_arr(
    int A[], 
    int n
) {
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);
    printf("\n");
}

int min_heap_minimum(
    int A[],
    int n
) {
    if (n < 1) {
        printf("Heap underflow! No elements in heap.\n");
        return 0;
    }
    return A[0];
}

int min_heap_extract_min(
    int A[],
    int *n
) {
    if (*n < 1) {
        printf("Heap underflow! Cannot extract from an empty heap.\n");
        return 0;
    }

    int min = min_heap_minimum(A, *n);
    A[0] = A[--(*n)];
    min_heapify(A, *n, 0);

    return min;
}

void min_heap_increase_key(
    int A[],
    int n,
    int i,
    int key
) {
    if (key < A[i]) {
        printf("New key is smaller than current key!\n");
        return;
    }

    A[i] = key;
    min_heapify(A, n, i);
}

void min_heap_insert(
    int A[],
    int *n,
    int key
) {
    if (*n >= min_SIZE) {
        printf("Heap overflow! Cannot insert more elements.\n");
        return;
    }

    (*n)++;
    A[*n - 1] = INT_MIN;
    min_heap_increase_key(A, n, *n - 1, key);
}

int main() {
    int A[min_SIZE] = {15, 13, 9, 5, 12, 8, 7, 4, 0, 6, 2, 1};
    int n = 12;

    printf("Original array:\n");
    print_arr(A, n);

    build_min_heap(A, n);
    printf("min Heap:\n");
    print_arr(A, n);

    printf("min element: %d\n", min_heap_minimum(A, n));

    printf("Extracted min: %d\n", min_heap_extract_min(A, &n));
    print_arr(A, n);

    printf("Increasing key at index 10 to 15:\n");
    min_heap_increase_key(A, n, 10, 15);
    print_arr(A, n);

    // printf("Inserting new key 30:\n");
    // min_heap_insert(A, &n, 30);
    // print_arr(A, n);

    // printf("Sorted array using Heap Sort:\n");
    // heap_sort(A, n);
    // print_arr(A, n);

    return 0;
}