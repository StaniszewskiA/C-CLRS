#include "part_2_sorting_and_order_statistics/6_heapsort/heapsort.h"

int main(void) {
    int original_arr[] = {27, 17, 3, 16, 13, 10, 1, 5, 7, 12, 4, 8, 9, 0};
    int n = sizeof(original_arr) / sizeof(original_arr[0]);

    printf("1. Build Max Heap (Iterative):\n");
    int arr1[14];
    for (int i = 0; i < n; i++) arr1[i] = original_arr[i]; 
    
    printf("Original: ");
    print_arr(arr1, n);
    
    build_max_heap(arr1, n);
    
    printf("Max Heap: ");
    print_arr(arr1, n);
    printf("\n");

    printf("2. Build Max Heap (Recursive):\n");
    int arr2[14];
    for (int i = 0; i < n; i++) arr2[i] = original_arr[i]; 
    
    printf("Original: ");
    print_arr(arr2, n);
    
    build_max_heap_recursive(arr2, n);
    
    printf("Max Heap: ");
    print_arr(arr2, n);
    printf("\n");

    printf("3. Build Min Heap (Recursive):\n");
    int arr3[14];
    for (int i = 0; i < n; i++) arr3[i] = original_arr[i];  
    
    printf("Original: ");
    print_arr(arr3, n);
    
    build_min_heap_recursive(arr3, n);
    
    printf("Min Heap: ");
    print_arr(arr3, n);
    printf("\n");

    printf("4. Build Min Heap (Iterative):\n");
    int arr4[14];
    for (int i = 0; i < n; i++) arr4[i] = original_arr[i];
    
    printf("Original: ");
    print_arr(arr4, n);
    
    build_min_heap_iterative(arr4, n);
    
    printf("Min Heap: ");
    print_arr(arr4, n);
    printf("\n");

    return 0;
}