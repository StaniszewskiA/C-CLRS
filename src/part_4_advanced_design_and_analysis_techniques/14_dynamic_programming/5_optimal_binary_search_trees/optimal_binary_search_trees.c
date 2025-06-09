#include "part_4_advanced_design_and_analysis_techniques/14_dynamic_programming/dynamic_programming.h"

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

BSTNode* construct_optimal_bst(int root[][100], int keys[], int i, int j) {
    if (i > j) return NULL;

    int k = root[i][j];
    BSTNode* node = bst_node_init(keys[k - 1]);  

    if (i < j) {  
        node->left = construct_optimal_bst(root, keys, i, k - 1);
        node->right = construct_optimal_bst(root, keys, k, j);
    }

    return node;
}

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

void print_root_table(int root[][N+1], int n) {
    printf("\nRoot Table:\n");
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            printf("%d ", root[i][j]);
        }
        printf("\n");
    }
}
