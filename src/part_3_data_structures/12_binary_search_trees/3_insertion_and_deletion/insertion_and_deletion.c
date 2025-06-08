#include "part_3_data_structures/12_binary_search_trees/binary_search_trees.h"

void bts_with_node_parent_insert_node(
    BSTNodeWithParent* currNode, 
    BSTNodeWithParent* newNode
) {
    if (currNode == NULL) return;
    
    if (newNode->key < currNode->key) {
        if (currNode->left == NULL) {
            currNode->left = newNode;
            newNode->parent = currNode;
        } else {
            bts_with_node_parent_insert_node(currNode->left, newNode);
        }
    } else if (newNode->key > currNode->key) {
        if (currNode->right == NULL) {
            currNode->right = newNode;
            newNode->parent = currNode;
        } else {
            bts_with_node_parent_insert_node(currNode->right, newNode);
        }
    }
}

void bst_recursive_tree_insert(BST* tree, BSTNodeWithParent* newNode) {
    if (tree->root == NULL) tree->root = newNode;
    else bts_with_node_parent_insert_node(tree->root, newNode);
}

void bst_tree_transplant(BST* tree, BSTNodeWithParent* u, BSTNodeWithParent* v) {
    if (u->parent == NULL) tree->root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;

    if (v != NULL) v->parent = u->parent;
}

void bst_tree_delete(BST* tree, BSTNodeWithParent* target) {
    if (target->left == NULL) bst_tree_transplant(tree, target, target->right);
    else if (target->right == NULL) bst_tree_transplant(tree, target, target->left);
    else {
        BSTNodeWithParent* successor = bts_with_node_parent_tree_min(target->right);
        if (successor->parent != target) {
            bst_tree_transplant(tree, successor, successor->right);
            successor->right = target->right;
            successor->right->parent = successor;
        }
        bst_tree_transplant(tree, target, successor);
        successor->left = target->left;
        successor->left->parent = successor;
    }
    free(target);
}