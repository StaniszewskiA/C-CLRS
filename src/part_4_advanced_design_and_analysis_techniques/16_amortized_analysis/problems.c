#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TASK 3

/*
    16-1: Binary Gray codes.
*/
typedef unsigned int uint;

static inline uint gray_code(uint i) {
    return i ^ (i >> 1);
}

void generate_gray_codes(int k) {
    uint n = 1 << k;
    uint i, j, gray;
    printf("<");

    for (i = 0; i < n; i++) {
        gray = gray_code(i);

        for (int j = k - 1; j >= 0; j--) printf("%u", (gray >> j) & 1);

        if (i < n - 1) printf(", ");
    }
    printf(">\n");
}

/*
    16.2: Making binary search dynamic.
*/
#define MAX_ARRAYS 20

typedef struct {
    int* data;
    uint size;
    uint capacity;
} DynamicArray;

typedef struct {
    DynamicArray* arrays[MAX_ARRAYS];
    uint k;
} DynamicBinarySearch;

void init_dynamic_array(DynamicArray* arr, uint capacity) {
    arr->data = (int*)malloc(capacity * sizeof(int));
    arr->size = 0;
    arr->capacity = capacity;
}

void init_dbs(DynamicBinarySearch* dbs, uint n) {
    uint i;
    
    dbs->k = (int)ceil(log2(n + 1));
    for (i = 0; i < dbs->k; i++) {
        dbs->arrays[i] = (DynamicArray*)malloc(sizeof(DynamicArray));
        init_dynamic_array(dbs->arrays[i], 1 << i);
    } 
}

int binary_search(DynamicArray* arr, int target) {
    int low = 0, high = arr->size - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr->data[mid] == target) return mid;
        else if (arr->data[mid] < target) low = mid + 1;
        else high = mid - 1;
    }

    return -1;
}

int search(DynamicBinarySearch* dbs, int target) {
    int i, idx;

    for (i = 0; i < dbs->k; i++) {
        idx = binary_search(dbs->arrays[i], target);
        if (idx != -1) return idx;
    }

    return -1;
}

void insert(DynamicBinarySearch* dbs, int val) {
    DynamicArray* arr = dbs->arrays[0];
    int i, idx;

    if (arr->size < arr->capacity) {
        idx = arr->size - 1;
        while (idx >= 0 && arr->data[idx] > val) {
            arr->data[idx + 1] = arr->data[idx];
            idx--;
        }
        arr->data[idx + 1] = val;
        arr->size++;
    } else {
        for (i = 1; i < dbs->k; i++) {
            DynamicArray* curr = dbs->arrays[i];
            if (curr->size < curr->capacity) {
                idx = curr->size - 1;
                while (idx >= 0 && curr->data[idx] > val) {
                    curr->data[idx + 1] = curr->data[idx];
                    idx--;
                }
                curr->data[idx + 1] = val;
                curr->size++;
                break;
            }
        }
    }
}

void delete(DynamicBinarySearch* dbs, int val) {
    int i, idx, j;

    for (i = 0; i < dbs->k; i++) {
        DynamicArray* arr = dbs->arrays[i];
        idx = binary_search(arr, val);
        if (idx != -1) {
            for (j = idx; j < arr->size - 1; j++) 
                arr->data[j] = arr->data[j + 1];
            arr->size--;
            break;
        }
    }
}

void print_dbs(DynamicBinarySearch* dbs) {
    int i, j;

    for (i = 0; i < dbs->k; i++) {
        printf("Array A%d (size %d): ", i, dbs->arrays[i]->size);
        for (j = 0; j < dbs->arrays[i]->size; j++) {
            printf("%d ", dbs->arrays[i]->data[j]);  
        }
        printf("\n"); 
    }
    printf("\n");
}

/*
    16.3: Amortized weight-balanced trees.
*/
typedef struct TreeNode {
    int val;
    int size;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* create_node(int val) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->val = val;
    newNode->size = 1;
    newNode->left = newNode->right = NULL;
    printf("Created a node with value: %d\n", val);
    return newNode;
}

void update_size(TreeNode* node) {
    if (node) {
        node->size = 1;
        if (node->left) node->size += node->left->size;
        if (node->right) node->size += node->right->size;
    }
}

void inorder_traversal(TreeNode* root, int* nodes, int* idx) {
    if (root) {
        inorder_traversal(root->left, nodes, idx);
        nodes[(*idx)++] = root->val;
        inorder_traversal(root->right, nodes, idx);
    }
}

TreeNode* build_balanced_BST(int* nodes, int start, int end) {
    if (start > end) return NULL;

    int mid = (start + end) / 2;

    TreeNode* node = create_node(nodes[mid]);
    node->left = build_balanced_BST(nodes, start, mid - 1);
    node->right = build_balanced_BST(nodes, mid + 1, end);
    update_size(node);
    return node;
}

TreeNode* rebuild_tree(TreeNode* root) {
    if (root == NULL) return NULL;

    int size = root->size;
    int* nodes = (int*)malloc(size * sizeof(int));
    int idx = 0;

    inorder_traversal(root, nodes, &idx);
    TreeNode* newRoot = build_balanced_BST(nodes, 0, size - 1);

    free(nodes);
    return newRoot;
}

int main(void) {
    switch (TASK)
    {
        case 1: {
            // 16.1
            uint k1 = 3;
            generate_gray_codes(k1);

            break;
        }

        case 2:{
            // 16.2
            uint n2 = 16;
            DynamicBinarySearch dbs;
            init_dbs(&dbs, n2);

            insert(&dbs, 10);
            insert(&dbs, 20);
            insert(&dbs, 30);
            insert(&dbs, 40);
            insert(&dbs, 50);
            insert(&dbs, 60);
            insert(&dbs, 70);
            insert(&dbs, 80);
            insert(&dbs, 90);

            print_dbs(&dbs);

            uint target = 30;
            int idx = search(&dbs, target);

            if (idx != -1) {
                printf("Element %d found at index %d\n", target, idx);
            } else {
                printf("Element %d not found\n", target);
            }

            delete(&dbs, 30);
            printf("After deletion:\n");
            print_dbs(&dbs);

            break;
        }

        case 3: {
            // 16.3
            TreeNode* root = create_node(15);
            root->left = create_node(10);
            root->right = create_node(20);
            root->left->left = create_node(7);
            root->left->right = create_node(12);
            root->right->left = create_node(17);
            root->right->right = create_node(22);

            root = rebuild_tree(root);
            printf("Tree rebuild successfuly");

            break;
        }
        
        default:
            break;
    }
    
    return 0;
}