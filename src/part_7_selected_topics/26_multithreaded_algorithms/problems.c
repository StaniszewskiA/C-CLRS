#include "part_7_selected_topics/26_multithreaded_algorithms/multithreaded_algorithms.h"

#define TASK 1

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
        Work: T_1 = Θ()
        Span: T_{inf} = Θ()
        Parallelism: Θ()  
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

int main(void) {
    switch (TASK)
    {
        case 1: {
            // 
            test_p_sum_arrays();
            break;
        }
        
        default:
            break;
    }

    return 0;
}