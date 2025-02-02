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

void max_heap_increase_key(int A[], int i, int key) {
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

void build_max_heap_prim(
    int A[],
    int n
) {
    int heap_size = 1;

    for (int i = 1; i < n; i++)
        max_heap_insert(A, &heap_size, A[i]);
}

void print_arr(
    int A[], 
    int n
) {
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);
    printf("\n");
}

int main() {
    int A[MAX_SIZE] = {3, 2, 1, 4, 5};
    int n = 5;

    printf("Original array:\n");
    print_arr(A, n);

    build_max_heap_prim(A, n);
    printf("Max Heap (alternative build):\n");
    print_arr(A, n);

    return 0;
}