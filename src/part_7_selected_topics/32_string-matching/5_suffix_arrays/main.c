#include "part_7_selected_topics/32_string-matching/32_string-matching.h"

#define TASK 6

int main(void) {
    switch (TASK)
    {
        case 1: {
            text_compute_suffix_array();
            break;
        }

        case 2: {
            test_compute_lcp();
            break;
        }

        case 3: {
            test_compute_lcp_hippity_hoppity();
            break;
        }

        case 4: {
            test_compute_suffix_array_early();
            break;
        }

        case 5: {
            test_longest_common_substrings();
            break;
        }

        case 6: {
            test_possibly_longest_palindromes();
            break;
        }

        default:
            break;
    }
}
