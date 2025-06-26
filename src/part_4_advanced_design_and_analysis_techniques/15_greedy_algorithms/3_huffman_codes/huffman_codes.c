#include "part_4_advanced_design_and_analysis_techniques/15_greedy_algorithms/greedy_algorithms.h"

/*
    https://www.geeksforgeeks.org/huffman-coding-in-c/
*/
MinHeapNode* min_heap_create_node(char data, unsigned freq) {
    MinHeapNode* temp = (MinHeapNode*)malloc(sizeof(MinHeapNode));

    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;

    return temp;
}

MinHeap* min_heap_create(unsigned capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));

    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->nodes = (MinHeapNode**)malloc(
        minHeap->capacity * sizeof(MinHeapNode*)
    );

    return minHeap;
}

void min_heap_swap_nodes(MinHeapNode** a, MinHeapNode** b) {
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
        min_heap_swap_nodes(&minHeap->nodes[smallest], &minHeap->nodes[idx]);
        min_heapify(minHeap, smallest);
    }
}

int min_heap_is_size_one(MinHeap* minHeap) {
    return (minHeap->size == 1);
}

MinHeapNode* min_heap_extract_min(MinHeap* minHeap) {
    MinHeapNode* temp = minHeap->nodes[0];
    minHeap->nodes[0] = minHeap->nodes[minHeap->size - 1];

    // Decrease minHeap size without making an additional copy
    --minHeap->size;
    min_heapify(minHeap, 0);

    return temp;
}

void min_heap_insert(MinHeap* minHeap, MinHeapNode* minHeapNode) {
    // Increase minHeap size without making an additional copy
    ++minHeap->size;
    int i = minHeap->size - 1;

    // In case of binary heap: parent_idx = (i - 1) / 2

    while (i && minHeapNode->freq < minHeap->nodes[(i - 1) / 2]->freq) {
        minHeap->nodes[i] = minHeap->nodes[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    minHeap->nodes[i] = minHeapNode;
}

void min_heap_build(MinHeap* minHeap) { 
    int n = minHeap->size - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; --i) min_heapify(minHeap, i);
}

int min_heap_node_is_leaf(MinHeapNode* root) {
    return !(root->left) && !(root->right);
}

MinHeap* min_heap_create_and_build(char data[],  unsigned freqs[], unsigned size) {
    MinHeap* minHeap = min_heap_create(size);
    
    for (unsigned int i = 0; i < size; i++) {
        minHeap->nodes[i] = min_heap_create_node(data[i], freqs[i]);
    }

    minHeap->size = size;
    min_heap_build(minHeap);

    return minHeap;
}

MinHeapNode* huffman_tree_build(char data[], unsigned freqs[], unsigned size) {
    MinHeapNode *left, *right, *top;
    MinHeap* minHeap = min_heap_create_and_build(data, freqs, size);

    // Iterate while heap's size is not 1 - extractMin is destructive.
    while (!min_heap_is_size_one(minHeap)) {
        left = min_heap_extract_min(minHeap);
        right = min_heap_extract_min(minHeap);

        top = min_heap_create_node('$', left->freq + right->freq);

        top->left = left;
        top->right = right;

        min_heap_insert(minHeap, top);
    }

    return min_heap_extract_min(minHeap);
}

void print_huffman_codes(MinHeapNode* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        print_huffman_codes(root->left, arr, top + 1);
    }

    if (root->right) {
        arr[top] = 1;
        print_huffman_codes(root->right, arr, top + 1);
    }

    if (min_heap_node_is_leaf(root)) {
        printf("%c: ", root->data);
        print_arr(arr, top);
    }
}

void huffman_codes(char data[], unsigned freqs[], unsigned size) { 
    MinHeapNode* root = huffman_tree_build(data, freqs, size);
    int arr[MAX_TREE_H], top = 0;
    print_huffman_codes(root, arr, top);
}
