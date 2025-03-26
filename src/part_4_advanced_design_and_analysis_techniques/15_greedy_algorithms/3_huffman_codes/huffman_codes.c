#include <stdio.h>
#include <stdlib.h>

#define MAX_TREE_H 100

/*
    https://www.geeksforgeeks.org/huffman-coding-in-c/
*/

typedef struct MinHeapNode {
    char data;
    unsigned freq;
    struct MinHeapNode *left, *right;
} MinHeapNode;

typedef struct MinHeap {
    unsigned size;
    unsigned capacity;
    MinHeapNode** nodes;
} MinHeap;

MinHeapNode* new_node(char data, unsigned freq) {
    MinHeapNode* temp = (MinHeapNode*)malloc(sizeof(MinHeapNode));

    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;

    return temp;
}

MinHeap* create_minheap(unsigned capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));

    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->nodes = (MinHeapNode**)malloc(
        minHeap->capacity * sizeof(MinHeapNode*)
    );

    return minHeap;
}

void swap_min_heap_nodes(MinHeapNode** a, MinHeapNode** b) {
    MinHeapNode* temp = *a;
    *a = *b;
    *b = temp;
}

void min_heapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size 
        && minHeap->nodes[left]->freq < minHeap->nodes[smallest]->freq)
        smallest = left;

    if (right < minHeap->size
        && minHeap->nodes[right]->freq < minHeap->nodes[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swap_min_heap_nodes(&minHeap->nodes[smallest], &minHeap->nodes[idx]);
        min_heapify(minHeap, smallest);
    }
}

int is_size_one(MinHeap* minHeap) {
    return (minHeap->size == 1);
}

MinHeapNode* extract_min(MinHeap* minHeap) {
    MinHeapNode* temp = minHeap->nodes[0];
    minHeap->nodes[0] = minHeap->nodes[minHeap->size - 1];

    // Decrease minHeap size without making an additional copy
    --minHeap->size;
    min_heapify(minHeap, 0);

    return temp;
}

void insert_min_heap(MinHeap* minHeap, MinHeapNode* minHeapNode) {
    // Increase minHeap size without making an additional copy
    ++minHeap->size;
    int i = minHeap->size - 1;

    /*
        In case of binary heap: parent_idx = (i - 1) / 2
    */

    while (i && minHeapNode->freq < minHeap->nodes[(i - 1) / 2]->freq) {
        minHeap->nodes[i] = minHeap->nodes[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    minHeap->nodes[i] = minHeapNode;
}

void build_min_heap(MinHeap* minHeap) { 
    int n = minHeap->size - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; --i) min_heapify(minHeap, i);
}

void print_arr(int arr[], int n) {
    int i;

    for (i = 0; i < n; ++i) printf("%d", arr[i]);
    printf("\n");
}

int is_leaf(MinHeapNode* root) {
    return !(root->left) && !(root->right);
}

MinHeap* create_and_build_min_heap(
    char data[], 
    unsigned freqs[], 
    unsigned size
) {
    MinHeap* minHeap = create_minheap(size);
    int i;

    for (i = 0; i < size; i++) minHeap->nodes[i] = new_node(data[i], freqs[i]);

    minHeap->size = size;
    build_min_heap(minHeap);

    return minHeap;
}

MinHeapNode* build_huffman_tree(char data[], unsigned freqs[], unsigned size) {
    MinHeapNode *left, *right, *top;
    MinHeap* minHeap = create_and_build_min_heap(data, freqs, size);

    // Iterate while heap's size is not 1 - extractMin is destructive.
    while (!is_size_one(minHeap)) {
        left = extract_min(minHeap);
        right = extract_min(minHeap);

        top = new_node('$', left->freq + right->freq);

        top->left = left;
        top->right = right;

        insert_min_heap(minHeap, top);
    }

    return extract_min(minHeap);
}

void print_codes(MinHeapNode* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        print_codes(root->left, arr, top + 1);
    }

    if (root->right) {
        arr[top] = 1;
        print_codes(root->right, arr, top + 1);
    }

    if (is_leaf(root)) {
        printf("%c: ", root->data);
        print_arr(arr, top);
    }
}

void huffman_codes(char data[], unsigned freqs[], unsigned size) { 
    MinHeapNode* root = build_huffman_tree(data, freqs, size);
    int arr[MAX_TREE_H], top = 0;
    print_codes(root, arr, top);
}

int main(void) {
    char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    unsigned freqs[] = {5, 9, 12, 13, 16, 45};
    unsigned size = sizeof(arr) / sizeof(arr[0]);

    huffman_codes(arr, freqs, size);

    return 0;
}