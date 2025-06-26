#include "part_5_advanced_data_structures/17_enriching_data_structures/enriching_data_structures.h"

/*
    17.2-1
*/
RedBlackNode* rb_tree_find_min(RedBlackTree* T) {
    RedBlackNode* current = T->root;
    while (current->left != T->nil) {
        current = current->left;
    }
    return current;
}

RedBlackNode* rb_tree_find_max(RedBlackTree* T) {
    RedBlackNode* current = T->root;
    while (current->right != T->nil) {
        current = current->right;
    }
    return current;
}

RedBlackNode* rb_tree_find_successor(RedBlackTree* T, RedBlackNode* x) {
    if (x->right != T->nil) {
        RedBlackNode* current = x->right;
        while (current->left != T->nil) {
            current = current->left;
        }
        return current;
    }
    
    RedBlackNode* y = x->parent;
    while (y != NULL && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}

RedBlackNode* rb_tree_find_predecessor(RedBlackTree* T, RedBlackNode* x) {
    if (x->left != T->nil) {
        RedBlackNode* current = x->left;
        while (current->right != T->nil) {
            current = current->right;
        }
        return current;
    }
    
    RedBlackNode* y = x->parent;
    while (y != NULL && x == y->left) {
        x = y;
        y = y->parent;
    }
    return y;
}

/*
    17.2-2
*/
int calculate_black_height(RedBlackTree* tree, RedBlackNode* node) {
    if (node == tree->nil) return 0;
    
    int left_height = calculate_black_height(tree, node->left);
    int height = left_height + (node->color == BLACK ? 1 : 0);
    return height;
}

int calculate_depth(RedBlackTree* tree, RedBlackNode* node) {
    if (node == tree->root) return 0;
    if (node->parent == NULL) return -1;
    return calculate_depth(tree, node->parent) + 1;
}
