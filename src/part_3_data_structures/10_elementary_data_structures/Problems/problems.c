#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TASK 3

//----------Binomial Heap----------
typedef struct BinomialNode {
    int key;
    int degree;
    struct BinomialNode* parent;
    struct BinomialNode* child;
    struct BinomialNode* sibling;
} BinomialNode;

typedef struct BinomialHeap {
    BinomialNode* head;
} BinomialHeap;

BinomialNode* createNode(int key) {
    BinomialNode* newNode = (BinomialNode*)malloc(sizeof(BinomialNode));
    newNode->key = key;
    newNode->degree = 0;
    newNode->parent = newNode->child = newNode->sibling = NULL;
    return newNode;
}

BinomialNode* mergeTrees(BinomialNode* b1, BinomialNode* b2) {
    if (b1->key > b2->key) {
        BinomialNode* temp = b1;
        b1 = b2;
        b2 = temp;
    }
    b2->parent = b1;
    b2->sibling = b1->child;
    b2->sibling = b1->child;
    b1->child = b2;
    b1->degree++;
    return b1;
}

BinomialNode* mergeHeaps(BinomialNode* h1, BinomialNode* h2) {
    if (!h1) return h2;
    if (!h2) return h1;

    BinomialNode* newHead = NULL;
    BinomialNode** pos = &newHead;

    while (h1 && h2) {
        if (h1->degree <= h2->degree) {
            *pos = h1;
            h1 = h1->sibling;
        } else {
            *pos = h2;
            h2 = h2->sibling;
        }
        pos = &((*pos)->sibling);
    }
    *pos = h1 ? h1 : h2;
    return newHead;
}

BinomialHeap* unionHeaps(BinomialHeap* h1, BinomialHeap* h2) {
    BinomialHeap* newHeap = (BinomialHeap*)malloc(sizeof(BinomialHeap));
    newHeap->head = mergeHeaps(h1->head, h2->head);
    if (!newHeap->head) return newHeap;

    BinomialNode *prev = NULL, *curr = newHeap->head, *next = curr->sibling;
    while (next) {
        if ((curr->degree != next->degree) || (next->sibling && next->sibling->degree == curr->degree)) {
            prev = curr;
            curr = next;
        } else {
            if (curr->key <= next->key) {
                curr->sibling = next->sibling;
                mergeTrees(curr, next);
            } else {
                if (!prev) newHeap->head = next;
                else prev->sibling = next;
                mergeTrees(next, curr);
                curr = next;
            }
        }
        next = curr->sibling;
    }
    return newHeap;
}

void insert(BinomialHeap* heap, int key) {
    BinomialHeap* tempHeap = (BinomialHeap*)malloc(sizeof(BinomialHeap));
    tempHeap->head = createNode(key);
    *heap = *unionHeaps(heap, tempHeap);
}

int extractMin(BinomialHeap* heap) {
    if (!heap->head) return INT_MAX;
    
    BinomialNode* minNode = heap->head;
    BinomialNode* prevMin = NULL;
    BinomialNode* curr = heap->head;
    BinomialNode* prev = NULL;

    while (curr->sibling) {
        if (curr->sibling->key < minNode->key) {
            minNode = curr->sibling;
            prevMin = curr;
        }
        curr = curr->sibling;
    }

    if (prevMin) prevMin->sibling = minNode->sibling;
    else heap->head = minNode->sibling;

    BinomialNode* child = minNode->child;
    BinomialNode* prevChild = NULL;

    while (child) {
        BinomialNode* next = child->sibling;
        child->sibling = prevChild;
        child->parent = NULL;
        prevChild = child;
        child = next;
    }

    BinomialHeap tempHeap = {prevChild};
    *heap = *unionHeaps(heap, &tempHeap);

    int minKey = minNode->key;
    free(minNode);

    return minKey;
}

void printHeap(BinomialNode* node) {
    while (node) {
        printf("B%d: %d \n", node->degree, node->key);
        node = node->sibling;
    }
    printf("\n");
}

//----------Compact List Search----------
#include <time.h>

#define NIL -1

typedef struct Node {
    int key;
    int next;
} Node;

int random_idx(int n) {
    return (rand() % n);
}

int compact_list_search(Node L[], int head, int n, int k) {
    int i = head;
    while (i != NIL && L[i].key < k) {
        int j = random_idx(n);
        if (L[i].key < L[j].key && L[j].key <= k) {
            i = j;
            if (L[i].key == k) {
                return i;
            }
        }
        i = L[i].next;
    } 
    return (i == NIL || L[i].key > k) ? NIL : i;
}

//----------Compact List Search Prim----------
int compact_list_search_prim(Node L[], int head, int n, int k, int t) {
    int i = head;
    for (int q = 1; q <= t; q++) {
        int j = random_idx(n);
        if (L[i].key < L[j].key && L[j].key <= k) {
            i = j;
            if (L[i].key == k) {
                return i;
            } 
        }
        while (i != NIL && L[i].key < k) {
            i = L[i].next;
        }
    }
    return (i == NIL || L[i].key > k) ? NIL : i;
}

int main(void) {
    switch (TASK)
    {
    case 1: {
        BinomialHeap heap = {NULL};
        insert(&heap, 10);
        insert(&heap, 20);
        insert(&heap, 30);
        insert(&heap, 40);
        insert(&heap, 50);
        insert(&heap, 60);

        printf("Heap before extract-min:\n");
        printHeap(heap.head);

        printf("Extracted min: %d\n", extractMin(&heap));

        printf("Heap after extract-min:\n");
        printHeap(heap.head);
        break;
    }
    case 2: {
        srand(time(NULL));

        Node L[] = {
            {3, 1},
            {7, 2},
            {10, 3},
            {15, 4},
            {20, NIL}
        };

        int head = 0;
        int n = 5;
        int k = 10;
        int result = compact_list_search(L, head, n, k);
        
        if (result != NIL) {
            printf("Element %d found at index %d\n", k, result);
        } else {
            printf("Element %d not found\n", k);
        }
        
        break;
    }
    case 3: {
        srand(time(NULL));

        Node L[] = {
            {3, 1},
            {7, 2},
            {10, 3},
            {15, 4},
            {20, NIL}
        };
        
        int head = 0;
        int n = 5;
        int k = 10;
        int t = 3;
        int result = compact_list_search_prim(L, head, n, k, t);
        
        if (result != NIL) {
            printf("Element %d found at index %d\n", k, result);
        } else {
            printf("Element %d not found\n", k);
        }

        break;
    }
    default:
        break;
    }

    return 0;
}