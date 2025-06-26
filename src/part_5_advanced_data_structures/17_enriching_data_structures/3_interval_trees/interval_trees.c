#include "part_5_advanced_data_structures/17_enriching_data_structures/enriching_data_structures.h"

#define TASK 6

#pragma region INTERVAL-RB

IntervalRBNode* interval_rb_node_init(IntervalRBTree* tree, Interval interval) {
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

IntervalRBTree* interval_rb_tree_init() {
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

void interval_rb_tree_rotate_left(IntervalRBTree* tree, IntervalRBNode* x) {
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
    x->max = MAX3(x->interval.high, x->left->max, x->right->max);
    if (x->max < x->interval.high) x->max = x->interval.high;

    y->max = MAX3(y->interval.high, y->left->max, y->right->max);
    if (y->max < y->interval.high) y->max = y->interval.high;
}

void interval_rb_tree_rotate_right(IntervalRBTree* tree, IntervalRBNode* y) {
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
                    interval_rb_tree_rotate_left(tree, z);
                }
                z->parent->color = BLACK;  
                z->parent->parent->color = RED;
                interval_rb_tree_rotate_right(tree, z->parent->parent);
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
                    interval_rb_tree_rotate_right(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                interval_rb_tree_rotate_left(tree, z->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}

void interval_rb_insert(IntervalRBTree* tree, Interval interval) {
    IntervalRBNode* z = interval_rb_node_init(tree, interval);
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
        y->max = MAX3(y->interval.high, y->left->max, y->right->max);
        y = y->parent;
    }
}

void interval_rb_tree_inorder_traversal(IntervalRBNode* root, IntervalRBNode* nil) {
    if (root == nil) return;
    interval_rb_tree_inorder_traversal(root->left, nil);
    printf("[%d, %d] max = %d | Color = %s\n", 
        root->interval.low, 
        root->interval.high, 
        root->max, 
        root->color ? "BLACK" : "RED"
    );
    interval_rb_tree_inorder_traversal(root->right, nil);
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

    O(MIN(n, k*log(n)))
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
MinGapRBNode* min_gap_rb_node_init(MinGapRBTree* T, int key) {
    MinGapRBNode* node = (MinGapRBNode*)malloc(sizeof(MinGapRBNode));
    node->key = key;
    node->color = RED;
    node->left = T->nil;
    node->right = T->nil;
    node->parent = T->nil;
    node->successor = T->nil;
    node->predecessor = T->nil;
    printf("Successfully created a MinGapRBNode with a key of %d\n", key);
    return node;
}

MinGapRBTree* min_gap_rb_tree_init() {
    MinGapRBTree* T = (MinGapRBTree*)malloc(sizeof(MinGapRBTree));
    T->nil = (MinGapRBNode*)malloc(sizeof(MinGapRBNode));
    T->nil->color = BLACK;
    T->root = T->nil;
    T->minGap = INT_MAX;
    printf("Successfully created the MinGapRBTree\n");
    return T;
}

void min_gap_rb_tree_left_rotate(MinGapRBTree* T, MinGapRBNode* x) {
    MinGapRBNode* y = x->right;
    x->right = y->left;
    if (y->left != T->nil) y->left->parent = x;
    y->parent = x->parent;

    if (x->parent == T->nil) T->root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void min_gap_rb_tree_right_rotate(MinGapRBTree* T, MinGapRBNode* y) {
    MinGapRBNode* x = y->left;
    y->left = x->right;
    if (y->left != T->nil) y->left->parent = y;

    x->parent = y->parent;

    if (y->parent == T->nil) T->root = x;
    else if (y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;

    x->right = y;
    y->parent = x;
}

void min_gap_rb_tree_fixup(MinGapRBTree* T, MinGapRBNode* z) {
    while (z->parent->color == RED) {
        MinGapRBNode *y;
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
                    min_gap_rb_tree_left_rotate(T, z);
                }
                z->parent->color = BLACK;  
                z->parent->parent->color = RED;
                min_gap_rb_tree_right_rotate(T, z->parent->parent);
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
                    min_gap_rb_tree_right_rotate(T, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                min_gap_rb_tree_left_rotate(T, z->parent->parent);
            }
        }
    }
    T->root->color = BLACK;
}

void min_gap_rb_tree_insert(MinGapRBTree* T, int key) {
    MinGapRBNode* z = min_gap_rb_node_init(T, key);
    MinGapRBNode* x = T->root;
    MinGapRBNode* y = T->nil;

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
    MinGapRBNode* temp = z->right != T->nil ? z->right : z->parent;
    while (temp != T->nil && z == temp->right) temp = temp->parent;
    z->successor = temp;

    temp = z->left != T->nil ? z->left : z->parent;
    while (temp != T->nil && z == temp->left) temp = temp->parent;
    z->predecessor = temp;

    min_gap_rb_tree_update_min_gap(T, z);
    min_gap_rb_tree_fixup(T, z);
}

MinGapRBNode* min_gap_rb_node_find_successor(MinGapRBNode* x) {
    return x->successor;
}

MinGapRBNode* min_gap_rb_node_find_predecessor(MinGapRBNode* x) {
    return x->predecessor;
}

void min_gap_rb_tree_update_min_gap(MinGapRBTree* tree, MinGapRBNode* node) {
    int leftGap = INT_MAX;
    int rightGap = INT_MAX;

    if (node->predecessor) leftGap = node->key - node->predecessor->key; 
    if (node->successor) rightGap = node->successor->key - node->key;

    int localMin = MIN(leftGap, rightGap);
    if (localMin < tree->minGap) tree->minGap = localMin;
}

int min_gap_rb_tree_get_min_gap(MinGapRBTree* tree) {
    return tree->minGap;
}

#pragma endregion MIN-GAP

#pragma region VLSI
/*
    17.3-6
*/
RectRBNode* rect_rb_node_init(
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

RectRBTree* rect_rb_tree_init() {
    RectRBTree* T = (RectRBTree*)malloc(sizeof(RectRBTree));
    T->nil = (RectRBNode*)malloc(sizeof(RectRBNode));
    T->nil->color = BLACK;
    T->root = T->nil;
    printf("Successfully created the MinGapRBTree\n");
    return T;
}

void rect_rb_tree_left_rotate(RectRBTree* T, RectRBNode* x) {
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

void rect_rb_tree_right_rotate(RectRBTree* T, RectRBNode* y) {
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
                    rect_rb_tree_left_rotate(T, z);
                }
                z->parent->color = BLACK;  
                z->parent->parent->color = RED;
                rect_rb_tree_right_rotate(T, z->parent->parent);
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
                    rect_rb_tree_right_rotate(T, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rect_rb_tree_left_rotate(T, z->parent->parent);
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
    RectRBNode* z = rect_rb_node_init(tree, y_min, y_max, x_min, x_max);
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

int check_rect_overlap(Rect rects[], int n) {
    RectRBTree* tree = rect_rb_tree_init();
    Event* events = (Event*)malloc(sizeof(Event) * 2 * n);

    if (!events) {
        printf("Event malloc failed!");
        free(events);
        return 0;
    }

    int i;
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

void rect_rb_tree_transplant(RectRBTree *tree, RectRBNode *u, RectRBNode *v) {
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
                rect_rb_tree_left_rotate(tree, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rect_rb_tree_right_rotate(tree, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                rect_rb_tree_left_rotate(tree, x->parent);
                x = tree->root;
            }
        } else {
            RectRBNode *w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rect_rb_tree_right_rotate(tree, x->parent);
                w = x->parent->left;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    rect_rb_tree_left_rotate(tree, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rect_rb_tree_right_rotate(tree, x->parent);
                x = tree->root;
            }
        }
    }
    x->color = BLACK;
}

RectRBNode* rect_rb_tree_get_min(RectRBTree *tree, RectRBNode *node) {
    while (node->left != tree->nil) node = node->left;
    return node;
}

void rect_rb_tree_delete(RectRBTree *tree, RectRBNode *z) {
    RectRBNode *y = z;
    RectRBNode *x;
    int y_original_color = y->color;

    if (z->left == tree->nil) {
        x = z->right;
        rect_rb_tree_transplant(tree, z, z->right);
    } else if (z->right == tree->nil) {
        x = z->left;
        rect_rb_tree_transplant(tree, z, z->left);
    } else {
        y = rect_rb_tree_get_min(tree, z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) x->parent = y;
        else {
            rect_rb_tree_transplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        rect_rb_tree_transplant(tree, z, y);
        y->left = z->left;
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    free(z);

    if (y_original_color == BLACK) rect_rb_delete_fixup(tree, x);
}

#pragma endregion VLSI
