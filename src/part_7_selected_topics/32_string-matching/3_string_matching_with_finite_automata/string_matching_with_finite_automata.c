#include "part_7_selected_topics/32_string-matching/32_string-matching.h"

// 32.3-1
void compute_transition_function(char* P, int m, int delta[][ALPHABET_SIZE]) {
    for (int q = 0; q <= m; ++q) {
        for (int a = 0; a < ALPHABET_SIZE; ++a) {
            int k = MIN(m, q + 1);
            while (k > 0 && (P[k - 1] != (char)a || memcmp(P, P + q - k + 1, k - 1) != 0)) k--;
            delta[q][a] = k;
        }
    }
}

void finite_automaton_matcher(char* T, int n, char* P, int m, int delta[][ALPHABET_SIZE]) {
    compute_transition_function(P, m, delta);
    
    int q = 0;
    for (int i = 0; i < n; ++i) {
        q = delta[q][(unsigned char)T[i]];
        if (q == m) printf("Pattern occurs at shift %d\n", i - m + 1);
    }
}

void test_finite_automaton_matcher(void) {
    char T[] = "aaababaabaababaab";
    int n = (int)strlen(T);

    char P[] = "aabab";
    int m = (int)strlen(P);

    int delta[m + 1][ALPHABET_SIZE];

    finite_automaton_matcher(T, n, P, m, delta);
}

// 32.3-6
static int split_pattern(char* P, char subs[MAX_SUBS][MAX_SUB_LEN], int* subLens) {
    int subCnt = 0;
    int i = 0;
    int j = 0;

    while (P[i]) {
        char c = P[i++];

        if (c == '*') {
            if (j > 0) {
                subs[subCnt][j] = '\0';
                subLens[subCnt++] = j;
                j = 0;
            }
            continue;
        }

        subs[subCnt][j++] = c;
    }

    if (j > 0) {
        subs[subCnt][j] = '\0';
        subLens[subCnt++] = j;
    }

    return subCnt;
}

void finite_automaton_gap_matcher(char* T, int m, char* P) {
    char subs[MAX_SUBS][MAX_SUB_LEN];
    int subLens[MAX_SUBS];
    int subCnt = split_pattern(P, subs, subLens);
    int subIdx = 0;

    for (int s = 0; s < subCnt; ++s) {
        int n = subLens[s];
        int delta[m + 1][ALPHABET_SIZE];

        compute_transition_function(subs[s], n, delta);
        
        int q = 0;
        int found = 0;

        for (int i = subIdx; i < m; ++i) {
            q = delta[q][(unsigned char)T[i]];

            if (q == n) {
                int shift = i - n + 1;
                printf("Pattern occurs at shift %d\n", shift);

                found = 1;
                q = 0;
            }
        }

        if (!found) {
            printf("Pattern does not match.\n");
            return;
        }

        subIdx = m;
    }
}

void test_finite_automaton_gap_matcher(void) {
    char T[] = "00010001";
    int n = (int)strlen(T);

    char P[] = "000*";

    finite_automaton_gap_matcher(T, n, P);
}
