#include "part_5_advanced_data_structures/19_data_structures_for_disjoint_sets/data_structures_for_disjoint_sets.h"

#define TASK 1

int main(void) {
    switch (TASK)
    {
        case 1: {
            // 19.2-1
            SetNode* a = (SetNode*)malloc(sizeof(SetNode)); a->key = 1;
            SetNode* b = (SetNode*)malloc(sizeof(SetNode)); b->key = 2;
            SetNode* c = (SetNode*)malloc(sizeof(SetNode)); c->key = 3;

            make_set_node(a);
            make_set_node(b);
            make_set_node(c);

            union_set_nodes(a, b);
            union_set_nodes(a, c);

            SetNode* rep = find_set_node(c);
            printf("Representative of node c (key = %d): %d\n", c->key, rep->key);

            SetNode* iter = find_set_node(a);
            printf("Set members: ");
            while (iter != NULL) {
                printf("%d ", iter->key);
                iter = iter->next;
            }
            printf("\n");

            iter = a->set->head;
            while (iter != NULL) {
                SetNode* next = iter->next;
                free(iter);
                iter = next;
            }
            free(a->set);

            break;
        }
        
        default:
            break;
    }

    return 0;
}
