#include <stdio.h>
#include <stdlib.h>

#define TASK 3

typedef struct BSTNode {
    int key;
    struct BSTNode* left;
    struct BSTNode* right;
    struct BSTNode* parent;
} BSTNode;

BSTNode* init_node(int key) {
    BSTNode* newNode = (BSTNode*)malloc(sizeof(BSTNode));
    newNode->key = key;
    newNode->left = NULL;   
    newNode->right = NULL; 
    newNode->parent = NULL; 

    return newNode;  
}

BSTNode* insert(BSTNode* root, int key) {
    if (root == NULL) return init_node(key);
    
    BSTNode* parent = NULL;
    BSTNode* current = root;
    while (current != NULL) {
        parent = current;
        if (key < current->key) current = current->left;
        else if (key > current->key) current = current->right;
        else return root; 
    }

    BSTNode* newNode = init_node(key);
    newNode->parent = parent;
    if (key < parent->key) parent->left = newNode;
    else parent->right = newNode;

    return root;
}

BSTNode* tree_min(BSTNode* root) {
    if (root->left != NULL) return tree_min(root->left);
    return root;
}

BSTNode* tree_max(BSTNode* root) {
    if (root->right != NULL) return tree_max(root->right);
    return root;
}

void print_min_max(BSTNode* root) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }
    BSTNode* minNode = tree_min(root);
    BSTNode* maxNode = tree_max(root);
    printf("Minimum key: %d\n", minNode->key);
    printf("Maximum key: %d\n", maxNode->key);
}

BSTNode* tree_predecessor(BSTNode* x) {
    if (x->left != NULL) return tree_max(x->left);
    BSTNode* y = x->parent;
    while (y != NULL && x == y->left) {
        x = y;
        y = y->parent;
    }
    return y;
}

BSTNode* tree_search(BSTNode* root, int key) {
    if (root == NULL || root->key == key) return root;
    if (key < root->key) return tree_search(root->left, key);
    if (key > root->key) return tree_search(root->right, key);
}

BSTNode* tree_search_iter(BSTNode* root, int key) {
    while (root != NULL && root->key != key) {
        if (key < root->key) root = root->left;
        else root = root->right;
    }
    return root;
}

BSTNode* tree_successor(BSTNode* x) {
    if (x->right != NULL) return tree_min(x->right);
    BSTNode* y = x->parent;
    while (y != NULL && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}

int main(void) {
    BSTNode* root = init_node(50);

    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    switch (TASK)
    {
    case 1: {        
        print_min_max(root);

        BSTNode* node = root->left; 
        BSTNode* pred = tree_predecessor(node);
        if (pred != NULL)
            printf("Predecessor of %d is %d\n", node->key, pred->key);
        else
            printf("No predecessor for %d\n", node->key);

        break;
    }
    case 2: {
        const int searchKey = 40;
        BSTNode* searchResult = tree_search(root, searchKey);
        if (searchResult != NULL)
            printf("Key %d found in the tree.\n", searchKey);
        else
            printf("Key %d not found in the tree.\n", searchKey);

        BSTNode* searchResultIter = tree_search_iter(root, searchKey);
        if (searchResult != NULL)
            printf("Key %d found in the tree iteratively.\n", searchKey);
        else
            printf("Key %d not found in the tree iteratively.\n", searchKey);

        break;
    }
    case 3: {
        BSTNode* node = root->left; 
        BSTNode* succ = tree_successor(node);
        if (succ != NULL)
            printf("Successor of %d is %d\n", node->key, succ->key);
        else
            printf("No successor for %d\n", node->key);

        break;
    }
    default:
        break;
    }

    return 0;
}