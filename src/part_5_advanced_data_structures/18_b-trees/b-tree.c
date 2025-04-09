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
void merge(BTreeNode* x, int i);
void fill(BTreeNode* x, int i);
void delete_from_node(BTreeNode* x, int k);
void delete_key(BTreeNode** root_ref, int k);
void free_tree(BTreeNode* node);

#pragma region Basic operations on B-trees

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

#pragma endregion Basic operations on B-trees

#pragma region Deleting a key from a B-tree

int get_predecessor(BTreeNode* x) {
    while (!x->isLeaf) x = x->children[x->numKeys];
    return x->keys[x->numKeys - 1];
}

int get_successor(BTreeNode* x) {
    while (!x->isLeaf) x = x->children[0];
    return x->keys[0];
}

void merge(BTreeNode* x, int i) {
    /*
        Merge i-th and (i + 1)-th nodes.
    */
    BTreeNode* c1 = x->children[i];
    BTreeNode* c2 = x->children[i + 1];
    int j;

    c1->keys[DEGREE - 1] = x->keys[i];
    for (int j = 0; j < c2->numKeys; j++) c1->keys[j + DEGREE] = c2->keys[j];

    if (!c1->isLeaf) {
        for (j = 0; j <= c2->numKeys; j++) 
            c1->children[j + DEGREE] = c2->children[j];
    } 

    for (j = i + 1; j < x->numKeys; j++) {
        x->keys[j - 1] = x->keys[j];
        x->children[j] = x->children[j + 1];
    }

    c1->numKeys += c2->numKeys + 1;
    x->numKeys--;
    free(c2);
}

void fill(BTreeNode* x, int i) {
    int j;

    if (i > 0 && x->children[i - 1]->numKeys >= DEGREE) {
        // Borrow a key from the previous child.
        BTreeNode* child = x->children[i];
        BTreeNode* sibling = x->children[i - 1];

        // Shift keys and children to the right
        for (j = child->numKeys - 1; j >= 0; j--) 
            child->keys[j + 1] = child->keys[j];
        if (!child->isLeaf) {
            for (j = child->numKeys; j >= 0; j--)
                child->children[j + 1] = child->children[j];
        }
        child->keys[0] = x->keys[i - 1];
        if (!child->isLeaf) 
            child->children[0] = sibling->children[sibling->numKeys];
        x->keys[i - 1] = sibling->keys[sibling->numKeys - 1];
        child->numKeys++;
        sibling->numKeys--;
    } else if (i < x->numKeys && x->children[i + 1]->numKeys >= DEGREE) {
        // Borrow a key from the next child.
        BTreeNode* child = x->children[i];
        BTreeNode* sibling = x->children[i - 1];
        child->keys[child->numKeys] = x->keys[i];
        if (!child->isLeaf)
            child->children[child->numKeys + 1] = sibling->children[0];
        x->keys[i] = sibling->keys[0];
        for (j = 1; j < sibling->numKeys; j++)
            sibling->keys[j - 1] = sibling->keys[j];
        if (!sibling->isLeaf) {
            for (j = 1; j <= sibling->numKeys; j++)
                sibling->children[j - 1] = sibling->children[j];
        }
        child->numKeys++;
        sibling->numKeys--;
    } else {
        // Merge the siblings.
        if (i < x->numKeys) merge(x, i);
        else merge(x, i - 1);
    }
}

void delete_from_node(BTreeNode* x, int k) {
    int i = 0;
    int j;
    while (i < x->numKeys && k > x->keys[i]) i++;

    if (i < x->numKeys && x->keys[i] == k) {
        if (x->isLeaf) {
            // Case 1: Key is in a leaf node
            for (j = i + 1; j < x->numKeys; j++) x->keys[j - 1] = x->keys[j];
            x->numKeys--;
        } else {
            // Case 2: key is in an internal node
            BTreeNode* pred = x->children[i];
            BTreeNode* succ = x->children[i + 1];
            if (pred->numKeys >= DEGREE) {
                int predKey = get_predecessor(pred);
                x->keys[i] = predKey;
                delete_from_node(pred, predKey);
            } else if (succ->numKeys >= DEGREE) {
                int succKey = get_successor(succ);
                x->keys[i] = succKey;
                delete_from_node(succ, succKey);
            } else {
                merge(x, i);
                delete_from_node(pred, k);
            }
        }
    } else {
        if (x->isLeaf) {
            printf("Key %d not found in the B-tree.\n", k);
            return;
        }
        int flag = (i == x->numKeys);
        if (x->children[i]->numKeys < DEGREE) fill(x, i);

        if (flag && i > x->numKeys) delete_from_node(x->children[i - 1], k);
        else delete_from_node(x->children[i], k);
    }
}

void delete_key(BTreeNode** rootRef, int k) {
    BTreeNode* root = *rootRef;
    delete_from_node(root, k);
    if (root->numKeys == 0) {
        BTreeNode* temp = root;
        if (root->isLeaf) *rootRef = NULL;
        else *rootRef = root->children[0];
        free(temp);
    }
}

void free_tree(BTreeNode* node) {
    if (!node) return;
    if (!node->isLeaf) {
        for (int i = 0; i < node->numKeys; i++) free_tree(node->children[i]);
    }
    free(node);
}

#pragma endregion Deleting a key from a B-tree

int main(void) {
    BTreeNode* root = init_btree();

    uint values[] = {10, 20, 5, 6, 12, 30, 7, 17};
    uint n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++) insert(&root, values[i]);

    printf("Initial B-tree: ");
    traverse(root);
    printf("\n");

    delete_key(&root, 6);
    printf("After deleting 6: ");
    traverse(root);
    printf("\n");

    delete_key(&root, 13); 
    delete_key(&root, 7);
    delete_key(&root, 4); 
    delete_key(&root, 17);
    delete_key(&root, 10);

    printf("After more deletions: ");
    traverse(root);
    printf("\n");

    free_tree(root);
    return 0;
}