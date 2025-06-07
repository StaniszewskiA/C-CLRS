CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Iinclude -lm  
SRCDIR = src
OBJDIR = obj
BINDIR = bin

COMMON_SRC = $(SRCDIR)/common.c
MAIN_SRC = $(SRCDIR)/main.c

# Common srcs
PART1_COMMONS_SRC = $(SRCDIR)/part_1_foundations/part_1_commons.c
PART2_COMMONS_SRC = $(SRCDIR)/part_2_sorting_and_order_statistics/part_2_commons.c

# Chapter 1
COMPLEXITY_TABLE_SRC = $(SRCDIR)/part_1_foundations/1_the_role_of_algorithms_in_computing/complexity_table/complexity_table.c
COMPLEXITY_TABLE_MAIN = $(SRCDIR)/part_1_foundations/1_the_role_of_algorithms_in_computing/complexity_table/main.c

# Chapter 2
INSERTION_SORT_SRC = $(SRCDIR)/part_1_foundations/2_getting_started/1_insertion_sort/insertion_sort.c
INSERTION_SORT_MAIN = $(SRCDIR)/part_1_foundations/2_getting_started/1_insertion_sort/main.c

ANALYZING_ALGORITHMS_SRC = $(SRCDIR)/part_1_foundations/2_getting_started/2_analyzing_algorithms/analyzing_algorithms.c
ANALYZING_ALGORITHMS_MAIN = $(SRCDIR)/part_1_foundations/2_getting_started/2_analyzing_algorithms/main.c

# Fix the broken line:
DESIGNING_ALGORITHMS_SRC = $(SRCDIR)/part_1_foundations/2_getting_started/3_designing_algorithms/designing_algorithms.c
DESIGNING_ALGORITHMS_MAIN = $(SRCDIR)/part_1_foundations/2_getting_started/3_designing_algorithms/main.c

CHARPTER_2_PROBLEMS_SRC = $(SRCDIR)/part_1_foundations/2_getting_started/problems.c

# Chapter 4
SQUARE_MATRIX_MULT_SRC = $(SRCDIR)/part_1_foundations/4_divide_and_conquer/1_square_matrix_mutliplication/square_matrix_multiplication.c
SQUARE_MATRIX_MULT_MAIN = $(SRCDIR)/part_1_foundations/4_divide_and_conquer/1_square_matrix_mutliplication/main.c
 
STRASSEN_SRC = $(SRCDIR)/part_1_foundations/4_divide_and_conquer/2_strassen_algorithm/strassen_algorithm.c
STRASSEN_MAIN = $(SRCDIR)/part_1_foundations/4_divide_and_conquer/2_strassen_algorithm/main.c

# Chapter 5
HIRE_ASSISTANT_SRC = $(SRCDIR)/part_1_foundations/5_probabilistic_analysis_and_randomized_algorithms/1_hire_assistant/hire_assistant.c
HIRE_ASSISTANT_MAIN = $(SRCDIR)/part_1_foundations/5_probabilistic_analysis_and_randomized_algorithms/1_hire_assistant/main.c

CHAPTER_5_PROBLEMS_SRC = $(SRCDIR)/part_1_foundations/5_probabilistic_analysis_and_randomized_algorithms/problems.c

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

.PHONY: all clean demo demo-debug run run-debug complexity-table run-complexity-table insertion-sort run-insertion-sort analyzing-algorithms run-analyzing-algorithms designing-algorithms run-designing-algorithms chapter-2-problems run-chapter-2-problems square-matrix-mult run-square-matrix-mult strassen run-strassen hire-assistant run-hire-assistant chapter-5-problems run-chapter-5-problems maintaining-heap-property run-maintaining-heap-property heapsort run-heapsort priority-queues run-priority-queues chapter-6-problems run-chapter-6-problems quicksort run-quicksort chapter-7-problems run-chapter-7-problems counting-sort run-counting-sort radix-sort run-radix-sort bucket-sort run-bucket-sort chapter-8-problems run-chapter-8-problems min-max run-min-max randomized-select run-randomized-select worst-case-select run-worst-case-select chapter-9-problems run-chapter-9-problems

all: demo demo-debug

$(BINDIR):
	mkdir -p $(BINDIR)

# Compile
demo: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(MAIN_SRC) -o $(BINDIR)/demo

demo-debug: $(BINDIR)
	$(CC) -DDEBUG $(CFLAGS) $(COMMON_SRC) $(MAIN_SRC) -o $(BINDIR)/demo_debug

complexity-table: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(COMPLEXITY_TABLE_SRC) $(COMPLEXITY_TABLE_MAIN) -o $(BINDIR)/complexity_table

insertion-sort: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART1_COMMONS_SRC) $(INSERTION_SORT_SRC) $(INSERTION_SORT_MAIN) -o $(BINDIR)/insertion_sort

analyzing-algorithms: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART1_COMMONS_SRC) $(ANALYZING_ALGORITHMS_SRC) $(ANALYZING_ALGORITHMS_MAIN) -o $(BINDIR)/analyzing_algorithms

designing-algorithms: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART1_COMMONS_SRC) $(DESIGNING_ALGORITHMS_SRC) $(DESIGNING_ALGORITHMS_MAIN) -o $(BINDIR)/designing_algorithms

chapter-2-problems: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART1_COMMONS_SRC) $(CHARPTER_2_PROBLEMS_SRC) -o $(BINDIR)/getting_started_problems

square-matrix-mult: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART1_COMMONS_SRC) $(SQUARE_MATRIX_MULT_SRC) $(SQUARE_MATRIX_MULT_MAIN) -o $(BINDIR)/square_matrix_mult

strassen: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART1_COMMONS_SRC) $(STRASSEN_SRC) $(STRASSEN_MAIN) -o $(BINDIR)/strassen

hire-assistant: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART1_COMMONS_SRC) $(HIRE_ASSISTANT_SRC) $(HIRE_ASSISTANT_MAIN) -o $(BINDIR)/hire_assistant

chapter-5-problems: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART1_COMMONS_SRC) $(CHAPTER_5_PROBLEMS_SRC) -o $(BINDIR)/chapter_5_problems

maintaining-heap-property: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART2_COMMONS_SRC) $(MAINTAINING_HEAP_PROPERTY_SRC) $(MAINTAINING_HEAP_PROPERTY_MAIN) -o $(BINDIR)/maintaining_heap_property

heapsort: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART2_COMMONS_SRC) $(MAINTAINING_HEAP_PROPERTY_SRC) $(HEAPSORT_SRC) $(HEAPSORT_MAIN) -o $(BINDIR)/heapsort

priority-queues: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART2_COMMONS_SRC) $(MAINTAINING_HEAP_PROPERTY_SRC) $(HEAPSORT_SRC) $(PRIORITY_QUEUES_SRC) $(PRIORITY_QUEUES_MAIN) -o $(BINDIR)/priority_queues

chapter-6-problems: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART2_COMMONS_SRC) $(MAINTAINING_HEAP_PROPERTY_SRC) $(PRIORITY_QUEUES_SRC) $(CHAPTER_6_PROBLEMS_SRC) -o $(BINDIR)/chapter_6_problems

quicksort: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART2_COMMONS_SRC) $(QUICKSORT_SRC) $(QUICKSORT_MAIN) -o $(BINDIR)/quicksort

chapter-7-problems: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART2_COMMONS_SRC) $(QUICKSORT_SRC) $(CHAPTER_7_PROBLEMS_SRC) -o $(BINDIR)/chapter_7_problems

counting-sort: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART2_COMMONS_SRC) $(COUNTING_SORT_SRC) $(COUNTING_SORT_MAIN) -o $(BINDIR)/counting_sort

radix-sort: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART2_COMMONS_SRC) $(COUNTING_SORT_SRC) $(RADIX_SORT_SRC) $(RADIX_SORT_MAIN) -o $(BINDIR)/radix_sort

bucket-sort: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART2_COMMONS_SRC) $(BUCKET_SORT_SRC) $(BUCKET_SORT_MAIN) -o $(BINDIR)/bucket_sort

chapter-8-problems: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART2_COMMONS_SRC) $(COUNTING_SORT_SRC) $(CHAPTER_8_PROBLEMS_SRC) -o $(BINDIR)/chapter_8_problems


min-max: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART2_COMMONS_SRC) $(MIN_MAX_SRC) $(MIN_MAX_MAIN) -o $(BINDIR)/min_max

randomized-select: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART2_COMMONS_SRC) $(RANDOMIZED_SELECT_SRC) $(RANDOMIZED_SELECT_MAIN) -o $(BINDIR)/randomized_select

worst-case-select: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART2_COMMONS_SRC) $(WORST_CASE_SELECT_SRC) $(WORST_CASE_SELECT_MAIN) -o $(BINDIR)/worst_case_select

chapter-9-problems: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(PART2_COMMONS_SRC) $(RANDOMIZED_SELECT_SRC) $(CHAPTER_9_PROBLEMS_SRC) -o $(BINDIR)/chapter_9_problems

# Run
run: demo
	$(BINDIR)/demo

run-debug: demo-debug
	$(BINDIR)/demo_debug

run-complexity-table: complexity-table
	$(BINDIR)/complexity_table

run-insertion-sort: insertion-sort
	$(BINDIR)/insertion_sort

run-analyzing-algorithms: analyzing-algorithms
	$(BINDIR)/analyzing_algorithms

run-designing-algorithms: designing-algorithms
	$(BINDIR)/designing_algorithms

run-chapter-2-problems: chapter-2-problems
	$(BINDIR)/getting_started_problems

run-square-matrix-mult: square-matrix-mult
	$(BINDIR)/square_matrix_mult

run-strassen: strassen
	$(BINDIR)/strassen

run-hire-assistant: hire-assistant
	$(BINDIR)/hire_assistant

run-chapter-5-problems: chapter-5-problems
	$(BINDIR)/chapter_5_problems

run-maintaining-heap-property: maintaining-heap-property
	$(BINDIR)/maintaining_heap_property

run-heapsort: heapsort
	$(BINDIR)/heapsort

run-priority-queues: priority-queues
	$(BINDIR)/priority_queues

run-chapter-6-problems: chapter-6-problems
	$(BINDIR)/chapter_6_problems

run-quicksort: quicksort
	$(BINDIR)/quicksort

run-chapter-7-problems: chapter-7-problems
	$(BINDIR)/chapter_7_problems

run-counting-sort: counting-sort
	$(BINDIR)/counting_sort

run-radix-sort: radix-sort
	$(BINDIR)/radix_sort

run-bucket-sort: bucket-sort
	$(BINDIR)/bucket_sort

run-chapter-8-problems: chapter-8-problems
	$(BINDIR)/chapter_8_problems

run-min-max: min-max
	$(BINDIR)/min_max

run-randomized-select: randomized-select
	$(BINDIR)/randomized_select

run-worst-case-select: worst-case-select
	$(BINDIR)/worst_case_select

run-chapter-9-problems: chapter-9-problems
	$(BINDIR)/chapter_9_problems

# Other
clean:
	rm -rf $(BINDIR)