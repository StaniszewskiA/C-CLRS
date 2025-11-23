#include "part_7_selected_topics/32_string-matching/32_string-matching.h"

#define TASK 3

int main(void) {
    switch (TASK)
    {
        case 1: {
            test_rabin_karp_matcher();
            break;
        }

        case 2: {
            test_rabin_karp_multi_matcher();
            break;
        }

        case 3: {
            test_rabin_karp_2d_matcher();
            break;
        }

        default:
            break;
    }
}
