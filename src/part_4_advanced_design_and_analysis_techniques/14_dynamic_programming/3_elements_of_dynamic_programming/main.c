#include "part_4_advanced_design_and_analysis_techniques/14_dynamic_programming/dynamic_programming.h"

int main(void) {
    int p[] = {30, 35, 15, 5, 10, 20, 25};
    int n = sizeof(p) / sizeof(p[0]) - 1;

    printf("Minimum number of multiplications: %d\n", 
        memoized_matrix_chain(p, n));

    return 0;
}