#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "../../common.h"
#include "../part_2_commons.h"

// ============================================================================
// CHAPTER 7.1 QUICKSORT
// ============================================================================

void swap4(int *a, int *b);
int partition(int A[], int p, int r);
void quicksort(int A[], int p, int r);

// ============================================================================
// PROBLEMS
// ============================================================================

void fuzzy_partition(
    Interval A[],
    int p,
    int r,
    int *q1,
    int *q2
);
void fuzzy_quicksort(Interval A[], int p, int r);

int hoare_partition(int A[], int p, int r);

typedef struct {
    int q;
    int t;
} PartitionIndices;

PartitionIndices partition_prim(int A[], int p, int r);
PartitionIndices randomized_partition(
    int A[],
    int p,
    int r
);
void randomized_quicksort(int A[], int p, int r);
void quicksort_prim(int A[], int p, int r);

void stooge_sort(int A[], int p, int r);

void tre_quicksort(int A[], int p, int r);
void tre_quicksort_prim(int A[], int p, int r);

#endif // QUICKSORT_H