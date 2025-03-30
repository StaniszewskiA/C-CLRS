#include <stdio.h>
#include <stdlib.h>

#define EXAMPLE 4

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

    The accounting method - assuming a cost of 2 for push, 0 for pop, 
    and 0 for multipush—we can estimate the overall cost to be O(n).

    The potential method - for an empty heap:
        
        Φ(D_i) >= 0
                = Φ(D_0)

    In case of a push operation:

        Φ(D_i) - Φ(D_{i-1}) = (s + 1) - s = 1

    which yields the amortized cost of: 1 + 1 = 2

    In case of a multipop operation:

        Φ(D_i) - Φ(D_{i-1}) = -k'

    which yields the amortized cost of: k' - k' = 0

    Thus the overall cost of n operations is O(n).
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
    int high; // Highest order "on" bit
} BinaryCounter;

void init_counter(BinaryCounter* bCounter) {
    int i;
    for (i = 0; i < MAX_BITS; i++) bCounter->bits[i] = 0;
    bCounter->size = MAX_BITS;
    bCounter->high = -1;
}

/*
    Aggregate analysis - number of bit modifications can be expressed as:

        sum_(i=0)^(k-1)floor(n/(2^i)) < n*sum_(i=0)^(inf)i/2^i = 2n

    e.g., for n increments, the first bit is modified n times, 
    the second n/2 times, etc. This yields an amortized cost of each 
    operation equal to O(n) / n = O(1).

    The accounting method - let's assume a cost of 1 for modifying a bit. 
    Amortize changing a bit to 1 with an additional 1, yielding an overall 
    amortized cost of 2 for this operation. Then, changing a bit to 0 can 
    be paid for using the accumulated amortization from setting bits to 1. 
    Since every bit is initially 0, the amortization balance never goes 
    negative. This results in an overall cost of O(n).

    The potential method - let's assume that the bCounter data structure's
    potential upon increase is equals to the number of the "on" bits. Let's 
    denote it as b_i. With each increase operation, the potential grows by:

        Φ(D_i) - Φ(D_{i-1}) <= (b_{i - 1} - t_i + 1) - b_{i - 1}
                            = 1 - t_i

    This yields an amortized cost of 2.

    If we execute at least n = Ω(k) increment operations, the overall
    cost will be O(n), despite the initial value of the counter.
*/
void increment_counter(BinaryCounter* bCounter) {
    int carry = 1;
    int i, sum;

    for (i = 0; i < bCounter->size; i++) {
        sum = bCounter->bits[i] + carry;
        bCounter->bits[i] = sum % 2;
        carry = sum / 2;

        if (carry == 0) {
            bCounter->high = i;
            break;
        }
    }

    if (carry) printf("Counter overflow");
}

void reset_counter(BinaryCounter* counter) {
    int i;
    for (int i = counter->high + 1; i < counter->size; i++) 
        counter->bits[i] = 0;
    
    counter->high = -1;
}

void print_counter(BinaryCounter* bCounter) {
    int i;

    printf("Binary Counter: ");
    for (i = bCounter->size - 1; i >= 0; i--) printf("%d", bCounter->bits[i]);
    printf("\n");
}

/*
    16.3-5 - amortized queue implemented with two stacks.
*/
#define MAX_STACK_SIZE 100

typedef struct {
    int data[MAX_STACK_SIZE];
    int top;
} Stack;

void init_stack(Stack* s) {
    s->top = -1;
}

int is_stack_empty(Stack* s) {
    return s->top == -1;
}

void push_to_stack(Stack* s, int val) {
    s->data[++(s->top)] = val;
    printf("   push(%d) real cost = 1\n", val);
}

int pop_from_stack(Stack* s) {
    int val = s->data[(s->top)--];
    printf("   pop() -> %d real cost = 1\n", val);
    return val;
}

/*
    Enqueue yields an amortized cost of 3, and dequeue has a cost of 0. 
    Without amortization, each operation costs 1. 
    Enqueue generates credit for popping and pushing.
*/

typedef struct {
    Stack s1;
    Stack s2;
    int credits;
} Queue;

void init_queue(Queue* q) {
    init_stack(&q->s1);
    init_stack(&q->s2);
    q->credits = 0;
}

void enqueue(Queue* q, int val) {
    printf("Enqueue(%d)\n", val);
    q->credits += 2;
    printf("   Assign amortized cost = 3, saved credits = %d\n", q->credits);
    push_to_stack(&q->s1, val);
}

int dequeue(Queue* q) {
    printf("Dequeue()\n");
    if (is_stack_empty(&q->s2)) {
        while (!is_stack_empty(&q->s1)) {
            printf("   Move from s1 to s2 using 1 credit\n");
            q->credits--;
            int moved = pop_from_stack(&q->s1);
            push_to_stack(&q->s2, moved);
        }
    }

    if (is_stack_empty(&q->s2)) {
        printf("   Queue is empty\n");
        exit(1);
    }

    printf("   Pop from S2 using 1 credit\n");
    q->credits--;
    int result = pop_from_stack(&q->s2);
    printf("   Remaining credits = %d\n", q->credits);

    return result;
}

/*
    16.3-6 - Dynamic Multiset
*/
#define INITIAL_DMS_CAPACITY 4

typedef struct {
    int* data;
    unsigned size;
    unsigned capacity;
} DynamicMultiset;

DynamicMultiset* create_dms() {
    DynamicMultiset* dms = malloc(sizeof(DynamicMultiset));
    dms->data = malloc(INITIAL_DMS_CAPACITY);
    dms->size = 0;
    dms->capacity = INITIAL_DMS_CAPACITY;

    return dms;
}

void free_dms(DynamicMultiset* dms) {
    free(dms->data);
    free(dms);
}

void resize_dms(DynamicMultiset* dms, int newCapacity) {
    dms->data = realloc(dms->data, newCapacity * sizeof(int));
    dms->capacity = newCapacity;
}

void insert_dms(DynamicMultiset* dms, int val) {
    if (dms->size == dms->capacity) resize_dms(dms, dms->capacity * 2);
    dms->data[dms->size++] = val;
}

int parition(int* arr, int left, int right, int pivotIdx) {
    int i;
    
    int pivotVal = arr[pivotIdx];
    swap(&arr[pivotIdx], &arr[right]);
    int storeIdx = left;

    for (i = left; i < right; i++) {
        if (arr[i] < pivotVal) {
            swap(&arr[storeIdx], &arr[i]);
            storeIdx++;
        }
    }
    swap(&arr[right], &arr[storeIdx]);
    return storeIdx;
}

int quickselect(int* arr, int left, int right, int k) {
    if (left == right) return arr[left];

    int pivotIdx = left + rand() % (right - left + 1);
    pivotIdx = parition(arr, left, right, pivotIdx);

    int count = pivotIdx - left + 1;

    if (k == count) return arr[pivotIdx];
    else if (k < count) return quickselect(arr, left, pivotIdx - 1, k);
    else return quickselect(arr, pivotIdx + 1, right, k - count);
}

void delete_larger_half(DynamicMultiset* dms) {
    if (dms->size == 0) return;

    int i, j;

    int k = (dms->size + 1) / 2;
    int* temp = malloc(dms->size * sizeof(int));

    // Copy
    for (i = 0; i < dms->size; i++) temp[i] = dms->data[i];
    
    int threshold = quickselect(temp, 0, dms->size - 1, k);
    free(temp);
    
    j = 0;

    for (i = 0; i < dms->size; i++) 
        if (dms->data[i] <= threshold) dms->data[j++] = dms->data[i];

    dms->size = j;

    if (dms->size <= dms->capacity / 4 && dms->capacity > INITIAL_DMS_CAPACITY)
        resize_dms(dms, dms->capacity / 2);
}

void print_dms(DynamicMultiset* dms) {
    int i;
    printf("Multiset: ");
    for(i = 0; i < dms->size; i++) printf("%d, ", dms->data[i]);
    printf("\n");
}

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

            reset_counter(&bCounter);
            print_counter(&bCounter);

            break;
        }

        case 3: {
            // 16.3-5
            Queue q;
            init_queue(&q);

            enqueue(&q, 10);
            enqueue(&q, 20);
            enqueue(&q, 30);

            printf("Dequeued: %d\n\n", dequeue(&q));
            printf("Dequeued: %d\n\n", dequeue(&q));

            enqueue(&q, 40);
            printf("Dequeued: %d\n\n", dequeue(&q));
            printf("Dequeued: %d\n\n", dequeue(&q));

            break;
        }

        case 4: {
            // 16.3-6 - Dynamic Multiset
            DynamicMultiset* dms = create_dms();

            insert_dms(dms, 5);
            insert_dms(dms, 2);
            insert_dms(dms, 8);
            insert_dms(dms, 1);
            insert_dms(dms, 10);
            insert_dms(dms, 7);

            print_dms(dms);

            delete_larger_half(dms);

            print_dms(dms);

            free_dms(dms);

            break;
        }

        default:
            break;
    }

    return 0;
}