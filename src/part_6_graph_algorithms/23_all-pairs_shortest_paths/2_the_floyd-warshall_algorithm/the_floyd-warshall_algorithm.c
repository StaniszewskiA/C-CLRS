#include "part_6_graph_algorithms/23_all-pairs_shortest_paths/all-pairs_shortest_paths.h"

#pragma region Basic Floyd-Warshall

void floyd_warshall(
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int D[MAX_MAT_SIZE][MAX_MAT_SIZE]
) {
    int Dk[MAX_MAT_SIZE + 1][MAX_MAT_SIZE][MAX_MAT_SIZE];

    for (int i = 0; i < MAX_MAT_SIZE; i++)
        for (int j = 0; j < MAX_MAT_SIZE; j++)
            Dk[0][i][j] = W[i][j];

    for (int k = 1; k <= MAX_MAT_SIZE; k++) {
        for (int i = 0; i < MAX_MAT_SIZE; i++) {
            for (int j = 0; j < MAX_MAT_SIZE; j++) {
                if (Dk[k-1][i][k-1] == INF || Dk[k-1][k-1][j] == INF)
                    Dk[k][i][j] = Dk[k-1][i][j];
                else
                    Dk[k][i][j] = fmin(
                        Dk[k-1][i][j],
                        Dk[k-1][i][k-1] + Dk[k-1][k-1][j]
                    );
            }
        }
        char buff[BUFFER_SIZE];
        snprintf(buff, sizeof(buff), "D^{%d}", k);
        print_named_mat(Dk[k], buff);
    }

    for (int i = 0; i < MAX_MAT_SIZE; i++)
        for (int j = 0; j < MAX_MAT_SIZE; j++)
            D[i][j] = Dk[MAX_MAT_SIZE][i][j];
}

#pragma endregion Basic Floyd-Warshall

#pragma region Transitive closure

void transitive_closure(
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int T[MAX_MAT_SIZE][MAX_MAT_SIZE]
) {
    for (int i = 0; i < MAX_MAT_SIZE; i++) 
        for (int j = 0; j < MAX_MAT_SIZE; j++)
            T[i][j] = (i == j || W[i][j] != INF) ? 1 : 0;

    for (int k = 0; k < MAX_MAT_SIZE; k++)
        for (int i = 0; i < MAX_MAT_SIZE; i++) 
            for (int j = 0; j < MAX_MAT_SIZE; j++)
                T[i][j] = T[i][j] | (T[i][k] && T[k][j]);
}

#pragma endregion Transitive closure

#pragma region 23.2-2

void extend_transitive_paths(
    int A[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int B[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int C[MAX_MAT_SIZE][MAX_MAT_SIZE]
) {
    for (int i = 0; i < MAX_MAT_SIZE; i++) {
        for (int j = 0; j < MAX_MAT_SIZE; j++) {
            C[i][j] = A[i][j];
            for (int k = 0; k < MAX_MAT_SIZE; k++) 
                C[i][j] = C[i][j] | (A[i][k] && B[k][j]);
        }
    }
}

void slow_apsp_transitive_closure(
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int T[MAX_MAT_SIZE][MAX_MAT_SIZE]
) {
    int prevL[MAX_MAT_SIZE][MAX_MAT_SIZE], currL[MAX_MAT_SIZE][MAX_MAT_SIZE];

    for (int i = 0; i < MAX_MAT_SIZE; i++)
        for (int j = 0; j < MAX_MAT_SIZE; j++)
            prevL[i][j] = (i == j || W[i][j] != INF) ? 1 : 0;

    print_named_bool_mat(prevL, "Slow APSP transitive closure: L^{1}");

    for (int m = 2; m <= MAX_MAT_SIZE - 1; m++) {
        extend_transitive_paths(prevL, prevL, currL);
        char buff[BUFFER_SIZE];
        snprintf(buff, sizeof(buff), "Slow APSP transitive closure: L^{%d}", m);
        print_named_bool_mat(currL, buff);
        for (int i = 0; i < MAX_MAT_SIZE; i++)
            for (int j = 0; j < MAX_MAT_SIZE; j++)
                prevL[i][j] = currL[i][j];
    } 

    for (int i = 0; i < MAX_MAT_SIZE; i++)
        for (int j = 0; j < MAX_MAT_SIZE; j++)
            T[i][j] = prevL[i][j];
}

#pragma endregion 23.2-2

#pragma region 23.2-3

void floyd_warshall_with_pred(
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int D[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int pred[MAX_MAT_SIZE][MAX_MAT_SIZE]
) {
    for (int i = 0; i < MAX_MAT_SIZE; i++) {
        for (int j = 0; j < MAX_MAT_SIZE; j++) {
            D[i][j] = W[i][j];
            if (i != j && W[i][j] != INF) pred[i][j] = i;
            else pred[i][j] = -1;
        }
    }
            
    for (int k = 0; k < MAX_MAT_SIZE; k++) {
        for (int i = 0; i < MAX_MAT_SIZE; i++) {
            for (int j = 0; j < MAX_MAT_SIZE; j++) {
                if (D[i][k] == INF || D[k][j] == INF) continue;
                int cand = D[i][k] + D[k][j];
                if (D[i][j] <= cand) continue;
                D[i][j] = cand;
                pred[i][j] = pred[k][j];
            }
        }
        char buff[BUFFER_SIZE];
        snprintf(buff, sizeof(buff), "D^{%d}", k);
        print_named_mat(D, buff);

        snprintf(buff, sizeof(buff), "pred^{%d}", k);
        print_pred_mat(pred, buff);
    }
}

#pragma endregion 23.2-3

#pragma region 23.2-4

void space_optimized_floyd_warshall(
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int D[MAX_MAT_SIZE][MAX_MAT_SIZE]
) {
    for (int i = 0; i < MAX_MAT_SIZE; i++) 
        for (int j = 0; j < MAX_MAT_SIZE; j++)
            D[i][j] = W[i][j];
            
    for (int k = 0; k < MAX_MAT_SIZE; k++) {
        for (int i = 0; i < MAX_MAT_SIZE; i++) {
            for (int j = 0; j < MAX_MAT_SIZE; j++) {
                if (D[i][k] == INF || D[k][j] == INF) continue;
                int cand = D[i][k] + D[k][j];
                D[i][j] = fmin(D[i][j], cand);
            }
        }
        char buff[BUFFER_SIZE];
        snprintf(buff, sizeof(buff), "D^{%d}", k);
        print_named_mat(D, buff);
    }
}

#pragma endregion 23.2-4

#pragma region 23.2-6

void floyd_warshall_neg_cycle_detect(
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int D[MAX_MAT_SIZE][MAX_MAT_SIZE]
) {
    for (int i = 0; i < MAX_MAT_SIZE; i++) 
        for (int j = 0; j < MAX_MAT_SIZE; j++)
            D[i][j] = W[i][j];
            
    for (int k = 0; k < MAX_MAT_SIZE; k++) {
        for (int i = 0; i < MAX_MAT_SIZE; i++) {
            for (int j = 0; j < MAX_MAT_SIZE; j++) {
                if (D[i][k] == INF || D[k][j] == INF) continue;
                int cand = D[i][k] + D[k][j];
                D[i][j] = fmin(D[i][j], cand);
            }
        }
        char buff[BUFFER_SIZE];
        snprintf(buff, sizeof(buff), "D^{%d}", k);
        print_named_mat(D, buff);
    }

    int hasNegCycle = 0;
    for (int i = 0; i < MAX_MAT_SIZE; i++) {
        if (D[i][i] < 0) {
            hasNegCycle = 1;
            break;
        } 
    }

    if (hasNegCycle) printf("Negative-weight cycle detected!\n");
    else printf("No negative-weight cycle.\n");
}

#pragma endregion 23.2-6

#pragma region 23.2-7

void print_path_phi_helper(int phi[MAX_MAT_SIZE][MAX_MAT_SIZE], int i, int j) {
    if (phi[i][j] == -1 && i != j) printf(" %d", j);
    else {
        int k = phi[i][j];
        print_path_phi_helper(phi, i, k);
        print_path_phi_helper(phi, k, j);
    }
}

void print_path_phi(int phi[MAX_MAT_SIZE][MAX_MAT_SIZE], int i, int j) {
    printf("%d", i);
    print_path_phi_helper(phi, i, j);
}

void floyd_warshall_phi(
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int D[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int phi[MAX_MAT_SIZE][MAX_MAT_SIZE]
) {
    for (int i = 0; i < MAX_MAT_SIZE; i++) {
        for (int j = 0; j < MAX_MAT_SIZE; j++) {
            D[i][j] = W[i][j];
            phi[i][j] = -1;
        }
    }

    for (int k = 0; k < MAX_MAT_SIZE; k++) {
        for (int i = 0; i < MAX_MAT_SIZE; i++) {
            for (int j = 0; j < MAX_MAT_SIZE; j++) {
                if (D[i][k] == INF || D[k][j] == INF) continue;
                int cand = D[i][k] + D[k][j];
                if (D[i][j] <= cand) continue;
                D[i][j] = cand;
                phi[i][j] = k; 
            }
        }
    }
}

#pragma endregion 23.2-7

#pragma region 23.2-8

void transitive_closure_bfs(
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int T[MAX_MAT_SIZE][MAX_MAT_SIZE]
) {
    for (int i = 0; i < MAX_MAT_SIZE; i++) {
        for (int j = 0; j < MAX_MAT_SIZE; j++) {
            T[i][j] = 0;
        }
    }

    for (int src = 0; src < MAX_MAT_SIZE; src++) {
        int visited[MAX_MAT_SIZE] = {0};
        int queue[MAX_MAT_SIZE];
        int front = 0, rear = 0;
        queue[rear++] = src;
        visited[src] = 1;
        while (front < rear) {
            int u = queue[front++];
            T[src][u] = 1;
            for (int v = 0; v < MAX_MAT_SIZE; v++) {
                if (W[u][v] == INF || visited[v]) continue;
                queue[rear++] = v;
                visited[v] = 1;
            }
        }
    }
}

#pragma endregion 23.2-8

#pragma region 23.2-9

void dfs232(
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int node, 
    int visited[MAX_MAT_SIZE], 
    int stack[MAX_MAT_SIZE], 
    int* stackIdx
) {
    visited[node] = 1;
    for (int nei = 0; nei < MAX_MAT_SIZE; nei++) {
        if (W[node][nei] == INF || visited[nei]) continue;
        dfs232(W, nei, visited, stack, stackIdx);
    }
    stack[(*stackIdx)++] = node;
}

void assign_scc232(
    int WT[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int node, 
    int visited[MAX_MAT_SIZE], 
    int comp[MAX_MAT_SIZE], 
    int compIdx
) {
    visited[node] = 1;
    comp[node] = compIdx;
    for (int nei = 0; nei < MAX_MAT_SIZE; nei++) {
        if (WT[node][nei] == INF || visited[nei]) continue;
        assign_scc232(WT, nei, visited, comp, compIdx);
    }
}

void transpose_graph232(
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int WT[MAX_MAT_SIZE][MAX_MAT_SIZE]
) {
    for (int i = 0; i < MAX_MAT_SIZE; i++)
        for (int j = 0; j < MAX_MAT_SIZE; j++)
            WT[i][j] = W[j][i];
}

int kosaraju_scc232(
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int comp[MAX_MAT_SIZE]
) {
    int visited[MAX_MAT_SIZE] = {0};
    int stack[MAX_MAT_SIZE];
    int stackIdx = 0;
    int WT[MAX_MAT_SIZE][MAX_MAT_SIZE];

    for (int i = 0; i < MAX_MAT_SIZE; i++) visited[i] = 0;
    for (int i = 0; i < MAX_MAT_SIZE; i++)
        if (!visited[i]) dfs232(W, i, visited, stack, &stackIdx);

    transpose_graph232(W, WT);

    for (int i = 0; i < MAX_MAT_SIZE; i++) visited[i] = 0;
    int numComps = 0;
    for (int i = MAX_MAT_SIZE - 1; i >= 0; i--) {
        int v = stack[i];
        if (!visited[v]) assign_scc232(WT, v, visited, comp, numComps++);
    }

    return numComps;
}

void transitive_closure_comps(
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int T[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int numComps
) {
    for (int i = 0; i < numComps; i++)
        for (int j = 0; j < numComps; j++)
            T[i][j] = (i == j || W[i][j] != INF) ? 1 : 0;

    for (int k = 0; k < numComps; k++)
        for (int i = 0; i < numComps; i++)
            for (int j = 0; j < numComps; j++)
                T[i][j] = T[i][j] | (T[i][k] && T[k][j]);
}

void scc_transitive_closure(
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int T[MAX_MAT_SIZE][MAX_MAT_SIZE]
) {
    int comp[MAX_MAT_SIZE];
    int numComps = kosaraju_scc232(W, comp);

    int compGraph[MAX_MAT_SIZE][MAX_MAT_SIZE];
    for (int i = 0; i < numComps; i++)
        for (int j = 0; j < numComps; j++)
            compGraph[i][j] = INF;

    for (int u = 0; u < MAX_MAT_SIZE; u++)
        for (int v = 0; v < MAX_MAT_SIZE; v++)
            if (W[u][v] != INF && comp[u] != comp[v]) 
                compGraph[comp[u]][comp[v]] = 1;

    for (int i = 0; i < numComps; i++)
        compGraph[i][i] = 1;

    int compTC[MAX_MAT_SIZE][MAX_MAT_SIZE];
    transitive_closure_comps(compGraph, compTC, numComps);

    for (int u = 0; u < MAX_MAT_SIZE; u++)
        for (int v = 0; v < MAX_MAT_SIZE; v++)
            T[u][v] = (comp[u] == comp[v]) ? 1 : compTC[comp[u]][comp[v]];
}

#pragma endregion 23.2-9
