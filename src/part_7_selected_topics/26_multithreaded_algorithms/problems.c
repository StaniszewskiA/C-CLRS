#include "part_7_selected_topics/26_multithreaded_algorithms/multithreaded_algorithms.h"

#define TASK 6

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
        Work: T_1 = Θ()
        Span: T_∞ = Θ()
        Parallelism: Θ()
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

int main(void) {
    switch (TASK)
    {
        case 1: {
            // 26.1
            test_p_sum_arrays();
            break;
        }

        case 2: {
            // 26.2
            test_p_matrix_multiply_no_temp();
            break;
        }

        case 3: {
            // 26.3a
            test_p_lu_decomposition();
            break;
        }

        case 4: {
            // 26.3b
            test_p_lup_decomposition();
            break;
        }

        case 5: {
            // 26.3c
            test_p_lup_solve();
            break;
        }

        case 6: {
            // 26.3d
            test_p_cholesky_decomposition();
            break;
        }
        
        default:
            break;
    }

    return 0;
}
