# C-CLRS Makefile
# Compiler and flags
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Iinclude -lm
SRCDIR = src
BINDIR = bin

# Common source files
COMMON_SRC = $(SRCDIR)/common.c
MAIN_SRC = $(SRCDIR)/main.c

# Part commons
PART_1_COMMONS_SRC = $(SRCDIR)/part_1_foundations/part_1_commons.c
PART_2_COMMONS_SRC = $(SRCDIR)/part_2_sorting_and_order_statistics/part_2_commons.c
PART_3_COMMONS_SRC = $(SRCDIR)/part_3_data_structures/part_3_commons.c
PART_4_COMMONS_SRC = $(SRCDIR)/part_4_advanced_design_and_analysis_techniques/part_4_commons.c
PART_5_COMMONS_SRC = $(SRCDIR)/part_5_advanced_data_structures/part_5_commons.c
PART_6_COMMONS_SRC = $(SRCDIR)/part_6_graph_algorithms/part_6_commons.c
PART_7_COMMONS_SRC = $(SRCDIR)/part_7_selected_topics/part_7_commons.c

# ============================================================================
# PART 1: FOUNDATIONS
# ============================================================================

# Chapter 1
COMPLEXITY_TABLE_SRC = $(SRCDIR)/part_1_foundations/1_the_role_of_algorithms_in_computing/complexity_table/complexity_table.c
COMPLEXITY_TABLE_MAIN = $(SRCDIR)/part_1_foundations/1_the_role_of_algorithms_in_computing/complexity_table/main.c

# Chapter 2
INSERTION_SORT_SRC = $(SRCDIR)/part_1_foundations/2_getting_started/1_insertion_sort/insertion_sort.c
INSERTION_SORT_MAIN = $(SRCDIR)/part_1_foundations/2_getting_started/1_insertion_sort/main.c

ANALYZING_ALGORITHMS_SRC = $(SRCDIR)/part_1_foundations/2_getting_started/2_analyzing_algorithms/analyzing_algorithms.c
ANALYZING_ALGORITHMS_MAIN = $(SRCDIR)/part_1_foundations/2_getting_started/2_analyzing_algorithms/main.c

DESIGNING_ALGORITHMS_SRC = $(SRCDIR)/part_1_foundations/2_getting_started/3_designing_algorithms/designing_algorithms.c
DESIGNING_ALGORITHMS_MAIN = $(SRCDIR)/part_1_foundations/2_getting_started/3_designing_algorithms/main.c

CHAPTER_2_PROBLEMS_SRC = $(SRCDIR)/part_1_foundations/2_getting_started/problems.c

# Chapter 4
SQUARE_MATRIX_MULT_SRC = $(SRCDIR)/part_1_foundations/4_divide_and_conquer/1_square_matrix_mutliplication/square_matrix_multiplication.c
SQUARE_MATRIX_MULT_MAIN = $(SRCDIR)/part_1_foundations/4_divide_and_conquer/1_square_matrix_mutliplication/main.c

STRASSEN_SRC = $(SRCDIR)/part_1_foundations/4_divide_and_conquer/2_strassen_algorithm/strassen_algorithm.c
STRASSEN_MAIN = $(SRCDIR)/part_1_foundations/4_divide_and_conquer/2_strassen_algorithm/main.c

# Chapter 5
HIRE_ASSISTANT_SRC = $(SRCDIR)/part_1_foundations/5_probabilistic_analysis_and_randomized_algorithms/1_hire_assistant/hire_assistant.c
HIRE_ASSISTANT_MAIN = $(SRCDIR)/part_1_foundations/5_probabilistic_analysis_and_randomized_algorithms/1_hire_assistant/main.c

CHAPTER_5_PROBLEMS_SRC = $(SRCDIR)/part_1_foundations/5_probabilistic_analysis_and_randomized_algorithms/problems.c

# ============================================================================
# PART 2: SORTING AND ORDER STATISTICS
# ============================================================================

# Chapter 6
MAINTAINING_HEAP_PROPERTY_SRC = $(SRCDIR)/part_2_sorting_and_order_statistics/6_heapsort/2_maintaining_the_heap_property/maintaining_the_heap_property.c
MAINTAINING_HEAP_PROPERTY_MAIN = $(SRCDIR)/part_2_sorting_and_order_statistics/6_heapsort/2_maintaining_the_heap_property/main.c

HEAPSORT_SRC = $(SRCDIR)/part_2_sorting_and_order_statistics/6_heapsort/4_the_heapsort_algorithm/the_heapsort_algorithm.c
HEAPSORT_MAIN = $(SRCDIR)/part_2_sorting_and_order_statistics/6_heapsort/4_the_heapsort_algorithm/main.c

PRIORITY_QUEUES_SRC = $(SRCDIR)/part_2_sorting_and_order_statistics/6_heapsort/5_priority_queues/priority_queues.c
PRIORITY_QUEUES_MAIN = $(SRCDIR)/part_2_sorting_and_order_statistics/6_heapsort/5_priority_queues/main.c

CHAPTER_6_PROBLEMS_SRC = $(SRCDIR)/part_2_sorting_and_order_statistics/6_heapsort/problems.c

# Chapter 7
QUICKSORT_SRC = $(SRCDIR)/part_2_sorting_and_order_statistics/7_quicksort/1_quicksort/quicksort.c
QUICKSORT_MAIN = $(SRCDIR)/part_2_sorting_and_order_statistics/7_quicksort/1_quicksort/main.c

CHAPTER_7_PROBLEMS_SRC = $(SRCDIR)/part_2_sorting_and_order_statistics/7_quicksort/problems.c

# Chapter 8
COUNTING_SORT_SRC = $(SRCDIR)/part_2_sorting_and_order_statistics/8_sorting_in_linear_time/2_counting_sort/counting_sort.c
COUNTING_SORT_MAIN = $(SRCDIR)/part_2_sorting_and_order_statistics/8_sorting_in_linear_time/2_counting_sort/main.c

RADIX_SORT_SRC = $(SRCDIR)/part_2_sorting_and_order_statistics/8_sorting_in_linear_time/3_radix_sort/radix_sort.c
RADIX_SORT_MAIN = $(SRCDIR)/part_2_sorting_and_order_statistics/8_sorting_in_linear_time/3_radix_sort/main.c

BUCKET_SORT_SRC = $(SRCDIR)/part_2_sorting_and_order_statistics/8_sorting_in_linear_time/4_bucket_sort/bucket_sort.c
BUCKET_SORT_MAIN = $(SRCDIR)/part_2_sorting_and_order_statistics/8_sorting_in_linear_time/4_bucket_sort/main.c

CHAPTER_8_PROBLEMS_SRC = $(SRCDIR)/part_2_sorting_and_order_statistics/8_sorting_in_linear_time/problems.c

# Chapter 9
MIN_MAX_SRC = $(SRCDIR)/part_2_sorting_and_order_statistics/9_medians_and_order_statistics/1_minimum_and_maximum/minimum_and_maximum.c
MIN_MAX_MAIN = $(SRCDIR)/part_2_sorting_and_order_statistics/9_medians_and_order_statistics/1_minimum_and_maximum/main.c

RANDOMIZED_SELECT_SRC = $(SRCDIR)/part_2_sorting_and_order_statistics/9_medians_and_order_statistics/2_selection_in_expected_linear_time/selection_in_expected_linear_time.c
RANDOMIZED_SELECT_MAIN = $(SRCDIR)/part_2_sorting_and_order_statistics/9_medians_and_order_statistics/2_selection_in_expected_linear_time/main.c

WORST_CASE_SELECT_SRC = $(SRCDIR)/part_2_sorting_and_order_statistics/9_medians_and_order_statistics/3_selection_in_worst-case_linear_time/selection_in_worst-case_linear_time.c
WORST_CASE_SELECT_MAIN = $(SRCDIR)/part_2_sorting_and_order_statistics/9_medians_and_order_statistics/3_selection_in_worst-case_linear_time/main.c

CHAPTER_9_PROBLEMS_SRC = $(SRCDIR)/part_2_sorting_and_order_statistics/9_medians_and_order_statistics/problems.c

# ============================================================================
# PART 3: DATA STRUCTURES
# ============================================================================

# Chapter 10
STACKS_QUEUES_SRC = $(SRCDIR)/part_3_data_structures/10_elementary_data_structures/1_stacks_and_queues/stacks_and_queues.c
STACKS_QUEUES_MAIN = $(SRCDIR)/part_3_data_structures/10_elementary_data_structures/1_stacks_and_queues/main.c

LINKED_LISTS_SRC = $(SRCDIR)/part_3_data_structures/10_elementary_data_structures/2_linked_lists/linked_lists.c
LINKED_LISTS_MAIN = $(SRCDIR)/part_3_data_structures/10_elementary_data_structures/2_linked_lists/main.c

ROOTED_TREES_SRC = $(SRCDIR)/part_3_data_structures/10_elementary_data_structures/4_representing_rooted_trees/representing_rooted_trees.c
ROOTED_TREES_MAIN = $(SRCDIR)/part_3_data_structures/10_elementary_data_structures/4_representing_rooted_trees/main.c

CHAPTER_10_PROBLEMS_SRC = $(SRCDIR)/part_3_data_structures/10_elementary_data_structures/problems.c

# Chapter 11
DIRECT_ACCESS_TABLES_SRC = $(SRCDIR)/part_3_data_structures/11_hash_tables/1_direct-address_tables/direct_address_tables.c
DIRECT_ACCESS_TABLES_MAIN = $(SRCDIR)/part_3_data_structures/11_hash_tables/1_direct-address_tables/main.c

HASH_TABLES_SRC = $(SRCDIR)/part_3_data_structures/11_hash_tables/2_hash_tables/hash_tables.c
HASH_TABLES_MAIN = $(SRCDIR)/part_3_data_structures/11_hash_tables/2_hash_tables/main.c

HASH_FUNCTIONS_SRC = $(SRCDIR)/part_3_data_structures/11_hash_tables/3_hash_functions/hash_functions.c
HASH_FUNCTIONS_MAIN = $(SRCDIR)/part_3_data_structures/11_hash_tables/3_hash_functions/main.c

OPEN_ADDRESSING_SRC = $(SRCDIR)/part_3_data_structures/11_hash_tables/4_open_addressing/open_addressing.c
OPEN_ADDRESSING_MAIN = $(SRCDIR)/part_3_data_structures/11_hash_tables/4_open_addressing/main.c

PERFECT_HASHING_SRC = $(SRCDIR)/part_3_data_structures/11_hash_tables/5_perfect_hashing/perfect_hashing.c
PERFECT_HASHING_MAIN = $(SRCDIR)/part_3_data_structures/11_hash_tables/5_perfect_hashing/main.c

# Chapter 12
WHAT_IS_BST_SRC = $(SRCDIR)/part_3_data_structures/12_binary_search_trees/1_what_is_a_binary_search_tree/what_is_a_binary_search_tree.c
WHAT_IS_BST_MAIN = $(SRCDIR)/part_3_data_structures/12_binary_search_trees/1_what_is_a_binary_search_tree/main.c

BST_QUERYING_SRC = $(SRCDIR)/part_3_data_structures/12_binary_search_trees/2_querying_a_binary_search_tree/querying_a_binary_search_tree.c
BST_QUERYING_MAIN = $(SRCDIR)/part_3_data_structures/12_binary_search_trees/2_querying_a_binary_search_tree/main.c

BST_INSERTION_DELETION_SRC = $(SRCDIR)/part_3_data_structures/12_binary_search_trees/3_insertion_and_deletion/insertion_and_deletion.c
BST_INSERTION_DELETION_MAIN = $(SRCDIR)/part_3_data_structures/12_binary_search_trees/3_insertion_and_deletion/main.c

# Chapter 13
RED_BLACK_TREES_SRC = $(SRCDIR)/part_3_data_structures/13_red-black_trees/red-black_trees.c
RED_BLACK_TREES_MAIN = $(SRCDIR)/part_3_data_structures/13_red-black_trees/main.c

CHAPTER_13_PROBLEMS_SRC = $(SRCDIR)/part_3_data_structures/13_red-black_trees/problems.c

# ============================================================================
# PART 4: ADVANCED DESIGN AND ANALYSIS TECHNIQUES
# ============================================================================

# Chapter 14
ROD_CUTTING_SRC = $(SRCDIR)/part_4_advanced_design_and_analysis_techniques/14_dynamic_programming/1_rod_cutting/rod_cutting.c
ROD_CUTTING_MAIN = $(SRCDIR)/part_4_advanced_design_and_analysis_techniques/14_dynamic_programming/1_rod_cutting/main.c

MATRIX_CHAIN_MULT_SRC = $(SRCDIR)/part_4_advanced_design_and_analysis_techniques/14_dynamic_programming/2_matrix_chain_multiplication/matrix_chain_multiplication.c
MATRIX_CHAIN_MULT_MAIN = $(SRCDIR)/part_4_advanced_design_and_analysis_techniques/14_dynamic_programming/2_matrix_chain_multiplication/main.c

ELEMENTS_DP_SRC = $(SRCDIR)/part_4_advanced_design_and_analysis_techniques/14_dynamic_programming/3_elements_of_dynamic_programming/elements_of_dynamic_programming.c
ELEMENTS_DP_MAIN = $(SRCDIR)/part_4_advanced_design_and_analysis_techniques/14_dynamic_programming/3_elements_of_dynamic_programming/main.c

LCS_SRC = $(SRCDIR)/part_4_advanced_design_and_analysis_techniques/14_dynamic_programming/4_longest_common_subsequence/longest_common_subsequence.c
LCS_MAIN = $(SRCDIR)/part_4_advanced_design_and_analysis_techniques/14_dynamic_programming/4_longest_common_subsequence/main.c

OPTIMAL_BST_SRC = $(SRCDIR)/part_4_advanced_design_and_analysis_techniques/14_dynamic_programming/5_optimal_binary_search_trees/optimal_binary_search_trees.c
OPTIMAL_BST_MAIN = $(SRCDIR)/part_4_advanced_design_and_analysis_techniques/14_dynamic_programming/5_optimal_binary_search_trees/main.c

CHAPTER_14_PROBLEMS_SRC = $(SRCDIR)/part_4_advanced_design_and_analysis_techniques/14_dynamic_programming/problems.c

# Chapter 15
ACTIVITY_SELECTION_SRC = $(SRCDIR)/part_4_advanced_design_and_analysis_techniques/15_greedy_algorithms/1_activity_selection_problem/activity_selection_problem.c
ACTIVITY_SELECTION_MAIN = $(SRCDIR)/part_4_advanced_design_and_analysis_techniques/15_greedy_algorithms/1_activity_selection_problem/main.c

GREEDY_ELEMENTS_SRC = $(SRCDIR)/part_4_advanced_design_and_analysis_techniques/15_greedy_algorithms/2_elements_of_the_greedy_strategy/elements_of_the_greedy_strategy.c
GREEDY_ELEMENTS_MAIN = $(SRCDIR)/part_4_advanced_design_and_analysis_techniques/15_greedy_algorithms/2_elements_of_the_greedy_strategy/main.c

HUFFMAN_CODES_SRC = $(SRCDIR)/part_4_advanced_design_and_analysis_techniques/15_greedy_algorithms/3_huffman_codes/huffman_codes.c
HUFFMAN_CODES_MAIN = $(SRCDIR)/part_4_advanced_design_and_analysis_techniques/15_greedy_algorithms/3_huffman_codes/main.c

OFFLINE_CACHING_SRC = $(SRCDIR)/part_4_advanced_design_and_analysis_techniques/15_greedy_algorithms/4_off-line_caching/off-line_caching.c
OFFLINE_CACHING_MAIN = $(SRCDIR)/part_4_advanced_design_and_analysis_techniques/15_greedy_algorithms/4_off-line_caching/main.c

CHAPTER_15_PROBLEMS_SRC = $(SRCDIR)/part_4_advanced_design_and_analysis_techniques/15_greedy_algorithms/problems.c

# Chapter 16
AMORTIZED_ANALYSIS_SRC = $(SRCDIR)/part_4_advanced_design_and_analysis_techniques/16_amortized_analysis/amortized_analysis.c
AMORTIZED_ANALYSIS_MAIN = $(SRCDIR)/part_4_advanced_design_and_analysis_techniques/16_amortized_analysis/main.c

CHAPTER_16_PROBLEMS_SRC = $(SRCDIR)/part_4_advanced_design_and_analysis_techniques/16_amortized_analysis/problems.c

# ============================================================================
# PART 5: ADVANCED DATA STRUCTURES
# ============================================================================

# Chapter 17
DYNAMIC_ORDER_STATISTICS_SRC = $(SRCDIR)/part_5_advanced_data_structures/17_enriching_data_structures/1_dynamic_order_statistics/dynamic_order_statistics.c
DYNAMIC_ORDER_STATISTICS_MAIN = $(SRCDIR)/part_5_advanced_data_structures/17_enriching_data_structures/1_dynamic_order_statistics/main.c

HOW_TO_ENRICH_DATA_STRUCTURE_SRC = $(SRCDIR)/part_5_advanced_data_structures/17_enriching_data_structures/2_how_to_enrich_a_data_structure/how_to_enrich_a_data_structure.c
HOW_TO_ENRICH_DATA_STRUCTURE_MAIN = $(SRCDIR)/part_5_advanced_data_structures/17_enriching_data_structures/2_how_to_enrich_a_data_structure/main.c

INTERVAL_TREES_SRC = $(SRCDIR)/part_5_advanced_data_structures/17_enriching_data_structures/3_interval_trees/interval_trees.c
INTERVAL_TREES_MAIN = $(SRCDIR)/part_5_advanced_data_structures/17_enriching_data_structures/3_interval_trees/main.c

CHAPTER_17_PROBLEMS_SRC = $(SRCDIR)/part_5_advanced_data_structures/17_enriching_data_structures/problems.c

# Chapter 18
B_TREES_SRC = $(SRCDIR)/part_5_advanced_data_structures/18_b-trees/b-trees.c
B_TREES_MAIN = $(SRCDIR)/part_5_advanced_data_structures/18_b-trees/main.c

CHAPTER_18_PROBLEMS_SRC = $(SRCDIR)/part_5_advanced_data_structures/18_b-trees/problems.c

# Chapter 19
DISJOINT_SET_OPERATIONS_SRC = $(SRCDIR)/part_5_advanced_data_structures/19_data_structures_for_disjoint_sets/1_disjoint_set_operations/disjoint_set_operations.c
DISJOINT_SET_OPERATIONS_MAIN = $(SRCDIR)/part_5_advanced_data_structures/19_data_structures_for_disjoint_sets/1_disjoint_set_operations/main.c

LINKED_LIST_REPRESENTATION_SRC = $(SRCDIR)/part_5_advanced_data_structures/19_data_structures_for_disjoint_sets/2_linked-list_representation_of_disjoint_sets/linked-list_representation_of_disjoint_sets.c
LINKED_LIST_REPRESENTATION_MAIN = $(SRCDIR)/part_5_advanced_data_structures/19_data_structures_for_disjoint_sets/2_linked-list_representation_of_disjoint_sets/main.c

DISJOINT_SET_FORESTS_SRC = $(SRCDIR)/part_5_advanced_data_structures/19_data_structures_for_disjoint_sets/3_disjoint_set_forests/disjoint_set_forests.c
DISJOINT_SET_FORESTS_MAIN = $(SRCDIR)/part_5_advanced_data_structures/19_data_structures_for_disjoint_sets/3_disjoint_set_forests/main.c

CHAPTER_19_PROBLEMS_SRC = $(SRCDIR)/part_5_advanced_data_structures/19_data_structures_for_disjoint_sets/problems.c

# ============================================================================
# PART 6: GRAPH ALGORITHMS
# ============================================================================

# Chapter 20
REPRESENTATIONS_OF_GRAPHS_SRC = $(SRCDIR)/part_6_graph_algorithms/20_elementary_graph_algorithms/1_representations_of_graphs/representations_of_graphs.c
REPRESENTATIONS_OF_GRAPHS_MAIN = $(SRCDIR)/part_6_graph_algorithms/20_elementary_graph_algorithms/1_representations_of_graphs/main.c

BREADTH_FIRST_SEARCH_SRC = $(SRCDIR)/part_6_graph_algorithms/20_elementary_graph_algorithms/2_breadth-first_search/breadth-first_search.c
BREADTH_FIRST_SEARCH_MAIN = $(SRCDIR)/part_6_graph_algorithms/20_elementary_graph_algorithms/2_breadth-first_search/main.c

DEPTH_FIRST_SEARCH_SRC = $(SRCDIR)/part_6_graph_algorithms/20_elementary_graph_algorithms/3_depth-first_search/depth-first_search.c
DEPTH_FIRST_SEARCH_MAIN = $(SRCDIR)/part_6_graph_algorithms/20_elementary_graph_algorithms/3_depth-first_search/main.c

TOPOLOGICAL_SORT_SRC = $(SRCDIR)/part_6_graph_algorithms/20_elementary_graph_algorithms/4_topological_sort/topological_sort.c
TOPOLOGICAL_SORT_MAIN = $(SRCDIR)/part_6_graph_algorithms/20_elementary_graph_algorithms/4_topological_sort/main.c

STRONGLY_CONNECTED_COMPONENTS_SRC = $(SRCDIR)/part_6_graph_algorithms/20_elementary_graph_algorithms/5_strongly_connected_components/strongly_connected_components.c
STRONGLY_CONNECTED_COMPONENTS_MAIN = $(SRCDIR)/part_6_graph_algorithms/20_elementary_graph_algorithms/5_strongly_connected_components/main.c

CHAPTER_20_PROBLEMS_SRC = $(SRCDIR)/part_6_graph_algorithms/20_elementary_graph_algorithms/problems.c

# Chapter 21
GROWING_MST_SRC = $(SRCDIR)/part_6_graph_algorithms/21_minimum_spanning_trees/1_growing_a_minimum_spanning_tree/growing_a_minimum_spanning_tree.c
GROWING_MST_MAIN = $(SRCDIR)/part_6_graph_algorithms/21_minimum_spanning_trees/1_growing_a_minimum_spanning_tree/main.c

THE_ALGORITHMS_OF_KRUSKAL_AND_PRIM_SRC = $(SRCDIR)/part_6_graph_algorithms/21_minimum_spanning_trees/2_the_algorithms_of_kruskal_and_prim/the_algorithms_of_kruskal_and_prim.c
THE_ALGORITHMS_OF_KRUSKAL_AND_PRIM_MAIN = $(SRCDIR)/part_6_graph_algorithms/21_minimum_spanning_trees/2_the_algorithms_of_kruskal_and_prim/main.c

CHAPTER_21_PROBLEMS_SRC = $(SRCDIR)/part_6_graph_algorithms/21_minimum_spanning_trees/problems.c

# Chapter 22
BELLMAN_FORD_ALGORITHM_SRC = $(SRCDIR)/part_6_graph_algorithms/22_single-source_shortest_paths/1_the_bellman-ford_algorithm/the_bellman-ford_algorithm.c
BELLMAN_FORD_ALGORITHM_MAIN = $(SRCDIR)/part_6_graph_algorithms/22_single-source_shortest_paths/1_the_bellman-ford_algorithm/main.c

DAG_SHORTEST_PATHS_SRC = $(SRCDIR)/part_6_graph_algorithms/22_single-source_shortest_paths/2_single-source_shortest_paths_in_dags/single-source_shortest_paths_in_dags.c
DAG_SHORTEST_PATHS_MAIN = $(SRCDIR)/part_6_graph_algorithms/22_single-source_shortest_paths/2_single-source_shortest_paths_in_dags/main.c

DIJKSTRA_ALGORITHM_SRC = $(SRCDIR)/part_6_graph_algorithms/22_single-source_shortest_paths/3_dijkstras_algorithm/dijkstras_algorithm.c
DIJKSTRA_ALGORITHM_MAIN = $(SRCDIR)/part_6_graph_algorithms/22_single-source_shortest_paths/3_dijkstras_algorithm/main.c

DIFFERENCE_CONSTRAINTS_SRC = $(SRCDIR)/part_6_graph_algorithms/22_single-source_shortest_paths/4_difference_constraints_and_shortest_paths/difference_constraints_and_shortest_paths.c
DIFFERENCE_CONSTRAINTS_MAIN = $(SRCDIR)/part_6_graph_algorithms/22_single-source_shortest_paths/4_difference_constraints_and_shortest_paths/main.c

CHAPTER_22_PROBLEMS_SRC = $(SRCDIR)/part_6_graph_algorithms/22_single-source_shortest_paths/problems.c

# Chapter 23
SHORTEST_PATHS_MATRIX_MULT_SRC = $(SRCDIR)/part_6_graph_algorithms/23_all-pairs_shortest_paths/1_shortest_paths_and_matrix_multiplication/shortest_paths_and_matrix_multiplication.c
SHORTEST_PATHS_MATRIX_MULT_MAIN = $(SRCDIR)/part_6_graph_algorithms/23_all-pairs_shortest_paths/1_shortest_paths_and_matrix_multiplication/main.c

FLOYD_WARSHALL_ALGORITHM_SRC = $(SRCDIR)/part_6_graph_algorithms/23_all-pairs_shortest_paths/2_the_floyd-warshall_algorithm/the_floyd-warshall_algorithm.c
FLOYD_WARSHALL_ALGORITHM_MAIN = $(SRCDIR)/part_6_graph_algorithms/23_all-pairs_shortest_paths/2_the_floyd-warshall_algorithm/main.c

JOHNSONS_ALGORITHM_SRC = $(SRCDIR)/part_6_graph_algorithms/23_all-pairs_shortest_paths/3_johnsons_algorithm_for_sparse_graphs/johnsons_algorithm_for_sparse_graphs.c
JOHNSONS_ALGORITHM_MAIN = $(SRCDIR)/part_6_graph_algorithms/23_all-pairs_shortest_paths/3_johnsons_algorithm_for_sparse_graphs/main.c

CHAPTER_23_PROBLEMS_SRC = $(SRCDIR)/part_6_graph_algorithms/23_all-pairs_shortest_paths/problems.c

# Chapter 24
THE_FORD_FULKERSON_METHOD_SRC = $(SRCDIR)/part_6_graph_algorithms/24_maximum_flow/2_the_ford_fulkerson_method/the_ford_fulkerson_method.c
THE_FORD_FULKERSON_METHOD_MAIN = $(SRCDIR)/part_6_graph_algorithms/24_maximum_flow/2_the_ford_fulkerson_method/main.c

MAXIMUM_BIPARTITE_MATCHING_SRC = $(SRCDIR)/part_6_graph_algorithms/24_maximum_flow/3_maximum_bipartite_matching/maximum_bipartite_matching.c
MAXIMUM_BIPARTITE_MATCHING_MAIN = $(SRCDIR)/part_6_graph_algorithms/24_maximum_flow/3_maximum_bipartite_matching/main.c

CHAPTER_24_PROBLEMS_SRC = $(SRCDIR)/part_6_graph_algorithms/24_maximum_flow/problems.c

# Chapter 25
CHAPTER_25_PROBLEMS_SRC = \
	$(SRCDIR)/part_6_graph_algorithms/25_bipartite_matching/problems.c \
	$(SRCDIR)/part_6_graph_algorithms/25_bipartite_matching/1_maximum_bipartite_matching/maximum_bipartite_matching.c

# ============================================================================
# PART 7: SELECTED TOPICS
# ============================================================================

# Chapter 26
THE_BASICS_OF_FORK_JOIN_MAIN = src/part_7_selected_topics/26_multithreaded_algorithms/1_the_basics_of_fork-join_multithreading/main.c
THE_BASICS_OF_FORK_JOIN_SRC = src/part_7_selected_topics/26_multithreaded_algorithms/1_the_basics_of_fork-join_multithreading/the_basics_of_fork-join_multithreading.c

MULTITHREADED_MATRIX_MULTIPLICATION_MAIN = src/part_7_selected_topics/26_multithreaded_algorithms/2_multithreaded_matrix_multiplication/main.c
MULTITHREADED_MATRIX_MULTIPLICATION_SRC = src/part_7_selected_topics/26_multithreaded_algorithms/2_multithreaded_matrix_multiplication/multithreaded_matrix_multiplication.c

MULTITHREADED_MERGE_SORT_MAIN = src/part_7_selected_topics/26_multithreaded_algorithms/3_multithreaded_merge_sort/main.c
MULTITHREADED_MERGE_SORT_SRC = src/part_7_selected_topics/26_multithreaded_algorithms/3_multithreaded_merge_sort/multithreaded_merge_sort.c

CHAPTER_26_PROBLEMS_SRC = $(SRCDIR)/part_7_selected_topics/26_multithreaded_algorithms/problems.c

# Chapter 27
WAITING_FOR_AN_ELEVATOR_MAIN = src/part_7_selected_topics/27_online_algorithms/1_waiting_for_an_elevator/main.c
WAITING_FOR_AN_ELEVATOR_SRC = src/part_7_selected_topics/27_online_algorithms/1_waiting_for_an_elevator/1_waiting_for_an_elevator.c

MAINTAINING_A_SEARCH_LIST_MAIN = src/part_7_selected_topics/27_online_algorithms/2_maintaining_a_search_list/main.c
MAINTAINING_A_SEARCH_LIST_SRC = src/part_7_selected_topics/27_online_algorithms/2_maintaining_a_search_list/maintaining_a_search_list.c

ONLINE_CACHE_MANAGEMENT_MAIN = src/part_7_selected_topics/27_online_algorithms/3_online_cache_management/main.c
ONLINE_CACHE_MANAGEMENT_SRC = src/part_7_selected_topics/27_online_algorithms/3_online_cache_management/online_cache_management.c

CHAPTER_27_PROBLEMS_SRC = $(SRCDIR)/part_7_selected_topics/27_online_algorithms/problems.c

# Chapter 28
SOLVING_SYSTEMS_OF_LINEAR_EQUATIONS_MAIN = src/part_7_selected_topics/28_matrix_operations/1_solving_systems_of_linear_equations/main.c
SOLVING_SYSTEMS_OF_LINEAR_EQUATIONS_SRC = src/part_7_selected_topics/28_matrix_operations/1_solving_systems_of_linear_equations/solving_systems_of_linear_equations.c

INVERTING_MATRICES_MAIN = src/part_7_selected_topics/28_matrix_operations/2_inverting_matrices/main.c
INVERTING_MATRICES_SRC = src/part_7_selected_topics/28_matrix_operations/2_inverting_matrices/inverting_matrices.c

POLYNOMIAL_LEAST_SQUARES_MAIN = src/part_7_selected_topics/28_matrix_operations/3_symmetric_positive-definite_matrices_and_least-squares_approximation/main.c
POLYNOMIAL_LEAST_SQUARES_SRC = src/part_7_selected_topics/28_matrix_operations/3_symmetric_positive-definite_matrices_and_least-squares_approximation/symmetric_positive-definite_matrices_and_least-squares_approximation.c

CHAPTER_28_PROBLEMS_MAIN = src/part_7_selected_topics/28_matrix_operations/problems.c
CHAPTER_28_PROBLEMS_SRC = src/part_7_selected_topics/28_matrix_operations/problems.c

# Chapter 29

# Chapter 30
REPRESENTING_POLYNOMIALS_SRC = $(SRCDIR)/part_7_selected_topics/30_polynomials_and_the_fft/1_representing_polynomials/representing_polynomials.c
REPRESENTING_POLYNOMIALS_MAIN = $(SRCDIR)/part_7_selected_topics/30_polynomials_and_the_fft/1_representing_polynomials/main.c

THE_DFT_AND_FFT_SRC = $(SRCDIR)/part_7_selected_topics/30_polynomials_and_the_fft/2_the_dft_and_fft/the_dft_and_fft.c
THE_DFT_AND_FFT_MAIN = $(SRCDIR)/part_7_selected_topics/30_polynomials_and_the_fft/2_the_dft_and_fft/main.c

EFFICIENT_FFT_IMPLEMENTATION_SRC = $(SRCDIR)/part_7_selected_topics/30_polynomials_and_the_fft/3_efficient_fft_implementations/efficient_fft_implementations.c
EFFICIENT_FFT_IMPLEMENTATION_MAIN = $(SRCDIR)/part_7_selected_topics/30_polynomials_and_the_fft/3_efficient_fft_implementations/main.c

# ============================================================================
# PHONY TARGETS
# ============================================================================

.PHONY: all clean help \
        demo demo-debug run run-debug \
        complexity-table run-complexity-table \
        insertion-sort run-insertion-sort \
        analyzing-algorithms run-analyzing-algorithms \
        designing-algorithms run-designing-algorithms \
        chapter-2-problems run-chapter-2-problems \
        square-matrix-mult run-square-matrix-mult \
        strassen run-strassen \
        hire-assistant run-hire-assistant \
        chapter-5-problems run-chapter-5-problems \
        maintaining-heap-property run-maintaining-heap-property \
        heapsort run-heapsort \
        priority-queues run-priority-queues \
        chapter-6-problems run-chapter-6-problems \
        quicksort run-quicksort \
        chapter-7-problems run-chapter-7-problems \
        counting-sort run-counting-sort \
        radix-sort run-radix-sort \
        bucket-sort run-bucket-sort \
        chapter-8-problems run-chapter-8-problems \
        min-max run-min-max \
        randomized-select run-randomized-select \
        worst-case-select run-worst-case-select \
        chapter-9-problems run-chapter-9-problems \
        stacks-queues run-stacks-queues \
        linked-lists run-linked-lists \
        rooted-trees run-rooted-trees \
        chapter-10-problems run-chapter-10-problems \
        direct-access-tables run-direct-access-tables \
        hash-tables run-hash-tables \
        hash-functions run-hash-functions \
        open-addressing run-open-addressing \
        perfect-hashing run-perfect-hashing \
        bst-what-is run-bst-what-is \
        bst-querying run-bst-querying \
        bst-insertion-deletion run-bst-insertion-deletion \
        red-black-trees run-red-black-trees \
        chapter-13-problems run-chapter-13-problems \
        rod-cutting run-rod-cutting \
		matrix-chain-mult run-matrix-chain-mult \
		elements-dp run-elements-dp \
		lcs run-lcs \
		optimal-bst run-optimal-bst \
		dp-problems run-dp-problems \
		activity-selection run-activity-selection \
		greedy-elements run-greedy-elements \
		huffman-codes run-huffman-codes \
		offline-caching run-offline-caching \
		chapter-15-problems run-chapter-15-problems \
		amortized-analysis run-amortized-analysis \
		chapter-16-problems run-chapter-16-problems \
		dynamic-order-statistics run-dynamic-order-statistics \
		how-to-enrich-data-structure run-how-to-enrich-data-structure \
		interval-trees run-interval-trees \
		chapter-17-problems run-chapter-17-problems \
        b-trees run-b-trees \
		chapter-18-problems run-chapter-18-problems \
		disjoint-set-operations run-disjoint-set-operations \
		linked-list-representation run-linked-list-representation \
		disjoint-set-forests run-disjoint-set-forests \
		chapter-19-problems run-chapter-19-problems \
		representations-of-graphs run-representations-of-graphs \
		breadth-first-search run-breadth-first-search \
		depth-first-search run-depth-first-search \
		topological-sort run-topological-sort \
		strongly-connected-components run-strongly-connected-components \
		chapter-20-problems run-chapter-20-problems \
		growing-mst run-growing-mst \
		kruskal-prim run-kruskal-prim \
		chapter-21-problems run-chapter-21-problems \
		bellman-ford run-bellman-ford \
		dag-shortest-paths run-dag-shortest-paths \
		dijkstra run-dijkstra \
		difference-constraints run-difference-constraints \
		chapter-22-problems run-chapter-22-problems \
		shortest-paths-matrix-mult run-shortest-paths-matrix-mult \
		floyd-warshall run-floyd-warshall \
		johnsons-algorithm run-johnsons-algorithm \
		chapter-23-problems run-chapter-23-problems \
		ford-fulkerson-method run-ford-fulkerson-method \
		maximum-bipartite-matching run-maximum-bipartite-matching \
		chapter-24-problems run-chapter-24-problems \
		maximum-bipartite-matching-2 run-maximum-bipartite-matching-2 \
		stable-marriage run-stable-marriage \
		hungarian-algorithm run-hungarian-algorithm \
		chapter-25-problems run-chapter-25-problems \
		the-basics-of-fork-join run-the-basics-of-fork-join \
		multithreaded-matrix-multiplication run-multithreaded-matrix-multiplication \
		multithreaded-merge-sort run-multithreaded-merge-sort \
		chapter-26-problems run-chapter-26-problems \
		waiting-for-an-elevator run-waiting-for-an-elevator \
		maintaining-a-search-list run-maintaining-a-search-list \
		online-cache-management run-online-cache-management \
		chapter-27-problems run-chapter-27-problems \
		solving-systems-of-linear-equations run-solving-systems-of-linear-equations \
		inverting-matrices run-inverting-matrices \
		polynomial-least-squares run-polynomial-least-squares \
		chapter-28-problems run-chapter-28-problems \
		representing-polynomials run-representing-polynomials \
		the-dft-and-fft run-the-dft-and-fft\
		efficient_fft_implementations run_efficient_fft_implementations \

# ============================================================================
# DEFAULT TARGETS
# ============================================================================

all: demo

$(BINDIR):
	mkdir -p $(BINDIR)

# ============================================================================
# MAIN DEMO TARGETS
# ============================================================================

demo: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(MAIN_SRC) -o $(BINDIR)/demo

demo-debug: $(BINDIR)
	$(CC) -DDEBUG $(CFLAGS) $(COMMON_SRC) $(MAIN_SRC) -o $(BINDIR)/demo_debug

run: demo
	$(BINDIR)/demo

run-debug: demo-debug
	$(BINDIR)/demo_debug

# ============================================================================
# PART 1: FOUNDATIONS
# ============================================================================
	
# Chapter 1
complexity-table: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(COMPLEXITY_TABLE_SRC) $(COMPLEXITY_TABLE_MAIN) -o $(BINDIR)/complexity_table

run-complexity-table: complexity-table
	$(BINDIR)/complexity_table

# Chapter 2
insertion-sort: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_1_COMMONS_SRC) $(INSERTION_SORT_SRC) $(INSERTION_SORT_MAIN) -o $(BINDIR)/insertion_sort

run-insertion-sort: insertion-sort
	$(BINDIR)/insertion_sort

analyzing-algorithms: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_1_COMMONS_SRC) $(ANALYZING_ALGORITHMS_SRC) $(ANALYZING_ALGORITHMS_MAIN) -o $(BINDIR)/analyzing_algorithms

run-analyzing-algorithms: analyzing-algorithms
	$(BINDIR)/analyzing_algorithms

designing-algorithms: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_1_COMMONS_SRC) $(DESIGNING_ALGORITHMS_SRC) $(DESIGNING_ALGORITHMS_MAIN) -o $(BINDIR)/designing_algorithms

run-designing-algorithms: designing-algorithms
	$(BINDIR)/designing_algorithms

chapter-2-problems: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_1_COMMONS_SRC) $(CHAPTER_2_PROBLEMS_SRC) -o $(BINDIR)/chapter_2_problems

run-chapter-2-problems: chapter-2-problems
	$(BINDIR)/chapter_2_problems

# Chapter 4
square-matrix-mult: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_1_COMMONS_SRC) $(SQUARE_MATRIX_MULT_SRC) $(SQUARE_MATRIX_MULT_MAIN) -o $(BINDIR)/square_matrix_mult

run-square-matrix-mult: square-matrix-mult
	$(BINDIR)/square_matrix_mult

strassen: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_1_COMMONS_SRC) $(STRASSEN_SRC) $(STRASSEN_MAIN) -o $(BINDIR)/strassen

run-strassen: strassen
	$(BINDIR)/strassen

# Chapter 5
hire-assistant: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_1_COMMONS_SRC) $(HIRE_ASSISTANT_SRC) $(HIRE_ASSISTANT_MAIN) -o $(BINDIR)/hire_assistant

run-hire-assistant: hire-assistant
	$(BINDIR)/hire_assistant

chapter-5-problems: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_1_COMMONS_SRC) $(CHAPTER_5_PROBLEMS_SRC) -o $(BINDIR)/chapter_5_problems

run-chapter-5-problems: chapter-5-problems
	$(BINDIR)/chapter_5_problems

# ============================================================================
# PART 2: SORTING AND ORDER STATISTICS
# ============================================================================

# Chapter 6
maintaining-heap-property: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_2_COMMONS_SRC) $(MAINTAINING_HEAP_PROPERTY_SRC) $(MAINTAINING_HEAP_PROPERTY_MAIN) -o $(BINDIR)/maintaining_heap_property

run-maintaining-heap-property: maintaining-heap-property
	$(BINDIR)/maintaining_heap_property

heapsort: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_2_COMMONS_SRC) $(MAINTAINING_HEAP_PROPERTY_SRC) $(HEAPSORT_SRC) $(HEAPSORT_MAIN) -o $(BINDIR)/heapsort

run-heapsort: heapsort
	$(BINDIR)/heapsort

priority-queues: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_2_COMMONS_SRC) $(MAINTAINING_HEAP_PROPERTY_SRC) $(HEAPSORT_SRC) $(PRIORITY_QUEUES_SRC) $(PRIORITY_QUEUES_MAIN) -o $(BINDIR)/priority_queues

run-priority-queues: priority-queues
	$(BINDIR)/priority_queues

chapter-6-problems: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_2_COMMONS_SRC) $(MAINTAINING_HEAP_PROPERTY_SRC) $(PRIORITY_QUEUES_SRC) $(CHAPTER_6_PROBLEMS_SRC) -o $(BINDIR)/chapter_6_problems

run-chapter-6-problems: chapter-6-problems
	$(BINDIR)/chapter_6_problems

# Chapter 7
quicksort: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_2_COMMONS_SRC) $(QUICKSORT_SRC) $(QUICKSORT_MAIN) -o $(BINDIR)/quicksort

run-quicksort: quicksort
	$(BINDIR)/quicksort

chapter-7-problems: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_2_COMMONS_SRC) $(QUICKSORT_SRC) $(CHAPTER_7_PROBLEMS_SRC) -o $(BINDIR)/chapter_7_problems

run-chapter-7-problems: chapter-7-problems
	$(BINDIR)/chapter_7_problems

# Chapter 8
counting-sort: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_2_COMMONS_SRC) $(COUNTING_SORT_SRC) $(COUNTING_SORT_MAIN) -o $(BINDIR)/counting_sort

run-counting-sort: counting-sort
	$(BINDIR)/counting_sort

radix-sort: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_2_COMMONS_SRC) $(COUNTING_SORT_SRC) $(RADIX_SORT_SRC) $(RADIX_SORT_MAIN) -o $(BINDIR)/radix_sort

run-radix-sort: radix-sort
	$(BINDIR)/radix_sort

bucket-sort: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_2_COMMONS_SRC) $(BUCKET_SORT_SRC) $(BUCKET_SORT_MAIN) -o $(BINDIR)/bucket_sort

run-bucket-sort: bucket-sort
	$(BINDIR)/bucket_sort

chapter-8-problems: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_2_COMMONS_SRC) $(COUNTING_SORT_SRC) $(CHAPTER_8_PROBLEMS_SRC) -o $(BINDIR)/chapter_8_problems

run-chapter-8-problems: chapter-8-problems
	$(BINDIR)/chapter_8_problems

# Chapter 9
min-max: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_2_COMMONS_SRC) $(MIN_MAX_SRC) $(MIN_MAX_MAIN) -o $(BINDIR)/min_max

run-min-max: min-max
	$(BINDIR)/min_max

randomized-select: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_2_COMMONS_SRC) $(RANDOMIZED_SELECT_SRC) $(RANDOMIZED_SELECT_MAIN) -o $(BINDIR)/randomized_select

run-randomized-select: randomized-select
	$(BINDIR)/randomized_select

worst-case-select: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_2_COMMONS_SRC) $(WORST_CASE_SELECT_SRC) $(WORST_CASE_SELECT_MAIN) -o $(BINDIR)/worst_case_select

run-worst-case-select: worst-case-select
	$(BINDIR)/worst_case_select

chapter-9-problems: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_2_COMMONS_SRC) $(RANDOMIZED_SELECT_SRC) $(CHAPTER_9_PROBLEMS_SRC) -o $(BINDIR)/chapter_9_problems

run-chapter-9-problems: chapter-9-problems
	$(BINDIR)/chapter_9_problems

# ============================================================================
# PART 3: DATA STRUCTURES
# ============================================================================

# Chapter 10
stacks-queues: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_3_COMMONS_SRC) $(STACKS_QUEUES_SRC) $(STACKS_QUEUES_MAIN) -o $(BINDIR)/stacks_queues

run-stacks-queues: stacks-queues
	$(BINDIR)/stacks_queues

linked-lists: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_3_COMMONS_SRC) $(LINKED_LISTS_SRC) $(LINKED_LISTS_MAIN) -o $(BINDIR)/linked_lists

run-linked-lists: linked-lists
	$(BINDIR)/linked_lists

rooted-trees: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_3_COMMONS_SRC) $(ROOTED_TREES_SRC) $(ROOTED_TREES_MAIN) -o $(BINDIR)/rooted_trees

run-rooted-trees: rooted-trees
	$(BINDIR)/rooted_trees

chapter-10-problems: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_3_COMMONS_SRC) $(CHAPTER_10_PROBLEMS_SRC) -o $(BINDIR)/chapter_10_problems

run-chapter-10-problems: chapter-10-problems
	$(BINDIR)/chapter_10_problems

# Chapter 11
direct-access-tables: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_3_COMMONS_SRC) $(DIRECT_ACCESS_TABLES_SRC) $(DIRECT_ACCESS_TABLES_MAIN) -o $(BINDIR)/direct_access_tables

run-direct-access-tables: direct-access-tables
	$(BINDIR)/direct_access_tables

hash-tables: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_3_COMMONS_SRC) $(HASH_TABLES_SRC) $(HASH_TABLES_MAIN) -o $(BINDIR)/hash_tables

run-hash-tables: hash-tables
	$(BINDIR)/hash_tables

hash-functions: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_3_COMMONS_SRC) $(HASH_FUNCTIONS_SRC) $(HASH_FUNCTIONS_MAIN) -o $(BINDIR)/hash_functions

run-hash-functions: hash-functions
	$(BINDIR)/hash_functions

open-addressing: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_3_COMMONS_SRC) $(HASH_FUNCTIONS_SRC) $(OPEN_ADDRESSING_SRC) $(OPEN_ADDRESSING_MAIN) -o $(BINDIR)/open_addressing

run-open-addressing: open-addressing
	$(BINDIR)/open_addressing

perfect-hashing: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_3_COMMONS_SRC) $(HASH_FUNCTIONS_SRC) $(PERFECT_HASHING_SRC) $(PERFECT_HASHING_MAIN) -o $(BINDIR)/perfect_hashing

run-perfect-hashing: perfect-hashing
	$(BINDIR)/perfect_hashing

what-is-bst: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_3_COMMONS_SRC) $(WHAT_IS_BST_SRC) $(WHAT_IS_BST_MAIN) -o $(BINDIR)/what-is-bst

run-bst-what-is: what-is-bst
	$(BINDIR)/what-is-bst

bst-querying: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_3_COMMONS_SRC) $(BST_QUERYING_SRC) $(BST_QUERYING_MAIN) -o $(BINDIR)/bst_querying

run-bst-querying: bst-querying
	$(BINDIR)/bst_querying

bst-insertion-deletion: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_3_COMMONS_SRC) $(BST_QUERYING_SRC) $(BST_INSERTION_DELETION_SRC) $(BST_INSERTION_DELETION_MAIN) -o $(BINDIR)/bst_insertion_deletion

run-bst-insertion-deletion: bst-insertion-deletion
	$(BINDIR)/bst_insertion_deletion

red-black-trees: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_3_COMMONS_SRC) $(RED_BLACK_TREES_SRC) $(RED_BLACK_TREES_MAIN) -o $(BINDIR)/red-black_trees

run-red-black-trees: red-black-trees
	$(BINDIR)/red-black_trees

chapter-13-problems: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_3_COMMONS_SRC) $(CHAPTER_13_PROBLEMS_SRC) -o $(BINDIR)/chapter_13_problems

run-chapter-13-problems: chapter-13-problems
	$(BINDIR)/chapter_13_problems

# Chapter 14

rod-cutting: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_4_COMMONS_SRC) $(ROD_CUTTING_SRC) $(ROD_CUTTING_MAIN) -o $(BINDIR)/rod_cutting

run-rod-cutting: rod-cutting
	$(BINDIR)/rod_cutting

matrix-chain-mult: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_4_COMMONS_SRC) $(MATRIX_CHAIN_MULT_SRC) $(MATRIX_CHAIN_MULT_MAIN) -o $(BINDIR)/matrix_chain_mult

run-matrix-chain-mult: matrix-chain-mult
	$(BINDIR)/matrix_chain_mult

elements-dp: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_4_COMMONS_SRC) $(ELEMENTS_DP_SRC) $(ELEMENTS_DP_MAIN) -o $(BINDIR)/elements_dp

run-elements-dp: elements-dp
	$(BINDIR)/elements_dp

lcs: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_4_COMMONS_SRC) $(LCS_SRC) $(LCS_MAIN) -o $(BINDIR)/lcs

run-lcs: lcs
	$(BINDIR)/lcs

optimal-bst: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_3_COMMONS_SRC) $(PART_4_COMMONS_SRC) $(BST_QUERYING_SRC) $(OPTIMAL_BST_SRC) $(OPTIMAL_BST_MAIN) -o $(BINDIR)/optimal_bst

run-optimal-bst: optimal-bst
	$(BINDIR)/optimal_bst

chapter-14-problems: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_4_COMMONS_SRC) $(CHAPTER_14_PROBLEMS_SRC) -o $(BINDIR)/chapter_14_problems

run-chapter-14-problems: chapter-14-problems
	$(BINDIR)/chapter_14_problems

# Chapter 15
activity-selection: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_4_COMMONS_SRC) $(ACTIVITY_SELECTION_SRC) $(ACTIVITY_SELECTION_MAIN) -o $(BINDIR)/activity_selection

run-activity-selection: activity-selection
	$(BINDIR)/activity_selection

greedy-elements: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_4_COMMONS_SRC) $(GREEDY_ELEMENTS_SRC) $(GREEDY_ELEMENTS_MAIN) -o $(BINDIR)/greedy_elements

run-greedy-elements: greedy-elements
	$(BINDIR)/greedy_elements

huffman-codes: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_4_COMMONS_SRC) $(HUFFMAN_CODES_SRC) $(HUFFMAN_CODES_MAIN) -o $(BINDIR)/huffman_codes

run-huffman-codes: huffman-codes
	$(BINDIR)/huffman_codes

offline-caching: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_4_COMMONS_SRC) $(OFFLINE_CACHING_SRC) $(OFFLINE_CACHING_MAIN) -o $(BINDIR)/offline_caching

run-offline-caching: offline-caching
	$(BINDIR)/offline_caching

chapter-15-problems: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_4_COMMONS_SRC) $(CHAPTER_15_PROBLEMS_SRC) -o $(BINDIR)/chapter_15_problems

run-chapter-15-problems: chapter-15-problems
	$(BINDIR)/chapter_15_problems

# Chapter 16
amortized-analysis: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_4_COMMONS_SRC) $(AMORTIZED_ANALYSIS_SRC) $(AMORTIZED_ANALYSIS_MAIN) -o $(BINDIR)/amortized_analysis

run-amortized-analysis: amortized-analysis
	$(BINDIR)/amortized_analysis

chapter-16-problems: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_4_COMMONS_SRC) $(CHAPTER_16_PROBLEMS_SRC) -o $(BINDIR)/chapter_16_problems

run-chapter-16-problems: chapter-16-problems
	$(BINDIR)/chapter_16_problems

# Chapter 17
dynamic-order-statistics: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_3_COMMONS_SRC) $(RED_BLACK_TREES_SRC) $(DYNAMIC_ORDER_STATISTICS_SRC) $(DYNAMIC_ORDER_STATISTICS_MAIN) -o $(BINDIR)/dynamic_order_statistics

run-dynamic-order-statistics: dynamic-order-statistics
	$(BINDIR)/dynamic_order_statistics

how-to-enrich-data-structure: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_3_COMMONS_SRC) $(RED_BLACK_TREES_SRC) $(HOW_TO_ENRICH_DATA_STRUCTURE_SRC) $(HOW_TO_ENRICH_DATA_STRUCTURE_MAIN) -o $(BINDIR)/how_to_enrich_data_structure

run-how-to-enrich-data-structure: how-to-enrich-data-structure
	$(BINDIR)/how_to_enrich_data_structure

interval-trees: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_3_COMMONS_SRC) $(RED_BLACK_TREES_SRC) $(INTERVAL_TREES_SRC) $(INTERVAL_TREES_MAIN) -o $(BINDIR)/interval_trees

run-interval-trees: interval-trees
	$(BINDIR)/interval_trees

chapter-17-problems: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_3_COMMONS_SRC) $(PART_5_COMMONS_SRC) $(RED_BLACK_TREES_SRC) $(CHAPTER_17_PROBLEMS_SRC) -o $(BINDIR)/chapter_17_problems

run-chapter-17-problems: chapter-17-problems
	$(BINDIR)/chapter_17_problems

# Chapter 18
b-trees: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_5_COMMONS_SRC) $(B_TREES_SRC) $(B_TREES_MAIN) -o $(BINDIR)/b_trees

run-b-trees: b-trees
	$(BINDIR)/b_trees

chapter-18-problems: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_5_COMMONS_SRC) $(B_TREES_SRC) $(CHAPTER_18_PROBLEMS_SRC) -o $(BINDIR)/chapter_18_problems

run-chapter-18-problems: chapter-18-problems
	$(BINDIR)/chapter_18_problems

# Chapter 19
disjoint-set-operations: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_5_COMMONS_SRC) $(DISJOINT_SET_OPERATIONS_SRC) $(DISJOINT_SET_OPERATIONS_MAIN) -o $(BINDIR)/disjoint_set_operations

run-disjoint-set-operations: disjoint-set-operations
	$(BINDIR)/disjoint_set_operations

linked-list-representation: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_5_COMMONS_SRC) $(LINKED_LIST_REPRESENTATION_SRC) $(LINKED_LIST_REPRESENTATION_MAIN) -o $(BINDIR)/linked_list_representation

run-linked-list-representation: linked-list-representation
	$(BINDIR)/linked_list_representation

disjoint-set-forests: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_5_COMMONS_SRC) $(DISJOINT_SET_FORESTS_SRC) $(DISJOINT_SET_FORESTS_MAIN) -o $(BINDIR)/disjoint_set_forests

run-disjoint-set-forests: disjoint-set-forests
	$(BINDIR)/disjoint_set_forests

chapter-19-problems: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_5_COMMONS_SRC) $(CHAPTER_19_PROBLEMS_SRC) -o $(BINDIR)/chapter_19_problems

run-chapter-19-problems: chapter-19-problems
	$(BINDIR)/chapter_19_problems

# Chapter 20
representations-of-graphs: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_1_COMMONS_SRC) $(PART_6_COMMONS_SRC) $(STRASSEN_SRC) $(REPRESENTATIONS_OF_GRAPHS_SRC) $(REPRESENTATIONS_OF_GRAPHS_MAIN) -o $(BINDIR)/representations_of_graphs

run-representations-of-graphs: representations-of-graphs
	$(BINDIR)/representations_of_graphs

breadth-first-search: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_1_COMMONS_SRC) $(PART_6_COMMONS_SRC) $(STRASSEN_SRC) $(BREADTH_FIRST_SEARCH_SRC) $(BREADTH_FIRST_SEARCH_MAIN) -o $(BINDIR)/breadth_first_search

run-breadth-first-search: breadth-first-search	

depth-first-search: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_1_COMMONS_SRC) $(PART_6_COMMONS_SRC) $(DEPTH_FIRST_SEARCH_SRC) $(DEPTH_FIRST_SEARCH_MAIN) -o $(BINDIR)/depth_first_search

run-depth-first-search: depth-first-search
	$(BINDIR)/depth_first_search

topological-sort: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_6_COMMONS_SRC) $(TOPOLOGICAL_SORT_SRC) $(TOPOLOGICAL_SORT_MAIN) -o $(BINDIR)/topological_sort

run-topological-sort: topological-sort
	$(BINDIR)/topological_sort

strongly-connected-components: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_6_COMMONS_SRC) $(STRASSEN_SRC) $(TOPOLOGICAL_SORT_SRC) $(STRONGLY_CONNECTED_COMPONENTS_SRC) $(STRONGLY_CONNECTED_COMPONENTS_MAIN) -o $(BINDIR)/strongly_connected_components

run-strongly-connected-components: strongly-connected-components
	$(BINDIR)/strongly_connected_components

chapter-20-problems: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_6_COMMONS_SRC) $(TOPOLOGICAL_SORT_SRC) $(STRONGLY_CONNECTED_COMPONENTS_SRC) $(CHAPTER_20_PROBLEMS_SRC) -o $(BINDIR)/chapter_20_problems

run-chapter-20-problems: chapter-20-problems
	$(BINDIR)/chapter_20_problems

# Chapter 21
growing-mst: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_6_COMMONS_SRC) $(GROWING_MST_SRC) $(GROWING_MST_MAIN) -o $(BINDIR)/growing_mst

run-growing-mst: growing-mst
	$(BINDIR)/growing_mst

kruskal-prim: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_5_COMMONS_SRC) $(PART_6_COMMONS_SRC) $(DISJOINT_SET_OPERATIONS_SRC) $(THE_ALGORITHMS_OF_KRUSKAL_AND_PRIM_SRC) $(THE_ALGORITHMS_OF_KRUSKAL_AND_PRIM_MAIN) -o $(BINDIR)/kruskal_prim

run-kruskal-prim: kruskal-prim
	$(BINDIR)/kruskal_prim

chapter-21-problems: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_5_COMMONS_SRC) $(PART_6_COMMONS_SRC) $(DISJOINT_SET_OPERATIONS_SRC) $(CHAPTER_21_PROBLEMS_SRC) -o $(BINDIR)/chapter_21_problems

run-chapter-21-problems: chapter-21-problems
	$(BINDIR)/chapter_21_problems

# Chapter 22
bellman-ford: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_6_COMMONS_SRC) $(BELLMAN_FORD_ALGORITHM_SRC) $(BELLMAN_FORD_ALGORITHM_MAIN) -o $(BINDIR)/bellman_ford

run-bellman-ford: bellman-ford
	$(BINDIR)/bellman_ford

dag-shortest-paths: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_6_COMMONS_SRC) $(DAG_SHORTEST_PATHS_SRC) $(DAG_SHORTEST_PATHS_MAIN) -o $(BINDIR)/dag_shortest_paths

run-dag-shortest-paths: dag-shortest-paths
	$(BINDIR)/dag_shortest_paths

dijkstra: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_6_COMMONS_SRC) $(DIJKSTRA_ALGORITHM_SRC) $(DIJKSTRA_ALGORITHM_MAIN) -o $(BINDIR)/dijkstra

run-dijkstra: dijkstra
	$(BINDIR)/dijkstra

difference-constraints: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_6_COMMONS_SRC) $(BELLMAN_FORD_ALGORITHM_SRC) $(DIFFERENCE_CONSTRAINTS_SRC) $(DIFFERENCE_CONSTRAINTS_MAIN) -o $(BINDIR)/difference_constraints

run-difference-constraints: difference-constraints
	$(BINDIR)/difference_constraints

chapter-22-problems: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_6_COMMONS_SRC) $(BELLMAN_FORD_ALGORITHM_SRC) $(DAG_SHORTEST_PATHS_SRC) $(DIJKSTRA_ALGORITHM_SRC) $(DIFFERENCE_CONSTRAINTS_SRC) $(CHAPTER_22_PROBLEMS_SRC) -o $(BINDIR)/chapter_22_problems

run-chapter-22-problems: chapter-22-problems
	$(BINDIR)/chapter_22_problems

# Chapter 23
shortest_paths_matrix_mult: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_6_COMMONS_SRC) $(SHORTEST_PATHS_MATRIX_MULT_SRC) $(SHORTEST_PATHS_MATRIX_MULT_MAIN) -o $(BINDIR)/shortest_paths_matrix_mult

run-shortest_paths_matrix_mult: shortest_paths_matrix_mult
	$(BINDIR)/shortest_paths_matrix_mult

floyd-warshall: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_6_COMMONS_SRC) $(SHORTEST_PATHS_MATRIX_MULT_SRC) $(FLOYD_WARSHALL_ALGORITHM_SRC) $(FLOYD_WARSHALL_ALGORITHM_MAIN) -o $(BINDIR)/floyd_warshall

run-floyd-warshall: floyd-warshall
	$(BINDIR)/floyd_warshall

johnsons-algorithm: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_6_COMMONS_SRC) $(JOHNSONS_ALGORITHM_SRC) $(JOHNSONS_ALGORITHM_MAIN) -o $(BINDIR)/johnsons_algorithm

run-johnsons-algorithm: johnsons-algorithm
	$(BINDIR)/johnsons_algorithm

chapter-23-problems: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_6_COMMONS_SRC) $(SHORTEST_PATHS_MATRIX_MULT_SRC) $(FLOYD_WARSHALL_ALGORITHM_SRC) $(JOHNSONS_ALGORITHM_SRC) $(CHAPTER_23_PROBLEMS_SRC) -o $(BINDIR)/chapter_23_problems

run-chapter-23-problems: chapter-23-problems
	$(BINDIR)/chapter_23_problems

# Chapter 24
ford-fulkerson-method: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_6_COMMONS_SRC) $(THE_FORD_FULKERSON_METHOD_SRC) $(THE_FORD_FULKERSON_METHOD_MAIN) -o $(BINDIR)/ford_fulkerson_method

run-ford-fulkerson-method: ford-fulkerson-method
	$(BINDIR)/ford_fulkerson_method

maximum-bipartite-matching: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_6_COMMONS_SRC) $(THE_FORD_FULKERSON_METHOD_SRC) $(MAXIMUM_BIPARTITE_MATCHING_SRC) $(MAXIMUM_BIPARTITE_MATCHING_MAIN) -o $(BINDIR)/maximum_bipartite_matching

run-maximum-bipartite-matching: maximum-bipartite-matching
	$(BINDIR)/maximum_bipartite_matching

chapter-24-problems: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_6_COMMONS_SRC) $(THE_FORD_FULKERSON_METHOD_SRC) $(CHAPTER_24_PROBLEMS_SRC) -o $(BINDIR)/chapter_24_problems

run-chapter-24-problems: chapter-24-problems
	$(BINDIR)/chapter_24_problems

# Chapter 25
maximum-bipartite-matching-2: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_6_COMMONS_SRC) $(MAXIMUM_BIPARTITE_MATCHING_2_SRC) $(MAXIMUM_BIPARTITE_MATCHING_2_MAIN) -o $(BINDIR)/maximum_bipartite_matching

run-maximum-bipartite-matching-2: maximum-bipartite-matching-2
	$(BINDIR)/maximum_bipartite_matching

stable-marriage: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_6_COMMONS_SRC) $(STABLE_MARRIAGE_SRC) $(STABLE_MARRIAGE_MAIN) -o $(BINDIR)/stable_marriage

run-stable-marriage: stable-marriage
	$(BINDIR)/stable_marriage

hungarian-algorithm: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_6_COMMONS_SRC) $(HUNGARIAN_ALGORITHM_SRC) $(HUNGARIAN_ALGORITHM_MAIN) -o $(BINDIR)/hungarian_algorithm

run-hungarian-algorithm: hungarian-algorithm
	$(BINDIR)/hungarian_algorithm

chapter-25-problems: $(BINDIR)
	$(CC) $(CFLAGS) \
	$(COMMON_SRC) \
	$(PART_6_COMMONS_SRC) \
	$(STACKS_QUEUES_SRC) \
	$(CHAPTER_25_PROBLEMS_SRC) \
	src/part_6_graph_algorithms/25_bipartite_matching/3_the_hungarian_algorithm_for_assignment_problem/the_hungarian_algorithm_for_assignment_problem.c \
	-o $(BINDIR)/chapter_25_problems

run-chapter-25-problems: chapter-25-problems
	$(BINDIR)/chapter_25_problems

# ============================================================================
# PART 7: SELECTED TOPICS
# ============================================================================

# Chapter 26
the-basics-of-fork-join: $(BINDIR)
	$(CC) $(CFLAGS) -fopenmp -lpthread $(COMMON_SRC) $(THE_BASICS_OF_FORK_JOIN_SRC) $(THE_BASICS_OF_FORK_JOIN_MAIN) -o $(BINDIR)/the_basics_of_fork_join 

run-the-basics-of-fork-join: the-basics-of-fork-join
	$(BINDIR)/the_basics_of_fork_join

multithreaded-matrix-multiplication: $(BINDIR)
	$(CC) $(CFLAGS) -fopenmp -lpthread $(COMMON_SRC) $(PART_7_COMMONS_SRC) $(MULTITHREADED_MATRIX_MULTIPLICATION_SRC) $(MULTITHREADED_MATRIX_MULTIPLICATION_MAIN) -o $(BINDIR)/multithread_matrix_multiplication

run-multithreaded-matrix-multiplication: multithreaded-matrix-multiplication
	$(BINDIR)/multithread_matrix_multiplication

multithreaded-merge-sort: $(BINDIR)
	$(CC) $(CFLAGS) -fopenmp -lpthread $(COMMON_SRC) $(PART_7_COMMONS_SRC) $(PART_1_COMMONS_SRC) $(QUICKSORT_SRC) $(MULTITHREADED_MERGE_SORT_SRC) $(MULTITHREADED_MERGE_SORT_MAIN) -o $(BINDIR)/multithread_merge_sort

run-multithreaded-merge-sort: multithreaded-merge-sort
	$(BINDIR)/multithread_merge_sort

chapter-26-problems: $(BINDIR)
	$(CC) $(CFLAGS) -fopenmp -lpthread \
	$(COMMON_SRC) \
	$(PART_7_COMMONS_SRC) \
	$(PART_1_COMMONS_SRC) \
	$(QUICKSORT_SRC) \
	$(MULTITHREADED_MERGE_SORT_SRC) \
	$(CHAPTER_26_PROBLEMS_SRC) \
	-o $(BINDIR)/chapter_26_problems

run-chapter-26-problems: chapter-26-problems
	$(BINDIR)/chapter_26_problems

# Chapter 27
waiting-for-an-elevator: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_7_COMMONS_SRC) $(WAITING_FOR_AN_ELEVATOR_SRC) \
	$(WAITING_FOR_AN_ELEVATOR_MAIN) -o $(BINDIR)/waiting-for-an-elevator

run-waiting-for-an-elevator: waiting-for-an-elevator
	$(BINDIR)/waiting-for-an-elevator

maintaining-a-search-list: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_7_COMMONS_SRC) $(MAINTAINING_A_SEARCH_LIST_SRC) \
	$(MAINTAINING_A_SEARCH_LIST_MAIN) -o $(BINDIR)/maintaining-a-search-list

run-maintaining-a-search-list: maintaining-a-search-list
	$(BINDIR)/maintaining-a-search-list

online-cache-management: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_7_COMMONS_SRC) $(ONLINE_CACHE_MANAGEMENT_SRC) $(ONLINE_CACHE_MANAGEMENT_MAIN) -o $(BINDIR)/online_cache_management

assembly-online-cache-management: $(SRCDIR)/part_7_selected_topics/27_online_algorithms/3_online_cache_management/online_cache_management.c
	$(CC) $(CFLAGS) -S $< -o $(SRCDIR)/part_7_selected_topics/27_online_algorithms/3_online_cache_management/online_cache_management.s

run-online-cache-management: online-cache-management
	$(BINDIR)/online_cache_management

chapter-27-problems: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_7_COMMONS_SRC) $(CHAPTER_27_PROBLEMS_SRC) -o $(BINDIR)/chapter_27_problems

run-chapter-27-problems: chapter-27-problems
	$(BINDIR)/chapter_27_problems

# Chapter 28
solving-systems-of-linear-equations: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_7_COMMONS_SRC) $(SOLVING_SYSTEMS_OF_LINEAR_EQUATIONS_SRC) $(SOLVING_SYSTEMS_OF_LINEAR_EQUATIONS_MAIN) -o $(BINDIR)/solving_systems_of_linear_equations

run-solving-systems-of-linear-equations: solving-systems-of-linear-equations
	$(BINDIR)/solving_systems_of_linear_equations

inverting-matrices: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_7_COMMONS_SRC) $(SOLVING_SYSTEMS_OF_LINEAR_EQUATIONS_SRC) $(INVERTING_MATRICES_SRC) $(INVERTING_MATRICES_MAIN) -o $(BINDIR)/inverting_matrices

run-inverting-matrices: inverting-matrices
	$(BINDIR)/inverting_matrices

polynomial-least-squares: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_7_COMMONS_SRC) \
    $(SOLVING_SYSTEMS_OF_LINEAR_EQUATIONS_SRC) \
    $(INVERTING_MATRICES_SRC) \
    $(POLYNOMIAL_LEAST_SQUARES_SRC) \
    $(POLYNOMIAL_LEAST_SQUARES_MAIN) \
    -o $(BINDIR)/polynomial_least_squares

run-polynomial-least-squares: polynomial-least-squares
	$(BINDIR)/polynomial_least_squares

chapter-28-problems: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_7_COMMONS_SRC) src/part_7_selected_topics/28_matrix_operations/problems.c -o $(BINDIR)/chapter_28_problems

run-chapter-28-problems: chapter-28-problems
	$(BINDIR)/chapter_28_problems

# Chapter 29

# Chapter 30
representing-polynomials: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_7_COMMONS_SRC) $(REPRESENTING_POLYNOMIALS_SRC) $(REPRESENTING_POLYNOMIALS_MAIN) -o $(BINDIR)/representing_polynomials

run-representing-polynomials: representing-polynomials
	$(BINDIR)/representing_polynomials

the-dft-and-fft: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_7_COMMONS_SRC) $(THE_DFT_AND_FFT_SRC) $(THE_DFT_AND_FFT_MAIN) -o $(BINDIR)/the_dft_and_fft

run-the-dft-and-fft: the-dft-and-fft
	$(BINDIR)/the_dft_and_fft

efficient_fft_implementations: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART_7_COMMONS_SRC) $(EFFICIENT_FFT_IMPLEMENTATION_SRC) $(EFFICIENT_FFT_IMPLEMENTATION_MAIN) -o $(BINDIR)/efficient_fft_implementations

run_efficient_fft_implementations: efficient_fft_implementations
	$(BINDIR)/efficient_fft_implementations

# ============================================================================
# UTILITY TARGETS
# ============================================================================

clean:
	rm -rf $(BINDIR)