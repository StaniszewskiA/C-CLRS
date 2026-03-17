#include "part_7_selected_topics/32_string-matching/32_string-matching.h"

#define TASK 3

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

// 32-2 TODO

// 32-3
void burrows_wheeler_transform(
    const char* T,
    const int* SA,
    int n,
    char* out
) {
    char* Tprime = safe_malloc((n + 2) * sizeof(char));
    memcpy(Tprime, T, n);
    Tprime[n] = '$';
    Tprime[n + 1] = '\0';

    for (int i = 0; i < n + 1; ++i) {
        if (SA[i] == 0) out[i] = Tprime[n];
        else out[i] = Tprime[SA[i] - 1];
    }

    out[n + 1] = '\0';

    safe_free(Tprime);
}

void test_burrows_wheeler_transform(void) {
    const char* T = "banana";
    /*
        Sufixes:
        0:"banana", 
        1:"anana", 
        2:"nana", 
        3:"ana", 
        4:"na", 
        5:"a", 
        6:""

        SA is simulated.
    */
    int SA[] = {6, 5, 3, 1, 0, 4, 2};
    int n = strlen(T);
    char bwt[n + 2];

    burrows_wheeler_transform(T, SA, n, bwt);

    printf("T:    %s\n", T);
    printf("BWT:  %s\n", bwt);

    if (strcmp(bwt, "annb$aa") == 0) printf("BWT test passed!\n\n");
    else printf("BWT test failed! Expected: annb$aa\n");
}

void compute_rank(
    const char* bwt,
    int n,
    int* rank
) {
    int alphabetSize = 256;
    int cnt[256] = {0};

    for (int i = 0; i < n; ++i) cnt[(unsigned char)bwt[i]]++;

    // count lexicographically smaller characters
    int offset[256] = {0};
    int currOffset = 0;
    for (int c = 0; c < alphabetSize; ++c) {
        offset[c] = currOffset;
        currOffset += cnt[c];
    }

    memset(cnt, 0, sizeof(cnt));

    // compute rank
    for (int i = 0; i < n; ++i) {
        unsigned char c = bwt[i];
        rank[i] = offset[c] + cnt[c] + 1;
        cnt[c]++;
    }
}

void test_compute_rank(void) {
    const char* T = "banana";
    int SA[] = {6, 5, 3, 1, 0, 4, 2};
    int n = strlen(T);
    char bwt[n + 2];

    burrows_wheeler_transform(T, SA, n, bwt);

    int rank[n + 1];
    compute_rank(bwt, n + 1, rank);

    printf("T:    %s\n", T);
    printf("BWT:  %s\n", bwt);
    printf("Rank: ");
    for (int i = 0; i < n + 1; ++i) printf("%d ", rank[i]);
    printf("\n");
}

void inverse_bwt(
    const char* bwt,
    const int* rank,
    int n,
    char* out
) {
    int dollarIdx = -1;
    for (int i = 0; i < n; ++i) {
        if (bwt[i] != '$') continue;
        dollarIdx = i;
        break;
    }

    if (dollarIdx == -1) dollarIdx = 0;

    int i = dollarIdx;
    for (int k = n - 1; k >= 0; --k) {
        out[k] = bwt[i];
        i = rank[i] - 1;
    }

    out[n] = '\0';
}

void test_inverse_bwt(void) {
    const char* T = "banana";
    int SA[] = {6, 5, 3, 1, 0, 4, 2};
    int n = strlen(T);
    char bwt[n + 2];
    burrows_wheeler_transform(T, SA, n, bwt);

    int rank[n + 1];
    compute_rank(bwt, n + 1, rank);

    char out[n + 2];
    inverse_bwt(bwt, rank, n + 1, out);

    printf("BWT:   %s\n", bwt);
    printf("T':    %s\n", out);
    printf("Expected: banana$\n");
    if (strcmp(out, "banana$") == 0) printf("Inverse BWT test passed!\n\n");
    else printf("Inverse BWT test failed!\n");
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

        case 3: {
            test_burrows_wheeler_transform();
            test_compute_rank();
            test_inverse_bwt();
            break;
        }

        default:
            break;
    }
    
    return 0;
}