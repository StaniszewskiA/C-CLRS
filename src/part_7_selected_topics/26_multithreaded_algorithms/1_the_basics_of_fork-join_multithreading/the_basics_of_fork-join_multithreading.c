#include "part_7_selected_topics/26_multithreaded_algorithms/multithreaded_algorithms.h"

pthread_mutex_t threadCntMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t spawnedThreadsMutex = PTHREAD_MUTEX_INITIALIZER;

unsigned int activeThreads = 1;
unsigned int spawnedThreads = 0;

int try_spawn_thread() {
    pthread_mutex_lock(&threadCntMutex);
    int allowed = 1;

    if (activeThreads > THREAD_LIMIT) {
        allowed = 0;
        printf("Tried to exceed the thread limit: %d\n",
            THREAD_LIMIT);
    }
    else activeThreads++;

    pthread_mutex_unlock(&threadCntMutex);
    return allowed;
}

void release_thread_slot() {
    pthread_mutex_lock(&threadCntMutex);
    activeThreads--;
    pthread_mutex_unlock(&threadCntMutex);
}

void* p_fib_thread(void* arg) {
    fib_args_t* args = (fib_args_t*)arg;
    int n = args->n;

    printf("Thread id: %lu, n = %d\n", (unsigned long)pthread_self(), n);

    if (n <= 1) {
        args->res = n;
        return NULL;
    }

    if (n <= SEQ_THRESHOLD) {
        fib_args_t xArgs = { .n = n - 1 };
        fib_args_t yArgs = { .n = n - 2 };
        p_fib_thread(&xArgs);
        p_fib_thread(&yArgs);
        args->res = xArgs.res + yArgs.res;
        return NULL;
    }

    fib_args_t* xArgs = safe_malloc(sizeof(fib_args_t));
    xArgs->n = n - 1;

    pthread_t xThread;
    int spawn = try_spawn_thread();

    if (spawn) {
        pthread_create(&xThread, NULL, p_fib_thread, xArgs);
        pthread_mutex_lock(&spawnedThreadsMutex);
        spawnedThreads++;
        pthread_mutex_unlock(&spawnedThreadsMutex);
    }
    else p_fib_thread(xArgs);

    fib_args_t yArgs = { .n = n - 2 };
    p_fib_thread(&yArgs);

    if (spawn) {
        pthread_join(xThread, NULL);
        release_thread_slot();
    }

    args->res = xArgs->res + yArgs.res;
    safe_free(xArgs);

    return NULL;
}

int p_fib(int n) {
    fib_args_t args = { .n = n };
    p_fib_thread(&args);
    return args.res;
}

void test_p_fib(void) {
    int n = 5;
    clock_t start = clock();
    int res = p_fib(n);
    clock_t end = clock();
    float elapsed = (float)(end - start) / CLOCKS_PER_SEC;
    printf("P-FIB(%d) = %d\n", n, res);
    printf("Elapsed time: %.2f seconds\n", elapsed);
    printf("Spawned threads: %d\n", spawnedThreads);
}

void p_mat_vec(int** A, int* x, int* y, int n) {
    #pragma omp parallel for num_threads(THREAD_LIMIT)
    for (int i = 0; i < n; ++i) {
        int sum = 0;
        for (int j = 0; j < n; ++j) {
            sum += A[i][j] * x[j];
        }
        y[i] = sum;
    }
}

void test_p_mat_vec(void) {
    int n = 10000;
    int** A = allocate_matrix(n, n);
    int* x = safe_malloc(n * sizeof(int));
    int* y = safe_malloc(n * sizeof(int));

    for (int i = 0; i < n; ++i) {
        x[i] = i + 1;
        y[i] = 0;
        for (int j = 0; j < n; ++j) A[i][j] = (i + 1) * (j + 1);
    }

    double start = omp_get_wtime();
    p_mat_vec(A, x, y, n);
    double end = omp_get_wtime();
    double elapsed = end - start;

    printf("Elapsed time: %.4f seconds\n", elapsed);
    free_matrix(A, n);
    safe_free(x);
    safe_free(y);
}

void p_mat_vec_recursive(int** A, int* x, int* y, int n, int i, int iPrime) {
    if (i > iPrime) return;
    if (i == iPrime) {
        int sum = 0;
        for (int j = 0; j < n; ++j)
            sum += A[i][j] * x[j];
        y[i] = sum;
    } else {
        int mid = (i + iPrime) / 2;
        #pragma omp task shared(A, x, y)
        p_mat_vec_recursive(A, x, y, n, i, mid);
        p_mat_vec_recursive(A, x, y, n, mid + 1, iPrime);
        #pragma omp taskwait
    }
}

void test_p_mat_vec_recursive(void) {
    int n = 10000;
    int** A = allocate_matrix(n, n);
    int* x = safe_malloc(n * sizeof(int));
    int* y = safe_malloc(n * sizeof(int));

    for (int i = 0; i < n; ++i) {
        x[i] = i + 1;
        y[i] = 0;
        for (int j = 0; j < n; ++j) A[i][j] = (i + 1) * (j + 1);
    }

    double start = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp single
        p_mat_vec_recursive(A, x, y, n, 0, n - 1);
    }

    double end = omp_get_wtime();
    double elapsed = end - start;

    printf("Elapsed time: %.4f seconds\n", elapsed);
    free_matrix(A, n);
    safe_free(x);
    safe_free(y);
}

void race_example(void) {
    int x = 0;
    int n = 1000;
    #pragma omp parallel for shared(x)
    for (int i = 0; i < n; ++i) x++;
    printf("x = %d\n", x);
}

void test_race_example(void) {
    int n = 10;
    for (int i = 0; i < n; ++i) race_example();
}

void p_mat_vec_wrong(int** A, int* x, int* y, int n) {
    #pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        #pragma omp parallel for
        for (int j = 1; j < n; ++j) y[i] += A[i][j] * x[j];
    }
}

void test_p_mat_vec_wrong(void) {
    int n = 8;
    int** A = allocate_matrix(n, n);
    int* x = safe_malloc(n * sizeof(int));
    int* yWrong = safe_calloc(n, sizeof(int));
    int* yCorrect = safe_calloc(n, sizeof(int));

    for (int i = 0; i < n; ++i) {
        x[i] = i + 1;
        for (int j = 0; j < n; ++j) {
            A[i][j] = (i + 1) * (j + 1);
        }
    }

    p_mat_vec_wrong(A, x, yWrong, n);
    p_mat_vec(A, x, yCorrect, n);

    printf("P-MAT-VEC-WRONG result:   y = [");
    for (int i = 0; i < n; ++i) printf("%6d", yWrong[i]);
    printf(" ]^T\n");
    printf("P-MAT-VEC result: y = [");
    for (int i = 0; i < n; ++i) printf("%6d", yCorrect[i]);
    printf(" ]^T\n");

    free_matrix(A, n);
    safe_free(x);
    safe_free(yWrong);
    safe_free(yCorrect);
}

int sum_row_dc(int* row, int* x, int left, int right) {
    if (left == right) return row[left] * x[left];
    int mid = (left + right) / 2;
    int leftSum = 0;
    int rightSum = 0;

    #pragma omp task shared(leftSum)
    leftSum = sum_row_dc(row, x, left, mid);

    #pragma omp task shared(rightSum)
    rightSum = sum_row_dc(row, x, mid + 1, right);

    #pragma omp taskwait
    return leftSum + rightSum;
}

void p_mat_vec_dc(int** A, int* x, int* y, int n) {
    #pragma omp parallel
    for (int i = 0; i < n; ++i) {
        #pragma omp single
        y[i] = sum_row_dc(A[i], x, 0, n - 1);
    }
}

void test_p_mat_vec_dc(void) {
    int n = 4;
    int** A = allocate_matrix(n, n);
    int* x = safe_malloc(n * sizeof(int));
    int* yPar = safe_calloc(n, sizeof(int));
    int* ySeq = safe_calloc(n, sizeof(int));

    for (int i = 0; i < n; ++i) {
        x[i] = i + 1;
        for (int j = 0; j < n; ++j) A[i][j] = (i + 1) * (j + 1);
    }

    pretty_print_matrix("Input matrix", A, n);

    printf("Input vector: [");
    for (int i = 0; i < n; ++i) printf("%3d", x[i]);
    printf("]^T\n");

    // Seq for comparison
    for (int i = 0; i < n; ++i) {
        int sum = 0;
        for (int j = 0; j < n; ++j) sum += A[i][j] * x[j];
        ySeq[i] = sum;
    }

    p_mat_vec_dc(A, x, yPar, n);

    printf("Sequential result:     y = [");
    for (int i = 0; i < n; ++i) printf("%3d ", ySeq[i]);
    printf(" ]^T\n");

    printf("Parallel result:     y = [");
    for (int i = 0; i < n; ++i) printf("%3d ", yPar[i]);
    printf(" ]^T\n");

    free_matrix(A, n);
    safe_free(x);
    safe_free(yPar);
    safe_free(ySeq);
}

static int verify_transposition(int** A, int** B, int n) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (A[i][j] != B[j][i]) return 0;
    return 1;
}

void p_transpose(int** A, int n) {
    /*
        Work: T_1 = Θ(n^2)
        Span: T_{inf} = Θ(lg(n)) + Θ(lg(n)) + Θ(1) = Θ(lg(n))
        Parallelism: T_1 / T_{inf} = Θ(n^2/lg(n))
    */
    #pragma omp parallel
    {
        #pragma omp for schedule(static)
        for (int j = 1; j < n; ++j) {
            for (int i = 0; i < j; ++i) {
                SWAP_INT(A[i][j], A[j][i]);
            }
        }
    }
}

void test_p_transpose(void) {
    int n = 4;
    int** A = allocate_matrix(n, n);
    int** refA = allocate_matrix(n, n);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) A[i][j] = refA[i][j] = i * n + j + 1;
    
    pretty_print_matrix("Input matrix", A, n);
    pretty_print_matrix("Reference matrix", refA, n);

    p_transpose(A, n);

    pretty_print_matrix("Transposed matrix", A, n);

    int ok = verify_transposition(A, refA, n);
    if (ok) printf("Transposition is correct.\n");
    else printf("Transposition failed.\n");

    free_matrix(A, n);
    free_matrix(refA, n);
}
