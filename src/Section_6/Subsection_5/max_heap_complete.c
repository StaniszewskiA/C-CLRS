#include <stdio.h>
#include <limits.h>

#define MAX_SIZE 100

void swap(
    int A[],
    int i,
    int j
) {
    int temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}

void max_heapify(
    int A[], 
    int n, 
    int i
) {
    int largest = i;
    int left, right;

    while (1) {
        left = 2 * i + 1;
        right = 2 * i + 2;

        if (left < n && A[left] > A[largest]) {
            largest = left;
        }

        if (right < n && A[right] > A[largest]) {
            largest = right;
        }

        if (largest == i)  
            break;

        swap(A, i, largest);
        i = largest; 
    }
}


void build_max_heap(
    int A[],
    int n
) {
    for (int i = n / 2 - 1; i >= 0; i--)
        max_heapify(A, n, i);
}

void heap_sort(
    int A[],
    int n
) {
    build_max_heap(A, n);

    for (int i = n - 1; i > 0; i--) {
        swap(A, 0, i);
        max_heapify(A, i, 0);
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

int max_heap_maximum(
    int A[],
    int n
) {
    if (n < 1) {
        printf("Heap underflow! No elements in heap.\n");
        return 0;
    }
    return A[0];
}

int max_heap_extract_max(
    int A[],
    int *n
) {
    if (*n < 1) {
        printf("Heap underflow! Cannot extract from an empty heap.\n");
        return 0;
    }

    int max = max_heap_maximum(A, *n);
    A[0] = A[--(*n)];
    max_heapify(A, *n, 0);

    return max;
}

void max_heap_increase_key(
    int A[],
    int i,
    int key
) {
    if (key < A[i]) {
        printf("New key is smaller than current key!\n");
        return;
    }

    A[i] = key;
    while (i > 0 && A[(i - 1) / 2] < A[i]) {
        swap(A, i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

void max_heap_insert(
    int A[],
    int *n,
    int key
) {
    if (*n >= MAX_SIZE) {
        printf("Heap overflow! Cannot insert more elements.\n");
        return;
    }

    (*n)++;
    A[*n - 1] = INT_MIN;
    max_heap_increase_key(A, *n - 1, key);
}

void max_heap_decrease_key(
    int A[], 
    int n, 
    int i, 
    int key
) {
    if (i < 0 || i >= n) {
        printf("Index out of bounds!\n");
        return;
    }
    if (key > A[i]) {
        printf("New key is larger than current key!\n");
        return;
    }
    A[i] = key;
    max_heapify(A, n, i);
}

void max_heap_increase_key_insertion(
    int A[],
    int i,
    int key
) {
    if (key < A[i]) {
        printf("New key is smaller than current key!\n");
        return;
    }

    int parent;
    int value = key;

    while (i > 0 && A[(parent = (i - 1) / 2)] < value) {
        A[i] = A[parent];
        i = parent;
    }

    A[i] = value;
}

void max_heap_delete(
    int A[],
    int *n,
    int i
) {
    if (*n <= 0) {
        printf("Heap underflow! No elements in heap.\n");
        return;
    }
    if (i < 0 || i >= *n) {
        printf("Index out of bounds!\n");
        return;
    }

    A[i] = A[--(*n)];

    if (i > 0 && A[i] > A[(i - 1) / 2]) {
        max_heap_increase_key(A, i, A[i]);
    } else {
        max_heapify(A, *n, i);
    }
}

int main() {
    int A[MAX_SIZE] = {3, 2, 1, 4, 5};
    int n = 5;

    printf("Original array:\n");
    print_arr(A, n);

    build_max_heap(A, n);
    printf("Max Heap:\n");
    print_arr(A, n);

    // printf("Max element: %d\n", max_heap_maximum(A, n));

    // printf("Extracted max: %d\n", max_heap_extract_max(A, &n));
    // print_arr(A, n);

    // printf("Increasing key at index 10 to 15:\n");
    // max_heap_increase_key_insertion(A, 10, 15);
    // print_arr(A, n);

    // printf("Inserting new key 30:\n");
    // max_heap_insert(A, &n, 30);
    // print_arr(A, n);

    // // printf("Sorted array using Heap Sort:\n");
    // // heap_sort(A, n);
    // // print_arr(A, n);

    // printf("Decreasing key at index 2 to 1:\n");
    // max_heap_decrease_key(A, n, 2, 1);
    // print_arr(A, n);

    // printf("Deleting key at index 1: \n");
    // max_heap_delete(A, &n, 1);
    // print_arr(A, n);

    return 0;
}