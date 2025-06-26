#include "part_2_sorting_and_order_statistics/6_heapsort/heapsort.h"

PriorityQueue* create_queue(int capacity) {
    PriorityQueue *pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->data = (QueueElement*)malloc(capacity * sizeof(QueueElement));
    pq->size = 0;
    pq->capacity = capacity;
    pq->counter = 0;
    return pq;
}

int queue_compare_elements(QueueElement a, QueueElement b) {
    return a.order - b.order;  
}

void enqueue(PriorityQueue *pq, int value) {
    if (pq->size == pq->capacity) {
        printf("Queue is full!\n");
        return;
    }
    
    int i = pq->size++;
    pq->data[i].value = value;
    pq->data[i].order = pq->counter++;

    while (i > 0 && queue_compare_elements(pq->data[i], pq->data[(i - 1) / 2]) < 0) {
        QueueElement temp = pq->data[i];
        pq->data[i] = pq->data[(i - 1) / 2];
        pq->data[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

int dequeue(PriorityQueue *pq) {
    if (pq->size == 0) {
        printf("Queue is empty!\n");
        return -1;
    }

    int value = pq->data[0].value;
    pq->data[0] = pq->data[--pq->size];

    int i = 0;
    while (2 * i + 1 < pq->size) {
        int left = 2 * i + 1, right = 2 * i + 2, min = left;
        if (right < pq->size && queue_compare_elements(pq->data[right], pq->data[left]) < 0)
            min = right;
        if (queue_compare_elements(pq->data[i], pq->data[min]) <= 0)
            break;
        QueueElement temp = pq->data[i];
        pq->data[i] = pq->data[min];
        pq->data[min] = temp;
        i = min;
    }

    return value;
}

void queue_free(PriorityQueue* pq) {
    free(pq->data);
    free(pq);
}

void heapnode_swap(HeapNode *x, HeapNode *y) {
    HeapNode temp = *x;
    *x = *y;
    *y = temp;
}

void heapnode_min_heapify(HeapNode A[],int n,int i) {
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

        heapnode_swap(&A[i], &A[smallest]);
        i = smallest; 
    }
}

void heapnode_build_min_heap(HeapNode A[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) heapnode_min_heapify(A, n, i);
}

void merge_k_sorted_lists(
    int* lists[],
    int listSizes[],
    int k,
    int* result
) {
    HeapNode heap[MAX_LIST_SIZE];
    int heapSize = k;
    int resultIdx = 0;

    for (int i = 0; i < k; i++) {
        if (listSizes[i] > 0) {
            heap[i].value = lists[i][0];
            heap[i].listIdx = i;
            heap[i].nextIdx = 1;
        }
    }

    heapnode_build_min_heap(heap, heapSize);

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

        heapnode_min_heapify(heap, heapSize, 0);
    }
}

int max_heap_get_max(int A[], int n) {
    if (n < 1) {
        printf("Heap underflow! No elements in heap.\n");
        return 0;
    }
    return A[0];
}

int max_heap_extract_max(int A[], int *n) {
    if (*n < 1) {
        printf("Heap underflow! Cannot extract from an empty heap.\n");
        return 0;
    }

    int max = max_heap_get_max(A, *n);
    A[0] = A[--(*n)];
    max_heapify_iterative(A, *n, 0);

    return max;
}

void max_heap_increase_key(int A[], int i, int key) {
    if (key < A[i]) {
        printf("New key is smaller than current key!\n");
        return;
    }

    A[i] = key;
    while (i > 0 && A[(i - 1) / 2] < A[i]) {
        SWAP_INT(A[i], A[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void max_heap_insert(int A[], int *n, int key) {
    if (*n >= MAX_SIZE) {
        printf("Heap overflow! Cannot insert more elements.\n");
        return;
    }

    (*n)++;
    A[*n - 1] = INT_MIN;
    max_heap_increase_key(A, *n - 1, key);
}

void max_heap_decrease_key(int A[], int n, int i, int key) {
    if (i < 0 || i >= n) {
        printf("Index out of bounds!\n");
        return;
    }
    if (key > A[i]) {
        printf("New key is larger than current key!\n");
        return;
    }
    A[i] = key;
    max_heapify_iterative(A, n, i);
}

void max_heap_increase_key_insertion(int A[], int i, int key) {
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

void max_heap_delete_element(int A[], int* n, int i) {
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
        max_heapify_iterative(A, *n, i);
    }
}

int min_heap_get_min(int A[], int n) {
    if (n < 1) {
        printf("Heap underflow! No elements in heap.\n");
        return 0;
    }
    return A[0];
}

int min_heap_extract_min(int A[], int* n) {
    if (*n < 1) {
        printf("Heap underflow! Cannot extract from an empty heap.\n");
        return 0;
    }

    int min = min_heap_get_min(A, *n);
    A[0] = A[--(*n)];
    min_heapify_iterative(A, *n, 0);

    return min;
}

void min_heap_increase_key(int A[], int n, int i, int key) {
    if (key < A[i]) {
        printf("New key is smaller than current key!\n");
        return;
    }

    A[i] = key;
    min_heapify_iterative(A, n, i);
}

void min_heap_insert(int A[], int* n, int key) {
    if (*n >= MAX_SIZE) {
        printf("Heap overflow! Cannot insert more elements.\n");
        return;
    }

    (*n)++;
    A[*n - 1] = INT_MIN;
    min_heap_increase_key(A, *n, *n - 1, key);
}