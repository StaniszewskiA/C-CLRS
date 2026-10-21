#include "part_7_selected_topics/33_machine_learning_algorithms/33_machine_learning_algorithms.h"

void gradient_descent(
    GradientFunc gradient,
    const double* x0,
    int n,
    double gamma,
    int T,
    double* xAvg
) {
    double x[n];
    double grad[n];
    double sum[n];

    for (int i = 0; i < n; ++i) {
        x[i] = x0[i];
        sum[i] = 0.0;
    }

    for (int t = 0; t < T; ++t) {
        for (int i = 0; i < n; ++i) sum[i] += x[i];
        
        gradient(x, grad, n);

        for (int i = 0; i < n; ++i) x[i] -= gamma * grad[i];
    }

    for (int i = 0; i < n; ++i) xAvg[i] = sum[i] / T;
}

static double gd_quadratic(
    const double* x,
    int n
) {
    double val = 0.0;
    for (int i = 1; i <= n; ++i) {
        double diff = x[i - 1] - i;
        val += i * diff * diff;
    } 

    return val;
}

static void gd_quadratic_gradient(
    const double* x,
    double* grad,
    int n
) {
    for (int i = 1; i <= n; ++i) grad[i - 1] = 2.0 * i * (x[i - 1] - i);
}

static void gd_print_vec(
    const double* x,
    int n
) {
    printf("(");
    for (int j = 0; j < n; ++j) printf("%.6f%s", x[j], j == n - 1 ? ")" : ", ");
}

void test_gradient_descent(void) {
    double x0[GD_N_DIM];
    int n = ARRAY_SIZE(x0);
    for (int i = 0; i < n; ++i) x0[i] = 0.0;

    double minimum[GD_N_DIM];
    for (int i = 0; i < n; ++i) minimum[i] = i + 1;

    int iters[] = {1, 10, 100, 1000};
    int nIters = ARRAY_SIZE(iters);

    print_separator("Gradient descent, f(x) = sum j (x_j - j)^2");
    printf("n = %d, gamma = %.2f, x(0) = ", n, GD_GAMMA);
    gd_print_vec(x0, n);
    printf(", minimum at ");
    gd_print_vec(minimum, n);
    printf("\n");

    for (int i = 0; i < nIters; ++i) {
        double xAvg[GD_N_DIM];
        gradient_descent(
            gd_quadratic_gradient,
            x0,
            n,
            GD_GAMMA,
            iters[i],
            xAvg
        );

        printf("T = %4d: x-avg = ", iters[i]);
        gd_print_vec(xAvg, n);
        printf(", f(x-avg) = %.6f\n", gd_quadratic(xAvg, n));
    }
}

void gradient_descent_constrained(
    GradientFunc gradient,
    ProjectionFunc project,
    const double* x0,
    int n,
    double gamma,
    int T,
    double* xAvg
) {
    double x[n];
    double xNext[n];
    double grad[n];
    double sum[n];

    for (int i = 0; i < n; ++i) {
        x[i] = x0[i];
        sum[i] = 0.0;
    }

    for (int t = 0; t < T; ++t) {
        for (int i = 0; i < n; ++i) sum[i] += x[i];

        gradient(x, grad, n);
        for (int i = 0; i < n; ++i) xNext[i] = x[i] - gamma * grad[i];

        project(xNext, x, n);
    }

    for (int i = 0; i < n; ++i) xAvg[i] = sum[i] / T;
}

static void gd_project_box(
    const double* y,
    double* x,
    int n
) {
    for (int i = 0; i < n; ++i)
        x[i] = fmin(fmax(y[i], GD_BOX_LOWER), GD_BOX_UPPER);
}

void test_gradient_descent_constrained(void) {
    double x0[GD_N_DIM];
    int n = ARRAY_SIZE(x0);
    for (int i = 0; i < n; ++i) x0[i] = 0.0;

    double unconstrained[GD_N_DIM];
    double minimum[GD_N_DIM];
    for (int i = 0; i < n; ++i) unconstrained[i] = i + 1;
    gd_project_box(unconstrained, minimum, n);
    double fMin = gd_quadratic(minimum, n);

    int iters[] = {1, 10, 100, 1000};
    int nIters = ARRAY_SIZE(iters);

    print_separator("Constrained gradient descent, K = box");
    printf("n = %d, gamma = %.2f, K = [%.2f, %.2f]^n, x(0) = ",
        n, GD_GAMMA, GD_BOX_LOWER, GD_BOX_UPPER
    );
    gd_print_vec(x0, n);
    printf("\nminimum on K at ");
    gd_print_vec(minimum, n);
    printf(", f = %.6f\n", fMin);

    for (int i = 0; i < nIters; ++i) {
        double xAvg[GD_N_DIM];
        gradient_descent_constrained(
            gd_quadratic_gradient,
            gd_project_box,
            x0,
            n,
            GD_GAMMA,
            iters[i],
            xAvg
        );

        printf("T = %4d: x-avg = ", iters[i]);
        gd_print_vec(xAvg, n);
        printf(", f(x-avg) - f(x*) = %.6f\n", gd_quadratic(xAvg, n) - fMin);
    }
}

// 33.3-5
void squared_error_gradient(
    const double* w,
    const double* x,
    const double* y,
    int n,
    int m,
    double* grad
) {
    for (int k = 0; k <= n; ++k) grad[k] = 0.0;

    for (int i = 0; i < m; ++i) {
        const double* xi = &x[i * n];

        // error e^(i), computed once per point
        double e = w[0] - y[i];
        for (int j = 0; j < n; ++j) e += w[j + 1] * xi[j];

        grad[0] += 2.0 * e;

        for (int k = 0; k < n; ++k) grad[k + 1] += 2.0 * e * xi[k];
    }
}

static double gd_squared_error(
    const double* w,
    const double* x,
    const double* y,
    int n,
    int m
) {
    double sum = 0.0;
    for (int i = 0; i < m; ++i) {
        double e = w[0] - y[i];
        for (int j = 0; j < n; ++j) e += w[j + 1] * x[i * n + j];
        sum += e * e;
    }

    return sum;
}

void test_squared_error_gradient(void) {
    // y = 1 + 2 x_1 - 3 x_2, so the gradient is zero at w = (1, 2, -3)
    double x[GD_N_POINTS][GD_N_FEATURES] = {
        {0.0, 0.0},
        {1.0, 0.0},
        {0.0, 1.0},
        {1.0, 1.0},
        {2.0, 1.0}
    };
    double y[GD_N_POINTS] = {1.0, 3.0, -2.0, 0.0, 2.0};

    int m = ARRAY_SIZE(y);
    int n = ARRAY_SIZE(x[0]);

    double weights[][GD_N_FEATURES + 1] = {
        {0.0, 0.0, 0.0},
        {0.5, -1.0, 2.0},
        {1.0, 2.0, -3.0}
    };
    int nWeights = ARRAY_SIZE(weights);
    double h = 1e-6;

    print_separator("Gradient of squared error (33.3-5)");
    printf("m = %d points, n = %d features, data from y = 1 + 2 x1 - 3 x2\n",
        m, n
    );

    for (int i = 0; i < nWeights; ++i) {
        double* w = weights[i];
        double grad[GD_N_FEATURES + 1];
        squared_error_gradient(w, &x[0][0], y, n, m, grad);

        // central differences as an independent check
        double numeric[GD_N_FEATURES + 1];
        for (int k = 0; k <= n; ++k) {
            double saved = w[k];
            w[k] = saved + h;
            double plus = gd_squared_error(w, &x[0][0], y, n, m);
            w[k] = saved - h;
            double minus = gd_squared_error(w, &x[0][0], y, n, m);
            w[k] = saved;
            numeric[k] = (plus - minus) / (2.0 * h);
        }

        printf("\nw = ");
        gd_print_vec(w, n + 1);
        printf(", error = %.4f\n", gd_squared_error(w, &x[0][0], y, n, m));
        printf("  gradient:           ");
        gd_print_vec(grad, n + 1);
        printf("\n  finite differences: ");
        gd_print_vec(numeric, n + 1);
        printf("\n");
    }
}

// 33.3-7
static int gd_nearest_centroid(
    const double* x,
    const ClusteringCentroid* centroids,
    int k,
    int nDim,
    double* bestDist
) {
    int best = 0;
    *bestDist = DBL_MAX;
    for (int l = 0; l < k; ++l) {
        double dist = 0.0;
        for (int d = 0; d < nDim; ++d) {
            double diff = x[d] - centroids[l].coords[d];
            dist += diff * diff;
        }

        if (dist < *bestDist) {
            *bestDist = dist;
            best = l;
        }
    }


    return best;
}

void kmeans_gradient_descent(
    ClusteringPoint* points,
    int nPoints,
    int nDim,
    int k,
    double gamma,
    int T,
    ClusteringCentroid* centroids
) {
    double grad[k][nDim];
    int counts[k];
    double dist[nPoints];

    for (int t = 0; t < T; ++t) {
        for (int l = 0; l < k; ++l) {
            counts[l] = 0;
            for (int d = 0; d < nDim; ++d) grad[l][d] = 0.0; 
        }

        // assign every points to its nearest center and add
        // 2*(c- - x) to that center's gradient
        for (int i = 0; i < nPoints; ++i) {
            int l = gd_nearest_centroid(
                points[i].coords,
                centroids,
                k,
                nDim,
                &dist[i]
            );
            points[i].clusterId = l;
            counts[l]++;

            for (int d = 0; d < nDim; ++d)
                grad[l][d] += 2.0 * (
                    centroids[l].coords[d] - points[i].coords[d]
                );
        }

        for (int l = 0; l < k; ++l) {
            if (counts[l] > 0) {
                for (int d = 0; d < nDim; ++d) centroids[l].coords[d] -= gamma * grad[l][d];
                continue;
            }

            // an empty cluster has zero gradeint
            int farthest = 0;
            for (int i = 1; i < nPoints; ++i)
                if (dist[i] > dist[farthest]) farthest = i;

            for (int d = 0; d < nDim; ++d)
                centroids[l].coords[d] = points[farthest].coords[d];
            dist[farthest] = -1.0;
        }
    }

    for (int i = 0; i < nPoints; ++i) {
        double unused;
        points[i].clusterId = gd_nearest_centroid(
            points[i].coords,
            centroids,
            k,
            nDim,
            &unused
        );
    }
}

// f(S, C) from eq. 33.2
static double gd_kmeans_objective(
    const ClusteringPoint* points,
    int nPoints,
    int nDim,
    int k,
    const ClusteringCentroid* centroids
) {
    double sum = 0.0;
    for (int i = 0; i < nPoints; ++i) {
        double dist;
        gd_nearest_centroid(
            points[i].coords,
            centroids,
            k,
            nDim,
            &dist
        );
        sum += dist;
    }

    return sum;
}

void test_kmeans_gradient_descent(void) {
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

    ClusteringCentroid initial[] = {
        {{1.0, 2.0}},
        {{5.0, 8.0}},
        {{8.0, 2.0}}
    };
    int k = ARRAY_SIZE(initial);

    int iters[] = {0, 1, 2, 5, 10, 50};
    int nIters = ARRAY_SIZE(iters);
    ClusteringCentroid centroids[ARRAY_SIZE(initial)];

    print_separator("k-means by gradient descent (33.3-7)");
    printf("%d points, k = %d, gamma = %.2f\n",
        nPoints, k, GD_KMEANS_GAMMA
    );

    for (int i = 0; i < nIters; ++i) {
        for (int l = 0; l < k; ++l) centroids[l] = initial[l];

        kmeans_gradient_descent(
            points,
            nPoints,
            nDim,
            k,
            GD_KMEANS_GAMMA,
            iters[i],
            centroids
        );
        printf("T = %2d: f(S, C) = %.6f\n",
            iters[i], gd_kmeans_objective(points, nPoints, nDim, k, centroids)
        );
    }

    for (int l = 0; l < k; ++l) {
        printf("Cluster %d center: ", l);
        gd_print_vec(centroids[l].coords, nDim);
        printf("\n  Points: ");
        for (int i = 0; i < nPoints; ++i) {
            if (points[i].clusterId != l) continue;
            gd_print_vec(points[i].coords, nDim);
            printf(" ");
        }
        printf("\n");
    }
}