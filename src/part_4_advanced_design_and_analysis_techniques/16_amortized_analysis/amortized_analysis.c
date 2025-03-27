#include <stdio.h>
#include <stdlib.h>

#define EXAMPLE 2

/*
    Example 1 - Multipop Heap
*/
#define MAX_HEAP_SIZE 100

typedef struct {
    int data[MAX_HEAP_SIZE];
    unsigned size;
} MinHeap;

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_down(MinHeap* heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->data[left] < heap->data[smallest]) 
        smallest = left;

    if (right < heap->size && heap->data[right] < heap->data[smallest])
        smallest = right;

    if (smallest != idx) {
        swap(&heap->data[idx], &heap->data[smallest]);
        heapify_down(heap, smallest);
    }
}

void heapify_up(MinHeap* heap, int idx) {
    int parentIdx = (idx - 1) / 2;

    if (idx > 0 && heap->data[idx] < heap->data[parentIdx]) {
        swap(&heap->data[idx], &heap->data[parentIdx]);
        heapify_up(heap, parentIdx);
    }
}

void heap_insert(MinHeap* heap, int val) {
    if (heap->size >= MAX_HEAP_SIZE) {
        printf("Heap overflow\n");
        return;
    }

    heap->data[heap->size] = val;
    heap->size++;
    heapify_up(heap, heap->size - 1);
}

int heap_pop(MinHeap* heap) {
    if (heap->size == 0) {
        printf("Heap underflow\n");
        return -1;
    }

    int minVal = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    heapify_down(heap, 0);

    return minVal;
}

/*
    Aggregate analysis - each operation takes at most T(n)/n.
*/
void heap_multipop(MinHeap* heap, int k) {
    int i;
    printf("Removing up to %d elements: ", k);

    for (i = 0; i < k && heap->size > 0; i++) 
        printf("%d ", heap_pop(heap));
    printf("\n");
}

void print_heap(MinHeap* heap) {
    int i;
    printf("Heap: ");
    
    for (i = 0; i < heap->size; i++) printf("%d ", heap->data[i]);
    printf("\n");
}

/*
    Example 2 - Binary Counter
*/
#define MAX_BITS 8

typedef struct {
    int bits[MAX_BITS];
    unsigned size;
} BinaryCounter;

void init_counter(BinaryCounter* bCounter) {
    int i;
    for (i = 0; i < MAX_BITS; i++) bCounter->bits[i] = 0;
    bCounter->size = MAX_BITS;
}

/*
    Aggregate analysis - number of bit modifications can be expressed as:

        sum_(i=0)^(k-1)floor(n/(2^i)) < n*sum_(i=0)^(inf)i/2^i = 2n

    e.g., for n increments, the first bit is modified n times, 
    the second n/2 times, etc. This yields an amortized cost of each 
    operation equal to O(n) / n = O(1).
*/
void increment_counter(BinaryCounter* bCounter) {
    int carry = 1;
    int i, sum;

    for (i = 0; i < bCounter->size; i++) {
        sum = bCounter->bits[i] + carry;
        bCounter->bits[i] = sum % 2;
        carry = sum / 2;

        if (carry == 0) break;
    }

    if (carry) printf("Counter overflow");
}

void print_counter(BinaryCounter* bCounter) {
    int i;

    printf("Binary Counter: ");
    for (i = bCounter->size - 1; i >= 0; i--) printf("%d", bCounter->bits[i]);
    printf("\n");
}

/*
    Example 3 - Dynamic Tables
*/

int main(void) {
    int i;

    switch (EXAMPLE)
    {
        case 1: {
            // Mutlipop Heap
            MinHeap heap;
            heap.size = 0;

            heap_insert(&heap, 10);
            heap_insert(&heap, 20);
            heap_insert(&heap, 5);
            heap_insert(&heap, 30);
            heap_insert(&heap, 15);

            print_heap(&heap);

            heap_multipop(&heap, 3);
            print_heap(&heap);

            break;
        }
        
        case 2: {
            // Binary Counter
            BinaryCounter bCounter;
            init_counter(&bCounter);

            printf("Initial bCounter:\n");
            print_counter(&bCounter);

            for (i = 0; i < 20; i++) {
                increment_counter(&bCounter);
                print_counter(&bCounter);
            }

            break;
        }

        case 3: {
            // Dynamic Tables
            break;
        }

        default:
            break;
    }

    return 0;
}