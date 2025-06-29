#include "../common.h"

// Matrix utils

void pretty_print_matrix(const char* name, int** A, int dim1, int dim2);
void get_submatrix(int** A, int** subA, int startRow, int startCol, int size);
void set_submatrix(int** A, int** subA, int startRow, int startCol, int size);
