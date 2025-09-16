#include "part_7_selected_topics/30_polynomials_and_the_fft/polynomials_and_the_fft.h"

void fft(const complex double* a, complex double* y, int n, int invert) {
    if (n == 1) {
        y[0] = a[0];
        return;
    }

    double angle = 2 * M_PI / n * (invert ? -1 : 1);
    complex double omega_n = cexp(I * angle);
    complex double omega = 1;

    complex double aEven[n / 2];
    complex double aOdd[n / 2];
    for (int i = 0; i < n / 2; ++i) {
        aEven[i] = a[2 * i];
        aOdd[i] = a[2 * i + 1];
    }

    complex double yEven[n / 2];
    complex double yOdd[n / 2];

    fft(aEven, yEven, n / 2, invert);
    fft(aOdd, yOdd, n / 2, invert);

    for (int k = 0; k < n / 2; ++k) {
        y[k] = yEven[k] + omega * yOdd[k];
        y[k + n / 2] = yEven[k] - omega * yOdd[k];
        omega *= omega_n;
    }

    if (invert)
        for (int i = 0; i < n; ++i) y[i] /= 2;
}

void test_fft(void) {
    int n = 4;
    complex double a[4] = {-1, 8, 0, 0};
    complex double y[4];
    complex double b[4];

    printf("Input: \n");
    for (int i = 0; i < n; ++i) printf("%.2f%+.2fi ", creal(a[i]), cimag(a[i]));
    printf("\n");

    fft(a, y, n, 0);

    printf("FFT:\n");
    for (int i = 0; i < n; ++i) printf("%.2f%+.2fi ", creal(y[i]), cimag(y[i]));
    printf("\n");

    fft(y, b, n, 1);

    printf("IFFT of previous FFT (should be equal to the original input):\n");
    for (int i = 0; i < n; ++i) printf("%.2f%+.2fi ", creal(b[i]), cimag(b[i]));
    printf("\n");
}

void fft_radix3(const complex double* a, complex double* y, int n, int invert) {
    if (n == 1) {
        y[0] = a[0];
        return;
    }

    int m = n / 3;
    complex double a0[m];
    complex double a1[m];
    complex double a2[m];

    for (int i = 0; i < m; ++i) {
        a0[i] = a[3 * i];
        a1[i] = a[3 * i + 1];
        a2[i] = a[3 * i + 2];
    }

    complex double y0[m];
    complex double y1[m];
    complex double y2[m];
    
    fft_radix3(a0, y0, m, invert);
    fft_radix3(a1, y1, m, invert);
    fft_radix3(a2, y2, m, invert);

    double sign = invert ? -1.0 : 1.0;

    for (int k = 0; k < n; ++k) {
        int km = k % m;
        complex double omega = cexp(sign * 2.0 * M_PI * I * k / m);
        complex double omegaSquared = omega * omega;
        y[k] = y0[km] + omega * y1[km] + omegaSquared * y2[km];
        if (invert) y[k] /= 3.0;
    }
}

void test_fft_radix3(void) {
    int n = 9;
    complex double a[9] = {1,2,3,4,5,6,7,8,9};
    complex double y[9];

    printf("Input:\n");
    for (int i = 0; i < n; ++i) printf("%.2f%+.2fi ", creal(a[i]), cimag(a[i]));
    printf("\n");

    fft_radix3(a, y, n, 0);
    for (int i = 0; i < n; ++i) printf("%.2f%+.2fi ", creal(y[i]), cimag(y[i]));
    printf("\n");
}

void z_transform(
    const double* a, 
    int n, 
    complex double* z, 
    int m, 
    complex double* Y
) {
    for (int i = 0; i < m; ++i) {
        Y[i] = 0.0;
        for (int k = 0; k < n; ++k) Y[i] += a[k] * cpow(z[i], -k);
    }
}

void test_z_transform(void) {
    int n = 4;
    double a[4] = {1, 2, 3, 4};

    int m = 3;
    complex double z[3] = {1.0, 0.5 + 0.5*I, -1.0};
    complex double Y[3];

    printf("Input:\n");
    for (int i = 0; i < n; ++i) printf("%.2f%+.2fi ", creal(a[i]), cimag(a[i]));
    printf("\n");

    printf("Z vector:\n");
    for (int i = 0; i < m; ++i) printf("%.2f%+.2fi ", creal(z[i]), cimag(z[i]));
    printf("\n");

    z_transform(a, n, z, m, Y);

    printf("Z-transform's output:\n");
    for (int i = 0; i < m; ++i) printf("%.2f%+.2fi ", creal(Y[i]), cimag(Y[i]));
    printf("\n");
}
