#include "part_4_advanced_design_and_analysis_techniques/16_amortized_analysis/amortized_analysis.h"

void heapify_down(MinHeap* heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < (int)heap->size && heap->data[left] < heap->data[smallest])
        smallest = left;

    if (right < (int)heap->size && heap->data[right] < heap->data[smallest])
        smallest = right;

    if (smallest != idx) {
        SWAP_INT(heap->data[idx], heap->data[smallest]);
        heapify_down(heap, smallest);
    }
}

void heapify_up(MinHeap* heap, int idx) {
    int parentIdx = (idx - 1) / 2;

    if (idx > 0 && heap->data[idx] < heap->data[parentIdx]) {
        SWAP_INT(heap->data[idx], heap->data[parentIdx]);
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
    printf("Heap: ");
    for (int i = 0; i < (int)heap->size; i++) printf("%d ", heap->data[i]);
    printf("\n");
}

/*
    Example 2 - Binary Counter
*/
void binary_counter_init(BinaryCounter* bCounter) {
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
void binary_counter_increment(BinaryCounter* bCounter) {
    int i;
    for (i = 0; i < (int)bCounter->size; i++) {
        if (bCounter->bits[i] == 0) {
            bCounter->bits[i] = 1;
            break;
        } else {
            bCounter->bits[i] = 0;
        }
    }
    
    if (i > bCounter->high) {
        bCounter->high = i;
    }
}

void binary_counter_reset(BinaryCounter* counter) {
    for (int i = counter->high + 1; i < (int)counter->size; i++)
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
void stack_init(Stack* s) {
    s->top = -1;
}

int stack_is_empty(Stack* s) {
    return s->top == -1;
}

void stack_push(Stack* s, int val) {
    s->data[++(s->top)] = val;
    printf("   push(%d) real cost = 1\n", val);
}

int stack_pop(Stack* s) {
    int val = s->data[(s->top)--];
    printf("   pop() -> %d real cost = 1\n", val);
    return val;
}

/*
    Enqueue yields an amortized cost of 3, and credits_dequeue has a cost of 0. 
    Without amortization, each operation costs 1. 
    Enqueue generates credit for popping and pushing.
*/
void credits_queue_init(CreditsQueue* q) {
    stack_init(&q->s1);
    stack_init(&q->s2);
    q->credits = 0;
}

void credits_enqueue(CreditsQueue* q, int val) {
    printf("Enqueue(%d)\n", val);
    q->credits += 2;
    printf("   Assign amortized cost = 3, saved credits = %d\n", q->credits);
    stack_push(&q->s1, val);
}

int credits_dequeue(CreditsQueue* q) {
    printf("Dequeue()\n");
    if (stack_is_empty(&q->s2)) {
        while (!stack_is_empty(&q->s1)) {
            printf("   Move from s1 to s2 using 1 credit\n");
            q->credits--;
            int moved = stack_pop(&q->s1);
            stack_push(&q->s2, moved);
        }
    }

    if (stack_is_empty(&q->s2)) {
        printf("   CreditsQueue is empty\n");
        exit(1);
    }

    printf("   Pop from S2 using 1 credit\n");
    q->credits--;
    int result = stack_pop(&q->s2);
    printf("   Remaining credits = %d\n", q->credits);

    return result;
}

/*
    16.3-6 - Dynamic Multiset
*/
DynamicMultiset* dms_init() {
    DynamicMultiset* dms = malloc(sizeof(DynamicMultiset));
    dms->data = malloc(INITIAL_DMS_CAPACITY);
    dms->size = 0;
    dms->capacity = INITIAL_DMS_CAPACITY;

    return dms;
}

void dms_free(DynamicMultiset* dms) {
    free(dms->data);
    free(dms);
}

void dms_resize(DynamicMultiset* dms, int newCapacity) {
    dms->data = realloc(dms->data, newCapacity * sizeof(int));
    dms->capacity = newCapacity;
}

void dms_insert(DynamicMultiset* dms, int val) {
    if (dms->size == dms->capacity) dms_resize(dms, dms->capacity * 2);
    dms->data[dms->size++] = val;
}

int parition(int* arr, int left, int right, int pivotIdx) {
    int i;
    
    int pivotVal = arr[pivotIdx];
    SWAP_INT(arr[pivotIdx], arr[right]);
    int storeIdx = left;

    for (i = left; i < right; i++) {
        if (arr[i] < pivotVal) {
            SWAP_INT(arr[storeIdx], arr[i]);
            storeIdx++;
        }
    }
    SWAP_INT(arr[right], arr[storeIdx]);
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

void dms_delete_larger_half(DynamicMultiset* dms) {
    if (dms->size <= 1) return;

    int* temp = malloc(dms->size * sizeof(int));
    int i;
    
    for (i = 0; i < (int)dms->size; i++) temp[i] = dms->data[i];

    unsigned median_idx = dms->size / 2;
    int median = quickselect(temp, 0, dms->size - 1, median_idx);

    dms->size = 0;
    for (i = 0; i < (int)(median_idx + 1); i++)
        if (temp[i] <= median) dms->data[dms->size++] = temp[i];

    free(temp);
}

void print_dms(DynamicMultiset* dms) {
    printf("Multiset: ");
    for(int i = 0; i < (int)dms->size; i++) printf("%d, ", dms->data[i]);
    printf("\n");
}
