#ifndef BIPARTITE_MATCHING_H
#define BIPARTITE_MATCHING_H

#include "../../common.h"
#include "../part_6_commons.h"

// ============================================================================
// CHAPTER 25.1: MAXIMUM BIPARTITE MATCHING
// ============================================================================

typedef struct {
    int leftSize;
    int rightSize;
    int adj[MAX_GRAPH_VERTICES][MAX_GRAPH_VERTICES];
    int adjSize[MAX_GRAPH_VERTICES];
} BipartiteGraph;

BipartiteGraph* bipartite_graph_init(int leftSize, int rightSize);
void bipartite_graph_add_edge(BipartiteGraph* g, int u, int v);
void print_bipartite_graph(BipartiteGraph* g);
void print_matching(int pairU[], int leftSize);
int bfs_build_layers(
    BipartiteGraph* g, 
    int pairU[], 
    int pairV[], 
    int dist[]
);
int dfs_find_augmenting_path(
    BipartiteGraph* g, 
    int u, 
    int pairU[], 
    int pairV[], 
    int dist[]
);
int hopcroft_karp(BipartiteGraph* g);
void test_hopcroft_karp_algorithm(void);
int earky_stopping_hopcroft_karp(BipartiteGraph* g);
void test_early_stopping_hopcroft_karp_algorithm(void);

// ============================================================================
// CHAPTER 25.2: STABLE MARRIAGE PROBLEM
// ============================================================================



// ============================================================================
// CHAPTER 25.3: THE HUNGARIAN ALGORITHM FOR ASSIGNMENT PROBLEM
// ============================================================================



// ============================================================================
// PROBLEMS
// ============================================================================

#endif // BIPARTITE_MATCHING_H