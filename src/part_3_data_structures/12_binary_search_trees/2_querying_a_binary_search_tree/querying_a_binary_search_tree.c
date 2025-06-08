#include "part_3_data_structures/12_binary_search_trees/binary_search_trees.h"

BSTNodeWithParent* bts_with_node_parent_init(int key) {
    BSTNodeWithParent* newNode = (BSTNodeWithParent*)malloc(sizeof(BSTNodeWithParent));
    newNode->key = key;
    newNode->left = NULL;   
    newNode->right = NULL; 
    newNode->parent = NULL; 

    return newNode;  
}

BSTNodeWithParent* bts_with_node_parent_insert(BSTNodeWithParent* root, int key) {
    if (root == NULL) return bts_with_node_parent_init(key);
    
    BSTNodeWithParent* parent = NULL;
    BSTNodeWithParent* current = root;
    while (current != NULL) {
        parent = current;
        if (key < current->key) current = current->left;
        else if (key > current->key) current = current->right;
        else return root; 
    }

    BSTNodeWithParent* newNode = bts_with_node_parent_init(key);
    newNode->parent = parent;
    if (key < parent->key) parent->left = newNode;
    else parent->right = newNode;

    return root;
}

BSTNodeWithParent* bts_with_node_parent_tree_min(BSTNodeWithParent* root) {
    if (root->left != NULL) return bts_with_node_parent_tree_min(root->left);
    return root;
}

BSTNodeWithParent* bts_with_node_parent_tree_max(BSTNodeWithParent* root) {
    if (root->right != NULL) return bts_with_node_parent_tree_max(root->right);
    return root;
}

void bts_with_node_parent_tree_print_min_max(BSTNodeWithParent* root) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }
    BSTNodeWithParent* minNode = bts_with_node_parent_tree_min(root);
    BSTNodeWithParent* maxNode = bts_with_node_parent_tree_max(root);
    printf("Minimum key: %d\n", minNode->key);
    printf("Maximum key: %d\n", maxNode->key);
}

BSTNodeWithParent* bts_with_node_parent_tree_predecessor(BSTNodeWithParent* x) {
    if (x->left != NULL) return bts_with_node_parent_tree_max(x->left);
    BSTNodeWithParent* y = x->parent;
    while (y != NULL && x == y->left) {
        x = y;
        y = y->parent;
    }
    return y;
}

BSTNodeWithParent* bts_with_node_parent_tree_search(BSTNodeWithParent* root, int key) {
    if (root == NULL || root->key == key) return root;
    if (key < root->key) return bts_with_node_parent_tree_search(root->left, key);
    if (key > root->key) return bts_with_node_parent_tree_search(root->right, key);
    return NULL;
}

BSTNodeWithParent* bts_with_node_parent_tree_search_iter(BSTNodeWithParent* root, int key) {
    while (root != NULL && root->key != key) {
        if (key < root->key) root = root->left;
        else root = root->right;
    }
    return root;
}

BSTNodeWithParent* bts_with_node_parent_tree_successor(BSTNodeWithParent* x) {
    if (x->right != NULL) return bts_with_node_parent_tree_min(x->right);
    BSTNodeWithParent* y = x->parent;
    while (y != NULL && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}