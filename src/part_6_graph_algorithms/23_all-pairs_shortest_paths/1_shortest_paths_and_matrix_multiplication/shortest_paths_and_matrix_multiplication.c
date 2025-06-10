#include "part_6_graph_algorithms/23_all-pairs_shortest_paths/all-pairs_shortest_paths.h"

#pragma region Basic algorithms

void extend_shortest_paths(
    int A[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int B[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int C[MAX_MAT_SIZE][MAX_MAT_SIZE]
) {
    for (int i = 0; i < MAX_MAT_SIZE; i++) {
        for (int j = 0; j < MAX_MAT_SIZE; j++) {
            C[i][j] = INF;
            for (int k = 0; k < MAX_MAT_SIZE; k++) {
                if (A[i][k] != INF && B[k][j] != INF) {
                    int cand = A[i][k] + B[k][j];
                    if (cand < C[i][j]) C[i][j] = cand;
                }
            }
        }
    }
}

void slow_apsp(
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int L[MAX_MAT_SIZE][MAX_MAT_SIZE]
) {
    /*
        O(V^4)
    */
    int L_prev[MAX_MAT_SIZE][MAX_MAT_SIZE], L_curr[MAX_MAT_SIZE][MAX_MAT_SIZE];
    for (int i = 0; i < MAX_MAT_SIZE; i++)
        for (int j = 0; j < MAX_MAT_SIZE; j++)
            L_prev[i][j] = W[i][j];

    print_named_mat(L_prev, "Slow APSP: L^{1}");

    for (int m = 2; m <= MAX_MAT_SIZE - 1; m++) {
        extend_shortest_paths(L_prev, W, L_curr);
        char buff[BUFFER_SIZE];
        snprintf(buff, sizeof(buff), "Slow APSP: L^{%d}", m);
        print_named_mat(L_curr, buff);
        for (int i = 0; i < MAX_MAT_SIZE; i++)
            for (int j = 0; j < MAX_MAT_SIZE; j++)
                L_prev[i][j] = L_curr[i][j];
    }

    for (int i = 0; i < MAX_MAT_SIZE; i++) 
        for (int j = 0; j < MAX_MAT_SIZE; j++)
            L[i][j] = L_prev[i][j];
}

void faster_apsp(
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int L[MAX_MAT_SIZE][MAX_MAT_SIZE]
) {
    /*
        O(V^3*lg(V))
    */
    int S[MAX_MAT_SIZE][MAX_MAT_SIZE], T[MAX_MAT_SIZE][MAX_MAT_SIZE];
    // S = W
    for (int i = 0; i < MAX_MAT_SIZE; i++)
        for (int j = 0; j < MAX_MAT_SIZE; j++)
            S[i][j] = W[i][j];
    
    print_named_mat(S, "Faster APSP: S^{1}");

    int r = 1;
    while (r < MAX_MAT_SIZE - 1) {
        extend_shortest_paths(S, S, T);
        char buff[BUFFER_SIZE];
        snprintf(buff, sizeof(buff), "Faster APSP: L^{%d}", r);
        print_named_mat(T, buff);
        for (int i = 0; i < MAX_MAT_SIZE; i++)
            for (int j = 0; j < MAX_MAT_SIZE; j++)
                S[i][j] = T[i][j];

        r *= 2;
    }

    for (int i = 0; i < MAX_MAT_SIZE; i++)
        for (int j = 0; j < MAX_MAT_SIZE; j++)
            L[i][j] = S[i][j];
}

#pragma endregion Basic algorithms

#pragma region 23.1-5

void pseudo_bellman_ford(
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int src, int dist[MAX_MAT_SIZE]
) {
    /*
        Bellman-Ford-like algorithm with 
        min-plus matrix-vector products.
    */
    int v[MAX_MAT_SIZE], v_next[MAX_MAT_SIZE];
    for (int i = 0; i < MAX_MAT_SIZE; i++) v[i] = (i == src) ? 0 : INF;

    print_named_vec(v, "Pseudo Bellman-Ford v^{0}");

    for (int step = 1; step < MAX_MAT_SIZE; step++) {
        for (int i = 0; i < MAX_MAT_SIZE; i++) {
            v_next[i] = v[i];
            for (int j = 0; j < MAX_MAT_SIZE; j++) {
                if (v[j] < INF && W[j][i] < INF) {
                    int cand = v[j] + W[j][i];
                    if (cand < v_next[i]) v_next[i] = cand;
                }
            }
        }
        char buff[BUFFER_SIZE];
        snprintf(buff, sizeof(buff), "Pseudo Bellman-Ford v^{%d}", step);
        print_named_vec(v_next, buff);
        for (int i = 0; i < MAX_MAT_SIZE; i++) v[i] = v_next[i];
    }
    for (int i = 0; i < MAX_MAT_SIZE; i++) dist[i] = v[i];
}

#pragma endregion 23.1-5

#pragma region 23.1-6

void space_optimized_slow_apsp(
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int L[MAX_MAT_SIZE][MAX_MAT_SIZE]
) {
    /*
        Overwrite L instead of copying 
        it to other matrix.
    */
    for (int i = 0; i < MAX_MAT_SIZE; i++)
        for (int j = 0; j < MAX_MAT_SIZE; j++)
            L[i][j] = W[i][j];

    print_named_mat(L, "Slow APSP: L^{1}");

    for (int m = 2; m <= MAX_MAT_SIZE - 1; m++) {
        for (int i = 0; i < MAX_MAT_SIZE; i++) {
            for (int j = 0; j < MAX_MAT_SIZE; j++) {
                int minVal = L[i][j];
                for (int k = 0; k < MAX_MAT_SIZE; k++) {
                    if (L[i][k] != INF && W[k][j] != INF) {
                        int cand = L[i][k] + W[k][j];
                        if (cand < minVal) minVal = cand;
                    }
                }
                L[i][j] = minVal;
            }  
        }
        char buff[BUFFER_SIZE];
        snprintf(buff, sizeof(buff), "Slow APSP: L^{%d}", m);
        print_named_mat(L, buff);
    }
}

void space_optimized_faster_apsp(
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int L[MAX_MAT_SIZE][MAX_MAT_SIZE]
) {
    /*
        Overwrite L instead of copying 
        it to other matrix.
    */
    for (int i = 0; i < MAX_MAT_SIZE; i++)
        for (int j = 0; j < MAX_MAT_SIZE; j++)
            L[i][j] = W[i][j];
    
    print_named_mat(L, "Faster APSP: S^{1}");

    int r = 1;
    int changed = 1;
    while (r < MAX_MAT_SIZE - 1 && changed) {
        changed = 0;
        for (int i = 0; i < MAX_MAT_SIZE; i++) {
            for (int j = 0; j < MAX_MAT_SIZE; j++) {
                int minVal = L[i][j];
                for (int k = 0; k < MAX_MAT_SIZE; k++) {
                    if (L[i][k] == INF || L[k][j] == INF) continue; 
                    int cand = L[i][k] + L[k][j];
                    if (cand < minVal) minVal = cand;
                }
                if (minVal != L[i][j]) changed = 1;
                L[i][j] = minVal;
            }
        }
        char buff[BUFFER_SIZE];
        snprintf(buff, sizeof(buff), "Faster APSP: S^{%d}", r);
        print_named_mat(L, buff);
        r *= 2;
    }
}

#pragma endregion 23.1-6

#pragma region 23.1-7

void compute_pred_mat(
    int L[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int pred[MAX_MAT_SIZE][MAX_MAT_SIZE]
) {
    for (int i = 0; i < MAX_MAT_SIZE; i++) {
        for (int j = 0; j < MAX_MAT_SIZE; j++) {
            if (i == j || L[i][j] == INF) {
                pred[i][j] = -1;
                continue;
            }
            pred[i][j] = -1;
            for (int k = 0; k < MAX_MAT_SIZE; k++) {
                if (L[i][k] != INF && W[k][j] != INF && L[i][k] + W[k][j] == L[i][j]) {
                    pred[i][j] = k;
                    break;
                }
            }
        }
    }
}

#pragma endregion 23.1-7

#pragma region 23.1-8

void print_pred_mat(int pred[MAX_MAT_SIZE][MAX_MAT_SIZE], const char* name) {
    printf("%s (predecessors):\n", name);
    for (int i = 0; i < MAX_MAT_SIZE; i++) {
        for (int j = 0; j < MAX_MAT_SIZE; j++) {
            if (pred[i][j] == -1) printf("%5s", "NIL");
            else printf("%5d", pred[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void extend_shortest_path_mod(
    int prevPred[MAX_MAT_SIZE][MAX_MAT_SIZE],
    int L[MAX_MAT_SIZE][MAX_MAT_SIZE],
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE],
    int newPred[MAX_MAT_SIZE][MAX_MAT_SIZE],
    int newL[MAX_MAT_SIZE][MAX_MAT_SIZE]
) {
    for (int i = 0; i < MAX_MAT_SIZE; i++) {
        for (int j = 0; j < MAX_MAT_SIZE; j++) {
            newL[i][j] = INF;
            newPred[i][j] = -1;
            for (int k = 0; k < MAX_MAT_SIZE; k++) {
                if (L[i][k] != INF && W[k][j] != INF) {
                    int cand = L[i][k] + W[k][j];
                    if (cand >= newL[i][j]) continue;
                    newL[i][j] = cand;
                    if (k != j) newPred[i][j] = k;
                    else newPred[i][j] = prevPred[i][j];
                }
            }
        }
    }
}

void space_optimized_slow_apsp_mod(
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int L[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int pred[MAX_MAT_SIZE][MAX_MAT_SIZE]
) {
    int prevL[MAX_MAT_SIZE][MAX_MAT_SIZE];
    int prevPred[MAX_MAT_SIZE][MAX_MAT_SIZE];
    int currL[MAX_MAT_SIZE][MAX_MAT_SIZE];
    int currPred[MAX_MAT_SIZE][MAX_MAT_SIZE];

    for (int i = 0; i < MAX_MAT_SIZE; i++) {
        for (int j = 0; j < MAX_MAT_SIZE; j++) {
            prevL[i][j] = W[i][j];
            if (i != j && W[i][j] != INF) prevPred[i][j] = i;
            else prevPred[i][j] = -1;
        }
    }

    print_named_mat(prevL, "Slow APSP MOD: L^{1}");
    print_pred_mat(prevPred, "Slow APSP MOD: Pi^{1}");

    for (int m = 2; m <= MAX_MAT_SIZE - 1; m++) {
        extend_shortest_path_mod(prevPred, prevL, W, currPred, currL);

        char buff[BUFFER_SIZE];
        snprintf(buff, sizeof(buff), "Slow APSP MOD: L^{%d}", m);
        print_named_mat(currL, buff);
        snprintf(buff, sizeof(buff), "Slow APSP MOD: Pi^{%d}", m);
        print_pred_mat(currPred, buff);

        for (int i = 0; i < MAX_MAT_SIZE; i++) {
            for (int j = 0; j < MAX_MAT_SIZE; j++) {
                prevL[i][j] = currL[i][j];
                prevPred[i][j] = currPred[i][j];
            }
        }
    }

    for (int i = 0; i < MAX_MAT_SIZE; i++) {
        for (int j = 0; j < MAX_MAT_SIZE; j++) {
            L[i][j] = prevL[i][j];
            pred[i][j] = prevPred[i][j];
        }
    }
}

#pragma endregion 23.1-8

#pragma region 23.1-9

int faster_apsp_neg_cycle(
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int L[MAX_MAT_SIZE][MAX_MAT_SIZE]
) {
    for (int i = 0; i < MAX_MAT_SIZE; i++)
        for (int j = 0; j < MAX_MAT_SIZE; j++)
            L[i][j] = W[i][j];
    
    print_named_mat(L, "Faster APSP: S^{1}");

    int r = 1;
    int changed = 1;
    while (r < MAX_MAT_SIZE - 1 && changed) {
        changed = 0;
        for (int i = 0; i < MAX_MAT_SIZE; i++) {
            for (int j = 0; j < MAX_MAT_SIZE; j++) {
                int minVal = L[i][j];
                for (int k = 0; k < MAX_MAT_SIZE; k++) {
                    if (L[i][k] != INF && L[k][j] != INF) {
                        int cand = L[i][k] + L[k][j];
                        if (cand < minVal) minVal = cand;
                    }
                }
                if (minVal != L[i][j]) changed = 1;
                L[i][j] = minVal;
            }
        }
        char buff[BUFFER_SIZE];
        snprintf(buff, sizeof(buff), "Faster APSP: S^{%d}", r);
        print_named_mat(L, buff);
        r *= 2;
    }

    int temp[MAX_MAT_SIZE][MAX_MAT_SIZE];
    for (int i = 0; i < MAX_MAT_SIZE; i++) {
        for (int j = 0; j < MAX_MAT_SIZE; j++) {
            int minVal = L[i][j];
            for (int k = 0; k < MAX_MAT_SIZE; k++) {
                if (L[i][k] == INF || L[k][j] == INF) continue;
                int cand = L[i][k] + L[k][j];
                if (cand < minVal) minVal = cand;
            }
            temp[i][j] = minVal;
        }
    }

    int hasNegCycle = 0;
    for (int i = 0; i < MAX_MAT_SIZE; i++)
        for (int j = 0; j < MAX_MAT_SIZE; j++)
            if (temp[i][j] != L[i][j]) hasNegCycle = 1;

    print_named_mat(L, "Faster APSP result");
    if (hasNegCycle) printf("Negative-weight cycle detected!\n");
    else printf("No negative-weight cycle detected.\n");

    return hasNegCycle;
}

#pragma endregion 23.1-9

#pragma region 23.1-10

int min_length_neg_cycle(int W[MAX_MAT_SIZE][MAX_MAT_SIZE]) {
    int L[MAX_MAT_SIZE][MAX_MAT_SIZE];

    for (int i = 0; i < MAX_MAT_SIZE; i++)
        for (int j = 0; j < MAX_MAT_SIZE; j++) L[i][j] = W[i][j];

    for (int i = 0; i < MAX_MAT_SIZE; i++) if (L[i][i] < 0) return 1;

    for (int m = 2; m <= MAX_MAT_SIZE; m++) {
        for (int i = 0; i < MAX_MAT_SIZE; i++) {
            for (int j = 0; j < MAX_MAT_SIZE;j ++) {
                int minVal = L[i][j];
                for (int k = 0; k < MAX_MAT_SIZE; k++) {
                    if (L[i][k] == INF || W[k][j] == INF) continue;
                    int cand = L[i][k] + W[k][j];
                    if (cand < minVal) minVal = cand;
                }
                L[i][j] = minVal;
            }
        }
        for (int i = 0; i < MAX_MAT_SIZE; i++) if (L[i][i] < 0) return m;
    }
    return 0;
}

#pragma endregion 23.1-10
