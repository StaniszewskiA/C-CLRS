#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TASK 4

//----------Singly Linked List----------

typedef struct Node {
    int data;
    struct Node* next;
} SinglyNode;

SinglyNode* createSinglyNode(int data) {
    SinglyNode *newNode = (SinglyNode*)malloc(sizeof(SinglyNode));
    if (!newNode) {
        printf("Malloc failed");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertSinglyAtBegin(SinglyNode** head, int x) {
    SinglyNode* newNode = createSinglyNode(x);
    newNode->next = *head;
    *head = newNode;
}

void insertSinglyAtIdx(SinglyNode** head, int x, int idx) {
    SinglyNode* newNode = createSinglyNode(x);
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

void deleteHead(SinglyNode** head) {
    if (*head == NULL) return;

    SinglyNode* temp = *head;
    *head = (*head)->next;
    free(temp);
}

void deleteNodeByValue(SinglyNode** head, int val) {
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

void deleteNodeAtIdx(SinglyNode** head, int idx) {
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

void deleteList(SinglyNode** head) {
    SinglyNode* curr = *head;
    SinglyNode* nextNode;

    while (curr != NULL) {
        nextNode = curr->next;
        free(curr);
        curr = nextNode;
    }

    *head = NULL;
}

void printSinglyList(SinglyNode *head) {
    SinglyNode* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

//----------Stack----------

typedef struct Stack {
    SinglyNode* top;
    int size;
} Stack;

void initStack(Stack* stack) {
    stack->top = NULL;  
    stack->size = 0;
}

bool isStackEmpty(Stack* stack) {
    return stack->top == NULL;
}

void pushToStack(Stack* stack, int val) {
    SinglyNode* newNode = (SinglyNode*)malloc(sizeof(SinglyNode));
    if (!newNode) {
        printf("Malloc failed!\n");
        return;
    }
    newNode->data = val;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;
} 

int popFromStack(Stack* stack) {
    if (isStackEmpty(stack)) {
        printf("Stack underflow!\n");
        return 01;
    }
    SinglyNode* temp = stack->top;
    int poppedVal = temp->data;
    stack->top = stack->top->next;
    free(temp);
    stack->size--;

    return poppedVal;
}

int peek(Stack *stack) {
    if (isStackEmpty(stack)) {
        printf("Stack is empty!\n");
        return -1;
    }
    
    return stack->top->data;
}

int getSize(Stack* stack) {
    return stack->size;
}

void printStack(Stack* stack) {
    if (isStackEmpty(stack)) {
        printf("Stack is empty\n");
        return;
    }
    SinglyNode* current = stack->top;
    printf("Stack: ");
    while (current) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

//----------Deque----------

typedef struct Deque {
    SinglyNode* head;
    SinglyNode* tail;
    int size;
} Deque;

void initDeque(Deque* dq) {
    dq->head = dq->tail = NULL;
    dq->size = 0;
}

bool isDequeEmpty(Deque *dq) {
    return dq->size == 0;
}

void enqueue(Deque *dq, int x) {
    SinglyNode* newNode = createSinglyNode(x);
    if (!newNode) {
        printf("Malloc failed!\n");
        return;
    }

    if (isDequeEmpty(dq)) {
        dq->head = dq->tail = newNode;
    } else {
        dq->tail->next = newNode;
        dq->tail = newNode;
    }
    dq->size++;
}

int dequeue(Deque *dq) {
    if (isDequeEmpty(dq)) {
        printf("Deque is empty!\n");
        return -1;
    }

    SinglyNode* temp = dq->head;
    int dequedVal = temp->data;
    dq->head = dq->head->next;
    free(temp);

    if (dq->head == NULL) // Reset tail
        dq->tail = NULL;

    dq->size--;
    return dequedVal;
}

int peekFront(Deque* dq) {
    if (isDequeEmpty(dq)) {
        printf("Deque is empty!\n");
        return -1;
    }
    return dq->head->data;
}

int peekRear(Deque* dq) {
    if (isDequeEmpty(dq)) {
        printf("Deque is empty!\n");
        return -1;
    }
    return dq->tail->data;
}

int getDequeSize(Deque* dq) {
    return dq->size;
}

void printDeque(Deque* dq) {
    if (isDequeEmpty(dq)) {
        printf("Deque is empty!\n");
        return;
    }
    SinglyNode* temp = dq->head;
    printf("Deque: ");
    while (temp) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void deleteDeque(Deque* dq) {
    while (!isDequeEmpty(dq)) {
        dequeue(dq);
    }
}

//----------Reverse----------
void reverseSinglyList(SinglyNode** head) {
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

//----------Main----------

int main(void) {
    switch (TASK) {
        case 1: {
            SinglyNode* head = NULL;

            insertSinglyAtBegin(&head, 10);
            insertSinglyAtBegin(&head, 20);
            insertSinglyAtBegin(&head, 30);
            printSinglyList(head);

            deleteHead(&head);
            printSinglyList(head);

            deleteNodeByValue(&head, 20);
            printSinglyList(head);
            
            deleteList(&head);
            printSinglyList(head);

            break; 
        }
        case 2: {
            Stack stack;
            initStack(&stack);

            pushToStack(&stack, 100);
            pushToStack(&stack, 200);
            pushToStack(&stack, 300);

            printStack(&stack); 

            printf("Popped: %d\n", popFromStack(&stack)); 
            printf("Top element: %d\n", peek(&stack)); 

            printStack(&stack);
            printf("Stack size: %d\n", getSize(&stack)); 

            break;
        }
        case 3: {
            Deque dq;
            initDeque(&dq);

            enqueue(&dq, 10);
            enqueue(&dq, 20);
            enqueue(&dq, 30);

            printDeque(&dq);
            printf("Front: %d, Rear: %d\n", peekFront(&dq), peekRear(&dq));

            printf("Dequeued: %d\n", dequeue(&dq));

            deleteDeque(&dq);
            printDeque(&dq);

            break;
        }
        case 4: {
            SinglyNode* head = NULL;

            insertSinglyAtBegin(&head, 10);
            insertSinglyAtBegin(&head, 20);
            insertSinglyAtBegin(&head, 30);
            printSinglyList(head);

            reverseSinglyList(&head);
            printSinglyList(head);

            break;
        }
        default:
            printf("Invalid task\n");
            break;
    }

    return 0;
}
