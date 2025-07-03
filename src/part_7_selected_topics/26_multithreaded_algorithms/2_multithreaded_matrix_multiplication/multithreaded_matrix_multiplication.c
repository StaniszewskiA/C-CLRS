#include "part_7_selected_topics/26_multithreaded_algorithms/multithreaded_algorithms.h"

void p_matrix_multiply(int** A, int** B, int** C, int n) {
    /*
        Work: T_1 = Θ(n^3)
        Span: T_{inf} = Θ(lg(n)) + Θ(lg(n)) +Θ(n) = Θ(n) 
        Parallelism: Θ(n^3) / Θ(n) = Θ(n^2)
    */
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < n; ++i) {
        #pragma omp parallel for schedule(static)
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void s_matrix_multiply(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k) C[i][j] += A[i][k] * B[k][j];
}

int verify_matrix_multiplication(int** A, int** B, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int expected = 0;
            for (int k = 0; k < n; ++k) expected += A[i][k] * B[k][j];
            if (A[i][j] != expected) return 0;
        }
    }

    return 1;
}

void test_p_matrix_multiply(void) {
    int n = 1000;
    int** A = allocate_matrix(n, n);
    int** B = allocate_matrix(n, n);
    int** parC = allocate_matrix(n, n);
    int** seqC = allocate_matrix(n, n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            A[i][j] = i * n + j + 1;
            B[i][j] = (i + 1) * (j + 1);
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            parC[i][j] = 0;
            seqC[i][j] = 0;
        }
    }

    if (n <= 10) {
        pretty_print_matrix("Matrix A", A, n, n);
        pretty_print_matrix("Matrix B", B, n, n);
    }

    double startPar = omp_get_wtime();
    p_matrix_multiply(A, B, parC, n);
    double endPar = omp_get_wtime();
    double parTime = endPar - startPar;

    double startSeq = omp_get_wtime();
    s_matrix_multiply(A, B, seqC, n);
    double endSeq = omp_get_wtime();
    double seqTime = endSeq - startSeq;

    if (n <= 10) {
        pretty_print_matrix("C_parallel", parC, n, n);
        pretty_print_matrix("C_parallel", seqC, n, n);
    }

    int correct = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (parC[i][j] != seqC[i][j]) {
                correct = 0;
                break;
            }
        }
        if (!correct) break;
    } 

    if (correct) printf("The multiplication is correct.\n");
    else printf("The multiplication is not correct.\n");

    printf("Seq time: %.6f\n", seqTime);
    printf("Par time: %.6f\n", parTime);
    printf("Speed-up: %.2fx\n", seqTime / parTime);
    
    free_matrix(A, n);
    free_matrix(B, n);
    free_matrix(parC, n);
    free_matrix(seqC, n);
}

void p_matrix_multiply_recursive(int** A, int** B, int** C, int n) {
    /*
        Work: T_1 = 8*T_1(n / 2) + Θ(n^2) = Θ(n^3)
        Span: T_{inf} = T_{inf}(n / 2) + Θ(lg(n)) = Θ(lg^2(n))
        Parallelism: Θ(n^3) / Θ(lg^2(n))
    */
    if (n <= 32) {
        s_matrix_multiply(A, B, C, n);
        return;
    }
    
    if (n == 1) {
        C[0][0] += A[0][0] * B[0][0];
        return;
    }
    
    int** D = allocate_matrix(n, n);
    
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < n; ++i) {
        #pragma omp parallel for schedule(static)
        for (int j = 0; j < n; ++j) D[i][j] = 0;
    }

    int half = n / 2;

    int** A11 = allocate_matrix(half, half);
    int** A12 = allocate_matrix(half, half);
    int** A21 = allocate_matrix(half, half);
    int** A22 = allocate_matrix(half, half);
    
    int** B11 = allocate_matrix(half, half);
    int** B12 = allocate_matrix(half, half);
    int** B21 = allocate_matrix(half, half);
    int** B22 = allocate_matrix(half, half);
    
    int** C11 = allocate_matrix(half, half);
    int** C12 = allocate_matrix(half, half);
    int** C21 = allocate_matrix(half, half);
    int** C22 = allocate_matrix(half, half);
    
    int** D11 = allocate_matrix(half, half);
    int** D12 = allocate_matrix(half, half);
    int** D21 = allocate_matrix(half, half);
    int** D22 = allocate_matrix(half, half);

    get_submatrix(A, A11, 0, 0, half);
    get_submatrix(A, A12, 0, half, half);
    get_submatrix(A, A21, half, 0, half);
    get_submatrix(A, A22, half, half, half);
    
    get_submatrix(B, B11, 0, 0, half);
    get_submatrix(B, B12, 0, half, half);
    get_submatrix(B, B21, half, 0, half);
    get_submatrix(B, B22, half, half, half);
    
    get_submatrix(C, C11, 0, 0, half);
    get_submatrix(C, C12, 0, half, half);
    get_submatrix(C, C21, half, 0, half);
    get_submatrix(C, C22, half, half, half);
    
    get_submatrix(D, D11, 0, 0, half);
    get_submatrix(D, D12, 0, half, half);
    get_submatrix(D, D21, half, 0, half);
    get_submatrix(D, D22, half, half, half);

    #pragma omp parallel sections
    {
        #pragma omp section
        p_matrix_multiply_recursive(A11, B11, C11, half);
        
        #pragma omp section
        p_matrix_multiply_recursive(A11, B12, C12, half);
        
        #pragma omp section
        p_matrix_multiply_recursive(A21, B11, C21, half);
        
        #pragma omp section
        p_matrix_multiply_recursive(A21, B12, C22, half);
        
        #pragma omp section
        p_matrix_multiply_recursive(A12, B21, D11, half);
        
        #pragma omp section
        p_matrix_multiply_recursive(A12, B22, D12, half);
        
        #pragma omp section
        p_matrix_multiply_recursive(A22, B21, D21, half);
        
        #pragma omp section
        p_matrix_multiply_recursive(A22, B22, D22, half);
    }

    set_submatrix(C, C11, 0, 0, half);
    set_submatrix(C, C12, 0, half, half);
    set_submatrix(C, C21, half, 0, half);
    set_submatrix(C, C22, half, half, half);

    set_submatrix(D, D11, 0, 0, half);
    set_submatrix(D, D12, 0, half, half);
    set_submatrix(D, D21, half, 0, half);
    set_submatrix(D, D22, half, half, half);

    #pragma omp parallel for schedule(static)
    for (int i = 0; i < n; ++i) {
        #pragma omp parallel for schedule(static)
        for (int j = 0; j < n; ++j) C[i][j] += D[i][j];
    }

    free_matrix(A11, half);
    free_matrix(A12, half);
    free_matrix(A21, half);
    free_matrix(A22, half);
    
    free_matrix(B11, half);
    free_matrix(B12, half);
    free_matrix(B21, half);
    free_matrix(B22, half);
    
    free_matrix(C11, half);
    free_matrix(C12, half);
    free_matrix(C21, half);
    free_matrix(C22, half);
    
    free_matrix(D11, half);
    free_matrix(D12, half);
    free_matrix(D21, half);
    free_matrix(D22, half);
    
    free_matrix(D, n);
}

void test_p_matrix_multiply_recursive(void) {
    int n = 1 << 12; 
    printf("Input matrix size: %d\n", n);
    int** A = allocate_matrix(n, n);
    int** B = allocate_matrix(n, n);
    int** parC = allocate_matrix(n, n);
    int** seqC = allocate_matrix(n, n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            A[i][j] = i * n + j + 1;
            B[i][j] = (i + 1) * (j + 1);
            parC[i][j] = 0;
            seqC[i][j] = 0;
        }
    }

    if (n <= 10) {
        pretty_print_matrix("Matrix A", A, n, n);
        pretty_print_matrix("Matrix B", B, n, n);
    }

    double startPar = omp_get_wtime();
    p_matrix_multiply_recursive(A, B, parC, n);
    double endPar = omp_get_wtime();
    double parTime = endPar - startPar;

    double startSeq = omp_get_wtime();
    s_matrix_multiply(A, B, seqC, n);
    double endSeq = omp_get_wtime();
    double seqTime = endSeq - startSeq;

    if (n <= 10) {
        pretty_print_matrix("C_parallel", parC, n, n);
        pretty_print_matrix("C_parallel", seqC, n, n);
    }

    int correct = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (parC[i][j] != seqC[i][j]) {
                correct = 0;
                break;
            }
        }
        if (!correct) break;
    } 

    if (correct) printf("The multiplication is correct.\n");
    else printf("The multiplication is not correct.\n");

    printf("Seq time: %.6f\n", seqTime);
    printf("Par time: %.6f\n", parTime);
    printf("Speed-up: %.2fx\n", seqTime / parTime);
    
    free_matrix(A, n);
    free_matrix(B, n);
    free_matrix(parC, n);
    free_matrix(seqC, n);
}

void p_strassen_algorithm(int** A, int** B, int** C, int n) {
    /*
        Work: T_1 = Θ(n^{lg7})
        Span: T_{inf} = Θ(lg^2(n))
        Parallelism: Θ(n^{lg7}) / Θ(lg^2(n))
    */
    if (n <= 32) {
        s_matrix_multiply(A, B, C, n);
        return;
    }

    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];    
        return;
    }

    int half = n / 2;

    int** A11 = allocate_matrix(half, half);
    int** A12 = allocate_matrix(half, half);
    int** A21 = allocate_matrix(half, half);
    int** A22 = allocate_matrix(half, half);
    
    int** B11 = allocate_matrix(half, half);
    int** B12 = allocate_matrix(half, half);
    int** B21 = allocate_matrix(half, half);
    int** B22 = allocate_matrix(half, half);
    
    get_submatrix(A, A11, 0, 0, half);
    get_submatrix(A, A12, 0, half, half);
    get_submatrix(A, A21, half, 0, half);
    get_submatrix(A, A22, half, half, half);
    
    get_submatrix(B, B11, 0, 0, half);
    get_submatrix(B, B12, 0, half, half);
    get_submatrix(B, B21, half, 0, half);
    get_submatrix(B, B22, half, half, half);

    int** S1 = allocate_matrix(half, half);
    int** S2 = allocate_matrix(half, half);
    int** S3 = allocate_matrix(half, half);
    int** S4 = allocate_matrix(half, half);
    int** S5 = allocate_matrix(half, half);
    int** S6 = allocate_matrix(half, half);
    int** S7 = allocate_matrix(half, half);
    int** S8 = allocate_matrix(half, half);
    int** S9 = allocate_matrix(half, half);
    int** S10 = allocate_matrix(half, half);

    int** P1 = allocate_matrix(half, half);
    int** P2 = allocate_matrix(half, half);
    int** P3 = allocate_matrix(half, half);
    int** P4 = allocate_matrix(half, half);
    int** P5 = allocate_matrix(half, half);
    int** P6 = allocate_matrix(half, half);
    int** P7 = allocate_matrix(half, half);

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            for (int i = 0; i < half; ++i)
                for (int j = 0; j < half; ++j) S1[i][j] = B12[i][j] - B22[i][j];
        }

        #pragma omp section
        {
            for (int i = 0; i < half; ++i) 
                for (int j = 0; j < half; ++j) S2[i][j] = A11[i][j] + A12[i][j];
        }
        
        #pragma omp section
        {
            for (int i = 0; i < half; ++i) 
                for (int j = 0; j < half; ++j) S3[i][j] = A21[i][j] + A22[i][j];
        }
        
        #pragma omp section
        {
            for (int i = 0; i < half; ++i)
                for (int j = 0; j < half; ++j) S4[i][j] = B21[i][j] - B11[i][j];
        }
        
        #pragma omp section
        {
            for (int i = 0; i < half; ++i) 
                for (int j = 0; j < half; ++j) S5[i][j] = A11[i][j] + A22[i][j];
        }
        
        #pragma omp section
        {
            for (int i = 0; i < half; ++i) 
                for (int j = 0; j < half; ++j) S6[i][j] = B11[i][j] + B22[i][j];
        }
        
        #pragma omp section
        {
            for (int i = 0; i < half; ++i) 
                for (int j = 0; j < half; ++j) S7[i][j] = A12[i][j] - A22[i][j];
        }
        
        #pragma omp section
        {
            for (int i = 0; i < half; ++i) 
                for (int j = 0; j < half; ++j) S8[i][j] = B21[i][j] + B22[i][j];
        }
        
        #pragma omp section
        {
            for (int i = 0; i < half; ++i) 
                for (int j = 0; j < half; ++j) S9[i][j] = A11[i][j] - A21[i][j];
        }
        
        #pragma omp section
        {
            for (int i = 0; i < half; ++i) 
                for (int j = 0; j < half; ++j) S10[i][j] = B11[i][j] + B12[i][j];
        }
    }

    #pragma omp parallel sections
    {
        #pragma omp section
        p_strassen_algorithm(A11, S1, P1, half); 
        
        #pragma omp section
        p_strassen_algorithm(S2, B22, P2, half);   
        
        #pragma omp section
        p_strassen_algorithm(S3, B11, P3, half);  
        
        #pragma omp section
        p_strassen_algorithm(A22, S4, P4, half);    
        
        #pragma omp section
        p_strassen_algorithm(S5, S6, P5, half);    
        
        #pragma omp section
        p_strassen_algorithm(S7, S8, P6, half);    
        
        #pragma omp section
        p_strassen_algorithm(S9, S10, P7, half);   
    }

    #pragma omp parallel for schedule(static)
    for (int i = 0; i < half; ++i) {
        #pragma omp parallel for schedule(static)
        for (int j = 0; j < half; ++j) {
            C[i][j] = P5[i][j] + P4[i][j] - P2[i][j] + P6[i][j];
            C[i][j + half] = P1[i][j] + P2[i][j];
            C[i + half][j] = P3[i][j] + P4[i][j];
            C[i + half][j + half] = P5[i][j] + P1[i][j] - P3[i][j] - P7[i][j];
        }
    }

    free_matrix(A11, half);
    free_matrix(A12, half);
    free_matrix(A21, half);
    free_matrix(A22, half);
    
    free_matrix(B11, half);
    free_matrix(B12, half);
    free_matrix(B21, half);
    free_matrix(B22, half);
    
    free_matrix(S1, half);
    free_matrix(S2, half);
    free_matrix(S3, half);
    free_matrix(S4, half);
    free_matrix(S5, half);
    free_matrix(S6, half);
    free_matrix(S7, half);
    free_matrix(S8, half);
    free_matrix(S9, half);
    free_matrix(S10, half);
    
    free_matrix(P1, half);
    free_matrix(P2, half);
    free_matrix(P3, half);
    free_matrix(P4, half);
    free_matrix(P5, half);
    free_matrix(P6, half);
    free_matrix(P7, half);
}

void test_p_strassen_algorithm(void) {
    int n = 1 << 7; 
    printf("Input matrix size: %d\n", n);
    int** A = allocate_matrix(n, n);
    int** B = allocate_matrix(n, n);
    int** parC = allocate_matrix(n, n);
    int** seqC = allocate_matrix(n, n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            A[i][j] = i * n + j + 1;
            B[i][j] = (i + 1) * (j + 1);
            parC[i][j] = 0;
            seqC[i][j] = 0;
        }
    }

    if (n <= 10) {
        pretty_print_matrix("Matrix A", A, n, n);
        pretty_print_matrix("Matrix B", B, n, n);
    }

    double startPar = omp_get_wtime();
    p_strassen_algorithm(A, B, parC, n);
    double endPar = omp_get_wtime();
    double parTime = endPar - startPar;

    double startSeq = omp_get_wtime();
    s_matrix_multiply(A, B, seqC, n);
    double endSeq = omp_get_wtime();
    double seqTime = endSeq - startSeq;

    if (n <= 10) {
        pretty_print_matrix("C_parallel", parC, n, n);
        pretty_print_matrix("C_parallel", seqC, n, n);
    }

    int correct = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (parC[i][j] != seqC[i][j]) {
                correct = 0;
                break;
            }
        }
        if (!correct) break;
    } 

    if (correct) printf("The multiplication is correct.\n");
    else printf("The multiplication is not correct.\n");

    printf("Seq time: %.6f\n", seqTime);
    printf("Par time: %.6f\n", parTime);
    printf("Speed-up: %.2fx\n", seqTime / parTime);
    
    free_matrix(A, n);
    free_matrix(B, n);
    free_matrix(parC, n);
    free_matrix(seqC, n);
}

void test_all_matrix_multiplication_methods(void) {
    int n = 1 << 12; 
    const char* testTitle = "Testing all matrix multiplication methods with size";
    print_separator(testTitle);
    printf("Input matrix size: %d\n", n);
    
    int** A = allocate_matrix(n, n);
    int** B = allocate_matrix(n, n);
    int** seqC = allocate_matrix(n, n);
    int** naiveC = allocate_matrix(n, n);
    int** recursiveC = allocate_matrix(n, n);
    int** strassenC = allocate_matrix(n, n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            A[i][j] = i * n + j + 1;
            B[i][j] = (i + 1) * (j + 1);
            seqC[i][j] = 0;
            naiveC[i][j] = 0;
            recursiveC[i][j] = 0;
            strassenC[i][j] = 0;
        }
    }

    if (n <= 10) {
        pretty_print_matrix("Matrix A", A, n, n);
        pretty_print_matrix("Matrix B", B, n, n);
    }


    printf("\n1. Sequential Matrix Multiplication:\n");
    double startSeq = omp_get_wtime();
    s_matrix_multiply(A, B, seqC, n);
    double endSeq = omp_get_wtime();
    double seqTime = endSeq - startSeq;
    printf("   Time: %.6f seconds\n", seqTime);
    
    if (n <= 10) {
        pretty_print_matrix("   Result", seqC, n, n);
    }

    printf("\n2. Naive Parallel Matrix Multiplication:\n");
    double startNaive = omp_get_wtime();
    p_matrix_multiply(A, B, naiveC, n);
    double endNaive = omp_get_wtime();
    double naiveTime = endNaive - startNaive;
    printf("   Time: %.6f seconds\n", naiveTime);
    printf("   Speed-up: %.2fx\n", seqTime / naiveTime);
    
    if (n <= 10) {
        pretty_print_matrix("   Result", naiveC, n, n);
    }

    printf("\n3. Recursive Parallel Matrix Multiplication:\n");
    double startRecursive = omp_get_wtime();
    p_matrix_multiply_recursive(A, B, recursiveC, n);
    double endRecursive = omp_get_wtime();
    double recursiveTime = endRecursive - startRecursive;
    printf("   Time: %.6f seconds\n", recursiveTime);
    printf("   Speed-up: %.2fx\n", seqTime / recursiveTime);
    
    if (n <= 10) {
        pretty_print_matrix("   Result", recursiveC, n, n);
    }

    printf("\n4. Strassen Parallel Matrix Multiplication:\n");
    double startStrassen = omp_get_wtime();
    p_strassen_algorithm(A, B, strassenC, n);
    double endStrassen = omp_get_wtime();
    double strassenTime = endStrassen - startStrassen;
    printf("   Time: %.6f seconds\n", strassenTime);
    printf("   Speed-up: %.2fx\n", seqTime / strassenTime);
    
    if (n <= 10) {
        pretty_print_matrix("   Result", strassenC, n, n);
    }

    printf("\n5. Correctness Verification:\n");
    int naiveCorrect = 1, recursiveCorrect = 1, strassenCorrect = 1;
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (naiveC[i][j] != seqC[i][j]) naiveCorrect = 0;
            if (recursiveC[i][j] != seqC[i][j]) recursiveCorrect = 0;
            if (strassenC[i][j] != seqC[i][j]) strassenCorrect = 0;
        }
    }
    
    printf("   Naive Parallel: %s\n", naiveCorrect ? "correct" : "Incorrect");
    printf("   Recursive Parallel: %s\n", recursiveCorrect ? "correct" : "Incorrect");
    printf("   Strassen Parallel: %s\n", strassenCorrect ? "correct" : "Incorrect");


    printf("\n6. Performance Summary:\n");
    printf("   Method           | Time (s) | Speed-up | Status\n");
    printf("   -----------------|----------|----------|--------\n");
    printf("   Sequential       | %8.6f | %8.2fx | Baseline\n", seqTime, 1.0);
    printf("   Naive Parallel   | %8.6f | %8.2fx | %s\n", 
           naiveTime, seqTime/naiveTime, naiveCorrect ? "correct" : "Incorrect");
    printf("   Recursive Parallel| %8.6f | %8.2fx | %s\n", 
           recursiveTime, seqTime/recursiveTime, recursiveCorrect ? "correct" : "Incorrect");
    printf("   Strassen Parallel| %8.6f | %8.2fx | %s\n", 
           strassenTime, seqTime/strassenTime, strassenCorrect ? "correct" : "Incorrect");

    free_matrix(A, n);
    free_matrix(B, n);
    free_matrix(seqC, n);
    free_matrix(naiveC, n);
    free_matrix(recursiveC, n);
    free_matrix(strassenC, n);
}

static int matrix_mult_subloop(
    int** A,
    int** B,
    int i,
    int j,
    int k,
    int kPrime
) {
    if (k == kPrime) {
        return A[i][k] * B[k][j];
    } else if (kPrime - k + 1 <= 32) {
        int sum = 0;
        for (int kk = k; kk <= kPrime; ++kk) sum += A[i][kk] * B[kk][j];
        return sum;
    } else {
        int mid = (k + kPrime) / 2;
        int leftHalf;
        int rightHalf;

        #pragma omp task shared(leftHalf)
        {
            leftHalf = matrix_mult_subloop(A, B, i, j, k, mid);
        }

        rightHalf = matrix_mult_subloop(A, B, i, j, mid + 1, kPrime);
        #pragma omp taskwait

        return leftHalf + rightHalf;
    }
}

void p_fast_matrix_multiply(int** A, int** B, int** C, int n) {
    /*
        Work: T_1 = Θ(n^3)
        Span: T_{inf} = Θ(lg(n))
        Parallelism: Θ(n^3) / Θ(lg(n))
    */
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < n; ++i) {
        #pragma omp parallel for schedule(static)
        for (int j = 0; j < n; ++j) 
            C[i][j] = matrix_mult_subloop(A, B, i, j, 0, n - 1);
    }
}

void test_p_fast_matrix_multiply(void) {
    int n = 1 << 10;
    printf("Input matrix size: %d\n", n);
    int** A = allocate_matrix(n, n);
    int** B = allocate_matrix(n, n);
    int** parC = allocate_matrix(n, n);
    int** seqC = allocate_matrix(n, n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            A[i][j] = i * n + j + 1;
            B[i][j] = (i + 1) * (j + 1);
            parC[i][j] = 0;
            seqC[i][j] = 0;
        }
    }

    if (n <= 10) {
        pretty_print_matrix("Matrix A", A, n, n);
        pretty_print_matrix("Matrix B", B, n, n);
    }

    double startPar = omp_get_wtime();
    p_fast_matrix_multiply(A, B, parC, n);
    double endPar = omp_get_wtime();
    double parTime = endPar - startPar;

    double startSeq = omp_get_wtime();
    s_matrix_multiply(A, B, seqC, n);
    double endSeq = omp_get_wtime();
    double seqTime = endSeq - startSeq;

    if (n <= 10) {
        pretty_print_matrix("C_parallel", parC, n, n);
        pretty_print_matrix("C_parallel", seqC, n, n);
    }

    int correct = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (parC[i][j] != seqC[i][j]) {
                correct = 0;
                break;
            }
        }
        if (!correct) break;
    } 

    if (correct) printf("The multiplication is correct.\n");
    else printf("The multiplication is not correct.\n");

    printf("Seq time: %.6f\n", seqTime);
    printf("Par time: %.6f\n", parTime);
    printf("Speed-up: %.2fx\n", seqTime / parTime);
    
    free_matrix(A, n);
    free_matrix(B, n);
    free_matrix(parC, n);
    free_matrix(seqC, n);
}

void p_gen_matrix_multiply(int** A, int** B, int** C, int p, int q, int r) {
    /*
        Work: T_1 = Θ(pqr)
        Span: T_{inf} = Θ(lg(pqr))
        Parallelism: Θ(pqr) / Θ(lg(pqr))
    */
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < p; ++i) {
        #pragma omp parallel for schedule(static)
        for (int j = 0; j < r; ++j) {
            C[i][j] = matrix_mult_subloop(A, B, i, j, 0, q - 1);
        }
    }
}

void test_p_get_matrix_multiply(void) {
    int p = 1 << 11;
    int q = 1 << 12;
    int r = 1 << 13;

    printf("Matrix A size: %dx%d\n", p, q);
    printf("Matrix B size: %dx%d\n", q, r);
    printf("Expected matrix C size: %dx%d\n", p, r);

    int** A = allocate_matrix(p, q);
    int** B = allocate_matrix(q, r);
    int** parC = allocate_matrix(p, r);
    int** seqC = allocate_matrix(p, r);

    for (int i = 0; i < p; ++i)
        for (int j = 0; j < q; ++j) A[i][j] = i * q + j + 1;

    for (int i = 0; i < q; ++i)
        for (int j = 0; j < r; ++j) B[i][j] = i * r + j + 1;

    for (int i = 0; i < p; ++i) {
        for (int j = 0; j < r; ++j) {
            parC[i][j] = 0;
            seqC[i][j] = 0;
        }
    }

    if (p <= 10 && q <= 10 && r <= 10) {
        pretty_print_matrix("Matrix A", A, p, q);
        pretty_print_matrix("Matrix B", B, q, r);
    }

    double startPar = omp_get_wtime();
    p_gen_matrix_multiply(A, B, parC, p, q, r);
    double endPar = omp_get_wtime();
    double parTime = endPar - startPar;

    double startSeq = omp_get_wtime();
    for (int i = 0; i < p; ++i)
        for (int j = 0; j < r; ++j)
            for (int k = 0; k < q; ++k) seqC[i][j] += A[i][k] * B[k][j];
    double endSeq = omp_get_wtime();
    double seqTime = endSeq - startSeq;

    if (p <= 10 && q <= 10 && r <= 10) {
        printf("C_parallel (%dx%d):\n", p, r);
        for (int i = 0; i < p; ++i) {
            for (int j = 0; j < r; ++j) {
                printf("%d ", parC[i][j]);
            }
            printf("\n");
        }
        printf("C_sequential (%dx%d):\n", p, r);
        for (int i = 0; i < p; ++i) {
            for (int j = 0; j < r; ++j) {
                printf("%d ", seqC[i][j]);
            }
            printf("\n");
        }
    }

    int correct = 1;
    for (int i = 0; i < p; ++i) {
        for (int j = 0; j < r; ++j) {
            if (parC[i][j] != seqC[i][j]) {
                correct = 0;
                break;
            }
        }
        if (!correct) break;
    } 

    if (correct) printf("The multiplication is correct.\n");
    else printf("The multiplication is not correct.\n");

    printf("Seq time: %.6f\n", seqTime);
    printf("Par time: %.6f\n", parTime);
    printf("Speed-up: %.2fx\n", seqTime / parTime);

    free_matrix(A, p);
    free_matrix(B, q);
    free_matrix(parC, p);
    free_matrix(seqC, p);
}

void p_floyd_warshall(int** W, int** D, int n) {
    /*
        Work: T_1 = Θ(n^3)
        Span: T_{inf} = Θ(n*lg(n))
        Parallelism: Θ(n^2) / Θ(lg(n))
    */
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < n; ++i) {
        #pragma omp parallel for schedule(static)
        for (int j = 0; j < n; ++j) D[i][j] = W[i][j];
    }

    for (int k = 0; k < n; ++k) {
        #pragma omp parallel for schedule(static)
        for (int i = 0; i < n; ++i) {
            #pragma omp parallel for schedule(static)
            for (int j = 0; j < n; ++j) {
                if (D[i][k] == INF || D[k][j] == INF) continue;
                int newDist = D[i][k] + D[k][j];
                if (newDist < D[i][j]) D[i][j] = newDist;
            }
        }
    }
}

void test_p_floyd_warshall(void) {
    int n = 1 << 13;
    printf("Number of vertices: %d\n", n);

    int** W = allocate_matrix(n, n);
    int** parD = allocate_matrix(n, n);
    int** seqD = allocate_matrix(n, n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) W[i][j] = 0;
            else W[i][j] = INF;
        }
    }

    for (int i = 0; i < n - 1; ++i) {
        W[i][i + 1] = 1;
        W[i + 1][i] = 1;
    }

    for (int i = 0; i < n * n; ++i) {
        int u = rand() % n;
        int v = rand() % n;
        if (u != v) W[u][v] = rand() % 10 + 1;
    }

    if (n <= 10) {
        printf("Weight matrix W:\n");
        for (int i = 0; i < n; ++i) {
            printf("[");
            for (int j = 0; j < n; ++j) {
                if (W[i][j] == INF) {
                    printf("INF ");
                } else {
                    printf("%3d ", W[i][j]);
                }
            }
            printf("]\n");
        }
    }

    double startPar = omp_get_wtime();
    p_floyd_warshall(W, parD, n);
    double endPar = omp_get_wtime();
    double parTime = endPar - startPar;

    double startSeq = omp_get_wtime();

    for (int i = 0; i < n; ++i) 
        for (int j = 0; j < n; ++j) seqD[i][j] = W[i][j];

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (seqD[i][k] == INF || seqD[k][j] == INF) continue;
                int newDist = seqD[i][k] + seqD[k][j];
                if (newDist < seqD[i][j]) seqD[i][j] = newDist;
            }
        }
    }

    double endSeq = omp_get_wtime();
    double seqTime = endSeq - startSeq;

    if (n <= 10) {
        printf("Result matrix D (parallel):\n");
        for (int i = 0; i < n; ++i) {
            printf("[");
            for (int j = 0; j < n; ++j) {
                if (parD[i][j] == INF) {
                    printf("INF ");
                } else {
                    printf("%3d ", parD[i][j]);
                }
            }
            printf("]\n");
        }
    }

    int correct = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (parD[i][j] != seqD[i][j]) {
                correct = 0;
                break;
            }
        }
        if (!correct) break;
    }
    
    if (correct) printf("The Floyd-Warshall algorithm is correct.\n");
    else printf("The Floyd-Warshall algorithm is not correct.\n");
    
    printf("Seq time: %.6f\n", seqTime);
    printf("Par time: %.6f\n", parTime);
    printf("Speed-up: %.2fx\n", seqTime / parTime);
    
}
