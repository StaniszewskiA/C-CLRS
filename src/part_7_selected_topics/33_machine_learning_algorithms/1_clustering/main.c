#include "part_7_selected_topics/33_machine_learning_algorithms/33_machine_learning_algorithms.h"

#define TASK 2

int main(void) {
    switch (TASK)
    {
        case 1: {
            test_lloyd_kmeans();
            break;
        }

        case 2: {
            test_kmeans_1d();
            break;
        }

        default:
            break;
    }
}
