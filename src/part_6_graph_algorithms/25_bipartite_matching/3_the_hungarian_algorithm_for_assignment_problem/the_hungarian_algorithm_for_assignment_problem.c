#include "part_6_graph_algorithms/25_bipartite_matching/bipartite_matching.h"

AssignmentInstance* assignment_init(int n) {
    if (n <= 0 || n >= MAX_GRAPH_VERTICES) {
        print_error("Invalid graphg size\n");
        return NULL;
    }

    AssignmentInstance* instance = (AssignmentInstance*)safe_malloc(sizeof(AssignmentInstance));

    instance->n = n;

    for (int i = 0; i < n; ++i) {
        instance->leftLabel[i] = 0;
        instance->rightLabel[i] = 0;
        instance->matching[i] = NIL;
        instance->matchedRight[i] = NIL;
        instance->visitedLeft[i] = 0;
        instance->visitedRight[i] = 0;
        instance->parentLeft[i] = NIL;
        instance->parentRight[i] = NIL; 

        for (int j = 0; j < n; ++j) {
            instance->cost[i][j] = 0;
        } 
    }

    return instance;
}

void assignment_set_cost(AssignmentInstance* instance, int i, int j, int cost) {
    if (i < 0 || i >= instance->n || j < 0 || j >= instance->n) {
        printf("assignment_set_cost: i=%d, j=%d, n=%d\n", i, j, instance ? instance->n : -1);
        print_error("Invalid params for cost setting\n");
        return;
    }

    instance->cost[i][j] = cost;
}

void assignment_free(AssignmentInstance* instance) {
    if (instance != NULL) safe_free(instance);
}

void print_assignment_instance(AssignmentInstance* instance) {
    if (instance == NULL) {
        print_error("Passed graph object is NULL\n");
        return;
    }

    printf("Cost matrix:\n");
    for (int i = 0; i < instance->n; ++i) {
        for (int j = 0; j < instance->n; ++j) {
            printf("%3d", instance->cost[i][j]);
        }
        printf("\n");
    }

    printf("Labels:\n");
    printf("Left labels: ");
    for (int i = 0; i < instance->n; ++i) {
        printf("%3d ", instance->leftLabel[i]);
    }
    printf("\n");

    printf("Right labels: ");
    for (int j = 0; j < instance->n; ++j) {
        printf("%3d ", instance->rightLabel[j]);
    }
    printf("\n");
}

void print_assignment_matching(AssignmentInstance* instance) {
    if (instance == NULL) {
        print_error("Passed graph object is NULL\n");
        return;
    }

    printf("Current matching: \n");
    for (int i = 0; i < instance->n; i++) {
        if (instance->matching[i] != NIL) {
            printf(
                "Left vertex %d -> Right vertex %d (cost: %d)\n",
                i, instance->matching[i], instance->cost[i][instance->matching[i]]
            );
        } else {
            printf("Left vertex %d -> unmatched\n", i);
        }
    }
}

void assignment_init_labels(AssignmentInstance* instance) {
    if (instance == NULL) {
        printf("Passed instance is NULL\n");
        return;
    }

    int n = instance->n;
    int i;

    for (i = 0; i < n; ++i) {
        instance->leftLabel[i] = NEG_INF;
        for (int j = 0; j < n; ++j) {
            if (instance->cost[i][j] > instance->leftLabel[i]) {
                instance->leftLabel[i] = instance->cost[i][j];
            }
        }
    }

    for (i = 0; i < n; ++i) {
        instance->rightLabel[i] = 0;
    }
}

int assignment_find_initial_matching(AssignmentInstance* instance) {
    int foundCnt = 0;
    int i;
    int n = instance->n;

    for (i = 0; i < n; ++i) {
        instance->matching[i] = NIL;
        instance->matchedRight[i] = NIL;    
    }

    for (i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (instance->cost[i][j] != instance->leftLabel[i] + instance->rightLabel[j]) continue; 
            if (instance->matchedRight[j] != NIL) continue;

            instance->matching[i] = j;
            instance->matchedRight[j] = i;
            foundCnt++;
            break;
        }
    }

    return foundCnt;
}

void assignment_update_matching_from_path(AssignmentInstance* instance) {
    int n = instance->n;
    int endRight = NIL;
    for (int j = 0; j < n; ++j) {
        if (instance->visitedRight[j] && instance->matchedRight[j] == NIL) {
            endRight = j;
            break;
        }
    }
    if (endRight == NIL) return;

    int currRight = endRight;
    while (currRight != NIL) {
        int currLeft = instance->parentRight[currRight];
        int nextRight = instance->matching[currLeft];
        instance->matching[currLeft] = currRight;
        instance->matchedRight[currRight] = currLeft;
        currRight = nextRight;
    }
}

void assignment_update_equality_graph(AssignmentInstance* instance) {
    int minSlack = INF;
    int i, j;
    int n = instance->n;

    for (i = 0; i < n; ++i) {
        if (!instance->visitedLeft[i]) continue;
        for (j = 0; j < n; ++j) {
            if (instance->visitedRight[j]) continue;
            int slack = instance->cost[i][j] - instance->leftLabel[i] - instance->rightLabel[j];
            if (slack < minSlack) minSlack = slack;
        }
    }

    if (minSlack == INF) return;
    for (i = 0; i < n; ++i) {
        if (instance->visitedLeft[i]) {
            instance->leftLabel[i] -= minSlack;
        }
    }
    for (j = 0; j < n; ++j) {
        if (instance->visitedRight[j]) {
            instance->rightLabel[j] += minSlack;
        }
    }
}

static int assignment_bfs_augmenting_path(
    AssignmentInstance* instance, 
    int* rootLeft
) {
    int n = instance->n;
    int queue[MAX_GRAPH_VERTICES];
    int front = 0;
    int rear = 0;
    int found = 0;
    int freeLeft = -1;
    int i;

    // Find a free left node
    for (i = 0; i < n; ++i) {
        if (instance->matching[i] == NIL) {
            freeLeft = i;
            break;
        }
    } 

    if (freeLeft == -1) return 0; // All matched
    *rootLeft = freeLeft;

    // Set up visited and parrent arrays
    for (i = 0; i < n; ++i) {
        instance->visitedLeft[i] = 0;
        instance->visitedRight[i] = 0;
        instance->parentLeft[i] = NIL;
        instance->parentRight[i] = NIL;
    }

    queue[rear++] = freeLeft;
    instance->visitedLeft[freeLeft] = 1;

    while (front != rear && !found) {
        int u = queue[front++];
        for (int v = 0; v < n; ++v) {
            if (instance->cost[u][v] != instance->leftLabel[u] + instance->rightLabel[v] ||
                instance->visitedRight[v]) continue;
            instance->parentRight[v] = u;
            instance->visitedRight[v] = 1;
            if (instance->matchedRight[v] == NIL) {
                found = 1;
                break;
            } else {
                int nextLeft = instance->matchedRight[v];
                if (instance->visitedLeft[nextLeft]) continue;
                queue[rear++] = nextLeft;
                instance->visitedLeft[nextLeft] = 1;
                instance->parentLeft[nextLeft] = v; 
            }
        }
    }

    return found;
}

int* assignment_solver(AssignmentInstance* instance) {
    assignment_init_labels(instance);
    assignment_find_initial_matching(instance);

    while (!assignment_is_perfect_matching(instance)) {
        int rootLeft = -1;
        int found = assignment_bfs_augmenting_path(instance, &rootLeft);
        if (found) {
            assignment_update_matching_from_path(instance);
        } else {
            assignment_update_equality_graph(instance);
        }
    }
    int* res = (int*)safe_malloc(instance->n * sizeof(int));
    for (int i = 0; i < instance->n; ++i)
        res[i] = instance->matching[i];
    return res;
}

int assignment_is_perfect_matching(AssignmentInstance* instance) {
    for (int i = 0; i < instance->n; ++i) 
        if (instance->matching[i] == NIL)
            return 0;
    return 1;
}

void print_assignment_equality_graph(AssignmentInstance* instance) { 
    printf("Equality graph (edges with cost[i][j] == leftLabel[i] + rightLabel[j]):\n");
    int n = instance->n;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) 
            if (instance->cost[i][j] == instance->leftLabel[i] + instance->rightLabel[j])  
                printf("(%d, %d)", i, j);
    }

    printf("\n");
}

int assignment_calculate_total_cost(AssignmentInstance* instance) {
    int total = 0;

    for (int i = 0; i < instance->n; ++i) {
        if (instance->matching[i] != NIL)
            total += instance->cost[i][instance->matching[i]];
    }

    return total;
}

void test_assignment_solver(void) {
    const char* testCaseTitle1 = "The assignment problem solved with the hungarian method";
    print_separator(testCaseTitle1);

    int n = 4;
    int costMat[4][4] = {
        {54, 54, 51, 53},
        {51, 57, 52, 52},
        {50, 53, 54, 56},
        {56, 54, 55, 53}
    };

    AssignmentInstance* instance = assignment_init(n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("Setting cost[%d][%d] = %d\n", i, j, costMat[i][j]);
            assignment_set_cost(instance, i, j, costMat[i][j]);
        }
    }

    assignment_init_labels(instance);

    printf("Original cost matrix:\n");
    print_assignment_instance(instance);

    int* optimalMatching = assignment_solver(instance);

    if (optimalMatching != NULL) {
        printf("\nOptimal Assignment:\n");
        int totalCost = 0;
        for (int i = 0; i < n; i++) {
            printf("Worker %d -> Job %d (cost: %d)\n",
                   i, optimalMatching[i], costMat[i][optimalMatching[i]]);
            totalCost += costMat[i][optimalMatching[i]];
        }
        printf("Total optimal cost: %d\n", totalCost);
        safe_free(optimalMatching);
    } else {
        printf("No matching found.\n");
    }

    assignment_free(instance);
    printf("\n");
}
