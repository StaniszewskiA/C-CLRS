#include "part_7_selected_topics/27_online_algorithms/27_online_algorithms.h"

#define TASK 2

int main(void) {
    switch (TASK) {
        case 1: {
            // Deterministic
            test_deterministic_caches();
            break;
        }
        case 2: {
            // Non-deterministic
            test_non_deterministic_caches();
            break;
        }

    }
}