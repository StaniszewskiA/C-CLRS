#include "part_7_selected_topics/32_string-matching/32_string-matching.h"

int* compute_prefix_function(const char* P, int m) {
    int* pi = (int*)safe_malloc((m + 1) * sizeof(int));
    pi[1] = 0;
    int k = 0;

    for (int q = 2; q <= m; ++q) {
        while (k > 0 && P[k] != P[q - 1]) k = pi[k];
        if (P[k]== P[q - 1]) k += 1;
        pi[q] = k;
    }

    return pi;
}

void kmp_matching(const char* T, const char* P, int n, int m) {
    int* pi = compute_prefix_function(P, m);
    int q = 0;

    for (int i = 1; i <= n; ++i) {
        while (q > 0 && P[q] != T[i - 1]) q = pi[q];
        if (P[q] == T[i - 1]) q += 1;
		if (q == m) {
			printf("The pattern appears with a shift %d\n", i - m);
			q = pi[q];
		}
    }

    safe_free(pi);
}

void test_kmp_matching(void) {
    const char* T = "ABC ABCDAB ABCDABCDABDE";
    const char* P = "ABCDABD";
    int n = strlen(T);
    int m = strlen(P);
    kmp_matching(T, P, n, m);
}

// 32.4-3
void concat_kmp_matching(const char* T, const char* P, int n, int m) {
    int sLen = m + n;
    char* S = (char*)safe_malloc((sLen + 1) * sizeof(char));
    memcpy(S, P, m);
    memcpy(S + m, T, n);
    S[sLen] = '\0';

    int* pi = compute_prefix_function(S, sLen);

    for (int i = m + 1; i <= sLen; ++i) {
        if (pi[i] != m || i - pi[i] < m) continue;
        int idx = i - 2 * m;
        printf("Pattern appears at shift %d\n", idx);
    }

    safe_free(S);
    safe_free(pi);
}


void test_concat_kmp_matching(void) {
    const char* T = "ABC ABCDAB ABCDABCDABDE";
    const char* P = "ABCDABD";
    int n = strlen(T);
    int m = strlen(P);
    concat_kmp_matching(T, P, n, m);
}

// 32.4-6
int* compute_prime_prefix_function(const char* P, int m, const int* pi) {
    int* piPrime = (int*)safe_malloc((m + 1) * sizeof(int));
    piPrime[1] = 0;
    
    for (int q = 2; q <= m; ++q) {
        if (pi[q] == 0) piPrime[q] = 0;
        else if (P[pi[q] + 1] == P[q + 1]) piPrime[q] = piPrime[pi[q]];
        else piPrime[q] = pi[q];
    }

    return piPrime;
}

void kmp_matching_prime_prefix(const char* T, const char* P, int n, int m) {
    int* pi = compute_prefix_function(P, m);
    int* piPrime = compute_prime_prefix_function(P, m, pi);
    int q = 0;

    for (int i = 1; i <= n; ++i) {
        while (q > 0 && P[q] != T[i - 1]) q = piPrime[q];
        if (P[q] == T[i - 1]) q += 1;
        if (q == m) {
            printf("The pattern appears with a shift %d\n", i - m);
            q = pi[q];
        }
    }

    safe_free(pi);
    safe_free(piPrime);
}

void test_kmp_matching_prime_prefix(void) {
    const char* T = "ABC ABCDAB ABCDABCDABDE";
    const char* P = "ABCDABD";
    int n = strlen(T);
    int m = strlen(P);
    kmp_matching_prime_prefix(T, P, n, m);
}

// 32.4-7
static bool kmp_search(const char* T, const char* P, int n, int m) {
    int* pi = compute_prefix_function(P, m);
    int q = 0;

    for (int i = 1; i <= n; ++i) {
        while (q > 0 && P[q] != T[i - 1]) q = pi[q];
        if (P[q] == T[i - 1]) q += 1;
        if (q == m) {
            safe_free(pi);
            return true;
        }
    }

    safe_free(pi);
    return false;
}

bool is_cyclic_rotation(
    const char* T, 
    const char* TPrime, 
    int n, 
    int m
) {
    if (n != m) return false;

    char* TT = (char*)safe_malloc((2 * n + 1) * sizeof(char));
    memcpy(TT, T, n);
    memcpy(TT + n, T, n);
    TT[2 * n] = '\0';

    bool found = kmp_search(TT, TPrime, 2 * n, n);

    safe_free(TT);

    return found;
}

void test_is_cyclic_rotation(void) {
    const char* T = "braze";
    const char* TPrime = "zebra";
    int n = strlen(T);
    int m = strlen(TPrime);
    printf("Is T a cyclic rotation of T'? %d\n", is_cyclic_rotation(T, TPrime, n, m));
}

// 32.4-8
void compute_transition_function_kmp(
    const char* P,
    int m,
    const char* Sigma,
    int sigmaSize,
    int** delta
) {
    int* pi = compute_prefix_function(P, m);

    for (int i = 0; i < sigmaSize; ++i) delta[0][i] = 0;

    for (int i = 0; i < sigmaSize; ++i)
        if (P[0] == Sigma[i]) delta[0][i] = 1;

    for (int q = 1; q <= m; ++q) {
        for (int i = 0; i < sigmaSize; ++i) {
            char a = Sigma[i];
            if (q == m || P[q + 1] != a) delta[q][i] = delta[pi[q]][i];
            else delta[q][i] = q + 1;
        }
    }

    safe_free(pi);
}

void test_compute_transition_function_kmp(void) {
    const char* P = "ababaca";
    int m = strlen(P);

    const char* Sigma = "abc";
    int sigmaSize = strlen(Sigma);

    int** delta = (int**)safe_malloc((m + 1) * sizeof(int*));
    for (int q = 0; q <= m; ++q) delta[q] = (int*)safe_malloc(sigmaSize * sizeof(int));

    compute_transition_function_kmp(P, m, Sigma, sigmaSize, delta);

        printf("Transition table for pattern '%s':\n", P);
    printf("    ");
    for (int i = 0; i < sigmaSize; ++i) printf("  %c", Sigma[i]);
    printf("\n");
    for (int q = 0; q <= m; ++q) {
        printf("q=%d:", q);
        for (int i = 0; i < sigmaSize; ++i) printf(" %2d", delta[q][i]);
        printf("\n");
    }

    for (int q = 0; q <= m; ++q) safe_free(delta[q]);
    safe_free(delta);
}
