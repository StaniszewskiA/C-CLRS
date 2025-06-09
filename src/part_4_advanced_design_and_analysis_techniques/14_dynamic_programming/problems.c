#include "part_4_advanced_design_and_analysis_techniques/14_dynamic_programming/dynamic_programming.h"

#define TASK 1

AdjList graph[MAX_VERTICES];
int in_degrees[MAX_VERTICES];
int topo_order[MAX_VERTICES];
int dp[MAX_VERTICES];
int idxMap[MAX_EMPLOYEES];
Employee *employees[MAX_EMPLOYEES];
int dp9[MAX_M9][MAX_M9];
int breakSeq[MAX_M9][MAX_M9];
int breaks[MAX_M9];

/*
14-1: Longest simple path in a DAG (Kahn's algorithm + DP)

Time: O(|V| + |E|)
*/
void graph_add_edge(int u, int v, int w) {
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

int longest_path_in_dag(int n, int s, int t) {
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

// Euclidean distance between two points.
double euc_dist(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

// Sort based on euclidean distance
int compare_points(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    // Return 1, 0 or -1
    return (p1->x > p2->x) - (p1->x < p2->x);
}

void bitonic_tsp(Point points[], int n) {
    // O(n*log(n))
    qsort(points, n, sizeof(Point), compare_points);

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

O(n)
*/
int employee_count = 0;

Employee* employee_create(const char* name, double conviviality) {
    Employee* emp = (Employee*)malloc(sizeof(Employee));
    strcpy(emp->name, name);
    emp->conviviality = conviviality;
    emp->leftChild = NULL;
    emp->rightSibling = NULL;
    employees[employee_count] = emp;
    idxMap[employee_count] = employee_count;
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
ViterbiVertex* viterbi_vertex_create(int id, int edgeCount) {
    ViterbiVertex* vertex = (ViterbiVertex*)malloc(sizeof(ViterbiVertex));
    vertex->id = id;
    vertex->edgeCount = edgeCount;
    vertex->edges = (ViterbiEdge*)malloc(sizeof(ViterbiEdge) * edgeCount);
    printf("Created vertex with id %d and edge count of %d\n", id, edgeCount);
    return vertex;
}

void viterbi_edge_add(
    ViterbiVertex* from, 
    int dest, 
    int sigma, 
    double proba, 
    int edgeIdx
) {
    from->edges[edgeIdx].dest = dest;
    from->edges[edgeIdx].sigma = sigma;
    from->edges[edgeIdx].proba = proba;
    printf(
        "Created edge with id %d leading from vertex %d to vertex %d. "
        "Edge has sigma value of %d and transition probability of %f.\n",
        edgeIdx, from->id, dest, sigma, proba
    );    
}

ViterbiSolution viterbi(
    ViterbiVertex **graph, 
    int numNodes, 
    int *sigma, 
    int sigmaLen, 
    int v0
) {
    // Base case - empty sigma seq
    if (sigmaLen == 0) {
        ViterbiSolution result = {NULL, 0, 1.0}; 
        result.seq = (int*)malloc(sizeof(int)); // Only the current state
        result.seq[0] = v0;
        result.seqLen = 1;
        return result;
    }

    // Init solution with no sequence and zero proba
    ViterbiSolution result = {NULL, 0, 0};

    for (int i = 0; i < graph[v0]->edgeCount; i++) {
        ViterbiEdge currEdge = graph[v0]->edges[i];

        // Find path with matching sigma
        if (currEdge.sigma == sigma[0]) {
            ViterbiSolution res = viterbi(
                graph, 
                numNodes, 
                sigma + 1, 
                sigmaLen - 1, 
                currEdge.dest
            );

            // Update the solution if we find better proba
            double newProba = currEdge.proba * res.proba;
            if (newProba > result.proba) { 
                int *newSeq = (int*)malloc(sizeof(int) * (res.seqLen + 1));
                if (newSeq) {
                    newSeq[0] = v0;
                    memcpy(newSeq + 1, res.seq, sizeof(int) * res.seqLen);
                    free(result.seq);
                    result.seq = newSeq;
                    result.seqLen = res.seqLen + 1;
                }
                result.proba = newProba;
            }            
        }
    }

    return result;
}

/*
14-8: Image compression by seam carving
*/
void seam_init(Seam* seam, int capacity) {
    seam->pixels = (Pixel*)malloc(sizeof(Pixel) * capacity);
    seam->size = 0;
    seam->capacity = capacity;
}

void add_to_seam(Seam* seam, int row, int col) {
    if (seam->size == seam->capacity) {
        seam->capacity *= 2;
        seam->pixels = (Pixel *)realloc(seam->pixels, sizeof(Pixel) * seam->capacity);
    }
    seam->pixels[seam->size].row = row;
    seam->pixels[seam->size].col = col;
    seam->size++;
}

void seam_free(Seam* seam) {
    free(seam->pixels);
}

void seam_carving(int **d, int m, int n) {
    int D[MAX_M][MAX_N];
    Seam S[MAX_M][MAX_N];
    int seamCap = 10;

    printf("Initializing...");
    // Init first rows.
    for (int i = 0; i < n; i++) {
        D[0][i] = d[0][i];
        seam_init(&S[0][i], seamCap);
        add_to_seam(&S[0][i], 0, i);
    }

    for (int i = 1; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int prevVal;
            Seam prevSeam;

            if (j == 0) { // Left edge case
                if (D[i - 1][j] < D[i - 1][j + 1]) {
                    prevVal = D[i - 1][j];
                    prevSeam = S[i - 1][j];
                } else {
                    prevVal = D[i - 1][j + 1];
                    prevSeam = S[i - 1][j + 1];
                }
            }
            else if (j == n - 1) { // Right edge case
                if (D[i - 1][j - 1] < D[i - 1][j]) {
                    prevVal = D[i - 1][j - 1];
                    prevSeam = S[i - 1][j - 1]; 
                } else {
                    prevVal = D[i - 1][j];
                    prevSeam = S[i - 1][j];  
                }
            }
            else {
                int minVal = min_of_three(
                    D[i - 1][j - 1],
                    D[i - 1][j],
                    D[i - 1][j + 1]
                );
                if (minVal == D[i - 1][j - 1]) {
                    prevVal = D[i - 1][j - 1];
                    prevSeam = S[i - 1][j - 1];  // Seam from left diagonal
                } else if (minVal == D[i - 1][j]) {
                    prevVal = D[i - 1][j];
                    prevSeam = S[i - 1][j];  // Seam from above
                } else {
                    prevVal = D[i - 1][j + 1];
                    prevSeam = S[i - 1][j + 1];  // Seam from right diagonal
                }
            }

            D[i][j] = prevVal + d[i][j];
            S[i][j] = prevSeam;
            add_to_seam(&S[i][j], i, j);
        }
    }

    int q = 0;
    for (int j = 1; j < n; j++) {
        if (D[m - 1][j] < D[m - 1][q]) q = j;
    }

    printf("Optimal seam: \n");
    for (int i = 0; i < m; i++) 
        printf("(%d, %d)\n", S[i][q].pixels[i].row, S[i][q].pixels[i].col);

    printf("Freeing up the seam...\n");
    for (int i = 0; i < m; i++) seam_free(&S[i][q]);
}

/*
14-9: Breaking a string
*/
int break_string(int L[], int i, int j, int l, int r) {
    if (i >= j) return 0;
    if (dp9[i][j] != -1) return dp9[i][j];

    int minCost = INF9; 
    int minIdx = -1;

    for (int k = i; k < j; k++) {
        int leftCost = break_string(L, i, k, l, L[k]);
        int rightCost = break_string(L, k + 1, j, L[k], r);

        printf("leftCost at k=%d: %d\n", k, leftCost);
        printf("rightCost at k=%d: %d\n", k, rightCost);

        if (leftCost < INF9 && rightCost < INF9) {  
            int cost = (r - l) + leftCost + rightCost;
            printf("Evaluating cut at L[k]=%d, cost: %d\n", L[k], cost);

            if (cost < minCost) {
                minCost = cost;
                minIdx = k;
            }
        }
    }

    dp9[i][j] = minCost;
    breakSeq[i][j] = minIdx;
    return minCost;
}


void reconstruct_break_seq(int i, int j) {
    if (i >= j) return;
    int k = breakSeq[i][j];
    if (k == -1) return;
    printf("%d ", breaks[k]);
    reconstruct_break_seq(i, k);
    reconstruct_break_seq(k + 1, j);
}

/*
14-10: Planning an investment strategy
*/
void invest(
    int r[YEARS + 1][YEARS + 1], 
    int dr[YEARS + 1][YEARS + 1], 
    int fees[2], 
    int n, 
    int I[YEARS + 1], 
    int R[YEARS + 1]
) {
    int k, i;

    for (k = 1; k <= YEARS; k++) {
        I[k] = 0;
        R[k] = 0;
    }

    for (k = YEARS; k >= 1; k--) {
        int q = 1;

        // Find the investment with the highest return for year k.
        for (i = 1; i <= n; i++) {
            if (r[i][k] > r[q][k]) q = i;
        }

        // Check if it is better to not move the money.
        if (R[k + 1] + dr[I[k + 1]][k] - fees[1] > R[k + 1] + dr[q][k] - fees[2]) {
            R[k] = R[k + 1] + dr[I[k + 1]][k] - fees[1];
            I[k] = I[k + 1];
        } else {
            R[k] = R[k + 1] + dr[q][k] - fees[2];
            I[k] = q;
        }
    }

    printf("Optimal Investment Strategy: ");
    for (k = 1; k <= YEARS; k++) {
        printf("%d ", I[k]);
    }
    printf("\nTotal Return: %d\n", R[1]);
}

/*
14-11: Inventory planning

O(nD^2)
*/
void inventory_planning(int n, int m, int c, int* demand, int* inventoryCost) {
    int D = 0;
    for (int i = 0; i < n; i++) D += demand[i];
    
    int dp[n + 1][D + 1];
    int i, j, k;

    for (i = 0; i <= n; i++) {
        for (j = 0; j <= D; j++) dp[i][j] = INF;
    }

    // Base case
    dp[0][0] = 0;

    for (i = 1; i <= n; i++) {
        for (j = 0; j <= D; j++) {
            if (dp[i - 1][j] != INF) { // Process if previous state is valid.
                for (k = 0; k <= D; k++) {
                    if (k < demand[i - 1]) continue;
                    int newInv = j + k - demand[i - 1];
                    if (newInv > D) continue;

                    int partTimeCost = (k > m) ? c * (k - m) : 0;
                    int totalCost = dp[i - 1][j]
                        + partTimeCost
                        + inventoryCost[newInv];

                    if (totalCost < dp[i][newInv]) dp[i][newInv] = totalCost;
                }
            }
        }
    }

    int result = INF;
    for (j = 0; j <= D; j++) {
        if (dp[n][j] < result) result = dp[n][j];
    }

    printf("Minimum cost to fulfill demand: %d\n", result);
}

/*
14-12: Signing free-agent baseball players

n - number of players
B - budget
P - players per position

O(NBP)
*/
void sign_players(int n, int B, int P, Player players[n][P]) {    
    int dp[n + 1][B + 1];
    int i, j, k;

    for (i = 0; i <= n; i++) {
        for (j = 0; j <= B; j++) dp[i][j] = 0;
    } 
    printf("DP table initialized");

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= B; j++) {
            dp[i][j] = dp[i - 1][j]; // Sign last player just in case.

            // Try to sign a player
            for (k = 0; k < P; k++) {
                if (j >= players[i - 1][k].cost) {
                    int newWar = dp[i - 1][j 
                        - players[i - 1][k].cost]
                        + players[i - 1][k].war;
                    if (newWar > dp[i][j]) dp[i][j] = newWar;
                }
            }
        }
    }

    printf("The total WAR is %d\n", dp[n][B]);

    // Reconstruct chosen players
    int totalCost = 0;
    int playerCost = 0;
    j = B;
    printf("The players selected are:\n");

    for (i = n; i > 0; i--) {
        for (k = 0; k < P; k++) {
            if (j >= players[i - 1][k].cost 
                && dp[i][j] == dp[i - 1][j - players[i - 1][k].cost] 
                    + players[i - 1][k].war
            ) {
                printf("Position %d: Player with cost %d and WAR %d\n", 
                    players[i - 1][k].pos, players[i - 1][k].cost, players[i - 1][k].war);
                playerCost = players[i - 1][k].cost;
                j -= playerCost;
                totalCost += playerCost;
                break;
            }
        }
    }

    printf("The total cost is %d\n", totalCost);
}

int main(void) {
    switch (TASK)
    {
        case 1:
            // 14-1
            int n = 6;
            for (int i = 0; i < n; i++) graph[i].size = 0, in_degrees[i] = 0;

            graph_add_edge(0, 1, 5);
            graph_add_edge(0, 2, 3);
            graph_add_edge(1, 3, 6);
            graph_add_edge(1, 2, 2);
            graph_add_edge(2, 4, 4);
            graph_add_edge(2, 5, 2);
            graph_add_edge(2, 3, 7);
            graph_add_edge(3, 5, 1);
            graph_add_edge(4, 5, 3);

            int s = 0, t = 5;
            int result = longest_path_in_dag(n, s, t);

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
            Employee* president = employee_create("President", 10);
            Employee* manager1 = employee_create("Manager1", 5);
            Employee* manager2 = employee_create("Manager2", 6);
            Employee* worker1 = employee_create("Worker1", 4);
            Employee* worker2 = employee_create("Worker2", 7);
            Employee* worker3 = employee_create("Worker3", 3);
            
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
            ViterbiVertex* graph[3]; 

            graph[0] = viterbi_vertex_create(0, 2);
            graph[1] = viterbi_vertex_create(1, 1);  
            graph[2] = viterbi_vertex_create(2, 0);

            viterbi_edge_add(graph[0], 1, 1, 0.9, 0);  
            viterbi_edge_add(graph[0], 2, 2, 0.8, 1);  
            viterbi_edge_add(graph[1], 2, 1, 0.7, 0);  

            int sigma[] = {1, 1}; 

            ViterbiSolution viterbiResult = viterbi(graph, 3, sigma, 2, 0);

            if (viterbiResult.seq != NULL) {
                printf("Best sequence: ");
                for (int i = 0; i < viterbiResult.seqLen; i++) {
                    printf("%d ", viterbiResult.seq[i]);
                }
                printf("\nProbability: %lf\n", viterbiResult.proba);
            } else {
                printf("No valid path found.\n");
            }

            for (int i = 0; i < 3; i++) {
                free(graph[i]->edges);
                free(graph[i]);
            }
            free(viterbiResult.seq);

            break;

        case 8:
            // 14-8
            int m8 = 5, n8 = 6;

            int **A8 = (int **)malloc(m8 * sizeof(int *));
            for (int i = 0; i < m8; i++) {
                A8[i] = (int *)malloc(n8 * sizeof(int));
            }

            int values[5][6] = {
                {1, 2, 3, 4, 5, 6},
                {2, 3, 4, 5, 6, 7},
                {3, 4, 5, 6, 7, 8},
                {4, 5, 6, 7, 8, 9},
                {5, 6, 7, 8, 9, 10}
            };

            for (int i = 0; i < m8; i++) {
                for (int j = 0; j < n8; j++) {
                    A8[i][j] = values[i][j];
                }
            }

            seam_carving(A8, m8, n8);

            break;

        case 9:
            // 14-9
            int n9 = 10;
            int m9 = 3;
            int L9[] = {0, 3, 7, 10};

            for (int i = 0; i < MAX_M9; i++) {
                for (int j = 0; j < MAX_M9; j++) {
                    dp9[i][j] = -1;
                    breakSeq[i][j] = -1;
                }
            }

            for (int i = 0; i < m9; i++) breaks[i] = L9[i + 1];

            int minCost = break_string(L9, 0, m9 + 1, 0, n9);
            printf("Minimum Cost: %d\n", minCost);
            printf("Cut Sequence: ");
            reconstruct_break_seq(0, m9 + 1);
            printf("\n");

            break;

        case 10:
            // 14-10
            int r10[YEARS+1][YEARS+1];
            int dr10[YEARS+1][YEARS+1];
            int f10[2] = { 10, 20 }; 
            int I10[YEARS+1]; 
            int R10[YEARS+1]; 
            int n10 = 5; 

            invest(r10, dr10, f10, n10, I10, R10);

            break;

        case 11:
            // 14-11
            int n11 = 3; // Number of months
            int m11 = 5; // Max production per month by full-time staff
            int c11 = 10; // Cost per machine produced with part-time labor

            int demand[] = {3, 6, 2};
            int inventoryCost[] = {0, 1, 2, 3, 4, 5, 6}; 

            inventory_planning(n11, m11, c11, demand, inventoryCost);

            break;

        case 12:
            // 14-12
            int n12 = 3;
            int x12 = 10; // in $100.000
            int p12 = 3;

            Player players[3][3] = {
                {{2, 8, 0}, {4, 12, 0}, {3, 10, 0}}, 
                {{3, 6, 1}, {2, 5, 1}, {6, 15, 1}}, 
                {{5, 10, 2}, {7, 13, 2}, {4, 9, 2}}  
            };

            sign_players(n12, x12, p12, players);

            break;
        
        default:
            break;
    }
}