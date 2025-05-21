#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TASK 2

#pragma region Graph utils

#define MAX_VERTICES 10
#define MAX_EDGES 100

typedef struct MatGraph {
    int adjMat[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
} MatGraph;

MatGraph* mat_graph_create(int numVertices) {
    MatGraph* g = malloc(sizeof(MatGraph));
    g->numVertices = numVertices;

    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) g->adjMat[i][j] = 0;
    }

    return g;
}

void mat_graph_free(MatGraph* g) {
    free(g);
}

void mat_graph_add_undirected_edge(MatGraph* g, int u, int v, int weight) {
    g->adjMat[u][v] = weight;
    g->adjMat[v][u] = weight;
}

void mat_graph_remove_undirected_edge(MatGraph* g, int u, int v) {
    g->adjMat[u][v] = 0;
    g->adjMat[v][u] = 0;
}

void mat_graph_add_directed_edge(MatGraph* g, int u, int v, int weight) {
    g->adjMat[u][v] = weight;
}

void mat_graph_remove_directed_edge(MatGraph* g, int u, int v, int weight) {
    g->adjMat[u][v] = 0;
}

void print_path(int pred[], int dest) {
    if (dest == -1) return;
    if (pred[dest] != -1) {
        print_path(pred, pred[dest]);
        printf(" -> ");
    }
    printf("%d", dest);
}

void print_solution(int dist[], int pred[], int numVertices, int src) {
    printf("Shortest paths from source %d:\n", src);
    for (int i = 0; i < numVertices; i++) {
        if (i != src) {
            printf("To vertex %d: ", i);
            if (dist[i] == INT_MAX) {
                printf("No path exists\n");
            } else {
                printf("Distance = %d, Path: ", dist[i]);
                print_path(pred, i);
                printf("\n");
            }
        }
    }
}

#pragma endregion Graph utils

#pragma region 22-1 Yens improvement to Bellman-Ford

#define INF INT_MAX 

void init_single_source(int dist[], int pred[], int numVertices, int src) {
    for (int i = 0; i < numVertices; i++) {
        dist[i] = INF;
        pred[i] = -1;
    }
    dist[src] = 0;
}

void relax_edge(int u, int v, int weight, int dist[], int pred[]) {
    if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
        dist[v] = dist[u] + weight;
        pred[v] = u;
    }
}

void yens_bellman_ford(MatGraph* g, int src, int dist[], int pred[]) {
    int n = g->numVertices;
    init_single_source(dist, pred, n, src);

    int passes = (n + 1) / 2;

    for (int pass = 0; pass < passes; pass++) {
        // Forward pass
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (g->adjMat[i][j] != 0) 
                    relax_edge(i, j, g->adjMat[i][j], dist, pred);
            }
        }

        // Backward pass
        for (int i = n - 1; i >= 0; i--) {
            for (int j = 0; j < i; j++) {
                if (g->adjMat[i][j] != 0)
                    relax_edge(i, j, g->adjMat[i][j], dist, pred);
            }
        }
    }
}

#pragma endregion 22-1 Yens improvement to Bellman-Ford

#pragma region 22-2 Nesting boxes

int compare_ints(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int nests_inside(int dims1[], int dims2[], int d) {
    int sortedBox1[MAX_VERTICES];
    int sortedBox2[MAX_VERTICES];

    memcpy(sortedBox1, dims1, d * sizeof(int));
    memcpy(sortedBox2, dims2, d * sizeof(int));
    qsort(sortedBox1, d, sizeof(int), compare_ints);
    qsort(sortedBox2, d, sizeof(int), compare_ints);

    for (int i = 0; i < d; i++)
        if (sortedBox1[i] >= sortedBox2[i]) return 0;
    
    return 1;
}

/*
    Sorting dimensions: O(nd*lg(d))
    Checking nesting for each pair: O(n^2)
    Finding the longest path: O(n^2)

    Overall: O(nd*max(lg(d), n))
*/
void find_longest_nesting_seq(int boxes[][MAX_VERTICES], int n, int d) {
    int nestingGraph[MAX_VERTICES][MAX_VERTICES] = {0};
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && nests_inside(boxes[i], boxes[j], d)) {
                nestingGraph[i][j] = 1;
                printf("Box %d nests inside Box %d\n", i, j);
            }
        } 
    }

    int dp[MAX_VERTICES];
    int pred[MAX_VERTICES];

    for (int i = 0; i < n; i++) {
        dp[i] = 1;
        pred[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (nestingGraph[i][j] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                pred[i] = j;
            }
        }
    }

    int maxIdx = 0;
    for (int i = 1; i < n; i++)
        if (dp[i] > dp[maxIdx]) maxIdx = i;

    printf("Length of the longest nesting seq: %d\n", dp[maxIdx]);
    
    int seq[MAX_VERTICES];
    int len = dp[maxIdx];
    int curr = maxIdx;
    for (int i = len - 1; i >= 0; i--) {
        seq[i] = curr;
        curr = pred[curr];
    }

    for (int i = 0; i < len; i++) {
        printf("Box %d", seq[i]);
        if (i < len - 1) printf(" -> ");
    }
    printf("\n\n");

    printf("Box dimensions in the seq:\n");
    for (int i = 0; i < len; i++) {
        int boxIdx = seq[i];
        printf("Box %d: (", boxIdx);
        for (int j = 0; j < d; j++) {
            printf("%d", boxes[boxIdx][j]);
            if (j < d - 1) printf(", ");
        }
        printf(")\n");
    }
}

#pragma endregion 22-2 Nesting boxes

int main(void) {
    switch (TASK)
    {
        case 1: {
            // 22-1
            int numVertices = 6;
            MatGraph* g = mat_graph_create(numVertices);

            mat_graph_add_directed_edge(g, 0, 1, 10);
            mat_graph_add_directed_edge(g, 1, 2, 5);
            mat_graph_add_directed_edge(g, 2, 3, 7);
            mat_graph_add_directed_edge(g, 3, 1, -8); 
            mat_graph_add_directed_edge(g, 4, 3, 4);
            mat_graph_add_directed_edge(g, 0, 4, 3);
            mat_graph_add_directed_edge(g, 5, 0, 2);

            int dist[MAX_VERTICES];
            int pred[MAX_VERTICES];
            int src = 0;

            yens_bellman_ford(g, src, dist, pred);

            print_solution(dist, pred, numVertices, src);
            mat_graph_free(g);
            break;
        }

        case 2: {
            // 22-2
            int d = 3;
            int box1[] = {3, 1, 5};
            int box2[] = {6, 2, 7};

            if (nests_inside(box1, box2, d)) printf("Box 1 nests inside Box 2\n");
            else printf("Box 1 does not nest inside Box 2\n");

            int n = 5;
            int boxes[MAX_VERTICES][MAX_VERTICES] = {
                {2, 6, 8}, 
                {1, 3, 4}, 
                {5, 7, 9},  
                {3, 5, 8},   
                {2, 4, 6} 
            };

            find_longest_nesting_seq(boxes, n, d);
            break;
        }
        
        default:
            break;
    }
}