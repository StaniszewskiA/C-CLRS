#include "part_5_advanced_data_structures/18_b-trees/b-trees.h"

#pragma region Basic operations on B-trees

BTreeNode* btree_node_init(int isLeaf) {
    BTreeNode* x = (BTreeNode*)malloc(sizeof(BTreeNode));
    x->isLeaf = isLeaf;
    x->numKeys = 0;
    for (int i = 0; i < 2 * DEGREE; i++) x->children[i] = NULL;
    printf("Succesfuly initialized a b-tree node!\n");
    return x;
}

BTreeNode* btree_init() {
    printf("Succesfuly initialized the b-tree!\n");
    return btree_node_init(1);
}

void btree_traverse(BTreeNode* root) {
    if (!root) return;
    int i;

    for (i = 0; i < root->numKeys; i++) {
        if (!root->isLeaf) btree_traverse(root->children[i]);
        printf("%d ", root->keys[i]);
    }

    if (!root->isLeaf) btree_traverse(root->children[root->numKeys]);
}

BTreeNode* btree_search(BTreeNode* root, int key) {
    /*
        Linear btree_search, could be replaced with binary.
    */
    int i = 0;
    while (i < root->numKeys && key > root->keys[i]) i++;
    if (i < root->numKeys && root->keys[i] == key) return root;
    if (root->isLeaf) return NULL;
    return btree_search(root->children[i], key);
}

void btree_node_split_child(BTreeNode* x, int i, BTreeNode* y) {
    BTreeNode* z = btree_node_init(y->isLeaf);
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

void btree_tree_insert_non_full(BTreeNode* x, int k) {
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
            btree_node_split_child(x, i, x->children[i]);
            if (k > x->keys[i]) i++;
            btree_tree_insert_non_full(x->children[i], k);
        }
    }
}

void btree_tree_insert(BTreeNode** root, int k) {
    BTreeNode* r = *root;
    if (r->numKeys == 2 * DEGREE - 1) {
        BTreeNode* s = btree_node_init(0);
        *root = s;
        s->children[0] = r;
        btree_node_split_child(s, 0, r);
        btree_tree_insert_non_full(s, k);
    } else btree_tree_insert_non_full(r, k);
}

#pragma endregion Basic operations on B-trees

#pragma region Deleting a key from a B-tree

int btree_tree_node_get_predecessor(BTreeNode* x) {
    while (!x->isLeaf) x = x->children[x->numKeys];
    return x->keys[x->numKeys - 1];
}

int btree_tree_node_get_successor(BTreeNode* x) {
    while (!x->isLeaf) x = x->children[0];
    return x->keys[0];
}

void btree_tree_node_merge(BTreeNode* x, int i) {
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

void btree_tree_fill(BTreeNode* x, int i) {
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
        if (i < x->numKeys) btree_tree_node_merge(x, i);
        else btree_tree_node_merge(x, i - 1);
    }
}

void btree_delete_from_node(BTreeNode* x, int k) {
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
                int predKey = btree_tree_node_get_predecessor(pred);
                x->keys[i] = predKey;
                btree_delete_from_node(pred, predKey);
            } else if (succ->numKeys >= DEGREE) {
                int succKey = btree_tree_node_get_successor(succ);
                x->keys[i] = succKey;
                btree_delete_from_node(succ, succKey);
            } else {
                btree_tree_node_merge(x, i);
                btree_delete_from_node(pred, k);
            }
        }
    } else {
        if (x->isLeaf) {
            printf("Key %d not found in the B-tree.\n", k);
            return;
        }
        int flag = (i == x->numKeys);
        if (x->children[i]->numKeys < DEGREE) btree_tree_fill(x, i);

        if (flag && i > x->numKeys) btree_delete_from_node(x->children[i - 1], k);
        else btree_delete_from_node(x->children[i], k);
    }
}

void btree_delete_key(BTreeNode** rootRef, int k) {
    BTreeNode* root = *rootRef;
    btree_delete_from_node(root, k);
    if (root->numKeys == 0) {
        BTreeNode* temp = root;
        if (root->isLeaf) *rootRef = NULL;
        else *rootRef = root->children[0];
        free(temp);
    }
}

void btree_free(BTreeNode* node) {
    if (!node) return;
    if (!node->isLeaf) {
        for (int i = 0; i < node->numKeys; i++) btree_free(node->children[i]);
    }
    free(node);
}

#pragma endregion Deleting a key from a B-tree

