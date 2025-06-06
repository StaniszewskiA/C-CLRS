CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Iinclude -lm  
SRCDIR = src
OBJDIR = obj
BINDIR = bin

COMMON_SRC = $(SRCDIR)/common.c
MAIN_SRC = $(SRCDIR)/main.c

# Part 1 source files - Updated paths to match actual file locations
COMPLEXITY_TABLE_SRC = $(SRCDIR)/part_1_foundations/1_the_role_of_algorithms_in_computing/complexity_table/complexity_table.c
COMPLEXITY_TABLE_MAIN = $(SRCDIR)/part_1_foundations/1_the_role_of_algorithms_in_computing/complexity_table/main.c

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

# Run

run: demo
	$(BINDIR)/demo

run-debug: demo-debug
	$(BINDIR)/demo_debug

run-complexity-table: complexity-table
	$(BINDIR)/complexity_table

clean:
	rm -rf $(BINDIR)

help:
	@echo "Available targets:"
	@echo "  demo                - Build release version"
	@echo "  demo-debug          - Build debug version"
	@echo "  complexity-table    - Build complexity table demo"
	@echo "  run                 - Build and run release version"
	@echo "  run-debug           - Build and run debug version"
	@echo "  run-complexity-table - Build and run complexity table demo"
	@echo "  clean               - Remove build files"