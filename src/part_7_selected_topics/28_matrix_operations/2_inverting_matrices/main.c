#include "part_7_selected_topics/28_matrix_operations/28_matrix_operations.h"

#define TASK 2

int main(void) {
    switch (TASK) {
        case 1: {
            test_matrix_inversion();
            break;
        }
        case 2: {
            // 28.2-5
            test_complex_matrix_inversion();
            break;
        }
    }
}
