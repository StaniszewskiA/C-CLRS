#include "part_4_advanced_design_and_analysis_techniques/14_dynamic_programming/dynamic_programming.h"

#define TASK 1

int main(void) {
    int p[] = {5, 10, 3, 12, 5, 50, 6};
    int n = sizeof(p) / sizeof(p[0]) - 1; 
    int s[100][100] = {0};

    printf("Matrix dimensions:\n");
    for (int i = 1; i <= n; i++) {
        printf("A%d: %dx%d\n", i, p[i-1], p[i]);
    }
    printf("\n");

    switch (TASK) {
        case 1: {            
            clock_t start = clock();
            int min_ops = matrix_chain_order(p, n, s); 
            clock_t end = clock();
            
            double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
            
            printf("Minimum number of scalar multiplications: %d\n", min_ops);
            printf("Optimal parenthesization: ");
            print_optimal_parens(s, 1, n); 
            printf("\n");
            printf("Execution Time: %.6f seconds\n", time_taken);
            break;
        }
        case 2: {
            int* A[7];  
            for (int i = 1; i <= n; i++) { 
                A[i] = (int*)malloc(sizeof(int));
                *A[i] = p[i]; 
            }

            matrix_chain_order(p, n, s);  
            
            printf("Optimal parenthesization: ");
            print_optimal_parens(s, 1, n);  
            printf("\n");
            
            printf("Demo multiplication result: %d\n", 
                   matrix_chain_multiply(A, s, 1, n));  

            for (int i = 1; i <= n; i++) {  
                free(A[i]);
            }
            break;
        }
        
        default:
            break;
    }
    
    return 0;  
}