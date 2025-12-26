#include "part_7_selected_topics/32_string-matching/32_string-matching.h"

#define TASK 5

int main(void) {
    switch (TASK)
    {
        case 1: {
            test_kmp_matching();
            break;
        }

        case 2: {
            test_concat_kmp_matching();
            break;
        }

        case 3: {
            test_kmp_matching_prime_prefix();
            break;
        }

        case 4: {
            test_is_cyclic_rotation();
            break;
        }

        case 5: {
            test_compute_transition_function_kmp();
            break;
        }

        default:
            break;
    }
}
