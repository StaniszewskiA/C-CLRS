#include "part_7_selected_topics/28_matrix_operations/28_matrix_operations.h"

void lup_invert_matrix(double** A, double** invA, int n) {
    int* pi = (int*)safe_malloc(n * sizeof(int));

    double** copyA = allocate_matrix_double(n, n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) copyA[i][j] = A[i][j];

    if (!lup_decomposition(copyA, pi, n)) {
        printf("Error: Matrix is singular\n");
        free_matrix_double(copyA, n);
        safe_free(pi);
        return;
    }

    double** L = allocate_matrix_double(n, n);
    double** U = allocate_matrix_double(n, n);
    extract_lu_from_lup(copyA, L, U, n);

    // Solve PAx = e_i for each column
    for (int col = 0; col < n; ++col) {
        double* e = (double*)safe_malloc(n * sizeof(double));
        for (int i = 0; i < n; ++i) e[i] = (i == col) ? 1.0 : 0.0;

        double* pe = (double*)safe_malloc(n * sizeof(double));
        for (int i = 0; i < n; ++i) pe[i] = e[pi[i]];

        // Solve Ly = Pe_i
        double* y = (double*)safe_malloc(n * sizeof(double));
        forward_substitution(L, y, pe, n);

        // Solve Ux = y
        double* xCol = (double*)safe_malloc(n * sizeof(double));
        backward_substitution(U, xCol, y, n);

        for (int i = 0; i < n; ++i) invA[i][col] = xCol[i];

        safe_free(e);
        safe_free(pe);
        safe_free(y);
        safe_free(xCol);
    }

    free_matrix_double(copyA, n);
    free_matrix_double(L, n);
    free_matrix_double(U, n);
    safe_free(pi);
}

static void verify_matrix_inverse(double** A, double** invA, int n) {
    double** res = allocate_matrix_double(n, n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            res[i][j] = 0.0;
            for (int k = 0; k < n; ++k) res[i][j] += A[i][k] * invA[k][j];
        }
    }

    printf("Matrix A * A^{-1}:\n");
    print_matrix_double(res, n);

    printf("Deviation from identity matrix:\n");
    double maxErr = 0.0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double expected = (i == j) ? 1.0 : 0.0;
            double error = fabs(res[i][j] - expected);
            if (error > maxErr) maxErr = error;
            printf("%8.6f ", error);
        }
        printf("\n");
    }
    printf("Maximum error: %.10f\n\n", maxErr);
    free_matrix_double(res, n);
}

void test_matrix_inversion(void) {
    int n = 3;
    double** A = allocate_matrix_double(n, n);
    double** invA = allocate_matrix_double(n, n);

    A[0][0] = 2.0;  A[0][1] = 1.0;  A[0][2] = 1.0;
    A[1][0] = 1.0;  A[1][1] = 3.0;  A[1][2] = 2.0;
    A[2][0] = 1.0;  A[2][1] = 0.0;  A[2][2] = 0.0;

    printf("Matrix A:\n");
    print_matrix_double(A, n);

    lup_invert_matrix(A, invA, n);

    printf("Inverse matrix A^{-1}:\n");
    print_matrix_double(invA, n);

    verify_matrix_inverse(A, invA, n);

    free_matrix_double(A, n);
    free_matrix_double(invA, n);
}

// 28.2-5

void conjugate_transpose(complex double** A, complex double** B, int n) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) B[i][j] = conj(A[i][j]);
}

void multiply_matrix_complex(
    complex double** A, 
    complex double** B, 
    complex double** C, 
    int n
) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = 0.0 + 0.0*I;
            for (int k = 0; k < n; ++k) C[i][j] += A[i][k] * B[k][j];
        }
    }
}

void forward_substitution_complex(
    complex double** L, 
    complex double* y, 
    complex double* b, 
    int n
) {
    for (int i = 0; i < n; ++i) {
        y[i] = b[i];
        for (int j = 0; j < i; ++j) y[i] -= L[i][j] * y[j];
        y[i] /= L[i][i];
    }
}

void backward_substitution_complex(
    complex double** U, 
    complex double* x,
    complex double* y,
    int n
) {
    for (int i = n - 1; i >= 0; --i) {
        x[i] = y[i];
        for (int j = i + 1; j < n; ++j) x[i] -= U[i][j] * x[j];
        x[i] /= U[i][i];
    }
}

int lup_decomposition_complex(complex double** A, int* pi, int n) {
    for (int i = 0; i < n; ++i) pi[i] = i;
    for (int k = 0; k < n; ++k) {
        double p = 0.0;
        int kPrime = k;
        for (int i = 0; i < n; ++i) {
            if (cabs(A[i][k]) <= p) continue;
            p = cabs(A[i][k]);
            kPrime = i;
        }

        if (p == 0.0) {
            printf("Error: singular matrix\n");
            return 0;
        }

        SWAP_INT(pi[k], pi[kPrime]);
        for (int j = 0; j < n; ++j) SWAP_COMPLEX(A[k][j], A[kPrime][j]);

        for (int i = k + 1; i < n; ++i) {
            A[i][k] /= A[k][k];
            for (int j = k + 1; j < n; ++j) A[i][j] -= A[i][k] * A[k][j];
        }
    }

    return 1;
}

void extract_lu_from_lup_complex(
    complex double** A, 
    complex double** L, 
    complex double** U, 
    int n
) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i > j) {
                L[i][j] = A[i][j];
                U[i][j] = 0.0 + 0.0*I;
            } else if (i == j) {
                L[i][j] = 1.0 + 0.0*I;
                U[i][j] = A[i][j];
            } else {
                L[i][j] = 0.0 + 0.0*I;
                U[i][j] = A[i][j];
            }
        }
    }
}

void lup_invert_matrix_complex(
    complex double** A,
    complex double** invA,
    int n
) {
    int* pi = (int*)safe_malloc(n * sizeof(int));
    complex double** copyA = allocate_matrix_complex(n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) copyA[i][j] = A[i][j];

    if (!lup_decomposition_complex(copyA, pi, n)) {
        printf("Error: Matrix is singular\n");
        free_matrix_complex(copyA, n);
        safe_free(pi);
        return;
    }

    complex double** L = allocate_matrix_complex(n);
    complex double** U = allocate_matrix_complex(n);
    extract_lu_from_lup_complex(copyA, L, U, n);

    for (int col = 0; col < n; ++col) {
        complex double* e = (complex double*)safe_malloc(n * sizeof(complex double));
        for (int i = 0; i < n; ++i) e[i] = (i == col) ? 1.0 + 0.0*I : 0.0 + 0.0*I;
        
        complex double* pe = (complex double*)safe_malloc(n * sizeof(complex double));
        for (int i = 0; i < n; ++i) pe[i] = e[pi[i]];

        complex double* y = (complex double*)safe_malloc(n * sizeof(complex double));
        forward_substitution_complex(L, y, pe, n);

        complex double* xCol = (complex double*)safe_malloc(n * sizeof(complex double));
        backward_substitution_complex(U, xCol, y, n);

        for (int i = 0; i < n; ++i) invA[i][col] = xCol[i];

        safe_free(e);
        safe_free(pe);
        safe_free(y);
        safe_free(xCol);
    }

    free_matrix_complex(copyA, n);
    free_matrix_complex(L, n);
    free_matrix_complex(U, n);
    safe_free(pi);
}

void test_complex_matrix_inversion(void) {
    int n = 2;
    complex double** A = allocate_matrix_complex(n);
    complex double** invA = allocate_matrix_complex(n);

    A[0][0] = 2.0 + 0.0*I;  A[0][1] = 1.0 - 1.0*I;
    A[1][0] = 1.0 + 1.0*I;  A[1][1] = 3.0 + 0.0*I;

    printf("Matrix A:\n");
    print_matrix_complex(A, n);

    lup_invert_matrix_complex(A, invA, n);

    printf("Inverse Matrix A^{-1}:\n");
    print_matrix_complex(invA, n);

    // Verify
    complex double** res = allocate_matrix_complex(n);
    multiply_matrix_complex(A, invA, res, n);
    printf("A * A^{-1}:\n");
    print_matrix_complex(res, n);

    free_matrix_complex(A, n);
    free_matrix_complex(invA, n);
    free_matrix_complex(res, n);
}
