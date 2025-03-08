#include <stdio.h>
#include <stdlib.h>

typedef struct BSTNode {
    int data;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

BSTNode* init_node(int data) {
    BSTNode* newNode = (BSTNode*)malloc(sizeof(BSTNode));
    newNode->data = data;
    newNode->left = NULL;   
    newNode->right = NULL; 

    return newNode;  
}

BSTNode* insert(BSTNode* root, int data) {
    if (root == NULL) return init_node(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data) 
        root->right = insert(root->right, data);

    return root;
}

void inorder_traversal(BSTNode* root) {
    if (root == NULL) return;

    inorder_traversal(root->left);
    printf("%d ", root->data);
    inorder_traversal(root->right);
}

void preorder_traversal(BSTNode* root) {
    if (root == NULL) return;

    printf("%d ", root->data);
    preorder_traversal(root->left);
    preorder_traversal(root->right);
}

void postorder_traversal(BSTNode* root) {
    if (root == NULL) return;

    postorder_traversal(root->left);
    postorder_traversal(root->right);
    printf("%d ", root->data);
}

int main(void) {
    BSTNode* root = NULL;
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++)
        root = insert(root, values[i]);

    printf("Inorder Traversal: ");
    inorder_traversal(root);
    printf("\n");

    printf("Preorder Traversal: ");
    preorder_traversal(root);
    printf("\n");

    printf("Postorder Traversal: ");
    postorder_traversal(root);
    printf("\n");

    return 0;
}