CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Iinclude -lm  
SRCDIR = src
OBJDIR = obj
BINDIR = bin

COMMON_SRC = $(SRCDIR)/common.c
MAIN_SRC = $(SRCDIR)/main.c

# Chapter 1
COMPLEXITY_TABLE_SRC = $(SRCDIR)/part_1_foundations/1_the_role_of_algorithms_in_computing/complexity_table/complexity_table.c
COMPLEXITY_TABLE_MAIN = $(SRCDIR)/part_1_foundations/1_the_role_of_algorithms_in_computing/complexity_table/main.c

# Chapter 2
INSERTION_SORT_SRC = $(SRCDIR)/part_1_foundations/2_getting_started/1_insertion_sort/insertion_sort.c
INSERTION_SORT_MAIN = $(SRCDIR)/part_1_foundations/2_getting_started/1_insertion_sort/main.c

ANALYZING_ALGORITHMS_SRC = $(SRCDIR)/part_1_foundations/2_getting_started/2_analyzing_algorithms/analyzing_algorithms.c
ANALYZING_ALGORITHMS_MAIN = $(SRCDIR)/part_1_foundations/2_getting_started/2_analyzing_algorithms/main.c


.PHONY: all clean demo demo-debug run run-debug complexity-table run-complexity-table

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
	$(CC) $(CFLAGS) $(COMMON_SRC) $(INSERTION_SORT_SRC) $(INSERTION_SORT_MAIN) -o $(BINDIR)/insertion_sort

analyzing-algorithms: $(BINDIR)
	$(CC) $(CFLAGS) $(COMMON_SRC) $(INSERTION_SORT_SRC) $(ANALYZING_ALGORITHMS_SRC) $(ANALYZING_ALGORITHMS_MAIN) -o $(BINDIR)/analyzing_algorithms

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


# Other
clean:
	rm -rf $(BINDIR)

help:
	@echo "Available targets:"
	@echo "  demo                    - Build release version"
	@echo "  demo-debug              - Build debug version"
	@echo "  complexity-table        - Build complexity table demo"
	@echo "  insertion-sort          - Build insertion sort demo"
	@echo "  analyzing-algorithms    - Build analyzing algorithms demo"
	@echo "  run                     - Build and run release version"
	@echo "  run-debug               - Build and run debug version"
	@echo "  run-complexity-table    - Build and run complexity table demo"
	@echo "  run-insertion-sort      - Build and run insertion sort demo"
	@echo "  run-analyzing-algorithms - Build and run analyzing algorithms demo"
	@echo "  clean                   - Remove build files"