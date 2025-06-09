#include "part_4_advanced_design_and_analysis_techniques/15_greedy_algorithms/greedy_algorithms.h"

int main(void) {
    char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    unsigned freqs[] = {5, 9, 12, 13, 16, 45};
    unsigned size = sizeof(arr) / sizeof(arr[0]);

    huffman_codes(arr, freqs, size);

    return 0;
}