#include "part_4_advanced_design_and_analysis_techniques/14_dynamic_programming/dynamic_programming.h"

int memo[100];

void init_memo(int n) {
    for (int i = 0; i <= n; i++) {
        memo[i] = -1;
    }
}