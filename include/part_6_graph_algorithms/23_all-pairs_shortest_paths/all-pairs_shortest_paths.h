#ifndef ALL_PAIRS_SHORTEST_PATHS_H
#define ALL_PAIRS_SHORTEST_PATHS_H

#include "../../common.h"
#include "../part_6_commons.h"

// ============================================================================
// CHAPTER 23.1: SHORTEST PATHS AND MATRIX MULTIPLICATION
// ============================================================================

#define BUFFER_SIZE 64

void extend_shortest_paths(
    int A[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int B[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int C[MAX_MAT_SIZE][MAX_MAT_SIZE]
);
void slow_apsp(
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int L[MAX_MAT_SIZE][MAX_MAT_SIZE]
);
void faster_apsp(
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int L[MAX_MAT_SIZE][MAX_MAT_SIZE]
);

void pseudo_bellman_ford(
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int src, 
    int dist[MAX_MAT_SIZE]
);

void space_optimized_slow_apsp(
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int L[MAX_MAT_SIZE][MAX_MAT_SIZE]
);
void space_optimized_faster_apsp(
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int L[MAX_MAT_SIZE][MAX_MAT_SIZE]
);

void compute_pred_mat(
    int L[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int pred[MAX_MAT_SIZE][MAX_MAT_SIZE]
);

void print_pred_mat(int pred[MAX_MAT_SIZE][MAX_MAT_SIZE], const char* name);
void extend_shortest_path_mod(
    int prevPred[MAX_MAT_SIZE][MAX_MAT_SIZE],
    int L[MAX_MAT_SIZE][MAX_MAT_SIZE],
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE],
    int newPred[MAX_MAT_SIZE][MAX_MAT_SIZE],
    int newL[MAX_MAT_SIZE][MAX_MAT_SIZE]
);
void space_optimized_slow_apsp_mod(
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int L[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int pred[MAX_MAT_SIZE][MAX_MAT_SIZE]
);

int faster_apsp_neg_cycle(
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int L[MAX_MAT_SIZE][MAX_MAT_SIZE]
);

int min_length_neg_cycle(int W[MAX_MAT_SIZE][MAX_MAT_SIZE]);

// ============================================================================
// CHAPTER 23.2: THE FLOYD-WARSHALL ALGORITHM
// ============================================================================

void floyd_warshall(
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int D[MAX_MAT_SIZE][MAX_MAT_SIZE]
);

void transitive_closure(
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int T[MAX_MAT_SIZE][MAX_MAT_SIZE]
);

void extend_transitive_paths(
    int A[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int B[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int C[MAX_MAT_SIZE][MAX_MAT_SIZE]
);
void slow_apsp_transitive_closure(
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int T[MAX_MAT_SIZE][MAX_MAT_SIZE]
);

void floyd_warshall_with_pred(
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int D[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int pred[MAX_MAT_SIZE][MAX_MAT_SIZE]
);

void space_optimized_floyd_warshall(
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int D[MAX_MAT_SIZE][MAX_MAT_SIZE]
);

void floyd_warshall_neg_cycle_detect(
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int D[MAX_MAT_SIZE][MAX_MAT_SIZE]
);

void print_path_phi_helper(int phi[MAX_MAT_SIZE][MAX_MAT_SIZE], int i, int j);
void print_path_phi(int phi[MAX_MAT_SIZE][MAX_MAT_SIZE], int i, int j);
void floyd_warshall_phi(
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int D[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int phi[MAX_MAT_SIZE][MAX_MAT_SIZE]
);

void transitive_closure_bfs(
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int T[MAX_MAT_SIZE][MAX_MAT_SIZE]
);

void dfs232(
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int node, 
    int visited[MAX_MAT_SIZE], 
    int stack[MAX_MAT_SIZE], 
    int* stackIdx
);
void assign_scc232(
    int WT[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int node, 
    int visited[MAX_MAT_SIZE], 
    int comp[MAX_MAT_SIZE], 
    int compIdx
);
void transpose_graph232(
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int WT[MAX_MAT_SIZE][MAX_MAT_SIZE]
);
int kosaraju_scc232(
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int comp[MAX_MAT_SIZE]
);
void transitive_closure_comps(
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int T[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int numComps
);
void scc_transitive_closure(
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int T[MAX_MAT_SIZE][MAX_MAT_SIZE]
);

// ============================================================================
// CHAPTER 23.3: JOHNSONES ALGORITHM FOR SPARSE GRAPHS
// ============================================================================

int bellman_ford_johnson(WeightedNodeListGraph* g, int src, int* h);
void dijkstra_johnson(
    WeightedNodeListGraph* g, 
    int src, 
    int* dist, 
    int* h, 
    int reweight
);
void print_h_vector(const int* h, int n);
void print_w_hat(WeightedNodeListGraph* g, const int* h);
int johnson(
    WeightedNodeListGraph* g, 
    int D[MAX_GRAPH_VERTICES][MAX_GRAPH_VERTICES]
);

// ============================================================================
// PROBLEMS
// ============================================================================

void update_transitive_closure(
    int T[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int n, 
    int x, 
    int y
);
void update_transitive_closure_prime(
    int T[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int n, 
    int x, 
    int y
);

#define MAX_HEAP_SIZE 64

typedef struct {
    int key;
    int val;
} DaryHeapNode;

typedef struct {
    DaryHeapNode data[MAX_HEAP_SIZE];
    int pos[MAX_HEAP_SIZE];
    int size;
    int d;
} DAryHeap;

void dary_heap_init(DAryHeap* heap, int d);
int dary_heap_is_empty(DAryHeap* heap);
void dary_heap_swap(DAryHeap* heap, int i, int j);
void dary_heapify_up(DAryHeap* heap, int i);
void dary_heapify_down(DAryHeap* heap, int i);
void dary_heap_insert(DAryHeap* heap, int key, int val);
void dary_heap_dec_key(DAryHeap* heap, int val, int newKey);
DaryHeapNode dary_heap_extract_min(DAryHeap* heap);

void dijkstra_eps_dense(
    int n, 
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int src, 
    int dist[MAX_MAT_SIZE], 
    int d
);
void apsp_eps_dense(
    int n, 
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int D[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int d
);
void eps_dense_johnson(
    int n, 
    int W[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int D[MAX_MAT_SIZE][MAX_MAT_SIZE], 
    int d
);

#endif // ALL_PAIRS_SHORTEST_PATHS_H