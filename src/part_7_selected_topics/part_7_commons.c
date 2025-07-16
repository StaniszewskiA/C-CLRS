#include "../../include/part_7_selected_topics/part_7_commons.h"

// Matrix utils

void pretty_print_matrix(const char* name, int** A, int dim1, int dim2) {
    printf("%s:\n", name);
    for (int i = 0; i < dim1; ++i) {
        printf("[");
        for (int j = 0; j < dim2; ++j) printf("%5d", A[i][j]);
        printf("]\n");
    }
}

void get_submatrix(int** A, int** subA, int startRow, int startCol, int size) {
    for (int i = 0 ; i < size; ++i)
        for (int j = 0; j < size; ++j)
            subA[i][j] = A[startRow + i][startCol + j];
}

void set_submatrix(int** A, int** subA, int startRow, int startCol, int size) {
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            A[startRow + i][startCol + j] = subA[i][j];
}
