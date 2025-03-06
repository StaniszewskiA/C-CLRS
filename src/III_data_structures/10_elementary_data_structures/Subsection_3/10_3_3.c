#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int key;
    struct TreeNode* left;
    struct TreeNode* right;
    struct TreeNode* parent;
} TreeNode;

typedef struct StackNode {
    TreeNode* treeNode;
    struct StackNode* next; 
} StackNode;

StackNode* push(StackNode* top, TreeNode* treeNode) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (!newNode) {
        perror("Failed to allocate memory for stack");
        exit(EXIT_FAILURE);
    }
    newNode->treeNode = treeNode;
    newNode->next = top;

    return newNode;
}

StackNode* pop(StackNode* top, TreeNode** treeNode) {
    if (!top) return NULL;   
    *treeNode = top->treeNode;
    StackNode* temp = top;
    top = top->next;
    free(temp);

    return top;
}

TreeNode* create_tree_node(int key, TreeNode* parent) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (!newNode) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = parent;

    return newNode;
}

// Iterative pre-oder traversal with stack
void print_tree_iterative(TreeNode* root) {
    if (!root) return;

    StackNode* stack = NULL;
    stack = push(stack, root);

    while (stack) {
        TreeNode* node;
        stack = pop(stack, &node);
        printf("%d ", node->key);

        if (node->right) stack = push(stack, node->right);
        if (node->left) stack = push(stack, node->left);
    }
}

void free_tree(TreeNode* root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main(void) {
    TreeNode* root = create_tree_node(1, NULL);
    root->left = create_tree_node(2, root),
    root->right = create_tree_node(3, root),
    root->left->left = create_tree_node(4, root->left);
    root->right->right = create_tree_node(5, root->right);

    printf("Tree (pre-order, itrerative): ");
    print_tree_iterative(root);
    printf("\n");

    free_tree(root);

    return 0;
}