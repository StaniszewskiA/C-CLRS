// complexity_table.h
#ifndef COMPLEXITY_TABLE_H
#define COMPLEXITY_TABLE_H

// Time in microseconds
#define ONE_SECOND 1000000LL
#define ONE_MINUTE (60 * ONE_SECOND)
#define ONE_HOUR (60 * ONE_MINUTE)
#define ONE_DAY (24 * ONE_HOUR)
#define ONE_MONTH (30 * ONE_DAY)
#define ONE_YEAR (365 * ONE_MONTH)
#define ONE_CENTURY (100 * ONE_YEAR)

long long logarithmic_time(long long time, long long base);
long long sqrt_time(long long time);
long long linear_time(long long time);
long long linearithmic_time(long long time);
long long quadratic_time(long long time);
long long cubic_time(long long time);
long long exponential_time(long long time);
long long factorial_time(long long time);

#endif
