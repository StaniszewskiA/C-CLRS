#include "part_7_selected_topics/33_machine_learning_algorithms/33_machine_learning_algorithms.h"

#define TASK 4

int main(void) {
    switch (TASK)
    {
        case 1: {
            test_weighted_majority();
            break;
        }

        case 2: {
            test_halving_with_reset();
            break;
        }

        case 3: {
            test_randomized_halving();
            break;
        }

        case 4: {
            test_randomized_weighted_majority();
            break;
        }

        default:
            break;
    }
}
