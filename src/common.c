#include "../include/common.h"

int compare(const void *a, const void *b) {
    return (*(char*)a - *(char*)b);
}

int min_of_three(int a, int b, int c) {
    if (a <= b && a <= c) return a;
    else if (b <= a && b <= c) return b;
    else return c;
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
    for (int i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
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

double** allocate_matrix(int size) {
    double** matrix = (double**)malloc(size * sizeof(double*));
    for (int i = 0; i < size; i++) {
        matrix[i] = (double*)malloc(size * sizeof(double));
    }
    return matrix;
}

void input_matrix(double** matrix, int size, const char* name) {
    printf("Enter elements of matrix %s:\n", name);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            scanf("%lf", &matrix[i][j]);
        }
    }
}

void free_matrix(double** matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void add_matrices(
    double** A, 
    double** B, 
    double** C, 
    int size, 
    int multiplier
) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = A[i][j] + multiplier* B[i][j];
        }
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

void generate_random_binary_string(char *str, size_t length) {
    for (size_t i = 0; i < length; i++) str[i] = (rand() % 2)  ? '1' : '0';
    str[length] = '\0';
}
