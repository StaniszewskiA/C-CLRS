#include "part_7_selected_topics/28_matrix_operations/28_matrix_operations.h"

#define TASK 2

int main(void) {
    switch (TASK) {
        case 1: {
            test_lu_decomposition();
            break;
        }

        case 2: {
            test_lup_decomposition();
            break;
        }
    }
}
