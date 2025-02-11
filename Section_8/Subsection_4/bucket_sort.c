#include <stdio.h>
#include <stdlib.h>

#define NARRAY 10
#define NBUCKET 6
struct Node {
    float data;
    struct Node *next;
};

void BucketSort(float A[]);
struct Node *InsertionSort(struct Node *list);
void printArr(float A[]);
void printBuckets(struct Node *list);
int getBucketIdx(float value);
void freeBuckets(struct Node **buckets);

void BucketSort(
    float A[]
) {
    int i, j;
    struct Node **buckets;

    buckets = (struct Node **)malloc(sizeof(struct Node *) * NBUCKET);

    for (i = 0; i < NBUCKET; ++i)
        buckets[i] = NULL;

    for (i = 0; i < NARRAY; ++i) {
        int idx = getBucketIdx(A[i]);
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->data = A[i];
        newNode->next = buckets[idx];
        buckets[idx] = newNode;
    }

    for (i = 0; i < NBUCKET; i++) {
        printf("Bucket[%d]: ", i);
        printBuckets(buckets[i]);
        printf("\n");
    }

    for (i = 0; i < NBUCKET; i++) {
        buckets[i] = InsertionSort(buckets[i]);
    }

    printf("-------------\n");
    printf("Buckets after sorting\n");
    for (i = 0; i < NBUCKET; i++) {
        printf("Bucket[%d]: ", i);
        printBuckets(buckets[i]);
        printf("\n");
    }

    for (j = 0, i = 0; i < NBUCKET; ++i) {
        struct Node *node = buckets[i];
        while (node) {
            A[j++] = node->data;
            node = node->next;
        }
    }

    freeBuckets(buckets);
}

struct Node *InsertionSort(
    struct Node *list 
) {
    if (list == NULL || list->next == NULL)
        return list;

    struct Node *sorted = NULL;
    struct Node *curr = list;

    while (curr) {
        struct Node *next = curr->next;

        if (!sorted || curr->data < sorted->data) {
            curr->next = sorted;
            sorted = curr;
        } else {
            struct Node *temp = sorted;
            while (temp->next && temp->next->data < curr->data) {
                temp = temp->next;
            }
            curr->next = temp->next;
            temp->next = curr;
        }

        curr = next;
    }

    return sorted;
}

int getBucketIdx(
    float value
) {
    return (int)(value * NBUCKET);
}


void printArr(float A[]) {
    for (int i = 0; i < NARRAY; ++i) {
        printf("%.2f ", A[i]);
    }
    printf("\n");
}

void printBuckets(struct Node *list) {
    struct Node *curr = list;
    while (curr) {
        printf("%.2f ", curr->data);
        curr = curr->next;
    }
}

void freeBuckets(
    struct Node **buckets 
) {
    for (int i = 0; i < NBUCKET; i++) {
        struct Node *node = buckets[i];
        while (node) {
            struct Node *temp = node;
            node = node->next;
            free(temp);
        }
    }
    free(buckets);
}

int main(void) {
    float A[NARRAY] = {
        0.79, 
        0.13, 
        0.16, 
        0.64, 
        0.30, 
        0.20, 
        0.89, 
        0.53, 
        0.71, 
        0.42
    };

    printf("Initial array: ");
    printArr(A);
    printf("-------------\n");

    BucketSort(A);
    printf("-------------\n");
    printf("Sorted array: ");
    printArr(A);
    return 0;
}