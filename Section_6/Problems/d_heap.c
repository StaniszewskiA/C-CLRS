#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *arr;
    int size;
    int capacity;
    int d;
} DHeap;

DHeap* create_dheap(
    int capacity,
    int d
) {
    DHeap *heap = (DHeap*)malloc(sizeof(DHeap));
    heap->capacity = capacity;
    heap->d = d;
    heap->size = 0;
    heap->arr = (int*)malloc(capacity * sizeof(int));

    return heap;
}

int get_left_child(
    DHeap *heap,
    int i
) {
    return heap->d * i + 1;
}

int get_right_child(
    DHeap *heap,
    int i
) {
    return heap->d * (i + 1);
}

int get_parent(
    DHeap *heap,
    int i
) {
    return (i - 1) / heap->d;
}

void heapify(
    DHeap *heap,
    int i
) {
    int largest = i;
    for (int j = 1; j <= heap->d; j++) {
        int child = get_left_child(heap, i) + j - 1;
        if (child < heap->size && heap->arr[child] > heap->arr[largest]) {
            largest = child;
        }
    }

    if (largest != i) {
        int temp = heap->arr[i];
        heap->arr[i] = heap->arr[largest];
        heap->arr[largest] = temp;
        heapify(heap, largest);
    }
}

void insert(
    DHeap *heap,
    int key
) {
    if (heap->size == heap->capacity) {
        printf("Heap overflow\n");
        return;
    }

    heap->arr[heap->size] = key;
    int i = heap->size;
    heap->size++;

    while (i > 0 && heap->arr[get_parent(heap, i)] < heap->arr[i]) {
        int temp = heap->arr[i];
        heap->arr[i] = heap->arr[get_parent(heap, i)];
        heap->arr[get_parent(heap, i)] = temp;
        i = get_parent(heap, i);
    }
}

int delete_root(
    DHeap *heap
) {
    if (heap->size <= 0) {
        printf("Heap underflow\n");
        return -1;
    }

    if (heap->size == 1) {
        heap->size--;
        return heap->arr[0];
    }

    int root = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;

    heapify(heap, 0);
    return root;
}

void print_heap(
    DHeap *heap 
) {
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->arr[i]);
    }
    printf("\n");
}

int extract_max(
    DHeap *heap
) {
    if (heap->size <= 0) {
        printf("Heap underflow\n");
        return -1;
    }

    if (heap->size == 1) {
        heap->size--;
        return heap->arr[0];
    }

    int max = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;

    heapify(heap, 0);
    return max;
}

void increase_key(
    DHeap *heap,
    int i,
    int k
) {
    if (k < heap->arr[i]) {
        printf("New key is smaller than current key\n");
        return;
    }

    heap->arr[i] = k;

    while (i < 0 && heap->arr[get_parent(heap, i)] < heap->arr[i]) {
        int temp = heap->arr[i];
        heap->arr[i] = heap->arr[get_parent(heap, i)];
        heap->arr[get_parent(heap, i)] = temp;
        i = get_parent(heap, i);
    }
}

int main() {
    int capacity = 10;
    int d = 3;
    DHeap *heap = create_dheap(capacity, d);

    insert(heap, 10);
    insert(heap, 20);
    insert(heap, 30);
    insert(heap, 40);
    insert(heap, 10);
    insert(heap, 20);
    insert(heap, 30);

    printf("Heap: ");
    print_heap(heap);

    printf("Deleted root: %d\n", delete_root(heap));

    printf("Heap: ");
    print_heap(heap);

    printf("Extracted max: %d\n", extract_max(heap));

    printf("Heap after extracting max: ");
    print_heap(heap);

    increase_key(heap, 2, 35);
    printf("Heap after increasing key at index 2 to 35: ");
    print_heap(heap);

    free(heap->arr);
    free(heap);

    return 0;
}