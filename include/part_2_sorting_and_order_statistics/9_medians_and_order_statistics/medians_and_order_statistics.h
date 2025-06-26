#ifndef MEDIANS_AND_ORDER_STATISTICS_H
#define MEDIANS_AND_ORDER_STATISTICS_H

#include "../../common.h"
#include "../part_2_commons.h"

// ============================================================================
// MINIMUM AND MAXIMUM
// ============================================================================

int simple_min(int A[], int size);
int simple_max(int A[], int size);
void min_max(int A[], int size, int *min, int *max);

// ============================================================================
// SELECTION IN EXPECTED LINEAR TIME
// ============================================================================

int partition(int A[], int p, int r);
int randomized_partition(int A[], int p, int r);
int randomized_select(int A[], int p, int r, int i);
int randomized_select_iter(int A[], int p, int r, int i);

// ============================================================================
// SELECTION IN WORST CASE LINEAR TIME
// ============================================================================

int median(int X[], int Y[], int n);

// ============================================================================
// PROBLEMS
// ============================================================================

int partition_left_right(int A[],  int left, int right, int pivot);
void insetion_sort_left_right(int A[], int left, int right);
int select_median(int A[], int left, int right);
int select3(int A[], int left, int right, int k);

#endif // MEDIANS_AND_ORDER_STATISTICS_H