#include "part_3_data_structures/10_elementary_data_structures/elementary_data_structures.h"

SinglyNode* singly_node_create(int data) {
    SinglyNode *newNode = (SinglyNode*)malloc(sizeof(SinglyNode));
    if (!newNode) {
        printf("Malloc failed");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void singly_list_insert_at_front(SinglyNode** head, int x) {
    SinglyNode* newNode = singly_node_create(x);
    newNode->next = *head;
    *head = newNode;
}

void singly_list_insert_at_idx(SinglyNode** head, int x, int idx) {
    SinglyNode* newNode = singly_node_create(x);
    if (idx == 0) {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    SinglyNode* temp = *head;
    for (int i = 0; i < idx - 1 && temp != NULL; i++)
        temp = temp->next;

    if (temp == NULL) {
        printf("Position out of range.\n");
        free(newNode);
        return;
    }
    newNode->next = temp->next;
    temp->next = newNode;
}

void singly_list_delete_head(SinglyNode** head) {
    if (*head == NULL) return;

    SinglyNode* temp = *head;
    *head = (*head)->next;
    free(temp);
}

void singly_list_delete_val(SinglyNode** head, int val) {
    if (*head == NULL) return;
    SinglyNode* curr = *head;

    if (curr->data == val) {
        *head = curr->next;
        free(curr);  
        return;
    }

    while (curr->next != NULL && curr->next->data != val) {
        curr = curr->next;
    }

    if (curr->next != NULL) {
        SinglyNode* temp = curr->next; 
        curr->next = curr->next->next;  
        free(temp); 
    }
}

void singly_list_delete_at_idx(SinglyNode** head, int idx) {
    if (*head == NULL) return;
    SinglyNode* curr = *head;

    if (idx == 0) {
        *head = curr->next;
        free(curr);
        return;
    }

    for (int i = 0; curr != NULL && i < idx - 1; i++)
        curr = curr->next;

    if (curr == NULL || curr->next == NULL)
        return;

    SinglyNode* temp = curr->next; 
    curr->next = curr->next->next;  
    free(temp);
}

void singly_list_delete(SinglyNode** head) {
    SinglyNode* curr = *head;
    SinglyNode* nextNode;

    while (curr != NULL) {
        nextNode = curr->next;
        free(curr);
        curr = nextNode;
    }

    *head = NULL;
}

void print_singly_list(SinglyNode *head) {
    SinglyNode* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void singly_list_reverse(SinglyNode** head) {
    SinglyNode* a = (*head)->next;
    SinglyNode* b = *head;
    SinglyNode* temp;

    while (a != NULL) {
        temp = a->next;
        a->next = b;
        b = a;
        a = temp;
    }

    (*head)->next = NULL;
    *head = b;
}

DoublyNode* doubly_node_create(int x) {
    DoublyNode* newNode = (DoublyNode*)malloc(sizeof(DoublyNode));
    
    if (newNode == NULL) {
        printf("Malloc failed!\n");
        return NULL; 
    }

    newNode->data = x;    
    newNode->next = NULL; 
    newNode->prev = NULL; 

    return newNode; 
}

void doubly_list_insert_at_front(DoublyNode** head, int x) {
    DoublyNode* newNode = doubly_node_create(x);
    if (newNode == NULL) return;  

    newNode->next = *head; 
    newNode->prev = NULL; 

    if (*head != NULL) { 
        (*head)->prev = newNode;
    }

    *head = newNode;  
}


void doubly_list_insert_at_idx(DoublyNode** head, int idx, int x) {
    if (idx == 0) {
        doubly_list_insert_at_front(head, x);
        return;
    }

    DoublyNode* newNode = doubly_node_create(x);
    if (newNode == NULL) return;

    DoublyNode* temp = *head;
    for (int i = 0; i < idx - 1 && temp != NULL; i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Position out of range.\n");
        free(newNode);
        return;
    }

    newNode->next = temp->next;
    temp->next = newNode;

    if (temp->next != NULL) {
        temp->next->prev = newNode;
    }
}

void doubly_list_delete_head(DoublyNode** head) {
    if (*head == NULL) return;

    DoublyNode* temp = *head;
    *head = (*head)->next;

    if (*head != NULL) 
        (*head)->prev = NULL;

    free(temp);
}

void doubly_list_delete_val(DoublyNode** head, int val) {
    if (*head == NULL) return;

    DoublyNode* curr = *head;

    while (curr != NULL && curr->data != val) 
        curr = curr->next;

    if (curr == NULL) return;

    if (curr == *head) {
        *head = curr->next;
        if (*head != NULL) {
            (*head)->prev = NULL;
        }
    } else {
        curr->prev->next = curr->next;
        if (curr->next != NULL) {
            curr->next->prev = curr->prev;
        }
    }

    free(curr);
}

void doubly_list_delete_at_idx(DoublyNode **head, int idx) {
    if (*head == NULL) return;

    DoublyNode* curr = *head;
    
    if (idx == 0) {
        doubly_list_delete_head(head);
        return;
    }

    for (int i = 0; curr != NULL && i < idx; i++) {
        curr = curr->next;
    }

    if (curr == NULL) return;

    if (curr->prev != NULL) {
        curr->prev->next = curr->next;
    }
    if (curr->next != NULL) {
        curr->next->prev = curr->prev;
    }

    free(curr);
}

void doubly_list_delete(DoublyNode** head) {
    DoublyNode* curr = *head;
    DoublyNode* nextNode;

    while (curr != NULL) {
        nextNode = curr->next;
        free(curr);
        curr = nextNode;
    }

    *head = NULL;
}

void print_doubly_list(DoublyNode *head) {
    DoublyNode* temp = head;
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}
 
DoublyNode* doubly_list_create_sentinel() {
    DoublyNode* sentinel = (DoublyNode*)malloc(sizeof(DoublyNode));
    if (sentinel == NULL) {
        printf("Malloc failed!\n");
        return NULL;
    }

    sentinel->data = 0;
    sentinel->next = sentinel;
    sentinel->prev = sentinel;

    return sentinel;
}

void sentinel_doubly_list_insert_at_front(DoublyNode* sentinel, int x) {
    DoublyNode* newNode = doubly_node_create(x);
    if (newNode == NULL) return;

    newNode->next = sentinel->next;
    newNode->prev = sentinel;

    sentinel->next->prev = newNode;
    sentinel->next = newNode; 
}

void sentinel_doubly_list_insert_at_idx(DoublyNode* sentinel, int idx, int x) {
    DoublyNode* newNode = doubly_node_create(x);
    if (newNode == NULL) return;

    DoublyNode* temp = sentinel->next;
    for (int i = 0; i < idx && temp != sentinel; i++) 
        temp = temp->next;

    if (temp == sentinel) {
        printf("Position out of range.\n");
        free(newNode);
        return;
    }

    newNode->next = temp;
    newNode->prev = temp->prev;
    temp->prev->next = newNode;
    temp->prev = newNode;
}

void sentinel_doubly_list_delete_head(DoublyNode* sentinel) {
    if (sentinel->next == sentinel) return;

    DoublyNode* temp = sentinel->next;
    sentinel->next = temp->next;
    temp->next->prev = sentinel;

    free(temp);
}

void sentinel_doubly_list_delete_val(DoublyNode* sentinel, int val) {
    DoublyNode* temp = sentinel->next;

    while (temp != sentinel && temp->data != val)
        temp = temp->next;

    if (temp == sentinel) return;

    temp->prev->next = temp->next;

    if (temp->next != sentinel)
        temp->next->prev = temp->prev;

    free(temp);
}

void sentinel_doubly_list_delete_at_idx(DoublyNode* sentinel, int idx) {
    DoublyNode* temp = sentinel->next;

    for (int i = 0; temp != sentinel && i < idx; i++)
        temp = temp->next;

    if (temp == sentinel) return; 

    temp->prev->next = temp->next;

    if (temp->next != sentinel)
        temp->next->prev = temp->prev;

    free(temp);
}

void sentinel_doubly_list_delete(DoublyNode* sentinel) {
    DoublyNode* temp = sentinel->next;
    DoublyNode* nextNode;

    while (temp != sentinel) {
        nextNode = temp->next;
        free(temp);
        temp = nextNode;
    }

    sentinel->next = sentinel;
    sentinel->prev = sentinel;
}

void sentinel_print_doubly_list(DoublyNode* sentinel) {
    DoublyNode* temp = sentinel->next;
    while (temp != sentinel) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void doubly_lists_union(DoublyNode* l1, DoublyNode* l2) {
    if (l1 == NULL || l2 == NULL) { 
        printf("One or both lists are empty!\n");
        return;
    }

    l1->prev->next = l2->next;
    l2->next->prev = l1->prev;

    l1->prev = l2->prev;
    l2->prev->next = l1;

    l2->next = l2->prev = NULL;
} 

XorNode* xor(XorNode* a, XorNode* b) {
    return (XorNode*)((uintptr_t)a ^ (uintptr_t)b);
}

void xor_list_init(XorList* L) {
    L->head = NULL;
    L->nil = (XorNode*)malloc(sizeof(XorNode));
    L->nil->np = NULL;
}

XorNode* xor_list_search(XorList* L, int k) {
    XorNode* p = NULL;
    XorNode* x = L->head;

    while (x != NULL && x->key != k) {
        XorNode* temp = x;
        x = xor(p, x->np);
        p = temp;
    }

    return x;
} 

void xor_list_insert(XorList* L, int k) {
    XorNode* x = (XorNode*)malloc(sizeof(XorNode));
    x->key = k;
    x->np = xor(NULL, L->head);

    if (L->head != NULL) {
        L->head->np = xor(x, xor(NULL, L->head->np));
    }

    L->head = x;
}

void xor_list_delete(XorList* L, int k) {
    XorNode* p = NULL;
    XorNode* x = L->head;

    while (x != NULL && x->key != k) {
        XorNode* temp = x;
        x = xor(p, x->np);  
        p = temp;
    }

    if (x == NULL) {
        printf("Node with key %d not found\n", k);
        return;
    }

    if (x == L->head) {
        L->head = xor(NULL, x->np);
        if (L->head != NULL) {
            L->head->np = xor(NULL, xor(L->head->np, x));
        }
    } else {
        XorNode* prev = xor(p, x->np);
        XorNode* next = xor(x->np, p);

        if (prev != NULL) {
            prev->np = xor(xor(prev->np, x), next); 
        }
        if (next != NULL) {
            next->np = xor(xor(next->np, x), prev);  
        }

        free(x); 
    }
}


void print_xor_list(XorList* L) {
    XorNode* p = NULL;
    XorNode* x = L->head;
    while (x != NULL) {
        printf("%d -> ", x->key);
        XorNode* temp = x;
        x = xor(p, x->np);
        p = temp;
    }
    printf("NULL\n");
}