#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct XorNode {
    int key;
    struct XorNode* np;
} XorNode;

typedef struct List {
    XorNode* head;
    XorNode* nil;
} List;

XorNode* XOR(XorNode* a, XorNode* b) {
    return (XorNode*)((uintptr_t)a ^ (uintptr_t)b);
}

void initList(List* L) {
    L->head = NULL;
    L->nil = (XorNode*)malloc(sizeof(XorNode));
    L->nil->np = NULL;
}

XorNode* search(List* L, int k) {
    XorNode* p = NULL;
    XorNode* x = L->head;

    while (x != NULL && x->key != k) {
        XorNode* temp = x;
        x = XOR(p, x->np);
        p = temp;
    }

    return x;
} 

void insert(List* L, int k) {
    XorNode* x = (XorNode*)malloc(sizeof(XorNode));
    x->key = k;
    x->np = XOR(NULL, L->head);

    if (L->head != NULL) {
        L->head->np = XOR(x, XOR(NULL, L->head->np));
    }

    L->head = x;
}

void delete(List* L, int k) {
    XorNode* p = NULL;
    XorNode* x = L->head;

    while (x != NULL && x->key != k) {
        XorNode* temp = x;
        x = XOR(p, x->np);  
        p = temp;
    }

    if (x == NULL) {
        printf("Node with key %d not found\n", k);
        return;
    }

    if (x == L->head) {
        L->head = XOR(NULL, x->np);
        if (L->head != NULL) {
            L->head->np = XOR(NULL, XOR(L->head->np, x));
        }
    } else {
        XorNode* prev = XOR(p, x->np);
        XorNode* next = XOR(x->np, p);

        if (prev != NULL) {
            prev->np = XOR(XOR(prev->np, x), next); 
        }
        if (next != NULL) {
            next->np = XOR(XOR(next->np, x), prev);  
        }

        free(x); 
    }
}


void printList(List* L) {
    XorNode* p = NULL;
    XorNode* x = L->head;
    while (x != NULL) {
        printf("%d -> ", x->key);
        XorNode* temp = x;
        x = XOR(p, x->np);
        p = temp;
    }
    printf("NULL\n");
}

int main(void) {
    List L;
    initList(&L);

    insert(&L, 10);
    insert(&L, 20);
    insert(&L, 30);

    printList(&L);

    XorNode* result = search(&L, 20);
    if (result != NULL) {
        printf("Found node with key %d\n", result->key);
    }

    delete(&L, 20);
    printList(&L);

    return 0;
}