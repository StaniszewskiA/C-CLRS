#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "../../common.h"
#include "../part_3_commons.h"

// ============================================================================
// CHAPTER 13.1-4: RED-BLACK TREES
// ============================================================================

typedef enum {
    RED = 0,
    BLACK = 1
} NodeColor;

typedef struct RedBlackNode {
    int key;
    int data;
    int size;
    NodeColor color;
    struct RedBlackNode *left, *right, *parent;
} RedBlackNode;

typedef struct RedBlackTree {
    RedBlackNode *root;
    RedBlackNode *nil; // sentinel
} RedBlackTree;

RedBlackNode* rb_node_create(RedBlackTree *tree, int data);
RedBlackTree* rb_tree_create();
void rb_tree_left_rotate(RedBlackTree *tree, RedBlackNode *x);
void rb_tree_right_rotate(RedBlackTree *tree, RedBlackNode *y);
void rb_tree_insert_fixup(RedBlackTree *tree, RedBlackNode *z);
void rb_tree_insert(RedBlackTree *tree, int data);
void rb_tree_transplant(RedBlackTree *tree, RedBlackNode *u, RedBlackNode *v);
void rb_tree_delete_fixup(RedBlackTree *tree, RedBlackNode *x);
RedBlackNode* rb_tree_get_min(RedBlackTree *tree, RedBlackNode *node);
void rb_tree_delete(RedBlackTree *tree, RedBlackNode *z);
void rb_tree_enumerate(RedBlackTree *tree, RedBlackNode *r, int a, int b);
RedBlackNode* rb_tree_join(
    RedBlackTree *tree, 
    RedBlackNode *T1, 
    RedBlackNode *x, 
    RedBlackNode *T2
);
RedBlackNode* rb_tree_search(RedBlackTree *tree, int data);
void rb_tree_inorder_traversal(RedBlackTree *tree, RedBlackNode *node);

// ============================================================================
// PROBLEMS
// ============================================================================

typedef struct Node2 {
    int key;
    struct Node2 *left, *right;
} Node2;

typedef struct PersistentTree {
    Node2 *root;
} PersistentTree;

Node2* node2_create(int key);
Node2* node2_copy(Node2* target);
void persistent_tree_insert(PersistentTree *tree, int k);

typedef struct AVLNode {
    int key;
    struct AVLNode *left; 
    struct AVLNode *right;
    int height; 
} AVLNode;

int avl_node_get_height(AVLNode *node);
int avl_node_get_balance_factor(AVLNode *node);
AVLNode* avl_node_create_node(int key);
AVLNode* avl_tree_right_rotate(AVLNode *y);
AVLNode* avl_tree_left_rotate(AVLNode *x);
AVLNode* avl_tree_insert(AVLNode *node, int key);
AVLNode* avl_tree_search(AVLNode *root, int key);
void avl_tree_inorder_traversal(AVLNode *root);
void avl_tree_balance(AVLNode **root);

#endif // BINARY_SEARCH_TREE_H