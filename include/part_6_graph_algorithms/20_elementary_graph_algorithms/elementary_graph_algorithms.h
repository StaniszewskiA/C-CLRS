#ifndef ELEMENTARY_GRAPH_ALGORITHM_H
#define ELEMENTARY_GRAPH_ALGORITHM_H

#include "../../common.h"
#include "../part_6_commons.h"
#include "../../part_1_foundations/4_divide_and_conquer/divide_and_conquer.h" // Strassen src

// ============================================================================
// CHAPTER 20.1: REPRESENTATIONS OF GRAPHS
// ============================================================================

void insert_edge(Node** adjList, int vertex);
void insert_edges(Node** adjList, int edges[][2], int numEdges);
void print_adj_list(Node** adjList, int numVertices);
void graph_print_matrix(int** matrix, int numVertices);
void init_adj_list(Node** adjList, int numVertices);
void init_matrix(int** matrix, int numVertices);
void free_adj_list(Node** adjList, int numVertices);
void graph_free_matrix(int** matrix, int size);
int** graph_allocate_matrix(int size);
void mat_set_edges(int** matrix);

void list_graph_transpose(Node** adjList, Node** adjListT, int numVertices);
void mat_graph_transpose(int** matrix, int** matrixT, int numVertices);
void demultify_graph(Node** adjList, Node** result, int numVertices);
void adj_square_graph(Node** adjList, Node** result, int numVertices);
void add_mat(int** A, int** B, int** C, int size);
void sub_mat(int** A, int** B, int** C, int size);
void mat_square_graph(int** matrix, int** result, int n);

int is_universal_sink(int** matrix, int numVertices, int candidate);
void find_universal_sink(int** matrix, int numVertices);

// ============================================================================
// CHAPTER 20.2: BREADTH-FIST SEARCH
// ============================================================================

void list_graph_bfs(ListGraph* g, int source);
void mat_graph_bfs(MatGraph* g, int source);

typedef enum { UNCOLORED = -1, BABYFACE = 0, HEEL = 1} Role;

int check_wrestlers(ListGraph* g, Role* roles, int source);
int can_assign_wrestlers(ListGraph* g, Role* roles);
int bfs_furthest_node(ListGraph* g, int source, int* outDist);
int tree_diameter(ListGraph* g);

// ============================================================================
// CHAPTER 20.3: DEPTH-FIRST SEARCH
// ============================================================================

void dfs_visit(ListGraph* g, int vertex, int visited[]);
void dfs(ListGraph* g, int* order, int orderSize);

void iterative_dfs_visit(ListGraph* g, int source, int visited[]);
void iterative_dfs(ListGraph* g, int* order, int orderSize);

#define WHITE 0
#define GRAY 1
#define BLACK 2

typedef struct ColoredVertex {
    int id;
    int color;
    int d;
    int f;
    int pi;
} ColoredVertex;

typedef struct ColoredGraph {
    int numVertices;
    int** adj;
    ColoredVertex* vertices;
} ColoredGraph;

void colored_dfs_print(ColoredGraph* g);
ColoredGraph* colored_graph_create(int numVertices);
void colored_graph_add_edge(ColoredGraph* g, int u, int v);
void colored_graph_free(ColoredGraph* g);

void dfs_both_dirs(ListGraph* g);

typedef struct CCNode {
    int cc;
    int color;
    int pi;
    int d;
    int f;
    struct CCNode* next;
} CCNode;

typedef struct CCList {
    struct CCNode* head;
} CCList;

typedef struct CCGraph {
    int numVertices;
    struct CCList* array;
} CCGraph;

CCGraph* cc_graph_create(int numVertices);
CCNode* cc_node_create(int cc);
void cc_graph_add_undirected_edge(CCGraph* g, int u, int v);
void cc_graph_free(CCGraph* g);
void cc_visit_dfs(CCGraph* g, int u, int* time, int cc);
void cc_dfs(CCGraph* g);

void topo_sort_helper(ListGraph* g, int v, int* visited, int* stack, int* stackIdx);
int* topological_sort(ListGraph* g);

int list_graph_is_singly_connected(ListGraph* g);

// ============================================================================
// CHAPTER 20.4: TOPOLOGICAL SORT
// ============================================================================

void mat_graph_topo_sort_helper(
    MatGraph* g, 
    int v, 
    int visited[], 
    int stack[], 
    int *stackIdx
);
void mat_graph_topo_sort(MatGraph* g, int stack[]);
int mat_graph_count_simple_paths(MatGraph* g, int s, int t);
int mat_graph_dfs_cycle_check(MatGraph* g, int v, int visited[], int parent);
int mat_graph_is_acyclic(MatGraph* g);

int mat_graph_indeg_topo_sort(MatGraph* g, int result[]);

// ============================================================================
// CHAPTER 20.5: STRONGLY CONNECTED COMPONENTS
// ============================================================================

MatGraph* build_component_graph(
    MatGraph* g, 
    int component[], 
    int numComponents
);

MatGraph* create_minimal_scc_graph(
    MatGraph* g, 
    int component[], 
    int numComponents
);
int mat_graph_is_semiconnected(MatGraph* g);

void find_max_delta_l(MatGraph* g, double labels[]);

// ============================================================================
// PROBLEMS
// ============================================================================

void compute_low_values(
    MatGraph* g,
    int u,
    int parent,
    int* visited,
    int* discovery,
    int* low,
    int* time
);
void find_low_values(MatGraph* g);
void compute_articulation_points(
    MatGraph* g,
    int* visited,
    int* discovery,
    int* low,
    int* articulationPoints
);
void find_articulation_points(MatGraph* g);
void compute_bridges(
    MatGraph* g,
    int u,
    int parent,
    int* visited,
    int* discovery,
    int* low,
    int* articulationPoints,
    int* degree,
    int* time,
    int bridges[MAX_GRAPH_VERTICES][MAX_GRAPH_VERTICES]
);
void find_bridges(MatGraph* g);
void label_bcc_edges(
    MatGraph* g, 
    int u, 
    int bccId,
    int* visited,
    int bccLabels[MAX_GRAPH_VERTICES][MAX_GRAPH_VERTICES]
);
void find_bccs(MatGraph* g);

void find_euler_tour(MatGraph* g, int source);

int reachability(
    MatGraph* gSCC, 
    int u, 
    int* minValues, 
    int* visited, 
    int* sccMinLabels
);
void compute_min_labels(MatGraph* g, int* labels);

typedef struct PlanarGraph {
    int adjList[MAX_GRAPH_VERTICES][MAX_GRAPH_VERTICES];
    int adjSize[MAX_GRAPH_VERTICES];
    int newestNei[MAX_GRAPH_VERTICES];
    int stack[MAX_GRAPH_VERTICES];
    int stackTop;
} PlanarGraph;

PlanarGraph* planar_graph_create();
void planar_graph_insert(PlanarGraph* pg, int v, int* neis, int numNeis);
int planar_graph_newest_nei(PlanarGraph* pg, int v);
void planar_graph_free(PlanarGraph* pg);

#endif // ELEMENTARY_GRAPH_ALGORITHM_H