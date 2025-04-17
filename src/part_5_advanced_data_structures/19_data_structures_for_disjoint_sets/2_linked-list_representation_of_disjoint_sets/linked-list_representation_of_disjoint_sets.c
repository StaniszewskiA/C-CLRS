#include <stdio.h>
#include <stdlib.h>

#define TASK 1

/*
    19.2-1
*/

struct set;

typedef struct Node {
    int key;
    struct Node* next;
    struct Set* set;
} Node;

typedef struct Set {
    Node* head;
    Node* tail;
    int size;
} Set;

Set* make_set(Node* x);
Node* find_set(Node* x);
Set* union_sets(Node* x, Node* y);

Set* make_set(Node* x) {
    Set* s = (Set*)malloc(sizeof(Set));
    x->next = NULL;
    x->set = s;
    s->head = x;
    s->tail = x;
    s->size = 1;
    return s;
}

Node* find_set(Node* x) {
    return x->set->head;
}

Set* union_sets(Node* x, Node* y) {
    Set* s1 = x->set;
    Set* s2 = y->set;

    if (s1 == s2) return s1;

    if (s1->size < s2->size) {
        Set* temp = s1;
        s1 = s2;
        s2 = temp;
    }

    s1->tail->next = s2->head;

    Node* z = s2->head;
    while (z != NULL) {
        z->set = s1;
        z = z->next;
    }

    s1->tail = s2->tail;
    s1->size += s2->size;

    free(s2);
    return s1;
}

int main(void) {
    switch (TASK)
    {
        case 1: {
            // 19.2-1
            Node* a = (Node*)malloc(sizeof(Node)); a->key = 1;
            Node* b = (Node*)malloc(sizeof(Node)); b->key = 2;
            Node* c = (Node*)malloc(sizeof(Node)); c->key = 3;

            make_set(a);
            make_set(b);
            make_set(c);

            union_sets(a, b);
            union_sets(a, c);

            Node* rep = find_set(c);
            printf("Representative of node c (key = %d): %d\n", c->key, rep->key);

            Node* iter = find_set(a);
            printf("Set members: ");
            while (iter != NULL) {
                printf("%d ", iter->key);
                iter = iter->next;
            }
            printf("\n");

            iter = a->set->head;
            while (iter != NULL) {
                Node* next = iter->next;
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
