#ifndef DATA_STRUCTURES_FOR_DISJOINT_SETS_H
#define DATA_STRUCTURES_FOR_DISJOINT_SETS_H

#include "../../common.h"
#include "../part_5_commons.h"

// ============================================================================
// CHAPTER 19.1: DISJOINT SET OPERATIONS
// ============================================================================

#define MAX_VERTICES 100

typedef struct {
    int numVertices;
    int edges[MAX_VERTICES][MAX_VERTICES];
} Graph;

void make_set(int n);
void union_sets(int u, int v);
int find(int u);
int is_same_component(int u, int v);
void connected_components(Graph* g);
void add_edge(Graph* g, int u, int v);

// ============================================================================
// CHAPTER 19.2: LINKED-LIST REPRESENTATION OF DISJOINT SETS
// ============================================================================

typedef struct SetNode {
    int key;
    struct SetNode* next;
    struct Set* set;
} SetNode;

typedef struct Set {
    SetNode* head;
    SetNode* tail;
    int size;
} Set;

Set* make_set_node(SetNode* x);
SetNode* find_set_node(SetNode* x);
Set* union_set_nodes(SetNode* x, SetNode* y);

// ============================================================================
// CHAPTER 19.3: DISJOINT SET FORESTS
// ============================================================================

#define MAX_DISJOINT_SET_SIZE 100

typedef struct {
    int parent[MAX_DISJOINT_SET_SIZE];
    int rank[MAX_DISJOINT_SET_SIZE];
} DisjointSet;

void make_disjoint_set(DisjointSet* ds, int n);
int disjoint_set_find(DisjointSet* ds, int x); 
void disjoint_set_link(DisjointSet* ds, int xRoot, int yRoot);
void union_disjoint_sets(DisjointSet* ds, int x, int y);
void print_disjoint_sets(DisjointSet* ds, int n);

typedef struct Node {
    int *elemPtr;
    struct Node* next;
} Node;

Node* create_node(int* elemPtr);
int find_non_recursive(DisjointSet* ds, int x);

typedef struct Node2 {
    int value;
    struct Node2* parent;
    int rank;
    struct Node2* next;
    struct Node2* tail;
} Node2;

Node2* make_set2(int val);
Node2* find_set2(Node2* x);
void link2(Node2* xRoot, Node2* yRoot);
void union_sets2(Node2* x, Node2* y);
void print_set2(Node2* x);

// ============================================================================
// PROBLEMS
// ============================================================================

typedef struct OfflineDisjointSet {
    int parent;
    int rank;
    int minVal;
    int nextSet;
    int exists;
} OfflineDisjointSet;

void offline_make_set(int i);
int offline_find_set(int i);
void offline_union_sets(int x, int y);
void offline_minimum(int ops[], int n);

typedef struct DeterminantNode {
    struct DeterminantNode* parent;
    int rank;
    int pseudoDepth;
} DeterminantNode;

DeterminantNode* determinant_make_tree();
DeterminantNode* determinant_find_set(DeterminantNode* v, int* depth);
int determinant_find_depth(DeterminantNode* v);
void determinant_graft(DeterminantNode* r, DeterminantNode* v);

typedef struct TarjanDSNode {
    int parent;
    int rank;
    int ancestor;
} TarjanDSNode;

typedef struct ListNode {
    int value;
    struct ListNode* next;
} ListNode;

void tarjan_add_edge(int u, int v);
void tarjan_add_query(int u, int v);
void tarjan_make_set(int u);
int tarjan_find_set(int u);
void tarjan_union_sets(int u, int v);
void tarjan_lca(int u);

#endif // DATA_STRUCTURES_FOR_DISJOINT_SETS_H