#include "../include/common.h"

int main() {
    print_separator("Common Functions Demo");
    
    printf("Testing memory functions:\n");
    int* numbers = (int*)safe_malloc(5 * sizeof(int));
    printf("Allocated array of 5 integers\n");
    
    int* zeros = (int*)safe_calloc(3, sizeof(int));
    printf("Allocated zero-initialized array: ");
    for (int i = 0; i < 3; i++) {
        printf("%d ", zeros[i]);
    }
    printf("\n");
    
    numbers = (int*)safe_realloc(numbers, 8 * sizeof(int));
    printf("Reallocated to 8 integers\n");
    
    printf("\nTesting random_int:\n");
    printf("Random numbers (1-10): ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", random_int(1, 10));
    }
    printf("\n");
    
    printf("random_int(5,5) = %d\n", random_int(5, 5));
    printf("random_int(10,5) = %d (error case)\n", random_int(10, 5));
    
    printf("\nTesting get_time_ms:\n");
    double start = get_time_ms();
    printf("Start time: %.3f ms\n", start);
    
    for (volatile int i = 0; i < 1000000; i++) {
        // wait
    }
    
    double end = get_time_ms();
    printf("End time: %.3f ms\n", end);
    printf("Elapsed: %.3f ms\n", end - start);
    
    printf("\nTesting print_error:\n");
    print_error("This is a test error message");
    print_error(NULL);
    
    printf("\nTesting macros:\n");
    int a = 15, b = 7;
    printf("a=%d, b=%d\n", a, b);
    printf("MAX(a,b) = %d\n", MAX(a, b));
    printf("MIN(a,b) = %d\n", MIN(a, b));
    printf("ABS(-25) = %d\n", ABS(-25));
    
    int temp;
    printf("Before SWAP: a=%d, b=%d\n", a, b);
    SWAP(a, b, temp);
    printf("After SWAP: a=%d, b=%d\n", a, b);
    
    int test_array[] = {1, 2, 3, 4, 5, 6};
    printf("Array size: %zu\n", ARRAY_SIZE(test_array));
    
    DEBUG_PRINT("This is a debug message with value: %d", 42);
    
    safe_free(numbers);
    safe_free(zeros);
    
    print_separator("Demo Complete");
    
    return SUCCESS;
}