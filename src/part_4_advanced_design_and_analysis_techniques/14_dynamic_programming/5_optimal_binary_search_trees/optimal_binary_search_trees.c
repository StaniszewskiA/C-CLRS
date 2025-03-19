#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <stdlib.h>

#define TASK 5
#define N 3

//----------BST utils----------
typedef struct Node {
    int key;
    struct Node* left;     
    struct Node* right;  
} Node;

Node* new_node(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    return node;
}

void print_bst(Node* root) {
    // Inorder traversal
    if (root != NULL) {
        print_bst(root->left);
        printf("%d ", root->key);
        print_bst(root->right);
    }
}

//----------Optimal BST----------
void optimal_bst(float p[], float q[], int n, int root[][n + 1]) {
    float costs[n + 1][n + 1]; 
    float weights[n + 1][n + 1];

    // Initialize tables
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            costs[i][j] = FLT_MAX; 
            weights[i][j] = 0;
            root[i][j] = 0;
        }
    }

    // Initialize dummy keys
    for (int i = 0; i <= n; i++) {
        costs[i][i] = q[i];
        weights[i][i] = q[i];
    }

    for (int l = 1; l <= n; l++) { 
        for (int i = 0; i <= n - l; i++) { 
            int j = i + l; 
            weights[i][j] = weights[i][j - 1] + p[j] + q[j];

            for (int r = i; r <= j; r++) { 
                float tempCost = costs[i][r - 1] + costs[r + 1][j] + weights[i][j]; 

                if (tempCost < costs[i][j]) {
                    costs[i][j] = tempCost;
                    root[i][j] = r; 
                    printf("Updated root[%d][%d] to %d\n", i, j, root[i][j]);
                }
            }
        }
    }
    
    printf("Minimum cost of Optimal BST: %f\n", costs[0][n]);
}

//----------14.5-1----------
Node* construct_optimal_bst(int root[][N+1], int i, int j) {
    if (i > j) return NULL;

    int root_key = i + 1;

    if (i == j) {
        Node* node = new_node(root_key);
        return node;
    } 

    Node* node = new_node(root_key);

    node->left = construct_optimal_bst(root, i, root[i][j] - 1);
    node->right = construct_optimal_bst(root, root[i][j] + 1, j);

    return node;
}

//----------14.5-4----------
void knuthian_optimal_bst(float p[], float q[], int n, int root[][n + 1]) {
    float costs[n + 1][n + 1]; 
    float weights[n + 1][n + 1];

    // Initialize tables
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            costs[i][j] = FLT_MAX; 
            weights[i][j] = 0;
            root[i][j] = 0;
        }
    }

    // Initialize dummy keys
    for (int i = 0; i <= n; i++) {
        costs[i][i] = q[i];
        weights[i][i] = q[i];
    }

    for (int l = 1; l <= n; l++) { 
        for (int i = 0; i <= n - l; i++) { 
            int j = i + l; 
            weights[i][j] = weights[i][j - 1] + p[j] + q[j];

            // Constant time(?)
            for (int r = root[i][j - 1]; r <= root[i + 1][j]; r++) { 
                float tempCost = costs[i][r - 1] + costs[r + 1][j] + weights[i][j]; 

                if (tempCost < costs[i][j]) {
                    costs[i][j] = tempCost;
                    root[i][j] = r; 
                    printf("Updated root[%d][%d] to %d\n", i, j, root[i][j]);
                }
            }
        }
    }
    
    printf("Minimum cost of Optimal BST: %f\n", costs[0][n]);
}

//----------Print Root Table (debug)----------
void print_root_table(int root[][N+1], int n) {
    printf("\nRoot Table:\n");
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            printf("%d ", root[i][j]);
        }
        printf("\n");
    }
}

int main(void) {
    float p[] = {0.0, 0.1, 0.25, 0.30, 0.05};  // Probabilities of keys (starting with p[0] for the dummy key)
    float q[] = {0.05, 0.10, 0.05, 0.05, 0.05};  // Probabilities of dummy keys
    int root[N + 1][N + 1] = {0};  // Root table for reconstructing the result

    switch (TASK)
    {
        case 1: {
            optimal_bst(p, q, N, root);
            break;
        }
        case 2: {
            // 14.5-1
            optimal_bst(p, q, N, root);
            printf("Optimal BST structure:\n");
            print_root_table(root, N);
            Node* bst_root = construct_optimal_bst(root, 0, N);
            printf("In-order traversal of the optimal BST: ");
            print_bst(bst_root);
            printf("\n");
            break;
        }
        case 4: {
            // 14.5-2 
            float p[] = {0.0, 0.04, 0.06, 0.08, 0.02, 0.1, 0.12, 0.14}; 
            float q[] = {0.06, 0.06, 0.06, 0.06, 0.05, 0.05, 0.05, 0.05, 0.05}; 
            int root[N + 1][N + 1] = {0};
            optimal_bst(p, q, N, root);
            break;
        }
        case 5:{
            // 14.5-4
            knuthian_optimal_bst(p, q, N, root);
            break;
        }
        case -1: {
            // Debug
            optimal_bst(p, q, N, root);
            print_root_table(root, N);
            break;
        }
        default:
            break;
    }

    return 0;
}
