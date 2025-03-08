#include <stdio.h>
#include <stdlib.h>

#define QUEUE_SIZE 10

typedef struct {
    int value;
    int order;
} QueueElement;

typedef struct {
    QueueElement *data;
    int size;
    int capacity;
    int counter;
} PriorityQueue;

PriorityQueue* create_queue(
    int capacity
) {
    PriorityQueue *pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->data = (QueueElement*)malloc(capacity * sizeof(QueueElement));
    pq->size = 0;
    pq->capacity = capacity;
    pq->counter = 0;
    return pq;
}

int compare(
    QueueElement a, 
    QueueElement b
) {
    return a.order - b.order;  
}

void enqueue(
    PriorityQueue *pq, 
    int value
) {
    if (pq->size == pq->capacity) {
        printf("Queue is full!\n");
        return;
    }
    
    int i = pq->size++;
    pq->data[i].value = value;
    pq->data[i].order = pq->counter++;

    while (i > 0 && compare(pq->data[i], pq->data[(i - 1) / 2]) < 0) {
        QueueElement temp = pq->data[i];
        pq->data[i] = pq->data[(i - 1) / 2];
        pq->data[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

int dequeue(
    PriorityQueue *pq
) {
    if (pq->size == 0) {
        printf("Queue is empty!\n");
        return -1;
    }

    int value = pq->data[0].value;
    pq->data[0] = pq->data[--pq->size];

    int i = 0;
    while (2 * i + 1 < pq->size) {
        int left = 2 * i + 1, right = 2 * i + 2, min = left;
        if (right < pq->size && compare(pq->data[right], pq->data[left]) < 0)
            min = right;
        if (compare(pq->data[i], pq->data[min]) <= 0)
            break;
        QueueElement temp = pq->data[i];
        pq->data[i] = pq->data[min];
        pq->data[min] = temp;
        i = min;
    }

    return value;
}

void free_queue(
    PriorityQueue *pq
) {
    free(pq->data);
    free(pq);
}

int main() {
    PriorityQueue *pq = create_queue(QUEUE_SIZE);

    enqueue(pq, 10);
    enqueue(pq, 20);
    enqueue(pq, 30);

    printf("%d\n", dequeue(pq)); 
    printf("%d\n", dequeue(pq)); 
    printf("%d\n", dequeue(pq)); 

    free_queue(pq);
    return 0;
}