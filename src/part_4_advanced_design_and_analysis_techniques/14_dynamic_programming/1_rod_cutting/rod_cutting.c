#include <stdio.h>
#include <limits.h>
#include <time.h>

#define TASK 8

//----------Brute Force----------
int brute_force(int p[], int n) {
    if (n == 0) return 0;

    int q = INT_MIN;

    for (int i = 1; i <= n; i++)  
        q = (q > p[i - 1] + brute_force(p, n - i)) 
            ? q 
            : (p[i - 1] + brute_force(p, n - i));

    return q;
}

//----------Top-Down-----------
int memo[100];

void init_memo(int n) {
    for (int i = 0; i <= n; i++) memo[i] = -1;
}

int top_down(int p[], int n) {
    if (memo[n] != -1) return memo[n];
    if (n == 0) return 0;

    int q = INT_MIN;

    for (int i = 1; i <= n; i++) 
        q = (q > p[i - 1] + top_down(p, n - i)) 
            ? q 
            : (p[i - 1] + top_down(p, n - i));

    memo[n] = q;

    return q; 
}

//----------Bottom-Up-----------
int bottom_up(int p[], int n) {
    int r[n + 1];
    r[0] = 0;

    for (int j = 1; j <= n; j++) {
        int q = INT_MIN;

        for (int i = 1; i <= j; i++)
            q = (q > p[i - 1] + r[j - i]) 
                ? q 
                : (p[i - 1] + r[j - i]);

        r[j] = q;
    }

    return r[n];
}

//----------Extended Bottom-Up (returning solution, not just costs)-----------
void extended_bottom_up(int p[], int n) {
    int r[n + 1];
    int s[n + 1];

    r[0] = 0;

    for (int j = 1; j <= n; j++) {
        int q = INT_MIN;

        for (int i = 1; i <= j; i++) {
            int temp = p[i - 1] + r[j - 1];
            if (q < temp) {
                q = temp;
                s[j] = i;
            }
        }

        r[j] = q;
    }

    printf("Maximum Obtainable Value: %d\n", r[n]);
    printf("Cuts made to achieve the maximum value: ");
    int length = n;
    while (length > 0) {
        printf("%d ", s[length]);
        length -= s[length]; 
    }
    printf("\n");
}

//----------14.1-3-----------
int bottom_up_with_cost(int p[], int n, int c) {
    int r[n + 1];
    r[0] = 0;

    for (int j = 1; j <= n; j++) {
        int q = p[j - 1];

        for (int i = 1; i <= j; i++)
            q = (q > p[i - 1] + r[j - i] - c) 
                ? q 
                : (p[i - 1] + r[j - i] - c);

        r[j] = q;
    }

    return r[n];
}

//----------14.1-4-----------
int memoized_cut_rod_aux(int p[], int n, int r[], int s[]) {
    if (r[n] >= 0) return r[n];
    
    int q = INT_MIN;

    if (n == 0) q = 0;
    else {
        for (int i = 1; i <= n; i++) {
            int val = memoized_cut_rod_aux(p, n - i, r, s);
            if (q < p[i - 1] + val) {
                q = p[i - 1] + val;  
                s[n] = i;
            }
        }
    }

    r[n] = q;
    return q;
}

void memoized_cut_rod_2(int p[], int n) {
    int r[n + 1];
    int s[n + 1];

    for (int i = 0; i <= n; i++) {
        r[i] = INT_MIN;
        s[i] = 0;
    }

    int val = memoized_cut_rod_aux(p, n, r, s);
    printf("The optimal value is %d and the cuts are at: ", val);

    int j = n;
    while (j > 0) {
        printf("%d ", s[j]);
        j = j - s[j];
    }
    printf("\n");
} 

//----------14.1-5-----------
int extended_top_down(int p[], int n) {
    if (memo[n] != -1) return memo[n];
    if (n == 0) return 0;

    int s[n + 1];

    for (int j = 1; j <= n; j++) {
        int q = INT_MIN;

        for (int i = 1; i <= j; i++) {
            int temp = p[i - 1] + memo[j - i];
            if (q < temp) {
                q = temp;
                s[j] = i; 
            }
        }

        memo[j] = q;
    }
    printf("Maximum Obtainable Value: %d\n", memo[n]);
    printf("Cuts made to achieve the maximum value: ");
    int length = n;
    while (length > 0) {
        printf("%d ", s[length]);
        length -= s[length];
    }
    printf("\n");
}

//----------14.1-6-----------
int fibonacci(int n) {
    int fib[n + 1];

    fib[0] = 1;
    fib[1] = 1;

    for (int i = 2; i <= n; i++)
        fib[i] = fib[i - 1] + fib[i - 2];

    return fib[n];
}

int main(void) {
    int p[] = {
        2, 3, 5, 7, 11, 13, 17, 
        19, 23, 29, 31, 37, 41, 
        43, 47, 53, 59, 61, 67, 
        71, 73, 79, 83, 89, 97,
    };
    int n = sizeof(p) / sizeof(p[0]);
    int cost = 2;

    switch (TASK)
    {
        case 1: {
            // Brute-Force
            clock_t start = clock();
            int max_val = brute_force(p ,n);
            clock_t end = clock();

            double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC; 

            printf("Maximum Obtainable Value: %d\n", max_val);
            printf("Execution Time: %.6f seconds\n", time_taken);
            break;
        }
        case 2: {
            // Top-Down
            clock_t start = clock();
            init_memo(n);
            int max_val = top_down(p ,n);
            clock_t end = clock();

            double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC; 

            printf("Maximum Obtainable Value: %d\n", max_val);
            printf("Execution Time: %.6f seconds\n", time_taken);
            break;
        }
        case 3: {
            // Bottom-Up
            clock_t start = clock();
            int max_value = bottom_up(p, n);
            clock_t end = clock();

            double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC; 
            printf("Maximum Obtainable Value: %d\n", max_value);
            printf("Execution Time: %.6f seconds\n", time_taken);
        }
        case 4: {
            // Bottom-Up with actual solution
            clock_t start = clock();
            extended_bottom_up(p, n);
            clock_t end = clock();

            double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC; 
            printf("Execution Time: %.6f seconds\n", time_taken);
        }
        case 5: {
            // 14.1-3
            clock_t start = clock();
            int max_value = bottom_up_with_cost(p, n, cost);
            clock_t end = clock();

            double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC; 
            printf("Maximum Obtainable Value: %d\n", max_value);
            printf("Execution Time: %.6f seconds\n", time_taken);
        }
        case 6: {
            // 14.1-4
            memoized_cut_rod_2(p, n);
            break;
        }
        case 7: {
            // 14.1-5
            init_memo(n);
            extended_top_down(p, n);
            break;
        }
        case 8: {
            // 14.1-6
            int target = 10;
            printf("Fibonacci number at position %d is: %d\n", target, fibonacci(target));
            break;
        }
        default:
            break;
    }

    return 0;
}