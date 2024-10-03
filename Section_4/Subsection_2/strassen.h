#ifndef STRASSEN_H
#define STRASSEN_H

#define ROW_1 4
#define COL_1 4
#define ROW_2 4
#define COL_2 4

void print_matrix(char *display, int matrix[ROW_1][COL_1], int start_row, int start_column, int end_row, int end_column);
void add_matrices(int matrix_A[ROW_1][COL_1], int matrix_B[ROW_2][COL_2], int result[ROW_1][COL_1], int split_index, int multiplier);
void multiply_matrices(int matrix_A[ROW_1][COL_1], int matrix_B[ROW_2][COL_2], int result_matrix[ROW_1][COL_2]);

#endif