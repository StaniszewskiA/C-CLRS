#include <stdio.h>
#include <stdlib.h>

#define TASK 1

//----------Task 1----------
typedef struct Node {
    int key;
    struct TreeNode* next;
    struct TreeNode* prev;
} Node;

typedef struct TreeNode {
    int key;
    struct TreeNode* left;
    struct TreeNode* right;
    struct TreeNode* parent;
} TreeNode;

TreeNode* create_tree_node(int key, TreeNode* parent) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (!newNode) {
        perror("Malloc failed!");
        return (EXIT_FAILURE);
    }
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = parent;

    return newNode;
}

void free_tree_node(TreeNode* node) {
    free(node);
}

void free_tree(TreeNode* root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

// Recursive pre-order print
void print_tree(TreeNode* root) {
    if (!root) return;    
    printf("%d ", root->key);
    print_tree(root->left);
    print_tree(root->right);
}

int main(void) {
    switch (TASK) {
        case 1: {
            TreeNode* root = create_tree_node(1, NULL);
            root->left = create_tree_node(2, root);
            root->right = create_tree_node(3, root);
            root->left->left = create_tree_node(4, root->left);
            root->right->right = create_tree_node(5, root->right);

            printf("Tree (Pre-order): ");
            print_tree(root);
            printf("\n");

            free_tree(root);
            break;
        }   
        default:
            break;
    }
}