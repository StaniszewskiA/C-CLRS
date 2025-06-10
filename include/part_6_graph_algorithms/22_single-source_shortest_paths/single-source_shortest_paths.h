#ifndef SINGLE_SOURCE_SHORTEST_PATHS_H
#define SINGLE_SOURCE_SHORTEST_PATHS_H

#include "../../common.h"
#include "../part_6_commons.h"
#include "../../part_5_advanced_data_structures/19_data_structures_for_disjoint_sets/data_structures_for_disjoint_sets.h" // Union-Find src

// ============================================================================
// CHAPTER 22.1: THE BELLMAN-FORD ALGORITHM
// ============================================================================

int bellman_ford(WeightedNodeListGraph* g, int src, int dist[], int pred[]);
void bellman_ford_print_solution(
    int dist[], 
    int pred[], 
    int numVertices, 
    int src
);
void print_negative_cycle(WeightedNodeListGraph* g);
int early_stopped_bellman_ford(
    WeightedNodeListGraph* g, 
    int src, 
    int dist[], 
    int pred[]
);
void dfs_mark(WeightedNodeListGraph* g, int u, int dist[], int visited[]);
int bellman_ford_negative_mark(
    WeightedNodeListGraph* g, 
    int src, 
    int dist[], 
    int pred[]
);
void bellman_ford_print_modified_solution(
    int dist[], 
    int numVertices, 
    int src
);
int bellman_ford_optimized(
    WeightedNodeListGraph* g, 
    int src, 
    int dist[], 
    int pred[]
);
int modified_relax_bellman_ford(
    WeightedNodeListGraph* g, 
    int dist[], 
    int pred[]
);
void bellman_ford_print_modified_solution_prim(
    int dist[], 
    int pred[], 
    int numVertices
);

// ============================================================================
// CHAPTER 22.2: SINGLE-SOURCE SHORTEST PATHS IN DAGS
// ============================================================================

void weighted_list_graph_topo_sort_helper(
    WeightedNodeListGraph* g, 
    int v, 
    int visited[], 
    int* stack, 
    int* stackIdx
);
void weighted_list_graph_topo_sort(WeightedNodeListGraph* g, int* stack);
void dag_shortest_path(
    WeightedNodeListGraph* g, 
    int src, 
    int dist[], 
    int pred[]
);
void print_solution_22_2(int dist[], int pred[], int numVertices, int src);

void split_weighted_vertices(
    WeightedNodeListGraph* g, 
    WeightedNodeListGraph* transformed, 
    int vertexWeights[]
);
int weighted_node_list_graph_count_paths(WeightedNodeListGraph* g);

// ============================================================================
// CHAPTER 22.3: DIJKSTRAS ALGORITHM
// ============================================================================

void dijkstra(MatGraph* g, int src, int dist[], int pred[]);
void print_dijkstra_solution(
    int dist[], 
    int pred[], 
    int numVertices, 
    int src
);

typedef struct PriorityQueueNode {
    int vertex;
    int distance;
} PriorityQueueNode;

typedef struct PriorityQueue {
    PriorityQueueNode nodes[MAX_GRAPH_VERTICES];
    int size;
} PriorityQueue;

void pq_init(PriorityQueue* pq);
void pq_push(PriorityQueue* pq, int vertex, int dist);
PriorityQueueNode pq_pop(PriorityQueue* pq);
int pq_is_empty(PriorityQueue* pq);
void pq_relax(
    int u, 
    int v, 
    int weight, 
    int dist[], 
    int pred[], 
    PriorityQueue* pq
);
void pq_dijkstra(MatGraph* g, int src, int dist[], int pred[]);
int verify_dijkstra_output(MatGraph* g, int dist[], int pred[], int src);

void mat_graph_add_directed_reliability_edge(
    MatGraph* g, 
    int u, 
    int v, 
    double reliability
);

#define MAX_WEIGHT 10

typedef struct BucketNode {
    int vertex;
    struct BucketNode* next;
} BucketNode;

typedef struct Bucket {
    BucketNode* head;
} Bucket;

void bucket_add(Bucket* bucket, int vertex);
int bucket_pop(Bucket* bucket);
int bucket_is_empty(Bucket* bucket);
void dial(MatGraph* g, int src, int dist[], int pred[]);

typedef struct BinaryHeapNode {
    int vertex;
    int distance;
} BinaryHeapNode;

typedef struct BinaryHeap {
    BinaryHeapNode* nodes;
    int size;
    int capacity;
} BinaryHeap;

BinaryHeap* binary_heap_create(int capacity);
void binary_heap_free(BinaryHeap* heap);
void binary_heap_push(BinaryHeap* heap, int vertex, int distance);
BinaryHeapNode binary_heap_pop(BinaryHeap* heap);
int binary_heap_is_empty(BinaryHeap* heap);
void heap_dial(MatGraph* g, int src, int dist[], int pred[]);

void bucket_dijkstra(MatGraph* g, int src, int dist[], int pred[], int C);

// ============================================================================
// CHAPTER 22.4: DIFFERENCE CONSTRAINTS AND SHORTEST PATHS
// ============================================================================

void print_solution_20_4(int dist[], int pred[], int numVertices, int src);

// ============================================================================
// PROBLEMS
// ============================================================================

void print_solution_part_22_problems_solution(
    int dist[], 
    int pred[], 
    int numVertices, 
    int src
);

void yens_bellman_ford(MatGraph* g, int src, int dist[], int pred[]);

int nests_inside(int dims1[], int dims2[], int d);
void find_longest_nesting_seq(int boxes[][MAX_GRAPH_VERTICES], int n, int d);

void build_exchange_rate_graph(
    MatGraph* g, 
    double rates[][MAX_GRAPH_VERTICES]
);
void print_arbitrage_cycle(
    int vertex, 
    int pred[], 
    double rates[][MAX_GRAPH_VERTICES]
);

int calculate_bits_gabow(int W);
int scale_weight(int weight, int i, int k);
void bucket_dijkstra_gabow(
    MatGraph* g, 
    int src, 
    int dist[], 
    int pred[], 
    int maxW
);
void mat_graph_reweight_edges(
    MatGraph* g, 
    MatGraph* reweighted, 
    int i, 
    int k, 
    int prevDist[]
);
void gabows_scaling(MatGraph* g, int src, int dist[], int pred[]);

double karps_minimum_mean_weight(MatGraph* g, int pred[]);

typedef struct WeightedEdge {
    int u, v, w;
} WeightedEdge;

int mat_graph_extract_edges(MatGraph* g, WeightedEdge edges[]);
int edge_weight_cmp_inc(const void* a, const void* b);
int edge_weight_cmp_dec(const void* a, const void* b);

void bitonic_shortest_paths(MatGraph* g, int src, int dist[], int pred[]);

#endif // SINGLE_SOURCE_SHORTEST_PATHS_H