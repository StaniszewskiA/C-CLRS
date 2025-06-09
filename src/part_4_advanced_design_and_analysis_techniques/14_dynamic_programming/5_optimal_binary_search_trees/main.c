#include "part_4_advanced_design_and_analysis_techniques/14_dynamic_programming/dynamic_programming.h"

#define TASK 1

int main(void) {
    printf("TODO");
    /*
    int keys[] = {1, 2, 3, 4, 5};
    double p[] = {0.0, 0.15, 0.10, 0.05, 0.10, 0.20}; 
    double q[] = {0.05, 0.10, 0.05, 0.05, 0.05, 0.10};
    
    static int root[MAX_BST_SIZE][MAX_BST_SIZE] = {0}; 
    static double costs[MAX_BST_SIZE][MAX_BST_SIZE] = {0.0};

    printf("Input Data:\n");
    printf("Keys: ");
    for (int i = 1; i <= 5; i++) printf("k%d ", i);
    printf("\n");
    
    printf("Search probabilities p[]: ");
    for (int i = 1; i <= 5; i++) printf("%.2f ", p[i]);
    printf("\n");
    
    printf("Dummy probabilities q[]: ");
    for (int i = 0; i <= 5; i++) printf("%.2f ", q[i]);
    printf("\n\n");

    switch (TASK) {
        case 1: {
            optimal_bst(p, q, 5, root, costs);
            print_root_table(root, 5);
            break;
        }
        case 2: {;
            optimal_bst(p, q, 5, root, costs);
            print_root_table(root, 5);
            
            BSTNode* bstRoot = construct_optimal_bst(root, keys, 0, 5);
            
            printf("\nOptimal BST structure:\n");
            printf("In-order traversal: ");
            if (bstRoot) {
                bst_inorder_traversal(bstRoot);
            } else {
                printf("(empty tree)");
            }
            printf("\n");
            break;
        }
        case 3: {
            double p2[] = {0.0, 0.04, 0.06, 0.08, 0.02, 0.10, 0.12, 0.14}; 
            double q2[] = {0.06, 0.06, 0.06, 0.06, 0.05, 0.05, 0.05, 0.05}; 
            int keys2[] = {1, 2, 3, 4, 5, 6, 7};
            
            optimal_bst(p2, q2, 7, root, costs);
            print_root_table(root, 7);
            
            BSTNode* bstRoot2 = construct_optimal_bst(root, keys2, 0, 7);
            printf("In-order traversal: ");
            if (bstRoot2) {
                bst_inorder_traversal(bstRoot2);
            }
            printf("\n");
            break;
        }
        case 4: {            
            printf("Standard O(n^3) algorithm:\n");
            clock_t start = clock();
            optimal_bst(p, q, 5, root, costs);
            clock_t end = clock();
            double time1 = ((double)(end - start)) / CLOCKS_PER_SEC;
            
            printf("\nKnuth optimized O(n^2) algorithm:\n");
            start = clock();
            knuthian_optimal_bst(p, q, 5, root, costs);
            end = clock();
            double time2 = ((double)(end - start)) / CLOCKS_PER_SEC;
            
            printf("\nPerformance comparison:\n");
            printf("Standard algorithm: %.6f seconds\n", time1);
            printf("Knuth optimization: %.6f seconds\n", time2);
            printf("Speedup factor: %.2fx\n", (time2 > 0) ? time1/time2 : 0);
            
            print_root_table(root, 5);
            break;
        }
        case 5: {
            optimal_bst(p, q, 5, root, costs);
            print_root_table(root, 5);
            
            printf("Cost table shows minimum expected search costs:\n");
            print_cost_table(costs, 5);
            
            BSTNode* bstRoot = construct_optimal_bst(root, keys, 0, 5);
            printf("Final optimal BST in-order: ");
            if (bstRoot) {
                bst_inorder_traversal(bstRoot);
            }
            printf("\n");
            break;
        }
        case 6: {
            double p_simple[] = {0.0, 0.25, 0.35, 0.40}; 
            double q_simple[] = {0.05, 0.15, 0.10, 0.15}; 
            int keys_simple[] = {10, 20, 30};
            
            printf("Simple 3-key example:\n");
            printf("Keys: k1=10, k2=20, k3=30\n");
            printf("p[] = [0.25, 0.35, 0.40]\n");
            printf("q[] = [0.05, 0.15, 0.10, 0.15]\n\n");
            
            optimal_bst(p_simple, q_simple, 3, root, costs);
            print_root_table(root, 3);
            print_cost_table(costs, 3);
            
            BSTNode* simple_tree = construct_optimal_bst(root, keys_simple, 0, 3);
            printf("Tree structure: ");
            if (simple_tree) {
                bst_inorder_traversal(simple_tree);
            }
            printf("\n");
            break;
        }
        default:
            break;
    }
    */

    return 0;
}