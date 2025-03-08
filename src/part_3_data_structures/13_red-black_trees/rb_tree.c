#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } NodeColor;

typedef struct Node {
    int data;
    NodeColor color;
    struct Node *left, *right, *parent;
} Node;

typedef struct RedBlackTree {
    Node *root;
    Node *NIL; // guardian
} RedBlackTree;

Node* create_node(RedBlackTree *tree, int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->color = RED;
    node->left = tree->NIL;
    node->right = tree->NIL;
    node->parent = NULL;
    return node;
}

void left_rotate(RedBlackTree *tree, Node *x) {
    Node *y = x->right;
    x->right = y->left;

    if (y->left != tree->NIL) y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL) tree->root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;

    x->left = x;
    x->parent = y;
}

void right_rotate(RedBlackTree *tree, Node *y) {
    Node *x = y->right;
    y->left = x->right;

    if (x->right != tree->NIL) y->right->parent = y;

    x->parent = y->parent;

    if (y->parent == NULL) tree->root = x;
    else if (y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;

    x->right = y;
    y->parent = x;
}

void rb_insert_fixup(RedBlackTree *tree, Node *z) {
    while (z->parent != NULL & z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node *y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    left_rotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                right_rotate(tree, z->parent->parent);
            }
        } else {
            Node *y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    right_rotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                left_rotate(tree, z->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}

void insert(RedBlackTree *tree, int data) {
    Node *z = create_node(tree, data);
    Node *x = tree->root;
    Node *y = NULL;

    while (x != tree->NIL) {
        y = x;
        if (z->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    z->parent = y;
    if (y == NULL) {
        tree->root = z;
    } else if (z->data < y->data) {
        y->left = z;
    } else {
        y->right = z;
    }

    z->left = tree->NIL;
    z->right = tree->NIL;
    z->color = RED;

    rb_insert_fixup(tree, z);
}

void rb_transplant(RedBlackTree *tree, Node *u, Node *v) {
    if (u->parent == NULL) tree->root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;

    v->parent = u->parent;
}

void rb_delete_fixup(RedBlackTree *tree, Node *x) {
    while (x != tree->root && x->color == BLACK){
        if (x == x->parent->left) {
            Node *w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                left_rotate(tree, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    right_rotate(tree, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                left_rotate(tree, x->parent);
                x = tree->root;
            }
        } else {
            Node *w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                right_rotate(tree, x->parent);
                w = x->parent->left;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    left_rotate(tree, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                right_rotate(tree, x->parent);
                x = tree->root;
            }
        }
    }
    x->color = BLACK;
}

Node* rb_minimum(RedBlackTree *tree, Node *node) {
    while (node->left != tree->NIL) node = node->left;
    return node;
}

void rb_delete(RedBlackTree *tree, Node *z) {
    Node *y = z;
    Node *x;
    NodeColor y_original_color = y->color;

    if (z->left == tree->NIL) {
        x = z->right;
        rb_transplant(tree, z, z->right);
    } else if (z->right == tree->NIL) {
        x = z->left;
        rb_transplant(tree, z, z->left);
    } else {
        y = rb_minimum(tree, z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) x->parent = y;
        else {
            rb_transplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        rb_transplant(tree, z, y);
        y->left = z->left;
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    free(z);

    if (y_original_color == BLACK) rb_delete_fixup(tree, x);
}

void rb_enumerate(RedBlackTree *tree, Node *r, int a, int b) {
    if (r == tree->NIL) return;
    
    if (a <= r->data) rb_enumerate(tree, r->left, a, b);
    if (a <= r->data && r->data <= b) printf("%d ", r->data);
    if (r->data <= b) rb_enumerate(tree, r->right, a, b);
}

Node* rb_join(RedBlackTree *tree, Node *T1, Node *x, Node *T2) {
    rb_transplant(tree, T1, x);

    x->left = T1;
    x->right = T2;

    if (T1 != tree->NIL) T1->parent = x;
    if (T2 != tree->NIL) T2->parent = x;

    return x;
}

int main(void) {
    RedBlackTree *tree = malloc(sizeof(RedBlackTree));
    tree->NIL = malloc(sizeof(Node));
    tree->NIL->color = BLACK;
    tree->root = tree->NIL;

    insert(tree, 10);
    insert(tree, 20);
    insert(tree, 30);
    insert(tree, 15);
    insert(tree, 25);
    insert(tree, 5);
    insert(tree, 35);

    printf("Nodes in range [10, 25]: ");
    rb_enumerate(tree, tree->root, 10, 25);
    printf("\n");

    Node *target = tree->root->right;
    rb_delete(tree, target);

    printf("Nodes in range [10, 25] after deletion: ");
    rb_enumerate(tree, tree->root, 10, 25);
    printf("\n");

    return 0;
}
