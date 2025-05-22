#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TASK 4

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
    MatGraph* nestingGraph = mat_graph_create(n);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && nests_inside(boxes[i], boxes[j], d)) {
                mat_graph_add_directed_edge(nestingGraph, i, j, 1);
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
            if (nestingGraph->adjMat[i][j] != 0 && dp[j] + 1 > dp[i]) {
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

#pragma region 22-3 Arbitrage

#include <math.h>

void build_exchange_rate_graph(MatGraph* g, double rates[][MAX_VERTICES]) {
    int n = g->numVertices;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && rates[i][j] > 0) {
                int weight = (int)(-log(rates[i][j]) * 1000);
                g->adjMat[i][j] = weight;
            }
        }
    }
}

int detect_currency_arbitrage(MatGraph* g, int src, int dist[], int pred[]) {
    int numVertices = g->numVertices;
    init_single_source(dist, pred, numVertices, src);

    for (int i = 0; i < numVertices - 1; i++) {
        for (int u = 0; u < numVertices; u++) {
            for (int v = 0; v < numVertices; v++) {
                if (g->adjMat[u][v] != 0)
                    relax_edge(u, v, g->adjMat[u][v], dist, pred);
            }
        }
    }

    for (int u = 0; u < numVertices; u++) {
        for (int v = 0; v < numVertices; v++) {
            if (g->adjMat[u][v] != 0) {
                if (dist[u] != INF && dist[u] + g->adjMat[u][v] < dist[v]) {
                    pred[v] = u;
                    return v;
                }
            }
        }
    }

    return -1;
}

void print_arbitrage_cycle(int vertex, int pred[], double rates[][MAX_VERTICES]) {
    int cycle[MAX_VERTICES];
    int cycleLen = 0;
    int visited[MAX_VERTICES] = {0};
    int curr = vertex;

    do {
        cycle[cycleLen++] = curr;
        curr = pred[curr];
        if (visited[curr]) break;
        visited[curr] = 1;
    } while (1);

    int startIdx = -1;
    for (int i = 0; i < cycleLen; i++) {
        if (cycle[i] == curr) {
            startIdx = i;
            break;
        }
    }

    if (startIdx == -1) {
        printf("Error extracting cycle\n");
        return;
    }

    printf("Currency exchange sequence: ");
    double profit = 1.0;

    printf("%d", curr);
    int prev = curr;

    for (int i = startIdx - 1; i >= 0; i--) {
        printf(" -> %d", cycle[i]);
        profit *= rates[prev][cycle[i]];
        prev = cycle[i];
    }

    printf(" -> %d\n", curr);
    profit *= rates[prev][curr];

    printf("Total profit factor: %.6f (%.2f%%)\n", profit, (profit-1)*100);
}

#pragma endregion 22-3 Arbitrage

#pragma region 22-4 Gabows scaling algorithm for single-source shortest paths

int calculate_bits(int W) {
    int k = 0;

    while (W > 0) {
        W >>= 1;
        k++;
    }

    return k == 0 ? 1 : k;
}

int scale_weight(int weight, int i, int k) {
    return weight >> (k - i);
}

void bucket_dijkstra(MatGraph* g, int src, int dist[], int pred[], int maxW) {
    int n = g->numVertices;
    init_single_source(dist, pred, n, src);

    int** buckets = (int**)malloc((maxW + 1) * sizeof(int*));
    int* bucketSize = (int*)calloc(maxW + 1, sizeof(int));

    for (int i = 0; i <= maxW; i++) buckets[i] = (int*)malloc(n * sizeof(int));

    buckets[0][0] = src;
    bucketSize[0] = 1; 

    for (int d = 0; d <= maxW; d++) {
        for (int i = 0; i < bucketSize[d]; i++) {
            int u = buckets[d][i];
            if (dist[u] < d) continue;;
            for (int v = 0; v < n; v++) {
                if (g->adjMat[u][v] >= 0) {
                    int prevDist = dist[v];
                    relax_edge(u, v, g->adjMat[u][v], dist, pred);
                    if (dist[v] < prevDist && dist[v] <= maxW)
                        buckets[dist[v]][bucketSize[dist[v]]++] = v;
                }
            }
        }
    }

    for (int i = 0; i <= maxW; i++) free(buckets[i]);
    free(buckets);
    free(bucketSize);
}

void reweight_edges(MatGraph* g, MatGraph* reweighted, int i, int k, int prevDist[]) {
    int n = g->numVertices;

    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (g->adjMat[u][v] != 0) {
                int weight = g->adjMat[u][v];
                int wi = scale_weight(weight, i, k);
                if (prevDist[u] != INF) {
                    int wHat = wi + 2 * prevDist[u];
                    if (prevDist[v] != INF) wHat -= 2 * prevDist[v];
                    reweighted->adjMat[u][v] = wHat;
                }
            }
        }
    }
}

void gabows_scaling(MatGraph* g, int src, int dist[], int pred[]) {
    int n = g->numVertices;

    int maxW = 0;
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (g->adjMat[u][v] > maxW) maxW = g->adjMat[u][v];
        }
    }

    int k = calculate_bits(maxW);
    printf("Max weight: %d, Number of bits (k): %d\n", maxW, k);

    MatGraph* reweighted = mat_graph_create(n);
    int* prevDist = (int*)malloc(n * sizeof(int));

    // Most significant bits
    printf("\nIteration i=1: Using only the most significant bit\n");
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (g->adjMat[u][v] != 0)
                reweighted->adjMat[u][v] = scale_weight(g->adjMat[u][v], 1, k);
        }
    }

    bucket_dijkstra(reweighted, src, dist, pred, 1);

    printf("Distances after the first iteration:\n");
    for (int v = 0; v < n; v++) printf("%d: %d, ", v, dist[v]);
    printf("\n");

    // Add more bits
    for (int i = 2; i <= k; i++) {
        printf("\nIteration i=%d: Using %d most significant bits\n", i, i);
        for (int v = 0; v < n; v++) prevDist[v] = dist[v];
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) reweighted->adjMat[u][v] = 0;
        }

        reweight_edges(g, reweighted, i, k, prevDist);
        bucket_dijkstra(reweighted, src, dist, pred, n - 1);

        for (int v = 0; v < n; v++) {
            if (dist[v] != INF && prevDist[v] != INF)
                dist[v] += 2 * prevDist[v];
        }

        printf("Distances after i=%d: ", i);
        for (int v = 0; v < n; v++) printf("%d: %d, ", v, dist[v]);
        printf("\n");
    }

    printf("\nFinal shortest path distances from source %d:\n", src);
    for (int v = 0; v < n; v++) {
        if (v != src) {
            printf("To vertex %d: ", v);
            if (dist[v] == INF) {
                printf("No path exists\n");
            } else {
                printf("Distance = %d, Path: ", dist[v]);
                print_path(pred, v);
                printf("\n");
            }
        }
    }

    free(prevDist);
    mat_graph_free(reweighted);
}

#pragma endregion 22-4 Gabows scaling algorithm for single-source shortest paths

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

        case 3: {
            // 22-3
            int n = 4;
            double rates[MAX_VERTICES][MAX_VERTICES] = {
                {1.0, 0.82, 0.72, 110.0},   
                {1.22, 1.0, 0.88, 134.0},   
                {1.39, 1.14, 1.0, 153.0},   
                {0.0091, 0.0075, 0.0065, 1.0}
            };

            printf("Currency Exchange Rates:\n");
            printf("------------------------\n");
            printf("     USD     EUR     GBP     JPY\n");
            for (int i = 0; i < n; i++) {
                if (i == 0) printf("USD ");
                else if (i == 1) printf("EUR ");
                else if (i == 2) printf("GBP ");
                else printf("JPY ");

                for (int j = 0; j < n; j++) {
                    printf("%7.4f ", rates[i][j]);
                }
                printf("\n");
            }
            printf("\n");

            MatGraph* g = mat_graph_create(n);
            build_exchange_rate_graph(g, rates);

            int dist[MAX_VERTICES];
            int pred[MAX_VERTICES];

            int vertex = detect_currency_arbitrage(g, 0, dist, pred);

            if (vertex != -1) print_arbitrage_cycle(vertex, pred, rates);
            else printf("No arbitrage opportunity. \n");

            mat_graph_free(g);
            break;
        }

        case 4: {
            // 22-4
            int numVertices = 5;
            MatGraph* g = mat_graph_create(numVertices);

            mat_graph_add_directed_edge(g, 0, 1, 4);  
            mat_graph_add_directed_edge(g, 0, 2, 2);  
            mat_graph_add_directed_edge(g, 1, 2, 5); 
            mat_graph_add_directed_edge(g, 1, 3, 10); 
            mat_graph_add_directed_edge(g, 2, 3, 3); 
            mat_graph_add_directed_edge(g, 2, 4, 12); 
            mat_graph_add_directed_edge(g, 3, 4, 2);  

            printf("Orignal graph's weights:\n");
            for (int u = 0; u < numVertices; u++) {
                for (int v = 0; v < numVertices; v++) {
                    if (g->adjMat[u][v] != 0) {
                        printf("Edge (%d,%d): %d (binary: ", u, v, g->adjMat[u][v]);
                        int weight = g->adjMat[u][v];
                        int pos = 1 << 30;
                        int printed = 0;

                        while (pos > 0) {
                            if (weight & pos) {
                                printf("1");
                                printed = 1;
                            } else if (printed) printf("0");
                            pos >>= 1;
                        }
                        if (!printed) printf("0");
                        printf(")\n");
                    }
                }
            }
            printf("\n");

            int dist[MAX_VERTICES];
            int pred[MAX_VERTICES];
            int src = 0;

            gabows_scaling(g, src, dist, pred);

            mat_graph_free(g);
            break;
        }
        
        default:
            break;
    }
}