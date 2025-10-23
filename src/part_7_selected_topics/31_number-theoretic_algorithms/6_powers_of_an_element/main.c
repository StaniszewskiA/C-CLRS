#include "part_7_selected_topics/31_number-theoretic_algorithms/31_number-theoretic_algorithms.h"

#define TASK 2

int main(void) {
    switch (TASK)
    {
        case 1: {
            test_modular_exponentation();
            break;
        }

        case 2: {
            test_modular_exponentation_iterative();
            break;
        }

        default:
            break;
    }
}