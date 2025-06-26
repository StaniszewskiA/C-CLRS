#include "../../../../include/part_1_foundations/1_the_role_of_algorithms_in_computing/complexity_table.h"

int main(void) {
    print_separator("Algorithm Complexity Analysis");
    print_complexity_table();

    print_separator("Problem Sizes for 1 Second");
    calculate_problem_sizes_for_time_limit(ONE_SECOND);
    
    print_separator("Problem Sizes for 1 Hour");
    calculate_problem_sizes_for_time_limit(ONE_HOUR);
    
    print_separator("Time Analysis for n=1000");
    print_time_comparison(1000);
    
    print_separator("Time Analysis for n=1000000");
    print_time_comparison(1000000);
    
    print_separator("Growth Rate Demonstration");
    demonstrate_growth_rates();
    
    return 0;  
}