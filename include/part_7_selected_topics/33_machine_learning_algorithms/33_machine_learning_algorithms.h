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



// ============================================================================
// CHAPTER 33.3: Gradient descent
// ============================================================================



// ============================================================================
// PROBLEMS
// ============================================================================

#endif 
