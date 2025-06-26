#include "part_2_sorting_and_order_statistics/8_sorting_in_linear_time/sorting_in_linear_time.h"

void bucket_sort(float A[]) {
    int i, j;
    struct Node **buckets;

    buckets = (struct Node **)malloc(sizeof(struct Node *) * NBUCKET);

    for (i = 0; i < NBUCKET; ++i)
        buckets[i] = NULL;

    for (i = 0; i < NARRAY; ++i) {
        int idx = get_bucket_idx(A[i]);
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->data = A[i];
        newNode->next = buckets[idx];
        buckets[idx] = newNode;
    }

    for (i = 0; i < NBUCKET; i++) {
        printf("Bucket[%d]: ", i);
        print_buckets(buckets[i]);
        printf("\n");
    }

    for (i = 0; i < NBUCKET; i++) {
        buckets[i] = insertion_sort(buckets[i]);
    }

    printf("-------------\n");
    printf("Buckets after sorting\n");
    for (i = 0; i < NBUCKET; i++) {
        printf("Bucket[%d]: ", i);
        print_buckets(buckets[i]);
        printf("\n");
    }

    for (j = 0, i = 0; i < NBUCKET; ++i) {
        struct Node *node = buckets[i];
        while (node) {
            A[j++] = node->data;
            node = node->next;
        }
    }

    free_buckets(buckets);
}

struct Node* insertion_sort(struct Node *list ) {
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

int get_bucket_idx(float value) {
    return (int)(value * NBUCKET);
}

void print_buckets(struct Node *list) {
    struct Node *curr = list;
    while (curr) {
        printf("%.2f ", curr->data);
        curr = curr->next;
    }
}

void free_buckets(struct Node **buckets ) {
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