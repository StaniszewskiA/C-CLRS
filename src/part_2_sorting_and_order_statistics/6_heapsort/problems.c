#include "part_2_sorting_and_order_statistics/6_heapsort/heapsort.h"

#define TASK 1

void build_max_heap_prim(int A[], int n) {
    int heap_size = 1;
    for (int i = 1; i < n; i++) max_heap_insert(A, &heap_size, A[i]);
}

DHeap* create_dheap(int capacity, int d) {
    DHeap *heap = (DHeap*)malloc(sizeof(DHeap));
    heap->capacity = capacity;
    heap->d = d;
    heap->size = 0;
    heap->arr = (int*)malloc(capacity * sizeof(int));

    return heap;
}

int dheap_get_left_child(DHeap* heap, int i) {
    return heap->d * i + 1;
}

int dheap_get_right_child(DHeap *heap, int i) {
    return heap->d * (i + 1);
}

int dheap_get_parent(DHeap *heap, int i) {
    return (i - 1) / heap->d;
}

void dheapify(DHeap *heap, int i) {
    int largest = i;
    for (int j = 1; j <= heap->d; j++) {
        int child = dheap_get_left_child(heap, i) + j - 1;
        if (child < heap->size && heap->arr[child] > heap->arr[largest]) {
            largest = child;
        }
    }

    if (largest != i) {
        int temp = heap->arr[i];
        heap->arr[i] = heap->arr[largest];
        heap->arr[largest] = temp;
        dheapify(heap, largest);
    }
}

void dheap_insert_key(DHeap *heap, int key) {
    if (heap->size == heap->capacity) {
        printf("Heap overflow\n");
        return;
    }

    heap->arr[heap->size] = key;
    int i = heap->size;
    heap->size++;

    while (i > 0 && heap->arr[dheap_get_parent(heap, i)] < heap->arr[i]) {
        int temp = heap->arr[i];
        heap->arr[i] = heap->arr[dheap_get_parent(heap, i)];
        heap->arr[dheap_get_parent(heap, i)] = temp;
        i = dheap_get_parent(heap, i);
    }
}

int dheap_delete_root(DHeap *heap) {
    if (heap->size <= 0) {
        printf("Heap underflow\n");
        return -1;
    }

    if (heap->size == 1) {
        heap->size--;
        return heap->arr[0];
    }

    int root = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;

    dheapify(heap, 0);
    return root;
}

void print_dheap(DHeap *heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->arr[i]);
    }
    printf("\n");
}

int dheap_extract_max(DHeap *heap) {
    if (heap->size <= 0) {
        printf("Heap underflow\n");
        return -1;
    }

    if (heap->size == 1) {
        heap->size--;
        return heap->arr[0];
    }

    int max = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;

    dheapify(heap, 0);
    return max;
}

void dheap_increase_key(DHeap *heap, int i, int k) {
    if (k < heap->arr[i]) {
        printf("New key is smaller than current key\n");
        return;
    }

    heap->arr[i] = k;

    while (i < 0 && heap->arr[dheap_get_parent(heap, i)] < heap->arr[i]) {
        int temp = heap->arr[i];
        heap->arr[i] = heap->arr[dheap_get_parent(heap, i)];
        heap->arr[dheap_get_parent(heap, i)] = temp;
        i = dheap_get_parent(heap, i);
    }
}

int young_table_extract_min(
    int Y[][MAX_COLS],
    int rows,
    int cols,
    int i,
    int j
) {
    int min = Y[i][j];

    if ((j + 1 >= cols || Y[i][j + 1] == INF) 
        && (i + 1 >= rows || Y[i + 1][j] == INF)) {
        Y[i][j] = INF;
        return min;
    }

    if (j + 1 < cols 
        && (i + 1 >= rows || Y[i][j + 1] < Y[i + 1][j])) {
        Y[i][j] = Y[i][j + 1];
        Y[i][j + 1] = min;
        return young_table_extract_min(Y, rows, cols, i, j + 1);
    } else {
        Y[i][j] = Y[i + 1][j];
        Y[i + 1][j] = min;
        return young_table_extract_min(Y, rows, cols, i + 1, j);
    }
}

void young_table_insert_key(
    int Y[][MAX_COLS],
    int i,    
    int j,   
    int key
) {
    Y[i][j] = key;

    while ((i > 0 && Y[i - 1][j] > Y[i][j]) 
        || (j > 0 && Y[i][j - 1] > Y[i][j])) {
        if (j > 0 && (i == 0 || Y[i - 1][j] >= Y[i][j - 1])) {
            int temp = Y[i][j];
            Y[i][j] = Y[i][j - 1];
            Y[i][j - 1] = temp;
            j--;
        } else {
            int temp = Y[i][j];
            Y[i][j] = Y[i - 1][j];
            Y[i - 1][j] = temp;
            i--;
        }
    } 
}

void young_table_check(
    int Y[][MAX_COLS],
    int i,
    int j
) {
    printf("Checking at (%d, %d): %d\n", i, j, Y[i][j]);
}

int young_table_search_key(
    int Y[][MAX_COLS],
    int rows,
    int key
) {
    int i = 0, j = 0;

    while (i < rows && j >= 0) {
        young_table_check(Y, i, j);
        if (Y[i][j] == key) {
            printf("Key %d found at (%d, %d)\n", key, i, j);
            return 1;
        }
        if (Y[i][j] > key) {
            j--; 
        } else {
            i++; 
        }
    }

    printf("Key %d not found.\n", key);
    return 0;
}

int main(void) {
    switch (TASK) {
        case 1: {
            int A[MAX_SIZE] = {3, 2, 1, 4, 5};
            int n = 5;

            printf("Original array:\n");
            print_arr(A, n);

            build_max_heap_prim(A, n);
            printf("Max Heap (alternative build):\n");
            print_arr(A, n);

            break;
        }
        
        case 2: {
            int capacity = 10;
            int d = 3;
            DHeap *heap = create_dheap(capacity, d);

            dheap_insert_key(heap, 10);
            dheap_insert_key(heap, 20);
            dheap_insert_key(heap, 30);
            dheap_insert_key(heap, 40);
            dheap_insert_key(heap, 50); 
            dheap_insert_key(heap, 25);
            dheap_insert_key(heap, 35);

            printf("Heap: ");
            print_dheap(heap);

            printf("Deleted root: %d\n", dheap_delete_root(heap));

            printf("Heap: ");
            print_dheap(heap);

            printf("Extracted max: %d\n", dheap_extract_max(heap));

            printf("Heap after extracting max: ");
            print_dheap(heap);

            dheap_increase_key(heap, 2, 35);
            printf("Heap after increasing key at index 2 to 35: ");
            print_dheap(heap);

            free(heap->arr);
            free(heap);

            break;
        }

        case 3: {
            int Y[MAX_ROWS][MAX_COLS] = { 
                {10, 20, 30, INF},
                {15, 25, 35, INF},
                {INF, INF, INF, INF}
            };

            int min_val = young_table_extract_min(Y, 3, 4, 0, 0);
            printf("Extracted min: %d\n", min_val);

            young_table_insert_key(Y, 3, 4, 17);
            
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 4; j++) {
                    if (Y[i][j] == INF) printf("INF ");
                    else printf("%d ", Y[i][j]);
                }
                printf("\n");
            }
            
            int key = 25;
            young_table_search_key(Y, 3, key);

            break;
        }
        
        default:
            break;
    }

    return 0;
}