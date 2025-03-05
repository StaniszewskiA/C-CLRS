#include <stdio.h>
#include <stdlib.h>

#define TASK 2

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

void insert_node(BSTNode* parentNode, BSTNode* currNode, BSTNode* newNode) {
    if (currNode == NULL) {
        newNode->parent = parentNode;
        if (newNode->key < parentNode->key) parentNode->left = newNode;
        else parentNode->right = newNode;
    } 
    else if (newNode->key < currNode->key) insert_node(currNode, currNode->left, newNode);
    else insert_node(currNode, currNode->right, newNode); 
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

typedef struct BST {
    BSTNode* root;
} BST;

void recursive_tree_insert(BST* tree, BSTNode* newNode) {
    if (tree->root == NULL) tree->root = newNode;
    else insert_node(NULL, tree->root, newNode);
}

void tree_transplant(BST* tree, BSTNode* u, BSTNode* v) {
    if (u->parent == NULL) tree->root = v;
    else if (u = u->parent->left) u->parent->left = v;
    else u->parent->right = v;

    if (v != NULL) v->parent = u->parent;
}

void tree_delete(BST* tree, BSTNode* target) {
    if (target->left == NULL) tree_transplant(tree, target, target->right);
    else if (target->right == NULL) tree_transplant(tree, target, target->left);
    else {
        BSTNode* successor = tree_min(target->right);
        if (successor->parent != target) {
            tree_transplant(tree, successor, successor->right);
            successor->right = target->right;
            successor->right->parent = successor;
        }
        tree_transplant(tree, target, successor);
        successor->left = target->left;
        successor->left->parent = successor;
    }
    free(target);
}

int main(void) {
    switch (TASK)
    {
    case 1: {        
        BSTNode* root = init_node(50); 
        BSTNode* newNode = init_node(40); 

        insert_node(root, root, newNode); 

        break;
    }
    case 2: {
        BST* tree = (BST*)malloc(sizeof(BST)); 
        tree->root = NULL; 

        BSTNode* newNode = init_node(40); 

        recursive_tree_insert(tree, newNode);

        BSTNode* u = tree_search(tree->root, 40);  
        BSTNode* v = tree_search(tree->root, 20);  

        tree_transplant(tree, u, v); 

        BSTNode* nodeToDelete = tree_search(tree->root, 40);  
        if (nodeToDelete != NULL) {
            tree_delete(tree, nodeToDelete); 
        }
    }
    default:
        break;
    }

    return 0;
}