#include "part_4_advanced_design_and_analysis_techniques/14_dynamic_programming/dynamic_programming.h"

#define TASK 7

int main(void) {
    srand((unsigned int)time(NULL));

    char X[SEQ_LEN + 1]; 
    char Y[SEQ_LEN + 1];

    generate_random_binary_string(X, SEQ_LEN);
    generate_random_binary_string(Y, SEQ_LEN);

    int m = strlen(X);
    int n = strlen(Y);

    int b[m + 1][n + 1];  
    int c[m + 1][n + 1];

    switch (TASK)
    {
        case 1: {
            // Brute-Force LCS
            clock_t start = clock();
            int result = lcs_brute_force(X, Y, m, n);
            clock_t end = clock();

            double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC; 
            printf("LCS: %d\n", result);
            printf("Execution Time: %.6f seconds\n", time_taken);
            break;
        }
        case 2: {
            // Dynamic Programming LCS
            clock_t start = clock();
            int result = lcs_dp(X, Y, m, n, b, c);
            clock_t end = clock();

            double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC; 
            printf("LCS Length: %d\n", result);
            printf("Execution Time: %.6f seconds\n", time_taken);

            printf("LCS: ");
            print_lcs(b, X, m, n);  
            printf("\n");
            break;
        }
        case 3: {
            // 14.4-1
            char seq_a[] = "10010101";
            char seq_b[] = "010110110";

            int len_a = strlen(seq_a);
            int len_b = strlen(seq_b);

            int result = lcs_dp(seq_a, seq_b, len_a, len_b, b, c);

            printf("LCS Length: %d\n", result);
            printf("LCS Sequence: ");
            print_lcs(b, seq_a, len_a, len_b);  
            printf("\n");

            break;
        }
        case 4: {
            // 14.4-2
            char seq_a[] = "10010101";
            char seq_b[] = "010110110";

            int len_a = strlen(seq_a);
            int len_b = strlen(seq_b);

            int result = lcs_dp(seq_a, seq_b, len_a, len_b, b, c);

            printf("LCS Length: %d\n", result);
            printf("LCS Sequence: ");
            print_lcs_no_b(c, seq_a, seq_b, len_b, len_b);  
            printf("\n");

            break;
        }
        case 5: {
            // 14.4-3
            char seq_a[] = "10010101";
            char seq_b[] = "010110110";

            int len_a = strlen(seq_a);
            int len_b = strlen(seq_b);

            int result = memoized_lcs_len(c, seq_a, seq_b, len_a, len_b);

            printf("LCS Length: %d\n", result);

            break;
        }
        case 6: {
            // 14.4-5
            char X[SEQ_LEN] = "231432"; 
            char Y[SEQ_LEN];

            int c[SEQ_LEN][SEQ_LEN] = {0};  
            int b[SEQ_LEN][SEQ_LEN] = {0};

            strcpy(Y, X);
            int m = strlen(X); 
            int n = m;

            qsort(Y, m, sizeof(char), compare);

            memo_lcs_length(X, Y, c, b, m, n);
            printf("Length of LCS: %d\n", c[m][n]);

            break;
        }
        case 7: {
            // 14.4-6
            int A[] = {3, 10, 2, 1, 20};
            int n = sizeof(A) / sizeof(A[0]);
            long_monotonic(A, n);

            break;
        }
        default:
            break;
    }

    return 0;
}