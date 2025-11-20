#include "part_7_selected_topics/31_number-theoretic_algorithms/31_number-theoretic_algorithms.h"

#define TASK 6

int main(void) {
    switch (TASK)
    {
        case 1: {
            test_euclid_gcd();
            break;
        }

        case 2: {
            test_extended_euclid_gcd();
            break;
        }

        case 3: {
            test_euclid_gcd_recursive();
            break;
        }

        case 4: {
            test_extended_euclid_gcd_multiple();
            break;
        }

        case 5: {
            test_lcm();
            break;
        }

        case 6: {
            test_lcm_multiple();
            break;
        }

        default:
            break;
    }
}