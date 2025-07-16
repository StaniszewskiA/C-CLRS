#include "part_7_selected_topics/26_multithreaded_algorithms/multithreaded_algorithms.h"

#define TASK 4

int main(void) {
    switch (TASK) {
        case 1: {
            // Parallel merge sort
            test_p_merge_sort();
            break;
        }
        
        case 2: {
            // 26.3-2
            test_p_median_merge();
            break;
        }

        case 3: {
            // 26.3-3
            test_p_partition();
            break;
        }

        case 4: {
            // 26.3-4
            test_p_recursive_fft();
            break;
        }
    }
}
