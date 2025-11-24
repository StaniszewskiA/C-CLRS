#include "part_7_selected_topics/32_string-matching/32_string-matching.h"

#define TASK 2

int main(void) {
    switch (TASK)
    {
        case 1: {
            test_finite_automaton_matcher();
            break;
        }

        case 2: {
            test_finite_automaton_gap_matcher();
            break;
        }

        default:
            break;
    }
}
