#include "part_7_selected_topics/31_number-theoretic_algorithms/31_number-theoretic_algorithms.h"

#define TASK 2

int main(void) {
    switch (TASK)
    {
        case 1: {
            int n = 7;
            int basis = 2;

            printf("Is %d pseudoprime with basis %d? %s\n", 
                n, basis, pseudoprime(n, basis) ? "true" : "false");
            break;
        }

        case 2: {
            int n = 7;
            int s = 2;

            printf("Is %d (probably) prime? %s\n",
                n, miller_rabin(n, s) ? "true" : "false");
            break;
        }

        default:
            break;
    }
}