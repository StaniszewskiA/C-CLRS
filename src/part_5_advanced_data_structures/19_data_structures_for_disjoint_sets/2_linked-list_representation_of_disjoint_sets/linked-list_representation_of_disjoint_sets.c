#include "part_5_advanced_data_structures/19_data_structures_for_disjoint_sets/data_structures_for_disjoint_sets.h"

/*
    19.2-1
*/
Set* make_set_node(SetNode* x) {
    Set* s = (Set*)malloc(sizeof(Set));
    x->next = NULL;
    x->set = s;
    s->head = x;
    s->tail = x;
    s->size = 1;
    return s;
}

SetNode* find_set_node(SetNode* x) {
    return x->set->head;
}

Set* union_set_nodes(SetNode* x, SetNode* y) {
    Set* s1 = x->set;
    Set* s2 = y->set;

    if (s1 == s2) return s1;

    if (s1->size < s2->size) {
        Set* temp = s1;
        s1 = s2;
        s2 = temp;
    }

    s1->tail->next = s2->head;

    SetNode* z = s2->head;
    while (z != NULL) {
        z->set = s1;
        z = z->next;
    }

    s1->tail = s2->tail;
    s1->size += s2->size;

    free(s2);
    return s1;
}
