#include "part_4_advanced_design_and_analysis_techniques/15_greedy_algorithms/greedy_algorithms.h"

PagedNode* paged_node_create(unsigned pageNum) {
    PagedNode* temp = (PagedNode*)malloc(sizeof(PagedNode));
    temp->pageNum = pageNum;
    temp->prev = temp->next = NULL;
    return temp;
}

Queue* queue_init(int numOfFrames) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->count = 0;
    q->front = q->rear = NULL;
    q->numOfFrames = numOfFrames;

    return q;
}

Hash* hash_init(int capacity) {
    Hash* hash = (Hash*)malloc(sizeof(Hash));
    hash->capacity = capacity;
    hash->nodeArray = (PagedNode**)malloc(hash->capacity * sizeof(PagedNode*));
    int i;

    for (i = 0; i < hash->capacity; ++i) hash->nodeArray[i] = NULL;

    return hash;
}

int are_all_frames_full(Queue* q) {
    return q->count == q->numOfFrames;
}

int queue_is_empty(Queue* q) {
    return q->rear == NULL;
}

void dequeue(Queue* q) {
    if (queue_is_empty(q)) return;
    if (q->front == q->rear) q->front = NULL;   

    PagedNode* temp = q->rear;
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

    PagedNode* temp = paged_node_create(pageNum);
    temp->next = q->front;

    if (queue_is_empty(q)) q->rear = q->front = temp;
    else {
        q->front->prev = temp;
        q->front = temp;
    }

    hash->nodeArray[pageNum] = temp;

    q->count++;
}

void ref_page(Queue* q, Hash* hash, unsigned pageNum) {
    PagedNode* page = hash->nodeArray[pageNum];

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

