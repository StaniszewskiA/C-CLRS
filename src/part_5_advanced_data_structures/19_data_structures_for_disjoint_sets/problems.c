#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TASK 1
#define MAX_N 1000

typedef struct DisjointSet {
    int parent;
    int rank;
    int minVal;
    int nextSet;
    int exists;
} DisjointSet;

/*
    19.1: Off-line minimum, O(nα(n))
*/

DisjointSet sets[MAX_N];
int extracted[MAX_N];

void make_set(int i);
int find_set(int i);
void union_sets(int x, int y);
void offline_minimum(int ops[], int n);

void make_set(int i) {
    sets[i].parent = i;
    sets[i].rank = 0;
    sets[i].minVal = INT_MAX;
    sets[i].nextSet = i + 1;
    sets[i].exists = 1; 
}

int find_set(int i) {
    if (sets[i].parent != i) sets[i].parent = find_set(sets[i].parent);
    return sets[i].parent;
}

void union_sets(int x, int y) {
    int xRoot = find_set(x);
    int yRoot = find_set(y);
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
        if (ops[i] == -1) make_set(extractIdx++);
    }

    int currSet = 0;
    extractIdx = 0;

    for (i = 0; i < n; i++) {
        if (ops[i] == -1) currSet++;
        else {
            int x = ops[i];
            int rep = find_set(currSet);
            if (x < sets[rep].minVal) sets[rep].minVal = x;
        }
    }

    for (i = 0; i < currSet; i++) {
        if (!sets[i].exists) continue;

        int rep = find_set(i);
        extracted[i] = sets[rep].minVal;

        int next = sets[i].nextSet;
        while (next < currSet && !sets[next].exists) next++;

        if (next < currSet) {
            union_sets(i, next);
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
        default:
            break;
    }
    return 0;
}