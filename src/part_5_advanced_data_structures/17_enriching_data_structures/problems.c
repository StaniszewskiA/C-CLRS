#include "part_5_advanced_data_structures/17_enriching_data_structures/enriching_data_structures.h"

#define TASK 3

#pragma region The point with the highest number of intersections
/*
    17-1
*/
IntersectionRBNode* intersection_rb_node_init(IntersectionRBTree* tree, int endpoint, int delta) {
    IntersectionRBNode* node = (IntersectionRBNode*)malloc(sizeof(IntersectionRBNode));
    node->endpoint = endpoint;
    node->delta = delta;
    node->intersections = 0;
    node->maxIntersections = delta;
    node->color = RED;
    node->left = tree->nil;
    node->right = tree->nil;
    node->parent = NULL;
    printf("Succesfuly created IntersectionRBNode\n");
    return node;
}

IntersectionRBTree* create_rbtree() {
    IntersectionRBTree* tree = (IntersectionRBTree*)malloc(sizeof(IntersectionRBTree));
    tree->nil = (IntersectionRBNode*)malloc(sizeof(IntersectionRBNode));
    tree->nil->color = BLACK;
    tree->root = tree->nil;
    printf("Succesfuly created IntersectionRBTree\n");
    return tree;
}

void intersection_rb_tree_left_rotate(IntersectionRBTree *tree, IntersectionRBNode *x) {
    IntersectionRBNode *y = x->right;
    x->right = y->left;

    if (y->left != tree->nil) y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL) tree->root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;

    x->left = x;
    x->parent = y;
}

void intersection_rb_tree_right_rotate(IntersectionRBTree *tree, IntersectionRBNode *y) {
    IntersectionRBNode *x = y->right;
    y->left = x->right;

    if (x->right != tree->nil) y->right->parent = y;

    x->parent = y->parent;

    if (y->parent == NULL) tree->root = x;
    else if (y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;

    x->right = y;
    y->parent = x;
}

void intersection_rb_tree_insert_fixup(IntersectionRBTree *tree, IntersectionRBNode *z) {
    while (z->parent != NULL && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            IntersectionRBNode *y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    intersection_rb_tree_left_rotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                intersection_rb_tree_right_rotate(tree, z->parent->parent);
            }
        } else {
            IntersectionRBNode *y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    intersection_rb_tree_right_rotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                intersection_rb_tree_left_rotate(tree, z->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}

void intersection_rb_tree_insert(IntersectionRBTree *tree, int endpoint, int delta) {
    IntersectionRBNode *z = intersection_rb_node_init(tree, endpoint, delta);
    IntersectionRBNode *x = tree->root;
    IntersectionRBNode *y = tree->nil;

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

    intersection_rb_tree_insert_fixup(tree, z);
    printf("Succesfuly inserted IntersectionRBNode into IntersectionRBTree\n");
    intersection_rb_tree_update_intersections(tree,z);
}

void intersection_rb_tree_update_intersections(IntersectionRBTree* tree, IntersectionRBNode* node) {
    node->intersections = node->delta;

    if (node->left != NULL && node->left != tree->nil) node->intersections += node->left->intersections;
    if (node->right != node->parent) node->intersections += node->right->intersections;

    node->maxIntersections = node->intersections;

    if (node->left != NULL && node->left != tree->nil)
        node->maxIntersections = MAX(node->left->maxIntersections, node->maxIntersections);

    if (node->right != node->parent) 
        node->maxIntersections = MAX(node->right->maxIntersections, node->maxIntersections);
    
}

int intersection_rb_tree_find_max_intersections(IntersectionRBTree *tree) {
    IntersectionRBNode* maxNode = tree->root;

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
size_t jrb_tree_get_size(JRBTree* tree, JRBNode* node) {
    return node == tree->nil ? 0 : node->size;
}

void jrb_tree_update_size(JRBTree* tree, JRBNode* node) {
    if (node != tree->nil) 
        node->size = jrb_tree_get_size(tree, node->left) + jrb_tree_get_size(tree, node->right) + 1;
}

JRBNode* jrb_node_init(JRBTree* tree, int key) {
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

JRBTree* jrb_tree_init() {
    JRBTree* tree = (JRBTree*)malloc(sizeof(JRBTree));
    tree->nil = (JRBNode*)malloc(sizeof(JRBNode));
    tree->nil->color = BLACK;
    tree->root = tree->nil;
    printf("Succesfuly created JRBTree\n");
    return tree;
}

void jrb_tree_left_rotate(JRBTree* tree, JRBNode* x) {
    JRBNode *y = x->right;
    x->right = y->left;

    if (y->left != tree->nil) y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL) tree->root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;

    y->left = x;
    x->parent = y;

    jrb_tree_update_size(tree, x);
    jrb_tree_update_size(tree, y);
}

void jrb_tree_right_rotate(JRBTree* tree, JRBNode* y) {
    JRBNode *x = y->left;
    y->left = x->right;

    if (x->right != tree->nil) x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == NULL) tree->root = x;
    else if (y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;

    x->right = y;
    y->parent = x;

    jrb_tree_update_size(tree, y);
    jrb_tree_update_size(tree, x);
}

void jrb_tree_insert_fixup(JRBTree* tree, JRBNode* z) {
    while (z->parent != NULL && z->parent->color == RED) {
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
                    jrb_tree_left_rotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                jrb_tree_right_rotate(tree, z->parent->parent);
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
                    jrb_tree_right_rotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                jrb_tree_left_rotate(tree, z->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}

void jrb_tree_insert(JRBTree* tree, int key) {
    JRBNode *z = jrb_node_init(tree, key);
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

    jrb_tree_insert_fixup(tree, z);
    printf("Succesfuly inserted IntersectionRBNode into IntersectionRBTree\n");
}

void jrb_tree_transplant(JRBTree* tree, JRBNode* u, JRBNode* v) {
    if (u->parent == tree->nil) tree->root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    v->parent = u->parent;
}

void jrb_tree_delete_fixup(JRBTree* tree, JRBNode* x) {
    JRBNode* root = tree->root;
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            JRBNode *w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                jrb_tree_left_rotate(tree, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    jrb_tree_right_rotate(tree, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                jrb_tree_left_rotate(tree, x->parent);
                x = root;
            }
        } else {
            JRBNode* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                jrb_tree_right_rotate(tree, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    jrb_tree_left_rotate(tree, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                jrb_tree_right_rotate(tree, x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

void jrb_tree_delete_node(JRBTree* tree, JRBNode* z) {
    JRBNode* y = z;
    JRBNode* x;
    int y_original_color = y->color;

    if (z->left == tree->nil) {
        x = z->right;
        jrb_tree_transplant(tree, z, z->right);
    } else if (z->right == tree->nil) {
        x = z->left;
        jrb_tree_transplant(tree, z, z->left);
    } else {
        y = z->right;
        while (y->left != tree->nil) y = y->left;
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) x->parent = y;
        else {
            jrb_tree_transplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        jrb_tree_transplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;

        jrb_tree_update_size(tree, y);
    }

    JRBNode* p = z->parent;
    while (p != tree->nil) {
        jrb_tree_update_size(tree, p);
        p = p->parent;
    }

    if (y_original_color == BLACK) jrb_tree_delete_fixup(tree, x);

    free(z);
}

JRBNode* jrb_node_find_successor(JRBNode* x) {
    return x->successor;
}

JRBNode* jrb_node_find_predecessor(JRBNode* x) {
    return x->predecessor;
}


void josephus(int n, int m) {
    JRBTree* tree = jrb_tree_init();
    int i;
    int count = n;
    JRBNode* curr = tree->root;

    for (i = 1; i <= n; i++) jrb_tree_insert(tree, i); 

    curr = jrb_node_find_predecessor(tree->root);

    printf("%d\n", curr->key);

    while (count > 0) {
        for (i = 1; i < m; i++) curr = jrb_node_find_predecessor(curr);  
        printf("%d ", curr->key);
        jrb_tree_delete_node(tree, curr); 
        curr = jrb_node_find_predecessor(curr);  
        count--;
    }
    printf("\n");
}

#pragma endregion Josephus Problem

#pragma region Array based Josephus problem

void print_victims(int n, int k) {
    int survivors = n;
    int circle[n];
    int i;

    for (i = 0; i < n; i++) circle[i] = i + 1;
    
    int idx = 0;

    while (survivors > 1) {
        idx = (idx + k - 1) % survivors;
        printf("Next victim: %d\n", circle[idx]);
        for (i = idx; i < survivors - 1; i++) circle[i] = circle[i + 1];
        survivors--;
    } 

    printf("The chosen place is %d\n", circle[0]);
}

#pragma endregion Array based Josephus problem

int main(void) {
    switch (TASK)
    {
        case 1: {
            // 17-1
            IntersectionRBTree* tree = create_rbtree();

            intersection_rb_tree_insert(tree, 5, 1);
            intersection_rb_tree_insert(tree, 10, -1);
            intersection_rb_tree_insert(tree, 15, 1);

            printf("Endpoint of node with MAX intersections: %d\n", 
                intersection_rb_tree_find_max_intersections(tree));

            break;
        }

        case 2: {
            // 17-2
            int n2 = 7, m2 = 3;
            josephus(n2, m2);

            break;
        }

        case 3: {
            int n3 = 7, m3 = 3;
            print_victims(n3, m3);
            break;
        }
        
        default:
            break;
    }

    return 0;
}