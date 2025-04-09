#include <stdio.h>
#include <stdlib.h>

#define DEGREE 3

typedef unsigned int uint;

typedef struct BTreeNode {
    int keys[2 * DEGREE - 1];
    int isLeaf;
    uint numKeys;
    struct BTreeNode* children[2 * DEGREE];
} BTreeNode;

BTreeNode* create_node(int isLeaf);
BTreeNode* init_btree();
void traverse(BTreeNode* root);
BTreeNode* search(BTreeNode* root, int key);
void split_child(BTreeNode* x, int i, BTreeNode* y);
void insert_non_full(BTreeNode* x, int k);
void insert(BTreeNode** root, int k);
int get_predecessor(BTreeNode* x);
int get_successor(BTreeNode* x);

BTreeNode* create_node(int isLeaf) {
    BTreeNode* x = (BTreeNode*)malloc(sizeof(BTreeNode));
    x->isLeaf = isLeaf;
    x->numKeys = 0;
    for (int i = 0; i < 2 * DEGREE; i++) x->children[i] = NULL;
    printf("Succesfuly initialized a b-tree node!\n");
    return x;
}

BTreeNode* init_btree() {
    printf("Succesfuly initialized the b-tree!\n");
    return create_node(1);
}

void traverse(BTreeNode* root) {
    if (!root) return;
    int i;

    for (i = 0; i < root->numKeys; i++) {
        if (!root->isLeaf) traverse(root->children[i]);
        printf("%d ", root->keys[i]);
    }

    if (!root->isLeaf) traverse(root->children[root->numKeys]);
}

BTreeNode* search(BTreeNode* root, int key) {
    /*
        Linear search, could be replaced with binary.
    */
    int i = 0;
    while (i < root->numKeys && key > root->keys[i]) i++;
    if (i < root->numKeys && root->keys[i] == key) return root;
    if (root->isLeaf) return NULL;
    return search(root->children[i], key);
}

void split_child(BTreeNode* x, int i, BTreeNode* y) {
    BTreeNode* z = create_node(y->isLeaf);
    z->numKeys = DEGREE - 1;
    int j;

    for (j = 0; j < DEGREE - 1; j++) z->keys[j] = y->keys[j + DEGREE];

    if (!y->isLeaf) {
        for (j = 0; j < DEGREE; j++) z->children[j] = y->children[j + DEGREE];
    } 

    y->numKeys = DEGREE - 1;

    for (int j = x->numKeys; j >= i + 1; j--) 
        x->children[j + 1] = x->children[j];
    
    x->children[i + 1] = z;

    for (j = x->numKeys - 1; j >= i; j--) x->keys[j + 1] = x->keys[j];

    x->keys[i] = y->keys[DEGREE - 1];
    x->numKeys++;
}

void insert_non_full(BTreeNode* x, int k) {
    int i = x->numKeys - 1;

    if (x->isLeaf) {
        while (i >= 0 && x->keys[i] > k) {
            x->keys[i + 1] = x->keys[i];
            i--;
        }
        x->keys[i + 1] = k;
        x->numKeys++;
    } else {
        while (i >= 0 && x->keys[i] > k) i--;
        i++;
        if (x->children[i]->numKeys == 2 * DEGREE - 1) {
            split_child(x, i, x->children[i]);
            if (k > x->keys[i]) i++;
            insert_non_full(x->children[i], k);
        }
    }
}

void insert(BTreeNode** root, int k) {
    BTreeNode* r = *root;
    if (r->numKeys == 2 * DEGREE - 1) {
        BTreeNode* s = create_node(0);
        *root = s;
        s->children[0] = r;
        split_child(s, 0, r);
        insert_non_full(s, k);
    } else insert_non_full(r, k);
}

int get_predecessor(BTreeNode* x) {
    while (!x->isLeaf) x = x->children[x->numKeys];
    return x->keys[x->numKeys - 1];
}

int get_successor(BTreeNode* x) {
    while (!x->isLeaf) x = x->children[0];
    return x->keys[0];
}

int main(void) {
    BTreeNode* root = init_btree();

    uint values[] = {10, 20, 5, 6, 12, 30, 7, 17};
    uint n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++) insert(&root, values[i]);

    printf("Initial B-tree: ");
    traverse(root);
    printf("\n");
}