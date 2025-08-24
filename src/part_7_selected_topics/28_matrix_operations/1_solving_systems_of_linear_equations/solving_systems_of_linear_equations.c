#include "part_7_selected_topics/28_matrix_operations/28_matrix_operations.h"

void lu_decomposition(double** A, double** L, double** U, int n) {
    // Initialize matrices
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            U[i][j] = 0.0;
            L[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }

    for (int k = 0; k < n; ++k) {
        U[k][k] = A[k][k];
        for (int i = k + 1; i < n; ++i) {
            L[i][k] = A[i][k] / A[k][k];
            U[k][i] = A[k][i];
        }

        // Schur complement
        for (int i = k + 1; i < n; ++i) 
            for (int j = k + 1; j < n; ++j) A[i][j] -= L[i][k] * U[k][j];
    }
}

static void forward_substitution(double** L, double* y, double* b, int n) {
    for (int i = 0; i < n; ++i) {
        y[i] = b[i];
        for (int j = 0; j < i; ++j) y[i] -= L[i][j] * y[j];
        y[i] /= L[i][i];
    }
}

static void backward_substitution(double** U, double* x, double* y, int n) {
    for (int i = n - 1; i >= 0; --i) {
        x[i] = y[i];
        for (int j = i + 1; j < n; j++) x[i] -= U[i][j] * x[j];
        x[i] /= U[i][i];
    }
}

void lu_solve(double** A, double* x, double* b, int n) {
    double** L = allocate_matrix_double(n, n);
    double** U = allocate_matrix_double(n, n);

    double** copyA = allocate_matrix_double(n, n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) copyA[i][j] = A[i][j];

    lu_decomposition(copyA, L, U, n);

    double* y = (double*)safe_malloc(n * sizeof(double));

    // Ly = B
    forward_substitution(L, y, b, n);

    // Ux = y
    backward_substitution(U, x, y, n);

    free_matrix_double(L, n);
    free_matrix_double(U, n);
    free_matrix_double(copyA, n);
    safe_free(y);
}

void test_lu_decomposition(void) {
    int n = 3;

    double** A = allocate_matrix_double(n, n);
    double** L = allocate_matrix_double(n, n);
    double** U = allocate_matrix_double(n, n);

    A[0][0] = 1.0;  A[0][1] = 2.0;  A[0][2] = 0.0; 
    A[1][0] = 3.0;  A[1][1] = 4.0;  A[1][2] = 4.0; 
    A[2][0] = 5.0;  A[2][1] = 6.0;  A[2][2] = 3.0;

    printf("Matrix A:\n");
    print_matrix_double(A, n);

    // Copy matrix
    double** copyA = allocate_matrix_double(n, n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) copyA[i][j] = A[i][j];


    double* b = (double*)safe_malloc(n * sizeof(double));
    double* x = (double*)safe_malloc(n * sizeof(double));

    b[0] = 3.0;
    b[1] = 7.0;
    b[2] = 8.0;

    lu_solve(A, x, b, n);

    printf("Solution x = [");
    for (int i = 0; i < n; ++i) {
        printf("%.3f", x[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");

    free_matrix_double(A, n);
    free_matrix_double(L, n);
    free_matrix_double(U, n);
    safe_free(b);
    safe_free(x);
}

int lup_decomposition(double** A, int* pi, int n) {
    for (int i = 0; i < n; ++i) pi[i] = i;

    for (int k = 0; k < n; ++k) {
        double p = 0.0;
        int kPrime = k;

        for (int i = k; i < n; ++i) {
            if (fabs(A[i][k]) <= p) continue;
            p = fabs(A[i][k]);
            kPrime = i;
        }

        if (p == 0.0) {
            printf("Error: singular matrix\n");
            return 0;
        }

        SWAP_INT(pi[k], pi[kPrime]);
        for (int j = 0; j < n; ++j) SWAP_DOUBLE(A[k][j], A[kPrime][j]);
        for (int i = k + 1; i < n; ++i) {
            A[i][k] = A[i][k] / A[k][k];
            for (int j = k + 1; j < n; ++j) A[i][j] -= A[i][k] * A[k][j];
        }
    }

    return 1;
}

static void extract_lu_from_lup(double** A, double** L, double** U, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i > j) {
                // Lower
                L[i][j] = A[i][j];
                U[i][j] = 0.0;
            } else if (i == j) {
                // Diagonal
                L[i][j] = 1.0;
                U[i][j] = A[i][j];
            } else {
                // Upper
                L[i][j] = 0.0;
                U[i][j] = A[i][j];
            }
        }
    } 
}

static void print_permutation_matrix(int* pi, int n) {
    printf("Permutation matrix P:\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j == pi[i]) printf("   1.000 ");
            else printf("   0.000 ");
        }
        printf("\n");
    }
    printf("\n");
}

void lup_solve(double** A, double* x, double* b, int n) {
    int* pi = (int*)safe_malloc(n * sizeof(int));
    double** copyA = allocate_matrix_double(n, n);
    double** A_copy = allocate_matrix_double(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A_copy[i][j] = A[i][j];
        }
    }

    if (!lup_decomposition(copyA, pi, n)) {
        printf("Failed to decompose the matrix\n");
        free_matrix_double(copyA, n);
        safe_free(pi);
        return;
    }

    printf("Permutation pi: [");
    for (int i = 0; i < n; i++) {
        printf("%d", pi[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");

    print_permutation_matrix(pi, n);

    double* pb = (double*)safe_malloc(n * sizeof(double));
    for (int i = 0; i < n; ++i) pb[i] = b[pi[i]];

    double** L = allocate_matrix_double(n, n);
    double** U = allocate_matrix_double(n, n);
    extract_lu_from_lup(A_copy, L, U, n);

    printf("Matrix L:\n");
    print_matrix_double(L, n);

    printf("Matrix U:\n");
    print_matrix_double(U, n);

    double* y = (double*)safe_malloc(n * sizeof(double));
    forward_substitution(L, y, pb, n);
    backward_substitution(U, x, y, n);

    free_matrix_double(copyA, n);
    free_matrix_double(L, n);
    free_matrix_double(U, n);
    safe_free(pi);
    safe_free(pb);
    safe_free(y);
}

void test_lup_decomposition(void) {
    int n = 4;
    double** A = allocate_matrix_double(n, n);
    A[0][0] = 2.0;  A[0][1] = 0.0;  A[0][2] = 2.0; A[0][3] = 0.6;
    A[1][0] = 3.0;  A[1][1] = 3.0;  A[1][2] = 4.0; A[1][3] = -2.0;
    A[2][0] = 5.0;  A[2][1] = 5.0;  A[2][2] = 4.0; A[2][3] = 2.0;
    A[3][0] = -1.0;  A[3][1] = -2.0;  A[3][2] = 3.4; A[3][3] = -1.0;

    printf("Matrix A:\n");
    print_matrix_double(A, n);

    int* pi = (int*)safe_malloc(n * sizeof(int));

    double* b = (double*)safe_malloc(n * sizeof(double));
    double* x = (double*)safe_malloc(n * sizeof(double));

    b[0] = 8.0;
    b[1] = 9.0;
    b[2] = 7.0;

    printf("Solving Ax = b where b = [%.1f, %.1f, %.1f]\n", b[0], b[1], b[2]);

    lup_solve(A, x, b, n);

    printf("Solution x = [");
    for (int i = 0; i < n; i++) {
        printf("%.3f", x[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");

    free_matrix_double(A, n);
    safe_free(pi);
    safe_free(b);
    safe_free(x);
}
