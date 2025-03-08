#include <stdio.h>
#include <stdlib.h>

#define TASK 3

//-----Persistent Trees-----
typedef struct Node {
    int key;
    struct Node *left, *right;
} Node;

typedef struct PersistentTree {
    Node *root;
} PersistentTree;

Node* new_node(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node* copy_node(Node* target) {
    if (target == NULL) return NULL;
    Node* copy = (Node*)malloc(sizeof(Node));
    *copy = *target;
    return copy;
}

void persistent_tree_insert(PersistentTree *tree, int k) {
    if (tree->root == NULL) {
        tree->root = new_node(k);
        return;
    }

    Node *x = tree->root, *y = NULL;
    while (x != NULL) {
        y = x;
        if (k < x->key) {
            x = x->left;
            y->left = copy_node(x);
        } else {
            x = x->right;
            y->right = copy_node(x);
        }
    }

    Node *z = new_node(k);
    if (k < y->key) y->left = z;
    else y->right = z; 
}

//-----AVL Trees-----
typedef struct AVLNode {
    int key;
    struct AVLNode *left; 
    struct AVLNode *right;
    int height; 
} AVLNode;

int get_height(AVLNode *node) {
    return (node == NULL) ? 0 : node->height; 
}

int get_balance_factor(AVLNode *node) {
    return (node == NULL) ? 0 : get_height(node->left) - get_height(node->right);
}

AVLNode *create_node(int key) {
    AVLNode *node = (AVLNode*)malloc(sizeof(AVLNode));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

AVLNode *right_rotate(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    y->right = y;
    y->left = T2;

    y->height = 1 + (
        (get_height(y->left) > get_height(y->right)) 
        ? get_height(y->left) 
        : get_height(y->right)
    );

    x->height = 1 + (
        (get_height(x->left) > get_height(x->right)) 
        ? get_height(x->left) 
        : get_height(x->right)
    );

    return x;
}

AVLNode *left_rotate(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + (
        (get_height(x->left) > get_height(x->right)) 
        ? get_height(x->left) 
        : get_height(x->right)
    );

    y->height = 1 + (
        (get_height(y->left) > get_height(y->right)) 
        ? get_height(y->left) 
        : get_height(y->right)
    );

    return y;
}

AVLNode *avl_insert(AVLNode *node, int key) {
    if (node == NULL) return create_node(key);

    if (key < node->key) node->left = avl_insert(node->left, key);
    else if (key > node->key) node->right = avl_insert(node->right, key);
    else return node;

    node->height = 1 + (
        (get_height(node->left) > get_height(node->right)) 
        ? get_height(node->left) 
        : get_height(node->right)
    );

    int balance = get_balance_factor(node);

    if (balance > 1 && key < node->left->key) return right_rotate(node);
    if (balance < -1 && key > node->right->key) return left_rotate(node);
    if (balance > 1 && key > node->left->key) {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }

    return node;
}

AVLNode *search(AVLNode *root, int key) {
    if (root == NULL || root->key == key) return root;
    
    if (key < root->key) return search(root->left, key);
    else return search(root->right, key);
}

void inorder(AVLNode *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

void balance(AVLNode **root) {
    AVLNode *node = *root;
    while (node != NULL) {
        int balance = get_balance_factor(node);

        if (balance > 1) {
            if (get_balance_factor(node->left) >= 0) node = right_rotate(node);
            else {
                node->left = left_rotate(node->left);
                node = right_rotate(node);
            }
        } else if (balance < -1) {
            if (get_balance_factor(node->right) <= 0) node = left_rotate(node);
            else {
                node->right = right_rotate(node->right);
                node = left_rotate(node);
            }
        }

        node = node->left ? node->left : node->right;
    }

    *root = node;
}

int main(void) {
    switch (TASK)
    {
    case 1: {
        PersistentTree tree = {NULL};
        persistent_tree_insert(&tree, 10);
        persistent_tree_insert(&tree, 5);
        persistent_tree_insert(&tree, 15);
        persistent_tree_insert(&tree, 3);
        persistent_tree_insert(&tree, 7);

        printf("Done!");

        break;
    }
    case 3: {
        AVLNode *root = NULL;

        root = avl_insert(root, 10);
        root = avl_insert(root, 20);
        root = avl_insert(root, 30);
        root = avl_insert(root, 40);
        root = avl_insert(root, 50);
        root = avl_insert(root, 25);

        printf("Inorder traversal of the AVL tree: ");
        inorder(root);
        printf("\n");

        int key = 25;
        if (search(root, key))
            printf("%d found in AVL tree\n", key);
        else
            printf("%d not found in AVL tree\n", key);

        break;
    }
    default:
        break;
    }
    
    return 0;
}