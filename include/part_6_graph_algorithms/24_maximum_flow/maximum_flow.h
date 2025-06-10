#ifndef ALL_PAIRS_SHORTEST_PATHS_H
#define ALL_PAIRS_SHORTEST_PATHS_H

#include "../../common.h"
#include "../part_6_commons.h"

// ============================================================================
// CHAPTER 24.2: THE FORD-FULKERSON METHOD
// ============================================================================

int flow_dfs(FlowMatGraph* g, int u, int t, int parent[], int visited[]);
int ford_fulkerson(FlowMatGraph* g, int s, int t);
int flow_bfs(FlowMatGraph* graph, int s, int t, int parent[]);
int edmonds_karp(FlowMatGraph* g, int s, int t);
void decompose_flow(FlowMatGraph* g, int s, int t);
int flow_graph_edge_connectivity(FlowMatGraph* g);
void cancel_out_src_inflow(FlowMatGraph* g, int src);

// ============================================================================
// CHAPTER 24.3: MAXIMUM BIPARTITE MATCHING
// ============================================================================

FlowMatGraph* create_bipartite_flow_graph(
    int leftSize,
    int rightSize,
    int bipartiteEdges[][2],
    int numEdges
);
void print_bipartite_matching(FlowMatGraph* g, int leftSize, int rightSize);

// ============================================================================
// PROBLEMS
// ============================================================================

int flow_mat_graph_has_cycle(
    FlowMatGraph* g, 
    int v, 
    int visited[], 
    int stack[]
);
int flow_mat_graph_is_dag(FlowMatGraph* g);
void flow_mat_graph_find_reachable_vertices(
    FlowMatGraph* g, 
    int src, 
    int reachable[]
);
int flow_mat_graph_get_random_edge(
    FlowMatGraph* g, 
    int activeEdges[], 
    int* u, 
    int* v
);
void flow_mat_graph_contract_edge(
    FlowMatGraph* g, 
    int u, 
    int v, 
    int activeEdges[]
);

typedef struct {
    int tree[MAX_GRAPH_VERTICES][MAX_GRAPH_VERTICES];
    int capacity[MAX_GRAPH_VERTICES][MAX_GRAPH_VERTICES];
    int n;
} GomoryHuTree;

GomoryHuTree* gomory_hu_tree_create(int n);
void gomory_hu_tree_free(GomoryHuTree* ghTree);
GomoryHuTree* gomory_hu_tree_build(FlowMatGraph* g);

int grid_to_vertex(int row, int col, int n);
int is_boundary(int row, int col, int n);
FlowMatGraph* create_escape_flow_network(
    int n, 
    int startingPoints[][2], 
    int m
);
int can_escape(int n, int startingPoints[][2], int m);

int find_minimum_path_cover(FlowMatGraph* g);

typedef struct {
    int profit;
    int numExperts;
    int experts[MAX_GRAPH_VERTICES];
} Job;

FlowMatGraph* create_consulting_flow_network(
    Job jobs[], 
    int numJobs, 
    int expertCosts[], 
    int numExperts
);
void solve_consulting_problem(
    Job jobs[],
    int numJobs,
    int expertCosts[],
    int numExperts
);

int flow_mat_graph_update_capacity(
    FlowMatGraph* g, 
    int src, 
    int v, 
    int sink, 
    int delta
);

int dfs_with_scale(
    FlowMatGraph* g,
    int src,
    int sink,
    int parent[],
    int visited[],
    int scale
);
int dfs_augmenting_path(
    FlowMatGraph* g,
    int src,
    int sink,
    int parent[],
    int scale
);
int max_flow_by_scaling(FlowMatGraph* g, int src, int sink);

int dijkstra_widest_path(FlowMatGraph* g, int src, int sink, int parent[]);
int widest_augmenting_path(FlowMatGraph* g, int src, int sink);

int find_min_global_cut_all_pairs(FlowMatGraph* g);
int find_min_global_cut_fixed_src(FlowMatGraph* g);
int find_min_global_cut_gomory_hu(FlowMatGraph* g);

int karger_single_run(FlowMatGraph* g);
int karger_unique(FlowMatGraph* g);
int karger(FlowMatGraph* g);

#endif // ALL_PAIRS_SHORTEST_PATHS_H