#include "part_7_selected_topics/32_string-matching/32_string-matching.h"

// 32.1-1
void naive_string_matcher(char* T, char* P, int n, int m) {
    for (int s = 0; s <= n - m; ++s) {
        int match = 1;
        printf("Comparing T[%d...%d] with P[0...%d]: ", s, s + m - 1, m - 1);
        for (int j = 0; j < m; ++j) {
            printf("%c-%c ", T[s + j], P[j]);
            if (T[s + j] != P[j]) {
                match = 0;
                break;
            }
        }
        printf("\n");
        if (match) printf("Pattern occurs at shift %d\n", s);
    }
}

void test_naive_string_matcher(void) {
    char T[] = "000010001010001";
    char P[] = "0001";
    int n = (int)strlen(T);
    int m = (int)strlen(P);
    naive_string_matcher(T, P, n, m);
}

// 32.1-2
void naive_string_matcher_distinct(char* T, char* P, int n, int m) {
    int s = 0;
    while (s <= n - m) {
        printf("Comparing T[%d...%d] with P[0...%d]", s, s + m - 1, m - 1);
        int j = 0;
        for (; j < m; ++j) {
            printf("%c-%c ", T[s + j], P[j]);
            if (T[s + j] != P[j]) break;
        }
        printf("\n");
        if (j == m) {
            printf("Pattern occurs at shift %d\n", s);
            s++;
        } else if (j == 0) {
            s++;
        } else s += j; // Skip
    }
}

void test_naive_string_matcher_distinct(void) {
    char T[] = "000010001010001";
    char P[] = "0001";
    int n = (int)strlen(T);
    int m = (int)strlen(P);
    naive_string_matcher_distinct(T, P, n, m);
}

// 32.1-4
int gap_string_matcher(const char* T, const char* P, int n, int m) {
    int dp[n + 1][m + 1];
    dp[0][0] = 1;

    for (int i = 1; i <= n; ++i) dp[i][0] = 0;
    for (int j = 1; j <= m; ++j) dp[0][j] = dp[0][j - 1] && (P[j - 1] == '*');

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (P[j - 1] == '*') dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
            else dp[i][j] = dp[i - 1][j - 1] && (T[i - 1] == P[j - 1]);
        }
    }

    return dp[n][m];
}

void test_gap_string_matcher(void) {
    const char* T = "000010001010001";
    const char* P = "000*";
    int n = (int)strlen(T);
    int m = (int)strlen(P);
    printf("Pattern \"%s\" %s text \"%s\"\n", 
        P, gap_string_matcher(T, P, n, m) ? "matches" : "does not match", T);
}
