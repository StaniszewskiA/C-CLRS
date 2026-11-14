#include "part_7_selected_topics/34_np-completeness/34_np-completeness.h"

#define TASK 6

int main(void) {
    switch (TASK)
    {
        case 1: {
            test_verify_graph_isomorphism();
            break;
        }

        case 2: {
            test_ham_cycle_order();
            break;
        }

        case 3: {
            test_decide_by_search();
            break;
        }

        case 4: {
            test_ham_path();
            break;
        }

        case 5: {
            test_ham_path_dag();
            break;
        }

        case 6: {
            test_verify_not_tautology();
            break;
        }

        default:
            break;
    }

    return 0;
}
