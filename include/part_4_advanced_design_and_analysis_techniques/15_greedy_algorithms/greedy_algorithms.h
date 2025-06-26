#ifndef GREEDY_ALGORITHMS_H
#define GREEDY_ALGORITHMS_H

#include "../../common.h"
#include "../part_4_commons.h"

// ============================================================================
// CHAPTER 15.1: ACTIVITY SELECTION PROBLEM
// ============================================================================

#define MAX_N 100

void recursive_activity_selector(int s[], int f[], int k, int n);
void greedy_activity_selector(int s[], int f[], int n);

void print_activities(int i, int j);
void dynamic_activity_selector(int s[], int f[], int n);

typedef struct Activity {
    int start, end;
} Activity; 

int compare_activities(const void *a, const void *b);
void max_halls(Activity activities[], int n);

typedef struct ValuedActivity {
    int start, end, value;
} ValuedActivity;

int compare_activities_end(const void* a, const void* b);
int activities_binary_search(ValuedActivity activities[], int idx);
int max_activity_value(ValuedActivity activities[], int n);

// ============================================================================
// CHAPTER 15.2: ELEMENTS OF GREEDY STRATEGY
// ============================================================================

typedef struct KnapsackItem {
    int value;
    int weight;
} KnapsackItem;

int discrete_knapsack(int W, KnapsackItem items[], int n);
int compare2(const void* a, const void* b);
int min_intervals(double points[], int n);

typedef struct FracItem {
    // KnapsackItem with fractional values
    double value;
    double weight;
} FracItem;

double vw_ratio(FracItem item);
int compare_wv(const void* a, const void* b);
FracItem select_median_frac(FracItem arr[], int low, int high);
double fractional_knapsack(FracItem items[], int n, int W);

// ============================================================================
// CHAPTER 15.3: HUFFMAN CODES
// ============================================================================

#define MAX_TREE_H 100

typedef struct MinHeapNode {
    char data;
    int freq;
    struct MinHeapNode *left, *right;
} MinHeapNode;

typedef struct MinHeap {
    int size;
    int capacity;
    MinHeapNode** nodes;
} MinHeap;

MinHeapNode* min_heap_create_node(char data, unsigned freq);
MinHeap* min_heap_create(unsigned capacity);
void min_heap_swap_nodes(MinHeapNode** a, MinHeapNode** b);
void min_heapify(MinHeap* minHeap, int idx);
int min_heap_is_size_one(MinHeap* minHeap);
MinHeapNode* min_heap_extract_min(MinHeap* minHeap);
void min_heap_insert(MinHeap* minHeap, MinHeapNode* minHeapNode);
void min_heapbuild(MinHeap* minHeap);
int min_heap_node_is_leaf(MinHeapNode* root);
MinHeap* min_heap_create_and_build(char data[],  unsigned freqs[], unsigned size);
MinHeapNode* huffman_tree_build(char data[], unsigned freqs[], unsigned size);
void print_huffman_codes(MinHeapNode* root, int arr[], int top);
void huffman_codes(char data[], unsigned freqs[], unsigned size);

// ============================================================================
// CHAPTER 15.4: OFF-LINE CACHING
// ============================================================================

#define Q_CAPACITY 4
#define HASH_CAPACITY 10

typedef struct PagedNode {
    struct PagedNode *prev, *next;
    unsigned pageNum;
} PagedNode;

typedef struct Queue {
    unsigned count;
    unsigned numOfFrames;
    PagedNode *front, *rear;
} Queue;

typedef struct Hash {
    int capacity;
    PagedNode** nodeArray;
} Hash;

PagedNode* paged_node_create(unsigned pageNum);
Queue* queue_init(int numOfFrames);
Hash* hash_init(int capacity);
int are_all_frames_full(Queue* q);
int queue_is_empty(Queue* q);
void dequeue(Queue* q);
void enqueue(Queue* q, Hash* hash, unsigned pageNum);
void ref_page(Queue* q, Hash* hash, unsigned pageNum);

// ============================================================================
// PROBLEMS
// ============================================================================

void make_change_greedy(int n);
void make_change_optimal(int denoms[], int k, int n);

typedef struct {
    int id;
    int pTime; // Abb. for processing time
} Task;

int compare_tasks(const void* a, const void* b);
void schedule_tasks(Task tasks[], int n);

typedef struct {
    int id;
    int pTime;
    int rTime; // Abb. for release time
} OnlineTask;

int compare_tasks_online_p_times(const void* a, const void* b);
int compare_tasks_online_r_times(const void* a, const void* b);
void schedule_online_tasks(OnlineTask tasks[], int n);

#endif // GREEDY_ALGORITHMS_H