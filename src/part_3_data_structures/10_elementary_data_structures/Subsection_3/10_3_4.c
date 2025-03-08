#include <stdio.h>
#include <stdlib.h>

//---------- Tree Node (Son on Left, Brother on Right) ----------
typedef struct TreeNode {
    int key;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* create_tree_node(int key) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

void print_tree_recursive(TreeNode* root) {
    if (!root) return;
    
    printf("%d ", root->key);
    print_tree_recursive(root->left);
    print_tree_recursive(root->right);
}


void free_tree(TreeNode* root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main(void) {
    /*
        Representing this tree:

                1
             /  |  \
            2   3   4
           / \     /  \
          5   6   7    8
    */
    TreeNode* root = create_tree_node(1);
    root->left = create_tree_node(2);  
    root->left->right = create_tree_node(3);  
    root->left->right->right = create_tree_node(4); 

    root->left->left = create_tree_node(5); 
    root->left->left->right = create_tree_node(6); 

    root->left->right->right->left = create_tree_node(7);  
    root->left->right->right->left->right = create_tree_node(8); 

    printf("Tree (SLBR, Iterative Without Stack): ");
    print_tree_recursive(root);
    printf("\n");

    free_tree(root);
    return 0;
}