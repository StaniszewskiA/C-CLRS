#include <stdio.h> 
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 10
#define TASK 1

/*
14-1: Longest simple path in a DAG (Kahn's algorithm + DP)
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
14-2: Longest palindrome subsequence
*/

/*
14-3: Bitonic euclidean
*/

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
            break;

        case 3:
            // 14-3
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