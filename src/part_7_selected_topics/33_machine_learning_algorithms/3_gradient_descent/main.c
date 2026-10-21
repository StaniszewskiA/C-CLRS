#include "part_7_selected_topics/33_machine_learning_algorithms/33_machine_learning_algorithms.h"

#define TASK 4

int main(void) {
    switch (TASK)
    {
        case 1: {
            test_gradient_descent();
            break;
        }

        case 2: {
            test_gradient_descent_constrained();
            break;
        }

        case 3: {
            test_squared_error_gradient();
            break;
        }

        case 4: {
            test_kmeans_gradient_descent();
            break;
        }

        default:
            break;
    }
}
