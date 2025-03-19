#include <stdio.h>

#define TASK 3

void recursive_activity_selector(int s[], int f[], int k, int n)  {
    int m = k + 1;

    while (m <= n && s[m] < f[k]) m++;

    if (m <= n) {
        printf("Chosen activity idx: %d\n", m);
        recursive_activity_selector(s, f, m, n);
    }
}

/*
    Θ(n)
*/
void greedy_activity_selector(int s[], int f[], int n) {
    int k = 0;

    for (int m = 1; m < n; m++) {
        if (s[m] >= f[k]) {
            printf("Chosen activity idx: %d\n", m);
            k = m;
        }
    }
}

/*
    15.1-1

    Ο(n^3)
*/
#define MAX_N 100

int dp1[MAX_N + 2][MAX_N + 2];
int act[MAX_N + 2][MAX_N + 2];

void print_activities(int i, int j) {
    if (dp1[i][j] > 0) {
        int k = act[i][j];
        if (k != 0) {
            printf("%d, ", k);
            print_activities(i, k);
            print_activities(k, j);
        }
    }
}

void dynamic_activity_selector(int s[], int f[], int n) {
    int i, l, j, k;

    for (i = 0; i <= n; i++) {
        dp1[i][i] = 0;
        dp1[i][i + 1] = 0;
    }
    // Base case
    dp1[n + 1][n + 1] = 0;

    for (l = 2; l <= n + 1; l++) {
        for (i = 0; i <= n - l + 1; i++) {
            j = i + l;
            dp1[i][j] = 0;
            k = j - 1;
            while (k > i && f[i] < f[k]) {
                if (f[i] <= s[k] && f[k] <= s[j]
                    && (dp1[i][k] + dp1[k][j] + 1 > dp1[i][j]))
                {
                    dp1[i][j] = dp1[i][k] + dp1[k][j] + 1;
                    act[i][j] = k;
                }
                k--;
            }
        }
    }

    printf("A maximum size set of mutually compatible activities has size %d\n", dp1[0][n + 1]);
    printf("The set contains: ");
    print_activities(0, n + 1);
    printf("\n");
}

int main(void) {
    int s[] = {0, 1, 3, 5, 8, 5};  
    int f[] = {0, 2, 4, 7, 9, 9};  
    int n = sizeof(s) / sizeof(s[0]) - 1;

    switch (TASK)
    {
        case 1: {
            recursive_activity_selector(s, f, 0, n);
            break;
        }

        case 2: {
            greedy_activity_selector(s, f, n);
            break;
        }

        case 3: {
            // 15.1-1
            dynamic_activity_selector(s, f, n);
            break;
        }
        
        default:
            break;
    }
}