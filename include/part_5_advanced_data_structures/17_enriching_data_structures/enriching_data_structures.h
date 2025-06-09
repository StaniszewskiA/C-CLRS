#ifndef ENRICHING_DATA_STRUCTURES_H
#define ENRICHING_DATA_STRUCTURES_H

#include "../../common.h"
#include "../part_5_commons.h"

#include "part_3_data_structures/13_red-black_trees/red-black_trees.h"

// ============================================================================
// CHAPTER 17.1: DYNAMIC ORDER STATISTICS
// ============================================================================

RedBlackNode* os_select(RedBlackNode* x, int i, RedBlackNode* nil);
int os_rank(RedBlackTree* T, RedBlackNode* x);
RedBlackNode* os_select_iterative(RedBlackNode* x, int i, RedBlackNode* nil);
int os_key_rank(RedBlackTree* T, RedBlackNode* x, int k);
int count_inversions(RedBlackTree* T, int* arr, int n);

typedef struct {
    double x, y;
    double angle;
} AngledPoint;

double calculate_angle(AngledPoint* p);
int compare_angles(const void *a, const void *b);
int count_intersections(AngledPoint* points, int n);

// ============================================================================
// CHAPTER 17.2: HOW TO ENRICH A DATA STRUCTURE
// ============================================================================

RedBlackNode* rb_tree_find_min(RedBlackTree* T);
RedBlackNode* rb_tree_find_max(RedBlackTree* T);
RedBlackNode* rb_tree_find_successor(RedBlackTree* T, RedBlackNode* x);
RedBlackNode* rb_tree_find_predecessor(RedBlackTree* T, RedBlackNode* x);
int calculate_black_height(RedBlackTree* tree, RedBlackNode* node);
int calculate_depth(RedBlackTree* tree, RedBlackNode* node);

// ============================================================================
// CHAPTER 17.3: INTERVAL TREES
// ============================================================================

typedef struct IntervalRBNode {
    Interval interval;
    int max;
    int color;
    struct IntervalRBNode* left;
    struct IntervalRBNode* right;
    struct IntervalRBNode* parent;
} IntervalRBNode;

typedef struct IntervalRBTree {
    IntervalRBNode* root;
    IntervalRBNode* nil; // sentinel
} IntervalRBTree;

IntervalRBNode* interval_rb_node_init(IntervalRBTree* tree, Interval interval);
IntervalRBTree* interval_rb_tree_init();
void interval_rb_tree_rotate_left(IntervalRBTree* tree, IntervalRBNode* x);
void interval_rb_tree_rotate_right(IntervalRBTree* tree, IntervalRBNode* y);
void interval_rb_insert_fixup(IntervalRBTree* tree, IntervalRBNode* z);
void interval_rb_insert(IntervalRBTree* tree, Interval interval);
void interval_rb_tree_inorder_traversal(IntervalRBNode* root, IntervalRBNode* nil);
int check_overlap(Interval i1, Interval i2);
IntervalRBNode* find_overlap_with_smallest_low(IntervalRBTree* tree, Interval i); // 17.3-2
void find_overlapping_intervals(IntervalRBTree* tree, IntervalRBNode* node, Interval query); // 17.3-3
IntervalRBNode* interval_search_exactly(IntervalRBTree* tree, Interval i); // 17.3-4

typedef struct MinGapRBNode {
    int key;
    int color;
    struct MinGapRBNode* left;
    struct MinGapRBNode* right;
    struct MinGapRBNode* parent;
    struct MinGapRBNode* predecessor;
    struct MinGapRBNode* successor;
} MinGapRBNode;

typedef struct MinGapRBTree {
    MinGapRBNode* root; 
    MinGapRBNode* nil; // sentinel 
    int minGap; // 17.3-5
} MinGapRBTree;

MinGapRBNode* min_gap_rb_node_init(MinGapRBTree* T, int key);
MinGapRBTree* min_gap_rb_tree_init();
void min_gap_rb_tree_left_rotate(MinGapRBTree* T, MinGapRBNode* x);
void min_gap_rb_tree_right_rotate(MinGapRBTree* T, MinGapRBNode* y);
void min_gap_rb_tree_insert_fixup(MinGapRBTree* tree, MinGapRBNode* z);
void min_gap_rb_tree_fixup(MinGapRBTree* T, MinGapRBNode* z);
void min_gap_rb_tree_insert(MinGapRBTree* T, int key);
MinGapRBNode* min_gap_rb_node_find_successor(MinGapRBNode* x);
MinGapRBNode* min_gap_rb_node_find_predecessor(MinGapRBNode* x);
void min_gap_rb_tree_update_min_gap(MinGapRBTree* tree, MinGapRBNode* node);
int min_gap_rb_tree_get_min_gap(MinGapRBTree* tree);

typedef struct RectRBNode {
    int y_min;
    int y_max;
    int x_min;
    int x_max;
    int color;
    struct RectRBNode* left;
    struct RectRBNode* right;
    struct RectRBNode* parent;
} RectRBNode;

typedef struct RectRBTree {
    RectRBNode* root;
    RectRBNode* nil; 
} RectRBTree;

typedef struct Rect {
    int x_min;
    int x_max;
    int y_min;
    int y_max;
} Rect;

typedef struct Event {
    int x;
    int type;
    int y_min;
    int y_max;
    int x_min;
    int x_max;
} Event;

RectRBNode* rect_rb_node_init(
    RectRBTree* T, 
    int y_min, 
    int y_max, 
    int x_min, 
    int x_max
);
RectRBTree* rect_rb_tree_init();
void rect_rb_tree_left_rotate(RectRBTree* T, RectRBNode* x);
void rect_rb_tree_right_rotate(RectRBTree* T, RectRBNode* y);
void rect_rb_insert_fixup(RectRBTree* T, RectRBNode* z);
void rect_rb_insert(
    RectRBTree* tree, 
    int x_min, 
    int x_max, 
    int y_min, 
    int y_max
);
int rect_overlap(RectRBNode* node, int y_min, int y_max);
int compare_event(const void* a, const void* b);
int check_rect_overlap(Rect rects[], int n);
void rect_rb_tree_transplant(RectRBTree *tree, RectRBNode *u, RectRBNode *v);
void rect_rb_delete_fixup(RectRBTree *tree, RectRBNode *x);
RectRBNode* rect_rb_tree_get_min(RectRBTree *tree, RectRBNode *node);
void rect_rb_tree_delete(RectRBTree *tree, RectRBNode *z);

// ============================================================================
// PROBLEMS
// ============================================================================

typedef struct IntersectionRBNode {
    int endpoint;
    int delta;
    int intersections;
    int maxIntersections;
    int color;
    struct IntersectionRBNode* left;
    struct IntersectionRBNode* right;
    struct IntersectionRBNode* parent;
} IntersectionRBNode;

typedef struct IntersectionRBTree {
    IntersectionRBNode* root;
    IntersectionRBNode* nil; // sentinel
} IntersectionRBTree;

IntersectionRBNode* intersection_rb_node_init(IntersectionRBTree* tree, int endpoint, int delta);
IntersectionRBTree* create_rbtree();
void intersection_rb_tree_left_rotate(IntersectionRBTree *tree, IntersectionRBNode *x);
void intersection_rb_tree_right_rotate(IntersectionRBTree *tree, IntersectionRBNode *y);
void intersection_rb_tree_insert_fixup(IntersectionRBTree *tree, IntersectionRBNode *z);
void intersection_rb_tree_insert(IntersectionRBTree *tree, int endpoint, int delta);
void intersection_rb_tree_update_intersections(IntersectionRBTree* tree, IntersectionRBNode* node);
int intersection_rb_tree_find_max_intersections(IntersectionRBTree *tree);

typedef struct JRBNode {
    int key;
    int size;
    int color;
    struct JRBNode* left;
    struct JRBNode* right;
    struct JRBNode* parent;
    struct JRBNode* successor;
    struct JRBNode* predecessor;
} JRBNode;

typedef struct JRBTree {
    JRBNode* root;
    JRBNode* nil; // sentinel
} JRBTree;

size_t jrb_tree_get_size(JRBTree* tree, JRBNode* node);
void jrb_tree_update_size(JRBTree* tree, JRBNode* node);
JRBNode* jrb_node_init(JRBTree* tree, int key);
JRBTree* jrb_tree_init();
void jrb_tree_left_rotate(JRBTree* tree, JRBNode* x);
void jrb_tree_right_rotate(JRBTree* tree, JRBNode* y);
void jrb_tree_insert_fixup(JRBTree* tree, JRBNode* z);
void jrb_tree_insert(JRBTree* tree, int key);
void jrb_tree_transplant(JRBTree* tree, JRBNode* u, JRBNode* v);
void jrb_tree_delete_fixup(JRBTree* tree, JRBNode* x);
void jrb_tree_delete_node(JRBTree* tree, JRBNode* z);
JRBNode* jrb_node_find_successor(JRBNode* x);
JRBNode* jrb_node_find_predecessor(JRBNode* x);
void josephus(int n, int m);

void print_victims(int n, int k);

#endif // ENRICHING_DATA_STRUCTURES_H