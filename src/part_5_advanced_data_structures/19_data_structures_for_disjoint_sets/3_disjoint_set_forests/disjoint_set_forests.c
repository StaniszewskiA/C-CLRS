#include <stdio.h>
#include <stdlib.h>

#define TASK 2
#define MAX_SIZE 100

typedef struct {
    int parent[MAX_SIZE];
    int rank[MAX_SIZE];
} DisjointSet;

void make_set(DisjointSet* ds, int n);
int find(DisjointSet* ds, int x); 
void link(DisjointSet* ds, int xRoot, int yRoot);
void union_sets(DisjointSet* ds, int x, int y);
void print_sets(DisjointSet* ds, int n);

void make_set(DisjointSet* ds, int n) {
    for (int i = 0; i < n; i++) {
        ds->parent[i] = i;
        ds->rank[i] = 0;
    }
}

int find(DisjointSet* ds, int x) {
    if (ds->parent[x] != x) ds->parent[x] = find(ds, ds->parent[x]);
    return ds->parent[x];
}

void link(DisjointSet* ds, int xRoot, int yRoot) {
    if (ds->rank[xRoot] > ds->rank[yRoot]) ds->parent[yRoot] = xRoot;
    else {
        ds->parent[xRoot] = yRoot;
        if (ds->rank[xRoot] == ds->rank[yRoot]) ds->rank[yRoot]++;
    }
}

void union_sets(DisjointSet* ds, int x, int y) {
    int xRoot = find(ds, x);
    int yRoot = find(ds, y);
    if (xRoot != yRoot) link(ds, xRoot, yRoot);
}

void print_sets(DisjointSet* ds, int n) {
    printf("Element : Representative: \n");
    for (int i = 0; i < n; i++) printf("%d : %d\n", i, find(ds, i));
}

/*
    19.3-2: Nonrecursive find operation.
*/
typedef struct Node {
    int *elemPtr;
    struct Node* next;
} Node;

Node* create_node(int* elemPtr) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->elemPtr = elemPtr;
    new_node->next = NULL;
    return new_node;
}

int find_non_recursive(DisjointSet* ds, int x) {
    Node* A = NULL;

    int curr = x;

    while (ds->parent[curr] != curr) {
        Node* new_node = create_node(&ds->parent[curr]);
        new_node->next = A;
        A = new_node;
        curr = ds->parent[curr];
    }

    int root = curr;

    Node* temp = A;
    while (temp != NULL) {
        *(temp->elemPtr) = root;
        Node *toFree = temp;
        temp = temp->next;
        free(toFree);
    }

    return root;
}

/*
    19.3-4
*/
typedef struct Node2 {
    int value;
    struct Node2* parent;
    int rank;
    struct Node2* next;
    struct Node2* tail;
} Node2;

Node2* nodes2[MAX_SIZE];

Node2* make_set2(int val) {
    Node2* node = (Node2*)malloc(sizeof(Node2));
    node->value = val;
    node->parent = node;
    node->rank = 0;
    node->next = NULL;
    node->tail = node;
    nodes2[val] = node;
    return node;
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


int main(void) {
    DisjointSet ds;
    int n = 10;

    make_set(&ds, n);

    union_sets(&ds, 0, 1);
    union_sets(&ds, 1, 2);
    union_sets(&ds, 3, 4);
    union_sets(&ds, 2, 4);
    union_sets(&ds, 5, 6);
    union_sets(&ds, 6, 7);
    union_sets(&ds, 0, 7);
    union_sets(&ds, 8, 9);
    union_sets(&ds, 0, 8);

    print_sets(&ds, n);

    switch (TASK)
    {
        case 1: {
            // 19.3-2
            int target = find_non_recursive(&ds, 1);
            printf("%d\n", target);
            break;
        }

        case 2: {
            // 19.3-4
            int n2 = 10;
            for (int i = 0; i < n2; i++) make_set2(i);

            union_sets2(nodes2[0], nodes2[1]);
            union_sets2(nodes2[1], nodes2[2]);
            union_sets2(nodes2[2], nodes2[3]);

            print_set2(nodes2[2]); 
            print_set2(nodes2[3]);

            break;
        }
        
        default:
            break;
    }

    return 0;
}