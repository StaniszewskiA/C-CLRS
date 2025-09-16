#include "part_7_selected_topics/30_polynomials_and_the_fft/polynomials_and_the_fft.h"

#define TASK 3

int main(void) {
    switch (TASK)
    {
        case 1: {
            test_fft();
            break;
        }
        
        case 2: {
            test_fft_radix3();
            break;
        }

        case 3: {
            test_z_transform();
            break;
        }

        default:
            break;
    }
}
