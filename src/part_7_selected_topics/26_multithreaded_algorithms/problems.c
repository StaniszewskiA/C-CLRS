#include "part_7_selected_topics/26_multithreaded_algorithms/multithreaded_algorithms.h"

#define TASK 2

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

    free(A);
    free(B);
    free(C1);
    free(C2);
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
        
        default:
            break;
    }

    return 0;
}