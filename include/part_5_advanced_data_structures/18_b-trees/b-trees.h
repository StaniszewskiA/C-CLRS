#ifndef B_TREES_H
#define B_TREES_H

#include "../../common.h"
#include "../part_5_commons.h"

// ============================================================================
// CHAPTER 18.1: B-TREES
// ============================================================================

#define DEGREE 3

typedef struct BTreeNode {
    int keys[2 * DEGREE - 1];
    int isLeaf;
    int numKeys;
    struct BTreeNode* children[2 * DEGREE];
} BTreeNode;

BTreeNode* btree_node_init(int isLeaf);
BTreeNode* btree_init();
void btree_traverse(BTreeNode* root);
BTreeNode* btree_search(BTreeNode* root, int key);
void btree_node_split_child(BTreeNode* x, int i, BTreeNode* y);
void btree_tree_insert_non_full(BTreeNode* x, int k);
void btree_tree_insert(BTreeNode** root, int k);
int btree_tree_node_get_predecessor(BTreeNode* x);
int btree_tree_node_get_successor(BTreeNode* x);
void btree_tree_node_merge(BTreeNode* x, int i);
void btree_tree_fill(BTreeNode* x, int i);
void btree_delete_from_node(BTreeNode* x, int k);
void btree_delete_key(BTreeNode** root_ref, int k);
void btree_free(BTreeNode* node);

// ============================================================================
// PROBLEMS
// ============================================================================

void btree_split_helper(BTreeNode* node, int key, BTreeNode** leftRef, BTreeNode** rightRef);
void btree_split_tree(BTreeNode* root, int key, BTreeNode** leftRef, BTreeNode** rightRef);
BTreeNode* btree_join_trees(BTreeNode* left, int midKey, BTreeNode* right);

#endif // B_TREES_H