#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TASK 6

#define RED 0
#define BLACK 1

typedef unsigned int uint;

#pragma region INTERVAL-RB

typedef struct {
    int low, high;
} Interval;

typedef struct IntervalRBNode {
    Interval interval;
    uint max;
    int color;
    struct IntervalRBNode* left;
    struct IntervalRBNode* right;
    struct IntervalRBNode* parent;
} IntervalRBNode;

typedef struct IntervalRBTree {
    IntervalRBNode* root;
    IntervalRBNode* nil; // sentinel
} IntervalRBTree;


// Interval RBT
IntervalRBNode* create_intervalRBNode(IntervalRBTree* tree, Interval interval);
IntervalRBTree* create_intervalRBTree();
int max3(int a, int b, int c);
void interval_left_rotate(IntervalRBTree* tree, IntervalRBNode* x);
void interval_right_rotate(IntervalRBTree* tree, IntervalRBNode* y);
void interval_rb_insert_fixup(IntervalRBTree* tree, IntervalRBNode* z);
void interval_rb_insert(IntervalRBTree* tree, Interval interval);
void inorder_traversal(IntervalRBNode* root, IntervalRBNode* nil);
int check_overlap(Interval i1, Interval i2);
IntervalRBNode* find_overlap_with_smallest_low(IntervalRBTree* tree, Interval i); // 17.3-2
void find_overlapping_intervals(IntervalRBTree* tree, IntervalRBNode* node, Interval query); // 17.3-3
IntervalRBNode* interval_search_exactly(IntervalRBTree* tree, Interval i); // 17.3-4

IntervalRBNode* create_intervalRBNode(IntervalRBTree* tree, Interval interval) {
    IntervalRBNode* x = (IntervalRBNode*)malloc(sizeof(IntervalRBNode));
    x->interval = interval;
    x->max = interval.high;
    x->color = RED;
    x->left = tree->nil;
    x->right = tree->nil;
    x->parent = tree->nil;
    printf("Created a IntervalRBNode representing an interval of (%d, %d)\n", 
        interval.low, interval.high);
    return x;
}

IntervalRBTree* create_intervalRBTree() {
    IntervalRBTree *tree = (IntervalRBTree*)malloc(sizeof(IntervalRBTree));
    tree->nil = (IntervalRBNode*)malloc(sizeof(IntervalRBNode));
    tree->nil->color = BLACK;
    tree->nil->max = 0;
    tree->nil->left = tree->nil;
    tree->nil->right = tree->nil;
    tree->nil->parent  = tree->nil;
    tree->root = tree->nil;
    printf("Successfully created the IntervalRBTree\n");
    return tree;
}

int max3(int a, int b, int c) {
    return (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);
}

void interval_left_rotate(IntervalRBTree* tree, IntervalRBNode* x) {
    IntervalRBNode* y = x->right;
    x->right = y->left;
    if (y->left != tree->nil) y->left->parent = x;
    y->parent = x->parent;

    if (x->parent == tree->nil) tree->root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;

    y->left = x;
    x->parent = y;

    // 17.3-1
    x->max = max3(x->interval.high, x->left->max, x->right->max);
    if (x->max < x->interval.high) x->max = x->interval.high;

    y->max = max3(y->interval.high, y->left->max, y->right->max);
    if (y->max < y->interval.high) y->max = y->interval.high;
}

void interval_right_rotate(IntervalRBTree* tree, IntervalRBNode* y) {
    IntervalRBNode* x = y->left;
    y->left = x->right;
    if (y->left != tree->nil) y->left->parent = y;

    x->parent = y->parent;

    if (y->parent == tree->nil) tree->root = x;
    else if (y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;

    x->right = y;
    y->parent = x;

    // 17.3-1
    y->max = (y->left->max > y->right->max) ? y->left->max : y->right->max;
    if (y->max < y->interval.high) y->max = y->interval.high;
    
    x->max = (x->left->max > x->right->max) ? x->left->max : x->right->max;
    if (x->max < x->interval.high) x->max = x->interval.high;
}

void interval_rb_insert_fixup(IntervalRBTree *tree, IntervalRBNode *z) {
    while (z->parent->color == RED) {
        IntervalRBNode *y;
        if (z->parent == z->parent->parent->left) {
            y = z->parent->parent->right;
            if (y->color == RED) {  
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {  
                    z = z->parent;
                    interval_left_rotate(tree, z);
                }
                z->parent->color = BLACK;  
                z->parent->parent->color = RED;
                interval_right_rotate(tree, z->parent->parent);
            }
        } else {
            y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    interval_right_rotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                interval_left_rotate(tree, z->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}

void interval_rb_insert(IntervalRBTree* tree, Interval interval) {
    IntervalRBNode* z = create_intervalRBNode(tree, interval);
    IntervalRBNode* x = tree->root;
    IntervalRBNode* y = tree->nil;

    while (x != tree->nil) {
        y = x;
        if (interval.low < x->interval.low) x = x->left;
        else x = x->right;
    }

    z->parent = y;

    // 17.3-4
    if (TASK == 4) {
        if (y == tree->nil) tree->root = z;
        else if (z->interval.low < y->interval.low 
            || (z->interval.low == y->interval.low 
                && z->interval.high < y->interval.high)) y->left = z;
        else y->right = z;
    } else {
        if (y == tree->nil) tree->root = z;
        else if (interval.low < y->interval.low) y->left = z;
        else y->right = z;
    }
    

    interval_rb_insert_fixup(tree, z);

    while (y != tree->nil) {
        y->max = max3(y->interval.high, y->left->max, y->right->max);
        y = y->parent;
    }
}

void inorder_traversal(IntervalRBNode* root, IntervalRBNode* nil) {
    if (root == nil) return;
    inorder_traversal(root->left, nil);
    printf("[%d, %d] max = %d | Color = %s\n", 
        root->interval.low, 
        root->interval.high, 
        root->max, 
        root->color ? "BLACK" : "RED"
    );
    inorder_traversal(root->right, nil);
}

int check_overlap(Interval i1, Interval i2) {
    return (i1.low <= i1.high) && (i2.low <= i1.high);
}

/*
    17.3-2
*/
IntervalRBNode* find_overlap_with_smallest_low(IntervalRBTree* tree, Interval i) {
    IntervalRBNode* curr = tree->root;
    IntervalRBNode* best = tree->nil;

    while (curr != tree->nil) {
        if (check_overlap(curr->interval, i)) {
            if (best == tree->nil || curr->interval.low < best->interval.low)
                best = curr;
        }

        // Go down the tree
        if (curr->left != tree->nil && curr->left->max >= i.low) 
            curr = curr->left;
        else curr = curr->right;
    }

    return best;
}

/*
    17.3-3

    O(min(n, k*log(n)))
*/
void find_overlapping_intervals(IntervalRBTree* tree, IntervalRBNode* node, Interval query) {
    if (node == tree->nil) return;

    if (check_overlap(node->interval, query)) 
        printf("Found overlapping interval: [%d, %d]\n", 
            node->interval.low, node->interval.high);

    if (node->left != tree->nil && node->left->max >= query.low)
        find_overlapping_intervals(tree, node->left, query);

    find_overlapping_intervals(tree, node->right, query);
}

/*
    17.3-4
*/
IntervalRBNode* interval_search_exactly(IntervalRBTree* tree, Interval i) {
    IntervalRBNode* x = tree->root;

    while (x != tree->nil) {
        if (i.low == x->interval.low && i.high == x->interval.high) return x;
        else if (i.low < x->interval.low 
            || (i.low == x->interval.low 
                && i.high < x->interval.high)) x = x->left;
        else x = x->right;
    }

    return tree->nil;
}

#pragma endregion INTERVAL-RB

#pragma region MIN-GAP

/*
    17.3-5
*/
typedef struct RBNode {
    int key;
    int color;
    struct RBNode* left;
    struct RBNode* right;
    struct RBNode* parent;
    struct RBNode* predecessor;
    struct RBNode* successor;
} RBNode;

typedef struct RBTree {
    RBNode* root; 
    RBNode* nil; // sentinel 
    uint minGap; // 17.3-5
} RBTree;


RBNode* create_rbnode(RBTree* T, int key);
RBTree* create_rbtree();
void left_rotate(RBTree* T, RBNode* x);
void right_rotate(RBTree* T, RBNode* y);
void insert_fixup(RBTree* tree, RBNode* z);
void rb_insert_fixup(RBTree* T, RBNode* z);
void rb_insert(RBTree* T, int key);
RBNode* find_successor(RBNode* x);
RBNode* find_predecessor(RBNode* x);
uint min(uint a, uint b);
void update_min_gap(RBTree* tree, RBNode* node);
uint get_min_gap(RBTree* tree);

RBNode* create_rbnode(RBTree* T, int key) {
    RBNode* node = (RBNode*)malloc(sizeof(RBNode));
    node->key = key;
    node->color = RED;
    node->left = T->nil;
    node->right = T->nil;
    node->parent = T->nil;
    node->successor = T->nil;
    node->predecessor = T->nil;
    printf("Successfully created a RBNode with a key of %d\n", key);
    return node;
}

RBTree* create_rbtree() {
    RBTree* T = (RBTree*)malloc(sizeof(RBTree));
    T->nil = (RBNode*)malloc(sizeof(RBNode));
    T->nil->color = BLACK;
    T->root = T->nil;
    T->minGap = INT_MAX;
    printf("Successfully created the RBTree\n");
    return T;
}

void left_rotate(RBTree* T, RBNode* x) {
    RBNode* y = x->right;
    x->right = y->left;
    if (y->left != T->nil) y->left->parent = x;
    y->parent = x->parent;

    if (x->parent == T->nil) T->root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void right_rotate(RBTree* T, RBNode* y) {
    RBNode* x = y->left;
    y->left = x->right;
    if (y->left != T->nil) y->left->parent = y;

    x->parent = y->parent;

    if (y->parent == T->nil) T->root = x;
    else if (y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;

    x->right = y;
    y->parent = x;
}

void rb_insert_fixup(RBTree* T, RBNode* z) {
    while (z->parent->color == RED) {
        RBNode *y;
        if (z->parent == z->parent->parent->left) {
            y = z->parent->parent->right;
            if (y->color == RED) {  
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {  
                    z = z->parent;
                    left_rotate(T, z);
                }
                z->parent->color = BLACK;  
                z->parent->parent->color = RED;
                right_rotate(T, z->parent->parent);
            }
        } else {
            y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    right_rotate(T, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                left_rotate(T, z->parent->parent);
            }
        }
    }
    T->root->color = BLACK;
}

void rb_insert(RBTree* T, int key) {
    RBNode* z = create_rbnode(T, key);
    RBNode* x = T->root;
    RBNode* y = T->nil;

    while (x != T->nil) {
        y = x;
        if (z->key < x->key) x = x->left;
        else x = x->right;
    }

    z->parent = y;
    if (y == T->nil) T->root = z;
    else if (z->key < y->key) y->left = z;
    else y->right = z;

    // Set successor and predecessor
    RBNode* temp = z->right != T->nil ? z->right : z->parent;
    while (temp != T->nil && z == temp->right) temp = temp->parent;
    z->successor = temp;

    temp = z->left != T->nil ? z->left : z->parent;
    while (temp != T->nil && z == temp->left) temp = temp->parent;
    z->predecessor = temp;

    update_min_gap(T, z);
    rb_insert_fixup(T, z);
}

RBNode* find_successor(RBNode* x) {
    return x->successor;
}

RBNode* find_predecessor(RBNode* x) {
    return x->predecessor;
}

uint min(uint a, uint b) {
    return (a < b) ? a : b;
}

void update_min_gap(RBTree* tree, RBNode* node) {
    uint leftGap = INT_MAX;
    uint rightGap = INT_MAX;

    if (node->predecessor) leftGap = node->key - node->predecessor->key; 
    if (node->successor) rightGap = node->successor->key - node->key;

    uint localMin = min(leftGap, rightGap);
    if (localMin < tree->minGap) tree->minGap = localMin;
}

uint get_min_gap(RBTree* tree) {
    return tree->minGap;
}

#pragma endregion MIN-GAP

#pragma region VLSI
/*
    17.3-6
*/
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
    RectRBNode* nil; // sentinel
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

RectRBNode* create_rect_rbnode(
    RectRBTree* T, 
    int y_min, 
    int y_max, 
    int x_min, 
    int x_max
);
RectRBTree* create_rect_rbtree();
void rect_left_rotate(RectRBTree* T, RectRBNode* x);
void rect_right_rotate(RectRBTree* T, RectRBNode* y);
void rect_insert_fixup(RectRBTree* tree, RectRBNode* z);
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
int check_rect_overlap(Rect rects[], uint n);
void rect_rb_transplant(RectRBTree *tree, RectRBNode *u, RectRBNode *v);
void rect_rb_delete_fixup(RectRBTree *tree, RectRBNode *x);
RectRBNode* rect_rb_minimum(RectRBTree *tree, RectRBNode *node);
void rect_rb_delete(RectRBTree *tree, RectRBNode *z);

RectRBNode* create_rect_rbnode(
    RectRBTree* T, 
    int y_min, 
    int y_max, 
    int x_min, 
    int x_max
) {
    RectRBNode* node = (RectRBNode*)malloc(sizeof(RectRBNode));
    node->y_min = y_min;
    node->y_max = y_max;
    node->x_min = x_min;
    node->x_max = x_max;

    node->left = T->nil;   
    node->right = T->nil;  
    node->parent = T->nil;

    node->color = RED;

    printf("Successfully created a RectRBNode with\n");
    return node;
}

RectRBTree* create_rect_rbtree() {
    RectRBTree* T = (RectRBTree*)malloc(sizeof(RectRBTree));
    T->nil = (RectRBNode*)malloc(sizeof(RectRBNode));
    T->nil->color = BLACK;
    T->root = T->nil;
    printf("Successfully created the RBTree\n");
    return T;
}

void rect_left_rotate(RectRBTree* T, RectRBNode* x) {
    RectRBNode* y = x->right;
    x->right = y->left;
    if (y->left != T->nil) y->left->parent = x;
    y->parent = x->parent;

    if (x->parent == T->nil) T->root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void rect_right_rotate(RectRBTree* T, RectRBNode* y) {
    RectRBNode* x = y->left;
    y->left = x->right;
    if (y->left != T->nil) y->left->parent = y;

    x->parent = y->parent;

    if (y->parent == T->nil) T->root = x;
    else if (y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;

    x->right = y;
    y->parent = x;
}

void rect_rb_insert_fixup(RectRBTree* T, RectRBNode* z) {
    while (z->parent->color == RED) {
        RectRBNode *y;
        if (z->parent == z->parent->parent->left) {
            y = z->parent->parent->right;
            if (y->color == RED) {  
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {  
                    z = z->parent;
                    rect_left_rotate(T, z);
                }
                z->parent->color = BLACK;  
                z->parent->parent->color = RED;
                rect_right_rotate(T, z->parent->parent);
            }
        } else {
            y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rect_right_rotate(T, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rect_left_rotate(T, z->parent->parent);
            }
        }
    }
    T->root->color = BLACK;
}

void rect_rb_insert(
    RectRBTree* tree, 
    int x_min, 
    int x_max, 
    int y_min, 
    int y_max
) {
    RectRBNode* z = create_rect_rbnode(tree, y_min, y_max, x_min, x_max);
    RectRBNode* y = tree->nil;
    RectRBNode* x = tree->root;

    while (x != tree->nil) {
        y = x;
        if (z->y_min < x->y_min) x = x->left;
        else x = x->right;
    }

    z->parent = y;

    if (y == tree->nil) tree->root = z;
    else if (z->y_min < y->y_min) y->left = z;
    else y->right = z;

    rect_rb_insert_fixup(tree, z);
}

int rect_overlap(RectRBNode* node, int y_min, int y_max) {
    return !(node->y_max <= y_min || node->y_min >= y_max);
}

int compare_event(const void* a, const void* b) {
    Event* eventA = (Event*)a;
    Event* eventB = (Event*)b;
    return eventA->x - eventB->x;
}

int check_rect_overlap(Rect rects[], uint n) {
    RectRBTree* tree = create_rect_rbtree();
    Event* events = (Event*)malloc(sizeof(Event) * 2 * n);

    if (!events) {
        printf("Event malloc failed!");
        free(events);
        return 0;
    }

    uint i;
    for (i = 0; i < n; i++) {
        events[2 * i].x = rects[i].x_min;
        events[2 * i].type = 1;  // start
        events[2 * i].y_min = rects[i].y_min;
        events[2 * i].y_max = rects[i].y_max;

        events[2 * i + 1].x = rects[i].x_max;
        events[2 * i + 1].type = -1;  // end
        events[2 * i + 1].y_min = rects[i].y_min;
        events[2 * i + 1].y_max = rects[i].y_max;
    }

    qsort(events, 2 * n, sizeof(Event), compare_event);

    for (i = 0; i < 2 * n; i++) {
        Event currEvent = events[i];

        if (currEvent.type == 1) {
            rect_rb_insert(
                tree, 
                currEvent.x_min, 
                currEvent.x_max, 
                currEvent.y_min, 
                currEvent.y_max
            );

            RectRBNode* node = tree->root;

            while (node != tree->nil) {
                if (rect_overlap(node, currEvent.y_min, currEvent.y_max)) {
                    free(events);
                    return 1;  
                }
                if (currEvent.y_min < node->y_min) node = node->left;
                else node = node->right;
            }
        } else {
            // TODO
        }
    }

    free(events);
    return 0;
}

void rect_rb_transplant(RectRBTree *tree, RectRBNode *u, RectRBNode *v) {
    if (u->parent == NULL) tree->root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;

    v->parent = u->parent;
}

void rect_rb_delete_fixup(RectRBTree *tree, RectRBNode *x) {
    while (x != tree->root && x->color == BLACK){
        if (x == x->parent->left) {
            RectRBNode *w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rect_left_rotate(tree, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rect_right_rotate(tree, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                rect_left_rotate(tree, x->parent);
                x = tree->root;
            }
        } else {
            RectRBNode *w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rect_right_rotate(tree, x->parent);
                w = x->parent->left;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    rect_left_rotate(tree, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rect_right_rotate(tree, x->parent);
                x = tree->root;
            }
        }
    }
    x->color = BLACK;
}

RectRBNode* rect_rb_minimum(RectRBTree *tree, RectRBNode *node) {
    while (node->left != tree->nil) node = node->left;
    return node;
}

void rect_rb_delete(RectRBTree *tree, RectRBNode *z) {
    RectRBNode *y = z;
    RectRBNode *x;
    int y_original_color = y->color;

    if (z->left == tree->nil) {
        x = z->right;
        rect_rb_transplant(tree, z, z->right);
    } else if (z->right == tree->nil) {
        x = z->left;
        rect_rb_transplant(tree, z, z->left);
    } else {
        y = rect_rb_minimum(tree, z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) x->parent = y;
        else {
            rect_rb_transplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        rect_rb_transplant(tree, z, y);
        y->left = z->left;
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    free(z);

    if (y_original_color == BLACK) rect_rb_delete_fixup(tree, x);
}

#pragma endregion VLSI

int main(void) {
    IntervalRBTree* tree = create_intervalRBTree();

    interval_rb_insert(tree, (Interval){15, 20});
    interval_rb_insert(tree, (Interval){10, 30});
    interval_rb_insert(tree, (Interval){17, 19});
    interval_rb_insert(tree, (Interval){5, 20});
    interval_rb_insert(tree, (Interval){12, 15});
    interval_rb_insert(tree, (Interval){30, 40});

    printf("Inorder traversal:\n");
    inorder_traversal(tree->root, tree->nil);

    switch (TASK)
    {
        case 1: {
            Interval query1 = {14, 16};
            printf("\nChecking for overlap with [%d, %d]:\n", 
                query1.low, query1.high);
            
            IntervalRBNode* result1 = tree->root;

            while (result1 != tree->nil) {
                if (check_overlap(result1->interval, query1))
                    printf("Overlapping with [%d, %d]\n", 
                        result1->interval.low, result1->interval.high);
                if (result1->left != tree->nil && result1->left->max >= query1.low) 
                    result1 = result1->left; 
                else result1 = result1->right;
            }

            break;
        }

        case 2: {
            // 17.3-2
            Interval query2 = {16, 18};
            IntervalRBNode* result2 = find_overlap_with_smallest_low(tree, query2);

            if (result2 != tree->nil) printf(
                "Overlapping interval with the lowest low value: [%d, %d]",
                result2->interval.low, result2->interval.high);
            else printf("There's no valid interval");

            break;
        }

        case 3: {
            // 17.3-3
            Interval query3 = {10, 18};
            find_overlapping_intervals(tree, tree->root, query3);

            break;
        }

        case 4: {
            // 17.3-4
            Interval query4 = {10, 30};
            IntervalRBNode* result4 = interval_search_exactly(tree, query4);
            printf("Result node has max value of: %d\n", result4->max);

            break;
        }

        case 5: {
            // 17.3-5
            RBTree* tree = create_rbtree();

            rb_insert(tree, 20);
            rb_insert(tree, 13);
            rb_insert(tree, 15);
            rb_insert(tree, 25);
            rb_insert(tree, 30);

            RBNode* node = tree->root; 
            RBNode* successor = find_successor(node);
            printf("Successor of node with key %d is %d\n", 
                node->key, successor->key);

            RBNode* predecessor = find_predecessor(node);
            printf("Predecessor of node with key %d is %d\n",
                node->key, predecessor->key);

            uint minGap = get_min_gap(tree);
            printf("Minimum gap in the set represented by the RBTree: %d\n", 
                minGap);

            break;
        }

        case 6: {
            // 17.3-6
            Rect rects[] = {
                {1, 4, 1, 4},
                {2, 5, 2, 5},
                {6, 8, 6, 8},
                {7, 9, 7, 9}
            };

            int n = sizeof(rects) / sizeof(rects[0]);

            if (check_rect_overlap(rects, n)) 
                printf("Detected overlapping rectangles!");

            break;
        }
        
        default: {
            break;
        }
    }
    
    return 0;
}