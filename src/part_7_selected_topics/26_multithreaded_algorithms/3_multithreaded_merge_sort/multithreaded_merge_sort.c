#include "part_7_selected_topics/26_multithreaded_algorithms/multithreaded_algorithms.h"

static void merge(int* A, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));
    
    for (int i = 0; i < n1; ++i) L[i] = A[p + i];
    for (int j = 0; j < n2; ++j) R[j] = A[q + 1 + j];

    int i = 0;
    int j = 0;
    int k = p;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) A[k++] = L[i++];
        else A[k++] = R[j++];
    } 

    while (i < n1) A[k++] = L[i++];
    while (j < n2) A[k++] = R[j++];

    safe_free(L);
    safe_free(R);
}

void p_naive_merge_sort(int* A, int p, int r) {
    if (p >= r) return;
    int q = (p + r) / 2;
    
    #pragma omp task shared(A)
    p_naive_merge_sort(A, p, q);
    #pragma omp task shared(A)
    p_naive_merge_sort(A, q + 1, r);
    #pragma omp taskwait

    merge(A, p, q, r);
}

static int find_split_point(int* A, int p, int r, int x) {
    int low = p;
    int high = r + 1;

    while (low < high) {
        int mid = (low + high) / 2;
        if (x <= A[mid]) high = mid;
        else low = mid + 1;
    }

    return low;
}

static void p_merge_aux(
    int* A, 
    int p1, 
    int r1, 
    int p2, 
    int r2, 
    int* B, 
    int p3
) {
    if (p1 > r1 && p2 > r2) return;

    if (p1 > r1) {
        for (int i = p2; i <= r2; ++i)
            B[p3 + (i - p2)] = A[i];
        return;
    }

    if (p2 > r2) {
        for (int i = p1; i <= r1; ++i)
            B[p3 + (i - p1)] = A[i];
        return;
    }

    if ((r1 - p1) < (r2 - p2)) {
        SWAP_INT(p1, p2);
        SWAP_INT(r1, r2);
    }

    int q1 = (p1 + r1) / 2;
    int x = A[q1];
    int q2 = find_split_point(A, p2, r2, x);
    int q3 = p3 + (q1 - p1) + (q2 - p2);
    B[q3] = x;

    #pragma omp task shared(A, B)
    p_merge_aux(A, p1, q1 - 1, p2, q2 - 1, B, p3);
    #pragma omp task shared(A, B)
    p_merge_aux(A, q1 + 1, r1, q2, r2, B, q3 + 1);
    #pragma omp taskwait
}

void p_merge_sort(int* A, int p, int q, int r) {
    if (p >= r) return;
    int threshold = 32;
    if (r - p + 1 <= threshold) {
        quicksort(A, p, r);
        return;
    }
    int* B = (int*)safe_malloc((r + 1) * sizeof(int));
    #pragma omp parallel
    {
        #pragma omp single nowait
        {
            p_merge_sort(A, p, (p + q) / 2, q);
            p_merge_sort(A, q + 1, (q + 1 + r) / 2, r);
        }
    }
    p_merge_aux(A, p, q, q + 1, r, B, 0);
    for (int i = 0; i <= r - p; ++i) {
        A[p + i] = B[i];
    }
    safe_free(B);
}

void test_p_merge_sort(void) {
    int n = 1 << 12;
    int arr1[n];
    int arr2[n];

    for (int i = 0; i < n; ++i) {
        arr1[i] = random_int(0, 99);
        arr2[i] = arr1[i]; 
    }

    printf("Array length: %d\n", n);
    if (n <= 100) print_arr(arr1, n);

    double naiveStart = omp_get_wtime();
    p_naive_merge_sort(arr1, 0, n - 1);
    double naiveEnd = omp_get_wtime();
    double naiveTime = naiveEnd - naiveStart;
    if (n <= 100) {
        printf("Sorted by p_naive_merge_sort: ");
        print_arr(arr1, n);
    }
    printf("Is sorted: %s\n", is_sorted_asc(arr1, n) ? "Yes": "No");

    double optimizedStart = omp_get_wtime();
    p_merge_sort(arr2, 0, (n - 1) / 2, n - 1);
    double optimizedEnd = omp_get_wtime();
    double opptimizedTime = optimizedEnd - optimizedStart;
    if (n <= 100) {
        printf("Sorted by p_merge_sort: ");
        print_arr(arr2, n);
    }
    printf("Is sorted: %s\n", is_sorted_asc(arr2, n) ? "Yes": "No");

    printf("Naive time: %.6f\n", naiveTime);
    printf("Optimized(?) time: %.6f\n", opptimizedTime);
}

static median_res_t median_of_two_sorted_subarrays(
    int* A, 
    int p1, 
    int r1, 
    int p2, 
    int r2
) {
    int n1 = r1 - p1 + 1;
    int n2 = r2 - p2 + 1;
    int total = n1 + n2;
    int k = total / 2;
    median_res_t res;

    if (n1 == 0) {
        res.pos = p2 + k;
        res.arr = 2;
        return res;
    }

    if (n2 == 0) {
        res.pos = p1 + k;
        res.arr = 1;
        return res;
    }

    int low = 0;
    int high = n1;

    while (low <= high) {
        int cut1 = (low + high) / 2;
        int cut2 = k - cut1;

        if (cut2 < 0) {
            high = cut1 - 1;
            continue;
        }

        if (cut2 > n2) {
            low = cut1 + 1;
            continue;
        }

        int left1 = (cut1 == 0) ? INT_MIN : A[p1 + cut1 - 1];
        int left2 = (cut2 == 0) ? INT_MIN : A[p2 + cut2 - 1];
        int right1 = (cut1 == n1) ? INT_MAX : A[p1 + cut1];
        int right2 = (cut2 == n2) ? INT_MAX : A[p2 + cut2];

        if (left1 <= right2 && left2 <= right1) {
            if (left1 >= left2) {
                res.pos = p1 + cut1 - 1;
                res.arr = 1;
            } else {
                res.pos = p2 + cut2 - 1;
                res.arr = 2;
            }
            return res;
        } else if (left1 > right2) {
            high = cut1 - 1;
        } else {
            low = cut1 + 1;
        }
    }

    res.pos = -1;
    res.arr = -1;
    return res;
}

void p_median_merge(
    int* T,
    int p1,
    int r1,
    int p2,
    int r2,
    int* A,
    int p3
) {
    /*
        Work: T_1 = Θ(n)
        Span: T_{inf} = Θ(lg^2(n)) 
        Parallelism: Θ(n) / Θ(lg^2(n)) 
    */
    int n1 = r1 - p1 + 1;
    int n2 = r2 - p2 + 1;

    if (n1 < n2) {
        SWAP_INT(p1, p2);
        SWAP_INT(r1, r2);
        SWAP_INT(n1, n2);
    }

    if (n1 == 0) return;
    if (n2 == 0) {
        for (int i = 0; i < n1; ++i) A[p3 + i] = T[p1 + i];
        return;
    }

    median_res_t q = median_of_two_sorted_subarrays(T, p1, r1, p2, r2);

    if (q.arr == 1) {
        int q2 = find_split_point(T, p2, r2, T[q.pos]);
        int q3 = p3 + (q.pos - p1) + (q2 - p2);
        A[q3] = T[q.pos];

        #pragma omp task shared(T, A)
        p_median_merge(T, p1, q.pos - 1, p2, q2 - 1, A, p3);
        p_median_merge(T, q.pos + 1, r1, q2, r2, A, q3 + 1);
        #pragma omp taskwait
    } else {
        int q2 = find_split_point(T, p1, r1, T[q.pos]);
        int q3 = p3 + (q.pos - p2) + (q2 - p1);
        A[q3] = T[q.pos];

        #pragma omp task shared(T, A)
        p_median_merge(T, p1, q2 - 1, p2, q.pos - 1, A, p3);
        p_median_merge(T, q2, r1, q.pos + 1, r2, A, q3 + 1);
        #pragma omp taskwait
    }
}

void test_p_median_merge(void) {
    int n1 = 1 << 8;
    int n2 = 1 << 8;
    int total = n1 + n2;
    
    int* arr1 = (int*)safe_malloc(n1 * sizeof(int));
    int* arr2 = (int*)safe_malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; ++i) arr1[i] = random_int(1, 20);
    for (int i = 0; i < n2; ++i) arr2[i] = random_int(1, 20);

    qsort(arr1, n1, sizeof(int), compare_ints);
    qsort(arr2, n2, sizeof(int), compare_ints);
    
    if (n1 <= 32) {
        printf("Input array sizes:\n");
        printf("Array 1: ");
        print_arr(arr1, n1);
        printf("Array 2: ");
        print_arr(arr2, n2);
    }


    int* combined = (int*)safe_malloc(total * sizeof(int));
    int* res = (int*)safe_malloc(total * sizeof(int));

    for (int i = 0; i < n1; i++) combined[i] = arr1[i];
    for (int i = 0; i < n2; i++) combined[n1 + i] = arr2[i];

    #pragma omp parallel
    {
        #pragma omp single
        {
            p_median_merge(combined, 0, n1 - 1, n1, n1 + n2 - 1, res, 0);
        }
    }

    if (total <= 32) {
        printf("Result:  ");
        print_arr(res, total);
    }

    printf("Is sorted: %s\n", is_sorted_asc(res, total) ? "Yes" : "No");
    
    safe_free(arr1);
    safe_free(arr2);
    safe_free(combined);
    safe_free(res);
}

void p_partition(int* A, int n, int* res, int pivot, int* pivotIdx) {
    /*
        Work: T_1 = Θ(n)
        Span: T_{inf} = Θ(lg(n)) 
        Parallelism: Θ(n) / Θ(lg(n)) 
    */
    if (n == 1) {
        res[0] = A[0];
        *pivotIdx = (A[0] < pivot) ? 1 : 0;
        return;
    } else if (n == 0) {
        *pivotIdx = 0;
        return;
    }

    int numThreads = omp_get_max_threads();
    int chunkSize = (n + numThreads - 1) / numThreads;

    int* lessCnts = (int*)safe_malloc(numThreads * sizeof(int));
    int* equalCnts = (int*)safe_malloc(numThreads * sizeof(int));
    int* lessPrefixes = (int*)safe_malloc(numThreads * sizeof(int));
    int* equalPrefixes = (int*)safe_malloc(numThreads * sizeof(int));

    // Count elements
    #pragma omp parallel 
    {
        int threadId = omp_get_thread_num();
        int start = threadId * chunkSize;
        int end = (start + chunkSize > n) ? n : start + chunkSize;
        int less = 0;
        int equal = 0;

        for (int i = start; i < end; i++) {
            if (A[i] < pivot) less++;
            else if (A[i] == pivot) equal++;
        }

        lessCnts[threadId] = less;
        equalCnts[threadId] = equal;
    }

    // Compute prefix sums
    #pragma omp parallel for
    for (int i = 0; i < numThreads; i++) {
        lessPrefixes[i] = 0;
        equalPrefixes[i] = 0;
        for (int j = 0; j < i; j++) {
            lessPrefixes[i] += lessCnts[j];
            equalPrefixes[i] += equalCnts[j];
        }
    }


    int totalLess = lessPrefixes[numThreads - 1] + lessCnts[numThreads - 1];
    *pivotIdx = totalLess;

    // Place elements
    #pragma omp parallel
    {
        int threadId = omp_get_thread_num();
        int start = threadId * chunkSize;
        int end = (start + chunkSize > n) ? n : start + chunkSize;

        int lessPos = lessPrefixes[threadId];
        int equalPos = totalLess + equalPrefixes[threadId];
        int greaterPos = totalLess + equalPrefixes[threadId] + equalCnts[threadId];
        
        for (int i = start; i < end; i++) {
            if (A[i] < pivot) res[lessPos++] = A[i];
            else if (A[i] == pivot) res[equalPos++] = A[i];
            else res[greaterPos++] = A[i];
        }
    }

    safe_free(lessCnts);
    safe_free(equalCnts);
    safe_free(lessPrefixes);
    safe_free(equalPrefixes);
}

void test_p_partition(void) {
    int n = 1 << 3; 
    int* arr = (int*)safe_malloc(n * sizeof(int));
    int* res = (int*)safe_malloc(n * sizeof(int));

    for (int i = 0 ; i < n; i++) arr[i] = random_int(1, 20);

    printf("Input array size: %d\n", n);
    if (n <= 20) {
        printf("Input array: ");
        print_arr(arr, n);
    }

    int pivot = arr[n - 1];
    int pivotIdx;
    printf("Starting pivot: %d\n", pivot);
    #pragma omp parallel
    {
        #pragma omp single
        {
            p_partition(arr, n, res, pivot, &pivotIdx);
        }
    }

    if (n <= 20) {
        printf("Partitioned: ");
        print_arr(res, n);
        printf("Pivot index: %d\n", pivotIdx);
    }

    int correct = 1;
    for (int i = 0; i < pivotIdx; i++) {
        if (res[i] >= pivot) {
            correct = 0;
            break;
        }
    }

    for (int i = pivotIdx; i < n; i++) {
        if (res[i] < pivot) {
            correct = 0;
            break;
        }
    }

    printf("Is partition correct: %s\n", correct ? "Yes" : "No");

    safe_free(arr);
    safe_free(res);
}

void p_recursive_fft(complex_t* a, int n, complex_t* res) {
    /*
        Work: T_1 = Θ(n*lg(n)) (?) 
        Span: T_{inf} = Θ(lg(n)) 
        Parallelism: Θ(n)
    */
    if (n == 1) {
        res[0] = a[0];
        return;
    }

    // Precompute powers of W_n
    complex_t w_n = complex_exp(2.0 * M_PI / n);
    complex_t* wPowers = (complex_t*)safe_malloc((n / 2) * sizeof(complex_t));
    wPowers[0] = (complex_t){1.0, 0.0}; 
    for (int i = 1; i < n / 2; i++) wPowers[i] = complex_mul(wPowers[i - 1], w_n);

    complex_t* aEven = (complex_t*)safe_malloc((n/2) * sizeof(complex_t));
    complex_t* aOdd = (complex_t*)safe_malloc((n/2) * sizeof(complex_t));
    complex_t* yEven = (complex_t*)safe_malloc((n/2) * sizeof(complex_t));
    complex_t* yOdd = (complex_t*)safe_malloc((n/2) * sizeof(complex_t));

    #pragma omp parallel for
    for (int i = 0; i < n / 2; i++) {
        aEven[i] = a[2 * i];
        aOdd[i] = a[2 * i + 1];
    }

    #pragma omp task shared(aEven, yEven)
    p_recursive_fft(aEven, n / 2, yEven);

    #pragma omp task shared(aOdd, yOdd)
    p_recursive_fft(aOdd, n / 2, yOdd);

    #pragma omp taskwait

    #pragma omp parallel for
    for (int k = 0; k < n / 2; k++) {
        complex_t temp = complex_mul(wPowers[k], yOdd[k]);
        res[k] = complex_add(yEven[k], temp);
        res[k + n / 2] = complex_sub(yEven[k], temp);
    }

    free(aEven);
    free(aOdd);
    free(yEven);
    free(yOdd);
    free(wPowers);
}

void test_p_recursive_fft(void) {
    int n = 1 << 4;

    complex_t* input = (complex_t*)safe_malloc(n * sizeof(complex_t));
    complex_t* output = (complex_t*)safe_malloc(n * sizeof(complex_t));

    printf("Input signal length: %d\n", n);
    printf("Input signal:\n");
    for (int i = 0; i < n; i++) {
        input[i].real = cos(2.0 * M_PI * i / 8.0) + 0.5 * cos(2.0 * M_PI * i / 4.0);
        input[i].imag = cos(2.0 * M_PI * i / 4.0) + 0.5 * cos(2.0 * M_PI * i / 3.0);
        if (n <= 16) {
            printf("  x[%2d] = %6.3f + %6.3fi\n", i, input[i].real, input[i].imag);
        }
    }

    #pragma omp parallel
    {
        #pragma omp single
        {
            p_recursive_fft(input, n, output);
        }
    }

    printf("\nFFT Output:\n");
    for (int i = 0; i < n && n <= 16; i++) {
        printf("  X[%2d] = %6.3f + %6.3fi\n", i, output[i].real, output[i].imag);
    }

    safe_free(input);
    safe_free(output);
}
