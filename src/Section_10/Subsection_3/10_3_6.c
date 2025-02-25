#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TreeNode {
    int key;
    struct TreeNode* left;
    struct TreeNode* right;
    bool b; // depth % 2
} TreeNode;

TreeNode* create_tree_node(int key, bool b) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (!newNode) {
        perror("Malloc failed!");
        return NULL;  
    }
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->b = b; 
    
    return newNode;
}

void free_tree(TreeNode* root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

void print_tree(TreeNode* root) {
    if (!root) return;
    printf("%d ", root->key);
    print_tree(root->left);
    print_tree(root->right);
}

void create_sample_tree(TreeNode* root, int depth, int maxDepth) {
    if (!root || depth >= maxDepth) return;

    bool b = (depth % 2 == 0);

    root->left = create_tree_node(root->key * 10 + 1, b);
    root->left->right = create_tree_node(root->key * 10 + 2, b);

    create_sample_tree(root->left, depth + 1, maxDepth); 
    create_sample_tree(root->left->right, depth + 1, maxDepth);
}

void traverse_tree(TreeNode* root, bool parent_b) {
    if (!root) return;

    printf("Visiting node: %d (b=%d)\n", root->key, root->b);

    if (root->b != parent_b) {
        printf("Going to child: %d (b=%d)\n", root->key, root->b);
        traverse_tree(root->left, root->b);  
    } else {
        printf("Going to sibling: %d (b=%d)\n", root->key, root->b);
        traverse_tree(root->right, parent_b); 
    }
}

int main(void) {
    int maxDepth = 3;
    TreeNode* root = create_tree_node(1, true);
    if (root == NULL) return EXIT_FAILURE;

    create_sample_tree(root, 1, maxDepth);

    printf("Tree (Pre-order): ");
    print_tree(root);
    printf("\n");

    printf("Tree Traversal:\n");
    traverse_tree(root, root->b);

    return 0;
}