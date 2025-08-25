#include "../include/common.h"

int compare(const void *a, const void *b) {
    return (*(char*)a - *(char*)b);
}

int min_of_three(int a, int b, int c) {
    if (a <= b && a <= c) return a;
    else if (b <= a && b <= c) return b;
    else return c;
}

int compare_ints(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// Memory allocation
void* safe_malloc(size_t size) {
    if (size == 0) return NULL;

    void* ptr = malloc(size);
    if (!ptr) {
        fprintf(stderr, "Memory allocation failed for %zu bytes\n", size);
        exit(EXIT_FAILURE);
    }

    return ptr;
}

void* safe_calloc(size_t num, size_t size) {
    if (num == 0 || size == 0) return NULL;

    void* ptr = calloc(num, size);
    if (!ptr) {
        fprintf(stderr, "Memory allocation failed for %zu elements of %zu bytes each\n", num, size);
        exit(EXIT_FAILURE);
    }

    return ptr;
}

void* safe_realloc(void* ptr, size_t size) {
    if (size == 0) {
        safe_free(ptr);
        return NULL;
    }

    void* newPtr = realloc(ptr, size);

    if (!newPtr) {
        fprintf(stderr, "Memory reallocation failed for %zu bytes\n", size);
        fprintf(stderr, "Original pointer remains valid.\n");
        exit(EXIT_FAILURE);
    }

    return newPtr; 
}

void safe_free(void* ptr) {
    if (ptr != NULL) free(ptr);
}

// Other
void print_separator(const char* title) {
    const int width = 50;
    
    printf("\n");

    for (int i = 0; i < width; i++) printf("=");
    printf("\n");

    if (title == NULL) return;

    int titlenLen = (int)strlen(title);
    int padding = (width - titlenLen) / 2;

    for (int i = 0; i < padding; i++) printf(" ");
    printf("%s\n", title);

    for (int i = 0; i < width; i++) printf("=");
    printf("\n");
}

void print_error(const char* msg) {
    if (!msg) {
        fprintf(stderr, "No error msg provided\n");
        return;
    }

    time_t now;
    struct tm* timeInfo;
    char timestamp[20];

    time(&now);
    timeInfo = localtime(&now);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeInfo);
    
    fprintf(stderr, "[%s] ERROR: %s\n", timestamp, msg);
}

double get_time_ms(void) {
    clock_t currTime = clock();

    if (currTime == (clock_t)-1) {
        print_error("Failed to get current time");
        return -1.0;
    }

    return (double)currTime / CLOCKS_PER_SEC * 1000.0;
}

int random_int(int min, int max) {
    if (min > max) {
        print_error("random_int: min cannot be greater than max");
        return min;
    }

    static int seedInitialized = 0;
    if (!seedInitialized) {
        srand((unsigned int)time(NULL));
        seedInitialized = 1;
    }

    int range = max - min + 1;
    return min + (rand() % range);
}

void print_arr(int arr[], int N) {
    printf("[");
    for (int i = 0; i < N; i++) {
        printf("%d", arr[i]);
        if (i < N - 1) printf(" ");
    }
    printf("]\n");
}

void print_arr_slice(int arr[], int left, int right)
{
    printf("Array slice: ");
    for (int i = left; i <= right; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void print_matrix(int matrix[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void print_arr_double(double arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%.2f ", arr[i]);
    }
    printf("\n");
}

void print_arr_float(float A[]) {
    for (int i = 0; i < NARRAY; ++i) {
        printf("%.2f ", A[i]);
    }
    printf("\n");
}

void print_named_mat(int mat[MAX_MAT_SIZE][MAX_MAT_SIZE], const char* name) {
    printf("%s:\n", name);
    for (int i = 0; i < MAX_MAT_SIZE; i++) {
        for (int j = 0; j < MAX_MAT_SIZE; j++) {
            if (mat[i][j] >= INF / 2) printf("%5s", "INF");
            else printf("%5d", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void print_named_vec(int v[MAX_MAT_SIZE], const char* name) {
    printf("%s: ", name);
    for (int i = 0; i < MAX_MAT_SIZE; i++) {
        if (v[i] >= INF / 2) printf("%5s", "INF");
        else printf("%5d", v[i]);
    }
    printf("\n");
};

void print_named_bool_mat(
    int mat[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    const char* name
) {
    printf("%s:\n", name);
    for (int i = 0; i < MAX_MAT_SIZE; i++) {
        for (int j = 0; j < MAX_MAT_SIZE; j++) printf("%2d", mat[i][j]);
        printf("\n");
    }
    printf("\n");
};

int** allocate_matrix(int dim1, int dim2) {
    int** matrix = (int**)safe_malloc(dim1 * sizeof(int*));
    for (int i = 0; i < dim1; i++) {
        matrix[i] = (int*)safe_malloc(dim2 * sizeof(int));
    }
    return matrix;
}

void input_matrix(int** matrix, int size, const char* name) {
    printf("Enter elements of matrix %s:\n", name);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
}

void free_matrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        safe_free(matrix[i]);
    }
    safe_free(matrix);
}

void add_matrices(
    int** A, 
    int** B, 
    int** C, 
    int size, 
    int multiplier
) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = A[i][j] + multiplier* B[i][j];
        }
    }
}

double** allocate_matrix_double(int dim1, int dim2) {
    double** matrix = (double**)safe_malloc(dim1 * sizeof(double*));
    for (int i = 0; i < dim1; i++) matrix[i] = (double*)safe_malloc(dim2 * sizeof(double));
    return matrix;
}

void free_matrix_double(double** matrix, int size) {
    for (int i = 0; i < size; i++) free(matrix[i]);
    free(matrix);
}

void print_matrix_double(double** matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%8.4f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void print_intervals(Interval A[], int size) {
    for (int i = 0; i < size; i++) {
        printf("(%d, %d) ", A[i].low, A[i].high);
    }
    printf("\n");
}

void convert_to_base_n(
    int A[],
    int n,
    int base,
    int converted[][MAX_BASE_DIGITS]
) {
    for (int i = 0; i < n; i++) {
        int num = A[i];
        for (int j = MAX_BASE_DIGITS - 1; j >= 0; j--) {
            converted[i][j] = num % base;
            num /= base;
        }
    }
}

void convert_back_from_base_n(
    int converted[][MAX_BASE_DIGITS], 
    int n, 
    int base, 
    int A[]
) {
    for (int i = 0; i < n; i++) {
        int num = 0;
        for (int j = 0; j < MAX_BASE_DIGITS; j++) {
            num = num * base + converted[i][j];
        }
        A[i] = num;
    }
}

int find_max(int A[], int n) {
    int max = A[0];
    for (int i = 1; i < n; i++) {
        if (A[i] > max) {
            max = A[i];
        }
    }
    return max;
}

int count_digits(int num) {
    if (num == 0) return 1;
    return (int)log10(abs(num)) + 1;
}

int next_power_of_two(int n) {
    int power = 1;
    while (power < n) power <<= 1;
    return power;
}

int median_of_five(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
    return arr[n / 2];
}

int select_kth(int arr[], int left, int right, int k) {
    if (right - left <= 5) {
        for (int i = left + 1; i <= right; i++) {
            int key = arr[i];
            int j = i - 1;
            while (j >= left && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
        return arr[left + k];
    }

    int groupCnt = (right - left + 5) / 4;
    int medians[groupCnt];

    for (int i = 0; i < groupCnt; i++) {
        int groupLeft = left + i * 5;
        int groupRight = (groupLeft + 4 < right) ? groupLeft + 4 : right;
        
        for (int j = groupLeft + 1; j <= groupRight; j++) {
            int key = arr[j];
            int m = j - 1;
            while (m >= groupLeft && arr[m] > key) {
                arr[m + 1] = arr[m];
                m--;
            }
            arr[m + 1] = key;
        }
        
        medians[i] = arr[groupLeft + (groupRight - groupLeft) / 2];
    }

    int pivot;
    if (groupCnt == 1) pivot = medians[0];
    else pivot = select_kth(medians, 0, groupCnt - 1, groupCnt / 2);

    int pivotIdx = left;
    for (int i = left; i <= right; i++) {
        if (arr[i] == pivot) {
            int temp = arr[i];
            arr[i] = arr[left];
            arr[left] = temp;
            pivotIdx = left;
            break;
        }
    }

    int storeIdx = left + 1;
    for (int i = left + 1; i <= right; i++) {
        if (arr[i] < pivot) {
            int tmp = arr[i];
            arr[i] = arr[storeIdx];
            arr[storeIdx] = tmp;
            storeIdx++;
        }
    }

    int tmp = arr[pivotIdx];
    arr[pivotIdx] = arr[storeIdx - 1];
    arr[storeIdx - 1] = tmp;
    
    pivotIdx = storeIdx - 1;

    int pivotRank = pivotIdx - left;
    if (k == pivotRank) return arr[pivotIdx];
    else if (k < pivotRank) return select_kth(arr, left, pivotIdx - 1, k);
    else return select_kth(arr, pivotIdx + 1, right, k - pivotRank - 1);
}

void generate_random_binary_string(char *str, size_t length) {
    for (size_t i = 0; i < length; i++) str[i] = (rand() % 2)  ? '1' : '0';
    str[length] = '\0';
}

complex_t complex_add(complex_t a, complex_t b) {
    complex_t res = {a.real + b.real, a.imag + b.imag};
    return res;
}

complex_t complex_sub(complex_t a, complex_t b) {
    complex_t res = {a.real - b.real, a.imag - b.imag};
    return res;
}

complex_t complex_mul(complex_t a, complex_t b) {
    complex_t res = {
        a.real * b.real - a.imag * b.imag,
        a.real * b.imag + a.imag * b.real
    };
    return res;
}

complex_t complex_exp(double theta) {
    complex_t res = {cos(theta), sin(theta)};
    return res;
}

complex double** allocate_matrix_complex(int n) {
    complex double** mat = (complex double**)safe_malloc(n * sizeof(complex double*));
    for (int i = 0; i < n; ++i) 
        mat[i] = (complex double*)safe_malloc(n * sizeof(complex double));
    return mat;
}

void free_matrix_complex(complex double** mat, int n) {
    for (int i = 0; i < n; ++i) safe_free(mat[i]);
    safe_free(mat);
}

void print_matrix_complex(complex double** mat, int n) {
    for (int i = 0; i < n; ++i) {
        printf("[");
        for (int j = 0; j < n; ++j) {
            printf("(%8.3f %+8.3fi)", creal(mat[i][j]), cimag(mat[i][j]));
            printf("]");
        }
        printf("\n");
    }
    printf("\n");
}
