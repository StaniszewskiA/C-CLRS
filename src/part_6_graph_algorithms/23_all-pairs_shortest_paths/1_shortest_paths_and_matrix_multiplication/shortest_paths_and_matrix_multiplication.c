#include <stdio.h>
#include <limits.h>

#define TASK 9
#define N 6
#define INF INT_MAX
#define BUFFER_SIZE 64

#pragma region Matrix utils

void print_mat(int mat[N][N], const char* name) {
    printf("%s:\n", name);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (mat[i][j] >= INF / 2) printf("%5s", "INF");
            else printf("%5d", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

#pragma endregion Matrix utils

#pragma region Basic algorithms

void extend_shortest_paths(int A[N][N], int B[N][N], int C[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = INF;
            for (int k = 0; k < N; k++) {
                if (A[i][k] != INF && B[k][j] != INF) {
                    int cand = A[i][k] + B[k][j];
                    if (cand < C[i][j]) C[i][j] = cand;
                }
            }
        }
    }
}

void slow_apsp(int W[N][N], int L[N][N]) {
    /*
        O(V^4)
    */
    int L_prev[N][N], L_curr[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            L_prev[i][j] = W[i][j];

    print_mat(L_prev, "Slow APSP: L^{1}");

    for (int m = 2; m <= N - 1; m++) {
        extend_shortest_paths(L_prev, W, L_curr);
        char buff[BUFFER_SIZE];
        snprintf(buff, sizeof(buff), "Slow APSP: L^{%d}", m);
        print_mat(L_curr, buff);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                L_prev[i][j] = L_curr[i][j];
    }

    for (int i = 0; i < N; i++) 
        for (int j = 0; j < N; j++)
            L[i][j] = L_prev[i][j];
}

void faster_apsp(int W[N][N], int L[N][N]) {
    /*
        O(V^3*lg(V))
    */
    int S[N][N], T[N][N];
    // S = W
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            S[i][j] = W[i][j];
    
    print_mat(S, "Faster APSP: S^{1}");

    int r = 1;
    while (r < N - 1) {
        extend_shortest_paths(S, S, T);
        char buff[BUFFER_SIZE];
        snprintf(buff, sizeof(buff), "Faster APSP: L^{%d}", r);
        print_mat(T, buff);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                S[i][j] = T[i][j];

        r *= 2;
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            L[i][j] = S[i][j];
}

#pragma endregion Basic algorithms

#pragma region 23.1-5

void print_vec(int v[N], const char* name) {
    printf("%s: ", name);
    for (int i = 0; i < N; i++) {
        if (v[i] >= INF / 2) printf("%5s", "INF");
        else printf("%5d", v[i]);
    }
    printf("\n");
}

void pseudo_bellman_ford(int W[N][N], int src, int dist[N]) {
    /*
        Bellman-Ford-like algorithm with 
        min-plus matrix-vector products.
    */
    int v[N], v_next[N];
    for (int i = 0; i < N; i++) v[i] = (i == src) ? 0 : INF;

    print_vec(v, "Pseudo Bellman-Ford v^{0}");

    for (int step = 1; step < N; step++) {
        for (int i = 0; i < N; i++) {
            v_next[i] = v[i];
            for (int j = 0; j < N; j++) {
                if (v[j] < INF && W[j][i] < INF) {
                    int cand = v[j] + W[j][i];
                    if (cand < v_next[i]) v_next[i] = cand;
                }
            }
        }
        char buff[BUFFER_SIZE];
        snprintf(buff, sizeof(buff), "Pseudo Bellman-Ford v^{%d}", step);
        print_vec(v_next, buff);
        for (int i = 0; i < N; i++) v[i] = v_next[i];
    }
    for (int i = 0; i < N; i++) dist[i] = v[i];
}

#pragma endregion 23.1-5

#pragma region 23.1-6

void space_optimized_slow_apsp(int W[N][N], int L[N][N]) {
    /*
        Overwrite L instead of copying 
        it to other matrix.
    */
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            L[i][j] = W[i][j];

    print_mat(L, "Slow APSP: L^{1}");

    for (int m = 2; m <= N - 1; m++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int minVal = L[i][j];
                for (int k = 0; k < N; k++) {
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
        print_mat(L, buff);
    }
}

void space_optimized_faster_apsp(int W[N][N], int L[N][N]) {
    /*
        Overwrite L instead of copying 
        it to other matrix.
    */
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            L[i][j] = W[i][j];
    
    print_mat(L, "Faster APSP: S^{1}");

    int r = 1;
    int changed = 1;
    while (r < N - 1 && changed) {
        changed = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int minVal = L[i][j];
                for (int k = 0; k < N; k++) {
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
        print_mat(L, buff);
        r *= 2;
    }
}

#pragma endregion 23.1-6

#pragma region 23.1-7

void compute_pred_mat(int L[N][N], int W[N][N], int pred[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j || L[i][j] == INF) {
                pred[i][j] = -1;
                continue;
            }
            pred[i][j] = -1;
            for (int k = 0; k < N; k++) {
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

void print_pred_mat(int pred[N][N], const char* name) {
    printf("%s (predecessors):\n", name);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (pred[i][j] == -1) printf("%5s", "NIL");
            else printf("%5d", pred[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void extend_shortest_path_mod(
    int prevPred[N][N],
    int L[N][N],
    int W[N][N],
    int newPred[N][N],
    int newL[N][N]
) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            newL[i][j] = INF;
            newPred[i][j] = -1;
            for (int k = 0; k < N; k++) {
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

void space_optimized_slow_apsp_mod(int W[N][N], int L[N][N], int pred[N][N]) {
    int prevL[N][N], prevPred[N][N];
    int currL[N][N], currPred[N][N];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            prevL[i][j] = W[i][j];
            if (i != j && W[i][j] != INF) prevPred[i][j] = i;
            else prevPred[i][j] = -1;
        }
    }

    print_mat(prevL, "Slow APSP MOD: L^{1}");
    print_pred_mat(prevPred, "Slow APSP MOD: Pi^{1}");

    for (int m = 2; m <= N - 1; m++) {
        extend_shortest_path_mod(prevPred, prevL, W, currPred, currL);

        char buff[BUFFER_SIZE];
        snprintf(buff, sizeof(buff), "Slow APSP MOD: L^{%d}", m);
        print_mat(currL, buff);
        snprintf(buff, sizeof(buff), "Slow APSP MOD: Pi^{%d}", m);
        print_pred_mat(currPred, buff);

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                prevL[i][j] = currL[i][j];
                prevPred[i][j] = currPred[i][j];
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            L[i][j] = prevL[i][j];
            pred[i][j] = prevPred[i][j];
        }
    }
}

#pragma endregion 23.1-8

#pragma region 23.1-9

int faster_apsp_neg_cycle(int W[N][N], int L[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            L[i][j] = W[i][j];
    
    print_mat(L, "Faster APSP: S^{1}");

    int r = 1;
    int changed = 1;
    while (r < N - 1 && changed) {
        changed = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int minVal = L[i][j];
                for (int k = 0; k < N; k++) {
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
        print_mat(L, buff);
        r *= 2;
    }

    int temp[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int minVal = L[i][j];
            for (int k = 0; k < N; k++) {
                if (L[i][k] == INF || L[k][j] == INF) continue;
                int cand = L[i][k] + L[k][j];
                if (cand < minVal) minVal = cand;
            }
            temp[i][j] = minVal;
        }
    }

    int hasNegCycle = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (temp[i][j] != L[i][j]) hasNegCycle = 1;

    print_mat(L, "Faster APSP result");
    if (hasNegCycle) printf("Negative-weight cycle detected!\n");
    else printf("No negative-weight cycle detected.\n");

    return hasNegCycle;
}

#pragma endregion 23.1-9

#pragma region 23.1-10

int min_length_neg_cycle(int W[N][N]) {
    int L[N][N];

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) L[i][j] = W[i][j];

    for (int i = 0; i < N; i++) if (L[i][i] < 0) return 1;

    for (int m = 2; m <= N; m++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N;j ++) {
                int minVal = L[i][j];
                for (int k = 0; k < N; k++) {
                    if (L[i][k] == INF || W[k][j] == INF) continue;
                    int cand = L[i][k] + W[k][j];
                    if (cand < minVal) minVal = cand;
                }
                L[i][j] = minVal;
            }
        }
        for (int i = 0; i < N; i++) if (L[i][i] < 0) return m;
    }
    return 0;
}

#pragma endregion 23.1-10

int main(void) {
    int W[N][N] = {
        {0, INF, INF, INF, -1, INF},
        {1, 0, INF, 2, INF, INF},
        {INF, 2, 0, INF, INF, -8},
        {-4, INF, INF, 0, 3, INF},
        {INF, 7, INF, INF, 0, INF},
        {INF, 5, 10, INF, INF, 0}
    };
    int L1[N][N], L2[N][N];

    switch (TASK)
    {
        case 1: {
            // Slow-APSP
            slow_apsp(W, L1);
            print_mat(L1, "Slow APSP result");

            break;
        }

        case 2: {
            // Faster-APSP
            faster_apsp(W, L1);
            print_mat(L1, "Faster APSP result");

            break;
        }

        case 3: {
            // 23.1-5
            int dist[N];
            int src = 0;
            pseudo_bellman_ford(W, src, dist);
            break;
        }

        case 4: {
            // 23.1-6 slow
            space_optimized_slow_apsp(W, L1);
            print_mat(L1, "Slow APSP result");
            break;
        }

        case 5: {
            // 23.1-6 faster
            space_optimized_faster_apsp(W, L1);
            print_mat(L1, "Faster APSP result");
            break;
        }

        case 6: {
            // 23.1-7
            space_optimized_faster_apsp(W, L1);
            int pred[N][N];
            compute_pred_mat(L1, W, pred);
            print_pred_mat(pred, "Predecessor matrix from L");
            break;
        }

        case 7: {
            // 23.1-8
            int pred[N][N];
            space_optimized_slow_apsp_mod(W, L1, pred);
            print_mat(L1, "Slow APSP MOD result");
            print_pred_mat(pred, "Predecessor matrix");
            break;
        }

        case 8: {
            // 23.1-9
            faster_apsp_neg_cycle(W, L1);
            break;
        }

        case 9: {
            // 23.1-10
            int len = min_length_neg_cycle(W);
            if (len) 
                printf("Minimum-length negative-weight cycle has %d edges.\n", len);
            else 
                printf("No negative-weight cycle found.\n");
            break;
        }
        
        default:
            break;
    }

    return 0;
}