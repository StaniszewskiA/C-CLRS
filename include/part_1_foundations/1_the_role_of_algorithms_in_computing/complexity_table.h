#ifndef COMPLEXITY_TABLE_H
#define COMPLEXITY_TABLE_H

#include "../../common.h"

// Time in microseconds
#define ONE_SECOND 1000000LL
#define ONE_MINUTE (60 * ONE_SECOND)
#define ONE_HOUR (60 * ONE_MINUTE)
#define ONE_DAY (24 * ONE_HOUR)
#define ONE_MONTH (30 * ONE_DAY)
#define ONE_YEAR (365 * ONE_MONTH)
#define ONE_CENTURY (100 * ONE_YEAR)

// Maximum input size for a given time limit
long long logarithmic_time(long long time_limit, long long base);
long long logarithmic_time_wrapper(long long time_limit);
long long sqrt_time(long long time_limit);
long long linear_time(long long time_limit);
long long linearithmic_time(long long time_limit);
long long quadratic_time(long long time_limit);
long long cubic_time(long long time_limit);
long long exponential_time(long long time_limit);
long long factorial_time(long long time_limit);

// Utils
long long factorial(long long n);
double log_base(double x, double base);

// Display
void print_complexity_table(void);
void print_time_comparison(long long n);
void generate_complexity_chart(long long max_n);

// Problem size calculcations
typedef struct {
    const char* complexityName;
    long long (*complexity_func)(long long);
    const char* description;
} ComplexityEntry;

void calculate_problem_sizes_for_time_limit(long long time_limit);
void demonstrate_growth_rates(void);

// Formatting
const char* format_time(long long microseconds);
const char* format_large_number(long long number);

#endif // COMPLEXITY_TABLE_H
