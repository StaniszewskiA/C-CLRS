#ifndef MACHINE_LEARNING_ALGORITHMS_H
#define MACHINE_LEARNING_ALGORITHMS_H

#include "../../common.h"
#include "../part_7_commons.h"

// ============================================================================
// CHAPTER 33.1: Clustering
// ============================================================================

#define CLUSTERING_N_POINTS 8
#define CLUSTERING_N_DIM 2
#define CLUSTERING_K 3
#define CLUSTERING_MAX_ITERS 10

typedef struct {
	double coords[CLUSTERING_N_DIM];
	int clusterId;
} ClusteringPoint;

typedef struct {
	double coords[CLUSTERING_N_DIM];
} ClusteringCentroid;

void lloyd_kmeans(
	ClusteringPoint* points,
	int nPoints,
	int nDim,
	int k,
	int maxIter,
	ClusteringCentroid* centroids
);
void test_lloyd_kmeans(void);

void kmeans_1d(
    ClusteringPoint* points,
    int nPoints,
    int k,
    ClusteringCentroid* centroids
);
void test_kmeans_1d(void);

// ============================================================================
// CHAPTER 33.2: Multiplicative weight update method
// ============================================================================

#define MWU_N_EXPERTS 4
#define MWU_N_ROUNDS 10
#define MWU_N_TRIALS 100000

void weighted_majority(
    const int* predictions,
    const int* outcomes,
    int T,
    int n,
    double gamma,
    double* weights,
    int* p
);
void test_weighted_majority(void);

int halving_with_reset(
    const int* preds,
    const int* outcomes,
    int T,
    int n,
    int* p
);
void test_halving_with_reset(void);

void randomized_halving(
    const int* preds,
    const int* outcomes,
    int T,
    int n,
    int* p
);
void test_randomized_halving(void);

void randomized_weighted_majority(
    const int* preds,
    const int* outcomes,
    int T,
    int n,
    double epsilon,
    double* weights,
    int* p
);
void test_randomized_weighted_majority(void);

// ============================================================================
// CHAPTER 33.3: Gradient descent
// ============================================================================



// ============================================================================
// PROBLEMS
// ============================================================================

#endif 
