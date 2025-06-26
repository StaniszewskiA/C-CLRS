#include "part_4_advanced_design_and_analysis_techniques/16_amortized_analysis/amortized_analysis.h"

#define TASK 3

/*
    16-1: Binary Gray codes.
*/
uint gray_code(uint i) {
    return i ^ (i >> 1);
}

void generate_gray_codes(int k) {
    uint n = 1 << k;
    uint i, gray;
    printf("<");

    for (i = 0; i < n; i++) {
        gray = gray_code(i);

        for (int j = k - 1; j >= 0; j--) printf("%u", (gray >> j) & 1);

        if (i < n - 1) printf(", ");
    }
    printf(">\n");
}

/*
    16.2: Making binary dbs_search dynamic.
*/
void dynamic_array_init(DynamicArray* arr, uint capacity) {
    arr->data = (int*)malloc(capacity * sizeof(int));
    arr->size = 0;
    arr->capacity = capacity;
}

void dbs_init(DynamicBinarySearch* dbs, uint n) {
    uint i;
    
    dbs->k = (int)ceil(log2(n + 1));
    for (i = 0; i < dbs->k; i++) {
        dbs->arrays[i] = (DynamicArray*)malloc(sizeof(DynamicArray));
        dynamic_array_init(dbs->arrays[i], 1 << i);
    } 
}

int dbs_binary_search(DynamicArray* arr, int target) {
    int low = 0, high = arr->size - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr->data[mid] == target) return mid;
        else if (arr->data[mid] < target) low = mid + 1;
        else high = mid - 1;
    }

    return -1;
}

int dbs_search(DynamicBinarySearch* dbs, int target) {
    int idx;

    for (uint i = 0; i < dbs->k; i++) {
        idx = dbs_binary_search(dbs->arrays[i], target);
        if (idx != -1) return idx;
    }

    return -1;
}

void dbs_insert(DynamicBinarySearch* dbs, int val) {
    DynamicArray* arr = dbs->arrays[0];
    int idx;

    if (arr->size < arr->capacity) {
        idx = arr->size - 1;
        while (idx >= 0 && arr->data[idx] > val) {
            arr->data[idx + 1] = arr->data[idx];
            idx--;
        }
        arr->data[idx + 1] = val;
        arr->size++;
    } else {
        for (uint i = 1; i < dbs->k; i++) { 
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

void dbs_delete(DynamicBinarySearch* dbs, int val) {
    int idx;

    for (uint i = 0; i < dbs->k; i++) {  
        DynamicArray* arr = dbs->arrays[i];
        idx = dbs_binary_search(arr, val);
        if (idx != -1) {
            for (uint j = idx; j < arr->size - 1; j++) 
                arr->data[j] = arr->data[j + 1];
            arr->size--;
            break;
        }
    }
}

void print_dbs(DynamicBinarySearch* dbs) {
    for (uint i = 0; i < dbs->k; i++) {  
        printf("Array A%u (size %u): ", i, dbs->arrays[i]->size);
        for (uint j = 0; j < dbs->arrays[i]->size; j++) { 
            printf("%d ", dbs->arrays[i]->data[j]);  
        }
        printf("\n"); 
    }
    printf("\n");
}

/*
    16.3: Amortized weight-balanced trees.
*/
TreeNode* tree_node_init(int val) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->val = val;
    newNode->size = 1;
    newNode->left = newNode->right = NULL;
    printf("Created a node with value: %d\n", val);
    return newNode;
}

void tree_update_size(TreeNode* node) {
    if (node) {
        node->size = 1;
        if (node->left) node->size += node->left->size;
        if (node->right) node->size += node->right->size;
    }
}

void tree_inorder_traversal(TreeNode* root, int* nodes, int* idx) {
    if (root) {
        tree_inorder_traversal(root->left, nodes, idx);
        nodes[(*idx)++] = root->val;
        tree_inorder_traversal(root->right, nodes, idx);
    }
}

TreeNode* build_balanced_BST(int* nodes, int start, int end) {
    if (start > end) return NULL;

    int mid = (start + end) / 2;

    TreeNode* node = tree_node_init(nodes[mid]);
    node->left = build_balanced_BST(nodes, start, mid - 1);
    node->right = build_balanced_BST(nodes, mid + 1, end);
    tree_update_size(node);
    return node;
}

TreeNode* tree_rebuild(TreeNode* root) {
    if (root == NULL) return NULL;

    int size = root->size;
    int* nodes = (int*)malloc(size * sizeof(int));
    int idx = 0;

    tree_inorder_traversal(root, nodes, &idx);
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
            dbs_init(&dbs, n2);

            dbs_insert(&dbs, 10);
            dbs_insert(&dbs, 20);
            dbs_insert(&dbs, 30);
            dbs_insert(&dbs, 40);
            dbs_insert(&dbs, 50);
            dbs_insert(&dbs, 60);
            dbs_insert(&dbs, 70);
            dbs_insert(&dbs, 80);
            dbs_insert(&dbs, 90);

            print_dbs(&dbs);

            uint target = 30;
            int idx = dbs_search(&dbs, target);

            if (idx != -1) {
                printf("Element %d found at index %d\n", target, idx);
            } else {
                printf("Element %d not found\n", target);
            }

            dbs_delete(&dbs, 30);
            printf("After deletion:\n");
            print_dbs(&dbs);

            break;
        }

        case 3: {
            // 16.3
            TreeNode* root = tree_node_init(15);
            root->left = tree_node_init(10);
            root->right = tree_node_init(20);
            root->left->left = tree_node_init(7);
            root->left->right = tree_node_init(12);
            root->right->left = tree_node_init(17);
            root->right->right = tree_node_init(22);

            root = tree_rebuild(root);
            printf("Tree rebuild successfuly");

            break;
        }
        
        default:
            break;
    }
    
    return 0;
}