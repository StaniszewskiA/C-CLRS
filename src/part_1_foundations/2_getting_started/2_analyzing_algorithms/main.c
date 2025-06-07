#include "part_1_foundations/2_getting_started/getting_started.h"

int main(void) {
    printf("1. Polynomial Complexity Analysis:\n");
    const char *polynomial = "3x^7 + 2x^3 - 7x + 10";
    printf("   Polynomial: %s\n", polynomial);
    printf("   Highest degree: ");
    int maxExponent = find_highest_degree(polynomial);
    printf("%d\n", maxExponent);
    printf("   Big-O complexity: ");
    determine_big_o(maxExponent);
    printf("\n");

    printf("2. Selection Sort Demonstration:\n");
    int arr[] = {64, 25, 12, 22, 11};
    int n = sizeof(arr) / sizeof(arr[0]);   

    printf("   Original array: ");
    print_arr(arr, n);
    
    selection_sort(arr, n);
    
    printf("   Sorted array:   ");
    print_arr(arr, n);
    
    printf("   Is sorted ascending: %s\n", is_sorted_asc(arr, n) ? "Yes" : "No");
    return 0;
}