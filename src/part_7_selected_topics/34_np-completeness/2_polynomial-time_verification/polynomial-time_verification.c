#include "part_7_selected_topics/34_np-completeness/34_np-completeness.h"

// 34.2-1
int verify_graph_isomorphism(
    const int* adjMat1,
    int n1,
    const int* adjMat2,
    int n2,
    const int* f
) {
    if (n1 != n2) return 0;
    int n = n1;

    // f has to be a bijection
    int* used = safe_calloc(n, sizeof(int));
    int valid = 1;
    for (int u = 0; u < n && valid; ++u) {
        valid = f[u] >= 0 && f[u] < n && !used[f[u]];
        if (valid) used[f[u]] = 1;
    }

    safe_free(used);
    if (!valid) return 0;

    // (u , v) in E_1 <=> (f(u), f(v)) in E_2
    for (int u = 0; u < n; ++u)
        for (int v = 0; v < n; ++v)
            if (adjMat1[u * n + v] != adjMat2[f[u] * n + f[v]]) return 0;

    return 1;
}

static int gi_next_permutation(
    int* a,
    int n
) {
    int i = n - 2;
    while (i >= 0 && a[i] >= a[i + 1]) i--;
    if (i < 0) return 0;

    int j = n - 1;
    while (a[j] <= a[i]) j--;
    SWAP_INT(a[i], a[j]);

    for (int l = i + 1, r = n - 1; l < r; ++l, --r)
        SWAP_INT(a[l], a[r]);

    return 1;
}

static int gi_count_isomorphisms(
    const int* adjMat1,
    const int* adjMat2,
    int n
) {
    int f[GI_N_VERTICES];
    for (int u = 0; u < n; ++u) f[u] = u;

    int cnt = 0;
    do {
        cnt += verify_graph_isomorphism(
            adjMat1,
            n,
            adjMat2,
            n,
            f
        );
    } while (gi_next_permutation(f, n));

    return cnt;
}

void test_verify_graph_isomorphism(void) {
    // G1: cycle 0 - 1 - 2 - 3 - 0
    int G1[GI_N_VERTICES][GI_N_VERTICES] = {
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}
    };
    // G2: cycle 0 - 2 - 1 - 3 - 0
    int G2[GI_N_VERTICES][GI_N_VERTICES] = {
        {0, 0, 1, 1},
        {0, 0, 1, 1},
        {1, 1, 0, 0},
        {1, 1, 0, 0}
    };
    // G3: triangle 0 - 1 - 2 with edge 2 - 3, also 4 edges
    int G3[GI_N_VERTICES][GI_N_VERTICES] = {
        {0, 1, 1, 0},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {0, 0, 1, 0}
    };
    // K3: 0 - 1 - 2
    int K3[3][3] = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}
    };
    int n = GI_N_VERTICES;

    int certificates[][GI_N_VERTICES] = {
        {0, 2, 1, 3},
        {0, 1, 2, 3},
        {0, 0, 1, 3},
        {0, 2, 1, 4}
    };
    const char* notes[] = {
        "isomorphism",
        "bijection, but (0, 1) is not an edge of G2",
        "not a bijection",
        "4 is not a vertex of G2"
    };
    int nCertificates = (int)ARRAY_SIZE(certificates);

    print_separator("Graph isomorphism verifier (34.2-1)");
    printf("G1: cycle 0 - 1 - 2 - 3 - 0\n");
    printf("G2: cycle 0 - 2 - 1 - 3 - 0\n");
    printf("G3: triangle 0 - 1 - 2 with edge 2 - 3\n\n");

    printf("f            | A(<G1, G2>, f)\n");
    for (int c = 0; c < nCertificates; ++c) {
        const int* f = certificates[c];
        int result = verify_graph_isomorphism(
            &G1[0][0],
            n,
            &G2[0][0],
            n,
            f
        );

        printf("(%d, %d, %d, %d) | %d (%s)\n",
            f[0], f[1], f[2], f[3], result, notes[c]
        );
    }

    printf("\naccepted certificates among all %d! = %d bijections:\n",
        n, (int)factorial(n)
    );
    printf("  <G1, G2>: %d\n",
        gi_count_isomorphisms(&G1[0][0], &G2[0][0], n)
    );
    printf("  <G1, G3>: %d\n",
        gi_count_isomorphisms(&G1[0][0], &G3[0][0], n)
    );

    printf("\n<G1, K3>: |V1| = %d, |V2| = 3, A = %d\n",
        n,
        verify_graph_isomorphism(
            &G1[0][0],
            n,
            &K3[0][0],
            3,
            certificates[0]
        )
    );
}

// 34.2-3
static int hc_extend(
    const int* adjMat,
    int n,
    int* path,
    int* used,
    int len
) {
    if (len == n) return adjMat[path[n - 1] * n + path[0]];

    int last = path[len - 1];
    for (int w = 0; w < n; ++w) {
        if (used[w] || !adjMat[last * n + w]) continue;

        used[w] = 1;
        path[len] = w;
        int found = hc_extend(
            adjMat,
            n,
            path,
            used,
            len + 1
        );
        used[w] = 0;

        if (found) return 1;
    }

    return 0;
}

int ham_cycle(const int* adjMat, int n) {
    if (n < 3) return 0;

    int* path = safe_malloc(n * sizeof(int));
    int* used = safe_calloc(n, sizeof(int));
    path[0] = 0;
    used[0] = 1;

    int found = hc_extend(
        adjMat,
        n,
        path,
        used,
        1
    );

    safe_free(path);
    safe_free(used);

    return found;
}

int ham_cycle_order(
    HamCycleDecider decide,
    const int* adjMat,
    int n,
    int* order,
    int* calls
) {
    *calls = 1;
    if (!decide(adjMat, n)) return 0;

    int* H = safe_malloc(n * n * sizeof(int));
    memcpy(H, adjMat, n * n * sizeof(int));

    for (int u = 0; u < n; ++u) {
        for (int v = u + 1; v < n; ++v) {
            if (!adjMat[u * n  + v]) continue;

            H[u * n + v] = H[v * n + u] = 0;
            (*calls)++;
            if (!decide(H, n)) H[u * n + v] = H[v * n + u] = 1;
        }
    }

    order[0] = 0;
    for (int i = 1; i < n; ++i) {
        int prev = i >= 2 ? order[i - 2] : NIL;
        int w = 0;
        while (!H[order[i - 1] * n + w] || w == prev) w++;
        order[i] = w;
    }

    safe_free(H);

    return 1;
}

static int hc_is_hamiltonian_cycle(
    const int* adjMat,
    int n,
    const int* order
) {
    int used[HC_MAX_VERTICES] = {0};
    for (int i = 0; i < n; ++i) {
        if (used[order[i]]) return 0;
        used[order[i]] = 1;

        if (!adjMat[order[i] * n + order[(i + 1) % n]]) return 0;
    }

    return 1;
}

static void hc_print_run(
    const char* name,
    int edges[][2],
    int m,
    int n
) {
    int adjMat[HC_MAX_VERTICES * HC_MAX_VERTICES] = {0};
    for (int e = 0; e < m; ++e) {
        int u = edges[e][0];
        int v = edges[e][1];
        adjMat[u * n + v] = adjMat[v * n + u] = 1;
    }

    int order[HC_MAX_VERTICES];
    int calls;
    int found = ham_cycle_order(
        ham_cycle,
        adjMat,
        n,
        order,
        &calls
    );

    printf("%s (n = %d, |E| = %d)\n", name, n, m);
    if (!found) {
        printf("  no hamiltonian cycle, decider calls = %d\n\n", calls);
        return;
    }

    printf("  cycle: ");
    for (int i = 0; i < n; ++i) printf("%d - ", order[i]);
    printf("%d\n", order[0]);
    printf("  decider calls = %d (|E| + 1 = %d), %s\n\n",
        calls,
        m + 1,
        hc_is_hamiltonian_cycle(adjMat, n, order) ? "valid" : "INVALID"
    );
}

void test_ham_cycle_order(void) {
    int prism[][2] = {
        {0, 1}, {1, 2}, {0, 2},
        {3, 4}, {4, 5}, {3, 5},
        {0, 3}, {1, 4}, {2, 5}
    };
    int k5[][2] = {
        {0, 1}, {0, 2}, {0, 3}, {0, 4},
        {1, 2}, {1, 3}, {1, 4},
        {2, 3}, {2, 4},
        {3, 4}
    };
    int k23[][2] = {
        {0, 2}, {0, 3}, {0, 4},
        {1, 2}, {1, 3}, {1, 4}
    };
    int petersen[][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 0},
        {0, 5}, {1, 6}, {2, 7}, {3, 8}, {4, 9},
        {5, 7}, {7, 9}, {9, 6}, {6, 8}, {8, 5}
    };

    print_separator("Hamiltonian cycle from a HAM-CYCLE decider (34.2-3)");
    hc_print_run("triangular prism", prism, (int)ARRAY_SIZE(prism), 6);
    hc_print_run("K5", k5, (int)ARRAY_SIZE(k5), 5);
    hc_print_run("K_{2,3}", k23, (int)ARRAY_SIZE(k23), 5);
    hc_print_run("Petersen graph", petersen, (int)ARRAY_SIZE(petersen), 10);
}

// 34.2-5
static int ds_next_word(
    char* y,
    int len
) {
    int i = len - 1;
    while (i >= 0 && y[i] == '1') y[i--] = '0';
    if (i < 0) return 0;

    y[i] = '1';

    return 1;
}

// try every certificate
int decide_by_search(
    Verifier verify,
    CertificateBound p,
    const char* x,
    char* certificate,
    long long* checked
) {
    int bound = p((int)strlen(x));
    char* y = safe_malloc(bound + 1);
    *checked = 0;

    int found = 0;
    for (int len = 0; len <= bound && !found; ++len) {
        memset(y, '0', len);
        y[len] = '\0';

        do {
            (*checked)++;
            found = verify(x, y);
        } while (!found && ds_next_word(y, len));
    }

    if (found) strcpy(certificate, y);
    safe_free(y);

    return found;
}

static long long get_ds_value(const char* s) {
    long long v = 0;
    for (int i = 0; s[i] != '\0'; ++i) v = 2 * v + (s[i] - '0');

    return v;
}

static int ds_verify_composite(
    const char* x,
    const char* y
) {
    long long N = get_ds_value(x);
    long long d = get_ds_value(y);

    return 1 < d && d < N && N % d == 0;
}

static int ds_composite_bound(int n) {
    return n;
}

static int ds_matrix_side(int len) {
    int n = 0;
    while (n * n < len) n++;

    return n * n == len ? n : NIL;
}

static int ds_verify_ham_cycle(
    const char* x,
    const char* y
) {
    int n = ds_matrix_side((int)strlen(x));
    if (n < 3) return 0;

    int b = get_num_bits(n - 1);
    if ((int)strlen(y) != n * b) return 0;

    int order[n];
    int used[n];
    memset(used, 0, sizeof(used));

    for (int i = 0; i < n; ++i) {
        int v = 0;
        for (int t = 0; t < b; ++t) 
            v = 2 * v + (y[i * b + t] - '0');

        if (v >= n || used[v]) return 0;
        used[v] = 1;
        order[i] = v;
    }

    for (int i = 0; i < n; ++i)
        if (x[order[i] * n + order[(i + 1) % n]] != '1') return 0;

    return 1;
}

static int ds_ham_cycle_bound(int len) {
    int n = ds_matrix_side(len);

    return n < 3 ? 0 : n * get_num_bits(n - 1);
}

static void ds_print_run(
    const char* name,
    Verifier verify,
    CertificateBound p,
    const char* x,
    int groupBits
) {
    char certificate[DS_MAX_CERTIFICATE + 1];
    long long checked;
    int len = (int)strlen(x);
    int bound = p(len);
    int found = decide_by_search(
        verify,
        p,
        x,
        certificate,
        &checked
    );

    printf("%-9s | %3d | %6d | %4d | %10lld | %16lld | ",
        name, len, bound, found, checked, (1LL << (bound + 1)) - 1
    );
    if (!found) {
        printf("-\n");
        return;
    }

    for (int i = 0; certificate[i] != '\0'; ++i) {
        if (groupBits > 0 && i > 0 && i % groupBits == 0) putchar(' ');
        putchar(certificate[i]);
    }
    printf("\n");
}

void test_decide_by_search(void) {
    print_separator("Deciding NP by trying certificates (34.2-5)");

    printf("COMPOSITE: x = number in binary, y = divisor, p(n) = n\n");
    printf("x         | |x| | p(|x|) | in L | candidates | 2^(p(|x|)+1) - 1 | y\n");
    ds_print_run("15", ds_verify_composite, ds_composite_bound, "1111", 0);
    ds_print_run("13", ds_verify_composite, ds_composite_bound, "1101", 0);
    ds_print_run("35", ds_verify_composite, ds_composite_bound, "100011", 0);
    ds_print_run("101", ds_verify_composite, ds_composite_bound, "1100101", 0);

    const char* c4 = "0101101001011010";              // cycle 0 - 1 - 2 - 3 - 0
    const char* star = "0111100010001000";            // edges 0 - 1, 0 - 2, 0 - 3
    const char* c5 = "0100110100010100010110010";     // cycle 0 - 1 - 2 - 3 - 4 - 0
    const char* k23 = "0011100111110001100011000";    // V1 = {0, 1}, V2 = {2, 3, 4}

    printf("\nHAM-CYCLE: x = e1(G), y = vertices of the cycle in binary\n");
    printf("graph     | |x| | p(|x|) | in L | candidates | 2^(p(|x|)+1) - 1 | y\n");
    ds_print_run("C4", ds_verify_ham_cycle, ds_ham_cycle_bound, c4, 2);
    ds_print_run("K1,3", ds_verify_ham_cycle, ds_ham_cycle_bound, star, 2);
    ds_print_run("C5", ds_verify_ham_cycle, ds_ham_cycle_bound, c5, 3);
    ds_print_run("K2,3", ds_verify_ham_cycle, ds_ham_cycle_bound, k23, 3);
}

// 34.2-6
static int hp_extend(
    const int* adjMat,
    int n,
    int v,
    int* path,
    int* used,
    int len
) {
    if (len == n) return path[n - 1] == v;

    int last = path[len - 1];
    for (int w = 0; w < n; ++w) {
        if (used[w] || !adjMat[last * n + w]) continue;
        // v must be the last vertex
        if (w == v && len != n - 1) continue;

        used[w] = 1;
        path[len] = w;
        
        int found = hp_extend(
            adjMat,
            n,
            v,
            path,
            used,
            len + 1
        );
        used[w] = 0;

        if (found) return 1;
    }

    return 0;
}

int ham_path(
    const int* adjMat,
    int n,
    int u,
    int v,
    int* path
) {
    if (n < 1) return 0;

    int* used = safe_calloc(n, sizeof(int));
    path[0] = u;
    used[u] = 1;

    int found = hp_extend(
        adjMat,
        n,
        v,
        path,
        used,
        1
    );

    safe_free(used);

    return found;
}

static int hp_verify(
    const int* adjMat,
    int n,
    int u,
    int v,
    const int* path
) {
    if (path[0] != u || path[n - 1] != v) return 0;

    int used[HC_MAX_VERTICES] = {0};
    for (int i = 0; i < n; ++i) {
        if (used[path[i]]) return 0;
        used[path[i]] = 1;
    }

    for (int i = 0; i < n - 1; ++i)
        if (!adjMat[path[i] * n + path[i + 1]]) return 0;

    return 1;
}

static void hp_print_run(
    const char* name,
    int edges[][2],
    int m,
    int n,
    int u,
    int v
) {
    int adjMat[HC_MAX_VERTICES * HC_MAX_VERTICES] = {0};
    for (int e = 0; e < m; ++e) {
        int a = edges[e][0];
        int b = edges[e][1];
        adjMat[a * n + b] = adjMat[b * n + a] = 1;
    }

    int path[HC_MAX_VERTICES];
    int found = ham_path(
        adjMat,
        n,
        u,
        v,
        path
    );

    printf("%-16s | %d | %d | ", name, u, v);
    if (!found) {
        printf("%-37s | -\n", "none");
        return;
    }

    char line[64] = "";
    for (int i = 0; i < n; ++i) {
        char vertex[8];
        sprintf(vertex, i == 0 ? "%d" : " - %d", path[i]);
        strcat(line, vertex);
    }
    printf("%-37s | %d\n", line, hp_verify(adjMat, n, u, v, path));
}

void test_ham_path(void) {
    int pathGraph[][2] = {
        {0, 1}, {1, 2}, {2, 3}
    };
    int prism[][2] = {
        {0, 1}, {1, 2}, {0, 2},
        {3, 4}, {4, 5}, {3, 5},
        {0, 3}, {1, 4}, {2, 5}
    };
    int k23[][2] = {
        {0, 2}, {0, 3}, {0, 4},
        {1, 2}, {1, 3}, {1, 4}
    };
    int petersen[][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 0},
        {0, 5}, {1, 6}, {2, 7}, {3, 8}, {4, 9},
        {5, 7}, {7, 9}, {9, 6}, {6, 8}, {8, 5}
    };
    int mPath = (int)ARRAY_SIZE(pathGraph);
    int mPrism = (int)ARRAY_SIZE(prism);
    int mK23 = (int)ARRAY_SIZE(k23);
    int mPetersen = (int)ARRAY_SIZE(petersen);

    print_separator("Hamiltonian path from u to v (34.2-6)");
    printf("graph            | u | v | hamiltonian path                      | verifier\n");
    hp_print_run("path 0-1-2-3", pathGraph, mPath, 4, 0, 3);
    hp_print_run("path 0-1-2-3", pathGraph, mPath, 4, 1, 2);
    hp_print_run("triangular prism", prism, mPrism, 6, 0, 3);
    hp_print_run("triangular prism", prism, mPrism, 6, 0, 5);
    hp_print_run("K_{2,3}", k23, mK23, 5, 2, 4);
    hp_print_run("K_{2,3}", k23, mK23, 5, 0, 1);
    hp_print_run("Petersen graph", petersen, mPetersen, 10, 0, 2);
    hp_print_run("Petersen graph", petersen, mPetersen, 10, 0, 1);
}

// 34.2-7
static int hpd_topo_sort(
    const int* adjMat,
    int n,
    int* order
) {
    int* inDeg = safe_calloc(n, sizeof(int));
    for (int a = 0; a < n; ++a)
        for (int b = 0; b < n; ++b) inDeg[b] += adjMat[a * n + b];

    int head = 0;
    int tail = 0;
    for (int w = 0; w < n; ++w)
        if (inDeg[w] == 0) order[tail++] = w;

    while (head < tail) {
        int a = order[head++];
        for (int b = 0; b < n; ++b) {
            if (!adjMat[a * n + b]) continue;
            if (--inDeg[b] == 0) order[tail++] = b;
        } 
    }

    safe_free(inDeg);

    return tail == n;
}

int ham_path_dag(
    const int* adjMat,
    int n,
    int u,
    int v,
    int* path
) {
    if (n < 1) return 0;
    if (!hpd_topo_sort(adjMat, n, path)) return NIL;
    if (path[0] != u || path[n - 1] != v) return 0;

    for (int i = 0; i < n - 1; ++i)
        if (!adjMat[path[i] * n + path[i + 1]]) return 0;

    return 1;
}

static void hpd_print_run(
    const char* name,
    int edges[][2],
    int m,
    int n,
    int u,
    int v
) {
    int adjMat[HC_MAX_VERTICES * HC_MAX_VERTICES] = {0};
    for (int e = 0; e < m; ++e) adjMat[edges[e][0] * n + edges[e][1]] = 1;
    
    int path[HC_MAX_VERTICES];
    int backtrackingPath[HC_MAX_VERTICES];
    int found = ham_path_dag(
        adjMat,
        n,
        u,
        v,
        path
    );
    int backtracking = ham_path(
        adjMat,
        n,
        u,
        v,
        backtrackingPath
    );

    printf("%-18s | %d | %d | %5d | %12d | ", name, u, v, found, backtracking);
    if (found != 1) {
        printf("       - | -\n");
        return;
    }

    printf("%8d | ", hp_verify(adjMat, n, u, v, path));
    for (int i = 0; i < n; ++i) printf(i == 0 ? "%d" : " - %d", path[i]);
    printf("\n");
}

void test_ham_path_dag(void) {
    int shuffled[][2] = {
        {3, 0}, {0, 4}, {4, 1}, {1, 2},
        {3, 4}, {0, 1}, {3, 2}
    };
    int mShuffled = (int)ARRAY_SIZE(shuffled);

    int rombus[][2] = {
        {0, 1}, {0, 2}, {1, 3}, {2, 3}
    };
    int mRombus = (int)ARRAY_SIZE(rombus);

    int rombusChord[][2] = {
        {0, 1}, {0, 2}, {1, 3}, {2, 3}, {1, 2}
    };
    int mRombusChord = (int)ARRAY_SIZE(rombusChord);

    int cycle[][2] = {
        {0, 1}, {1, 2}, {2, 0}
    };
    int mCycle = (int)ARRAY_SIZE(cycle);

    print_separator("Hamiltonian path in a DAG (34.2-7)");
    printf("graph              | u | v | found | backtracking | verifier | path\n");
    hpd_print_run("shuffled path", shuffled, mShuffled, 5, 3, 2);
    hpd_print_run("shuffled path", shuffled, mShuffled, 5, 0, 2);
    hpd_print_run("rombus", rombus, mRombus, 4, 0, 3);
    hpd_print_run("rombus with 1->2", rombusChord, mRombusChord, 4, 0, 3);
    hpd_print_run("cycle 0->1->2->0", cycle, mCycle, 3, 0, 2);
}

// 34.2-8
typedef struct {
    const char* bits;
    const char* s;
    int* varLen;
    int* varStart;
    int k;
    int pos;
} TfParser;

static int tf_parse_or(TfParser* p);

static void tf_init(
    TfParser* p,
    const char* x
) {
    int len = (int)strlen(x);

    p->bits = NULL;
    p->s = x;
    p->varLen = safe_calloc(len + 1, sizeof(int));
    p->varStart = safe_calloc(len + 1, sizeof(int));
    p->k = 0;
    p->pos = 0;
}

static void tf_free(TfParser* p) {
    safe_free(p->varLen);
    safe_free(p->varStart);
}

static int tf_find_variable(
    const TfParser* p,
    int start,
    int len
) {
    for (int i = 0; i < p->k; ++i) {
        if (p->varLen[i] != len) continue;
        if (strncmp(p->s + p->varStart[i], p->s + start, len) == 0) return i;
    }

    return NIL;
}

static int tf_parse_variable(TfParser* p) {
    if (p->s[p->pos] != 'x') return NIL;

    int start = p->pos + 1;
    int end = start;
    while (isdigit((unsigned char)p->s[end])) end++;

    int len = end - start;
    if (len == 0 || p->s[start] == '0') return NIL;
    p->pos = end;

    int j = tf_find_variable(p, start, len);
    if (p->bits != NULL) return p->bits[j] - '0';

    if (j == NIL) {
        p->varStart[p->k] = start;
        p->varLen[p->k] = len;
        p->k++;
    }

    return 0;
}

static int tf_parse_not(TfParser* p) {
    if (p->s[p->pos] == '~') {
        p->pos++;
        int value = tf_parse_not(p);

        return value == NIL ? NIL : !value;
    }

    if (p->s[p->pos] != '(') return tf_parse_variable(p);

    p->pos++;
    int value = tf_parse_or(p);
    if (value == NIL || p->s[p->pos] != ')') return NIL;
    p->pos++;

    return value;
}

static int tf_parse_and(TfParser* p) {
    int value = tf_parse_not(p);

    while (value != NIL && p->s[p->pos] == '&') {
        p->pos++;
        int right = tf_parse_not(p);
        value = right == NIL ? NIL : (value && right);
    }

    return value;
}

static int tf_parse_or(TfParser* p) {
    int value = tf_parse_and(p);

    while (value != NIL && p->s[p->pos] == '|') {
        p->pos++;
        int right = tf_parse_and(p);
        value = right == NIL ? NIL : (value || right);
    }

    return value;
}

static int tf_parse(
    TfParser* p,
    const char* bits
) {
    p->pos = 0;
    p->bits = bits;

    int value = tf_parse_or(p);

    return p->s[p->pos] == '\0' ? value : NIL;
}

static int tf_is_bit_string(
    const char* y,
    int k
) {
    if ((int)strlen(y) != k) return 0;

    for (int j = 0; j < k; ++j)
        if (y[j] != '0' && y[j] != '1') return 0;

    return 1;
}

int verify_not_tautology(
    const char* x,
    const char* y
) {
    TfParser parser;
    tf_init(&parser, x);

    int result;
    if (tf_parse(&parser, NULL) == NIL) result = 1;
    else if (!tf_is_bit_string(y, parser.k)) result = 0;
    else result = tf_parse(&parser, y) == 0;

    tf_free(&parser);

    return result;
}

static int tf_count_variables(const char* x) {
    TfParser parser;
    tf_init(&parser, x);

    int k = tf_parse(&parser, NULL) == NIL ? NIL : parser.k;
    tf_free(&parser);

    return k;
}

static void tf_print_search(const char* x) {
    int k = tf_count_variables(x);

    char y[k + 1];
    memset(y, '0', k);
    y[k] = '\0';

    long long checked = 0;
    int found = 0;
    do {
        checked++;
        found = verify_not_tautology(x, y);
    } while (!found && ds_next_word(y, k));

    printf("%-28s | %d | %3lld | %7lld | %9d | %s\n",
        x, k, 1LL << k, checked, !found, found ? y : "-"
    );
}

static void tf_print_verifier(
    const char* x,
    const char* y,
    const char* comment
) {
    printf("%-16s | %-4s | %6d | %s\n", x, y, verify_not_tautology(x, y), comment);
}

void test_verify_not_tautology(void) {
    const char* formulas[] = {
        "x1|~x1",
        "x1&~x1",
        "x1|x2",
        "(x1&x2)|~x1|~x2",
        "~(x1&x2)|x1|x2",
        "~((~x1|x2)&(~x2|x3))|~x1|x3",
        "~((~x1|x2)&(~x2|x3))|~x3|x1"
    };
    int nFormulas = (int)ARRAY_SIZE(formulas);

    print_separator("TAUTOLOGY in co-NP (34.2-8)");

    printf("Trying every assignment as a certificate\n");
    printf("formula                      | k | 2^k | checked | tautology | y\n");
    for (int i = 0; i < nFormulas; ++i) tf_print_search(formulas[i]);

    printf("\nSingle calls of the verifier\n");
    printf("x                | y    | A(x,y) | comment\n");
    tf_print_verifier("x1&x2", "10", "assignment gives 0");
    tf_print_verifier("x1&x2", "11", "assignment gives 1");
    tf_print_verifier("x1&x2", "1", "wrong length");
    tf_print_verifier("x1&x2", "1a", "not a bit string");
    tf_print_verifier("x1&x1", "1", "repeated variable counts once");
    tf_print_verifier("x5&x100", "10", "numbers do not have to be consecutive");
    tf_print_verifier("x1|x2&x3", "100", "& binds tighter than |");
    tf_print_verifier("x1&", "", "not a formula");
    tf_print_verifier("x01", "", "not a formula");
    tf_print_verifier("", "", "not a formula");
}