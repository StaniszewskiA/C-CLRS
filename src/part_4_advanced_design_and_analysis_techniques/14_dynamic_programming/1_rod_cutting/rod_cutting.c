#include "part_4_advanced_design_and_analysis_techniques/14_dynamic_programming/dynamic_programming.h"

int rod_cutting_brute_force(int p[], int n) {
    if (n == 0) return 0;

    int q = INT_MIN;

    for (int i = 1; i <= n; i++)  
        q = (q > p[i - 1] + rod_cutting_brute_force(p, n - i)) 
            ? q 
            : (p[i - 1] + rod_cutting_brute_force(p, n - i));

    return q;
}

int rod_cutting_top_down(int p[], int n) {
    if (memo[n] != -1) return memo[n];
    if (n == 0) return 0;

    int q = INT_MIN;

    for (int i = 1; i <= n; i++) 
        q = (q > p[i - 1] + rod_cutting_top_down(p, n - i)) 
            ? q 
            : (p[i - 1] + rod_cutting_top_down(p, n - i));

    memo[n] = q;

    return q; 
}

int rod_cutting_bottom_up(int p[], int n) {
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

void rod_cutting_extended_bottom_up(int p[], int n) {
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

int rod_cutting_bottom_up_with_cost(int p[], int n, int c) {
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

int rod_cutting_extended_top_down(int p[], int n) {
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

    return memo[n];
}

int dp_fibonacci(int n) {
    int fib[n + 1];

    fib[0] = 1;
    fib[1] = 1;

    for (int i = 2; i <= n; i++)
        fib[i] = fib[i - 1] + fib[i - 2];

    return fib[n];
}
