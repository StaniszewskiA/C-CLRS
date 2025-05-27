#include <stdio.h>
#include <limits.h>
#include <math.h>

#define TASK 9
#define N 6
#define INF INT_MAX
#define BUFFER_SIZE 64

#pragma region Basic Floyd-Warshall

void print_mat(int mat[N][N], const char* name) {
    printf("%s:\n", name);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (mat[i][j] == INF) printf("%5s", "INF");
            else printf("%5d", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void floyd_warshall(int W[N][N], int D[N][N]) {
    int Dk[N + 1][N][N];

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            Dk[0][i][j] = W[i][j];

    for (int k = 1; k <= N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
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
        print_mat(Dk[k], buff);
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            D[i][j] = Dk[N][i][j];
}

#pragma endregion Basic Floyd-Warshall

#pragma region Transitive closure

void print_bool_mat(int mat[N][N], const char* name) {
    printf("%s:\n", name);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) printf("%2d", mat[i][j]);
        printf("\n");
    }
    printf("\n");
}

void transitive_closure(int W[N][N], int T[N][N]) {
    for (int i = 0; i < N; i++) 
        for (int j = 0; j < N; j++)
            T[i][j] = (i == j || W[i][j] != INF) ? 1 : 0;

    for (int k = 0; k < N; k++)
        for (int i = 0; i < N; i++) 
            for (int j = 0; j < N; j++)
                T[i][j] = T[i][j] | (T[i][k] && T[k][j]);
}

#pragma endregion Transitive closure

#pragma region 23.2-2

void extend_transitive_paths(int A[N][N], int B[N][N], int C[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = A[i][j];
            for (int k = 0; k < N; k++) 
                C[i][j] = C[i][j] | (A[i][k] && B[k][j]);
        }
    }
}

void slow_apsp_transitive_closure(int W[N][N], int T[N][N]) {
    int prevL[N][N], currL[N][N];

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            prevL[i][j] = (i == j || W[i][j] != INF) ? 1 : 0;

    print_bool_mat(prevL, "Slow APSP transitive closure: L^{1}");

    for (int m = 2; m <= N - 1; m++) {
        extend_transitive_paths(prevL, prevL, currL);
        char buff[BUFFER_SIZE];
        snprintf(buff, sizeof(buff), "Slow APSP transitive closure: L^{%d}", m);
        print_bool_mat(currL, buff);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                prevL[i][j] = currL[i][j];
    } 

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            T[i][j] = prevL[i][j];
}

#pragma endregion 23.2-2

#pragma region 23.2-3

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

void floyd_warshall_with_pred(int W[N][N], int D[N][N], int pred[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            D[i][j] = W[i][j];
            if (i != j && W[i][j] != INF) pred[i][j] = i;
            else pred[i][j] = -1;
        }
    }
            
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (D[i][k] == INF || D[k][j] == INF) continue;
                int cand = D[i][k] + D[k][j];
                if (D[i][j] <= cand) continue;
                D[i][j] = cand;
                pred[i][j] = pred[k][j];
            }
        }
        char buff[BUFFER_SIZE];
        snprintf(buff, sizeof(buff), "D^{%d}", k);
        print_mat(D, buff);

        snprintf(buff, sizeof(buff), "pred^{%d}", k);
        print_pred_mat(pred, buff);
    }
}

#pragma endregion 23.2-3

#pragma region 23.2-4

void space_optimized_floyd_warshall(int W[N][N], int D[N][N]) {
    for (int i = 0; i < N; i++) 
        for (int j = 0; j < N; j++)
            D[i][j] = W[i][j];
            
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (D[i][k] == INF || D[k][j] == INF) continue;
                int cand = D[i][k] + D[k][j];
                D[i][j] = fmin(D[i][j], cand);
            }
        }
        char buff[BUFFER_SIZE];
        snprintf(buff, sizeof(buff), "D^{%d}", k);
        print_mat(D, buff);
    }
}

#pragma endregion 23.2-4

#pragma region 23.2-6

void floyd_warshall_neg_cycle_detect(int W[N][N], int D[N][N]) {
    for (int i = 0; i < N; i++) 
        for (int j = 0; j < N; j++)
            D[i][j] = W[i][j];
            
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (D[i][k] == INF || D[k][j] == INF) continue;
                int cand = D[i][k] + D[k][j];
                D[i][j] = fmin(D[i][j], cand);
            }
        }
        char buff[BUFFER_SIZE];
        snprintf(buff, sizeof(buff), "D^{%d}", k);
        print_mat(D, buff);
    }

    int hasNegCycle = 0;
    for (int i = 0; i < N; i++) {
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

void print_path_phi_helper(int phi[N][N], int i, int j) {
    if (phi[i][j] == -1 && i != j) printf(" %d", j);
    else {
        int k = phi[i][j];
        print_path_phi_helper(phi, i, k);
        print_path_phi_helper(phi, k, j);
    }
}

void print_path_phi(int phi[N][N], int i, int j) {
    printf("%d", i);
    print_path_phi_helper(phi, i, j);
}

void floyd_warshall_phi(int W[N][N], int D[N][N], int phi[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            D[i][j] = W[i][j];
            phi[i][j] = -1;
        }
    }

    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
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

void transitive_closure_bfs(int W[N][N], int T[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            T[i][j] = 0;
        }
    }

    for (int src = 0; src < N; src++) {
        int visited[N] = {0};
        int queue[N];
        int front = 0, rear = 0;
        queue[rear++] = src;
        visited[src] = 1;
        while (front < rear) {
            int u = queue[front++];
            T[src][u] = 1;
            for (int v = 0; v < N; v++) {
                if (W[u][v] == INF || visited[v]) continue;
                queue[rear++] = v;
                visited[v] = 1;
            }
        }
    }
}

#pragma endregion 23.2-8

#pragma region 23.2-9

void dfs(int W[N][N], int node, int visited[N], int stack[N], int* stackIdx) {
    visited[node] = 1;
    for (int nei = 0; nei < N; nei++) {
        if (W[node][nei] == INF || visited[nei]) continue;
        dfs(W, nei, visited, stack, stackIdx);
    }
    stack[(*stackIdx)++] = node;
}

void assign_scc(
    int WT[N][N], 
    int node, 
    int visited[N], 
    int comp[N], 
    int compIdx
) {
    visited[node] = 1;
    comp[node] = compIdx;
    for (int nei = 0; nei < N; nei++) {
        if (WT[node][nei] == INF || visited[nei]) continue;
        assign_scc(WT, nei, visited, comp, compIdx);
    }
}

void transpose_graph(int W[N][N], int WT[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            WT[i][j] = W[j][i];
}

int kosaraju_scc(int W[N][N], int comp[N]) {
    int visited[N] = {0};
    int stack[N];
    int stackIdx = 0;
    int WT[N][N];

    for (int i = 0; i < N; i++) visited[i] = 0;
    for (int i = 0; i < N; i++)
        if (!visited[i]) dfs(W, i, visited, stack, &stackIdx);

    transpose_graph(W, WT);

    for (int i = 0; i < N; i++) visited[i] = 0;
    int numComps = 0;
    for (int i = N - 1; i >= 0; i--) {
        int v = stack[i];
        if (!visited[v]) assign_scc(WT, v, visited, comp, numComps++);
    }

    return numComps;
}

void transitive_closure_comps(int W[N][N], int T[N][N], int numComps) {
    for (int i = 0; i < numComps; i++)
        for (int j = 0; j < numComps; j++)
            T[i][j] = (i == j || W[i][j] != INF) ? 1 : 0;

    for (int k = 0; k < numComps; k++)
        for (int i = 0; i < numComps; i++)
            for (int j = 0; j < numComps; j++)
                T[i][j] = T[i][j] | (T[i][k] && T[k][j]);
}

void scc_transitive_closure(int W[N][N], int T[N][N]) {
    int comp[N];
    int numComps = kosaraju_scc(W, comp);

    int compGraph[N][N];
    for (int i = 0; i < numComps; i++)
        for (int j = 0; j < numComps; j++)
            compGraph[i][j] = INF;

    for (int u = 0; u < N; u++)
        for (int v = 0; v < N; v++)
            if (W[u][v] != INF && comp[u] != comp[v]) 
                compGraph[comp[u]][comp[v]] = 1;

    for (int i = 0; i < numComps; i++)
        compGraph[i][i] = 1;

    int compTC[N][N];
    transitive_closure_comps(compGraph, compTC, numComps);

    for (int u = 0; u < N; u++)
        for (int v = 0; v < N; v++)
            T[u][v] = (comp[u] == comp[v]) ? 1 : compTC[comp[u]][comp[v]];
}

#pragma endregion 23.2-9

int main(void) {
    int W[N][N] = {
        {0, INF, INF, INF, -1, INF},
        {1, 0, INF, 2, INF, INF},
        {INF, 2, 0, INF, INF, -8},
        {-4, INF, INF, 0, 3, INF},
        {INF, 7, INF, INF, 0, INF},
        {INF, 5, 10, INF, INF, 0}
    };
    int D[N][N];

    switch (TASK)
    {
        case 1: {
            // Basic FW
            floyd_warshall(W, D);
            print_mat(D, "Floyd-Warshall result");
            break;
        }

        case 2: {
            // Transitive closure
            int T[N][N];
            transitive_closure(W, T);
            print_bool_mat(T, "Transitive closure of graph W");
            break;
        }

        case 3: {
            // 23.2-2
            int T[N][N];
            slow_apsp_transitive_closure(W, T);
            print_bool_mat(T, "Transitive closure with slow APSP");
            break;
        }

        case 4: {
            // 23.2-3
            int D[N][N], pred[N][N];
            floyd_warshall_with_pred(W, D, pred);
            print_mat(D, "Floyd-Warshall result");
            print_pred_mat(pred, "Predecessor matrix");
            break;
        }

        case 5: {
            // 23.2-4
            space_optimized_floyd_warshall(W, D);
            print_mat(D, "Floyd-Warshall result");
            break;
        }

        case 6: {
            // 23.2-6
            floyd_warshall_neg_cycle_detect(W, D);
            break;
        }

        case 7: {
            // 23.2-7
            int phi[N][N];
            floyd_warshall_phi(W, D, phi);
            print_mat(D, "Floyd-Warshall result");
            printf("Shortest path from 0 to 3: ");
            print_path_phi(phi, 0, 3);
            printf("\n");
            break;
        }

        case 8: {
            // 23.2-8
            int T[N][N];
            transitive_closure_bfs(W, T);
            print_bool_mat(T, "Transitive closure of graph W");
            break;
        }

        case 9: {
            // 23.2-9
            int T[N][N];
            scc_transitive_closure(W, T);
            print_bool_mat(T, "Transitive closure of graph W with SCCs");
            break;
        }
        
        default:
            break;
    }

    return 0;
}