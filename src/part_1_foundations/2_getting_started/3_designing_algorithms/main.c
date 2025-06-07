#include "part_1_foundations/2_getting_started/getting_started.h"

int main(void) {
    print_separator("Chapter 2.3: Designing Algorithms Demonstration");
    
    int original[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(original) / sizeof(original[0]);
    int test_array[7];
    
    printf("1. Merge Sort:\n");
    copy_arr(original, test_array, n);
    printf("   Original: ");
    print_arr(test_array, n);
    merge_sort(test_array, 0, n - 1);
    printf("   Sorted:   ");
    print_arr(test_array, n);
    printf("   Is sorted: %s\n\n", is_sorted_asc(test_array, n) ? "Yes" : "No");
    
    // 2. Binary Search Demonstrations (using sorted array)
    printf("2. Binary Search (using sorted array):\n");
    printf("   Array: ");
    print_arr(test_array, n);
    
    int target = 27;
    printf("   Searching for %d:\n", target);
    
    // Iterative binary search
    int index = iterative_binary_search(test_array, n, target);
    printf("     Iterative: %s", (index != -1) ? "Found at index " : "Not found");
    if (index != -1) printf("%d", index);
    printf("\n");
    
    // Recursive binary search
    index = recursive_binary_search(test_array, 0, n - 1, target);
    printf("     Recursive: %s", (index != -1) ? "Found at index " : "Not found");
    if (index != -1) printf("%d", index);
    printf("\n\n");
    
    // 3. Recursive Insertion Sort
    printf("3. Recursive Insertion Sort:\n");
    copy_arr(original, test_array, n);
    printf("   Original: ");
    print_arr(test_array, n);
    recursive_insertion_sort(test_array, n);
    printf("   Sorted:   ");
    print_arr(test_array, n);
    printf("   Is sorted: %s\n\n", is_sorted_asc(test_array, n) ? "Yes" : "No");
    
    // 4. Sum Search (Two-element sum)
    printf("4. Sum Search (Two-element sum):\n");
    int sum_array[] = {1, 2, 3, 4, 5, 6};
    int sum_size = sizeof(sum_array) / sizeof(sum_array[0]);
    printf("   Array: ");
    print_arr(sum_array, sum_size);
    
    int target_sum = 7;
    printf("   Looking for two elements that sum to %d: ", target_sum);
    int found = sum_search(sum_array, sum_size, target_sum);
    printf("%s\n", found ? "Found" : "Not found");
    
    target_sum = 15;
    printf("   Looking for two elements that sum to %d: ", target_sum);
    found = sum_search(sum_array, sum_size, target_sum);
    printf("%s\n", found ? "Found" : "Not found");
    
    return 0;
}