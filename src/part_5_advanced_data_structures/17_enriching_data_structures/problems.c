#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TASK 1

#define RED 0
#define BLACK 1

typedef unsigned int uint;

#pragma region The point with the highest number of intersections
/*
    17-1
*/
typedef struct RBNode {
    int endpoint;
    int delta;
    int intersections;
    int maxIntersections;
    int color;
    struct RBNode* left;
    struct RBNode* right;
    struct RBNode* parent;
} RBNode;

typedef struct RBTree {
    RBNode* root;
    RBNode* nil; // sentinel
} RBTree;

int max(int a, int b);
RBNode* create_rbnode(RBTree* tree, int endpoint, int delta);
RBTree* create_rbtree();
void left_rotate(RBTree *tree, RBNode *x);
void right_rotate(RBTree *tree, RBNode *y);
void rb_insert_fixup(RBTree *tree, RBNode *z);
void insert(RBTree *tree, int endpoint, int delta);
void update_intersections(RBNode* node);
int find_max_intersections(RBTree *tree);

int max(int a, int b) {
    return (a > b) ? a : b;
}

RBNode* create_rbnode(RBTree* tree, int endpoint, int delta) {
    RBNode* node = (RBNode*)malloc(sizeof(RBNode));
    node->endpoint = endpoint;
    node->delta = delta;
    node->intersections = 0;
    node->maxIntersections = delta;
    node->color = RED;
    node->left = tree->nil;
    node->right = tree->nil;
    node->parent = NULL;
    printf("Succesfuly created RBNode\n");
    return node;
}

RBTree* create_rbtree() {
    RBTree* tree = (RBTree*)malloc(sizeof(RBTree));
    tree->nil = (RBNode*)malloc(sizeof(RBNode));
    tree->nil->color = BLACK;
    tree->root = tree->nil;
    printf("Succesfuly created RBTree\n");
    return tree;
}

void left_rotate(RBTree *tree, RBNode *x) {
    RBNode *y = x->right;
    x->right = y->left;

    if (y->left != tree->nil) y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL) tree->root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;

    x->left = x;
    x->parent = y;
}

void right_rotate(RBTree *tree, RBNode *y) {
    RBNode *x = y->right;
    y->left = x->right;

    if (x->right != tree->nil) y->right->parent = y;

    x->parent = y->parent;

    if (y->parent == NULL) tree->root = x;
    else if (y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;

    x->right = y;
    y->parent = x;
}

void rb_insert_fixup(RBTree *tree, RBNode *z) {
    while (z->parent != NULL & z->parent->color == RED) {
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
                    left_rotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                right_rotate(tree, z->parent->parent);
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
                    right_rotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                left_rotate(tree, z->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}

void insert(RBTree *tree, int endpoint, int delta) {
    RBNode *z = create_rbnode(tree, endpoint, delta);
    RBNode *x = tree->root;
    RBNode *y = tree->nil;

    while (x != tree->nil) {
        y = x;
        if (z->endpoint < x->endpoint) x = x->left;
        else x = x->right;
    }

    z->parent = y;
    if (y == tree->nil) tree->root = z;
    else if (z->endpoint < y->endpoint) y->left = z;
    else y->right = z;
    

    z->left = tree->nil;
    z->right = tree->nil;
    z->color = RED;

    rb_insert_fixup(tree, z);
    printf("Succesfuly inserted RBNode into RBTree\n");
    update_intersections(z);
}

void update_intersections(RBNode* node) {
    node->intersections = node->delta;

    if (node->left != node->parent) node->intersections += node->left->intersections;
    if (node->right != node->parent) node->intersections += node->right->intersections;

    node->maxIntersections = node->intersections;

    if (node->left != node->parent)
        node->maxIntersections = max(node->left->maxIntersections, node->maxIntersections);

    if (node->right != node->parent) 
        node->maxIntersections = max(node->right->maxIntersections, node->maxIntersections);
    
}

int find_max_intersections(RBTree *tree) {
    RBNode* maxNode = tree->root;

    while (maxNode != tree->nil) {
        if (maxNode->maxIntersections == maxNode->intersections) break;
        maxNode = (maxNode->left->maxIntersections > maxNode->right->maxIntersections) 
            ? maxNode->left : maxNode->right;
    }
    return maxNode->endpoint;
}

#pragma endregion The point with the highest number of intersections

int main(void) {
    switch (TASK)
    {
        case 1: {
            // 17-1
            RBTree* tree = create_rbtree();

            insert(tree, 5, 1);
            insert(tree, 10, -1);
            insert(tree, 15, 1);

            printf("Endpoint of node with max intersections: %d\n", 
                find_max_intersections(tree));

            break;
        }
        
        default:
            break;
    }

    return 0;
}