#include "part_5_advanced_data_structures/19_data_structures_for_disjoint_sets/data_structures_for_disjoint_sets.h"

#define TASK 2

extern Node2* nodes2[MAX_DISJOINT_SET_SIZE];

int main(void) {
    DisjointSet ds;
    int n = 10;

    make_disjoint_set(&ds, n);

    union_disjoint_sets(&ds, 0, 1);
    union_disjoint_sets(&ds, 1, 2);
    union_disjoint_sets(&ds, 3, 4);
    union_disjoint_sets(&ds, 2, 4);
    union_disjoint_sets(&ds, 5, 6);
    union_disjoint_sets(&ds, 6, 7);
    union_disjoint_sets(&ds, 0, 7);
    union_disjoint_sets(&ds, 8, 9);
    union_disjoint_sets(&ds, 0, 8);

    print_disjoint_sets(&ds, n);

    switch (TASK)
    {
        case 1: {
            // 19.3-2
            int target = find_non_recursive(&ds, 1);
            printf("%d\n", target);
            break;
        }

        case 2: {
            // 19.3-4
            int n2 = 10;
            for (int i = 0; i < n2; i++) make_set2(i);

            union_sets2(nodes2[0], nodes2[1]);
            union_sets2(nodes2[1], nodes2[2]);
            union_sets2(nodes2[2], nodes2[3]);

            print_set2(nodes2[2]); 
            print_set2(nodes2[3]);

            break;
        }
        
        default:
            break;
    }

    return 0;
}