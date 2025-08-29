#include "part_7_selected_topics/28_matrix_operations/28_matrix_operations.h"

#define TASK 1

void solve_tridiagonal(
    int n, 
    double* a, 
    double* b, 
    double* c, 
    double* d, 
    double* x
) {
    double* cPrime = safe_malloc(n * sizeof(double));
    double* dPrime = safe_malloc(n * sizeof(double));

    cPrime[0] = c[0] / b[0];
    dPrime[0] = d[0] / b[0];

    for (int i = 1; i < n; ++i) {
        double denom = b[i] - a[i] * cPrime[i - 1];
        cPrime[i] = c[i] / denom;
        dPrime[i] = (d[i] - a[i] * dPrime[i - 1]) / denom;
    }

    x[n - 1] = dPrime[n - 1];
    for (int i = n - 2; i >= 0; --i) x[i] = dPrime[i] - cPrime[i] * x[i + 1];

    safe_free(cPrime);
    safe_free(dPrime);
}

void cubic_spline(int n, double* x, double* y, double* D) {
    double* h = safe_malloc((n - 1) * sizeof(double));
    double* a = safe_malloc(n * sizeof(double));
    double* b = safe_malloc(n * sizeof(double));
    double* c = safe_malloc(n * sizeof(double));
    double* d = safe_malloc(n * sizeof(double));

    for (int i = 0; i < n - 1; ++i) h[i] = x[i + 1] - x[i];

    a[0] = 0;
    b[0] = 1;
    c[0] = 0;
    d[0] = 0;

    for (int i = 1; i < n - 1; ++i) {
        a[i] = h[i - 1];
        b[i] = 2 * (h[i - 1] + h[i]);
        c[i] = h[i];
        d[i] = 3 * ((y[i + 1] - y[i]) / h[i] - (y[i] - y[i - 1]) / h[i - 1]);
    }

    a[n - 1] = 0;
    b[n - 1] = 1;
    c[n - 1] = 0;
    d[n - 1] = 0;

    solve_tridiagonal(n, a, b, c, d, D);

    safe_free(h);
    safe_free(a);
    safe_free(b);
    safe_free(c);
    safe_free(d);
}

double eval_cubic_spline(
    double x0,
    double x1,
    double y0,
    double y1,
    double D0,
    double D1,
    double x
) {
    double h = x1 - x0;
    double t = (x - x0) / h;
    double A = (1 - t);
    double B = t;
    double C = (A * A * A - A) * h * h / 6.0;
    double D = (B * B * B - B) * h * h / 6.0;

    return A * y0 + B * y1 + C * D0 + D * D1;
}

void test_cubic_spline(void) {
    int n = 5;
    double x[] = {0, 1, 2, 3, 4};
    double y[] = {1, 3, 3, 4, 5};
    double D[5];

    cubic_spline(n, x, y, D);

    printf("Derivatives vector D:\n");
    for (int i = 0; i <  n; ++i) printf("D[%d] = %f\n", i, D[i]);

    int i = 2;
    double val = eval_cubic_spline(x[i], x[i + 1], y[i], y[i + 1], D[i], D[i + 1], 2.5);
    printf("Spline(2.5) = %f\n", val);
}

int main(void) {
    switch (TASK)
    {
        case 1: {
            // 28-2: Splines
            test_cubic_spline();
            break;
        }
    }
}
