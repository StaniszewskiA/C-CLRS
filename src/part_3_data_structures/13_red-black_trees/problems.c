#include "part_3_data_structures/13_red-black_trees/red-black_trees.h"

#define TASK 3

Node2* node2_create(int key) {
    Node2* node = (Node2*)malloc(sizeof(Node2));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node2* node2_copy(Node2* target) {
    if (target == NULL) return NULL;
    Node2* copy = (Node2*)malloc(sizeof(Node2));
    *copy = *target;
    return copy;
}

void persistent_tree_insert(PersistentTree *tree, int k) {
    if (tree->root == NULL) {
        tree->root = node2_create(k);
        return;
    }

    Node2 *x = tree->root, *y = NULL;
    while (x != NULL) {
        y = x;
        if (k < x->key) {
            x = x->left;
            y->left = node2_copy(x);
        } else {
            x = x->right;
            y->right = node2_copy(x);
        }
    }

    Node2 *z = node2_create(k);
    if (k < y->key) y->left = z;
    else y->right = z; 
}

int avl_node_get_height(AVLNode *node) {
    return (node == NULL) ? 0 : node->height; 
}

int avl_node_get_balance_factor(AVLNode *node) {
    return (node == NULL) ? 0 : avl_node_get_height(node->left) - avl_node_get_height(node->right);
}

AVLNode* avl_node_create_node(int key) {
    AVLNode *node = (AVLNode*)malloc(sizeof(AVLNode));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

AVLNode* avl_tree_right_rotate(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    y->right = y;
    y->left = T2;

    y->height = 1 + (
        (avl_node_get_height(y->left) > avl_node_get_height(y->right)) 
        ? avl_node_get_height(y->left) 
        : avl_node_get_height(y->right)
    );

    x->height = 1 + (
        (avl_node_get_height(x->left) > avl_node_get_height(x->right)) 
        ? avl_node_get_height(x->left) 
        : avl_node_get_height(x->right)
    );

    return x;
}

AVLNode* avl_tree_left_rotate(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + (
        (avl_node_get_height(x->left) > avl_node_get_height(x->right)) 
        ? avl_node_get_height(x->left) 
        : avl_node_get_height(x->right)
    );

    y->height = 1 + (
        (avl_node_get_height(y->left) > avl_node_get_height(y->right)) 
        ? avl_node_get_height(y->left) 
        : avl_node_get_height(y->right)
    );

    return y;
}

AVLNode* avl_tree_insert(AVLNode *node, int key) {
    if (node == NULL) return avl_node_create_node(key);

    if (key < node->key) node->left = avl_tree_insert(node->left, key);
    else if (key > node->key) node->right = avl_tree_insert(node->right, key);
    else return node;

    node->height = 1 + (
        (avl_node_get_height(node->left) > avl_node_get_height(node->right)) 
        ? avl_node_get_height(node->left) 
        : avl_node_get_height(node->right)
    );

    int avl_tree_balance = avl_node_get_balance_factor(node);

    if (avl_tree_balance > 1 && key < node->left->key) return avl_tree_right_rotate(node);
    if (avl_tree_balance < -1 && key > node->right->key) return avl_tree_left_rotate(node);
    if (avl_tree_balance > 1 && key > node->left->key) {
        node->left = avl_tree_left_rotate(node->left);
        return avl_tree_right_rotate(node);
    }
    if (avl_tree_balance < -1 && key < node->right->key) {
        node->right = avl_tree_right_rotate(node->right);
        return avl_tree_left_rotate(node);
    }

    return node;
}

AVLNode* avl_tree_search(AVLNode *root, int key) {
    if (root == NULL || root->key == key) return root;
    
    if (key < root->key) return avl_tree_search(root->left, key);
    else return avl_tree_search(root->right, key);
}

void avl_tree_inorder_traversal(AVLNode *root) {
    if (root != NULL) {
        avl_tree_inorder_traversal(root->left);
        printf("%d ", root->key);
        avl_tree_inorder_traversal(root->right);
    }
}

void avl_tree_balance(AVLNode **root) {
    AVLNode *node = *root;
    while (node != NULL) {
        int avl_tree_balance = avl_node_get_balance_factor(node);

        if (avl_tree_balance > 1) {
            if (avl_node_get_balance_factor(node->left) >= 0) node = avl_tree_right_rotate(node);
            else {
                node->left = avl_tree_left_rotate(node->left);
                node = avl_tree_right_rotate(node);
            }
        } else if (avl_tree_balance < -1) {
            if (avl_node_get_balance_factor(node->right) <= 0) node = avl_tree_left_rotate(node);
            else {
                node->right = avl_tree_right_rotate(node->right);
                node = avl_tree_left_rotate(node);
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

        root = avl_tree_insert(root, 10);
        root = avl_tree_insert(root, 20);
        root = avl_tree_insert(root, 30);
        root = avl_tree_insert(root, 40);
        root = avl_tree_insert(root, 50);
        root = avl_tree_insert(root, 25);

        printf("Inorder traversal of the AVL tree: ");
        avl_tree_inorder_traversal(root);
        printf("\n");

        int key = 25;
        if (avl_tree_search(root, key))
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