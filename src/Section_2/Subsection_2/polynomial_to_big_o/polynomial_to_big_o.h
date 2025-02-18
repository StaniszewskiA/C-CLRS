#ifndef POLYNOMIAL_TO_BIG_O_H
#define POLYNOMIAL_TO_BIG_O_H

#define MAX_TERMS 100

typedef struct {
    int coefficient;
    int exponent;
} Term;

int findHighestDegree(const char *polynomial);
void determinBigO(int maxExponent);

#endif 