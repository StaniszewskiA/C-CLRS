#include <stdio.h> 
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <float.h>

#define MAX_VERTICES 10
#define TASK 3

/*
14-1: Longest simple path in a DAG (Kahn's algorithm + DP)

Time: O(|V| + |E|)
*/
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
*/

/*
14-5: Edit distance
*/

/*
14-6: Planning a company party
*/

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
            break;

        case 5:
            // 14-5
            break;

        case 6:
            // 14-6
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