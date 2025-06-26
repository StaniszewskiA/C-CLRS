#ifndef AMORTIZED_ANALYSIS_H
#define AMORTIZED_ANALYSIS_H

#include "../../common.h"
#include "../part_4_commons.h"

// ============================================================================
// CHAPTER 16.1: AMORTIZED ANALYSIS
// ============================================================================

#define MAX_HEAP_SIZE 100

typedef struct {
    int data[MAX_HEAP_SIZE];
    unsigned size;
} MinHeap;

void heapify_down(MinHeap* heap, int idx);
void heapify_up(MinHeap* heap, int idx);
void heap_insert(MinHeap* heap, int val);
int heap_pop(MinHeap* heap);
void heap_multipop(MinHeap* heap, int k);
void print_heap(MinHeap* heap);

#define MAX_BITS 8

typedef struct {
    int bits[MAX_BITS];
    unsigned size;
    int high; // Highest order "on" bit
} BinaryCounter;

void binary_counter_init(BinaryCounter* bCounter);
void binary_counter_increment(BinaryCounter* bCounter);
void binary_counter_reset(BinaryCounter* counter);
void print_counter(BinaryCounter* bCounter);

#define MAX_STACK_SIZE 100

typedef struct {
    int data[MAX_STACK_SIZE];
    int top;
} Stack;

void stack_init(Stack* s);
int stack_is_empty(Stack* s);
void stack_push(Stack* s, int val);
int stack_pop(Stack* s);


typedef struct {
    Stack s1;
    Stack s2;
    int credits;
} CreditsQueue;

void credits_queue_init(CreditsQueue* q);
void credits_enqueue(CreditsQueue* q, int val);
int credits_dequeue(CreditsQueue* q);

#define INITIAL_DMS_CAPACITY 4

typedef struct {
    int* data;
    unsigned size;
    unsigned capacity;
} DynamicMultiset;

DynamicMultiset* dms_init();
void dms_free(DynamicMultiset* dms);
void dms_resize(DynamicMultiset* dms, int newCapacity);
void dms_insert(DynamicMultiset* dms, int val);
int parition(int* arr, int left, int right, int pivotIdx);
int quickselect(int* arr, int left, int right, int k);
void dms_delete_larger_half(DynamicMultiset* dms);
void print_dms(DynamicMultiset* dms);

// ============================================================================
// PROBLEMS
// ============================================================================

uint gray_code(uint i);
void generate_gray_codes(int k);

#define MAX_ARRAYS 20

typedef struct {
    int* data;
    uint size;
    uint capacity;
} DynamicArray;

typedef struct {
    DynamicArray* arrays[MAX_ARRAYS];
    uint k;
} DynamicBinarySearch;

void dynamic_array_init(DynamicArray* arr, uint capacity);
void dbs_init(DynamicBinarySearch* dbs, uint n);
int dbs_binary_search(DynamicArray* arr, int target);
int dbs_search(DynamicBinarySearch* dbs, int target);
void dbs_insert(DynamicBinarySearch* dbs, int val);
void dbs_delete(DynamicBinarySearch* dbs, int val);
void print_dbs(DynamicBinarySearch* dbs);

typedef struct TreeNode {
    int val;
    int size;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* tree_node_init(int val);
void tree_update_size(TreeNode* node);
void tree_inorder_traversal(TreeNode* root, int* nodes, int* idx);
TreeNode* build_balanced_BST(int* nodes, int start, int end);
TreeNode* tree_rebuild(TreeNode* root);

#endif // AMORTIZED_ANALYSIS_H