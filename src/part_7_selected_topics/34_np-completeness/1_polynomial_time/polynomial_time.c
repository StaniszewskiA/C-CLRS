#include "part_7_selected_topics/34_np-completeness/34_np-completeness.h"

static const char* enc_h(char c) {
    switch (c) {
        case '0': return "00";
        case '1': return "11";
        case ',': return "01";
        default:  return "10";
    }
}

static char enc_h_inverse(const char* pair) {
    if (pair[0] == pair[1]) return pair[0];
    return pair[0] == '0' ? ',' : ';';
}

static int enc_put(
    char* y,
    int k,
    char c
) {
    const char* code = enc_h(c);
    y[k] = code[0];
    y[k + 1] = code[1];

    return k + 2;
}

static int enc_put_number(
    char* y,
    int k,
    int j
) {
    int b = get_num_bits(j) - 1;
    for (; b >= 0; --b) k = enc_put(
        y,
        k,
        (j >> b) & 1 ? '1' : '0'
    );

    return k;
}

// 34.1-3: f_12, e_1(G) -> e_2(G)
char* convert_matrix_to_lists(const char* x) {
    int len = (int)strlen(x);
    int n = 0;
    while (n * n < len) n++;
    if (n * n != len) return NULL;

    char* y = safe_malloc(
        2 * n * (n * get_num_bits(n) + n) + 1
    );

    int k = 0;
    for (int i = 0; i < n; ++i) {
        int first = 1;
        for (int j = 0; j < n; ++j) {
            if (x[i * n + j] != '1') continue;

            if (!first) k = enc_put(
                y,
                k,
                ','
            );
            k = enc_put_number(
                y,
                k,
                j + 1
            );
            first = 0;
        }
        k = enc_put(
            y,
            k,
            ';'
        );
    }
    y[k] = '\0';

    return y;
}

// 34.1-3: f_21, e_2(G) -> e_1(G)
char* convert_lists_to_matrix(const char* y) {
    int len = (int)strlen(y);
    if (len & 1) return NULL;

    // n = number of semicolons
    int n = 0;
    for (int k = 0; k < len; k += 2)
        if (enc_h_inverse(&y[k]) == ';') n++;

    char* x = safe_malloc(n * n + 1);
    memset(x, '0', n * n);
    x[n * n] = '\0';

    int i = 0;
    int j = 0;
    int inNumber = 0;
    int valid = 1;
    for (int k = 0; k < len && valid; k += 2) {
        char c = enc_h_inverse(&y[k]);
        if (c == '0' || c == '1') {
            j = 2 * j + (c - '0');
            inNumber = 1;
            valid = j <= n;
            continue;
        }

        // ',' or ';' closes the current number
        if (inNumber) {
            valid = i < n && j >= 1;
            if (valid) x[i * n + j - 1] = '1';
        }

        if (c == ';') i++;
        j = 0;
        inNumber = 0;
    }

    // digits after the last semilocon do not farm a complete list
    if (!valid || inNumber) {
        safe_free(x);
        return NULL;
    }

    return x;
}

static void enc_print_run(
    const char* title,
    const char* x
) {
    char* y = convert_matrix_to_lists(x);
    char* back = convert_lists_to_matrix(y);

    printf("%s\n", title);
    printf("  e1(G)            = %s\n", x);
    printf("  f12(e1(G))       = %s\n", y);
    printf("  h^-1(f12(e1(G))) = ");
    for (int k = 0; y[k] != '\0'; k += 2) putchar(enc_h_inverse(&y[k]));
    printf("\n");
    printf("  f21(f12(e1(G)))  = %s (%s)\n\n",
        back,
        strcmp(back, x) == 0 ? "round trip OK" : "round trip FAILED"
    );

    safe_free(y);
    safe_free(back);
}

void test_encoding_conversion(void) {
    print_separator("Matrix <-> adjacency lists encoding (34.1-3)");

    enc_print_run("cycle 1 -> 2 -> 3 -> 1", "010001100");
    enc_print_run("Adj[1] = <2, 3, 4>, Adj[2] = <>, Adj[3] = <3>, Adj[4] = <1, 4>",
        "0111000000101001"
    );

    int n = ENC_N_VERTICES;
    char empty[ENC_N_VERTICES * ENC_N_VERTICES + 1];
    char complete[ENC_N_VERTICES * ENC_N_VERTICES + 1];
    memset(empty, '0', n * n);
    memset(complete, '1', n * n);
    empty[n * n] = '\0';
    complete[n * n] = '\0';

    const char* names[] = {
        "no edges",
        "all n^2 edges"
    };
    const char* graphs[] = {
        empty,
        complete
    };
    int graphSizes = (int)ARRAY_SIZE(graphs);

    printf("n = %d           | |e1(G)| | |e2(G)| | round trip\n", n);
    for (int g = 0; g < graphSizes; ++g) {
        char* y = convert_matrix_to_lists(graphs[g]);
        char* back = convert_lists_to_matrix(y);

        printf("%-15s | %7d | %7d | %s\n",
            names[g], (int)strlen(graphs[g]), (int)strlen(y),
            strcmp(back, graphs[g]) == 0 ? "OK" : "FAILED"
        );

        safe_free(y);
        safe_free(back);
    }

    printf("\nf12(\"010\")    = %s (length is not a square)\n",
        convert_matrix_to_lists("010") == NULL ? "NULL" : "not NULL"
    );
    printf("f21(\"111110\") = %s (\"11;\": vertex 3 in a 1-vertex graph)\n",
        convert_lists_to_matrix("111110") == NULL ? "NULL" : "not NULL"
    );
}