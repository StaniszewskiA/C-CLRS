#include "../include/common.h"

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

void copy_arr(const int source[], int dest[], int size) {
    for (int i = 0; i < size; i++) dest[i] = source[i];
}
