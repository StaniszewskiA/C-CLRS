#include "part_2_sorting_and_order_statistics/8_sorting_in_linear_time/sorting_in_linear_time.h"

int main(void) {
    int arr[] = {12, 4, 15, 8, 3, 10, 6, 14, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int base = n;
    
    int converted[n][MAX_BASE_DIGITS];
    convert_to_base_n(arr, n, base, converted);
    
    radix_sort(converted, n, base);
    
    convert_back_from_base_n(converted, n, base, arr); 
    
    printf("Sorted array: ");
    print_array(arr, n);

    char words[][MAX_LEN] = {
        "COW",
        "DOG",
        "SEA",
        "RUG",
        "ROW",
        "MOB",
        "BOX",
        "TAB",
        "BAR",
        "EAR",
        "TAR",
        "DIG",
        "BIG",
        "TEA",
        "NOW",
        "FOX"
    };
    int n = sizeof(words) / sizeof(words[0]);

    radix_sort_char(words, n);
    print_arr(words, n);

    return 0;
}