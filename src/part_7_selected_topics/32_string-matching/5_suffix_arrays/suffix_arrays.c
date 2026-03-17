#include "part_7_selected_topics/32_string-matching/32_string-matching.h"

static int cmp_ranks(const void* a, const void* b) {
    const SubstrRank* sa = (const SubstrRank*)a;
    const SubstrRank* sb = (const SubstrRank*)b;

    if (sa->leftRank != sb->leftRank)
        return sa->leftRank - sb->leftRank;

    return sa->rightRank - sb->rightRank;
}

static void print_sr(const char* title, SubstrRank* sr, int n) {
    printf("\n%s\n", title);
    printf("idx | left | right\n");
    printf("------------------\n");
    for (int i = 0; i < n; ++i)
        printf("%3d | %4d | %5d\n",
            sr[i].idx, sr[i].leftRank, sr[i].rightRank);
}

static void print_ranks(int* ranks, int n) {
    printf("ranks:\n");
    for (int i = 0; i < n; ++i)
        printf("r[%d]=%d ", i, ranks[i]);
    printf("\n");
}

static void make_ranks(SubstrRank* sr, int* ranks, int n) {
    int r = 0;
    ranks[sr[0].idx] = r;

    for (int i = 1; i < n; ++i) {
        if (sr[i].leftRank != sr[i - 1].leftRank ||
            sr[i].rightRank != sr[i - 1].rightRank)
            ++r;
        ranks[sr[i].idx] = r;
    }
}

int* compute_suffix_array(const char* T, int n) {
    SubstrRank* sr = (SubstrRank*)safe_malloc(n * sizeof(SubstrRank));
    int* ranks = (int*)safe_malloc(n * sizeof(int));
    int* SA = (int*)safe_malloc(n * sizeof(int));
    
    for (int i = 0; i < n; ++i) {
        sr[i].leftRank  = (int)T[i];
        sr[i].rightRank = (i + 1 < n) ? (int)T[i + 1] : -1;
        sr[i].idx = i;
    }

    qsort(sr, n, sizeof(SubstrRank), cmp_ranks);
    print_sr("INIT substr-rank (after first sort)", sr, n);

    int l = 2;
    int iter = 1;

    while (l < n) {
        printf("\n=== WHILE ITERATION %d, l = %d ===\n", iter++, l);

        print_sr("Before make_ranks", sr, n);
        make_ranks(sr, ranks, n);
        print_ranks(ranks, n);

        for (int i = 0; i < n; ++i) {
            int pos = sr[i].idx;
            sr[i].leftRank = ranks[pos];
            sr[i].rightRank =
                (pos + l < n) ? ranks[pos + l] : -1;
        }

        qsort(sr, n, sizeof(SubstrRank), cmp_ranks);
        print_sr("After sorting updated substr-rank", sr, n);

        l <<= 1;
    }

    
    print_sr("\nFINAL substr-rank", sr, n);

    for (int i = 0; i < n; ++i)
        SA[i] = sr[i].idx;

    safe_free(sr);
    safe_free(ranks);

    return SA;
}


void text_compute_suffix_array(void) {
    const char* T = "banana";
    int n = strlen(T);

    int* SA = compute_suffix_array(T, n);

    printf("Suffix Array:\n");
    for (int i = 0; i < n; ++i)
        printf("%d: %s\n", SA[i], T + SA[i]);

    safe_free(SA);
}

int* compute_lcp(const char* T, int* SA, int n) {
    int* ranks = (int*)safe_malloc(n * sizeof(int));
    int* LCP = (int*)safe_malloc(n * sizeof(int));

    for (int i = 0; i < n; ++i) ranks[SA[i]] = i;

    LCP[0] = 0;
    int l = 0;

    printf("\nCOMPUTE-LCP TRACE\n");
    printf("i  rank  j  LCP\n");
    printf("----------------\n");


    for (int i = 1; i < n; ++i) {
        int r = ranks[i];

        if (r == 0) {
            l = 0;
            printf("%2d  %3d  -   0\n", i, r);
            continue;
        }

        int j = SA[r - 1];

        while (i + l < n && j + l < n && T[i + l] == T[j + l]) ++l;

        LCP[r] = l;
        printf("%2d  %3d %3d   %d\n", i, r, j, l);

        if (l > 0) --l;
    }

    safe_free(ranks);

    return LCP;
}

void test_compute_lcp(void) {
    const char* T = "banana";
    int n = strlen(T);

    int* SA = compute_suffix_array(T, n);
    int* LCP = compute_lcp(T, SA, n);

    printf("i   SA   LCP   suffix\n");
    printf("---------------------\n");

    for (int i = 0; i < n; ++i) {
        printf("%d   %d    %d    %s\n",
            i,
            SA[i],
            LCP[i],
            T + SA[i]);
    }

    safe_free(SA);
    safe_free(LCP);
}

// 32.5-1
void test_compute_lcp_hippity_hoppity(void) {
    const char* T = "hippityhoppity";
    int n = strlen(T);

    int* SA = compute_suffix_array(T, n);

    printf("\nFINAL SUFFIX ARRAY\n");
    printf("i  SA  suffix\n");
    printf("--------------\n");
    for (int i = 0; i < n; ++i)
        printf("%2d %3d  %s\n", i, SA[i], T + SA[i]);

    int* LCP = compute_lcp(T, SA, n);

    printf("\nFINAL LCP ARRAY\n");
    for (int i = 0; i < n; ++i)
        printf("LCP[%d] = %d\n", i, LCP[i]);

    safe_free(SA);
    safe_free(LCP);
}

// 32.5-2
static bool make_ranks_early(SubstrRank* sr, int* ranks, int n) {
    int r = 0;
    ranks[sr[0].idx] = r;

    for (int i = 1; i < n; ++i) {
        if (sr[i].leftRank != sr[i - 1].leftRank ||
            sr[i].rightRank != sr[i - 1].rightRank)
            ++r;
        ranks[sr[i].idx] = r;
    }

    return (r == n - 1);
}

int* compute_suffix_array_early(const char* T, int n) {
    SubstrRank* sr = (SubstrRank*)safe_malloc(n * sizeof(SubstrRank));
    int* ranks = (int*)safe_malloc(n * sizeof(int));
    int* SA = (int*)safe_malloc(n * sizeof(int));
    
    for (int i = 0; i < n; ++i) {
        sr[i].leftRank  = (int)T[i];
        sr[i].rightRank = (i + 1 < n) ? (int)T[i + 1] : -1;
        sr[i].idx = i;
    }

    qsort(sr, n, sizeof(SubstrRank), cmp_ranks);

    int l = 2;

    while (l < n) {
        bool done = make_ranks_early(sr, ranks, n);

        if (done) break;

        for (int i = 0; i < n; ++i) {
            int pos = sr[i].idx;
            sr[i].leftRank = ranks[pos];
            sr[i].rightRank =
                (pos + l < n) ? ranks[pos + l] : -1;
        }

        qsort(sr, n, sizeof(SubstrRank), cmp_ranks);

        l <<= 1;
    }

    for (int i = 0; i < n; ++i)
        SA[i] = sr[i].idx;

    safe_free(sr);
    safe_free(ranks);

    return SA;
}


void test_compute_suffix_array_early(void) {
    const char* bestT = "abcdefg";
    int nBest = strlen(bestT);

    int* bestSA = compute_suffix_array_early(bestT, nBest);

    printf("\nBEST CASE (O(1) iterations)\n");
    printf("Suffix Array for \"%s\":\n", bestT);
    for (int i = 0; i < nBest; ++i)
        printf("%2d: %s\n", bestSA[i], bestT + bestSA[i]);

    safe_free(bestSA);

    const char* worstT = "abababababab";
    int nWorst = strlen(worstT);

    int* worstSA = compute_suffix_array_early(worstT, nWorst);

    printf("\nWORST CASE (Theta(log n) iterations)\n");
    printf("Suffix Array for \"%s\":\n", worstT);
    for (int i = 0; i < nWorst; ++i)
        printf("%2d: %s\n", worstSA[i], worstT + worstSA[i]);

    safe_free(worstSA);
}

// 32.5-3
static int which_text(int pos, int n1) {
    if (pos < n1) return 1;
    if (pos > n1) return 2;
    return 0;
}

void longest_common_substrings(const char* T1, const char* T2) {
    int n1 = strlen(T1);
    int n2 = strlen(T2);
    int n = n1 + n2 + 2;

    char* T = (char*)safe_malloc((n + 1) * sizeof(char));

    memcpy(T, T1, n1);
    T[n1] = '#';
    memcpy(T + n1 + 1, T2, n2);
    T[n1 + n2 + 1] = '$';
    T[n] = '\0';

    int* SA = compute_suffix_array(T, n);
    int* LCP = compute_lcp(T, SA, n);

    int best = 0;

    for (int i = 1; i < n; ++i) {
        int a = which_text(SA[i], n1);
        int b = which_text(SA[i - 1], n1);

        if (a != 0 && b != 0 && a != b) {
            if (LCP[i] > best)
                best = LCP[i];
        }
    }

    printf("\nLONGEST COMMON SUBSTRINGS\n");
    printf("T1 = \"%s\"\n", T1);
    printf("T2 = \"%s\"\n", T2);
    printf("Length = %d\n", best);

    for (int i = 1; i < n; ++i) {
        int a = which_text(SA[i], n1);
        int b = which_text(SA[i - 1], n1);

        if (a != 0 && b != 0 && a != b) {
            if (LCP[i] == best && best > 0) {
                printf("  \"%.*s\"\n", best, T + SA[i]);
            }
        }
    }

    safe_free(T);
    safe_free(SA);
    safe_free(LCP);
}


void test_longest_common_substrings(void) {
    longest_common_substrings("banana", "ananas");
    longest_common_substrings("hippity", "hoppity");
}

// 32.5-4
void possibly_longest_palindromes(const char* T) {
    int n = strlen(T);
    int nPrime = 2 * n + 1;

    char* TPrime = (char*)safe_malloc((nPrime + 1) * sizeof(char));

    memcpy(TPrime, T, n);
    TPrime[n] = '@';
    for (int i = 0; i < n; ++i) TPrime[n + 1 + i] = T[n - 1 - i];
    TPrime[nPrime] = '\0';

    int* SA = compute_suffix_array(TPrime, nPrime);
    int* LCP = compute_lcp(TPrime, SA, nPrime);
    int best = 0;

        for (int i = 1; i < nPrime; ++i) {
        int left = SA[i - 1];
        int right = SA[i];
        int lcp = LCP[i];

        if (left == nPrime - right - lcp + 1) if (lcp > best) best = lcp;
    }

    printf("\nLONGEST PALINDROMES\n");
    printf("T = \"%s\"\n", T);
    printf("Length = %d\n", best);

    for (int i = 1; i < nPrime; ++i) {
        int left = SA[i - 1];
        int right = SA[i];
        int lcp = LCP[i];

        if (left == nPrime - right - lcp + 1 && lcp == best && best > 0)
            printf("  \"%.*s\"\n", best, TPrime + right);
    }
    
    safe_free(TPrime);
    safe_free(SA);
    safe_free(LCP);
}

void test_possibly_longest_palindromes(void) {
    possibly_longest_palindromes("unreferenced");
    possibly_longest_palindromes("banana");
    possibly_longest_palindromes("abacdfgdcaba");
}
