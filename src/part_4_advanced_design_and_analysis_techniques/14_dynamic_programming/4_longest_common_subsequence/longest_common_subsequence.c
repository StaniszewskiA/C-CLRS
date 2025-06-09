#include "part_4_advanced_design_and_analysis_techniques/14_dynamic_programming/dynamic_programming.h"

int lcs_brute_force(char *X, char *Y, int m, int n) {
    if (m == 0 || n == 0) return 0;

    if (X[m - 1] == Y[n - 1]) return 1 + lcs_brute_force(X, Y, m - 1, n - 1);
    else return fmin(lcs_brute_force(X, Y, m, n - 1), lcs_brute_force(X, Y, m - 1, n));
}

int lcs_dp(char *X, char *Y, int m, int n, int b[m+1][n+1], int c[m+1][n+1]) {
    for (int i = 0; i <= m; i++) c[i][0] = 0;
    for (int j = 0; j <= n; j++) c[0][j] = 0;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {  
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = 1;  
            }
            else if (c[i - 1][j] >= c[i][j - 1]) {  
                c[i][j] = c[i - 1][j];
                b[i][j] = 2;
            }
            else {  
                c[i][j] = c[i][j - 1];
                b[i][j] = 3;
            }
        }
    }

    return c[m][n];
}

void print_lcs(int b[SEQ_LEN + 1][SEQ_LEN + 1], char *X, int i, int j) {
    if (i == 0 || j == 0) return;

    if (b[i][j] == 1) {  
        print_lcs(b, X, i - 1, j - 1);  
        printf("%c", X[i - 1]);  
    }
    else if (b[i][j] == 2) 
        print_lcs(b, X, i - 1, j);
    else  
        print_lcs(b, X, i, j - 1);
}

void print_lcs_no_b(
    int c[SEQ_LEN + 1][SEQ_LEN + 1], 
    char *X, 
    char *Y, 
    int i, 
    int j
) {
    if (c[i][j] == 0) return;

    if (X[i] == Y[j]) {
        print_lcs_no_b(c, X, Y, i - 1, j - 1);
        printf("%c", X[i - 1]);  
    }
    else if (c[i - 1][j] > c[i][j - 1]) print_lcs_no_b(c, X, Y, i - 1, j);
    else print_lcs_no_b(c, X, Y, i, j - 1);
}

int memoized_lcs_len(
    int c[SEQ_LEN + 1][SEQ_LEN + 1], 
    char *X, 
    char *Y, 
    int i, 
    int j
) {
    if (c[i][j] > -1) return c[i][j];  

    if (i == 0 || j == 0) return c[i][j] = 0; 

    if (X[i - 1] == Y[j - 1]) { 
        c[i][j] = memoized_lcs_len(c, X, Y, i - 1, j - 1) + 1;
    } else {
        c[i][j] = fmax(
            memoized_lcs_len(c, X, Y, i - 1, j), 
            memoized_lcs_len(c, X, Y, i, j - 1)
        );  
    }

    return c[i][j];
}

void print_lcs_prim(
    int c[SEQ_LEN][SEQ_LEN], 
    char X[SEQ_LEN], 
    char Y[SEQ_LEN], 
    int m,
    int n
) {
    int s[SEQ_LEN];
    int i = m, j = n, n_lcs = c[m][n];

    while (i > 0 && j > 0) {
        if (X[i] == Y[j]) {
            s[n_lcs - 1] = X[i - 1];
            n_lcs = n_lcs - 1;
            i = i - 1;
            j = j + 1;
        } 
        else if (c[i - 1][j] >= c[i][j - 1]) i = i - 1;
        else j = j - 1;
    }

    for (int k = 0; k < c[m][n]; k++) {
        printf("%c", s[k]);
    }
    printf("\n");
}

int memo_lcs_length_aux(
    char X[SEQ_LEN], 
    char Y[SEQ_LEN], 
    int c[SEQ_LEN][SEQ_LEN], 
    int b[SEQ_LEN][SEQ_LEN], 
    int m, 
    int n
) {
    if (c[m][n] != 0 || m == 0 || n == 0) return 0;

    if (X[m - 1] == Y[n - 1]) {
        b[m][n] = DIAG;
        c[m][n] = memo_lcs_length_aux(X, Y, c, b, m - 1, n - 1) + 1;
    } else {
        int left = memo_lcs_length_aux(X, Y, c, b, m - 1, n);
        int up = memo_lcs_length_aux(X, Y, c, b, m, n - 1);

        if (left >= up) {
            b[m][n] = UP;
            c[m][n] = left;
        } else {
            b[m][n] = LEFT;
            c[m][n] = up;
        }
    }

    return c[m][n];
}

void memo_lcs_length(
    char X[SEQ_LEN], 
    char Y[SEQ_LEN], 
    int c[SEQ_LEN][SEQ_LEN], 
    int b[SEQ_LEN][SEQ_LEN], 
    int m, 
    int n
) {
    memo_lcs_length_aux(X, Y, c, b, m, n);
}


void print_list(List* list) {
    Node* temp = list->head;
    while (temp) {
        printf("%d ", temp->key);
        temp = temp->next;
    }
    printf("\n");
}

void list_insert(List* list, int key) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->key = key;
    new_node->next = NULL;  

    if (!list->head) list->head = new_node;
    else {
        Node* temp = list->head;
        while (temp->next) temp = temp->next;
        temp->next = new_node;
    }
}

void long_monotonic(int* A, int n) {
    int* B = (int*)malloc((n + 1) * sizeof(int));
    List* C = (List*)malloc((n + 1) * sizeof(List));

    for (int i = 0; i <= n; i++) {
        B[i] = INT_MAX;
        C[i].head = NULL;
    }

    int L = 1;

    for (int i = 0; i <= n; i++) {
        if (A[i] < B[i]) {
            B[1] = A[i];
            C[1].head = NULL;
            list_insert(&C[1], A[i]);
        } else {
            int j = 0;
            for (int k = 1; k <= L; k++) {
                if (B[k] < A[i]) {
                    j = k;
                }
            }
            B[j + 1] = A[i];
            C[j + 1] = C[j];
            list_insert(&C[j + 1], A[i]);
            if (j + i > L) L = j + 1;
        }
    }

    print_list(&C[L]);

    free(B);
    free(C);
}
