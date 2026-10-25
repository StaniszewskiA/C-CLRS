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

#define GD_N_DIM 2
#define GD_GAMMA 0.1

typedef void (*GradientFunc)(const double* x, double* grad, int n);

void gradient_descent(
    GradientFunc gradient,
    const double* x0,
    int n,
    double gamma,
    int T,
    double* xAvg
);
void test_gradient_descent(void);

#define GD_BOX_LOWER 0.0
#define GD_BOX_UPPER 1.5

typedef void (*ProjectionFunc)(const double* y, double* x, int n);

void gradient_descent_constrained(
    GradientFunc gradient,
    ProjectionFunc project,
    const double* x0,
    int n,
    double gamma,
    int T,
    double* xAvg
);
void test_gradient_descent_constrained(void);

#define GD_N_FEATURES 2
#define GD_N_POINTS 5

void squared_error_gradient(
    const double* w,
    const double* x,
    const double* y,
    int n,
    int m,
    double* grad
);
void test_squared_error_gradient(void);

#define GD_KMEANS_GAMMA 0.1

void kmeans_gradient_descent(
    ClusteringPoint* points,
    int nPoints,
    int nDim,
    int k,
    double gamma,
    int T,
    ClusteringCentroid* centroids
);
void test_kmeans_gradient_descent(void);


// ============================================================================
// PROBLEMS
// ============================================================================

#define NEWTON_N_ITERS 6

typedef double (*RealFunc)(double x);

int newton_method(
    RealFunc f,
    RealFunc fPrime,
    double x0,
    int T,
    double* xs
);
void test_newton_method(void);

void hedge(
    const int* preds,
    const int* outcomes,
    int T,
    int n,
    double epsilon,
    double* weights,
    int* p
);
void test_hedge(void);

#define SGD_N_POINTS 5
#define SGD_GAMMA 0.01
#define SGD_N_TRIALS 1000

void stochastic_gradient_descent(
    const double* x,
    const double* y,
    int n,
    double a0,
    double b0,
    double gamma,
    int T,
    double* aAvg,
    double* bAvg
);
void test_stochastic_gradient_descent(void);

#endif 
