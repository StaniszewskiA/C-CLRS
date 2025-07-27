#include "part_7_selected_topics/27_online_algorithms/27_online_algorithms.h"

#define TASK 2

int main(void) {
    switch (TASK) {
        case 1: {
            // Basic MTF algorithm,
            test_move_to_front();
            break;
        }

        case 2: {
            // Frequency count, 27.2-3
            test_frequency_count();
        }
    }
}
