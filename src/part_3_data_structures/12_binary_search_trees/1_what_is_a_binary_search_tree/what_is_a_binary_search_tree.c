#include "part_3_data_structures/12_binary_search_trees/binary_search_trees.h"

BSTNode* bst_node_init(int data) {
    BSTNode* newNode = (BSTNode*)malloc(sizeof(BSTNode));
    newNode->data = data;
    newNode->left = NULL;   
    newNode->right = NULL; 

    return newNode;  
}

BSTNode* bst_insert(BSTNode* root, int data) {
    if (root == NULL) return bst_node_init(data);

    if (data < root->data)
        root->left = bst_insert(root->left, data);
    else if (data > root->data) 
        root->right = bst_insert(root->right, data);

    return root;
}

void bst_inorder_traversal(BSTNode* root) {
    if (root == NULL) return;

    bst_inorder_traversal(root->left);
    printf("%d ", root->data);
    bst_inorder_traversal(root->right);
}

void bst_preorder_traversal(BSTNode* root) {
    if (root == NULL) return;

    printf("%d ", root->data);
    bst_preorder_traversal(root->left);
    bst_preorder_traversal(root->right);
}

void bst_postorder_traversal(BSTNode* root) {
    if (root == NULL) return;

    bst_postorder_traversal(root->left);
    bst_postorder_traversal(root->right);
    printf("%d ", root->data);
}