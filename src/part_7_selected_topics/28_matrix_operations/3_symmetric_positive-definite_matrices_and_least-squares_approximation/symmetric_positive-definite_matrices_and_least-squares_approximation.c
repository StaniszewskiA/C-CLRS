#include "part_7_selected_topics/28_matrix_operations/28_matrix_operations.h"

void compute_pseudoinverse(double** A, double** Ap, int rows, int cols) {
    // Compute A^T
    double** AT = allocate_matrix_double(cols, rows);
    for (int i = 0; i < cols; ++i)
        for (int j = 0; j < rows; ++j) AT[i][j] = A[j][i];

    // Compute A^T*A
    double** ATA = allocate_matrix_double(cols, cols);
    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < cols; ++j) {
            ATA[i][j] = 0.0;
            for (int k = 0; k < rows; ++k) ATA[i][j] += AT[i][k] * A[k][j];
        }
    }

    // Invert A^T*A
    double** invATA = allocate_matrix_double(cols, cols);
    lup_invert_matrix(ATA, invATA, cols);

    // Compute Ap = inv(A^T*A) * AT
    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++j) {
            Ap[i][j] = 0.0;
            for (int k = 0; k < cols; ++k) Ap[i][j] += invATA[i][k] * AT[k][j];
        }
    }

    free_matrix_double(AT, cols);
    free_matrix_double(ATA, cols);
    free_matrix_double(invATA, cols);
}

void polynomial_least_squares_pseudoinverse(
    const double* x, 
    const double* y, 
    int n, 
    int degree, 
    double* coeffs
) {
    // Build basis matrix
    double** A = allocate_matrix_double(n, degree + 1);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j <= degree; ++j) A[i][j] = pow(x[i], j);

    // Compute pseudoinverse
    double** Ap = allocate_matrix_double(degree + 1, n);
    compute_pseudoinverse(A, Ap, n, degree + 1);

    // coeffs = Ap * y
    for (int i = 0; i <= degree; ++i) {
        coeffs[i] = 0.0;
        for (int j = 0; j < n; ++j) coeffs[i] += Ap[i][j] * y[j];
    }

    free_matrix_double(A, n);
    free_matrix_double(Ap, degree);
}

void test_polynomial_least_squares_pseudoinverse(void) {
    int n = 5;
    int degree = 2;
    double x[5] = {-1, 1, 2, 3, 5};
    double y[5] = {2, 1, 1, 0, 3};
    double coeffs[3];

    polynomial_least_squares_pseudoinverse(x, y, n, degree, coeffs);

    printf("Least squares polynomial:\n");
    for (int i = 0; i <= degree; ++i) {
        if (i == 0) printf("%.6f", coeffs[i]);
        else printf(" %c %.6f*x^{%d}", (coeffs[i] >= 0) ? '+' : '-', fabs(coeffs[i]), i);
    }
    printf("\n");

    printf("Approximated values:\n");
    for (int i = 0; i < n; ++i) {
        double approx = 0.0;
        for (int j = 0; j <= degree; ++j) approx += coeffs[j] * pow(x[i], j);
        printf("x = %.2f, y = %.2f, approx = %.6f\n", x[i], y[i], approx);
    }
}
