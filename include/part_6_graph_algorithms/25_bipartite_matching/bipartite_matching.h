#ifndef BIPARTITE_MATCHING_H
#define BIPARTITE_MATCHING_H

#include "../../common.h"
#include "../part_6_commons.h"
#include "../../part_3_data_structures/10_elementary_data_structures/elementary_data_structures.h" // Stack utils

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

#define MAX_PEOPLE 100
#define MAX_RESIDENTS_PER_HOSPITAL 100

typedef struct {
    int n;
    int menPref[MAX_PEOPLE][MAX_PEOPLE];
    int womenPref[MAX_PEOPLE][MAX_PEOPLE];
    int womenRanking[MAX_PEOPLE][MAX_PEOPLE];
} StableMarriageInstance;

typedef struct {
    int manPartner[MAX_PEOPLE];
    int womanPartner[MAX_PEOPLE];
    int n;
} StableMarriageResult;

StableMarriageInstance* stable_marriage_init(int n);
void stable_marriage_set_men_prefs(
    StableMarriageInstance* 
    instance, 
    int man, 
    int prefs[]
);
void stable_marriage_set_women_prefs(
    StableMarriageInstance* 
    instance, 
    int woman, 
    int prefs[]
);
void print_stable_marriage_instance(StableMarriageInstance* instance);
void print_stable_marriage_result(StableMarriageResult* res);
int woman_prefers(
    StableMarriageInstance* instance, 
    int woman, 
    int man1, 
    int man2
);
StableMarriageResult* gale_shapley(StableMarriageInstance* instance);
int verify_stability(
    StableMarriageInstance* instance, 
    StableMarriageResult* res
);
void test_gale_shapley_algorithm(void);

#define MAX_RESIDENTS_PER_HOSPITAL 100

typedef struct NRMPInstance {
    int numStudents;
    int numHospitals;
    int hospitalCapacity[MAX_PEOPLE];
    int studentPref[MAX_PEOPLE][MAX_PEOPLE];           
    int hospitalPref[MAX_PEOPLE][MAX_PEOPLE]; 
    int hospitalRanking[MAX_PEOPLE][MAX_PEOPLE];
} NRMPInstance;

typedef struct NRMPResult {
    int studentsHospital[MAX_PEOPLE];
    int hospitalsStudents[MAX_PEOPLE][MAX_RESIDENTS_PER_HOSPITAL];
    int hospitalCapacity[MAX_PEOPLE];
    int numStudents;
    int numHospitals;
} NRMPResult;

NRMPInstance* nrmp_init(int numStudents, int numHospitals);
void nrmp_set_hospital_capacity(
    NRMPInstance* instance, 
    int hospital, 
    int capacity
);
void nrmp_set_student_prefs(NRMPInstance* instance, int student, int prefs[]);
void nrmp_set_hospital_prefs(NRMPInstance* instance, int hospital, int prefs[]);
void print_nrmp_instance(NRMPInstance* instance);
void print_nrmp_result(NRMPResult* res);
int hospital_prefers_student(
    NRMPInstance* instance,
    int hospital,
    int student1,
    int student2
);
int find_worst_student_in_hospital(
    NRMPInstance* instance, 
    NRMPResult* res, 
    int hospital
);
void remove_student_from_hospital(
    NRMPResult* res,
    int student,
    int hospital
);
void add_student_to_hospital(
    NRMPResult* res,
    int student,
    int hospital
);
NRMPResult* nrmp_gale_shapley(NRMPInstance* instance);
int verify_nrmp_stability(NRMPInstance* instance, NRMPResult* res);
void test_nrmp_solver(void);

typedef struct StableRoommatesInstance {
    int n;
    int prefs[MAX_PEOPLE][MAX_PEOPLE];
    int ranking[MAX_PEOPLE][MAX_PEOPLE];
} StableRoommatesInstance;

typedef struct StableRoommatesResult {
    int n;
    int partner[MAX_PEOPLE];
} StableRoommatesResult;

StableRoommatesInstance* stable_roommates_init(int n);
void stable_roommates_set_prefs(
    StableRoommatesInstance* instance, 
    int person, 
    int prefs[]
);
void print_stable_roommates_instace(StableRoommatesInstance* instance);
void print_stable_roommates_result(StableRoommatesResult* res);
int person_prefers(
    StableRoommatesInstance* instance, 
    int person,
    int cand1,
    int cand2
);
void irving_phase1_proposals(
    StableRoommatesInstance* instance,
    int props[MAX_PEOPLE][MAX_PEOPLE],
    int propCnt[MAX_PEOPLE]
);
int irving_phase2_reduction(
    StableRoommatesInstance* instance,
    int activeProps[MAX_PEOPLE][MAX_PEOPLE]
);
int irving_phase3_matching(
    StableRoommatesInstance* instance,
    int activeProps[MAX_PEOPLE][MAX_PEOPLE],
    StableRoommatesResult* res
);
StableRoommatesResult* irving_algorithm(StableRoommatesInstance* instance);
int verify_roommates_stability(
    StableRoommatesInstance* instance,
    StableRoommatesResult* res
);
void test_stable_roommates_solver(void);

// ============================================================================
// CHAPTER 25.3: THE HUNGARIAN ALGORITHM FOR ASSIGNMENT PROBLEM
// ============================================================================

typedef struct {
    int n;
    int cost[MAX_GRAPH_VERTICES][MAX_GRAPH_VERTICES];
    int leftLabel[MAX_GRAPH_VERTICES];
    int rightLabel[MAX_GRAPH_VERTICES];
    int matching[MAX_GRAPH_VERTICES];
    int matchedRight[MAX_GRAPH_VERTICES];
    int visitedLeft[MAX_GRAPH_VERTICES];
    int visitedRight[MAX_GRAPH_VERTICES];
    int parentLeft[MAX_GRAPH_VERTICES];
    int parentRight[MAX_GRAPH_VERTICES]; 
} AssignmentInstance;

AssignmentInstance* assignment_init(int n);
void assignment_set_cost(AssignmentInstance* instance, int i, int j, int cost);
void assignment_free(AssignmentInstance* instance);
void print_assignment_instance(AssignmentInstance* instance);
void print_assignment_matching(AssignmentInstance* instance);
void assignment_init_labels(AssignmentInstance* instance);
int assignment_find_initial_matching(AssignmentInstance* instance);
void assignment_update_matching_from_path(AssignmentInstance* instance);
void assignment_update_equality_graph(AssignmentInstance* instance);
int* assignment_solver(AssignmentInstance* instance);
int assignment_is_perfect_matching(AssignmentInstance* instance);
void print_assignment_equality_graph(AssignmentInstance* instance);
int assignment_calculate_total_cost(AssignmentInstance* instance);
void test_assignment_solver(void); 

// ============================================================================
// PROBLEMS
// ============================================================================

void hierholzer_euler_cycle(MatGraph* g, int start);
void test_hierholzer_algorithm(void);

#endif // BIPARTITE_MATCHING_H
