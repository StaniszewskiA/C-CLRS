#ifndef DYNAMIC_PROGRAMMING_H
#define DYNAMIC_PROGRAMMING_H

#include "../../common.h"
#include "../part_4_commons.h"

#include "part_3_data_structures/12_binary_search_trees/binary_search_trees.h"


// ============================================================================
// CHAPTER 14.1: ROD CUTTING
// ============================================================================

int rod_cutting_brute_force(int p[], int n);
int rod_cutting_top_down(int p[], int n);
int rod_cutting_bottom_up(int p[], int n);
void rod_cutting_extended_bottom_up(int p[], int n);
int rod_cutting_bottom_up_with_cost(int p[], int n, int c);
int memoized_cut_rod_aux(int p[], int n, int r[], int s[]);
void memoized_cut_rod_2(int p[], int n);
int rod_cutting_extended_top_down(int p[], int n);
int dp_fibonacci(int n);

// ============================================================================
// CHAPTER 14.2: MATRIX CHAIN MULTIPLICATION
// ============================================================================

int matrix_chain_order(int p[], int n, int s[][MAX_MATRIX_SIZE]);
void print_optimal_parens(int s[][MAX_MATRIX_SIZE], int i, int j);
int matrix_chain_multiply(int* A[], int s[][MAX_MATRIX_SIZE], int i, int j);

// ============================================================================
// CHAPTER 14.3: ELEMENTS OF DYNAMIC PROGRAMMING
// ============================================================================

int lookup_chain(int **m, int *p, int i, int j);
int memoized_matrix_chain(int *p, int n);

// ============================================================================
// CHAPTER 14.4: LONGEST COMMON SUBSEQUENCE
// ============================================================================

#define SEQ_LEN 41

int lcs_brute_force(char *X, char *Y, int m, int n);
int lcs_dp(char *X, char *Y, int m, int n, int b[m+1][n+1], int c[m+1][n+1]);
void print_lcs(int b[SEQ_LEN + 1][SEQ_LEN + 1], char *X, int i, int j);
void print_lcs_no_b(
    int c[SEQ_LEN + 1][SEQ_LEN + 1], 
    char *X, 
    char *Y, 
    int i, 
    int j
);
int memoized_lcs_len(
    int c[SEQ_LEN + 1][SEQ_LEN + 1], 
    char *X, 
    char *Y, 
    int i, 
    int j
);

#define UP 1
#define LEFT 2
#define DIAG 3

void print_lcs_prim(
    int c[SEQ_LEN][SEQ_LEN], 
    char X[SEQ_LEN], 
    char Y[SEQ_LEN], 
    int m,
    int n
);
int memo_lcs_length_aux(
    char X[SEQ_LEN], 
    char Y[SEQ_LEN], 
    int c[SEQ_LEN][SEQ_LEN], 
    int b[SEQ_LEN][SEQ_LEN], 
    int m, 
    int n
);
void memo_lcs_length(
    char X[SEQ_LEN], 
    char Y[SEQ_LEN], 
    int c[SEQ_LEN][SEQ_LEN], 
    int b[SEQ_LEN][SEQ_LEN], 
    int m, 
    int n
);

typedef struct Node {
    int key;
    struct Node* next;
} Node;

typedef struct List {
    Node *head;
} List;

void print_list(List* list);
void list_insert(List* list, int key);
void long_monotonic(int* A, int n);

// ============================================================================
// CHAPTER 14.5: OPTIMAL BINARY SEARCH TREES
// ============================================================================

#define MAX_BST_SIZE 100
#define N 3

void optimal_bst(float p[], float q[], int n, int root[][n + 1]);
BSTNode* construct_optimal_bst(int root[][100], int keys[], int i, int j);
void knuthian_optimal_bst(float p[], float q[], int n, int root[][n + 1]);
void print_root_table(int root[][N+1], int n);
void print_cost_table(double costs[][MAX_BST_SIZE], int n);

// ============================================================================
// PROBLEMS
// ============================================================================

#define MAX_VERTICES 10

typedef struct Edge {
    int dest, weight;
} Edge;

typedef struct AdjList {
    Edge edges[MAX_VERTICES];
    int size;
} AdjList;



void graph_add_edge(int u, int v, int w);
int topological_sort(int n);
int longest_path_in_dag(int n, int s, int t);
void longest_palindrome_subseq(char *s);

typedef struct Point {
    double x, y;
} Point;

int compare_points(const void *a, const void *b);
void bitonic_tsp(Point points[], int n);

#define MAX_LINE_WIDTH 10

void print_neatly(int *lengths, int n);

#define COST_COPY -1
#define COST_REPLACE 1
#define COST_DELETE 2
#define COST_INSERT 2
#define COST_TWIDDLE INF
#define COST_KILL INF

typedef enum { 
    COPY, 
    REPLACE, 
    DELETE, 
    INSERT, 
    TWIDDLE, 
    KILL,
    NONE
} Operation;

void edit_distance(char *x, char *y);

#define MAX_EMPLOYEES 10

typedef struct Employee {
    char name[50];
    double conviviality;
    struct Employee *leftChild;
    struct Employee *rightSibling;
} Employee;

typedef struct {
    double C[MAX_EMPLOYEES];
    int included[MAX_EMPLOYEES];
} DPResult;



Employee* employee_create(const char* name, double conviviality);
double max_convivality(Employee* root, DPResult* dp, int idx);
void print_guest_list(Employee* root, DPResult* dp, int idx);

#define NO_SUCH_PATH NULL
#define MAX_SEQ_LEN 100 

typedef struct ViterbiEdge {
    int dest;
    int sigma;
    double proba; // Transition probability
} ViterbiEdge;

typedef struct ViterbiVertex {
    int id;
    int edgeCount;
    ViterbiEdge* edges;
} ViterbiVertex;

typedef struct ViterbiSolution {
    int* seq; // Sequence of states
    int seqLen; 
    double proba; // Probability of sequence
} ViterbiSolution;

ViterbiVertex* viterbi_vertex_create(int id, int edgeCount);
void viterbi_edge_add(
    ViterbiVertex* from, 
    int dest, 
    int sigma, 
    double proba, 
    int edgeIdx
);
ViterbiSolution viterbi(
    ViterbiVertex **graph, 
    int numNodes, 
    int *sigma, 
    int sigmaLen, 
    int v0
);

#define MAX_M 100
#define MAX_N 100

typedef struct Pixel{
    int row;
    int col;
} Pixel;

typedef struct Seam {
    Pixel* pixels;
    int size;
    int capacity;
} Seam;

void seam_init(Seam* seam, int capacity);
void add_to_seam(Seam* seam, int row, int col);
void seam_free(Seam* seam);
void seam_carving(int **d, int m, int n);

#define MAX_M9 100
#define INF9 1000

int break_string(int L[], int i, int j, int l, int r);
void reconstruct_break_seq(int i, int j);

#define YEARS 10

void invest(
    int r[YEARS + 1][YEARS + 1], 
    int dr[YEARS + 1][YEARS + 1], 
    int fees[2], 
    int n, 
    int I[YEARS + 1], 
    int R[YEARS + 1]
);
void inventory_planning(int n, int m, int c, int* demand, int* inventoryCost);

typedef struct Player {
    int cost;
    int war;
    int pos;
} Player;

void sign_players(int n, int B, int P, Player players[n][P]);

#endif // DYNAMIC_PROGRAMMING_H