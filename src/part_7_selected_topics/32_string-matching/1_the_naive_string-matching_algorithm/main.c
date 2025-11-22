#include "part_7_selected_topics/32_string-matching/32_string-matching.h"

#define TASK 3

int main(void) {
    switch (TASK)
    {
        case 1: {
            test_naive_string_matcher();
            break;
        }

        case 2: {
            test_naive_string_matcher_distinct();
            break;
        }

        case 3: {
            test_gap_string_matcher();
            break;
        }

        default:
            break;
    }
}
