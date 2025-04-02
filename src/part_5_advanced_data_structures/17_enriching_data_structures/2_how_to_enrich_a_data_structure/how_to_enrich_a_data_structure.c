#include <stdio.h>
#include <stdlib.h>

#define TASK 1

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
    struct RBNode* successor;
    struct RBNode* predecessor;
} RBNode;

typedef struct RBTree {
    RBNode* root;
    RBNode* nil; // sentinel
    RBNode* min;
    RBNode* max;
} RBTree;

RBNode* create_rbnode(RBTree* T, int key) {
    RBNode* node = (RBNode*)malloc(sizeof(RBNode));
    node->key = key;
    node->color = RED;
    node->size = 1;
    node->left = T->nil;
    node->right = T->nil;
    node->parent = T->nil;
    node->successor = T->nil;  
    node->predecessor = T->nil;  
    printf("Successfuly created a RBNode with a key of %d\n", key);
    return node;
}

RBTree* create_rbtree() {
    RBTree* T = (RBTree*)malloc(sizeof(RBTree));
    T->nil = (RBNode*)malloc(sizeof(RBNode));
    T->nil->color = BLACK;
    T->nil->size = 0;
    T->root = T->nil;
    T->min = T->nil;
    T->max = T->nil;
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

    RBNode* node = z;
    while (node != T->nil) {
        node->size = node->left->size + node->right->size + 1;
        node = node->parent;
    }

    if (T->min == T->nil || z->key < T->min->key) T->min = z;
    if (T->max == T->nil || z->key > T->max->key) T->max = z;

    RBNode* temp;

    // Successor
    if (z->right != T->nil) {
        temp = z->right;
        while (temp->left != T->nil) temp = temp->left;
    } else {
        temp = z->parent;
        while (temp != T->nil && z == temp->right) {
            z = temp;
            temp = temp->parent;
        }
    }
    z->successor = temp;

    // Predecessor
    if (z->left != T->nil) {
        temp = z->left;
        while (temp->right != T->nil) temp = temp->right;
    } else {
        temp = z->parent;
        while (temp != T->nil && z == temp->left) {
            z = temp;
            temp = temp->parent;
        }
    }

    z->predecessor = temp;

    rb_insert_fixup(T, z);
}

void inorder_traversal(RBNode* root, RBNode* nil) {
    if (root == nil) return;
    inorder_traversal(root->left, nil);
    printf("%d (size=%d) \n", root->key, root->size);
    inorder_traversal(root->right, nil);
}

/*
    17.2-1
*/
RBNode* find_min(RBTree* T) {
    return T->min;
}

RBNode* find_max(RBTree* T) {
    return T->max;
}

RBNode* find_successor(RBNode* x) {
    return x->successor;
}

RBNode* find_predecessor(RBNode* x) {
    return x->predecessor;
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
            // 17.2-1
            RBNode* minNode = find_min(T);
            printf("Minimum key node: %d\n", minNode->key);

            RBNode* maxNode = find_max(T);
            printf("Maximum key node: %d\n", maxNode->key);

            RBNode* node = T->root->left->left; 
            RBNode* successor = find_successor(node);
            printf("Successor of node with key %d is %d\n", node->key, successor->key);

            node = T->root;
            RBNode* predecessor = find_predecessor(node);
            printf("Predecessor of node with key %d is %d\n", node->key, predecessor->key);

            break;
        }
        default:
            break;
        }
    return 0;
}