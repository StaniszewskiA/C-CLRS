#include <stdio.h>
#include <stdlib.h>

#define TASK 1

//----------Doubly Linked List----------

typedef struct DoublyNode {
    int data;
    struct DoublyNode* next;
    struct DoublyNode* prev;
} DoublyNode;

DoublyNode* createDoubleNode(int x) {
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

void insertDoublyAtBegin(DoublyNode** head, int x) {
    DoublyNode* newNode = createDoubleNode(x);
    if (newNode == NULL) return;  

    newNode->next = *head; 
    newNode->prev = NULL; 

    if (*head != NULL) { 
        (*head)->prev = newNode;
    }

    *head = newNode;  
}


void insertDoublyAtIdx(DoublyNode** head, int idx, int x) {
    if (idx == 0) {
        insertDoublyAtBegin(head, x);
        return;
    }

    DoublyNode* newNode = createDoubleNode(x);
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

void deleteHead(DoublyNode** head) {
    if (*head == NULL) return;

    DoublyNode* temp = *head;
    *head = (*head)->next;

    if (*head != NULL) 
        (*head)->prev = NULL;

    free(temp);
}

void deleteNodeByVal(DoublyNode** head, int val) {
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

void deleteNodeByIdx(DoublyNode **head, int idx) {
    if (*head == NULL) return;

    DoublyNode* curr = *head;
    
    if (idx == 0) {
        deleteHead(head);
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

void deleteList(DoublyNode** head) {
    DoublyNode* curr = *head;
    DoublyNode* nextNode;

    while (curr != NULL) {
        nextNode = curr->next;
        free(curr);
        curr = nextNode;
    }

    *head = NULL;
}

void printDoublyList(DoublyNode *head) {
    DoublyNode* temp = head;
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}
 
//----------Main----------

int main(void) {
    switch (TASK) {
        case 1: {
            DoublyNode* head = NULL;

            insertDoublyAtBegin(&head, 10);
            insertDoublyAtBegin(&head, 20);
            insertDoublyAtBegin(&head, 30);
            
            printf("List after insertions: ");
            printDoublyList(head);  
            
            insertDoublyAtIdx(&head, 1, 25);
            printf("List after inserting 25 at index 1: ");
            printDoublyList(head); 
            
            insertDoublyAtIdx(&head, 4, 5);
            printf("List after inserting 5 at index 4: ");
            printDoublyList(head); 
        
        
            insertDoublyAtIdx(&head, 10, 100);  
        
            return 0;

            break; 
        }
        case 2: {
            break;
        }
        default:
            printf("Invalid task\n");
            break;
    }

    return 0;
}
