#include "part_1_foundations/5_probabilistic_analysis_and_randomized_algorithms/probabilistic_analysis_and_randomized_algorithms.h"

int main() {
    int candidates[] = {5, 7, 3, 8, 6};
    int size = sizeof(candidates) / sizeof(candidates[0]); 
    int best = hire_assistant(candidates, size);
    printf("Best candidate score: %d\n", best);
    return 0;
}