#ifndef HEAPSORT_H
#define HEAPSORT_H

#include "../../common.h"
#include "../part_3_commons.h"

// ============================================================================
// CHAPTER 10.1: STACKS AND QUEUES
// ============================================================================

#define MAX_STACK_SIZE 10

typedef struct {
    int arr[MAX_STACK_SIZE];
    int topT;
    int topR;
} TwoStacks;

void two_stacks_init(TwoStacks* stacks);
void two_stacks_push_t(TwoStacks* stacks, int x);
void two_stacks_push_r(TwoStacks* stacks, int x);
int two_stacks_pop_t(TwoStacks* stacks);
int two_stacks_pop_r(TwoStacks* stacks);

typedef struct {
    int arr[MAX_STACK_SIZE];
    int front;
    int rear;
    int size;
} Queue;

void queue_init(Queue* q);
int queue_is_empty(Queue* q);
int queue_is_full(Queue* q);
void enqueue(Queue *q, int val);
int dequeue(Queue *q);
void print_queue(Queue *q);

typedef struct {
    int arr[MAX_STACK_SIZE];
    int front;
    int rear;
    int size;
} Deque;

void deque_init(Deque *dq);
int deque_is_empty(Deque *dq);
int deque_is_full(Deque *dq);
void enqueue_front(Deque *dq, int x);
void enqueue_rear(Deque *dq, int x);
int dequeue_front(Deque *dq);
int dequeue_rear(Deque *dq);
void deque_print(Deque *dq);
int deque_peek_front(Deque* dq);
int deque_peek_rear(Deque* dq);
int deque_get_size(Deque* dq);
void print_deque(Deque* dq);
void deque_delete(Deque* dq);

typedef struct {
    int arr[MAX_STACK_SIZE];
    int top;
} Stack;

void stack_init(Stack *s);
int stack_is_empty(Stack *s);
int stack_is_full(Stack *s);
void stack_push(Stack *s, int x);
int stack_pop(Stack *s);
int stack_peek(Stack *s);
int stack_get_size(Stack* s);
void print_stack(Stack* s);

typedef struct {
    Stack s1;
    Stack s2;
} QueueWithStacks;

void queue_with_stack_init(QueueWithStacks *qws);
void queue_with_stacks_enqueue(QueueWithStacks *qws, int x);
int queue_with_stacks_dequeque(QueueWithStacks *qws);

typedef struct {
    Queue q1;
    Queue q2;
} StackWithQueues;

void stack_with_queues_init(StackWithQueues* swq);
void stack_with_queues_push(StackWithQueues* swq, int x);
int stack_with_queues_pop(StackWithQueues* swq);

// ============================================================================
// CHAPTER 10.2: LINKED LISTS
// ============================================================================

typedef struct Node {
    int data;
    struct Node* next;
} SinglyNode;

SinglyNode* singly_node_create(int data);
void singly_list_insert_at_front(SinglyNode** head, int x);
void singly_list_insert_at_idx(SinglyNode** head, int x, int idx);
void singly_list_delete_head(SinglyNode** head);
void singly_list_delete_val(SinglyNode** head, int val);
void singly_list_delete_at_idx(SinglyNode** head, int idx);
void singly_list_delete(SinglyNode** head);
void print_singly_list(SinglyNode *head);
void singly_list_reverse(SinglyNode** head);

typedef struct DoublyNode {
    int data;
    struct DoublyNode* next;
    struct DoublyNode* prev;
} DoublyNode;

DoublyNode* doubly_node_create(int x);
void doubly_list_insert_at_front(DoublyNode** head, int x);
void doubly_list_insert_at_idx(DoublyNode** head, int idx, int x);
void doubly_list_delete_head(DoublyNode** head);
void doubly_list_delete_val(DoublyNode** head, int val);
void doubly_list_delete_at_idx(DoublyNode **head, int idx);
void doubly_list_delete(DoublyNode** head);
void print_doubly_list(DoublyNode *head);

DoublyNode* doubly_list_create_sentinel();
void sentinel_doubly_list_insert_at_front(DoublyNode* sentinel, int x);
void sentinel_doubly_list_insert_at_idx(DoublyNode* sentinel, int idx, int x);
void sentinel_doubly_list_delete_head(DoublyNode* sentinel);
void sentinel_doubly_list_delete_val(DoublyNode* sentinel, int val);
void sentinel_doubly_list_delete_at_idx(DoublyNode* sentinel, int idx);
void sentinel_doubly_list_delete(DoublyNode* sentinel);
void sentinel_print_doubly_list(DoublyNode* sentinel);
void doubly_lists_union(DoublyNode* l1, DoublyNode* l2);

typedef struct XorNode {
    int key;
    struct XorNode* np;
} XorNode;

typedef struct XorList {
    XorNode* head;
    XorNode* nil;
} XorList;

XorNode* xor(XorNode* a, XorNode* b);
void xor_list_init(XorList* L);
XorNode* xor_list_search(XorList* L, int k);
void xor_list_insert(XorList* L, int k);
void xor_list_delete(XorList* L, int k);
void print_xor_list(XorList* L);

// ============================================================================
// CHAPTER 10.4: REPRESENTING ROOTED TREES
// ============================================================================

typedef struct TreeNode {
    int key;
    struct TreeNode* left;
    struct TreeNode* right;
    struct TreeNode* parent;
} TreeNode;

TreeNode* tree_node_create(int key, TreeNode* parent);
void tree_node_free(TreeNode* node);
void tree_free(TreeNode* root);
void print_tree(TreeNode* root);

typedef struct TreeStackNode {
    TreeNode* treeNode;
    struct TreeStackNode* next; 
} TreeStackNode;

TreeStackNode* tree_stack_push(TreeStackNode* top, TreeNode* treeNode);
TreeStackNode* tree_stack_pop(TreeStackNode* top, TreeNode** treeNode);
void print_tree_iterative(TreeNode* root);
void print_tree_recursive(TreeNode* root);

typedef struct DepthTreeNode {
    int key;
    struct DepthTreeNode* left;
    struct DepthTreeNode* right;
    int b; // depth % 2
} DepthTreeNode;

DepthTreeNode* create_depth_tree_node(int key, int b);
void depth_tree_free(DepthTreeNode* root);
void print_depth_tree(DepthTreeNode* root);
void create_sample_depth_tree(DepthTreeNode* root, int depth, int maxDepth);
void depth_tree_traverse(DepthTreeNode* root, int parB);
void depth_tree_free(DepthTreeNode* root);

// ============================================================================
// PROBLEMS
// ============================================================================

typedef struct BinomialNode {
    int key;
    int degree;
    struct BinomialNode* parent;
    struct BinomialNode* child;
    struct BinomialNode* sibling;
} BinomialNode;

typedef struct BinomialHeap {
    BinomialNode* head;
} BinomialHeap;

BinomialNode* binomial_node_create(int key);
BinomialNode* binomial_node_merge_trees(BinomialNode* b1, BinomialNode* b2);
BinomialNode* binomial_node_merge_heaps(BinomialNode* h1, BinomialNode* h2);
BinomialHeap* binomial_node_union_heaps(BinomialHeap* h1, BinomialHeap* h2);
void binomial_heap_insert(BinomialHeap* heap, int key);
int binomial_heap_extract_min(BinomialHeap* heap);
void print_binomial_heap(BinomialNode* node);

typedef struct SimpleNode {
    int key;
    int next;
} SimpleNode;

int compact_list_search(SimpleNode L[], int head, int n, int k);
int compact_list_search_prim(SimpleNode L[], int head, int n, int k, int t);

#endif // HEAPSORT_H