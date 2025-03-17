#include <stdio.h> 
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <float.h>

#define TASK 6

/*
14-1: Longest simple path in a DAG (Kahn's algorithm + DP)

Time: O(|V| + |E|)
*/
#define MAX_VERTICES 10

typedef struct Edge {
    int dest, weight;
} Edge;

typedef struct AdjList {
    Edge edges[MAX_VERTICES];
    int size;
} AdjList;

AdjList graph[MAX_VERTICES];
int in_degrees[MAX_VERTICES];
int topo_order[MAX_VERTICES];
int dp[MAX_VERTICES];

void add_edge(int u, int v, int w) {
    graph[u].edges[graph[u].size].dest = v;
    graph[u].edges[graph[u].size].weight = w;
    graph[u].size++;
    in_degrees[v]++;
}

// Topological sort using Kahn's algorithm
int topological_sort(int n) {
    int queue[MAX_VERTICES], front = 0, rear = 0;
    /*
    Find vertices with an in-degree of 0. 
    They will serve as starting points.
    */
    for (int i = 0; i < n; i++) {
        if (in_degrees[i] == 0) queue[rear++] = i;
    }

    // Construct topological ordering.
    int idx = 0;
    while (front < rear) {
        int node = queue[front++];
        topo_order[idx++] = node;
        /*
        Decrease in-degrees of vertices connected to retrieved node.
        */
        for (int i = 0; i < graph[node].size; i++) {
            int nei = graph[node].edges[i].dest;
            /*
            If the in-degree is 0, add the neighbor to the front of the queue.
            */
            if (--in_degrees[nei] == 0) queue[rear++] = nei;
        }
    }
    // Were all the nodes visited?
    return idx == n;
}

int longest_path_dag(int n, int s, int t) {
    // Check if the graph is in fact acyclic.
    if (!topological_sort(n)) return INT_MIN;

    // Init dp.
    for (int i = 0; i < n; i++) dp[i] = INT_MIN;
    dp[t] = 0; // Base case.

    // Reverse topological order
    for (int i = n - 1; i >= 0; i--) {
        int vertex = topo_order[i];
        for (int j = 0; j < graph[vertex].size; j++) {
            int nei = graph[vertex].edges[j].dest;
            int weight = graph[vertex].edges[j].weight;
            /*
                Recursive formula:
                longest(G, v, t) = max((v, v')) + longest(G, v', t)
            */
            if (dp[nei] != INT_MIN) {
                dp[vertex] = (dp[vertex] > weight + dp[nei])
                    ? dp[vertex]
                    : weight + dp[nei];
            }
        }
    }

    // Does the longest path exist?
    return dp[s] == INT_MIN ? -1 : dp[s];
}

/*
14-2: Longest palindrome subsequence (LCS)

Time: O(n^2)
*/
void longest_palindrome_subseq(char *s) {
    int n = strlen(s);
    int dp[n][n];

    // Single character is a palindrome of length 1. O(n)
    for (int i = 0; i < n; i++) dp[i][i] = 1;

    // Filling the DP.
    for (int len = 2; len <= n; len++) { // O(n)
        for (int i = 0; i <= n - len; i++) { // O(n)
            int j = i + len - 1;
            if (s[i] == s[j] && len == 2) dp[i][j] = 2;
            else if (s[i] == s[j]) dp[i][j] = 2 + dp[i + 1][j - 1];
            /*
                Recursive formula:
                LPS(i, j) = max(LPS(i + 1, j), LPS(i, j - 1))
            */
            else dp[i][j] = fmax(dp[i + 1][j], dp[i][j - 1]);
        }
    }

    // Length of the LPS.
    int lps_length = dp[0][n - 1];

    // Reconstruct the result (two pointers).
    char *lps = (char *)malloc((lps_length + 1) * sizeof(char));
    if (!lps) {
        printf("Memory allocation failed!\n");
        return;
    }
    lps[lps_length] = '\0';
    
    int i = 0;
    int j = n - 1;
    int start_idx = 0;
    int end_idx = lps_length - 1;

    while (i <= j) {
        if (s[i] == s[j]) {
            lps[start_idx++] = s[i];
            lps[end_idx--] = s[j];
            i++;
            j--;
        } 
        else if (dp[i + 1][j] > dp[i][j - 1]) i++;
        else j--;
    }

    printf("LPS: %s\n", lps);
}

/*
14-3: Bitonic euclidean

Sort the points based on their x coordinate, store
backtrack paths.
*/
typedef struct Point {
    double x, y;
} Point;

// Euclidean distance between two points.
double euc_dist(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

// Sort based on euclidean distance
int compare(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    // Return 1, 0 or -1
    return (p1->x > p2->x) - (p1->x < p2->x);
}

void bitonic_tsp(Point points[], int n) {
    // O(n*log(n))
    qsort(points, n, sizeof(Point), compare);

    // DP for minimum costs.
    double dp[n][n];
    int path[n][n];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) 
            dp[i][j] = DBL_MAX;

    // Base case
    dp[0][1] = euc_dist(points[0], points[1]);

    // Fill the DP (O(n^2))
    for (int j = 2; j < n; j++) {
        for (int i = 0; i < j; i++) {
            if (i == j - 1) {
                // Use intermediate point k
                double min_cost = DBL_MAX;
                int best_k = -1;
                for (int k = 0; k < i; k++) {
                    double cost = dp[k][i] + euc_dist(points[k], points[j]);
                    if (cost < min_cost) {
                        min_cost = cost;
                        best_k = k;
                    }
                }
                dp[i][j] = min_cost;
                path[i][j] = best_k;
            } else {
                // Rightmost extension
                dp[i][j] = dp[i][j - 1] + euc_dist(points[j - 1], points[j]);
                path[i][j] = j - 1;
            }
        }
    }

    double min_cost = DBL_MAX;
    int best_i = -1;

    for (int i = 0; i < n - 1; i++) {
        double cost = dp[i][n - 1] + euc_dist(points[i], points[n - 1]);
        if (cost < min_cost) {
            min_cost = cost;
            best_i = i;
        }
    }

    printf("Minimum Bitonic Tour Cost: %lf\n", min_cost);

    printf("Bitonic Tour: ");
    int tour[n];
    int idx = 0;
    tour[idx++] = best_i;

    for (int j = n - 1; j > best_i; j = path[best_i][j]) tour[idx++] = j;
    
    tour[idx++] = n - 1;

    for (int i = 0; i < idx; i++) {
        printf("(%lf, %lf) ", points[tour[i]].x, points[tour[i]].y);
    }
    printf("\n");
}
/*
14-4: Printing neatly

Just DP.
O(n^3).
*/
#define MAX_LINE_WIDTH 10

void print_neatly(int *lengths, int n) {
    int C[n + 1], P[n + 1];

    for (int i = 0; i <= n; i++) {
        C[i] = pow(MAX_LINE_WIDTH, 2); // Instead of INT_MAX to avoid overflow.
        P[i] = -1;
    }
    // Base case
    C[n] = 0;

    for (int k = n - 1; k >= 0; k--) {
        int total_len = 0;
        // Try placing j-th word on the current line.
        for (int j = 0; k + j < n; j++) {
            total_len += lengths[k + j] + (j > 0); // Spaces between lines.
            if (total_len > MAX_LINE_WIDTH) break;

            int diff = MAX_LINE_WIDTH - total_len;
            int diffSquared = pow(diff, 3);
            int cost = diffSquared + C[k + j + 1];

            printf("Total len: %d, diff: %d, diff squared: %d, cost: %d\n", 
                total_len, diff, diffSquared, cost);

            if (cost < C[k]) {
                C[k] = cost;
                P[k] = k + j + 1;
            }

            printf("%d\n", C[k]);
        }
    }

    int i = 0;
    while (i < n) {
        printf("Line: ");
        for (int j = i; j < P[i]; j++) printf("%d ", j + 1);  
        printf("\n");
        i = P[i];
    }

    printf("Executed properly");
}


/*
14-5: Edit distance

Time: O(m*n), where:
    - m = len of first seq,
    - n = len of second seq,

Space: O(m*n), same as time.

We need only the previous row.
*/
#define INF (INT_MAX / 2)

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

void edit_distance(char *x, char *y) {
    int m = strlen(x);
    int n = strlen(y);
    
    int *prev = (int*)malloc((n + 1) * sizeof(int));
    int *curr = (int*)malloc((n + 1) * sizeof(int));
    Operation *ops = (Operation *)malloc((m + 1) * (n + 1) * sizeof(Operation));

    if (!prev || !curr || !ops) {
        fprintf(stderr, "Malloc failed\n");
        free(prev);
        free(curr);
        free(ops);
        return;
    }

    // Base case
    for (int j = 0; j <= n; j++) prev[j] = j * COST_INSERT;
    for (int i = 0; i <= m; i++) ops[i * (n + 1)] = COST_DELETE;

    for (int i = 1; i <= m; i++) {
        curr[0] = i * COST_DELETE;
        for (int j = 1; j <= n; j++) {
            int cost = INF;
            Operation op = NONE;

            // Copy
            if (x[i - 1] == y[j - 1]) {
                cost = prev[j - 1] + COST_COPY;
                op = COPY;
            }
            // Replace
            if (cost > prev[j - 1] + COST_REPLACE) {
                cost = prev[j - 1] + COST_REPLACE;
                op = REPLACE;
            }
            // Delete
            if (cost > prev[j] + COST_DELETE) {
                cost = prev[j] + COST_DELETE;
                op = DELETE;
            }
            // Insert
            if (cost > curr[j - 1] + COST_INSERT) {
                cost = curr[j - 1] + COST_INSERT;
                op = INSERT;
            }

            curr[j] = cost;
            ops[i * (n + 1) + j] = op;
        }
        int *temp = prev;
        prev = curr;
        curr = temp;
    }

    // Reconstruct
    int i = m, j = n;
    while (i > 0 || j > 0) {
        switch (ops[i * (n + 1) + j]) {
            case COPY:
                printf("COPY %c\n", x[i - 1]);
                i--; j--;
                break;
            case REPLACE:
                printf("REPLACE %c -> %c\n", x[i - 1], y[j - 1]);
                i--; j--;
                break;
            case DELETE:
                printf("DELETE %c\n", x[i - 1]);
                i--;
                break;
            case INSERT:
                printf("INSERT %c\n", y[j - 1]);
                j--;
                break;
            default:
                break;
        }
    }

    free(prev);
    free(curr);
    free(ops);
}

/*
14-6: Planning a company party
*/
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

int idx_map[MAX_EMPLOYEES];
Employee *employees[MAX_EMPLOYEES];
int employee_count = 0;

Employee* create_employee(const char* name, double conviviality) {
    Employee* emp = (Employee*)malloc(sizeof(Employee));
    strcpy(emp->name, name);
    emp->conviviality = conviviality;
    emp->leftChild = NULL;
    emp->rightSibling = NULL;
    employees[employee_count] = emp;
    idx_map[employee_count] = employee_count;
    return emp;
}

double max_convivality(Employee* root, DPResult* dp, int idx) {
    if (!root) return 0;
    
    double exclude_root = 0, include_root = root->conviviality;
    Employee *child = root->leftChild;
    
    while (child) {
        exclude_root += max_convivality(child, dp, idx + 1);
        
        Employee *grandchild = child->leftChild;
        while (grandchild) {
            include_root += max_convivality(grandchild, dp, idx + 2);
            grandchild = grandchild->rightSibling;
        }
        
        child = child->rightSibling;
    }
    
    dp->C[idx] = fmax(exclude_root, include_root);
    dp->included[idx] = (exclude_root > include_root) ? 0 : 1;
    
    return dp->C[idx];
}

void print_guest_list(Employee* root, DPResult* dp, int idx) {
    if (!root) return;
    
    if (dp->included[idx]) {
        printf("%s\n", root->name);
        Employee *child = root->leftChild;
        while (child) {
            print_guest_list(child->leftChild, dp, idx + 2);
            child = child->rightSibling;
        }
    } else {
        Employee *child = root->leftChild;
        while (child) {
            print_guest_list(child, dp, idx + 1);
            child = child->rightSibling;
        }
    }
}


/*
14-7: Viterbi algorithm
*/

/*
14-8: Image compression by seam carving
*/

/*
14-9: Breaking a string
*/

/*
14-11: Inventory planning
*/

/*
14-12: Signing free-agent baseball players
*/

// Driver code
int main(void) {
    switch (TASK)
    {
        case 1:
            // 14-1
            int n = 6;
            for (int i = 0; i < n; i++) graph[i].size = 0, in_degrees[i] = 0;

            add_edge(0, 1, 5);
            add_edge(0, 2, 3);
            add_edge(1, 3, 6);
            add_edge(1, 2, 2);
            add_edge(2, 4, 4);
            add_edge(2, 5, 2);
            add_edge(2, 3, 7);
            add_edge(3, 5, 1);
            add_edge(4, 5, 3);

            int s = 0, t = 5;
            int result = longest_path_dag(n, s, t);

            if (result == -1) printf("No path from %d to %d\n", s, t);
            else printf("Longest path weight from %d to %d: %d\n", s, t, result);

            break;

        case 2:
            // 14-2
            char target[] = "character";
            longest_palindrome_subseq(target);

            break;

        case 3:
            // 14-3
            Point points[] = {
                {0, 0}, {1, 2}, {2, 1}, {3, 5}, {4, 3}, {5, 2}, {6, 4}
            };
            int num_points = sizeof(points) / sizeof(points[0]);

            bitonic_tsp(points, num_points);

            break;

        case 4:
            // 14-4
            int lengths[] = {3, 2, 2, 5, 4, 3};
            int num_lines = sizeof(lengths) / sizeof(lengths[0]);

            print_neatly(lengths, num_lines);
            break;

        case 5:
            // 14-5
            char x[] = "algorithm";
            char y[] = "algebra";
            edit_distance(x, y);

            break;

        case 6:
            // 14-6
            Employee* president = create_employee("President", 10);
            Employee* manager1 = create_employee("Manager1", 5);
            Employee* manager2 = create_employee("Manager2", 6);
            Employee* worker1 = create_employee("Worker1", 4);
            Employee* worker2 = create_employee("Worker2", 7);
            Employee* worker3 = create_employee("Worker3", 3);
            
            president->leftChild = manager1;
            manager1->rightSibling = manager2;
            manager1->leftChild = worker1;
            manager2->leftChild = worker2;
            worker2->rightSibling = worker3;
            
            DPResult dp;
            memset(&dp, 0, sizeof(dp));
            
            printf("Maximum conviviality: %.2f\n", 
                max_convivality(president, &dp, 0));
            printf("Guest List:\n");
            print_guest_list(president, &dp, 0);

            break;

        case 7:
            // 14-7
            break;

        case 8:
            // 14-8
            break;

        case 9:
            // 14-9
            break;

        case 10:
            // 14-10
            break;

        case 11:
            // 14-11
            break;

        case 12:
            // 14-12
            break;
        
        default:
            break;
    }
}