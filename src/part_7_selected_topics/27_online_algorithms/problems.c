#include "part_7_selected_topics/27_online_algorithms/27_online_algorithms.h"

#define TASK 1

// --- The cow-path problem ---

void find_pasture(double pasturePoss) {
    double currPoss = 0.0;
    double step = 1.0;
    int direction = 1;
    double traveled = 0.0;

    printf("Starting search for pasture (it is hidden at position %.2f)\n", 
        pasturePoss);

    while (1) {
        double destination = currPoss + direction * step;
        printf("Going from %.2f to %.2f\n", currPoss, destination);
        traveled += fabs(destination - currPoss);

        if ((direction == 1 && pasturePoss >= currPoss && pasturePoss <= destination) ||
            (direction == -1 && pasturePoss <= currPoss && pasturePoss >= destination)
            ) {
                traveled += fabs(pasturePoss - destination);
                printf("Found pasture!\n");
                printf("Total distance: %.2f, ratio: %.2f", 
                    traveled, traveled / fabs(pasturePoss));
                break;
            }

        currPoss = destination;
        direction *= -1;
        step *= 2;
    }
}

int main(void) {
    switch (TASK)
    {
        case 1: {
            // 27-1
            double pasturePoss = 300.00;
            find_pasture(pasturePoss);
            break;
        }

        case 2: {
            // 27-2
            printf("TODO");
            break;
        }

        default:
            break;
    }

    return 0;
}