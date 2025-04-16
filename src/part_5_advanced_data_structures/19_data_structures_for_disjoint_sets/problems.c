#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TASK 2

#pragma region Off-line minimum

#define MAX_N 1000

typedef struct OfflineDisjointSet {
    int parent;
    int rank;
    int minVal;
    int nextSet;
    int exists;
} OfflineDisjointSet;

OfflineDisjointSet sets[MAX_N];
int extracted[MAX_N];

void offline_make_set(int i);
int offline_find_set(int i);
void offline_union_sets(int x, int y);
void offline_minimum(int ops[], int n);

void offline_make_set(int i) {
    sets[i].parent = i;
    sets[i].rank = 0;
    sets[i].minVal = INT_MAX;
    sets[i].nextSet = i + 1;
    sets[i].exists = 1; 
}

int offline_find_set(int i) {
    if (sets[i].parent != i) sets[i].parent = offline_find_set(sets[i].parent);
    return sets[i].parent;
}

void offline_union_sets(int x, int y) {
    int xRoot = offline_find_set(x);
    int yRoot = offline_find_set(y);
    if (xRoot == yRoot) return;

    if (sets[xRoot].rank < sets[yRoot].rank) {
        sets[xRoot].parent = yRoot;
        if (sets[xRoot].minVal < sets[yRoot].minVal)
            sets[xRoot].minVal = sets[yRoot].minVal;
    } else {
        sets[yRoot].parent = xRoot;
        if (sets[yRoot].minVal < sets[xRoot].minVal)
            sets[xRoot].minVal = sets[yRoot].minVal;
        if (sets[xRoot].rank == sets[yRoot].rank)
            sets[xRoot].rank++;
    }
}

void offline_minimum(int ops[], int n) {
    int extractIdx = 0;
    int i;

    for (i = 0; i < n; i++) {
        if (ops[i] == -1) offline_make_set(extractIdx++);
    }

    int currSet = 0;
    extractIdx = 0;

    for (i = 0; i < n; i++) {
        if (ops[i] == -1) currSet++;
        else {
            int x = ops[i];
            int rep = offline_find_set(currSet);
            if (x < sets[rep].minVal) sets[rep].minVal = x;
        }
    }

    for (i = 0; i < currSet; i++) {
        if (!sets[i].exists) continue;

        int rep = offline_find_set(i);
        extracted[i] = sets[rep].minVal;

        int next = sets[i].nextSet;
        while (next < currSet && !sets[next].exists) next++;

        if (next < currSet) {
            offline_union_sets(i, next);
            sets[i].nextSet = next + 1;
        }

        sets[i].exists = 0;
    }

    printf("Extracted mins: ");
    for (int i = 0; i < currSet; i++) {
        printf("%d ", extracted[i]);
    }
    printf("\n");
}

#pragma endregion Off-line minimum

#pragma region Depth determination

typedef struct DeterminantNode {
    struct DeterminantNode* parent;
    int rank;
    int pseudoDepth;
} DeterminantNode;

DeterminantNode* determinant_make_tree();
DeterminantNode* determinant_find_set(DeterminantNode* v, int* depth);
int determinant_find_depth(DeterminantNode* v);
void determinant_graft(DeterminantNode* r, DeterminantNode* v);

DeterminantNode* determinant_make_tree() {
    DeterminantNode* obj = malloc(sizeof(DeterminantNode));
    obj->parent = obj;
    obj->rank = 0;
    obj->pseudoDepth = 0;
    return obj;
}

DeterminantNode* determinant_find_set(DeterminantNode* v, int* depth) {
    if (v != v->parent) {
        int parentDepth;
        DeterminantNode* root = determinant_find_set(v->parent, &parentDepth);
        v->pseudoDepth += parentDepth;
        v->parent = root;
        *depth = v->pseudoDepth;
        return root;
    } else {
        *depth = 0;
        return v;
    }
}

int determinant_find_depth(DeterminantNode* v) {
    int depth;
    determinant_find_set(v, &depth);
    return depth;
}

void determinant_graft(DeterminantNode* r, DeterminantNode* v) {
    int depthR, depthV;
    DeterminantNode* rootR = determinant_find_set(r, &depthR);
    DeterminantNode* rootV = determinant_find_set(v, &depthV);

    if (rootR == rootV) return;

    if (rootR->rank > rootV->rank) {
        rootV->parent = rootR;
        rootV->pseudoDepth = depthR - depthV;
    } else {
        rootR->parent = rootV;
        rootR->pseudoDepth = depthV - depthR + 1;
        if (rootR->rank == rootV->rank) rootV->rank += 1;
    }
}

#pragma endregion Depth determination

int main(void) {
    switch (TASK)
    {
        case 1: {
            // 19.1
            int ops[] = {4, 8, -1, 3, 9, -1, 2, -1};
            int n = sizeof(ops) / sizeof(ops[0]);

            offline_minimum(ops, n);
            break;
        }
        case 2:{
            // 19.2
            DeterminantNode* a = determinant_make_tree();
            DeterminantNode* b = determinant_make_tree();
            DeterminantNode* c = determinant_make_tree();

            printf("Initial depths:\n");
            printf("depth(a) = %d\n", determinant_find_depth(a));
            printf("depth(b) = %d\n", determinant_find_depth(b));
            printf("depth(c) = %d\n", determinant_find_depth(c));

            determinant_graft(b, a);
            determinant_graft(c, b);

            printf("\nAfter grafting:\n");
            printf("depth(a) = %d\n", determinant_find_depth(a));
            printf("depth(b) = %d\n", determinant_find_depth(b));
            printf("depth(c) = %d\n", determinant_find_depth(c));

            free(a);
            free(b);
            free(c);

            break;
        }
        default:
            break;
    }
    return 0;
}