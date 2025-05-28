#include <stdio.h>
#include <string.h>

#define TASK 2
#define N 4

#pragma region Transitive closure of a dynamic graph

void print_bool_mat(int mat[N][N], const char* name) {
    printf("%s:\n", name);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) printf("%2d", mat[i][j]);
        printf("\n");
    }
    printf("\n");
}

void update_transitive_closure(int T[N][N], int n, int x, int y) {
    if (T[x][y]) return;
    T[x][y] = 1;
    for (int u = 0; u < n; u++) {
        if (!T[u][x] && u != x) continue;
        for (int v = 0; v < n; v++) {
            if (T[y][v] || v == y) T[u][v] = 1;
        }
    }
}

void update_transitive_closure_prime(int T[N][N], int n, int x, int y) {
    if (T[x][y]) return;
    T[x][y] = 1;

    int uQueue[N], vQueue[N];
    int pred[N], succ[N];
    int predCnt = 0, succCnt = 0;

    for (int u = 0; u < n; u++) {
        if (!T[u][x] && u != x) continue;
        uQueue[predCnt++] = u;
    }

    for (int v = 0; v < n; v++) {
        if (!T[y][v] && v != y) {
            vQueue[succCnt++] = v;
        }
    }

    for (int i = 0; i < predCnt; i++) {
        int u = uQueue[i];
        for (int j = 0; j < succCnt; j++) {
            int v = vQueue[j];
            if (!T[u][v]) T[u][v] = 1;
        }
    }
}


#pragma endregion Transitive closure of a dynamic graph

#pragma region Shortest paths in epsilon-dense graphs

#pragma endregion Shortest paths in epsilon-dense graphs

int main(void) {
    switch (TASK)
    {
        case 1: {
            // Transitive closure of a dynamic graph A
            int n = 4;
            int T[N][N];
            memset(T, 0, sizeof(T));

            update_transitive_closure(T, n, 0, 1);
            print_bool_mat(T, "Transitive closure after adding vertex (0,1)");

            update_transitive_closure(T, n, 1, 2);
            print_bool_mat(T, "Transitive closure after adding vertex (1,2)");

            update_transitive_closure(T, n, 2, 3);
            print_bool_mat(T, "Transitive closure after adding vertex (2,3)");

            update_transitive_closure(T, n, 0, 3);
            print_bool_mat(T, "Transitive closure after adding vertex (0,3)");

            break;
        }

        case 2: {
            // Transitive closure of a dynamic graph C
            int n = 4;
            int T[N][N];
            memset(T, 0, sizeof(T));

            update_transitive_closure_prime(T, n, 0, 1);
            print_bool_mat(T, "Transitive closure after adding vertex (0,1)");

            update_transitive_closure_prime(T, n, 1, 2);
            print_bool_mat(T, "Transitive closure after adding vertex (1,2)");

            update_transitive_closure_prime(T, n, 2, 3);
            print_bool_mat(T, "Transitive closure after adding vertex (2,3)");

            update_transitive_closure_prime(T, n, 0, 3);
            print_bool_mat(T, "Transitive closure after adding vertex (0,3)");

            break;
        }
        
        default:
            break;
    }

    return 0;
}