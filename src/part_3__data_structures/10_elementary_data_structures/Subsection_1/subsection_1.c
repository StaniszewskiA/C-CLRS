#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TASK 5
#define MAX_SIZE 10

//===========================================================//

typedef struct {
    int arr[MAX_SIZE];
    int topT;
    int topR;
} TwoStacks;

void initTwoStacks(TwoStacks* stacks) {
    stacks->topT = -1;
    stacks->topR = MAX_SIZE;
}

void PUSH_T(TwoStacks* stacks, int x) {
    if (stacks->topT + 1 == stacks->topR) {
        printf("Error: Overflow in stack T\n");
        return;
    } else {
        stacks->topT = stacks->topT + 1;
        stacks->arr[stacks->topT] = x;
    }
}

void PUSH_R(TwoStacks* stacks, int x) {
    if (stacks->topR - 1 == stacks->topT) {
        printf("Error: Overflow in stack R\n");
        return;
    } else {
        stacks->topR = stacks->topR - 1;
        stacks->arr[stacks->topR] = x;
    }
}

int POP_T(TwoStacks* stacks) {
    if (stacks->topT == -1) {
        printf("Error: Underflow in stack T\n");
        return -1;
    } else {
        int val = stacks->arr[stacks->topT];
        stacks->topT = stacks->topT - 1;
        return val;
    }
}

int POP_R(TwoStacks* stacks) {
    if (stacks->topR == MAX_SIZE) {
        printf("Error: Underflow in stack R\n");
        return -1;  
    } else {
        int val = stacks->arr[stacks->topR];
        stacks->topR = stacks->topR + 1;
        return val;
    }
}

//===========================================================//

typedef struct {
    int arr[MAX_SIZE];
    int front;
    int rear;
    int size;
} Queue;

void initQueue(Queue* q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

bool isQueueEmpty(Queue *q) {
    return (q->size == 0);
}

bool isQueueFull(Queue *q) {
    return (q->size == MAX_SIZE);
}

void enqueue(Queue *q, int val) {
    if (isQueueFull(q)) {
        printf("Error: Queue overflow\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX_SIZE;
    q->arr[q->rear] = val;
    q->size++;
    printf("Enqueued %d\n", val);
}

int dequeue(Queue *q) {
    if (isQueueEmpty(q)) {
        printf("Error: Queue underflow\n");
        return -1;  
    }
    int val = q->arr[q->front];
    q->front = (q->front + 1) % MAX_SIZE;
    q->size--;
    return val; 
}

void displayQueue(Queue *q) {
    if (isQueueEmpty(q)) {
        printf("Qeueu is empty\n");
        return;
    }
    printf("Queue elements: ");
    int count = q->size;
    int idx = q->front;
    while (count--) {
        printf("%d ", q->arr[idx]);
        idx = (idx + 1) % MAX_SIZE;
    }
    printf("\n");
}

//===========================================================//
typedef struct {
    int arr[MAX_SIZE];
    int front;
    int rear;
    int size;
} Deque;

void initDeque(Deque *dq) {
    dq->front = -1;
    dq->rear = 0;
    dq->size = 0;
}

bool isDequeFull(Deque *dq) {
    return (dq->size == MAX_SIZE);
}

bool isDequeEmpty(Deque *dq) {
    return (dq->size == 0);
}

void enqueueFront(Deque *dq, int x) {
    if (isDequeFull(dq)) {
        printf("Error: Deque overflow\n");
        return;
    }
    if (dq->front == -1) {
        dq->front = dq->rear = 0;
    } else {
        dq->front = (dq->front - 1 + MAX_SIZE) % MAX_SIZE;
    }
    dq->arr[dq->front] = x;
    dq->size++;
    printf("Inserted %d at front\n", x);
}

void enqueueRear(Deque *dq, int x) {
    if (isDequeFull(dq)) {
        printf("Error: Deque overflow\n");
        return;
    }
    if (dq->rear == -1) {
        dq->front = dq->rear = 0;
    } else {
        dq->rear = (dq->rear + 1) % MAX_SIZE;
    }
    dq->arr[dq->rear] = x;
    dq->size++;
    printf("Inserted %d at rear\n", x);
}

int dequeueFront(Deque *dq) {
    if (isDequeEmpty(dq)) {
        printf("Error: Deque underflow\n");
        return -1;
    }
    int val = dq->arr[dq->front];
    if (dq->front == dq->rear) {
        dq->front = dq->rear = -1;
    } else {
        dq->front = (dq->front + 1) % MAX_SIZE;
    }
    dq->size--;
    return val;
}

int dequeueRear(Deque *dq) {
    if (isDequeEmpty(dq)) {
        printf("Error: Deque underflow\n");
        return -1;
    }
    int val = dq->arr[dq->rear];
    if (dq->front == dq->rear) {
        dq->front = dq->rear = -1;
    } else {
        dq->rear = (dq->rear - 1 + MAX_SIZE) % MAX_SIZE;
    }
    dq->size--;
    return val;
} 

void displayDeque(Deque *dq) {
    if (isDequeEmpty(dq)) {
        printf("Deque is empty\n");
        return;
    }
    printf("Deque elements: ");
    int idx = dq->front;
    for (int i = 0; i < dq->size; i++) {
        printf("%d ", dq->arr[idx]);
        idx = (idx + 1) % MAX_SIZE;
    }
    printf("\n");
}

//===========================================================//
typedef struct {
    int arr[MAX_SIZE];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

bool isStackEmpty(Stack *s) {
    return s->top == -1;
}

bool isStackFull(Stack *s) {
    return s->top == MAX_SIZE - 1;
}

void pushToStack(Stack *s, int x) {
    if (isStackFull(s)) {
        printf("Error: Stack overflow\n");
        return;
    }
    s->arr[++s->top] = x;
}

int popFromStack(Stack *s) {
    if (isStackEmpty(s)) {
        printf("Error: Stack underflow\n");
        return -1;
    }
    return s->arr[s->top--];
}

typedef struct {
    Stack s1;
    Stack s2;
} QueueWithStacks;

void initQueueWithStacks(QueueWithStacks *qws) {
    initStack(&qws->s1);
    initStack(&qws->s2);
}

void enqueueQueueWithStacks(QueueWithStacks *qws, int x) {
    pushToStack(&qws->s1, x);
}

int dequeueQueueWithStacks(QueueWithStacks *qws) {
    if (isStackEmpty(&qws->s2)) {
        while (!isStackEmpty(&qws->s1)) {
            pushToStack(&qws->s2, popFromStack(&qws->s1));
        }
    }
    if (isStackEmpty(&qws->s2)) {
        printf("Error: Queue underflow\n");
        return -1;
    }
    return popFromStack(&qws->s2);
}

//===========================================================//
typedef struct {
    Queue q1;
    Queue q2;
} StackWithQueues;

void initStackWithQueues(StackWithQueues* swq) {
    initQueue(&swq->q1);
    initQueue(&swq->q2);
}

void pushToSwq(StackWithQueues* swq, int x) {
    enqueue(&swq->q1, x); 
}

int popFromSwq(StackWithQueues* swq) {
    if (isQueueEmpty(&swq->q1)) {
        printf("Error: Stack underflow\n");
        return -1;
    }

    while (swq->q1.size > 1) {
        int val = dequeue(&swq->q1);
        enqueue(&swq->q2, val);
    }

    int top = dequeue(&swq->q1);

    Queue temp = swq->q1;
    swq->q1 = swq->q2;
    swq->q2 = temp;

    return top;
}

//===========================================================//

int main(void) {
    switch (TASK) {
        case 1: {
            TwoStacks stacks;
            initTwoStacks(&stacks);

            PUSH_T(&stacks, 10);
            PUSH_T(&stacks, 20);
            PUSH_R(&stacks, 30);
            PUSH_R(&stacks, 40);

            printf("POP_T: %d\n", POP_T(&stacks));
            printf("POP_R: %d\n", POP_R(&stacks));
            printf("POP_T: %d\n", POP_T(&stacks));
            printf("POP_R: %d\n", POP_R(&stacks));

            PUSH_T(&stacks, 50);
            PUSH_T(&stacks, 60);
            PUSH_R(&stacks, 70);
            PUSH_R(&stacks, 80);
            PUSH_T(&stacks, 90); 
            PUSH_R(&stacks, 100);

            break; 
        }

        case 2: {
            Queue q;
            initQueue(&q);

            enqueue(&q, 10);
            enqueue(&q, 20);
            enqueue(&q, 30);
            enqueue(&q, 40);
            enqueue(&q, 50);

            displayQueue(&q); 

            printf("Dequeued: %d\n", dequeue(&q));
            printf("Dequeued: %d\n", dequeue(&q));

            displayQueue(&q);

            enqueue(&q, 60);
            enqueue(&q, 70);

            displayQueue(&q);
            
            break; 
        }

        case 3: {
            Deque dq;
            initDeque(&dq);

            enqueueRear(&dq, 10);
            enqueueRear(&dq, 20);
            enqueueFront(&dq, 5);
            enqueueFront(&dq, 1);
            displayDeque(&dq);

            printf("Dequeued from front: %d\n", dequeueFront(&dq));
            printf("Dequeued from rear: %d\n", dequeueRear(&dq));

            displayDeque(&dq);

            enqueueRear(&dq, 30);
            enqueueFront(&dq, 0);
            displayDeque(&dq);

            break;
        }

        case 4: {
            QueueWithStacks qws;
            initQueueWithStacks(&qws); 
            
            enqueueQueueWithStacks(&qws, 1);
            enqueueQueueWithStacks(&qws, 2);
            enqueueQueueWithStacks(&qws, 3);
            
            printf("Dequeued: %d\n", dequeueQueueWithStacks(&qws));
            printf("Dequeued: %d\n", dequeueQueueWithStacks(&qws));
            
            enqueueQueueWithStacks(&qws, 4);  
            enqueueQueueWithStacks(&qws, 5);  
            
            printf("Dequeued: %d\n", dequeueQueueWithStacks(&qws));
            printf("Dequeued: %d\n", dequeueQueueWithStacks(&qws));
            printf("Dequeued: %d\n", dequeueQueueWithStacks(&qws));
        
            break;
        }

        case 5: {
            StackWithQueues swq;
            initStackWithQueues(&swq);

            pushToSwq(&swq, 10);
            pushToSwq(&swq, 20);
            pushToSwq(&swq, 30);

            printf("Popped: %d\n", popFromSwq(&swq));  
            printf("Popped: %d\n", popFromSwq(&swq));  

            pushToSwq(&swq, 40);

            printf("Popped: %d\n", popFromSwq(&swq));

            break;
        }

        default:
            printf("Invalid TASK\n");
            break;
    }

    return 0;
}