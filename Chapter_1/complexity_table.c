#include <stdio.h>
#include <math.h>
#include <limits.h>
#include "complexity_table.h"

int main() {
    long long times[] = {
        ONE_SECOND, 
        ONE_MINUTE, 
        ONE_HOUR, 
        ONE_DAY,
        ONE_MONTH, 
        ONE_YEAR, 
        ONE_CENTURY
    };

    char *time_labels[] = {
        "1 Second", 
        "1 Minute", 
        "1 Hour", 
        "1 Day", 
        "1 Month",
        "1 Year", 
        "1 Century"
    };

    printf("%-15s", "Complexity");
    for (int i = 0; i < 7; i++) {
        printf(" | %-15s", time_labels[i]);
    }
    printf("\n");
    printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
    
    long long (*functions[])(long long) = {
        logarithmic_time, 
        sqrt_time,
        linear_time, 
        linearithmic_time, 
        quadratic_time, 
        cubic_time, 
        exponential_time, 
        factorial_time
    };

    const char *complexity_labels[] = {
        "Logarithmic", 
        "Square", 
        "Linear", 
        "Linearithmic", 
        "Quadratic", 
        "Cubic", 
        "Exponential", 
        "Factorial"
    };

    for (int i = 0; i < 8; i++) {
        printf("%-15s", complexity_labels[i]);
        for (int j = 0; j < 7; j++) {
            printf(" | %-15lld", functions[i](times[j]));
        }
        printf("\n");
    }

    return 0;
}

long long logarithmic_time(long long time, long long base) {
    return pow(base, time);
}

long long sqrt_time(long long time) {
    return pow(time, 2);
}

long long linear_time(long long time) {
    return (long long)time;
}

long long linearithmic_time(long long time) {
    long long left = 1;
    long long right = LLONG_MAX;
    long long result = 0;

    while (left <= right) {
        long long mid = left + (right - left) / 2;
        double log_mid = log2((double)mid);
        double value = mid * log_mid;

        if (value <= time) {
            result = mid;
            left = mid + 1;
        } 
        else {
            right = mid - 1;
        }
    }

    return result;
}

long long quadratic_time(long long time) {
    return (long long)sqrt((double)time);
}

long long cubic_time(long long time) {
    long long left = 0;
    long long right = 1;
    // Find a proper upper bound
    while (right * right * right <= time) {
        right *= 2;
    }
    long long result = 0;

    while (left <= right) {
        long long mid = left + (right - left) / 2;
        // Check for a potential overflow
        long long mid_squared = mid * mid;
        if (mid_squared > LLONG_MAX / mid) {
            right = mid - 1;
            continue;
        }
        long long mid_cubed = mid_squared * mid;

        if (mid_cubed <= time) {
            result = mid;
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return result;
}

long long exponential_time(long long time) {
    long long exponential_result = log2(time);
    return exponential_result;
}

long long factorial_time(long long time) {
    long long left = 1;
    // It is unlikely for upper bound to go beyond 20.
    long long right = 20;
    long long result = 0;

    while (left <= right) {
        long long mid = left + (right - left) / 2;
        long long fact = factorial(mid);

        if (fact <= time) {
            result = mid;
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return result;
}

long long factorial(long long n) {
    long long result = 1;
    for (long long i = 2; i <= n; i++) {
        if (result > LLONG_MAX / i) {
            return LLONG_MAX;
        }
        result *= i;
    }

    return result;
}
