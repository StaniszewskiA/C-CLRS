CC      := gcc
CFLAGS  := -std=c99 -Wall -Wextra -Iinclude
LDLIBS  := -lm
SRCDIR  := src
BINDIR  := bin
EXE     := $(if $(filter Windows_NT,$(OS)),.exe)
OPENMP  := -fopenmp -lpthread

ifeq ($(shell echo "x"),"x")
  MKDIR = if not exist $(subst /,\,$(1)) mkdir $(subst /,\,$(1))
  RMDIR = if exist $(subst /,\,$(1)) rmdir /s /q $(subst /,\,$(1))
else
  MKDIR = mkdir -p $(1)
  RMDIR = rm -rf $(1)
endif

COMMON  := $(SRCDIR)/common.c
rwildcard = $(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$(d),$(2)) $(filter $(subst *,%,$(2)),$(d)))
HEADERS := $(call rwildcard,include,*.h)

app = $(1) $(dir $(1))main.c

P1 := $(SRCDIR)/part_1_foundations
P2 := $(SRCDIR)/part_2_sorting_and_order_statistics
P3 := $(SRCDIR)/part_3_data_structures
P4 := $(SRCDIR)/part_4_advanced_design_and_analysis_techniques
P5 := $(SRCDIR)/part_5_advanced_data_structures
P6 := $(SRCDIR)/part_6_graph_algorithms
P7 := $(SRCDIR)/part_7_selected_topics

P1_COMMONS := $(P1)/part_1_commons.c
P2_COMMONS := $(P2)/part_2_commons.c
P3_COMMONS := $(P3)/part_3_commons.c
P4_COMMONS := $(P4)/part_4_commons.c
P5_COMMONS := $(P5)/part_5_commons.c
P6_COMMONS := $(P6)/part_6_commons.c
P7_COMMONS := $(P7)/part_7_commons.c

# ============================================================================
# MAIN DEMO
# ============================================================================

PROGRAMS += demo demo-debug
demo_SRC        := $(SRCDIR)/main.c
demo-debug_SRC  := $(SRCDIR)/main.c
demo-debug_FLAGS := -DDEBUG

# ============================================================================
# PART 1: FOUNDATIONS
# ============================================================================

# Chapter 1
CH1 := $(P1)/1_the_role_of_algorithms_in_computing
COMPLEXITY_TABLE := $(CH1)/complexity_table/complexity_table.c

PROGRAMS += complexity-table
complexity-table_SRC := $(call app,$(COMPLEXITY_TABLE))

# Chapter 2
CH2 := $(P1)/2_getting_started
INSERTION_SORT       := $(CH2)/1_insertion_sort/insertion_sort.c
ANALYZING_ALGORITHMS := $(CH2)/2_analyzing_algorithms/analyzing_algorithms.c
DESIGNING_ALGORITHMS := $(CH2)/3_designing_algorithms/designing_algorithms.c

PROGRAMS += insertion-sort analyzing-algorithms designing-algorithms chapter-2-problems
insertion-sort_SRC       := $(P1_COMMONS) $(call app,$(INSERTION_SORT))
analyzing-algorithms_SRC := $(P1_COMMONS) $(call app,$(ANALYZING_ALGORITHMS))
designing-algorithms_SRC := $(P1_COMMONS) $(call app,$(DESIGNING_ALGORITHMS))
chapter-2-problems_SRC   := $(P1_COMMONS) $(CH2)/problems.c

# Chapter 4
CH4 := $(P1)/4_divide_and_conquer
SQUARE_MATRIX_MULT := $(CH4)/1_square_matrix_mutliplication/square_matrix_multiplication.c
STRASSEN           := $(CH4)/2_strassen_algorithm/strassen_algorithm.c

PROGRAMS += square-matrix-mult strassen
square-matrix-mult_SRC := $(P1_COMMONS) $(call app,$(SQUARE_MATRIX_MULT))
strassen_SRC           := $(P1_COMMONS) $(call app,$(STRASSEN))

# Chapter 5
CH5 := $(P1)/5_probabilistic_analysis_and_randomized_algorithms
HIRE_ASSISTANT := $(CH5)/1_hire_assistant/hire_assistant.c

PROGRAMS += hire-assistant chapter-5-problems
hire-assistant_SRC     := $(P1_COMMONS) $(call app,$(HIRE_ASSISTANT))
chapter-5-problems_SRC := $(P1_COMMONS) $(CH5)/problems.c

# ============================================================================
# PART 2: SORTING AND ORDER STATISTICS
# ============================================================================

# Chapter 6
CH6 := $(P2)/6_heapsort
HEAPIFY         := $(CH6)/2_maintaining_the_heap_property/maintaining_the_heap_property.c
HEAPSORT        := $(CH6)/4_the_heapsort_algorithm/the_heapsort_algorithm.c
PRIORITY_QUEUES := $(CH6)/5_priority_queues/priority_queues.c

PROGRAMS += maintaining-heap-property heapsort priority-queues chapter-6-problems
maintaining-heap-property_SRC := $(P2_COMMONS) $(call app,$(HEAPIFY))
heapsort_SRC                  := $(P2_COMMONS) $(HEAPIFY) $(call app,$(HEAPSORT))
priority-queues_SRC           := $(P2_COMMONS) $(HEAPIFY) $(HEAPSORT) $(call app,$(PRIORITY_QUEUES))
chapter-6-problems_SRC        := $(P2_COMMONS) $(HEAPIFY) $(PRIORITY_QUEUES) $(CH6)/problems.c

# Chapter 7
CH7 := $(P2)/7_quicksort
QUICKSORT := $(CH7)/1_quicksort/quicksort.c

PROGRAMS += quicksort chapter-7-problems
quicksort_SRC          := $(P2_COMMONS) $(call app,$(QUICKSORT))
chapter-7-problems_SRC := $(P2_COMMONS) $(QUICKSORT) $(CH7)/problems.c

# Chapter 8
CH8 := $(P2)/8_sorting_in_linear_time
COUNTING_SORT := $(CH8)/2_counting_sort/counting_sort.c
RADIX_SORT    := $(CH8)/3_radix_sort/radix_sort.c
BUCKET_SORT   := $(CH8)/4_bucket_sort/bucket_sort.c

PROGRAMS += counting-sort radix-sort bucket-sort chapter-8-problems
counting-sort_SRC      := $(P2_COMMONS) $(call app,$(COUNTING_SORT))
radix-sort_SRC         := $(P2_COMMONS) $(COUNTING_SORT) $(call app,$(RADIX_SORT))
bucket-sort_SRC        := $(P2_COMMONS) $(call app,$(BUCKET_SORT))
chapter-8-problems_SRC := $(P2_COMMONS) $(COUNTING_SORT) $(CH8)/problems.c

# Chapter 9
CH9 := $(P2)/9_medians_and_order_statistics
MIN_MAX           := $(CH9)/1_minimum_and_maximum/minimum_and_maximum.c
RANDOMIZED_SELECT := $(CH9)/2_selection_in_expected_linear_time/selection_in_expected_linear_time.c
WORST_CASE_SELECT := $(CH9)/3_selection_in_worst-case_linear_time/selection_in_worst-case_linear_time.c

PROGRAMS += min-max randomized-select worst-case-select chapter-9-problems
min-max_SRC            := $(P2_COMMONS) $(call app,$(MIN_MAX))
randomized-select_SRC  := $(P2_COMMONS) $(call app,$(RANDOMIZED_SELECT))
worst-case-select_SRC  := $(P2_COMMONS) $(call app,$(WORST_CASE_SELECT))
chapter-9-problems_SRC := $(P2_COMMONS) $(RANDOMIZED_SELECT) $(CH9)/problems.c

# ============================================================================
# PART 3: DATA STRUCTURES
# ============================================================================

# Chapter 10
CH10 := $(P3)/10_elementary_data_structures
STACKS_QUEUES := $(CH10)/1_stacks_and_queues/stacks_and_queues.c
LINKED_LISTS  := $(CH10)/2_linked_lists/linked_lists.c
ROOTED_TREES  := $(CH10)/4_representing_rooted_trees/representing_rooted_trees.c

PROGRAMS += stacks-queues linked-lists rooted-trees chapter-10-problems
stacks-queues_SRC       := $(P3_COMMONS) $(call app,$(STACKS_QUEUES))
linked-lists_SRC        := $(P3_COMMONS) $(call app,$(LINKED_LISTS))
rooted-trees_SRC        := $(P3_COMMONS) $(call app,$(ROOTED_TREES))
chapter-10-problems_SRC := $(P3_COMMONS) $(CH10)/problems.c

# Chapter 11
CH11 := $(P3)/11_hash_tables
DIRECT_ACCESS_TABLES := $(CH11)/1_direct-address_tables/direct_address_tables.c
HASH_TABLES          := $(CH11)/2_hash_tables/hash_tables.c
HASH_FUNCTIONS       := $(CH11)/3_hash_functions/hash_functions.c
OPEN_ADDRESSING      := $(CH11)/4_open_addressing/open_addressing.c
PERFECT_HASHING      := $(CH11)/5_perfect_hashing/perfect_hashing.c

PROGRAMS += direct-access-tables hash-tables hash-functions open-addressing perfect-hashing
direct-access-tables_SRC := $(P3_COMMONS) $(call app,$(DIRECT_ACCESS_TABLES))
hash-tables_SRC          := $(P3_COMMONS) $(call app,$(HASH_TABLES))
hash-functions_SRC       := $(P3_COMMONS) $(call app,$(HASH_FUNCTIONS))
open-addressing_SRC      := $(P3_COMMONS) $(HASH_FUNCTIONS) $(call app,$(OPEN_ADDRESSING))
perfect-hashing_SRC      := $(P3_COMMONS) $(HASH_FUNCTIONS) $(call app,$(PERFECT_HASHING))

# Chapter 12
CH12 := $(P3)/12_binary_search_trees
WHAT_IS_BST            := $(CH12)/1_what_is_a_binary_search_tree/what_is_a_binary_search_tree.c
BST_QUERYING           := $(CH12)/2_querying_a_binary_search_tree/querying_a_binary_search_tree.c
BST_INSERTION_DELETION := $(CH12)/3_insertion_and_deletion/insertion_and_deletion.c

PROGRAMS += bst-what-is bst-querying bst-insertion-deletion
bst-what-is_SRC            := $(P3_COMMONS) $(call app,$(WHAT_IS_BST))
bst-querying_SRC           := $(P3_COMMONS) $(call app,$(BST_QUERYING))
bst-insertion-deletion_SRC := $(P3_COMMONS) $(BST_QUERYING) $(call app,$(BST_INSERTION_DELETION))

# Chapter 13
CH13 := $(P3)/13_red-black_trees
RED_BLACK_TREES := $(CH13)/red-black_trees.c

PROGRAMS += red-black-trees chapter-13-problems
red-black-trees_SRC     := $(P3_COMMONS) $(call app,$(RED_BLACK_TREES))
chapter-13-problems_SRC := $(P3_COMMONS) $(CH13)/problems.c

# ============================================================================
# PART 4: ADVANCED DESIGN AND ANALYSIS TECHNIQUES
# ============================================================================

# Chapter 14
CH14 := $(P4)/14_dynamic_programming
ROD_CUTTING       := $(CH14)/1_rod_cutting/rod_cutting.c
MATRIX_CHAIN_MULT := $(CH14)/2_matrix_chain_multiplication/matrix_chain_multiplication.c
ELEMENTS_DP       := $(CH14)/3_elements_of_dynamic_programming/elements_of_dynamic_programming.c
LCS               := $(CH14)/4_longest_common_subsequence/longest_common_subsequence.c
OPTIMAL_BST       := $(CH14)/5_optimal_binary_search_trees/optimal_binary_search_trees.c

PROGRAMS += rod-cutting matrix-chain-mult elements-dp lcs optimal-bst chapter-14-problems
rod-cutting_SRC         := $(P4_COMMONS) $(call app,$(ROD_CUTTING))
matrix-chain-mult_SRC   := $(P4_COMMONS) $(call app,$(MATRIX_CHAIN_MULT))
elements-dp_SRC         := $(P4_COMMONS) $(call app,$(ELEMENTS_DP))
lcs_SRC                 := $(P4_COMMONS) $(call app,$(LCS))
optimal-bst_SRC         := $(P3_COMMONS) $(P4_COMMONS) $(BST_QUERYING) $(call app,$(OPTIMAL_BST))
chapter-14-problems_SRC := $(P4_COMMONS) $(CH14)/problems.c

# Chapter 15
CH15 := $(P4)/15_greedy_algorithms
ACTIVITY_SELECTION := $(CH15)/1_activity_selection_problem/activity_selection_problem.c
GREEDY_ELEMENTS    := $(CH15)/2_elements_of_the_greedy_strategy/elements_of_the_greedy_strategy.c
HUFFMAN_CODES      := $(CH15)/3_huffman_codes/huffman_codes.c
OFFLINE_CACHING    := $(CH15)/4_off-line_caching/off-line_caching.c

PROGRAMS += activity-selection greedy-elements huffman-codes offline-caching chapter-15-problems
activity-selection_SRC  := $(P4_COMMONS) $(call app,$(ACTIVITY_SELECTION))
greedy-elements_SRC     := $(P4_COMMONS) $(call app,$(GREEDY_ELEMENTS))
huffman-codes_SRC       := $(P4_COMMONS) $(call app,$(HUFFMAN_CODES))
offline-caching_SRC     := $(P4_COMMONS) $(call app,$(OFFLINE_CACHING))
chapter-15-problems_SRC := $(P4_COMMONS) $(CH15)/problems.c

# Chapter 16
CH16 := $(P4)/16_amortized_analysis
AMORTIZED_ANALYSIS := $(CH16)/amortized_analysis.c

PROGRAMS += amortized-analysis chapter-16-problems
amortized-analysis_SRC  := $(P4_COMMONS) $(call app,$(AMORTIZED_ANALYSIS))
chapter-16-problems_SRC := $(P4_COMMONS) $(CH16)/problems.c

# ============================================================================
# PART 5: ADVANCED DATA STRUCTURES
# ============================================================================

# Chapter 17
CH17 := $(P5)/17_enriching_data_structures
DYNAMIC_ORDER_STATISTICS     := $(CH17)/1_dynamic_order_statistics/dynamic_order_statistics.c
HOW_TO_ENRICH_DATA_STRUCTURE := $(CH17)/2_how_to_enrich_a_data_structure/how_to_enrich_a_data_structure.c
INTERVAL_TREES               := $(CH17)/3_interval_trees/interval_trees.c

PROGRAMS += dynamic-order-statistics how-to-enrich-data-structure interval-trees chapter-17-problems
dynamic-order-statistics_SRC     := $(P3_COMMONS) $(RED_BLACK_TREES) $(call app,$(DYNAMIC_ORDER_STATISTICS))
how-to-enrich-data-structure_SRC := $(P3_COMMONS) $(RED_BLACK_TREES) $(call app,$(HOW_TO_ENRICH_DATA_STRUCTURE))
interval-trees_SRC               := $(P3_COMMONS) $(RED_BLACK_TREES) $(call app,$(INTERVAL_TREES))
chapter-17-problems_SRC          := $(P3_COMMONS) $(P5_COMMONS) $(RED_BLACK_TREES) $(CH17)/problems.c

# Chapter 18
CH18 := $(P5)/18_b-trees
B_TREES := $(CH18)/b-trees.c

PROGRAMS += b-trees chapter-18-problems
b-trees_SRC             := $(P5_COMMONS) $(call app,$(B_TREES))
chapter-18-problems_SRC := $(P5_COMMONS) $(B_TREES) $(CH18)/problems.c

# Chapter 19
CH19 := $(P5)/19_data_structures_for_disjoint_sets
DISJOINT_SET_OPERATIONS    := $(CH19)/1_disjoint_set_operations/disjoint_set_operations.c
LINKED_LIST_REPRESENTATION := $(CH19)/2_linked-list_representation_of_disjoint_sets/linked-list_representation_of_disjoint_sets.c
DISJOINT_SET_FORESTS       := $(CH19)/3_disjoint_set_forests/disjoint_set_forests.c

PROGRAMS += disjoint-set-operations linked-list-representation disjoint-set-forests chapter-19-problems
disjoint-set-operations_SRC    := $(P5_COMMONS) $(call app,$(DISJOINT_SET_OPERATIONS))
linked-list-representation_SRC := $(P5_COMMONS) $(call app,$(LINKED_LIST_REPRESENTATION))
disjoint-set-forests_SRC       := $(P5_COMMONS) $(call app,$(DISJOINT_SET_FORESTS))
chapter-19-problems_SRC        := $(P5_COMMONS) $(CH19)/problems.c

# ============================================================================
# PART 6: GRAPH ALGORITHMS
# ============================================================================

# Chapter 20
CH20 := $(P6)/20_elementary_graph_algorithms
REPRESENTATIONS_OF_GRAPHS     := $(CH20)/1_representations_of_graphs/representations_of_graphs.c
BREADTH_FIRST_SEARCH          := $(CH20)/2_breadth-first_search/breadth-first_search.c
DEPTH_FIRST_SEARCH            := $(CH20)/3_depth-first_search/depth-first_search.c
TOPOLOGICAL_SORT              := $(CH20)/4_topological_sort/topological_sort.c
STRONGLY_CONNECTED_COMPONENTS := $(CH20)/5_strongly_connected_components/strongly_connected_components.c

PROGRAMS += representations-of-graphs breadth-first-search depth-first-search topological-sort \
            strongly-connected-components chapter-20-problems
representations-of-graphs_SRC     := $(P1_COMMONS) $(P6_COMMONS) $(STRASSEN) $(call app,$(REPRESENTATIONS_OF_GRAPHS))
breadth-first-search_SRC          := $(P1_COMMONS) $(P6_COMMONS) $(STRASSEN) $(call app,$(BREADTH_FIRST_SEARCH))
depth-first-search_SRC            := $(P1_COMMONS) $(P6_COMMONS) $(call app,$(DEPTH_FIRST_SEARCH))
topological-sort_SRC              := $(P6_COMMONS) $(call app,$(TOPOLOGICAL_SORT))
strongly-connected-components_SRC := $(P6_COMMONS) $(STRASSEN) $(TOPOLOGICAL_SORT) $(call app,$(STRONGLY_CONNECTED_COMPONENTS))
chapter-20-problems_SRC           := $(P6_COMMONS) $(TOPOLOGICAL_SORT) $(STRONGLY_CONNECTED_COMPONENTS) $(CH20)/problems.c

# Chapter 21
CH21 := $(P6)/21_minimum_spanning_trees
GROWING_MST  := $(CH21)/1_growing_a_minimum_spanning_tree/growing_a_minimum_spanning_tree.c
KRUSKAL_PRIM := $(CH21)/2_the_algorithms_of_kruskal_and_prim/the_algorithms_of_kruskal_and_prim.c

PROGRAMS += growing-mst kruskal-prim chapter-21-problems
growing-mst_SRC         := $(P6_COMMONS) $(call app,$(GROWING_MST))
kruskal-prim_SRC        := $(P5_COMMONS) $(P6_COMMONS) $(DISJOINT_SET_OPERATIONS) $(call app,$(KRUSKAL_PRIM))
chapter-21-problems_SRC := $(P5_COMMONS) $(P6_COMMONS) $(DISJOINT_SET_OPERATIONS) $(CH21)/problems.c

# Chapter 22
CH22 := $(P6)/22_single-source_shortest_paths
BELLMAN_FORD           := $(CH22)/1_the_bellman-ford_algorithm/the_bellman-ford_algorithm.c
DAG_SHORTEST_PATHS     := $(CH22)/2_single-source_shortest_paths_in_dags/single-source_shortest_paths_in_dags.c
DIJKSTRA               := $(CH22)/3_dijkstras_algorithm/dijkstras_algorithm.c
DIFFERENCE_CONSTRAINTS := $(CH22)/4_difference_constraints_and_shortest_paths/difference_constraints_and_shortest_paths.c

PROGRAMS += bellman-ford dag-shortest-paths dijkstra difference-constraints chapter-22-problems
bellman-ford_SRC           := $(P6_COMMONS) $(call app,$(BELLMAN_FORD))
dag-shortest-paths_SRC     := $(P6_COMMONS) $(call app,$(DAG_SHORTEST_PATHS))
dijkstra_SRC               := $(P6_COMMONS) $(call app,$(DIJKSTRA))
difference-constraints_SRC := $(P6_COMMONS) $(BELLMAN_FORD) $(call app,$(DIFFERENCE_CONSTRAINTS))
chapter-22-problems_SRC    := $(P6_COMMONS) $(BELLMAN_FORD) $(DAG_SHORTEST_PATHS) $(DIJKSTRA) \
                              $(DIFFERENCE_CONSTRAINTS) $(CH22)/problems.c

# Chapter 23
CH23 := $(P6)/23_all-pairs_shortest_paths
SHORTEST_PATHS_MATRIX_MULT := $(CH23)/1_shortest_paths_and_matrix_multiplication/shortest_paths_and_matrix_multiplication.c
FLOYD_WARSHALL             := $(CH23)/2_the_floyd-warshall_algorithm/the_floyd-warshall_algorithm.c
JOHNSONS_ALGORITHM         := $(CH23)/3_johnsons_algorithm_for_sparse_graphs/johnsons_algorithm_for_sparse_graphs.c

PROGRAMS += shortest-paths-matrix-mult floyd-warshall johnsons-algorithm chapter-23-problems
shortest-paths-matrix-mult_SRC := $(P6_COMMONS) $(call app,$(SHORTEST_PATHS_MATRIX_MULT))
floyd-warshall_SRC             := $(P6_COMMONS) $(SHORTEST_PATHS_MATRIX_MULT) $(call app,$(FLOYD_WARSHALL))
johnsons-algorithm_SRC         := $(P6_COMMONS) $(call app,$(JOHNSONS_ALGORITHM))
chapter-23-problems_SRC        := $(P6_COMMONS) $(SHORTEST_PATHS_MATRIX_MULT) $(FLOYD_WARSHALL) \
                                  $(JOHNSONS_ALGORITHM) $(CH23)/problems.c

# Chapter 24
CH24 := $(P6)/24_maximum_flow
FORD_FULKERSON             := $(CH24)/2_the_ford_fulkerson_method/the_ford_fulkerson_method.c
MAXIMUM_BIPARTITE_MATCHING := $(CH24)/3_maximum_bipartite_matching/maximum_bipartite_matching.c

PROGRAMS += ford-fulkerson-method maximum-bipartite-matching chapter-24-problems
ford-fulkerson-method_SRC      := $(P6_COMMONS) $(call app,$(FORD_FULKERSON))
maximum-bipartite-matching_SRC := $(P6_COMMONS) $(FORD_FULKERSON) $(call app,$(MAXIMUM_BIPARTITE_MATCHING))
chapter-24-problems_SRC        := $(P6_COMMONS) $(FORD_FULKERSON) $(CH24)/problems.c

# Chapter 25
CH25 := $(P6)/25_bipartite_matching
MAXIMUM_BIPARTITE_MATCHING_2 := $(CH25)/1_maximum_bipartite_matching/maximum_bipartite_matching.c
STABLE_MARRIAGE              := $(CH25)/2_stable_marriage_problem/stable_marriage_problem.c
HUNGARIAN_ALGORITHM          := $(CH25)/3_the_hungarian_algorithm_for_assignment_problem/the_hungarian_algorithm_for_assignment_problem.c

PROGRAMS += maximum-bipartite-matching-2 stable-marriage hungarian-algorithm chapter-25-problems
maximum-bipartite-matching-2_SRC := $(P6_COMMONS) $(STACKS_QUEUES) $(call app,$(MAXIMUM_BIPARTITE_MATCHING_2))
stable-marriage_SRC              := $(P6_COMMONS) $(call app,$(STABLE_MARRIAGE))
hungarian-algorithm_SRC          := $(P6_COMMONS) $(STACKS_QUEUES) $(MAXIMUM_BIPARTITE_MATCHING_2) \
                                    $(call app,$(HUNGARIAN_ALGORITHM))
chapter-25-problems_SRC          := $(P6_COMMONS) $(STACKS_QUEUES) $(MAXIMUM_BIPARTITE_MATCHING_2) \
                                    $(HUNGARIAN_ALGORITHM) $(CH25)/problems.c

# ============================================================================
# PART 7: SELECTED TOPICS
# ============================================================================

# Chapter 26
CH26 := $(P7)/26_multithreaded_algorithms
FORK_JOIN                  := $(CH26)/1_the_basics_of_fork-join_multithreading/the_basics_of_fork-join_multithreading.c
MULTITHREADED_MATRIX_MULT  := $(CH26)/2_multithreaded_matrix_multiplication/multithreaded_matrix_multiplication.c
MULTITHREADED_MERGE_SORT   := $(CH26)/3_multithreaded_merge_sort/multithreaded_merge_sort.c

PROGRAMS += the-basics-of-fork-join multithreaded-matrix-multiplication multithreaded-merge-sort chapter-26-problems
the-basics-of-fork-join_SRC             := $(P7_COMMONS) $(call app,$(FORK_JOIN))
multithreaded-matrix-multiplication_SRC := $(P7_COMMONS) $(call app,$(MULTITHREADED_MATRIX_MULT))
multithreaded-merge-sort_SRC            := $(P7_COMMONS) $(P1_COMMONS) $(QUICKSORT) $(call app,$(MULTITHREADED_MERGE_SORT))
chapter-26-problems_SRC                 := $(P7_COMMONS) $(P1_COMMONS) $(QUICKSORT) $(MULTITHREADED_MERGE_SORT) \
                                           $(CH26)/problems.c
the-basics-of-fork-join_FLAGS             := $(OPENMP)
multithreaded-matrix-multiplication_FLAGS := $(OPENMP)
multithreaded-merge-sort_FLAGS            := $(OPENMP)
chapter-26-problems_FLAGS                 := $(OPENMP)

# Chapter 27
CH27 := $(P7)/27_online_algorithms
WAITING_FOR_AN_ELEVATOR   := $(CH27)/1_waiting_for_an_elevator/1_waiting_for_an_elevator.c
MAINTAINING_A_SEARCH_LIST := $(CH27)/2_maintaining_a_search_list/maintaining_a_search_list.c
ONLINE_CACHE_MANAGEMENT   := $(CH27)/3_online_cache_management/online_cache_management.c

PROGRAMS += waiting-for-an-elevator maintaining-a-search-list online-cache-management chapter-27-problems
waiting-for-an-elevator_SRC   := $(P7_COMMONS) $(call app,$(WAITING_FOR_AN_ELEVATOR))
maintaining-a-search-list_SRC := $(P7_COMMONS) $(call app,$(MAINTAINING_A_SEARCH_LIST))
online-cache-management_SRC   := $(P7_COMMONS) $(call app,$(ONLINE_CACHE_MANAGEMENT))
chapter-27-problems_SRC       := $(P7_COMMONS) $(CH27)/problems.c

# Chapter 28
CH28 := $(P7)/28_matrix_operations
LINEAR_EQUATIONS         := $(CH28)/1_solving_systems_of_linear_equations/solving_systems_of_linear_equations.c
INVERTING_MATRICES       := $(CH28)/2_inverting_matrices/inverting_matrices.c
POLYNOMIAL_LEAST_SQUARES := $(CH28)/3_symmetric_positive-definite_matrices_and_least-squares_approximation/symmetric_positive-definite_matrices_and_least-squares_approximation.c

PROGRAMS += solving-systems-of-linear-equations inverting-matrices polynomial-least-squares chapter-28-problems
solving-systems-of-linear-equations_SRC := $(P7_COMMONS) $(call app,$(LINEAR_EQUATIONS))
inverting-matrices_SRC                  := $(P7_COMMONS) $(LINEAR_EQUATIONS) $(call app,$(INVERTING_MATRICES))
polynomial-least-squares_SRC            := $(P7_COMMONS) $(LINEAR_EQUATIONS) $(INVERTING_MATRICES) \
                                           $(call app,$(POLYNOMIAL_LEAST_SQUARES))
chapter-28-problems_SRC                 := $(P7_COMMONS) $(CH28)/problems.c

# Chapter 30
CH30 := $(P7)/30_polynomials_and_the_fft
REPRESENTING_POLYNOMIALS := $(CH30)/1_representing_polynomials/representing_polynomials.c
DFT_AND_FFT              := $(CH30)/2_the_dft_and_fft/the_dft_and_fft.c
EFFICIENT_FFT            := $(CH30)/3_efficient_fft_implementations/efficient_fft_implementations.c

PROGRAMS += representing-polynomials the-dft-and-fft efficient-fft-implementations chapter-30-problems
representing-polynomials_SRC      := $(P7_COMMONS) $(call app,$(REPRESENTING_POLYNOMIALS))
the-dft-and-fft_SRC               := $(P7_COMMONS) $(call app,$(DFT_AND_FFT))
efficient-fft-implementations_SRC := $(P7_COMMONS) $(call app,$(EFFICIENT_FFT))
chapter-30-problems_SRC           := $(P7_COMMONS) $(CH30)/problems.c

# Chapter 31
CH31 := $(P7)/31_number-theoretic_algorithms
NUMBER_THEORETIC_NOTIONS := $(CH31)/1_elementary_number-theoretic_notions/elementary_number-theoretic_notions.c
GCD                      := $(CH31)/2_greatest_common_divisor/greatest_common_divisor.c
MODULAR_LINEAR_EQUATIONS := $(CH31)/4_solving_modular_linear_equations/solving_modular_linear_equations.c
CHINESE_REMAINDER        := $(CH31)/5_chinese_remainder_theorem/chinese_remainder_theorem.c
POWERS_OF_AN_ELEMENT     := $(CH31)/6_powers_of_an_element/powers_of_an_element.c
RSA                      := $(CH31)/7_the_rsa_public-key-cryptosystem/the_rsa_public-key-cryptosystem.c
PRIMALITY_TESTING        := $(CH31)/8_primality_testing/primality_testing.c

PROGRAMS += elementary-number-theoretic-notions greatest-common-divisor solving-modular-linear-equations \
            chinese-remainder-theorem powers-of-an-element the-rsa-public-key-cryptosystem \
            primality-testing chapter-31-problems
elementary-number-theoretic-notions_SRC := $(P7_COMMONS) $(call app,$(NUMBER_THEORETIC_NOTIONS))
greatest-common-divisor_SRC             := $(P7_COMMONS) $(call app,$(GCD))
solving-modular-linear-equations_SRC    := $(P7_COMMONS) $(GCD) $(call app,$(MODULAR_LINEAR_EQUATIONS))
chinese-remainder-theorem_SRC           := $(P7_COMMONS) $(GCD) $(call app,$(CHINESE_REMAINDER))
powers-of-an-element_SRC                := $(P7_COMMONS) $(call app,$(POWERS_OF_AN_ELEMENT))
the-rsa-public-key-cryptosystem_SRC     := $(P7_COMMONS) $(GCD) $(POWERS_OF_AN_ELEMENT) $(CHINESE_REMAINDER) \
                                           $(call app,$(RSA))
primality-testing_SRC                   := $(P7_COMMONS) $(GCD) $(POWERS_OF_AN_ELEMENT) $(CHINESE_REMAINDER) \
                                           $(RSA) $(call app,$(PRIMALITY_TESTING))
chapter-31-problems_SRC                 := $(P7_COMMONS) $(GCD) $(POWERS_OF_AN_ELEMENT) $(CHINESE_REMAINDER) \
                                           $(RSA) $(PRIMALITY_TESTING) $(CH31)/problems.c

# Chapter 32
CH32 := $(P7)/32_string-matching
NAIVE_STRING_MATCHING := $(CH32)/1_the_naive_string-matching_algorithm/the_naive_string-matching_algorithm.c
RABIN_KARP            := $(CH32)/2_the_rabin-karp_algorithm/the_rabin-karp_algorithm.c
FINITE_AUTOMATA       := $(CH32)/3_string_matching_with_finite_automata/string_matching_with_finite_automata.c
KMP                   := $(CH32)/4_the_knuth-morris-pratt_algorithm/the_knuth-morris-pratt_algorithm.c
SUFFIX_ARRAYS         := $(CH32)/5_suffix_arrays/suffix_arrays.c

PROGRAMS += the-naive-string-matching-algorithm the-rabin-karp-algorithm string-matching-with-finite-automata \
            the-knuth-morris-pratt-algorithm suffix-arrays chapter-32-problems
the-naive-string-matching-algorithm_SRC  := $(P7_COMMONS) $(call app,$(NAIVE_STRING_MATCHING))
the-rabin-karp-algorithm_SRC             := $(P7_COMMONS) $(POWERS_OF_AN_ELEMENT) $(call app,$(RABIN_KARP))
string-matching-with-finite-automata_SRC := $(P7_COMMONS) $(call app,$(FINITE_AUTOMATA))
the-knuth-morris-pratt-algorithm_SRC     := $(P7_COMMONS) $(call app,$(KMP))
suffix-arrays_SRC                        := $(P7_COMMONS) $(call app,$(SUFFIX_ARRAYS))
chapter-32-problems_SRC                  := $(P7_COMMONS) $(KMP) $(CH32)/problems.c

# Chapter 33
CH33 := $(P7)/33_machine_learning_algorithms
CLUSTERING := $(CH33)/1_clustering/clustering.c

PROGRAMS += clustering
clustering_SRC := $(P7_COMMONS) $(call app,$(CLUSTERING))

# ============================================================================
# RULES
# ============================================================================

.DEFAULT_GOAL := demo

define PROGRAM
.PHONY: $(1) run-$(1)
$(1): $(BINDIR)/$(1)$(EXE)
run-$(1): $(BINDIR)/$(1)$(EXE)
	$(BINDIR)/$(1)$(EXE)
$(BINDIR)/$(1)$(EXE): $(COMMON) $($(1)_SRC) $(HEADERS) | $(BINDIR)
	$$(CC) $$(CFLAGS) $$($(1)_FLAGS) $(COMMON) $($(1)_SRC) -o $$@ $$(LDLIBS)
endef

$(foreach p,$(PROGRAMS),$(eval $(call PROGRAM,$(p))))

.PHONY: all list clean assembly-online-cache-management
all: $(PROGRAMS)

list:
	@$(foreach p,$(PROGRAMS),$(info $(p)))

$(BINDIR):
	$(call MKDIR,$@)

assembly-online-cache-management: $(ONLINE_CACHE_MANAGEMENT)
	$(CC) $(CFLAGS) -S $< -o $(<:.c=.s)

clean:
	$(call RMDIR,$(BINDIR))
