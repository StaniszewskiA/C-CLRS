#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "../../common.h"
#include "../part_3_commons.h"

// ============================================================================
// CHAPTER 12.1: WHAT IS A BINARY SEARCH TREE
// ============================================================================

typedef struct BSTNode {
    int data;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

BSTNode* bst_node_init(int data);
BSTNode* bst_insert(BSTNode* root, int data);
void bst_inorder_traversal(BSTNode* root);
void bst_preorder_traversal(BSTNode* root);
void bst_postorder_traversal(BSTNode* root);

// ============================================================================
// CHAPTER 12.2: QUERYING A BINARY SEARCH TREE
// ============================================================================

typedef struct BSTNodeWithParent {
    int key;
    struct BSTNodeWithParent* left;
    struct BSTNodeWithParent* right;
    struct BSTNodeWithParent* parent;
} BSTNodeWithParent;

BSTNodeWithParent* bts_with_node_parent_init(int key);
BSTNodeWithParent* bts_with_node_parent_insert(BSTNodeWithParent* root, int key);
BSTNodeWithParent* bts_with_node_parent_tree_min(BSTNodeWithParent* root);
BSTNodeWithParent* bts_with_node_parent_tree_max(BSTNodeWithParent* root);
void bts_with_node_parent_tree_print_min_max(BSTNodeWithParent* root);
BSTNodeWithParent* bts_with_node_parent_tree_predecessor(BSTNodeWithParent* x);
BSTNodeWithParent* bts_with_node_parent_tree_search(BSTNodeWithParent* root, int key);
BSTNodeWithParent* bts_with_node_parent_tree_search_iter(BSTNodeWithParent* root, int key);
BSTNodeWithParent* bts_with_node_parent_tree_successor(BSTNodeWithParent* x);

// ============================================================================
// CHAPTER 12.3: INSERTION AND DELETION
// ============================================================================

void bts_with_node_parent_insert_node(
    BSTNodeWithParent* currNode, 
    BSTNodeWithParent* newNode
);

typedef struct BST {
    BSTNodeWithParent* root;
} BST;

void bst_recursive_tree_insert(BST* tree, BSTNodeWithParent* newNode);
void bst_tree_transplant(BST* tree, BSTNodeWithParent* u, BSTNodeWithParent* v);
void bst_tree_delete(BST* tree, BSTNodeWithParent* target);

#endif // BINARY_SEARCH_TREE_H