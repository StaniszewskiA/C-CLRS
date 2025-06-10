#ifndef PART_6_COMMONS_H
#define PART_6_COMMONS_H

#include "../common.h"

#define MAX_GRAPH_VERTICES 100

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct ListGraph {
    int numVertices;
    Node* adjList[MAX_GRAPH_VERTICES];
} ListGraph;

Node* create_node(int vertex);
ListGraph* list_graph_create(int numVertices);
void list_graph_free(ListGraph* g);
void list_graph_add_edge(ListGraph* g, int u, int v);

typedef struct MatGraph {
    int numVertices;
    int adjMat[MAX_GRAPH_VERTICES][MAX_GRAPH_VERTICES];
} MatGraph;

MatGraph* mat_graph_create(int numVertices);
void mat_graph_free(MatGraph* g);
void mat_graph_add_undirected_edge(MatGraph* g, int u, int v);

void list_graph_add_undirected_edge(ListGraph* g, int u, int v);

void mat_graph_add_directed_edge(MatGraph* g, int u, int v);
void mat_graph_add_undirected_edge(MatGraph* g, int u, int v);
int mat_graph_has_cycle(MatGraph* g, int v, int visited[], int recursionStack[]);
int mat_graph_is_dag(MatGraph* g);

void mat_graph_dfs(MatGraph* g, int v, int visited[], int stack[], int* stackIdx);

MatGraph* transpose_mat_graph(MatGraph* g);

void assign_scc(
    MatGraph* gt, 
    int v, 
    int visited[], 
    int component[], 
    int compId
);

int kosaraju(MatGraph* g, int component[]);

void mat_graph_remove_undirected_edge(MatGraph* g, int u, int v);
void mat_graph_add_undirected_weighted_edge(MatGraph* g, int u, int v, int weight);

void mat_graph_print(MatGraph* g);

int mat_graph_is_connected(MatGraph* g);
int mat_graph_check_if_path_exists(MatGraph* g, int source, int target);

typedef struct WeightedNode {
    int vertex;
    int weight;
    struct WeightedNode* next;
} WeightedNode;

typedef struct WeightedNodeListGraph {
    int numVertices;
    WeightedNode* adjList[MAX_GRAPH_VERTICES];
} WeightedNodeListGraph;

WeightedNode* create_weighted_node(int vertex, int weight);
WeightedNodeListGraph* weighted_node_list_graph_create(int numVertices);
void weighted_node_list_graph_free(WeightedNodeListGraph* g);
void weighted_node_list_graph_add_edge(
    WeightedNodeListGraph* g, 
    int u, 
    int v, 
    int weight
);

void relax_edge(int u, int v, int weight, int dist[], int pred[]);
void print_path(int pred[], int dest);
void modified_relax(int u, int v, int weight, int dist[], int pred[]);
int find_negative_cycle_dfs(
    WeightedNodeListGraph* g,
    int source,
    int curr,
    int* path,
    int pathIdx,
    int* visited,
    int* onPath,
    int* cycleStart,
    int* weights
);

void mat_graph_add_directed_weighted_edge(
    MatGraph* g, 
    int u, 
    int v, 
    int weight
);

void init_single_source(int dist[], int pred[], int numVertices, int src);

void safe_relax_edge(int u, int v, int weight, int dist[], int pred[]);

#define MAX_GRAPH_EDGES 100

void mat_graph_remove_undirected_weighted_edge(MatGraph* g, int u, int v);

void mat_graph_add_directed_weighted_edge(
    MatGraph* g, 
    int u, 
    int v, 
    int weight
);
void mat_graph_remove_directed_weighted_edge(
    MatGraph* g, 
    int u, 
    int v
);

typedef struct FibNode {
    int vertex;
    int key;
    struct FibNode* parent;
    struct FibNode* child;
    struct FibNode* left;
    struct FibNode* right;
    int degree;
    int mark;
} FibNode;

typedef struct FibHeap {
    FibNode* min;
    int size;
} FibHeap;

FibNode* fib_node_create(int vertex, int key);
FibHeap* fib_heap_create();
void fib_insert(FibHeap* heap, FibNode* node);
void fib_link(FibNode* y, FibNode* x);
void fib_consolidate(FibHeap* heap);
FibNode* fib_extract_min(FibHeap* heap);
void fib_cut(FibHeap* heap, FibNode* x, FibNode* y);
void fib_cascading_cut(FibHeap* heap, FibNode* y);
void fib_dec_key(FibHeap* heap, FibNode* x, int k);
void fib_free(FibNode* node);

typedef struct FlowMatGraph {
    /*
        Flow network represented as
        adjacency matrix graph.
    */
    int adjMat[MAX_GRAPH_VERTICES][MAX_GRAPH_VERTICES]; // capacity
    int flow[MAX_GRAPH_VERTICES][MAX_GRAPH_VERTICES]; // flow 
    int numVertices;
} FlowMatGraph;

FlowMatGraph* flow_mat_graph_create(int numVertices);
void flow_mat_graph_free(FlowMatGraph* g);
void flow_mat_graph_add_directed_edge(
    FlowMatGraph* g, 
    int u, 
    int v, 
    int capacity
);
void flow_mat_graph_add_undirected_edge(FlowMatGraph* g, int u, int v);
void print_flow_matrix(FlowMatGraph* g, const char* name);
void flow_graph_copy(FlowMatGraph* dest, FlowMatGraph* src, int copyFlow);
FlowMatGraph* flow_mat_graph_copy(FlowMatGraph* original);
void flow_mat_graph_reset_flow(FlowMatGraph* g);

#endif // PART_6_COMMONS_H
