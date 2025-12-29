#include "part_7_selected_topics/32_string-matching/32_string-matching.h"

#define TASK 2

// 32-1
int* repetition_factors(const char* P) {
    int n = strlen(P);
    int* pi = compute_prefix_function(P, n);
    int* rep = malloc((n + 1) * sizeof(int));

    rep[0] = 1;

    for (int i = 1; i <= n; ++i) {
        int k = i - pi[i - 1];
        if (pi[i - 1] > 0 && i % k == 0)
            rep[i] = i / k;
        else
            rep[i] = 1;
    }

    safe_free(pi);
    return rep;
}

void test_repetition_factors(void) {
    const char* P;
    int* rep;
    int n;

    P = "ababab";
    n = strlen(P);
    rep = repetition_factors(P);

    printf("Pattern: \"%s\"\n", P);
    for (int i = 1; i <= n; ++i) printf("i=%2d  repetition=%d\n", i, rep[i]);

    safe_free(rep);
    printf("\n");

    P = "aaaaaa";
    n = strlen(P);
    rep = repetition_factors(P);

    printf("Pattern: \"%s\"\n", P);
    for (int i = 1; i <= n; ++i) printf("i=%2d  repetition=%d\n", i, rep[i]);

    safe_free(rep);
    printf("\n");
}

void repetition_matcher(const char* P, const char* T, int n, int m) {
    int* pi = compute_prefix_function(P, m);
    int k = m - pi[m - 1];
    if (m % k) k = m;

    int q = 0;
    int s = 0;

    printf("Pattern: \"%s\"\n", P);
    printf("Text:    \"%s\"\n", T);
    printf("Matches at shifts:\n");

    while (s <= n - m) {
        while (q < m && T[s + q] == P[q]) ++q;

        if (q == m) printf("  s = %d\n", s);

        int shift = q / k;
        if (shift < 1) shift = 1;

        s += shift;
        q = 0;
    }

    safe_free(pi);
}

void test_repetition_matcher(void) {
    repetition_matcher("abab", "abababab", 8, 4);
    printf("\n");
    repetition_matcher("aaaa", "aaaaaaaa", 8, 4);
    printf("\n");
}


int main(void) {
    switch (TASK)
    {
        case 1: {
            test_repetition_factors();
            break;
        }
        
        case 2: {
            test_repetition_matcher();
            break;
        }

        default:
            break;
    }
    
    return 0;
}