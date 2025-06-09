#ifndef HEAPSORT_H
#define HEAPSORT_H

#include "../../common.h"
#include "../part_2_commons.h"

// ============================================================================
// CHAPTER 6.2: MAINTAING THE HEAP PROPERTY
// ============================================================================
void max_heapify_iterative(int A[], int n, int i);
void build_max_heap(int A[], int n); 

void max_heapify_recursive(int A[], int n, int i);
void build_max_heap_recursive(int A[], int n);

void min_heapify_recursive(int A[], int n, int i);
void build_min_heap_recursive(int A[], int n);

void min_heapify_iterative(int A[], int n, int i);
void build_min_heap_iterative(int A[], int n);

// ============================================================================
// CHAPTER 6.4: HEAPSORT
// ============================================================================

void heapsort(int A[], int n);

// ============================================================================
// CHAPTER 6.5: PRIORITY QUEUES
// ============================================================================

#define QUEUE_SIZE 10

typedef struct {
    int value;
    int order;
} QueueElement;

typedef struct {
    QueueElement *data;
    int size;
    int capacity;
    int counter;
} PriorityQueue;

PriorityQueue* create_queue(int capacity);
int queue_compare_elements(QueueElement a, QueueElement b);
void enqueue(PriorityQueue *pq, int value);
int dequeue(PriorityQueue *pq);
void queue_free(PriorityQueue* pq);

#define MAX_LIST_SIZE 100

typedef struct {
    int value;
    int listIdx;
    int nextIdx;
} HeapNode;

void heapnode_swap(HeapNode* x, HeapNode* y);
void heapnode_min_heapify(HeapNode A[],int n,int i);
void heapnode_build_min_heap(HeapNode A[], int n);
void merge_k_sorted_lists(
    int* lists[],
    int listSizes[],
    int k,
    int* result
);

#define MAX_HEAP_SIZE 100

int max_heap_get_max(int A[], int n);
int max_heap_extract_max(int A[], int *n);
void max_heap_increase_key(int A[], int i, int key);
void max_heap_insert(int A[], int *n, int key);
void max_heap_decrease_key(int A[], int n, int i, int key);
void max_heap_increase_key_insertion(int A[], int i, int key);
void max_heap_delete_element(int A[], int* n, int i);

int min_heap_get_min(int A[], int n);
int min_heap_extract_min(int A[], int *n);
void min_heap_increase_key(int A[], int n, int i, int key);
void min_heap_insert(int A[],int* n, int key);

// ============================================================================
// PROBLEMS
// ============================================================================

void build_max_heap_prim(int A[], int n);

typedef struct {
    int *arr;
    int size;
    int capacity;
    int d;
} DHeap;

DHeap* create_dheap(int capacity, int d);
int dheap_get_left_child(DHeap* heap, int i);
int dheap_get_right_child(DHeap* heap, int i);
int dheap_get_parent(DHeap *heap, int i);
void dheapify(DHeap *heap, int i);
void dheap_insert_key(DHeap *heap, int key);
int dheap_delete_root(DHeap *heap);
void print_dheap(DHeap *heap);
int dheap_extract_max(DHeap *heap);
void dheap_increase_key(DHeap *heap, int i, int k);

#define MAX_ROWS 100
#define MAX_COLS 100

int young_table_extract_min(
    int Y[][MAX_COLS],
    int rows,
    int cols,
    int i,
    int j
);
void young_table_insert_key(
    int Y[][MAX_COLS],
    int i,    
    int j,   
    int key
);
void young_table_check(
    int Y[][MAX_COLS],
    int i,
    int j
);
int young_table_search_key(
    int Y[][MAX_COLS],
    int rows,
    int key
);

#endif // HEAPSORT_H