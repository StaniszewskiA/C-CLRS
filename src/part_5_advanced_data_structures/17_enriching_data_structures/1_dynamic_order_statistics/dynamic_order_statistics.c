#include "part_5_advanced_data_structures/17_enriching_data_structures/enriching_data_structures.h"

/*
    17.1-1
*/
RedBlackNode* os_select(RedBlackNode* x, int i, RedBlackNode* nil) {
    if (x == nil) return NULL;

    int r = x->left->size + 1;

    if (i == r) return x;
    else if (i < r) return os_select(x->left, i, nil);
    else return os_select(x->right, i - r , nil);
}

/*
    17.1-2
*/
int os_rank(RedBlackTree* T, RedBlackNode* x) {
    int r = x->left->size + 1;
    RedBlackNode* y = x;

    while (y != T->root) {
        if (y == y->parent->right) r += y->parent->left->size + 1;
        y = y->parent;
    }

    return r;
}

/*
    17.1-3
*/
RedBlackNode* os_select_iterative(RedBlackNode* x, int i, RedBlackNode* nil) {
    while (x != nil) {
        int r = x->left->size + 1;

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
int os_key_rank(RedBlackTree* T, RedBlackNode* x, int k) {
    if (x == T->nil) return 0;

    if (k == x->key) return x->left->size + 1;
    else if (k < x->key) return os_key_rank(T, x->left, k);
    else return (x->left->size + 1) + os_key_rank(T, x->right, k);
}

/*
    17.1-7
*/
int count_inversions(RedBlackTree* T, int* arr, int n) {
    int invCount = 0;
    int i;

    for (i = 0; i < n; i++) {
        RedBlackNode* temp = T->root;
        while (temp != T->nil) {
            if (arr[i] < temp->key) {
                if (temp->right != T->nil) invCount += temp->right->size + 1;
                temp = temp->left;
            } else temp = temp->right;
        }
        rb_tree_insert(T, arr[i]);
    }

    return invCount;
}

/*
    17.1-8
*/
double calculate_angle(AngledPoint* p) {
    return atan2(p->y, p->x);
}

int compare_angles(const void *a, const void *b) {
    return ((AngledPoint*)a)->angle - ((AngledPoint*)b)->angle;
}

int count_intersections(AngledPoint* points, int n) {
    for (int i = 0; i < n; i++) { 
        points[i].angle = calculate_angle(&points[i]);
        printf("%2f\n",points[i].angle);
    }

    qsort(points, n, sizeof(AngledPoint), compare_angles);

    RedBlackTree* T = rb_tree_create();
    int* angles = (int*)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) angles[i] = i;  

    int interCnt = count_inversions(T, angles, n);
    free(angles);

    return interCnt;
}
