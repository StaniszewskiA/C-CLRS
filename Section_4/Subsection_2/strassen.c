#include "strassen.h"
#include <stdio.h>
#include <stdlib.h>

void print_matrix(char *display, int matrix[ROW_1][COL_1], int start_row, int start_column, int end_row, int end_column) {
    printf("\n%s =>\n", display);
    for (int i = start_row; i <= end_row; i++) {
        for (int j = start_column; j <= end_column; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void add_matrices(int matrix_A[ROW_1][COL_1], int matrix_B[ROW_2][COL_2], int result[ROW_1][COL_1], int split_index, int multiplier) {
    for (int i = 0; i < split_index; i++)
        for (int j = 0; j < split_index; j++)
        result[i][j] = matrix_A[i][j] + multiplier * matrix_B[i][j];
}

void multiply_matrices(int matrix_A[ROW_1][COL_1], int matrix_B[ROW_2][COL_2], int result_matrix[ROW_1][COL_2]) {
    int col_1 = COL_1;
    int row_1 = ROW_1;
    int col_2 = COL_2;
    int row_2 = ROW_2;

    if (col_1 != row_2) {
        printf("\nError: The number of columns in Matrix A must be equal to the number of rows in Matrix B\n");
        return;
    }

    if (col_1 == 1) {
        result_matrix[0][0] = matrix_A[0][0] * matrix_B[0][0];
    } else {
        int split_index = col_1 / 2;

        int a00[ROW_1 / 2][COL_1 / 2], a01[ROW_1 / 2][COL_1 / 2];
        int a10[ROW_1 / 2][COL_1 / 2], a11[ROW_1 / 2][COL_1 / 2];
        int b00[ROW_2 / 2][COL_2 / 2], b01[ROW_2 / 2][COL_2 / 2];
        int b10[ROW_2 / 2][COL_2 / 2], b11[ROW_2 / 2][COL_2 / 2];

        for (int i = 0; i < split_index; i++) {
            for (int j = 0; j < split_index; j++) {
                a00[i][j] = matrix_A[i][j];
                a01[i][j] = matrix_A[i][j + split_index];
                a10[i][j] = matrix_A[split_index + i][j];
                a11[i][j] = matrix_A[i + split_index][j + split_index];
                b00[i][j] = matrix_B[i][j];
                b01[i][j] = matrix_B[i][j + split_index];
                b10[i][j] = matrix_B[split_index + i][j];
                b11[i][j] = matrix_B[i + split_index][j + split_index];
            }
        }

        int p[ROW_1 / 2][COL_2 / 2], q[ROW_1 / 2][COL_2 / 2], r[ROW_1 / 2][COL_2 / 2], s[ROW_1 / 2][COL_2 / 2];
        int t[ROW_1 / 2][COL_2 / 2], u[ROW_1 / 2][COL_2 / 2], v[ROW_1 / 2][COL_2 / 2];

        int temp1[ROW_1 / 2][COL_1 / 2], temp2[ROW_1 / 2][COL_1 / 2];

        add_matrices(b01, b11, temp1, split_index, -1);
        multiply_matrices(a00, temp1, p);

        add_matrices(a00, a01, temp1, split_index, 1);
        multiply_matrices(temp1, b11, q);

        add_matrices(a10, a11, temp1, split_index, 1);
        multiply_matrices(temp1, b00, r);

        add_matrices(b10, b00, temp1, split_index, -1);
        multiply_matrices(a11, temp1, s);

        add_matrices(a00, a11, temp1, split_index, 1);
        add_matrices(b00, b11, temp2, split_index, 1);
        multiply_matrices(temp1, temp2, t);

        add_matrices(a01, a11, temp1, split_index, -1);
        add_matrices(b10, b11, temp2, split_index, 1);
        multiply_matrices(temp1, temp2, u);

        add_matrices(a00, a10, temp1, split_index, -1);
        add_matrices(b00, b01, temp2, split_index, 1);
        multiply_matrices(temp1, temp2, v);

        int result_matrix_00[ROW_1 / 2][COL_2 / 2], result_matrix_01[ROW_1 / 2][COL_2 / 2];
        int result_matrix_10[ROW_1 / 2][COL_2 / 2], result_matrix_11[ROW_1 / 2][COL_2 / 2];

        add_matrices(t, s, temp1, split_index, 1);
        add_matrices(temp1, u, temp2, split_index, 1);
        add_matrices(temp2, q, result_matrix_00, split_index, -1);

        add_matrices(p, q, result_matrix_01, split_index, 1);
        add_matrices(r, s, result_matrix_10, split_index, 1);

        add_matrices(t, p, temp1, split_index, 1);
        add_matrices(temp1, r, temp2, split_index, -1);
        add_matrices(temp2, v, result_matrix_11, split_index, -1);

        for (int i = 0; i < split_index; i++) {
            for (int j = 0; j < split_index; j++) {
                result_matrix[i][j] = result_matrix_00[i][j];
                result_matrix[i][j + split_index] = result_matrix_01[i][j];
                result_matrix[split_index + i][j] = result_matrix_10[i][j];
                result_matrix[split_index + i][j + split_index] = result_matrix_11[i][j];
            }
        }
    }
}

int main() {
    int matrix_A[ROW_1][COL_1] = { {1, 1, 1, 1},
                                    {2, 2, 2, 2},
                                    {3, 3, 3, 3},
                                    {2, 2, 2, 2} };

    print_matrix("Matrix A", matrix_A, 0, 0, ROW_1 - 1,  COL_1 - 1);

    int matrix_B[ROW_2][COL_2] = { {1, 1, 1, 1},
                                   {2, 2, 2, 2},
                                   {3, 3, 3, 3},
                                   {2, 2, 2, 2} };

    print_matrix("Matrix B", matrix_B, 0, 0, ROW_2 - 1, COL_2 - 1);

    int result_matrix[ROW_1][COL_2] = {0};
    multiply_matrices(matrix_A, matrix_B, result_matrix);

    return 0;
}