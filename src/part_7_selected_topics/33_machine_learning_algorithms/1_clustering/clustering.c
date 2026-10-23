#include "part_7_selected_topics/33_machine_learning_algorithms/33_machine_learning_algorithms.h"

static int points_equal(
    const ClusteringPoint* a,
    const ClusteringPoint* b,
    int nDim
) {
    for (int i = 0; i < nDim; ++i) if (fabs(a->coords[i] - b->coords[i]) > 1e-9) return 0;
    return 1;
}

static double clustering_distance(
    const double* a, 
    const double* b,
    int nDim
) {
    // clrs uses distance squared, not Euclidean distance
    double sum = 0.0;

    for (int i = 0; i < nDim; ++i) {
        double dist = a[i] - b[i];
        sum += dist * dist;
    }

    return sum;
}

static void clustering_init_centroids(
    const ClusteringPoint* points,
    ClusteringCentroid* centroids,
    int nPoints,
    int k,
    int nDim
) {
    // 33.1-3: assign centroids using Fisher-Yates shuffling
    int chosenCnt = 0;
    
    int indices[nPoints];
    for (int i = 0; i < nPoints; ++i) indices[i] = i;

    for (int i = nPoints - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        SWAP_INT(indices[i], indices[j]);
    }

    for (int i = 0; i < nPoints && chosenCnt < k; ++i) {
        int idx = indices[i];
        int duplicate = 0;

        for (int centroid = 0; centroid < chosenCnt; ++centroid) {
            ClusteringPoint tmpPoint;
            for (int dim = 0; dim < nDim; ++dim)
                tmpPoint.coords[dim] = centroids[centroid].coords[dim];

            if (points_equal(&points[idx], &tmpPoint, nDim)) {
                duplicate = 1;
                break;
            }
        }

        if (!duplicate) {
            for (int dim = 0; dim < nDim; ++dim)
                centroids[chosenCnt].coords[dim] = points[idx].coords[dim];
            chosenCnt++;
        }
    }

    while (chosenCnt < k) {
        int idx = rand() % nPoints;
        for (int dim = 0; dim < nDim; ++dim) 
            centroids[chosenCnt].coords[dim] = points[idx].coords[dim];
        chosenCnt++;
    }
}

static int clustering_assign_clusters(
    ClusteringPoint* points,
    const ClusteringCentroid* centroids,
    int nPoints,
    int k,
    int nDim
) {
    int changed = 0;

    for (int i = 0; i < nPoints; ++i) {
        double minDist = DBL_MAX;
        int best = -1;

        for (int centroid = 0; centroid < k; ++centroid) {
            double dist = clustering_distance(points[i].coords, centroids[centroid].coords, nDim);

            if (dist < minDist) {
                minDist = dist;
                best = centroid;
            }
        }

        if (points[i].clusterId != best) {
            points[i].clusterId = best;
            changed = 1;
        }
    }

    return changed;
}

static void clustering_update_centroids(
    const ClusteringPoint* points,
    ClusteringCentroid* centroids,
    int nPoints,
    int k,
    int nDim
) {
    int counts[k];
    double sums[k][nDim];

    for (int cluster = 0; cluster < k; ++cluster) {
        counts[cluster] = 0;
        for (int j = 0; j < nDim; ++j) sums[cluster][j] = 0.0;
    }

    for (int i = 0; i < nPoints; ++i) {
        int cluster = points[i].clusterId;

        for (int j = 0; j < nDim; ++j) sums[cluster][j] += points[i].coords[j];

        counts[cluster]++;
    }

    for (int cluster = 0; cluster < k; ++cluster) {
        if (counts[cluster] == 0) continue;
        for (int j = 0; j < nDim; ++j) 
            centroids[cluster].coords[j] = sums[cluster][j] / counts[cluster];
    }
}

void lloyd_kmeans(
	ClusteringPoint* points,
	int nPoints,
	int nDim,
	int k,
	int maxIter,
	ClusteringCentroid* centroids
) {
    clustering_init_centroids(points, centroids, nPoints, k, nDim);

    for (int iter = 0; iter < maxIter; ++iter) {
        int changed = clustering_assign_clusters(points, centroids, nPoints, k, nDim);
        clustering_update_centroids(points, centroids, nPoints, k, nDim);
        if (!changed) break;
    }
}


static void clustering_print_clusters(
    const ClusteringPoint* points,
    const ClusteringCentroid* centroids,
    int nClusters,
    int nDim,
    int nPoints
) {
    for (int c = 0; c < nClusters; ++c) {
        printf("Cluster %d centroid: (", c);
        for (int j = 0; j < nDim; ++j)
            printf("%.2f%s", centroids[c].coords[j],
                   j == nDim - 1 ? ")\n" : ", ");

        printf("  Points: ");
        for (int i = 0; i < nPoints; ++i) {
            if (points[i].clusterId == c) {
                printf("[");
                for (int d = 0; d < nDim; ++d) {
                    printf("%.2f%s", points[i].coords[d], d == nDim - 1 ? "" : ", ");
                }
                printf("] ");
            }
        }
        printf("\n");
    }
}

void test_lloyd_kmeans(void) {
    srand(time(NULL));
    ClusteringPoint points[] = {
        {{1.0, 2.0}, -1},
        {{1.5, 1.8}, -1}, 
        {{5.0, 8.0}, -1}, 
        {{8.0, 8.0}, -1},
        {{1.0, 0.6}, -1}, 
        {{9.0, 11.0}, -1}, 
        {{8.0, 2.0}, -1}, 
        {{10.0, 2.0}, -1}
    };

    int nPoints = ARRAY_SIZE(points);
    int nDim = ARRAY_SIZE(points[0].coords);
    int k = 3;

    ClusteringCentroid centroids[nPoints];

    lloyd_kmeans(points, nPoints, nDim, k, CLUSTERING_MAX_ITERS, centroids);
    clustering_print_clusters(points, centroids, k, nDim, nPoints);
}

// 33.1-4
void kmeans_1d(
    ClusteringPoint* points,
    int nPoints,
    int k,
    ClusteringCentroid* centroids
) {
    // sort
    for (int i = 0; i < nPoints - 1; ++i) {
        for (int j = 0; j < nPoints - i - 1; ++j) {
            if (points[j].coords[0] <= points[j + 1].coords[0]) continue;
            ClusteringPoint tmp = points[j];
            points[j] = points[j+1];
            points[j+1] = tmp;
        }
    }

    // get diffs
    double diffs[nPoints - 1];
    for (int i = 0; i < nPoints - 1; ++i)
        diffs[i] = points[i + 1].coords[0] - points[i].coords[0];

    // get biggest diffs as bounds
    int bounds[k-1];
    for (int i = 0; i < k - 1; ++i) bounds[i] = -1;

    for (int b = 0; b < k - 1; ++b) {
        double maxDiff = -1;
        int maxIdx = -1;
        for (int i = 0; i < nPoints - 1; ++i) {
            int seen = 0;
            for (int j = 0; j < b; ++j) {
                if (bounds[j] == i) { seen = 1; break; }
            }
            if (!seen && diffs[i] > maxDiff) {
                maxDiff = diffs[i];
                maxIdx = i;
            }
        }
        bounds[b] = maxIdx;
    }

    // sort bounds
    for (int i = 0; i < k - 2; ++i) {
        for (int j = 0; j < k - 2 - i; ++j) {
            if (bounds[j] > bounds[j + 1]) SWAP_INT(bounds[j], bounds[j + 1]);
        }
    }

    // assign clusters
    int startIdx = 0;
    for (int cluster = 0; cluster < k; ++cluster) {
        int endIdx = (cluster < k - 1) ? bounds[cluster] : nPoints - 1;
        double sum = 0.0;
        for (int i = startIdx; i <= endIdx; ++i) {
            points[i].clusterId = cluster;
            sum += points[i].coords[0];
        }

        centroids[cluster].coords[0] = sum / (endIdx - startIdx + 1);
        startIdx = endIdx + 1;
    }
}

void test_kmeans_1d(void) {
    srand(time(NULL));

    ClusteringPoint points[] = {
        {{1.0}, -1},
        {{2.0}, -1},
        {{3.0}, -1},
        {{10.0}, -1},
        {{11.0}, -1},
        {{12.0}, -1}
    };

    int nPoints = ARRAY_SIZE(points);
    int nDim = ARRAY_SIZE(points[0].coords);
    int k = 2;

    ClusteringCentroid centroids[k];

    kmeans_1d(points, nPoints, k, centroids);
    clustering_print_clusters(points, centroids, k, nDim, nPoints);
}
