#include "part_2_sorting_and_order_statistics/6_heapsort/heapsort.h"

void demonstrate_heap_based_fifo() {
    print_separator("Heap-Based FIFO Queue Demo");
    
    PriorityQueue *pq = create_queue(QUEUE_SIZE);
    
    printf("Enqueuing elements: 10, 20, 30\n");
    enqueue(pq, 10);
    enqueue(pq, 20);
    enqueue(pq, 30);
    
    printf("Dequeuing elements (FIFO order):\n");
    printf("Dequeued: %d\n", dequeue(pq));
    printf("Dequeued: %d\n", dequeue(pq)); 
    printf("Dequeued: %d\n", dequeue(pq)); 
    
    queue_free(pq);
}

void demonstrate_k_way_merge() {
    print_separator("K-Way Merge Demo");
    
    int list1[] = {1, 2, 3};
    int list2[] = {4, 5, 6, 7};
    int list3[] = {8, 9};
    
    int *lists[] = {list1, list2, list3};
    int listSizes[] = {3, 4, 2};
    int k = 3;
    int total_size = listSizes[0] + listSizes[1] + listSizes[2];
    int result[total_size];
    
    printf("Merging 3 sorted lists:\n");
    printf("List 1: [1, 2, 3]\n");
    printf("List 2: [4, 5, 6, 7]\n");
    printf("List 3: [8, 9]\n");
    
    merge_k_sorted_lists(lists, listSizes, k, result);
    
    printf("Merged result: ");
    print_arr(result, total_size);
}

void demonstrate_max_heap_operations() {
    print_separator("Max Heap Operations Demo");
    
    int A[] = {3, 2, 1, 4, 5};
    int n = sizeof(A) / sizeof(A[0]);
    
    printf("Original array: ");
    print_arr(A, n);
    
    build_max_heap(A, n);
    printf("After build_max_heap: ");
    print_arr(A, n);
    
    printf("Maximum element: %d\n", max_heap_get_max(A, n));
    
    printf("Extracted max: %d\n", max_heap_extract_max(A, &n));
    printf("After extraction: ");
    print_arr(A, n);
    
    printf("Inserting new key 30...\n");
    max_heap_insert(A, &n, 30);
    printf("After insertion: ");
    print_arr(A, n);
    
    printf("Increasing key at index 2 to 15...\n");
    max_heap_increase_key_insertion(A, 2, 15);
    printf("After key increase: ");
    print_arr(A, n);
    
    printf("Decreasing key at index 1 to 1...\n");
    max_heap_decrease_key(A, n, 1, 1);
    printf("After key decrease: ");
    print_arr(A, n);
    
    printf("Deleting key at index 1...\n");
    max_heap_delete_element(A, &n, 1);
    printf("After deletion: ");
    print_arr(A, n);
}

void demonstrate_min_heap_operations() {
    print_separator("Min Heap Operations Demo");
    
    int B[] = {15, 13, 9, 5, 12, 8, 7, 4, 0, 6, 2, 1};
    int n = sizeof(B) / sizeof(B[0]);
    
    printf("Original array: ");
    print_arr(B, n);
    
    build_min_heap_iterative(B, n);
    printf("After build_min_heap: ");
    print_arr(B, n);
    
    printf("Minimum element: %d\n", min_heap_get_min(B, n));
    
    printf("Extracted min: %d\n", min_heap_extract_min(B, &n));
    printf("After extraction: ");
    print_arr(B, n);
    
    printf("Inserting new key 2...\n");
    min_heap_insert(B, &n, 2);
    printf("After insertion: ");
    print_arr(B, n);
    
    printf("Increasing key at index 3 to 20...\n");
    min_heap_increase_key(B, n, 3, 20);
    printf("After key increase: ");
    print_arr(B, n);
}

void demonstrate_heap_sort() {
    print_separator("Heap Sort Demo");
    
    int C[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(C) / sizeof(C[0]);
    
    printf("Original array: ");
    print_arr(C, n);
    
    heapsort(C, n);
    printf("After heap sort: ");
    print_arr(C, n);
}

int main() {
    demonstrate_heap_based_fifo();
    demonstrate_k_way_merge();
    demonstrate_max_heap_operations();
    demonstrate_min_heap_operations();
    demonstrate_heap_sort();
        
    return 0;
}