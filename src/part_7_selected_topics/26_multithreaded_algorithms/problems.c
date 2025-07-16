#include "part_7_selected_topics/26_multithreaded_algorithms/multithreaded_algorithms.h"

#define TASK 11

#pragma region Implementing parallel loops using nested parallelism

void p_sum_arrays(int* A, int* B, int* C, int n) {
    /*
        Work: T_1 = Θ(n*lg(n))
        Span: T_{inf} = Θ(lg(n))
        Parallelism: Θ(n)  
    */
    #pragma omp parallel for
    for (int i = 0; i < n; i++) C[i] = A[i] + B[i];
}

static void add_subarray(int* A, int* B, int* C, int i, int j) {
    for (int k = i; k <= j; k++) C[k] = A[k] + B[k];
}

void sum_arrays_prime(int* A, int* B, int* C, int n) {
    /*
        Work: T_1 = Θ(n)
        Span: T_{inf} = Θ(sqrt(n))
        Parallelism: Θ(sqrt(n))  
    */
    int numThreads = omp_get_max_threads();
    int grainSize = (n < numThreads) ? 1 : (n + numThreads - 1) / numThreads;
    int r = (n + grainSize - 1) / grainSize;

    printf("n = %d, grain_size = %d, r = %d\n", n, grainSize, r);

    #pragma omp parallel
    {
        #pragma omp single
        {
            for (int k = 0; k < r; k++) {
                int start = k * grainSize;
                int end = ((k + 1) * grainSize < n) 
                    ? (k + 1) * grainSize - 1 : n - 1;
                #pragma omp task shared(A, B, C)
                add_subarray(A, B, C, start, end);
            }
            #pragma omp taskwait
        }
    }
}

void test_p_sum_arrays(void) {
    int n = 1 << 14;

    int* A = (int*)safe_malloc(n * sizeof(int));
    int* B = (int*)safe_malloc(n * sizeof(int));
    int* C1 = (int*)safe_malloc(n * sizeof(int));
    int* C2 = (int*)safe_malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        A[i] = random_int(1, 100);
        B[i] = random_int(1, 100);
    }

    printf("Arrays' size: %d\n", n);
    if (n <= 50) {
        printf("arr1: ");
        print_arr(A, n);
        printf("arr2: ");
        print_arr(B, n);
    }

    p_sum_arrays(A, B, C1, n);

    if (n <= 50) {
        printf("result: ");
        print_arr(C1, n);
    }

    sum_arrays_prime(A, B, C2, n);
    if (n <= 50) {
        printf("result: ");
        print_arr(C2, n);
    }

    int correct = 1;
    for (int i = 0; i < n; i++) {
        if (C1[i] != C2[i]) {
            correct = 0;
            break;
        }
    }

    printf("Are results correct: %s\n", correct ? "Yes" : "No");

    safe_free(A);
    safe_free(B);
    safe_free(C1);
    safe_free(C2);
}

#pragma endregion Implementing parallel loops using nested parallelism

#pragma region Saving temporary space in matrix multiplication

static void matrix_multiply_add(
    int** A, int** B, int** C,
    int aRowStart, int aColStart,
    int bRowStart, int bColStart,
    int cRowStart, int cColStart,
    int size
) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                C[cRowStart + i][cColStart + j] +=
                    A[aRowStart + i][aColStart + k] *
                    B[bRowStart + k][bColStart + j]; 
            }
        }
    }
}

void p_matrix_multiply_recursive_no_temp(int** A, int** B, int** C, int n) {
    /*
        Work: T_1 = Θ(n^3)
        Span: T_{inf} = Θ(n)
        Parallelism: Θ(n^2)  
    */
    if (n <= 4) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                C[i][j] = 0;
                for (int k = 0; k < n; k++) C[i][j] += A[i][k] * B[k][j];
            }
        }
        return;
    }

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = 0;;

    int half = n / 2;

    #pragma omp task shared(A, B, C)
    {
        // C11 = A11 * B11 + A12 * B21
        matrix_multiply_add(A, B, C, 0, 0, 0, 0, 0, 0, half);        // A11 * B11 -> C11
        matrix_multiply_add(A, B, C, 0, half, half, 0, 0, 0, half);  // A12 * B21 -> C11
    }
    
    #pragma omp task shared(A, B, C)
    {
        matrix_multiply_add(A, B, C, 0, 0, 0, half, 0, half, half);      
        matrix_multiply_add(A, B, C, 0, half, half, half, 0, half, half); 
    }
    
    #pragma omp task shared(A, B, C)
    {
        matrix_multiply_add(A, B, C, half, 0, 0, 0, half, 0, half);    
        matrix_multiply_add(A, B, C, half, half, half, 0, half, 0, half);
    }
    
    #pragma omp task shared(A, B, C)
    {
        matrix_multiply_add(A, B, C, half, 0, 0, half, half, half, half);     
        matrix_multiply_add(A, B, C, half, half, half, half, half, half, half);
    }

    #pragma omp taskwait
}

void print_dynamic_matrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void test_p_matrix_multiply_no_temp(void) {
    int n = 1 << 3;

    int** A = allocate_matrix(n, n);
    int** B = allocate_matrix(n, n);
    int** C = allocate_matrix(n, n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            A[i][j] = random_int(1, 2);
            B[i][j] = random_int(1, 2);
        }
    }

    printf("Matrix size: %dx%d\n", n, n);
    if (n <= 8) {
        printf("\nMatrix A:\n");
        print_dynamic_matrix(A, n);
        printf("\nMatrix B:\n");
        print_dynamic_matrix(B, n);
    }

    #pragma omp parallel
    {
        #pragma omp single
        {
            p_matrix_multiply_recursive_no_temp(A, B, C, n);
        }
    }

    if (n <= 8) {
        printf("\nMatrix C:\n");
        print_dynamic_matrix(C, n);
    }

    free_matrix(A, n);
    free_matrix(B, n);
    free_matrix(C, n);
}

#pragma endregion Saving temporary space in matrix multiplication

#pragma region Multithreaded matrix algorithms

void p_lu_decomposition(double** A, double** L, double** U, int n) {
    /*
        Work: T_1 = Θ(n^3)
        Span: T_∞ = Θ(n*lg(n))
        Parallelism: Θ(n^2/lg(n))
    */
    double** tmp = allocate_matrix_double(n, n);
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) tmp[i][j] = A[i][j];

    // Init
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            L[i][j] = (i == j) ? 1.0 : 0.0;
            U[i][j] = 0.0;
        }
    }

    // Decompose
    for (int k = 0; k < n; k++) {

        // Copy (U)
        #pragma omp parallel for
        for (int j = k ; j < n; j++) U[k][j] = tmp[k][j];

        // Multipliers (L)
        #pragma omp parallel for
        for (int i = k + 1; i < n; i++) L[i][k] = tmp[i][k] / tmp[k][k];

        // Update submatrix
        #pragma omp parallel for collapse(2)
        for (int i = k + 1; i < n; i++)
            for (int j = k + 1; j < n; j++) 
                tmp[i][j] = tmp[i][j] - L[i][k] * U[k][j];
    }

    free_matrix_double(tmp, n);
}

void test_p_lu_decomposition(void) {
    int n = 1 << 2;
    double** A = allocate_matrix_double(n, n);
    double** L = allocate_matrix_double(n, n);
    double** U = allocate_matrix_double(n, n);

    printf("Succefully allocated matrices\n");
    
    double testData[4][4] = {
        {4.0, 3.0, 2.0, 1.0},
        {3.0, 4.0, 3.0, 2.0},
        {2.0, 3.0, 4.0, 3.0},
        {1.0, 2.0, 3.0, 4.0}
    };
    
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < n; j++) A[i][j] = testData[i][j];

    printf("Original matrix A:\n");
    print_matrix_double(A, n);

    p_lu_decomposition(A, L, U, n);

    printf("\nL matrix:\n");
    print_matrix_double(L, n);
    
    printf("\nU matrix:\n");
    print_matrix_double(U, n);

    // Verify A = L*U
    double maxErr = 0.0;
    int correct = 1;
    double** tmp = allocate_matrix_double(n, n);

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            tmp[i][j] = 0.0;
            for (int k = 0; k < n; k++) tmp[i][j] += L[i][k] * U[k][j];
        }
    }

    printf("\nVerification (L*U):\n");
    print_matrix_double(tmp, n);


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double err = fabs(testData[i][j] - tmp[i][j]);
            printf("A[%d][%d] = %8.4f, (L*U)[%d][%d] = %8.4f, error = %e\n", 
                   i, j, testData[i][j], i, j, tmp[i][j], err);
            maxErr = fmax(maxErr, err);
            if (err > 1e-10) correct = 0;
        }
    }

    printf("\nResults:\n");
    printf("Maximum error: %e\n", maxErr);
    printf("LU decomposition: %s\n", correct ? "CORRECT" : "INCORRECT");

    free_matrix_double(A, n);
    free_matrix_double(L, n);
    free_matrix_double(U, n);
    free_matrix_double(tmp, n);
}

void p_lup_decomposition(double** A, double** L, double** U, int* P, int n) {
    /*
        Work: T_1 = Θ(n^3)
        Span: T_∞ = Θ(n^2)
        Parallelism: Θ(n)
    */
    double** tmpMat = allocate_matrix_double(n, n);
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) tmpMat[i][j] = A[i][j];

    // Init perm 
    for (int i = 0; i < n; i++) P[i] = i;

    // Init L and U
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            L[i][j] = (i == j) ? 1.0 : 0.0;
            U[i][j] = 0.0;
        }
    }

    // Decompose
    for (int k = 0; k < n; k++) {
        // Find pivot
        double maxVal = 0.0;
        int pivotRow = k;
        for (int i = k; i < n; i++) {
            if (fabs(tmpMat[i][k]) <= maxVal) continue;
            maxVal = fabs(tmpMat[i][k]);
            pivotRow = i;
        }

        if (pivotRow != k) {
            // Swap perms
            int tmpP = P[k];
            P[k] = P[pivotRow];
            P[pivotRow] = tmpP;

            // Swap rows
            #pragma omp parallel for
            for (int j = 0; j < n; j++) {
                double tmp = tmpMat[k][j];
                tmpMat[k][j] = tmpMat[pivotRow][j];
                tmpMat[pivotRow][j] = tmp;
            }
        }

        // U
        #pragma omp parallel for
        for (int j = k; j < n; j++) U[k][j] = tmpMat[k][j];

        // L
        #pragma omp parallel for
        for (int i = k + 1; i < n; i++) L[i][k] = tmpMat[i][k] / tmpMat[k][k];

        // Update submatrix
        #pragma omp parallel for collapse(2)
        for (int i = k + 1; i < n; i++)
            for (int j = k + 1; j < n; j++)
                tmpMat[i][j] = tmpMat[i][j] - L[i][k] * U[k][j];
    }

    free_matrix_double(tmpMat, n);
}

void test_p_lup_decomposition(void) {
    int n = 1 << 2;
    double** A = allocate_matrix_double(n, n);
    double** L = allocate_matrix_double(n, n);
    double** U = allocate_matrix_double(n, n);
    int* P = (int*)safe_malloc(n * sizeof(int));

    printf("Succefully allocated matrices\n");
    
    double testData[4][4] = {
        {4.0, 3.0, 2.0, 1.0},
        {3.0, 4.0, 3.0, 2.0},
        {2.0, 3.0, 4.0, 3.0},
        {1.0, 2.0, 3.0, 4.0}
    };
    
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < n; j++) A[i][j] = testData[i][j];

    printf("Original matrix A:\n");
    print_matrix_double(A, n);

    p_lup_decomposition(A, L, U, P, n);

    printf("\nL matrix:\n");
    print_matrix_double(L, n);
    
    printf("\nU matrix:\n");
    print_matrix_double(U, n);

    printf("\nPermutation vector P:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", P[i]);
    }
    printf("\n");

    // Verify PA = LU
    double** PA = allocate_matrix_double(n, n);
    double** LU = allocate_matrix_double(n, n);
    
    // Compute PA
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) PA[i][j] = testData[P[i]][j];

    // Compute LU
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            LU[i][j] = 0.0;
            for (int k = 0; k < n; k++) LU[i][j] += L[i][k] * U[k][j];
        }
    }

    printf("\nPA matrix (permuted A):\n");
    print_matrix_double(PA, n);
    
    printf("\nLU matrix:\n");
    print_matrix_double(LU, n);

    double maxErr = 0.0;
    int correct = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double err = fabs(PA[i][j] - LU[i][j]);
            printf("PA[%d][%d] = %8.4f, (L*U)[%d][%d] = %8.4f, error = %e\n", 
                   i, j, PA[i][j], i, j, LU[i][j], err);
            maxErr = fmax(maxErr, err);
            if (err > 1e-10) correct = 0;
        }
    }

    printf("\nResults:\n");
    printf("Maximum error: %e\n", maxErr);
    printf("LUP decomposition: %s\n", correct ? "CORRECT" : "INCORRECT");

    free_matrix_double(A, n);
    free_matrix_double(L, n);
    free_matrix_double(U, n);
    free_matrix_double(PA, n);
    free_matrix_double(LU, n);
    safe_free(P);
}

void p_lup_solve(
    double** L,
    double** U, 
    int* P, 
    double* b, 
    double* x, 
    int n
) {
    /*
        1) Solve Ly = Pb (forward substitution)
        2) Solve Ux = y (backward substitution)

        Work: T_1 = Θ(n^2)
        Span: T_∞ = Θ(n)
        Parallelism: Θ(n)
    */
    double* y = (double*)safe_malloc(n * sizeof(double));
    double* pb = (double*)safe_malloc(n * sizeof(double));

    // Permute b vec
    #pragma omp parallel for
    for (int i = 0; i < n; i++) pb[i] = b[P[i]];

    // Forward substitution
    for (int i = 0; i < n; i++) {
        y[i] = pb[i];
        for (int j = 0; j < i; j++) y[i] -= L[i][j] * y[j];
    }

    // Backward substitution
    for (int i = n - 1; i >= 0; i--) {
        x[i] = y[i];
        for (int j = i + 1; j < n; j++) x[i] -= U[i][j] * x[j];
        x[i] /= U[i][i];
    }

    safe_free(y);
    safe_free(pb);
}

void test_p_lup_solve(void) {
    int n = 1 << 2;
    double** A = allocate_matrix_double(n, n);
    double** L = allocate_matrix_double(n, n);
    double** U = allocate_matrix_double(n, n);
    int* P = (int*)safe_malloc(n * sizeof(int));
    double* b = (double*)safe_malloc(n * sizeof(double));
    double* x = (double*)safe_malloc(n * sizeof(double));

    double testData[4][4] = {
        {4.0, 3.0, 2.0, 1.0},
        {3.0, 4.0, 3.0, 2.0},
        {2.0, 3.0, 4.0, 3.0},
        {1.0, 2.0, 3.0, 4.0}
    };
    double solution[4]= {1.0, 2.0, 3.0, 4.0};

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) A[i][j] = testData[i][j];

    for (int i = 0; i < n; i++) {
        b[i] = 0.0;
        for (int j = 0; j < n; j++) b[i] += A[i][j] * solution[j];
    }

    printf("Original matrix A:\n");
    print_matrix_double(A, n);

    printf("\nRight-hand side b:\n");
    for (int i = 0; i < n; i++) {
        printf("%8.4f ", b[i]);
    }
    printf("\n");
    
    printf("\nExpected solution x:\n");
    for (int i = 0; i < n; i++) {
        printf("%8.4f ", solution[i]);
    }
    printf("\n");

    p_lup_decomposition(A, L, U, P, n);

    printf("\nAfter LUP decomposition:\n");
    printf("L matrix:\n");
    print_matrix_double(L, n);
    
    printf("\nU matrix:\n");
    print_matrix_double(U, n);
    
    printf("\nPermutation vector P:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", P[i]);
    }
    printf("\n");

    // Solve
    p_lup_solve(L, U, P, b, x, n);
    
    printf("\nComputed solution x:\n");
    for (int i = 0; i < n; i++) {
        printf("%8.4f ", x[i]);
    }
    printf("\n");
    
    // Verify
    double maxErr = 0.0;
    int correct = 1;
    
    printf("\nVerification:\n");
    for (int i = 0; i < n; i++) {
        double err = fabs(solution[i] - x[i]);
        printf("Expected[%d] = %8.4f, Computed[%d] = %8.4f, error = %e\n", 
               i, solution[i], i, x[i], err);
        maxErr = fmax(maxErr, err);
        if (err > 1e-10) correct = 0;
    }

    double* verification_b = (double*)safe_malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) {
        verification_b[i] = 0.0;
        for (int j = 0; j < n; j++) {
            verification_b[i] += testData[i][j] * x[j];
        }
    }
    
    printf("\nVerification (A*x should equal b):\n");
    double maxErrB = 0.0;
    for (int i = 0; i < n; i++) {
        double err = fabs(b[i] - verification_b[i]);
        printf("b[%d] = %8.4f, (A*x)[%d] = %8.4f, error = %e\n", 
               i, b[i], i, verification_b[i], err);
        maxErrB = fmax(maxErrB, err);
        if (err > 1e-10) correct = 0;
    }
    
    printf("\nResults:\n");
    printf("Maximum solution error: %e\n", maxErr);
    printf("Maximum verification error: %e\n", maxErrB);
    printf("LUP solve: %s\n", correct ? "CORRECT" : "INCORRECT");

    free_matrix_double(A, n);
    free_matrix_double(L, n);
    free_matrix_double(U, n);
    safe_free(P);
    safe_free(b);
    safe_free(x);
}

void p_cholesky_decomposition(double** A, double** L, int n) {
    /*
        Work: T_1 = Θ(M(n))
        Span: T_∞ = Θ(lg^2(n))
        Parallelism: Θ(M(n)/lg^2(n))

        M(n) - time to compute matrix products
    */
    
    // Init L
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) L[i][j] = 0.0;

    // Decompose
    for (int k = 0; k < n; k++) {
        // Diagonal
        double sum = 0.0;
        for (int j = 0; j < k; j++) sum += L[k][j] * L[k][j];
        L[k][k] = (sqrt(A[k][k] - sum));
        
        // Column below diagonal
        #pragma omp parallel for 
        for (int i = k + 1; i < n; i++) {
            double iSum = 0.0;
            for (int j = 0; j < k; j++) iSum += L[i][j] * L[k][j];
            L[i][k] = (A[i][k] - iSum) / L[k][k];
        }
    }
}

void p_matrix_inverse_spd(double** A, double** invA, int n) {
    /*
        Work: T_1 = Θ(n^3)
        Span: T_∞ = Θ(n)
        Parallelism: Θ(n^2)
    */
    double** L = allocate_matrix_double(n, n);
    double** Y = allocate_matrix_double(n, n);

    // Decompose
    p_cholesky_decomposition(A, L, n);

    // LY = I
    #pragma omp parallel for
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            double sum = 0.0;
            for (int j = 0; j < i; j++) sum += L[i][j] * Y[j][k];
            Y[i][k] = ((i == k) ? 1.0 : 0.0) - sum;
            Y[i][k] /= L[i][i]; 
        }
    }

    // L^T = A^{-1} = Y
    #pragma omp parallel for
    for (int k = 0; k < n; k++) {
        for(int i = n - 1; i >= 0; i--) {
            double sum = 0.0;
            for (int j = i + 1; j < n; j++) sum += L[j][i] * invA[j][k];
            invA[i][k] = (Y[i][k] - sum) / L[i][i];
        }
    }

    free_matrix_double(L, n);
    free_matrix_double(Y, n);
}

void test_p_cholesky_decomposition(void) {
    int n = 1 << 2;
    double** A = allocate_matrix_double(n, n);
    double** L = allocate_matrix_double(n, n);
    double** invA = allocate_matrix_double(n, n);
    double** verification = allocate_matrix_double(n, n);

    double spdData[4][4] = {
        {4.0, 2.0, 1.0, 0.5},
        {2.0, 3.0, 1.5, 0.8},
        {1.0, 1.5, 2.0, 1.0},
        {0.5, 0.8, 1.0, 1.5}
    };

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) A[i][j] = spdData[i][j];
        
    printf("Original SPD matrix A:\n");
    print_matrix_double(A, n);

    // Cholesky decomposition
    p_cholesky_decomposition(A, L, n);
    printf("\nCholesky factor L:\n");
    print_matrix_double(L, n);

    // Verify Cholesky decomposition (A = L*L^T)
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            verification[i][j] = 0.0;
            for (int k = 0; k < n; k++) verification[i][j] += L[i][k] * L[j][k];
        }
    }

    printf("\nVerification (L * L^T):\n");
    print_matrix_double(verification, n);
    
    double maxErr = 0.0;
    int correct = 1;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double err = fabs(spdData[i][j] - verification[i][j]);
            maxErr = fmax(maxErr, err);
            if (err > 1e-10) correct = 0;
        }
    }
    
    printf("\nCholesky decomposition: %s (max error: %e)\n", 
           correct ? "CORRECT" : "INCORRECT", maxErr);

    // Invert matrix
    p_matrix_inverse_spd(A, invA, n);

    printf("\nComputed inverse A^(-1):\n");
    print_matrix_double(invA, n);

    // Verify A * A^{-1} = I
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            verification[i][j] = 0.0;
            for (int k = 0; k < n; k++) verification[i][j] += A[i][k] * invA[k][j];
        }
    }

    printf("\nVerification (A * A^(-1)):\n");
    print_matrix_double(verification, n);
    
    double maxErr2 = 0.0;
    int correct2 = 1;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double expected = (i == j) ? 1.0 : 0.0;
            double err = fabs(verification[i][j] - expected);
            maxErr2 = fmax(maxErr2, err);
            if (err > 1e-10) correct2 = 0;
        }
    }
    
    printf("\nMatrix inversion: %s (max error: %e)\n", 
           correct2 ? "CORRECT" : "INCORRECT", maxErr2);

    free_matrix_double(A, n);
    free_matrix_double(invA, n);
    free_matrix_double(verification, n);
}

#pragma endregion Multithreaded matrix algorithms

#pragma region Multithreading reductions and prefix computations

static int p_reduce_helper(int* x, int n, int i, int j) {
    /*
        Work: T_1 = Θ(n) (cutoff is Θ(sqrt(n)))
        Span: T_{inf} = Θ(lg(n)) 
        Parallelism: Θ(n) / Θ(n/lg(n)) 
    */
    if (i == j) return x[i];

    if (j - i < sqrt(n)) {
        int sum = 0;
        for (int k = i; k <= j; k++) sum += x[k];
        return sum;
    }

    int mid = (i + j) / 2;
    int left = 0; 
    int right = 0;

    #pragma omp taskgroup
    {
        #pragma omp task shared(left)
        left = p_reduce_helper(x, n, i, mid);

        #pragma omp task shared(right) 
        right = p_reduce_helper(x, n, mid + 1, j);
    }

    return left + right;
}

int p_reduce(int* x, int n) {
    int res = 0;

    #pragma omp parallel
    {
        #pragma omp single nowait
        {
            res = p_reduce_helper(x, n, 0, n - 1);
        }
    }

    return res;
}

void test_p_reduce(void) {
    int n = 1 << 25;
    int* x = (int*)safe_malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) x[i] = random_int(1, 100);

    printf("Input array size: %d\n", n);
    if (n <= 50) {
        printf("Array:\n");
        print_arr(x, n);
    }

    int seqSum = 0;

    double seqStart = omp_get_wtime();
    for (int i = 0; i < n; i++) seqSum += x[i];
    double seqEnd = omp_get_wtime();
    double seqTime = seqEnd - seqStart;

    printf("seq reduction time: %.6f\n", seqTime);
    printf("seq sum: %d\n", seqSum);

    double par1Start = omp_get_wtime();
    int parSum = p_reduce(x, n);
    double par1End = omp_get_wtime();
    double par1Time = par1End - par1Start;

    printf("Parallel reduction time: %.6f\n", par1Time);
    printf("Parallel reduction sum: %d\n", parSum);

    printf("Speedup: %.2fx\n", seqTime / par1Time);
    printf("Results match? %s\n", (seqSum == parSum) ? "Yes" : "No");

    safe_free(x);
}

void scan(int* x, int* y, int n) {
    if (n <= 0) return;
    y[0] = x[0];
    for (int i = 1; i < n; ++i) y[i] = y[i - 1] + x[i];
}

static void p_scan1_aux(int* x, int* y, int i, int j) {
    #pragma omp parallel for
    for (int l = i; l <= j; l++) y[l] = p_reduce(x, l + 1);
}

void p_scan1(int* x, int* y, int n) {
    /*
        Work: T_1 = Θ(n^2)
        Span: T_∞ = Θ(lg(n))
        Parallelism: Θ(n^2/lg(n))
    */
    p_scan1_aux(x, y, 0, n - 1);
}

static void p_scan2_aux(int* x, int* y, int i, int j) {
    if (i == j) {
        y[i] = x[i];
        return;
    }
    int k = (i + j) / 2;

    #pragma omp task shared(x, y)
    p_scan2_aux(x, y, i, k);
    p_scan2_aux(x, y, k + 1, j);
    #pragma omp taskwait

    int leftSum = y[k];
    #pragma omp parallel for
    for (int l = k + 1; l <= j; l++) y[l] = leftSum + y[l];
}

void p_scan2(int* x, int* y, int n) {
    /*
        Work: T_1 = Θ(n)
        Span: T_∞ = Θ(lg(n))
        Parallelism: Θ(n/lg(n))
    */
    #pragma omp parallel
    {
        #pragma omp single nowait
        {
            p_scan2_aux(x, y, 0, n - 1);
        }
    }
}

static int p_scan3_up(int* x, int* t, int i, int j) {
    /*
        Compute subarrays and store in t
    */
    if (i == j) return x[i];
    int k = (i + j) / 2;
    int left, right;

    #pragma omp task shared(left)
    left = p_scan3_up(x, t, i, k);
    right = p_scan3_up(x, t, k + 1, j);
    #pragma omp taskwait

    t[k] = left;
    return left + right;
}

static int p_scan3_down(int v, int* x, int* t, int* y, int i, int j) {
    /*
        Compute the final scan using t
    */
    if (i == j) {
        y[i] = v + x[i];
        return 0;
    }
    int k = (i + j) / 2;

    #pragma omp task
    p_scan3_down(v, x, t, y, i, k);
    p_scan3_down(v + t[k], x, t, y, k + 1, j);
    #pragma omp taskwait

    return 0;
}

void p_scan3(int* x, int* y, int n) {
    /*
        Work: T_1 = Θ(n)
        Span: T_∞ = Θ(lg(n))
        Parallelism: Θ(n/lg(n))
    */
    if (n <= 0) return;
    int* t = (int*)safe_malloc(n * sizeof(int));
    y[0] = x[0];
    if (n > 1) {
        #pragma omp parallel
        {
            #pragma omp single nowait
            {
                p_scan3_up(x, t, 1, n - 1);
                p_scan3_down(x[0], x, t, y, 1, n - 1);
            }
        }
    }

    safe_free(t);
}

static void p_scan3_aux_no_t(int v, int* x, int* y, int i, int j) {
    if (i == j) {
        y[i] = v + x[i];
        return;
    }

    int k = (i + j) / 2;
    int leftSum;

    #pragma omp task shared(leftSum)
    {
        p_scan3_aux_no_t(v, x, y, i, k);
    }
    #pragma omp taskwait

    leftSum = y[k];

    #pragma omp task
    {
        p_scan3_aux_no_t(leftSum, x, y, k + 1, j);
    }
    #pragma omp taskwait
}

void p_scan3_no_t(int* x, int* y, int n) {
    if (n <= 0) return;
    y[0] = x[0];

    if (n > 1) {
        #pragma omp parallel
        {
            #pragma omp single nowait
            {
                p_scan3_aux_no_t(x[0], x, y, 1, n - 1);
            }
        }
    }
}

void p_scan4(int* x, int n) {
    // Blelloch scan
    if (n <= 1) return;

    int last = x[n - 1]; // Θ(1) space

    // Up
    for (int d = 1; d < n; d <<= 1) {
        #pragma omp parallel for
        for (int i = 0; i < n; i += (d << 1))
            if (i + (d << 1) - 1 < n) x[i + (d << 1) - 1] += x[i + d - 1];
    }

    // Set to neutral element
    x[n - 1] = 0;

    // Down
    for (int d = n >> 1; d >= 1; d >>= 1) {
        #pragma omp parallel for
        for (int i = 0; i < n; i += (d << 1)) {
            if (i + (d << 1) - 1 >= n) continue;
            int temp = x[i + d - 1];
            x[i + d - 1] = x[i + (d << 1) - 1];
            x[i + (d << 1) - 1] += temp;
        }
    }

    // Convert exclusive to inclusive
    for (int i = 0; i < n - 1; ++i) x[i] = x[i + 1];
    x[n - 1] += last;
}

void test_p_scan(void) {
    int n = 1 << 2;
    printf("Input size: %d\n", n);

    int* x = (int*)safe_malloc(n * sizeof(int));
    int* seqY = (int*)safe_malloc(n * sizeof(int));
    int* parY1 = (int*)safe_malloc(n * sizeof(int));
    int* parY2 = (int*)safe_malloc(n * sizeof(int));
    int* parY3a = (int*)safe_malloc(n * sizeof(int));
    int* parY3b = (int*)safe_malloc(n * sizeof(int));

    for (int i = 0; i < n; ++i) x[i] = random_int(1, 100);

    if (n <= 32) {
        printf("Input array:\n");
        print_arr(x, n);
    }

    #define TIME_SCAN(func, out, ...) ({         \
        double start = omp_get_wtime();     \
        func(__VA_ARGS__);                  \
        double end = omp_get_wtime();       \
        (end - start);                      \
    })

    double seqTime = TIME_SCAN(scan, seqY, x, seqY, n);
    double par1Time = TIME_SCAN(p_scan1, parY1, x, parY1, n);
    double par2Time = TIME_SCAN(p_scan2, parY2, x, parY2, n);
    double par3aTime = TIME_SCAN(p_scan3, parY3a, x, parY3a, n);
    double par3bTime = TIME_SCAN(p_scan3_no_t, parY3b, x, parY3b, n);

    double par4Start = omp_get_wtime();
    p_scan4(x, n);
    double par4End = omp_get_wtime();
    double par4Time = par4End - par4Start;

    if (n <= 32) {
        printf("Sequential scan result:\n"); print_arr(seqY, n);
        printf("Parallel scan1 result:\n"); print_arr(parY1, n);
        printf("Parallel scan2 result:\n"); print_arr(parY2, n);
        printf("Parallel scan3a result:\n"); print_arr(parY3a, n);
        printf("Parallel scan3b result:\n"); print_arr(parY3b, n);
        printf("Parallel scan4 result:\n"); print_arr(x, n);
    }

    int correct = 1;
    for (int i = 0; i < n; ++i) {
        int val = seqY[i];
        if (val != parY1[i] || val != parY2[i] || val != parY3a[i] || val != parY3b[i] || val != x[i]) {
            correct = 0;
            break;
        }
    }

    printf("Sequential scan time: %.6f\n", seqTime);
    printf("Parallel scan1 time: %.6f\n", par1Time);
    printf("Parallel scan2 time: %.6f\n", par2Time);
    printf("Parallel scan3a time: %.6f\n", par3aTime);
    printf("Parallel scan3b time: %.6f\n", par3bTime);
    printf("Parallel scan4 time: %.6f\n", par4Time);
    printf("Speedup (scan1): %.2fx\n", seqTime / par1Time);
    printf("Speedup (scan2): %.2fx\n", seqTime / par2Time);
    printf("Speedup (scan3a): %.2fx\n", seqTime / par3aTime);
    printf("Speedup (scan3b): %.2fx\n", seqTime / par3bTime);
    printf("Speedup (scan4): %.2fx\n", seqTime / par4Time);
    printf("Results match? %s\n", correct ? "Yes" : "No");

    safe_free(x);
    safe_free(seqY);
    safe_free(parY1);
    safe_free(parY2);
    safe_free(parY3a);
    safe_free(parY3b);
}

int p_are_parenthese_balanced(const char* str, int n) {
    int* tmp = (int*)safe_malloc(n * sizeof(int));
    int* scanArr = (int*)safe_malloc(n * sizeof(int));

    #pragma omp parallel for
    for (int i = 0; i < n; ++i) tmp[i] = (str[i] == '(') ? 1 : -1;

    p_scan2(tmp, scanArr, n);

    int isValid = 1;
    #pragma omp parallel for reduction(&&:isValid)
    for (int i = 0; i < n; ++i) if (scanArr[i] < 0) isValid = 0;

    int sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; ++i) sum += (str[i] == '(') ? 1 : -1;

    safe_free(tmp);
    safe_free(scanArr);
    return isValid && (sum == 0);
}

void test_p_are_parentheses_balanced(void) {
    const char* testCase1 = "((()))";
    const char* testCase2 = ")))()";
    const char* testCase3 = "(())))";

    printf("Test1: %s -> %s\n", testCase1, 
        p_are_parenthese_balanced(testCase1, strlen(testCase1)) 
            ? "PASSED" 
            : "NOT PASSED"
        );
    printf("Test2: %s -> %s\n", testCase2, 
        p_are_parenthese_balanced(testCase2, strlen(testCase2)) 
            ? "PASSED" 
            : "NOT PASSED"
        );
    printf("Test3: %s -> %s\n", testCase3, 
        p_are_parenthese_balanced(testCase3, strlen(testCase3)) 
            ? "PASSED" 
            : "NOT PASSED"
        );
}

#pragma endregion Multithreading reductions and prefix computations

#pragma region Multithreading a simple stencil calculation

void simple_stencil(int** A, int** staticInfo, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int up = (i > 0) ? A[i - 1][j] : 0;
            int left = (j > 0) ? A[i][j - 1] : 0;
            A[i][j] = up + left + staticInfo[i][j];
        }
    }
}

void p_simple_stencil_recursive_2_by_2(
    int** A,
    int** staticInfo,
    int i1,
    int i2,
    int j1,
    int j2
) {
    /*
        Work: T_1 = Θ(n^2)
        Span: T_{inf} = Θ(n)
        Parallelism: Θ(n)  
    */
    int cutoff = 1 << 4;
    if ((i2 - i1 + 1) <= cutoff || (j2 - j1 + 1) <= cutoff) {
        for (int i = i1; i <= i2; ++i)
            for (int j = j1; j <= j2; ++j) {
                int up = (i > 0) ? A[i - 1][j] : 0;
                int left = (j > 0) ? A[i][j - 1] : 0;
                A[i][j] = up + left + staticInfo[i][j];
            }
        return;
    }

    int mi = (i1 + i2) / 2;
    int mj = (j1 + j2) / 2;

    // Fill A11
    p_simple_stencil_recursive_2_by_2(A, staticInfo, i1, mi, j1, mj);

    // Fill A12 and A21
    #pragma omp parallel sections
    {
        #pragma omp section
        p_simple_stencil_recursive_2_by_2(A, staticInfo, i1, mi, mj + 1, j2);

        #pragma omp section
        p_simple_stencil_recursive_2_by_2(A, staticInfo, mi + 1, i2, j1, mj);
    }

    // Fill A22
    p_simple_stencil_recursive_2_by_2(A, staticInfo, mi + 1, i2, mj + 1, j2);
}

void p_simple_stencil_recursive_3_by_3(
    int** A, 
    int** staticInfo,
    int i1,
    int i2,
    int j1,
    int j2
) {
    /*
        Work: T_1 = Θ(n^2)
        Span: T_{inf} = Θ(n)
        Parallelism: Θ(n)  
    */
    int cutoff = 1 << 4;
    if ((i2 - i1 + 1) <= cutoff || (j2 - j1 + 1) <= cutoff) {
        for (int i = i1; i <= i2; ++i)
            for (int j = j1; j <= j2; ++j) {
                int up = (i > 0) ? A[i - 1][j] : 0;
                int left = (j > 0) ? A[i][j - 1] : 0;
                A[i][j] = up + left + staticInfo[i][j];
            }
        return;
    }

    int di = (i2 - i1 + 1) / 3;
    int dj = (j2 - j1 + 1) / 3;

    int iA = i1 + di - 1;
    int iB = i1 + 2 * di - 1;
    int jA = j1 + dj - 1;
    int jB = j1 + 2 * dj - 1;

    // Fill A11
    p_simple_stencil_recursive_3_by_3(A, staticInfo, i1, iA, j1, jA);

    // Fill A12 and A21
    #pragma omp parallel sections
    {
        #pragma omp section
        p_simple_stencil_recursive_3_by_3(A, staticInfo, i1, iA, jA + 1, jB);
        
        #pragma omp section
        p_simple_stencil_recursive_3_by_3(A, staticInfo, iA + 1, iB, j1, jA);
    }

    // Fill A13, A22 and A31
    #pragma omp parallel sections
    {
        #pragma omp section
        p_simple_stencil_recursive_3_by_3(A, staticInfo, i1, iA, jB + 1, j2);

        #pragma omp section
        p_simple_stencil_recursive_3_by_3(A, staticInfo, iA + 1, iB, jA + 1, jB);
        
        #pragma omp section
        p_simple_stencil_recursive_3_by_3(A, staticInfo, iB + 1, i2, j1, jA);
    }

    // Fill A23 and A32
    #pragma omp parallel sections
    {
        #pragma omp section
        p_simple_stencil_recursive_3_by_3(A, staticInfo, iA + 1, iB, jB + 1, j2);
        
        #pragma omp section
        p_simple_stencil_recursive_3_by_3(A, staticInfo, iB + 1, i2, jA + 1, jB);
    }

    // Fill A33
    p_simple_stencil_recursive_3_by_3(A, staticInfo, iB + 1, i2, jB + 1, j2);
}

void p_simple_stencil_recursive_b_by_b(
    int** A, 
    int** staticInfo,
    int i1,
    int i2,
    int j1,
    int j2,
    int b
) {
    /*
        Work: T_1 = Θ(n^2)
        Span: T_{inf} = Θ(n)
        Parallelism: Θ(n)  
    */
    int cutoff = 1 << 4;
    if ((i2 - i1 + 1) <= cutoff || (j2 - j1 + 1) <= cutoff) {
        for (int i = i1; i <= i2; ++i)
            for (int j = j1; j <= j2; ++j) {
                int up = (i > 0) ? A[i - 1][j] : 0;
                int left = (j > 0) ? A[i][j - 1] : 0;
                A[i][j] = up + left + staticInfo[i][j];
            }
        return;
    }

    int ni = i2 - i1 + 1;
    int nj = j2 - j1 + 1;
    int bi = ni / b;
    int bj = nj / b;

    // Set block limits
    int iStart[b + 1];
    iStart[0] = i1;
    
    int jStart[b + 1];
    jStart[0] = j1;

    for (int k = 1; k <= b; ++k) {
        iStart[k] = iStart[k - 1] + bi;
        jStart[k] = jStart[k - 1] + bj;
    }

    iStart[b] = i2 + 1;
    jStart[b] = j2 + 1;

    for (int biIdx = 0; biIdx < b; ++biIdx) {
        for (int bjIdx = 0; bjIdx < b; ++bjIdx) {
            #pragma omp task firstprivate(biIdx, bjIdx)
            p_simple_stencil_recursive_b_by_b(
                A, staticInfo, 
                iStart[biIdx], iStart[biIdx + 1] - 1,
                jStart[bjIdx], jStart[bjIdx + 1] - 1,
                b
            );
        }
        #pragma omp taskwait
    }
}

void p_simple_stencil_log(int** A, int** staticInfo, int n) {
    int blockSize = (int)(log2(n));
    if (blockSize < 1) blockSize = 1;
    int numBlocks = (n + blockSize - 1) / blockSize;

    for (int d = 0; d <= ((numBlocks - 1) << 1); ++d) {
        #pragma omp parallel for
        for (int bi = 0; bi < numBlocks; ++bi) {
            int bj = d - bi;
            if (bj < 0 || bj >= numBlocks) continue;

            int i1 = bi * blockSize;
            int i2 = (i1 + blockSize - 1 < n) ? (i1 + blockSize - 1) : (n - 1);

            int j1 = bj * blockSize;
            int j2 = (j1 + blockSize - 1 < n) ? (j1 + blockSize - 1) : (n - 1);

            for (int i = i1; i <= i2; ++i) {
                for (int j = j1; j <= j2; ++j) {
                    int up = (i > 0) ? A[i - 1][j] : 0;
                    int left = (j > 0) ? A[i][j - 1] : 0;
                    A[i][j] = up + left + staticInfo[i][j];
                }
            }
        }
    }
}

void test_p_simple_stencil(void) {
    int n = 1 << 2;
    printf("Matrix size: %dx%d\n", n, n);
    int** seqA = allocate_matrix(n, n);
    int** parA2 = allocate_matrix(n, n);
    int** parA3 = allocate_matrix(n, n);
    int** parAb = allocate_matrix(n, n);
    int** parAlog = allocate_matrix(n, n);
    int** staticInfo = allocate_matrix(n, n);
    int b = 4;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; j++) staticInfo[i][j] = (i + j) % 10;

    if (n <= 8) {
        printf("Static info matrix:\n");
        print_dynamic_matrix(staticInfo, n);
    }

    // Sequential
    double seqStart = omp_get_wtime();
    simple_stencil(seqA, staticInfo, n);
    double seqElapsed = omp_get_wtime() - seqStart;

    // Parallel 2x2
    double par2Elapsed;
    #pragma omp parallel
    {
        #pragma omp single
        {
            double t0 = omp_get_wtime();
            p_simple_stencil_recursive_2_by_2(parA2, staticInfo, 0, n - 1, 0, n - 1);
            par2Elapsed = omp_get_wtime() - t0;
        }
    }

    // Parallel 3x3
    double par3Elapsed;
    #pragma omp parallel
    {
        #pragma omp single
        {
            double t0 = omp_get_wtime();
            p_simple_stencil_recursive_3_by_3(parA3, staticInfo, 0, n - 1, 0, n - 1);
            par3Elapsed = omp_get_wtime() - t0;
        }
    }

    // Parallel bxb
    double parbElapsed;
    #pragma omp parallel
    {
        #pragma omp single
        {
            double t0 = omp_get_wtime();
            p_simple_stencil_recursive_b_by_b(parAb, staticInfo, 0, n - 1, 0, n - 1, b);
            parbElapsed = omp_get_wtime() - t0;
        }
    }

    // Parallel log-block wavefront
    double parlogElapsed = 0.0;
    double t0 = omp_get_wtime();
    p_simple_stencil_log(parAlog, staticInfo, n);
    parlogElapsed = omp_get_wtime() - t0;


    printf("Elapsed time (seq): %.6f seconds\n", seqElapsed);
    printf("Elapsed time (par 2 by 2): %.6f seconds\n", par2Elapsed);
    printf("Speedup (par2/seq): %.2fx\n", seqElapsed / par2Elapsed);
    printf("Elapsed time (par 3 by 3): %.6f seconds\n", par3Elapsed);
    printf("Speedup (par3/seq): %.2fx\n", seqElapsed / par3Elapsed);
    printf("Elapsed time (par b by b): %.6f seconds\n", parbElapsed);
    printf("Speedup (parb/seq): %.2fx\n", seqElapsed / parbElapsed);
    printf("Elapsed time (par log): %.6f seconds\n", parlogElapsed);
    printf("Speedup (parb/seq): %.2fx\n", seqElapsed / parlogElapsed);

    if (n <= 8) {
        printf("Result (seq):\n"); print_dynamic_matrix(seqA, n);
        printf("Result (par 2 by 2):\n"); print_dynamic_matrix(parA2, n);
        printf("Result (par 3 by 3):\n"); print_dynamic_matrix(parA3, n);
        printf("Result (par b by b):\n"); print_dynamic_matrix(parAb, n);
        printf("Result (par log ):\n"); print_dynamic_matrix(parAlog, n);
    }

    int correct = 1;
    for (int i = 0; i < n && correct; ++i)
        for (int j = 0; j < n; ++j)
            if (seqA[i][j] != parA2[i][j] || seqA[i][j] != parA3[i][j] 
                || seqA[i][j] != parAb[i][j] || seqA[i][j] != parAlog[i][j]) {
                correct = 0;
                break;
            }
    printf("Results match? %s\n", correct ? "Yes" : "No");

    free_matrix(seqA, n);
    free_matrix(parA2, n);
    free_matrix(parA3, n);
    free_matrix(parAb, n);
    free_matrix(parAlog, n);
    free_matrix(staticInfo, n);
}

#pragma endregion Multithreading a simple stencil calculation

#pragma region Randomized multithreaded algorithms

void p_randomized_quicksort(int* A, int p, int r) {
    /*
        Work: E[T_1] = O(n*lg(n))
        Span: E[T_{inf}] = O(lg(n))
        Parallelism: E[T_1] / E[T_{inf}] = O(n)
    */
    int cutoff = 1 << 7;
    if (r - p + 1 <= cutoff) {
        qsort(A + p, r - p + 1, sizeof(int), compare_ints);
        return;
    }

    if (p > r) return;
    int q = p_randomized_partition(A, p, r);
    #pragma omp parallel sections
    {
        #pragma omp section
        p_randomized_quicksort(A, p, q - 1);

        #pragma omp section
        p_randomized_quicksort(A, q + 1, r);
    }
}

int p_randomized_partition(int* A, int p, int r) {
    int i = random_int(p, r);
    int tmp = A[r];
    A[r] = A[i];
    A[i] = tmp;
    int x = A[r];
    int j = p - 1;

    for (int k = p; k < r; ++k) {
        if (A[k] > x) continue;
        ++j;
        tmp = A[j];
        A[j] = A[k];
        A[k] = tmp;
    }

    tmp = A[j + 1];
    A[j + 1] = A[r];
    A[r] = tmp;

    return j + 1;
}

void test_p_randomized_quicksort(void) {
    int n = 1 << 14;
    int* seqA = (int*)safe_malloc(n * sizeof(int));
    int* parA = (int*)safe_malloc(n * sizeof(int));

    for (int i = 0; i < n; ++i) {
        seqA[i] = random_int(1, 10000);
        parA[i] = seqA[i];
    }

    double seqStart = omp_get_wtime();
    qsort(seqA, n, sizeof(int), compare_ints);
    double seqEnd = omp_get_wtime();
    double seqTime = seqEnd - seqStart;

    double parStart = omp_get_wtime();
    #pragma omp parallel 
    {
        #pragma omp single
        {
            p_randomized_quicksort(parA, 0, n - 1);
        }
    }
    double parEnd = omp_get_wtime();
    double parTime = parEnd - parStart; 

    int correct = 1;
    for (int i = 0; i < n; ++i) {
        if (seqA[i] != parA[i]) {
            correct = 0;
            break;
        }
    }

    printf("Parallel randomized quicksort time: %.6f\n", parTime);
    printf("qsort time: %.6f\n", seqTime);
    printf("Speedup: %.2fx\n", seqTime / parTime);
    printf("Results match? %s\n", correct ? "Yes" : "No");

    safe_free(seqA);
    safe_free(parA);
}

#pragma endregion Randomized multithreaded algorithms

int main(void) {
    switch (TASK)
    {
        case 1: {
            // 26-1
            test_p_sum_arrays();
            break;
        }

        case 2: {
            // 26-2
            test_p_matrix_multiply_no_temp();
            break;
        }

        case 3: {
            // 26-3a
            test_p_lu_decomposition();
            break;
        }

        case 4: {
            // 26-3b
            test_p_lup_decomposition();
            break;
        }

        case 5: {
            // 26-3c
            test_p_lup_solve();
            break;
        }

        case 6: {
            // 26-3d
            test_p_cholesky_decomposition();
            break;
        }

        case 7: {
            // 26-4a
            test_p_reduce();
            break;
        }

        case 8: {
            // 26-4b-g
            test_p_scan();
            break;
        }

        case 9: {
            // 26-4h
            test_p_are_parentheses_balanced();
            break;
        }

        case 10: {
            // 26-5
            test_p_simple_stencil();
            break;
        }

        case 11: {
            // 26-6
            test_p_randomized_quicksort();
            break;
        }
        
        default:
            break;
    }

    return 0;
}
