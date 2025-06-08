#include "part_3_data_structures/13_red-black_trees/red-black_trees.h"

RedBlackNode* rb_node_create(RedBlackTree *tree, int data) {
    RedBlackNode* node = (RedBlackNode*)malloc(sizeof(RedBlackNode));
    node->data = data;
    node->color = RED;
    node->left = tree->nil;
    node->right = tree->nil;
    node->parent = NULL;
    return node;
}

void rb_tree_left_rotate(RedBlackTree *tree, RedBlackNode *x) {
    RedBlackNode *y = x->right;
    x->right = y->left;

    if (y->left != tree->nil) y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL) tree->root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void rb_tree_right_rotate(RedBlackTree *tree, RedBlackNode *y) {
    RedBlackNode *x = y->left;
    y->left = x->right;

    if (x->right != tree->nil) x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == NULL) tree->root = x;
    else if (y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;

    x->right = y;
    y->parent = x;
}

void rb_tree_insert_fixup(RedBlackTree *tree, RedBlackNode *z) {
    while (z->parent != NULL && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            RedBlackNode *y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    rb_tree_left_rotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rb_tree_right_rotate(tree, z->parent->parent);
            }
        } else {
            RedBlackNode *y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rb_tree_right_rotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rb_tree_left_rotate(tree, z->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}

void rb_tree_insert(RedBlackTree *tree, int data) {
    RedBlackNode *z = rb_node_create(tree, data);
    RedBlackNode *x = tree->root;
    RedBlackNode *y = NULL;

    while (x != tree->nil) {
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

    z->left = tree->nil;
    z->right = tree->nil;
    z->color = RED;

    rb_tree_insert_fixup(tree, z);
}

void rb_tree_transplant(RedBlackTree *tree, RedBlackNode *u, RedBlackNode *v) {
    if (u->parent == NULL) tree->root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;

    v->parent = u->parent;
}

void rb_tree_delete_fixup(RedBlackTree *tree, RedBlackNode *x) {
    while (x != tree->root && x->color == BLACK) {
        if (x == x->parent->left) {
            RedBlackNode *w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rb_tree_left_rotate(tree, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rb_tree_right_rotate(tree, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                rb_tree_left_rotate(tree, x->parent);
                x = tree->root;
            }
        } else {
            RedBlackNode *w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rb_tree_right_rotate(tree, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {  
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    rb_tree_left_rotate(tree, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rb_tree_right_rotate(tree, x->parent);
                x = tree->root;
            }
        }
    }
    x->color = BLACK;
}

RedBlackNode* rb_tree_get_min(RedBlackTree *tree, RedBlackNode *node) {
    while (node->left != tree->nil) node = node->left;
    return node;
}

void rb_tree_delete(RedBlackTree *tree, RedBlackNode *z) {
    RedBlackNode *y = z;
    RedBlackNode *x;
    NodeColor y_original_color = y->color;

    if (z->left == tree->nil) {
        x = z->right;
        rb_tree_transplant(tree, z, z->right);
    } else if (z->right == tree->nil) {
        x = z->left;
        rb_tree_transplant(tree, z, z->left);
    } else {
        y = rb_tree_get_min(tree, z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) x->parent = y;
        else {
            rb_tree_transplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        rb_tree_transplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    free(z);

    if (y_original_color == BLACK) rb_tree_delete_fixup(tree, x);
}

void rb_tree_enumerate(RedBlackTree *tree, RedBlackNode *r, int a, int b) {
    if (r == tree->nil) return;
    
    if (a <= r->data) rb_tree_enumerate(tree, r->left, a, b);
    if (a <= r->data && r->data <= b) printf("%d ", r->data);
    if (r->data <= b) rb_tree_enumerate(tree, r->right, a, b);
}

RedBlackNode* rb_tree_join(
    RedBlackTree *tree, 
    RedBlackNode *T1, 
    RedBlackNode *x, 
    RedBlackNode *T2
) {
    rb_tree_transplant(tree, T1, x);

    x->left = T1;
    x->right = T2;

    if (T1 != tree->nil) T1->parent = x;
    if (T2 != tree->nil) T2->parent = x;

    return x;
}

RedBlackNode* rb_tree_search(RedBlackTree *tree, int data) {
    RedBlackNode *current = tree->root;
    while (current != tree->nil && current->data != data) {
        if (data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return current == tree->nil ? NULL : current;
}

void rb_tree_inorder_traversal(RedBlackTree *tree, RedBlackNode *node) {
    if (node != tree->nil) {
        rb_tree_inorder_traversal(tree, node->left);
        printf("%d(%s) ", node->data, node->color == RED ? "R" : "B");
        rb_tree_inorder_traversal(tree, node->right);
    }
}