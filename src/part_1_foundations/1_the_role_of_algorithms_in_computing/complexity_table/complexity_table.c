#include "../../../../include/part_1_foundations/1_the_role_of_algorithms_in_computing/complexity_table.h"

double log_base(double x, double base) {
    return log(x) / log(base);
}

long long logarithmic_time(long long time_limit, long long base) {
    if (time_limit <= 0 || base <= 1) return 0;
    
    double result = pow((double)base, (double)time_limit);
    
    if (result > LLONG_MAX) return LLONG_MAX;
    return (long long)result;
}

long long logarithmic_time_wrapper(long long time_limit) {
    return logarithmic_time(time_limit, 2); 
}

long long sqrt_time(long long time_limit) {
    if (time_limit <= 0) return 0;
    
    if (time_limit > sqrt(LLONG_MAX)) return LLONG_MAX;
    return time_limit * time_limit;
}

long long linear_time(long long time_limit) {
    return time_limit > 0 ? time_limit : 0;
}

long long linearithmic_time(long long time_limit) {
    if (time_limit <= 0) return 0;
    
    long long left = 1, right = time_limit, result = 1;
    
    while (left <= right) {
        long long mid = left + (right - left) / 2;
        
        double complexity = mid * log_base(mid, 2.0);
        
        if (complexity <= time_limit) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
        
        if (right - left > time_limit) break;
    }
    
    return result;
}

long long quadratic_time(long long time_limit) {
    if (time_limit <= 0) return 0;
    return (long long)sqrt((double)time_limit);
}

long long cubic_time(long long time_limit) {
    if (time_limit <= 0) return 0;
    return (long long)cbrt((double)time_limit);
}

long long exponential_time(long long time_limit) {
    if (time_limit <= 0) return 0;
    return (long long)log_base((double)time_limit, 2.0);
}

long long factorial_time(long long time_limit) {
    if (time_limit <= 0) return 0;
    
    long long n = 1;
    long long fact = 1;
    
    while (fact <= time_limit / n) { 
        n++;
        fact *= n;
        if (fact > time_limit) {
            return n - 1;
        }
    }
    
    return n - 1;
}

long long factorial(long long n) {
    if (n <= 1) return 1;
    if (n > 20) return LLONG_MAX; 
    
    long long result = 1;
    for (long long i = 2; i <= n; i++) {
        if (result > LLONG_MAX / i) return LLONG_MAX;  
        result *= i;
    }
    return result;
}

const char* format_time(long long microseconds) {
    static char buffer[100];
    
    if (microseconds < ONE_SECOND) {
        snprintf(buffer, sizeof(buffer), "%lld micro sec", microseconds);
    } else if (microseconds < ONE_MINUTE) {
        snprintf(buffer, sizeof(buffer), "%.2f sec", (double)microseconds / ONE_SECOND);
    } else if (microseconds < ONE_HOUR) {
        snprintf(buffer, sizeof(buffer), "%.2f min", (double)microseconds / ONE_MINUTE);
    } else if (microseconds < ONE_DAY) {
        snprintf(buffer, sizeof(buffer), "%.2f hrs", (double)microseconds / ONE_HOUR);
    } else if (microseconds < ONE_YEAR) {
        snprintf(buffer, sizeof(buffer), "%.2f days", (double)microseconds / ONE_DAY);
    } else if (microseconds < ONE_CENTURY) {
        snprintf(buffer, sizeof(buffer), "%.2f years", (double)microseconds / ONE_YEAR);
    } else {
        snprintf(buffer, sizeof(buffer), "%.2f centuries", (double)microseconds / ONE_CENTURY);
    }
    
    return buffer;
}

const char* format_large_number(long long number) {
    static char buffer[50];
    
    if (number < 1000) {
        snprintf(buffer, sizeof(buffer), "%lld", number);
    } else if (number < 1000000) {
        snprintf(buffer, sizeof(buffer), "%.2fK", (double)number / 1000);
    } else if (number < 1000000000) {
        snprintf(buffer, sizeof(buffer), "%.2fM", (double)number / 1000000);
    } else if (number < 1000000000000LL) {
        snprintf(buffer, sizeof(buffer), "%.2fB", (double)number / 1000000000);
    } else {
        snprintf(buffer, sizeof(buffer), "%.2fT", (double)number / 1000000000000LL);
    }
    
    return buffer;
}

void print_complexity_table(void) {
    printf("\nMaximum problem size solvable in given time:\n");
    printf("%-15s %-12s %-12s %-12s %-12s %-12s\n", 
           "Complexity", "1 second", "1 minute", "1 hour", "1 day", "1 month");
    printf("%-15s %-12s %-12s %-12s %-12s %-12s\n", 
           "----------", "--------", "--------", "------", "-----", "-------");
    
    ComplexityEntry entries[] = {
        {"log_2(n)", logarithmic_time_wrapper, "Logarithmic (base 2)"},
        {"sqrt(n)", sqrt_time, "Square root"},
        {"n", linear_time, "Linear"},
        {"n log n", linearithmic_time, "Linearithmic"},
        {"n^2", quadratic_time, "Quadratic"},
        {"n^3", cubic_time, "Cubic"},
        {"2^n", exponential_time, "Exponential"},
        {"n!", factorial_time, "Factorial"}
    };
    
    int num_entries = sizeof(entries) / sizeof(entries[0]);
    long long time_limits[] = {ONE_SECOND, ONE_MINUTE, ONE_HOUR, ONE_DAY, ONE_MONTH};
    
    for (int i = 0; i < num_entries; i++) {
        printf("%-15s ", entries[i].complexityName);
        
        for (int j = 0; j < 5; j++) {
            long long max_n = entries[i].complexity_func(time_limits[j]);
            printf("%-12s ", format_large_number(max_n));
        }
        printf("\n");
    }
}

void calculate_problem_sizes_for_time_limit(long long time_limit) {
    printf("\nMaximum problem size solvable in %s:\n", format_time(time_limit));
    printf("%-15s %-15s\n", "Complexity", "Max n");
    printf("%-15s %-15s\n", "----------", "-----");
    
    printf("%-15s %-15s\n", "log_2(n)", format_large_number(logarithmic_time(time_limit, 2)));
    printf("%-15s %-15s\n", "sqrt(n)", format_large_number(sqrt_time(time_limit)));
    printf("%-15s %-15s\n", "n", format_large_number(linear_time(time_limit)));
    printf("%-15s %-15s\n", "n log n", format_large_number(linearithmic_time(time_limit)));
    printf("%-15s %-15s\n", "n^2", format_large_number(quadratic_time(time_limit)));
    printf("%-15s %-15s\n", "n^3", format_large_number(cubic_time(time_limit)));
    printf("%-15s %-15s\n", "2^n", format_large_number(exponential_time(time_limit)));
    printf("%-15s %-15s\n", "n!", format_large_number(factorial_time(time_limit)));
}

void print_time_comparison(long long n) {
    printf("\nExecution time for n = %s:\n", format_large_number(n));
    printf("%-15s %-20s\n", "Complexity", "Time");
    printf("%-15s %-20s\n", "----------", "----");
    
    long long log_time = (long long)log_base((double)n, 2.0);
    long long sqrt_op_time = (long long)sqrt((double)n);
    long long linear_op_time = n;
    long long nlogn_time = (long long)(n * log_base((double)n, 2.0));
    long long quadratic_op_time = (n <= 46340) ? n * n : LLONG_MAX;  
    long long cubic_op_time = (n <= 2097) ? n * n * n : LLONG_MAX;   
    
    printf("%-15s %-20s\n", "log_2(n)", format_time(log_time));
    printf("%-15s %-20s\n", "sqrt(n)", format_time(sqrt_op_time));
    printf("%-15s %-20s\n", "n", format_time(linear_op_time));
    printf("%-15s %-20s\n", "n log n", format_time(nlogn_time));
    
    if (quadratic_op_time == LLONG_MAX) {
        printf("%-15s %-20s\n", "n^2", "> 1 century");
    } else {
        printf("%-15s %-20s\n", "n^3", format_time(quadratic_op_time));
    }
    
    if (cubic_op_time == LLONG_MAX) {
        printf("%-15s %-20s\n", "n^3", "> 1 century");
    } else {
        printf("%-15s %-20s\n", "n^3", format_time(cubic_op_time));
    }
    
    if (n <= 60) {
        long long exp_time = (long long)pow(2.0, (double)n);
        if (exp_time > ONE_CENTURY) {
            printf("%-15s %-20s\n", "2^n", "> 1 century");
        } else {
            printf("%-15s %-20s\n", "2^n", format_time(exp_time));
        }
    } else {
        printf("%-15s %-20s\n", "2^n", "> 1 century");
    }
    
    if (n <= 20) {
        printf("%-15s %-20s\n", "n!", format_time(factorial(n)));
    } else {
        printf("%-15s %-20s\n", "n!", "> 1 century");
    }
}

void demonstrate_growth_rates(void) {
    printf("\nGrowth Rate Demonstration:\n");
    printf("%-10s %-10s %-10s %-12s %-12s %-12s %-12s\n", 
           "n", "log_2(n)", "sqrt(n)", "n", "n log n", "n^2", "n^3");
    printf("%-10s %-10s %-10s %-12s %-12s %-12s %-12s\n", 
           "--", "------", "--", "-", "-------", "--", "--");
    
    int sizes[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    
    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];
        printf("%-10d %-10.1f %-10.1f %-12d %-12.1f %-12lld %-12lld\n",
               n,
               log_base((double)n, 2.0),
               sqrt((double)n),
               n,
               n * log_base((double)n, 2.0),
               (long long)n * n,
               (long long)n * n * n);
    }
}

void generate_complexity_chart(long long max_n) {
    printf("\nComplexity Growth Chart (relative scale):\n");
    printf("n = 1 to %s\n", format_large_number(max_n));
        
    printf("\nSample data points:\n");
    printf("%-10s %-10s %-10s %-10s %-10s\n", "n", "log n", "n", "n log n", "n²");
    
    for (long long n = 1; n <= max_n; n *= 2) {
        if (n > 1024) break;  
        
        printf("%-10lld %-10.1f %-10lld %-10.1f %-10lld\n",
               n,
               log_base((double)n, 2.0),
               n,
               n * log_base((double)n, 2.0),
               n * n);
    }
}