#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TASK 2

#define RED 0
#define BLACK 1

typedef unsigned int uint;

#pragma region The point with the highest number of intersections
/*
    17-1
*/
typedef struct RBNode {
    int endpoint;
    int delta;
    int intersections;
    int maxIntersections;
    int color;
    struct RBNode* left;
    struct RBNode* right;
    struct RBNode* parent;
} RBNode;

typedef struct RBTree {
    RBNode* root;
    RBNode* nil; // sentinel
} RBTree;

int max(int a, int b);
RBNode* create_rbnode(RBTree* tree, int endpoint, int delta);
RBTree* create_rbtree();
void left_rotate(RBTree *tree, RBNode *x);
void right_rotate(RBTree *tree, RBNode *y);
void rb_insert_fixup(RBTree *tree, RBNode *z);
void insert(RBTree *tree, int endpoint, int delta);
void update_intersections(RBTree* tree, RBNode* node);
int find_max_intersections(RBTree *tree);

int max(int a, int b) {
    return (a > b) ? a : b;
}

RBNode* create_rbnode(RBTree* tree, int endpoint, int delta) {
    RBNode* node = (RBNode*)malloc(sizeof(RBNode));
    node->endpoint = endpoint;
    node->delta = delta;
    node->intersections = 0;
    node->maxIntersections = delta;
    node->color = RED;
    node->left = tree->nil;
    node->right = tree->nil;
    node->parent = NULL;
    printf("Succesfuly created RBNode\n");
    return node;
}

RBTree* create_rbtree() {
    RBTree* tree = (RBTree*)malloc(sizeof(RBTree));
    tree->nil = (RBNode*)malloc(sizeof(RBNode));
    tree->nil->color = BLACK;
    tree->root = tree->nil;
    printf("Succesfuly created RBTree\n");
    return tree;
}

void left_rotate(RBTree *tree, RBNode *x) {
    RBNode *y = x->right;
    x->right = y->left;

    if (y->left != tree->nil) y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL) tree->root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;

    x->left = x;
    x->parent = y;
}

void right_rotate(RBTree *tree, RBNode *y) {
    RBNode *x = y->right;
    y->left = x->right;

    if (x->right != tree->nil) y->right->parent = y;

    x->parent = y->parent;

    if (y->parent == NULL) tree->root = x;
    else if (y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;

    x->right = y;
    y->parent = x;
}

void rb_insert_fixup(RBTree *tree, RBNode *z) {
    while (z->parent != NULL & z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            RBNode *y = z->parent->parent->right;
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
            RBNode *y = z->parent->parent->left;
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

void insert(RBTree *tree, int endpoint, int delta) {
    RBNode *z = create_rbnode(tree, endpoint, delta);
    RBNode *x = tree->root;
    RBNode *y = tree->nil;

    while (x != tree->nil) {
        y = x;
        if (z->endpoint < x->endpoint) x = x->left;
        else x = x->right;
    }

    z->parent = y;
    if (y == tree->nil) tree->root = z;
    else if (z->endpoint < y->endpoint) y->left = z;
    else y->right = z;
    

    z->left = tree->nil;
    z->right = tree->nil;
    z->color = RED;

    rb_insert_fixup(tree, z);
    printf("Succesfuly inserted RBNode into RBTree\n");
    update_intersections(tree,z);
}

void update_intersections(RBTree* tree, RBNode* node) {
    node->intersections = node->delta;

    if (node->left != NULL && node->left != tree->nil) node->intersections += node->left->intersections;
    if (node->right != node->parent) node->intersections += node->right->intersections;

    node->maxIntersections = node->intersections;

    if (node->left != NULL && node->left != tree->nil)
        node->maxIntersections = max(node->left->maxIntersections, node->maxIntersections);

    if (node->right != node->parent) 
        node->maxIntersections = max(node->right->maxIntersections, node->maxIntersections);
    
}

int find_max_intersections(RBTree *tree) {
    RBNode* maxNode = tree->root;

    while (maxNode != tree->nil) {
        if (maxNode->maxIntersections == maxNode->intersections) break;
        maxNode = (maxNode->left->maxIntersections > maxNode->right->maxIntersections) 
            ? maxNode->left : maxNode->right;
    }
    return maxNode->endpoint;
}

#pragma endregion The point with the highest number of intersections

#pragma region Josephus Problem
/*
    17-2
*/
typedef struct JRBNode {
    int key;
    int size;
    int color;
    struct JRBNode* left;
    struct JRBNode* right;
    struct JRBNode* parent;
    struct JRBNode* successor;
    struct JRBNode* predecessor;
} JRBNode;

typedef struct JRBTree {
    JRBNode* root;
    JRBNode* nil; // sentinel
} JRBTree;

size_t size(JRBTree* tree, JRBNode* node);
void j_update_size(JRBTree* tree, JRBNode* node);
JRBNode* create_jrbnode(JRBTree* tree, int key);
JRBTree* create_jrbtree();
void j_left_rotate(JRBTree* tree, JRBNode* x);
void j_right_rotate(JRBTree* tree, JRBNode* y);
void jrb_insert_fixup(JRBTree* tree, JRBNode* z);
void j_insert(JRBTree* tree, int key);
void j_transplant(JRBTree* tree, JRBNode* u, JRBNode* v);
void j_delete_fixup(JRBTree* tree, JRBNode* x);
void j_delete_node(JRBTree* tree, JRBNode* z);
JRBNode* find_successor(JRBNode* x);
JRBNode* find_predecessor(JRBNode* x);
void josephus(uint n, uint m);

size_t size(JRBTree* tree, JRBNode* node) {
    return node == tree->nil ? 0 : node->size;
}

void j_update_size(JRBTree* tree, JRBNode* node) {
    if (node != tree->nil) 
        node->size = size(tree, node->left) + size(tree, node->right) + 1;
}

JRBNode* create_jrbnode(JRBTree* tree, int key) {
    JRBNode* node = (JRBNode*)malloc(sizeof(JRBNode));
    node->key = key;
    node->size = 1;
    node->color = RED;
    node->left = tree->nil;
    node->right = tree->nil;
    node->parent = tree->nil;
    node->successor = tree->nil;
    node->predecessor = tree->nil;
    printf("Succesfuly created JRBNode\n");
    return node;
}

JRBTree* create_jrbtree() {
    JRBTree* tree = (JRBTree*)malloc(sizeof(JRBTree));
    tree->nil = (JRBNode*)malloc(sizeof(JRBNode));
    tree->nil->color = BLACK;
    tree->root = tree->nil;
    printf("Succesfuly created JRBTree\n");
    return tree;
}

void j_left_rotate(JRBTree* tree, JRBNode* x) {
    JRBNode *y = x->right;
    x->right = y->left;

    if (y->left != tree->nil) y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL) tree->root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;

    y->left = x;
    x->parent = y;

    j_update_size(tree, x);
    j_update_size(tree, y);
}

void j_right_rotate(JRBTree* tree, JRBNode* y) {
    JRBNode *x = y->left;
    y->left = x->right;

    if (x->right != tree->nil) x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == NULL) tree->root = x;
    else if (y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;

    x->right = y;
    y->parent = x;

    j_update_size(tree, y);
    j_update_size(tree, x);
}

void jrb_insert_fixup(JRBTree* tree, JRBNode* z) {
    while (z->parent != NULL & z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            JRBNode *y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    j_left_rotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                j_right_rotate(tree, z->parent->parent);
            }
        } else {
            JRBNode *y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    j_right_rotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                j_left_rotate(tree, z->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}

void j_insert(JRBTree* tree, int key) {
    JRBNode *z = create_jrbnode(tree, key);
    JRBNode *x = tree->root;
    JRBNode *y = tree->nil;

    while (x != tree->nil) {
        y = x;
        if (z->key < x->key) x = x->left;
        else x = x->right;
    }

    z->parent = y;
    if (y == tree->nil) tree->root = z;
    else if (z->key < y->key) y->left = z;
    else y->right = z;
    

    z->left = tree->nil;
    z->right = tree->nil;
    z->color = RED;

    printf("Updating successor...\n");
    JRBNode* temp = z->right != tree->nil ? z->right : z->parent;
    while (temp != tree->nil && z == temp->right) temp = temp->parent;
    z->successor = temp;
    printf("Successor set to: %d\n", z->successor->key);

    printf("Updating predecessor...\n");
    temp = z->left != tree->nil ? z->left : z->parent;
    while (temp != tree->nil && z == temp->left) temp = temp->parent;
    z->predecessor = temp;
    printf("Predecessor set to: %d\n", z->predecessor->key);

    jrb_insert_fixup(tree, z);
    printf("Succesfuly inserted RBNode into RBTree\n");
}

void j_transplant(JRBTree* tree, JRBNode* u, JRBNode* v) {
    JRBNode* root = tree->root;
    if (u->parent == tree->nil) root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    v->parent = u->parent;
}

void j_delete_fixup(JRBTree* tree, JRBNode* x) {
    JRBNode* root = tree->root;
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            JRBNode *w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                j_left_rotate(tree, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    j_right_rotate(tree, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                j_left_rotate(tree, x->parent);
                x = root;
            }
        } else {
            JRBNode* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                j_right_rotate(tree, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    j_left_rotate(tree, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                j_right_rotate(tree, x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

void j_delete_node(JRBTree* tree, JRBNode* z) {
    JRBNode* root = tree->root;
    JRBNode* y = z;
    JRBNode* x;
    int y_original_color = y->color;

    if (z->left == tree->nil) {
        x = z->right;
        j_transplant(tree, z, z->right);
    } else if (z->right == tree->nil) {
        x = z->left;
        j_transplant(tree, z, z->left);
    } else {
        y = z->right;
        while (y->left != tree->nil) y = y->left;
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) x->parent = y;
        else {
            j_transplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        j_transplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;

        j_update_size(tree, y);
    }

    JRBNode* p = z->parent;
    while (p != tree->nil) {
        j_update_size(tree, p);
        p = p->parent;
    }

    if (y_original_color == BLACK) j_delete_fixup(tree, x);

    free(z);
}

JRBNode* find_successor(JRBNode* x) {
    return x->successor;
}

JRBNode* find_predecessor(JRBNode* x) {
    return x->predecessor;
}


void josephus(uint n, uint m) {
    JRBTree* tree = create_jrbtree();
    uint i;
    uint count = n;
    JRBNode* curr = tree->root;

    for (i = 1; i <= n; i++) j_insert(tree, i); 

    curr = find_predecessor(tree->root);

    printf("%d\n", curr->key);

    while (count > 0) {
        for (i = 1; i < m; i++) curr = find_predecessor(curr);  
        printf("%d ", curr->key);
        j_delete_node(tree, curr); 
        curr = find_predecessor(curr);  
        count--;
    }
    printf("\n");
}

#pragma endregion Josephus Problem

int main(void) {
    switch (TASK)
    {
        case 1: {
            // 17-1
            RBTree* tree = create_rbtree();

            insert(tree, 5, 1);
            insert(tree, 10, -1);
            insert(tree, 15, 1);

            printf("Endpoint of node with max intersections: %d\n", 
                find_max_intersections(tree));

            break;
        }

        case 2: {
            // 17-2
            uint n2 = 7, m2 = 3;
            josephus(n2, m2);

            break;
        }
        
        default:
            break;
    }

    return 0;
}