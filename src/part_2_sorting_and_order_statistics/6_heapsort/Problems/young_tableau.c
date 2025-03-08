#include <stdio.h>
#include <limits.h>

#define INF INT_MAX
#define MAX_ROWS 100
#define MAX_COLS 100

int extract_min(
    int Y[][MAX_COLS],
    int rows,
    int cols,
    int i,
    int j
) {
    int min = Y[i][j];

    if ((j + 1 >= cols || Y[i][j + 1] == INF) 
        && (i + 1 >= rows || Y[i + 1][j] == INF)) {
        Y[i][j] = INF;
        return min;
    }

    if (j + 1 < cols 
        && (i + 1 >= rows || Y[i][j + 1] < Y[i + 1][j])) {
        Y[i][j] = Y[i][j + 1];
        Y[i][j + 1] = min;
        return extract_min(Y, rows, cols, i, j + 1);
    } else {
        Y[i][j] = Y[i + 1][j];
        Y[i + 1][j] = min;
        return extract_min(Y, rows, cols, i + 1, j);
    }
}

void insert_key(
    int Y[][MAX_COLS],
    int rows,
    int cols,
    int m, 
    int n,
    int key
) {
    int i = m;
    int j = n;
    Y[i][j] = key;

    while ((i > 0 && Y[i - 1][j] > Y[i][j]) 
        || (j > 0 && Y[i][j - 1] > Y[i][j])) {
        if (j > 0 && (i == 0 || Y[i - 1][j] >= Y[i][j - 1])) {
            int temp = Y[i][j];
            Y[i][j] = Y[i][j - 1];
            Y[i][j - 1] = temp;
            j--;
        } else {
            int temp = Y[i][j];
            Y[i][j] = Y[i - 1][j];
            Y[i - 1][j] = temp;
            i--;
        }
    } 
}

void check(
    int Y[][MAX_COLS],
    int key,
    int i,
    int j
) {
    printf("Checking at (%d, %d): %d\n", i, j, Y[i][j]);
}

int search_key(
    int Y[][MAX_COLS],
    int rows,
    int cols,
    int m,
    int n,
    int key
) {
    int i = 0, j = 0;

    while (i < rows && j >= 0) {
        check(Y, key, i, j);
        if (Y[i][j] == key) {
            printf("Key %d found at (%d, %d)\n", key, i, j);
            return 1;
        }
        if (Y[i][j] > key) {
            j--; 
        } else {
            i++; 
        }
    }

    printf("Key %d not found.\n", key);
    return 0;
}

int main() {
    int Y[100][100] = { 
        {10, 20, 30, INF},
        {15, 25, 35, INF},
        {INF, INF, INF, INF}
    };

    int min_val = extract_min(Y, 3, 4, 0, 0);
    printf("Extracted min: %d\n", min_val);

    insert_key(Y, 3, 4, 2, 2, 17);
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            if (Y[i][j] == INF) {
                printf("INF ");
            } else {
                printf("%d ", Y[i][j]);
            }
        }
        printf("\n");
    }
    
    int key = 25;
    search_key(Y, 3, 4, 3, 4, key);
    
    return 0;
}