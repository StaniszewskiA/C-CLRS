#include <stdio.h>
#include <stdlib.h>

#define Q_CAPACITY 4
#define HASH_CAPACITY 10

typedef struct Node {
    struct Node *prev, *next;
    unsigned pageNum;
} Node;

typedef struct Queue {
    unsigned count;
    unsigned numOfFrames;
    Node *front, *rear;
} Queue;

typedef struct Hash {
    int capacity;
    Node** nodeArray;
} Hash;

Node* new_node(unsigned pageNum) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->pageNum = pageNum;
    temp->prev = temp->next = NULL;
    return temp;
}

Queue* init_queue(int numOfFrames) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->count = 0;
    q->front = q->rear = NULL;
    q->numOfFrames = numOfFrames;

    return q;
}

Hash* init_hash(int capacity) {
    Hash* hash = (Hash*)malloc(sizeof(Hash));
    hash->capacity = capacity;
    hash->nodeArray = (Node**)malloc(hash->capacity * sizeof(Node*));
    int i;

    for (i = 0; i < hash->capacity; ++i) hash->nodeArray[i] = NULL;

    return hash;
}

int are_all_frames_full(Queue* q) {
    return q->count == q->numOfFrames;
}

int is_queue_empty(Queue* q) {
    return q->rear == NULL;
}

void dequeue(Queue* q) {
    if (is_queue_empty(q)) return;
    if (q->front == q->rear) q->front = NULL;   

    Node* temp = q->rear;
    q->rear = q->rear->prev;

    if (q->rear) q->rear->next = NULL;

    free(temp);

    q->count--;
}

void enqueue(Queue* q, Hash* hash, unsigned pageNum) {
    if (are_all_frames_full(q)) {
        hash->nodeArray[q->rear->pageNum] = NULL;
        dequeue(q);
    }

    Node* temp = new_node(pageNum);
    temp->next = q->front;

    if (is_queue_empty(q)) q->rear = q->front = temp;
    else {
        q->front->prev = temp;
        q->front = temp;
    }

    hash->nodeArray[pageNum] = temp;

    q->count++;
}

void ref_page(Queue* q, Hash* hash, unsigned pageNum) {
    Node* page = hash->nodeArray[pageNum];

    if (page == NULL) enqueue(q, hash, pageNum);

    else if (page != q->front) {
        if (page->next) page->next->prev = page->prev;
        if (page == q->rear) {
            q->rear = page->prev;
            q->rear->next = NULL;
        }

        page->next = q->front;
        page->prev = NULL;
        page->next->prev = page;

        q->front = page;
    }
}


int main(void) {
    Queue* q = init_queue(Q_CAPACITY);
    Hash* hash = init_hash(HASH_CAPACITY);

    ref_page(q, hash, 1);
    ref_page(q, hash, 2);
    ref_page(q, hash, 3);
    ref_page(q, hash, 1);
    ref_page(q, hash, 4);
    ref_page(q, hash, 5);

    printf ("%d ", q->front->pageNum);
    printf ("%d ", q->front->next->pageNum);
    printf ("%d ", q->front->next->next->pageNum);
    printf ("%d ", q->front->next->next->next->pageNum);

    return 0;
}