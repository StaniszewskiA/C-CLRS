#include "part_3_data_structures/10_elementary_data_structures/elementary_data_structures.h"

TreeNode* tree_node_create(int key, TreeNode* parent) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (!newNode) {
        perror("Malloc failed!");
        return NULL;
    }
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = parent;

    return newNode;
}

void tree_node_free(TreeNode* node) {
    free(node);
}

void tree_free(TreeNode* root) {
    if (!root) return;
    tree_free(root->left);
    tree_free(root->right);
    free(root);
}

void print_tree(TreeNode* root) {
    if (!root) return;    
    printf("%d ", root->key);
    print_tree(root->left);
    print_tree(root->right);
}

TreeStackNode* tree_stack_push(TreeStackNode* top, TreeNode* treeNode) {
    TreeStackNode* newNode = (TreeStackNode*)malloc(sizeof(TreeStackNode));
    if (!newNode) {
        perror("Failed to allocate memory for stack");
        exit(EXIT_FAILURE);
    }
    newNode->treeNode = treeNode;
    newNode->next = top;

    return newNode;
}

TreeStackNode* tree_stack_pop(TreeStackNode* top, TreeNode** treeNode) {
    if (!top) return NULL;   
    *treeNode = top->treeNode;
    TreeStackNode* temp = top;
    top = top->next;
    free(temp);

    return top;
}

void print_tree_iterative(TreeNode* root) {
    if (!root) return;

    TreeStackNode* stack = NULL;
    stack = tree_stack_push(stack, root);

    while (stack) {
        TreeNode* node;
        stack = tree_stack_pop(stack, &node);
        printf("%d ", node->key);

        if (node->right) stack = tree_stack_push(stack, node->right);
        if (node->left) stack = tree_stack_push(stack, node->left);
    }
}

void print_tree_recursive(TreeNode* root) {
    if (!root) return;
    
    printf("%d ", root->key);
    print_tree_recursive(root->left);
    print_tree_recursive(root->right);
}

DepthTreeNode* create_depth_tree_node(int key, int b) {
    DepthTreeNode* newNode = (DepthTreeNode*)malloc(sizeof(DepthTreeNode));
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

void depth_tree_free(DepthTreeNode* root) {
    if (!root) return;
    depth_tree_free(root->left);
    depth_tree_free(root->right);
    free(root);
}

void print_depth_tree(DepthTreeNode* root) {
    if (!root) return;
    printf("%d ", root->key);
    print_depth_tree(root->left);
    print_depth_tree(root->right);
}

void create_sample_depth_tree(DepthTreeNode* root, int depth, int maxDepth) {
    if (!root || depth >= maxDepth) return;

    int b = (depth % 2 == 0);

    root->left = create_depth_tree_node(root->key * 10 + 1, b);
    root->left->right = create_depth_tree_node(root->key * 10 + 2, b);

    create_sample_depth_tree(root->left, depth + 1, maxDepth); 
    create_sample_depth_tree(root->left->right, depth + 1, maxDepth);
}

void depth_tree_traverse(DepthTreeNode* root, int parB) {
    if (!root) return;

    printf("Visiting node: %d (b=%d)\n", root->key, root->b);

    if (root->b != parB) {
        printf("Going to child: %d (b=%d)\n", root->key, root->b);
        depth_tree_traverse(root->left, root->b);  
    } else {
        printf("Going to sibling: %d (b=%d)\n", root->key, root->b);
        depth_tree_traverse(root->right, parB); 
    }
}
