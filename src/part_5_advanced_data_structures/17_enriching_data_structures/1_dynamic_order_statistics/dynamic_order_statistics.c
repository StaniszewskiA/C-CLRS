#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TASK 6

#define RED 0
#define BLACK 1

typedef unsigned int uint;

typedef struct RBNode {
    int color;
    uint key;
    uint size;
    struct RBNode* left;
    struct RBNode* right;
    struct RBNode* parent;
} RBNode;

typedef struct RBTree {
    RBNode* root;
    RBNode* nil; // sentinel
} RBTree;

RBNode* create_rbnode(RBTree* T, int key) {
    RBNode* node = (RBNode*)malloc(sizeof(RBNode));
    node->key = key;
    node->color = RED;
    node->size = 1;
    node->left = T->nil;
    node->right = T->nil;
    node->parent = T->nil;
    printf("Successfuly created a RBNode with a key of %d\n", key);
    return node;
}

RBTree* create_rbtree() {
    RBTree* T = (RBTree*)malloc(sizeof(RBTree));
    T->nil = (RBNode*)malloc(sizeof(RBNode));
    T->nil->color = BLACK;
    T->nil->size = 0;
    T->root = T->nil;
    printf("Successfuly created the RBTree\n");
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

    y->size = x->size;
    x->size = x->left->size + x->right->size + 1;
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

    x->size = y->size;
    y->size = y->left->size + y->right->size + 1;
}

void rb_insert_fixup(RBTree *T, RBNode *z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            RBNode *y = z->parent->parent->right;
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
            RBNode *y = z->parent->parent->left;
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
        x->size++; 
        if (z->key < x->key) x = x->left;
        else x = x->right;
    }

    z->parent = y;
    if (y == T->nil) T->root = z;
    else if (z->key < y->key) y->left = z;
    else y->right = z;

    // 17.1-6
    RBNode* node = z;
    while (node != T->nil) {
        node->size = node->left->size + node->right->size + 1;
        node = node->parent;
    }

    rb_insert_fixup(T, z);
}

/*
    17.1-1
*/
RBNode* os_select(RBNode* x, int i, RBNode* nil) {
    if (x == nil) return NULL;

    int r = x->left->size + 1;

    if (i == r) return x;
    else if (i < r) return os_select(x->left, i, nil);
    else return os_select(x->right, i - r , nil);
}

/*
    17.1-2
*/
uint os_rank(RBTree* T, RBNode* x) {
    uint r = x->left->size + 1;
    RBNode* y = x;

    while (y != T->root) {
        if (y == y->parent->right) r += y->parent->left->size + 1;
        y = y->parent;
    }

    return r;
}

void inorder_traversal(RBNode* root, RBNode* nil) {
    if (root == nil) return;
    inorder_traversal(root->left, nil);
    printf("%d (size=%d) ", root->key, root->size);
    inorder_traversal(root->right, nil);
}

/*
    17.1-3
*/
RBNode* os_select_iterative(RBNode* x, int i, RBNode* nil) {
    while (x != nil) {
        uint r = x->left->size + 1;

        if (i == r) return x;
        else if (i < r) x = x->left;
        else {
            i -= r;
            x = x->right;
        }
    }

    return NULL;
}

/*
    17.1-4
*/
uint os_key_rank(RBTree* T, RBNode* x, uint k) {
    if (x == T->nil) return 0;

    if (k == x->key) return x->left->size + 1;
    else if (k < x->key) return os_key_rank(T, x->left, k);
    else return (x->left->size + 1) + os_key_rank(T, x->right, k);
}

/*
    17.1-7
*/
uint count_inversions(RBTree* T, int* arr, uint n) {
    uint invCount = 0;
    uint i;

    for (i = 0; i < n; i++) {
        RBNode* temp = T->root;
        while (temp != T->nil) {
            if (arr[i] < temp->key) {
                if (temp->right != T->nil) invCount += temp->right->size + 1;
                temp = temp->left;
            } else temp = temp->right;
        }
        rb_insert(T, arr[i]);
    }

    return invCount;
}

/*
    17.1-8
*/
typedef struct {
    double x, y;
    double angle;
} Point;

static inline double calculate_angle(Point* p) {
    return atan2(p->y, p->x);
}

int compare_angles(const void *a, const void *b) {
    return ((Point*)a)->angle - ((Point*)b)->angle;
}

uint count_intersections(Point* points, uint n) {
    for (uint i = 0; i < n; i++) { 
        points[i].angle = calculate_angle(&points[i]);
        printf("%2f\n",points[i].angle);
    }

    qsort(points, n, sizeof(Point), compare_angles);

    RBTree* T = create_rbtree();
    int* angles = (int*)malloc(sizeof(int) * n);

    for (uint i = 0; i < n; i++) angles[i] = i;  

    uint interCnt = count_inversions(T, angles, n);
    free(angles);

    return interCnt;
}

int main(void) {
    RBTree* T = create_rbtree();

    rb_insert(T, 20);
    rb_insert(T, 15);
    rb_insert(T, 25);
    rb_insert(T, 10);
    rb_insert(T, 5);
    rb_insert(T, 1);
    rb_insert(T, 30);

    printf("Inorder traversal with sizes:\n");
    inorder_traversal(T->root, T->nil);

    switch (TASK)
    {
        case 1: {
            // 17.1-1
            uint target1 = 4;
            RBNode* result1 = os_select(T->root, target1, T->nil); 
            if (result1) printf("%d-th smallest element is: %d\n", 
                target1, result1->key);
            break;
        }

        case 2: {
            // 17.1-2
            uint result2 = os_rank(T, T->root->right);
            if (result2) printf("Rank of the target node: %d\n", result2);
            break;
        }

        case 3: {
            // 17.1-3
            uint target3 = 4;
            RBNode* result3 = os_select_iterative(T->root, target3, T->nil); 
            if (result3) printf("%d-th smallest element is: %d\n", 
                target3, result3->key);
            break;
        }

        case 4: {
            // 17.1-4
            uint target4 = 5;
            uint result4 = os_key_rank(T, T->root, target4);
            printf("Rank of the node with key %u is: %u\n", target4, result4);
            break;
        }

        case 5: {
            // 17.1-7
            RBTree* T7 = create_rbtree();

            int arr7[] = {0, 4, 2, 1};
            int n7 = sizeof(arr7) / sizeof(arr7[0]);

            printf("Number of inversions: %d\n", 
                count_inversions(T7, arr7, n7));

            break;
        }

        case 6: {
            // 17.1-8
            Point points[] = {
                {1.0, 2.0}, 
                {2.0, 3.0}, 
                {3.0, 1.0}, 
                {4.0, 2.0}, 
            };

            uint n8 = sizeof(points) / sizeof(points[0]);
            printf("Total intersecting chords: %u\n", 
                count_intersections(points, n8));

            break;
        }
        
        default:
            break;
    }

    return 0;
}