#include "../../../../include/part_1_foundations/2_getting_started/getting_started.h"

int main(void) {
    int original[] = {5, 2, 4, 6, 1, 3};
    int n = sizeof(original) / sizeof(original[0]);
    int test_array[6];

    printf("1. Basic Insertion Sort (Ascending):\n");
    copy_arr(original, test_array, n);
    printf("   Original: ");
    print_arr(test_array, n);
    insertion_sort(test_array, n);
    printf("   Sorted:   ");
    print_arr(test_array, n);
    printf("   Is sorted ascending: %s\n\n", is_sorted_asc(test_array, n) ? "Yes" : "No");

    printf("2. Insertion Sort (Descending):\n");
    copy_arr(original, test_array, n);
    printf("   Original: ");
    print_arr(test_array, n);
    insertion_sort_desc(test_array, n);
    printf("   Sorted:   ");
    print_arr(test_array, n);
    printf("   Is sorted descending: %s\n\n", is_sorted_desc(test_array, n) ? "Yes" : "No");
    
    printf("3. Recursive Insertion Sort:\n");
    copy_arr(original, test_array, n);
    printf("   Original: ");
    print_arr(test_array, n);
    recursive_insertion_sort(test_array, n);
    printf("   Sorted:   ");
    print_arr(test_array, n);
    printf("   Is sorted ascending: %s\n\n", is_sorted_asc(test_array, n) ? "Yes" : "No");
    
    printf("4. Step-by-Step Insertion Sort:\n");
    copy_arr(original, test_array, n);
    printf("   Original: ");
    print_arr(test_array, n);
    printf("   Sorting process:\n");
    insertion_sort_step_by_step(test_array, n);
    printf("   Final result: ");
    print_arr(test_array, n);
    printf("\n");
    
    printf("5. Linear Search:\n");
    int sorted_array[] = {1, 2, 3, 4, 5, 6};
    int search_size = sizeof(sorted_array) / sizeof(sorted_array[0]);
    printf("   Array: ");
    print_arr(sorted_array, search_size);
    
    int target = 4;
    int index = linear_search(sorted_array, search_size, target);
    printf("   Searching for %d: ", target);
    if (index != -1) {
        printf("Found at index %d\n", index);
    } else printf("Not found\n");
    
    target = 7;
    index = linear_search(sorted_array, search_size, target);
    printf("   Searching for %d: ", target);
    if (index != -1) {
        printf("Found at index %d\n", index);
    } else printf("Not found\n");
    printf("\n");
    
    printf("6. Array Sum:\n");
    printf("   Array: ");
    print_arr(sorted_array, search_size);
    printf("   Sum: %d\n\n", sum_arr(sorted_array, search_size));
    
    printf("7. Binary Number Addition:\n");
    int A[] = {1, 0, 1, 1}; 
    int B[] = {1, 1, 0, 1};  
    int lenA = sizeof(A) / sizeof(A[0]);
    int lenB = sizeof(B) / sizeof(B[0]);
    
    printf("   A = ");
    print_binary_arr(A, lenA);
    printf("   B = ");
    print_binary_arr(B, lenB);
    
    int resultLen;
    int* result = add_binary_numbers(A, lenA, B, lenB, &resultLen);
    
    if (result) {
        printf("   A + B = ");
        print_binary_arr(result, resultLen);
        printf("   (Binary: 1011 + 1101 = result, Decimal: 11 + 13 = 24)\n");
        free(result);
    } else printf("   Error in binary addition\n");
    printf("\n");
    
    printf("8. Array Reversal:\n");
    int reverse_test[] = {1, 2, 3, 4, 5};
    int reverse_len = sizeof(reverse_test) / sizeof(reverse_test[0]);
    printf("   Original: ");
    print_arr(reverse_test, reverse_len);
    reverse_arr(reverse_test, reverse_len);
    printf("   Reversed: ");
    print_arr(reverse_test, reverse_len);
    printf("\n");
    
    printf("9. Sorting Validation Tests:\n");
    int asc_test[] = {1, 2, 3, 4, 5};
    int desc_test[] = {5, 4, 3, 2, 1};
    int unsorted_test[] = {3, 1, 4, 2, 5};
    int test_size = 5;
    
    printf("   Array [1,2,3,4,5] is sorted ascending: %s\n", 
           is_sorted_asc(asc_test, test_size) ? "Yes" : "No");
    printf("   Array [5,4,3,2,1] is sorted descending: %s\n", 
           is_sorted_desc(desc_test, test_size) ? "Yes" : "No");
    printf("   Array [3,1,4,2,5] is sorted ascending: %s\n", 
           is_sorted_asc(unsorted_test, test_size) ? "Yes" : "No");
    printf("   Array [3,1,4,2,5] is sorted descending: %s\n", 
           is_sorted_desc(unsorted_test, test_size) ? "Yes" : "No");
    
    return 0;
}