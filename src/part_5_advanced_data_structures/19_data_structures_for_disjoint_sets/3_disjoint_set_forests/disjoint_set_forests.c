#include "part_5_advanced_data_structures/19_data_structures_for_disjoint_sets/data_structures_for_disjoint_sets.h"

void make_disjoint_set(DisjointSet* ds, int n) {
    for (int i = 0; i < n; i++) {
        ds->parent[i] = i;
        ds->rank[i] = 0;
    }
}

int disjoint_set_find(DisjointSet* ds, int x) {
    if (ds->parent[x] != x) ds->parent[x] = disjoint_set_find(ds, ds->parent[x]);
    return ds->parent[x];
}

void disjoint_set_link(DisjointSet* ds, int xRoot, int yRoot) {
    if (ds->rank[xRoot] > ds->rank[yRoot]) ds->parent[yRoot] = xRoot;
    else {
        ds->parent[xRoot] = yRoot;
        if (ds->rank[xRoot] == ds->rank[yRoot]) ds->rank[yRoot]++;
    }
}

void union_disjoint_sets(DisjointSet* ds, int x, int y) {
    int xRoot = disjoint_set_find(ds, x);
    int yRoot = disjoint_set_find(ds, y);
    if (xRoot != yRoot) disjoint_set_link(ds, xRoot, yRoot);
}

void print_disjoint_sets(DisjointSet* ds, int n) {
    printf("Element : Representative: \n");
    for (int i = 0; i < n; i++) printf("%d : %d\n", i, disjoint_set_find(ds, i));
}

/*
    19.3-2: Nonrecursive disjoint_set_find operation.
*/
DSNode* create_ds_node(int* elemPtr) {
    DSNode* new_node = (DSNode*)malloc(sizeof(DSNode));
    new_node->elemPtr = elemPtr;
    new_node->next = NULL;
    return new_node;
}

int find_non_recursive(DisjointSet* ds, int x) {
    DSNode* A = NULL;

    int curr = x;

    while (ds->parent[curr] != curr) {
        DSNode* new_node = create_ds_node(&ds->parent[curr]);
        new_node->next = A;
        A = new_node;
        curr = ds->parent[curr];
    }

    int root = curr;

    DSNode* temp = A;
    while (temp != NULL) {
        *(temp->elemPtr) = root;
        DSNode *toFree = temp;
        temp = temp->next;
        free(toFree);
    }

    return root;
}

/*
    19.3-4
*/
Node2* nodes2[MAX_DISJOINT_SET_SIZE];

Node2* make_set2(int val) {
    Node2* DSNode = (Node2*)malloc(sizeof(Node2));
    DSNode->value = val;
    DSNode->parent = DSNode;
    DSNode->rank = 0;
    DSNode->next = NULL;
    DSNode->tail = DSNode;
    nodes2[val] = DSNode;
    return DSNode;
}

Node2* find_set2(Node2* x) {
    if (x->parent != x) x->parent = find_set2(x->parent);
    return x->parent;
}

void link2(Node2* xRoot, Node2* yRoot) {
    if (xRoot->rank > yRoot->rank) {
        yRoot->parent = xRoot;
        xRoot->tail->next = yRoot;
        xRoot->tail = yRoot->tail;
    } else {
        xRoot->parent = yRoot;

        yRoot->tail->next = xRoot;
        yRoot->tail = xRoot->tail;

        if (xRoot->rank == yRoot->rank) {
            yRoot->rank++;
        }
    }
}

void union_sets2(Node2* x, Node2* y) {
    Node2* xRoot = find_set2(x);
    Node2* yRoot = find_set2(y);
    if (xRoot != yRoot) link2(xRoot, yRoot);
}

void print_set2(Node2* x) {
    Node2* rep = find_set2(x);
    Node2* curr = rep;
    printf("Set members: ");
    while (curr != NULL) {
        printf("%d ", curr->value);
        curr = curr->next;
    }
    printf("\n");
}
