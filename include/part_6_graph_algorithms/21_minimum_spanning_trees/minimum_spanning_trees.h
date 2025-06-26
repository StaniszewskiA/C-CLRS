#ifndef GROWING_A_MINIMUM_SPANNING_TREE_H
#define GROWING_A_MINIMUM_SPANNING_TREE_H

#include "../../common.h"
#include "../part_6_commons.h"
#include "../../part_5_advanced_data_structures/19_data_structures_for_disjoint_sets/data_structures_for_disjoint_sets.h" // Union-Find src

// ============================================================================
// CHAPTER 21.1: GROWING A MINIMUM SPANNING TREE
// ============================================================================

int dfs_find_path(
    MatGraph* g,
    int u,
    int v,
    int* visited,
    int* parent,
    int* maxU,
    int* maxV,
    int* maxW
);
void update_mst(MatGraph* mst, int u, int v, int newWeight);

// ============================================================================
// CHAPTER 21.2: THE ALGORITHMS OF KRUSKAL AND PRIM
// ============================================================================


#define MAX_NEIS 10
#define MAX_EDGES 100

typedef struct AdjList {
    int neis[MAX_NEIS];
    int weights[MAX_NEIS];
    int neiCnt;
} AdjList;

typedef struct ExplicitAdjListGraph {
    AdjList adjList[MAX_VERTICES];
    int numVertices;
} ExplicitAdjListGraph;

ExplicitAdjListGraph* explicit_adj_list_graph_create(int numVertices);
void explicit_adj_list_graph_free(ExplicitAdjListGraph* g);
void explicit_adj_list_graph_add_undirected_weighted_edge(
    ExplicitAdjListGraph* g, 
    int u, 
    int v, 
    int weight
);

typedef struct Edge {
    int u, v, weight;
} Edge;

void mst_add_edge(int u, int v, int weight);
int compare_edges(const void* a, const void* b);

int kruskal(int numVertices, Edge* edges, int edgeCnt);

typedef struct PrimMinHeapNode {
    int vertex;
    int weight;
} PrimMinHeapNode;

typedef struct PrimMinHeap {
    PrimMinHeapNode* nodes[MAX_VERTICES];
    int size;
} PrimMinHeap;

PrimMinHeap* prim_min_heap_create();
void prim_min_heap_swap(PrimMinHeap* heap, int i, int j);
void prim_min_heap_insert(PrimMinHeap* heap, int vertex, int weight);
PrimMinHeapNode* prim_min_heap_extract_min(PrimMinHeap* heap);
void prim_min_heap_decrease_key(PrimMinHeap* heap, int vertex, int newWeight);

void prim(ExplicitAdjListGraph* g, int source);

#define GRAPH_SIZE 5

typedef struct {
    int parent;
    int weight;
} Pair;

void adj_mat_prim(int adjMat[GRAPH_SIZE][GRAPH_SIZE], int root);

// ============================================================================
// PROBLEMS
// ============================================================================

void mat_graph_dfs_set_p_d(MatGraph* g, int u, int p, int d);
int find_lca(int u, int v);
int max_on_path(MatGraph* g, int u, int v);
void compute_max_edges(MatGraph* g);
int mst_kruskal(MatGraph* g, Edge* edges, int edgeCnt, MatGraph* mst);
int find_second_best_mst_weight( 
    MatGraph* mst, 
    Edge* edges, 
    int edgeCnt, 
    int mstW
);

typedef struct {
    int u;
    int v;
    int weight;
} OrigEdge;

void mst_reduce(MatGraph* g, MatGraph** gPrimePtr, Edge* t, int* tSize);
void print_mst_edges(Edge* t, int tSize);

int compare_edges_descending(const void* a, const void* b);
void print_maybe_mst_edges(Edge* edges, int size);
void maybe_mst_a(MatGraph* g, Edge* resultEdges, int* resultSize);
void maybe_mst_b(MatGraph* g, Edge* resultEdges, int* resultSize);

void find_cycle_and_max_edge(
    MatGraph* g, 
    int u, 
    int v, 
    int* uMax, 
    int* vMax, 
    int* weightMax
);

void maybe_mst_c(MatGraph* g, Edge* resultEdges, int* resultSize);

int mat_graph_has_bottleneck_spanning_tree(MatGraph* g, int b);

void mat_graph_contract_edges(
    MatGraph* g, 
    int threshold, 
    MatGraph** contractedGraph
);
int find_bottleneck_spanning_tree(MatGraph* g);

#endif // GROWING_A_MINIMUM_SPANNING_TREE_H