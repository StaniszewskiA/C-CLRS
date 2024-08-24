#include <stdio.h>
#include <math.h>
#include "complexity_table.h"

long long logarithmic_time(long long time, long long base) {
    if (time <= 0 || base <= 1) {
        return 0; 
    }
    double result = log((double)time) / log((double)base);
    return (long long)result;
}


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

    return 0;
}