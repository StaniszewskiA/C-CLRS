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
PART1_COMMONS_SRC = $(SRCDIR)/part_1_foundations/part_1_commons.c
PART2_COMMONS_SRC = $(SRCDIR)/part_2_sorting_and_order_statistics/part_2_commons.c
PART3_COMMONS_SRC = $(SRCDIR)/part_3_data_structures/part_3_commons.c

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

RED_BLACK_TREES_PROBLEMS_SRC = $(SRCDIR)/part_3_data_structures/13_red-black_trees/problems.c
RED_BLACK_TREES_PROBLEMS_MAIN = $(SRCDIR)/part_3_data_structures/13_red-black_trees/problems.c

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
        chapter-13-problems run-chapter-13-problems

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
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART1_COMMONS_SRC) $(INSERTION_SORT_SRC) $(INSERTION_SORT_MAIN) -o $(BINDIR)/insertion_sort

run-insertion-sort: insertion-sort
	$(BINDIR)/insertion_sort

analyzing-algorithms: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART1_COMMONS_SRC) $(ANALYZING_ALGORITHMS_SRC) $(ANALYZING_ALGORITHMS_MAIN) -o $(BINDIR)/analyzing_algorithms

run-analyzing-algorithms: analyzing-algorithms
	$(BINDIR)/analyzing_algorithms

designing-algorithms: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART1_COMMONS_SRC) $(DESIGNING_ALGORITHMS_SRC) $(DESIGNING_ALGORITHMS_MAIN) -o $(BINDIR)/designing_algorithms

run-designing-algorithms: designing-algorithms
	$(BINDIR)/designing_algorithms

chapter-2-problems: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART1_COMMONS_SRC) $(CHAPTER_2_PROBLEMS_SRC) -o $(BINDIR)/chapter_2_problems

run-chapter-2-problems: chapter-2-problems
	$(BINDIR)/chapter_2_problems

# Chapter 4
square-matrix-mult: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART1_COMMONS_SRC) $(SQUARE_MATRIX_MULT_SRC) $(SQUARE_MATRIX_MULT_MAIN) -o $(BINDIR)/square_matrix_mult

run-square-matrix-mult: square-matrix-mult
	$(BINDIR)/square_matrix_mult

strassen: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART1_COMMONS_SRC) $(STRASSEN_SRC) $(STRASSEN_MAIN) -o $(BINDIR)/strassen

run-strassen: strassen
	$(BINDIR)/strassen

# Chapter 5
hire-assistant: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART1_COMMONS_SRC) $(HIRE_ASSISTANT_SRC) $(HIRE_ASSISTANT_MAIN) -o $(BINDIR)/hire_assistant

run-hire-assistant: hire-assistant
	$(BINDIR)/hire_assistant

chapter-5-problems: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART1_COMMONS_SRC) $(CHAPTER_5_PROBLEMS_SRC) -o $(BINDIR)/chapter_5_problems

run-chapter-5-problems: chapter-5-problems
	$(BINDIR)/chapter_5_problems

# ============================================================================
# PART 2: SORTING AND ORDER STATISTICS
# ============================================================================

# Chapter 6
maintaining-heap-property: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART2_COMMONS_SRC) $(MAINTAINING_HEAP_PROPERTY_SRC) $(MAINTAINING_HEAP_PROPERTY_MAIN) -o $(BINDIR)/maintaining_heap_property

run-maintaining-heap-property: maintaining-heap-property
	$(BINDIR)/maintaining_heap_property

heapsort: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART2_COMMONS_SRC) $(MAINTAINING_HEAP_PROPERTY_SRC) $(HEAPSORT_SRC) $(HEAPSORT_MAIN) -o $(BINDIR)/heapsort

run-heapsort: heapsort
	$(BINDIR)/heapsort

priority-queues: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART2_COMMONS_SRC) $(MAINTAINING_HEAP_PROPERTY_SRC) $(HEAPSORT_SRC) $(PRIORITY_QUEUES_SRC) $(PRIORITY_QUEUES_MAIN) -o $(BINDIR)/priority_queues

run-priority-queues: priority-queues
	$(BINDIR)/priority_queues

chapter-6-problems: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART2_COMMONS_SRC) $(MAINTAINING_HEAP_PROPERTY_SRC) $(PRIORITY_QUEUES_SRC) $(CHAPTER_6_PROBLEMS_SRC) -o $(BINDIR)/chapter_6_problems

run-chapter-6-problems: chapter-6-problems
	$(BINDIR)/chapter_6_problems

# Chapter 7
quicksort: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART2_COMMONS_SRC) $(QUICKSORT_SRC) $(QUICKSORT_MAIN) -o $(BINDIR)/quicksort

run-quicksort: quicksort
	$(BINDIR)/quicksort

chapter-7-problems: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART2_COMMONS_SRC) $(QUICKSORT_SRC) $(CHAPTER_7_PROBLEMS_SRC) -o $(BINDIR)/chapter_7_problems

run-chapter-7-problems: chapter-7-problems
	$(BINDIR)/chapter_7_problems

# Chapter 8
counting-sort: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART2_COMMONS_SRC) $(COUNTING_SORT_SRC) $(COUNTING_SORT_MAIN) -o $(BINDIR)/counting_sort

run-counting-sort: counting-sort
	$(BINDIR)/counting_sort

radix-sort: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART2_COMMONS_SRC) $(COUNTING_SORT_SRC) $(RADIX_SORT_SRC) $(RADIX_SORT_MAIN) -o $(BINDIR)/radix_sort

run-radix-sort: radix-sort
	$(BINDIR)/radix_sort

bucket-sort: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART2_COMMONS_SRC) $(BUCKET_SORT_SRC) $(BUCKET_SORT_MAIN) -o $(BINDIR)/bucket_sort

run-bucket-sort: bucket-sort
	$(BINDIR)/bucket_sort

chapter-8-problems: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART2_COMMONS_SRC) $(COUNTING_SORT_SRC) $(CHAPTER_8_PROBLEMS_SRC) -o $(BINDIR)/chapter_8_problems

run-chapter-8-problems: chapter-8-problems
	$(BINDIR)/chapter_8_problems

# Chapter 9
min-max: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART2_COMMONS_SRC) $(MIN_MAX_SRC) $(MIN_MAX_MAIN) -o $(BINDIR)/min_max

run-min-max: min-max
	$(BINDIR)/min_max

randomized-select: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART2_COMMONS_SRC) $(RANDOMIZED_SELECT_SRC) $(RANDOMIZED_SELECT_MAIN) -o $(BINDIR)/randomized_select

run-randomized-select: randomized-select
	$(BINDIR)/randomized_select

worst-case-select: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART2_COMMONS_SRC) $(WORST_CASE_SELECT_SRC) $(WORST_CASE_SELECT_MAIN) -o $(BINDIR)/worst_case_select

run-worst-case-select: worst-case-select
	$(BINDIR)/worst_case_select

chapter-9-problems: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART2_COMMONS_SRC) $(RANDOMIZED_SELECT_SRC) $(CHAPTER_9_PROBLEMS_SRC) -o $(BINDIR)/chapter_9_problems

run-chapter-9-problems: chapter-9-problems
	$(BINDIR)/chapter_9_problems

# ============================================================================
# PART 3: DATA STRUCTURES
# ============================================================================

# Chapter 10
stacks-queues: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART3_COMMONS_SRC) $(STACKS_QUEUES_SRC) $(STACKS_QUEUES_MAIN) -o $(BINDIR)/stacks_queues

run-stacks-queues: stacks-queues
	$(BINDIR)/stacks_queues

linked-lists: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART3_COMMONS_SRC) $(LINKED_LISTS_SRC) $(LINKED_LISTS_MAIN) -o $(BINDIR)/linked_lists

run-linked-lists: linked-lists
	$(BINDIR)/linked_lists

rooted-trees: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART3_COMMONS_SRC) $(ROOTED_TREES_SRC) $(ROOTED_TREES_MAIN) -o $(BINDIR)/rooted_trees

run-rooted-trees: rooted-trees
	$(BINDIR)/rooted_trees

chapter-10-problems: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART3_COMMONS_SRC) $(CHAPTER_10_PROBLEMS_SRC) -o $(BINDIR)/chapter_10_problems

run-chapter-10-problems: chapter-10-problems
	$(BINDIR)/chapter_10_problems

# Chapter 11
direct-access-tables: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART3_COMMONS_SRC) $(DIRECT_ACCESS_TABLES_SRC) $(DIRECT_ACCESS_TABLES_MAIN) -o $(BINDIR)/direct_access_tables

run-direct-access-tables: direct-access-tables
	$(BINDIR)/direct_access_tables

hash-tables: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART3_COMMONS_SRC) $(HASH_TABLES_SRC) $(HASH_TABLES_MAIN) -o $(BINDIR)/hash_tables

run-hash-tables: hash-tables
	$(BINDIR)/hash_tables

hash-functions: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART3_COMMONS_SRC) $(HASH_FUNCTIONS_SRC) $(HASH_FUNCTIONS_MAIN) -o $(BINDIR)/hash_functions

run-hash-functions: hash-functions
	$(BINDIR)/hash_functions

open-addressing: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART3_COMMONS_SRC) $(HASH_FUNCTIONS_SRC) $(OPEN_ADDRESSING_SRC) $(OPEN_ADDRESSING_MAIN) -o $(BINDIR)/open_addressing

run-open-addressing: open-addressing
	$(BINDIR)/open_addressing

perfect-hashing: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART3_COMMONS_SRC) $(HASH_FUNCTIONS_SRC) $(PERFECT_HASHING_SRC) $(PERFECT_HASHING_MAIN) -o $(BINDIR)/perfect_hashing

run-perfect-hashing: perfect-hashing
	$(BINDIR)/perfect_hashing

what-is-bst: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART3_COMMONS_SRC) $(WHAT_IS_BST_SRC) $(WHAT_IS_BST_MAIN) -o $(BINDIR)/what-is-bst

run-bst-what-is: what-is-bst
	$(BINDIR)/what-is-bst

bst-querying: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART3_COMMONS_SRC) $(BST_QUERYING_SRC) $(BST_QUERYING_MAIN) -o $(BINDIR)/bst_querying

run-bst-querying: bst-querying
	$(BINDIR)/bst_querying

bst-insertion-deletion: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART3_COMMONS_SRC) $(BST_QUERYING_SRC) $(BST_INSERTION_DELETION_SRC) $(BST_INSERTION_DELETION_MAIN) -o $(BINDIR)/bst_insertion_deletion

run-bst-insertion-deletion: bst-insertion-deletion
	$(BINDIR)/bst_insertion_deletion

red-black-trees: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART3_COMMONS_SRC) $(RED_BLACK_TREES_SRC) $(RED_BLACK_TREES_MAIN) -o $(BINDIR)/red-black_trees

run-red-black-trees: red-black-trees
	$(BINDIR)/red-black_trees

chapter-13-problems: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART3_COMMONS_SRC) $(RED_BLACK_TREES_PROBLEMS_SRC) -o $(BINDIR)/chapter_13_problems

run-chapter-13-problems: chapter-13-problems
	$(BINDIR)/chapter_13_problems

# ============================================================================
# UTILITY TARGETS
# ============================================================================

clean:
	rm -rf $(BINDIR)