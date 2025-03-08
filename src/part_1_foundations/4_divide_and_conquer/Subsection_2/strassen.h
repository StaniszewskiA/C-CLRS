#ifndef STRASSEN_H
#define STRASSEN_H

double** allocate_matrix(int size);
void input_matrix(double** matrix, int size, const char* name);
void free_matrix(double** matrix, int size);
void add_matrices(double** A, double** B, double** C, int size, int multiplier);
void strassen(double** A, double** B, double** c, int size);
void print_matrix(double** matrix, int size, const char* name);

#endif