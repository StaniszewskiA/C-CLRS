#include <stdio.h>
#include <stdlib.h>

#define TASK 2

//----------Doubly with sentinel----------

typedef struct DoublyNode {
    int data;
    struct DoublyNode *next;
    struct DoublyNode *prev;
} DoublyNode;

DoublyNode* createDoublyNode(int x) {
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

DoublyNode* createSentinel() {
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

void insertDoublyAtBegin(DoublyNode* sentinel, int x) {
    DoublyNode* newNode = createDoublyNode(x);
    if (newNode == NULL) return;

    newNode->next = sentinel->next;
    newNode->prev = sentinel;

    sentinel->next->prev = newNode;
    sentinel->next = newNode; 
}

void insertDoublyAtIdx(DoublyNode* sentinel, int idx, int x) {
    DoublyNode* newNode = createDoublyNode(x);
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

void deleteHead(DoublyNode* sentinel) {
    if (sentinel->next == sentinel) return;

    DoublyNode* temp = sentinel->next;
    sentinel->next = temp->next;
    temp->next->prev = sentinel;

    free(temp);
}

void deleteNodeByVal(DoublyNode* sentinel, int val) {
    DoublyNode* temp = sentinel->next;

    while (temp != sentinel && temp->data != val)
        temp = temp->next;

    if (temp == sentinel) return;

    temp->prev->next = temp->next;

    if (temp->next != sentinel)
        temp->next->prev = temp->prev;

    free(temp);
}

void deleteNodeByIdx(DoublyNode* sentinel, int idx) {
    DoublyNode* temp = sentinel->next;

    for (int i = 0; temp != sentinel && i < idx; i++)
        temp = temp->next;

    if (temp == sentinel) return; 

    temp->prev->next = temp->next;

    if (temp->next != sentinel)
        temp->next->prev = temp->prev;

    free(temp);
}

void deleteList(DoublyNode* sentinel) {
    DoublyNode* temp;
    DoublyNode* nextNode;

    while (temp != sentinel) {
        nextNode = temp->next;
        free(temp);
        temp = nextNode;
    }

    sentinel->next = sentinel;
    sentinel->prev = sentinel;
}

void printDoublyList(DoublyNode* sentinel) {
    DoublyNode* temp = sentinel->next;
    while (temp != sentinel) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

//----------Union----------
void unionDoublyLists(DoublyNode* l1, DoublyNode* l2) {
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
//----------Main----------

int main(void) {
    switch (TASK) {
        case 1: {
            DoublyNode* sentinel = createSentinel();

            insertDoublyAtBegin(sentinel, 10);
            insertDoublyAtBegin(sentinel, 20);
            insertDoublyAtBegin(sentinel, 30);

            printf("List after insertions: ");
            printDoublyList(sentinel);  
            
            insertDoublyAtIdx(sentinel, 1, 25);
            printf("List after inserting 25 at index 1: ");
            printDoublyList(sentinel); 
            
            insertDoublyAtIdx(sentinel, 4, 5);
            printf("List after inserting 5 at index 4: ");
            printDoublyList(sentinel); 

            insertDoublyAtIdx(sentinel, 10, 100);  

            deleteHead(sentinel);
            printf("List after deleting head: ");
            printDoublyList(sentinel);

            deleteNodeByVal(sentinel, 25);
            printf("List after deleting 25 by value: ");
            printDoublyList(sentinel);

            deleteNodeByIdx(sentinel, 1);
            printf("List after deleting node at index 1: ");
            printDoublyList(sentinel);

            deleteList(sentinel);
            printf("List after deleting all nodes: ");
            printDoublyList(sentinel);

            break; 
        }
        case 2: {
            DoublyNode* L1 = createSentinel();
            DoublyNode* L2 = createSentinel();

            insertDoublyAtBegin(L1, 30);
            insertDoublyAtBegin(L1, 20);
            insertDoublyAtBegin(L1, 10);

            insertDoublyAtBegin(L2, 60);
            insertDoublyAtBegin(L2, 50);
            insertDoublyAtBegin(L2, 40);

            printf("L1 before union: ");
            printDoublyList(L1);
            
            printf("L2 before union: ");
            printDoublyList(L2);

            unionDoublyLists(L1, L2);

            printf("L1 after union: ");
            printDoublyList(L1);
        }
        default:
            printf("Invalid task\n");
            break;
    }

    return 0;
}
