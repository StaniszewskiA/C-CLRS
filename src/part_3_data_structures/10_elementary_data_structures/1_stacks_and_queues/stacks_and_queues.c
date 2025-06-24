#include "../../../../include/part_3_data_structures/10_elementary_data_structures/elementary_data_structures.h"
#include <stdio.h>

//================ TwoStacks ================//
void two_stacks_init(TwoStacks* stacks) {
    stacks->topT = -1;
    stacks->topR = MAX_STACK_SIZE;
}

void two_stacks_push_t(TwoStacks* stacks, int x) {
    if (stacks->topT + 1 == stacks->topR) {
        printf("Error: Overflow in stack T\n");
        return;
    }
    stacks->arr[++stacks->topT] = x;
}

void two_stacks_push_r(TwoStacks* stacks, int x) {
    if (stacks->topR - 1 == stacks->topT) {
        printf("Error: Overflow in stack R\n");
        return;
    }
    stacks->arr[--stacks->topR] = x;
}

int two_stacks_pop_t(TwoStacks* stacks) {
    if (stacks->topT == -1) {
        printf("Error: Underflow in stack T\n");
        return -1;
    }
    return stacks->arr[stacks->topT--];
}

int two_stacks_pop_r(TwoStacks* stacks) {
    if (stacks->topR == MAX_STACK_SIZE) {
        printf("Error: Underflow in stack R\n");
        return -1;
    }
    return stacks->arr[stacks->topR++];
}

//================ Queue ================//
void queue_init(Queue* q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

int queue_is_empty(Queue* q) {
    return q->size == 0;
}

int queue_is_full(Queue* q) {
    return q->size == MAX_STACK_SIZE;
}

void enqueue(Queue *q, int val) {
    if (queue_is_full(q)) {
        printf("Error: Queue overflow\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX_STACK_SIZE;
    q->arr[q->rear] = val;
    q->size++;
}

int dequeue(Queue *q) {
    if (queue_is_empty(q)) {
        printf("Error: Queue underflow\n");
        return -1;
    }
    int val = q->arr[q->front];
    q->front = (q->front + 1) % MAX_STACK_SIZE;
    q->size--;
    return val;
}

void print_queue(Queue *q) {
    if (queue_is_empty(q)) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue elements: ");
    int count = q->size;
    int idx = q->front;
    while (count--) {
        printf("%d ", q->arr[idx]);
        idx = (idx + 1) % MAX_STACK_SIZE;
    }
    printf("\n");
}

//================ Deque ================//
void deque_init(Deque *dq) {
    dq->front = -1;
    dq->rear = 0;
    dq->size = 0;
}

int deque_is_empty(Deque *dq) {
    return dq->size == 0;
}

int deque_is_full(Deque *dq) {
    return dq->size == MAX_STACK_SIZE;
}

void enqueue_front(Deque *dq, int x) {
    if (deque_is_full(dq)) {
        printf("Error: Deque overflow\n");
        return;
    }
    if (dq->front == -1) {
        dq->front = dq->rear = 0;
    } else {
        dq->front = (dq->front - 1 + MAX_STACK_SIZE) % MAX_STACK_SIZE;
    }
    dq->arr[dq->front] = x;
    dq->size++;
}

void enqueue_rear(Deque *dq, int x) {
    if (deque_is_full(dq)) {
        printf("Error: Deque overflow\n");
        return;
    }
    if (dq->rear == -1) {
        dq->front = dq->rear = 0;
    } else {
        dq->rear = (dq->rear + 1) % MAX_STACK_SIZE;
    }
    dq->arr[dq->rear] = x;
    dq->size++;
}

int dequeue_front(Deque *dq) {
    if (deque_is_empty(dq)) {
        printf("Error: Deque underflow\n");
        return -1;
    }
    int val = dq->arr[dq->front];
    if (dq->front == dq->rear) {
        dq->front = dq->rear = -1;
    } else {
        dq->front = (dq->front + 1) % MAX_STACK_SIZE;
    }
    dq->size--;
    return val;
}

int dequeue_rear(Deque *dq) {
    if (deque_is_empty(dq)) {
        printf("Error: Deque underflow\n");
        return -1;
    }
    int val = dq->arr[dq->rear];
    if (dq->front == dq->rear) {
        dq->front = dq->rear = -1;
    } else {
        dq->rear = (dq->rear - 1 + MAX_STACK_SIZE) % MAX_STACK_SIZE;
    }
    dq->size--;
    return val;
}

void deque_print(Deque *dq) {
    if (deque_is_empty(dq)) {
        printf("Deque is empty\n");
        return;
    }
    printf("Deque elements: ");
    int idx = dq->front;
    for (int i = 0; i < dq->size; i++) {
        printf("%d ", dq->arr[idx]);
        idx = (idx + 1) % MAX_STACK_SIZE;
    }
    printf("\n");
}

int deque_peek_front(Deque* dq) {
    if (deque_is_empty(dq)) {
        printf("Deque is empty\n");
        return -1;
    }
    return dq->arr[dq->front];
}

int deque_peek_rear(Deque* dq) {
    if (deque_is_empty(dq)) {
        printf("Deque is empty\n");
        return -1;
    }
    return dq->arr[dq->rear];
}

int deque_get_size(Deque* dq) {
    return dq->size;
}

void print_deque(Deque* dq) {
    deque_print(dq);
}

void deque_delete(Deque* dq) {
    dq->front = -1;
    dq->rear = 0;
    dq->size = 0;
}

//================ Stack ================//
void stack_init(Stack *s) {
    s->top = -1;
}

int stack_is_empty(Stack *s) {
    return s->top == -1;
}

int stack_is_full(Stack *s) {
    return s->top == MAX_STACK_SIZE - 1;
}

void stack_push(Stack *s, int x) {
    if (stack_is_full(s)) {
        printf("Error: Stack overflow\n");
        return;
    }
    s->arr[++s->top] = x;
}

int stack_pop(Stack *s) {
    if (stack_is_empty(s)) {
        printf("Error: Stack underflow\n");
        return -1;
    }
    return s->arr[s->top--];
}

int stack_peek(Stack *s) {
    if (stack_is_empty(s)) {
        printf("Stack is empty\n");
        return -1;
    }
    return s->arr[s->top];
}

int stack_get_size(Stack* s) {
    return s->top + 1;
}

void print_stack(Stack* s) {
    if (stack_is_empty(s)) {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack elements: ");
    for (int i = 0; i <= s->top; i++) {
        printf("%d ", s->arr[i]);
    }
    printf("\n");
}

//================ QueueWithStacks ================//
void queue_with_stack_init(QueueWithStacks *qws) {
    stack_init(&qws->s1);
    stack_init(&qws->s2);
}

void queue_with_stacks_enqueue(QueueWithStacks *qws, int x) {
    stack_push(&qws->s1, x);
}

int queue_with_stacks_dequeque(QueueWithStacks *qws) {
    if (stack_is_empty(&qws->s2)) {
        while (!stack_is_empty(&qws->s1)) {
            stack_push(&qws->s2, stack_pop(&qws->s1));
        }
    }
    if (stack_is_empty(&qws->s2)) {
        printf("Error: Queue underflow\n");
        return -1;
    }
    return stack_pop(&qws->s2);
}

//================ StackWithQueues ================//
void stack_with_queues_init(StackWithQueues* swq) {
    queue_init(&swq->q1);
    queue_init(&swq->q2);
}

void stack_with_queues_push(StackWithQueues* swq, int x) {
    enqueue(&swq->q1, x);
}

int stack_with_queues_pop(StackWithQueues* swq) {
    if (queue_is_empty(&swq->q1)) {
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
