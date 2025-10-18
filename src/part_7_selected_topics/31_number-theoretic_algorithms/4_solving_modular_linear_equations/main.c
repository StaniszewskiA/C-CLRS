#include "part_7_selected_topics/31_number-theoretic_algorithms/31_number-theoretic_algorithms.h"

#define TASK 2

int main(void) {
    switch (TASK)
    {
        case 1: {
            test_modular_linear_equation_solver();
            break;
        }

        case 2: {
            test_modular_linear_equation_solver_modified();
            break;
        }

        default:
            break;
    }
}