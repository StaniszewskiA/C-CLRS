#include "part_1_foundations/5_probabilistic_analysis_and_randomized_algorithms/probabilistic_analysis_and_randomized_algorithms.h"

int hire_assistant(int* candidates, int size) {
    int bestSoFar = 0;
    for (int i = 0; i < size; i++) {
        if (candidates[i] > bestSoFar) {
            bestSoFar = candidates[i];
        }
    }

    return bestSoFar;
}

