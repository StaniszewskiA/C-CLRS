#include "part_7_selected_topics/31_number-theoretic_algorithms/31_number-theoretic_algorithms.h"

#define TASK 4

int main(void) {
    switch (TASK)
    {
        case 1: {
            test_is_perfect_kth_power();
            break;
        }

        case 2: {
            test_long_division();
            break;
        }

        case 3: {
            test_bin_to_dec();
            break;
        }

        case 4: {
            test_print_on_bulbs();
            break;
        }

        default:
            break;
    }
}