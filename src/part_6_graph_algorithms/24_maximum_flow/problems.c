#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TASK 7
#define INF INT_MAX

#pragma region Graph utils

#define MAX_VERTICES 200

typedef struct FlowGraph {
    int adjMat[MAX_VERTICES][MAX_VERTICES];
    int flow[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
} FlowGraph;

FlowGraph* flow_graph_create(int numVertices) {
    FlowGraph* g = malloc(sizeof(FlowGraph));
    g->numVertices = numVertices;
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            g->adjMat[i][j] = 0;
            g->flow[i][j] = 0;
        }
    }

    return g;
}

void flow_graph_add_edge(FlowGraph* g, int u, int v, int capacity) {
    g->adjMat[u][v] = capacity;
}

void flow_graph_free(FlowGraph* g) {
    free(g);
}

int bfs(FlowGraph* g, int src, int sink, int parent[]) {
    int visited[MAX_VERTICES] = {0};
    int queue[MAX_VERTICES];
    int front = 0;
    int rear = 0;

    queue[rear++] = src;
    visited[src] = 1;
    parent[src] = -1;

    while (front != rear) {
        int src = queue[front++];

        for (int v = 0; v < g->numVertices; v++) {
            if (visited[v] || (g->adjMat[src][v] - g->flow[src][v]) <= 0) continue;
            if (v == sink) {
                parent[v] = src;
                return 1;
            }
            queue[rear++] = v;
            visited[v] = 1;
            parent[v] = src;
        }
    }

    return 0;
}

int edmonds_karp(FlowGraph* g, int src, int sink) {
    int u, v;
    int parent[MAX_VERTICES];
    int maxFlow = 0;

    for (u = 0; u < g->numVertices; u++)
        for (v = 0; v < g->numVertices; v++)
            g->flow[u][v] = 0;

    while (bfs(g, src, sink, parent)) {
        int pathFlow = INT_MAX;
        for (v = sink; v != src; v = parent[v]) {
            u = parent[v];
            pathFlow = fmin(pathFlow, g->adjMat[u][v] - g->flow[u][v]);
        }

        for (v = sink; v != src; v = parent[v]) {
            u = parent[v];
            g->flow[u][v] += pathFlow;
            g->flow[v][u] -= pathFlow;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}

int has_cycle(FlowGraph* g, int v, int visited[], int stack[]) {
    if (visited[v]) return stack[v];

    visited[v] = 1;
    stack[v] = 1;

    for (int i = 0; i < g->numVertices; ++i) {
        if (!g->adjMat[v][i]) continue;
        if (has_cycle(g, i, visited, stack)) return 1;
    }

    stack[v] = 0;
    return 0;
}

int is_dag(FlowGraph* g) {
    int visited[MAX_VERTICES] = {0};
    int stack[MAX_VERTICES] = {0};

    for (int i = 0; i < g->numVertices; ++i) {
        if (has_cycle(g, i, visited, stack)) return 0;
    }

    return 1;
}

FlowGraph* flow_graph_copy(FlowGraph* original) {
    int n = original->numVertices;
    FlowGraph* copy = flow_graph_create(n);

    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            copy->adjMat[u][v] = original->adjMat[u][v];
            copy->flow[u][v] = original->flow[u][v];
        }
    }

    return copy;
}

void flow_graph_reset_flow(FlowGraph* g) {
    int n = g->numVertices;

    for (int u = 0; u < n; u++)
        for (int v = 0; v < n; v++) g->flow[u][v] = 0;
}

void flow_graph_find_reachable_vertices(FlowGraph* g, int src, int reachable[]) {
    int queue[MAX_VERTICES];
    int front = 0;
    int rear = 0;
    int n = g->numVertices;

    for (int i = 0; i < n; i++) reachable[i] = 0;

    queue[rear++] = src;
    reachable[src] = 1;

    while (front != rear) {
        int curr = queue[front++];
        
        for (int v = 0; v < n; v++) {
            if (reachable[v] 
                || (g->adjMat[curr][v] - g->flow[curr][v]) <= 0) continue;
            queue[rear++] = v;
            reachable[v] = 1;
        }
    }
}

int flow_graph_get_random_edge(FlowGraph* g, int activeEdges[], int* u, int* v) {
    int n = g->numVertices;
    int totalEdges = 0;
    for (int i = 0; i < n; i++) {
        if (!activeEdges[i]) continue;
        for (int j = i + 1; j < n; j++) {
            if (!activeEdges[j]) continue;
            totalEdges += g->adjMat[i][j];
        }
    }

    if (totalEdges == 0) return 0;

    int randomEdgeIndex = rand() % totalEdges;

    for (int i = 0; i < n; i++) {
        if (!activeEdges[i]) continue;
        for (int j = i + 1; j < n; j++) {
            if (!activeEdges[j]) continue;
            int cnt = g->adjMat[i][j];
            if (randomEdgeIndex < cnt) {
                *u = i;
                *v = j;
                return 1;
            }
            randomEdgeIndex -= cnt;
        }
    }

    return 0;
} 

void flow_graph_contract_edge(FlowGraph* g, int u, int v, int activeEdges[]) {
    int n = g->numVertices;
    for (int i = 0; i < n; i++) {
        if (i == u || i == v || !activeEdges[i]) continue;

        g->adjMat[u][i] += g->adjMat[v][i];
        g->adjMat[i][u] += g->adjMat[i][v];

        g->adjMat[v][i] = 0;
        g->adjMat[i][v] = 0;
    }

    g->adjMat[u][v] = 0;
    g->adjMat[v][u] = 0;
}

#pragma endregion Graph utils

#pragma region Gomory-Hu utils

typedef struct {
    int tree[MAX_VERTICES][MAX_VERTICES];
    int capacity[MAX_VERTICES][MAX_VERTICES];
    int n;
} GomoryHuTree;

GomoryHuTree* gomory_hu_tree_create(int n) {
    GomoryHuTree* ghTree = malloc(sizeof(GomoryHuTree));
    ghTree->n = n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ghTree->tree[i][j] = 0;
            ghTree->capacity[i][j] = 0;
        }
    }

    return ghTree;
}

void gomory_hu_tree_free(GomoryHuTree* ghTree) {
    free(ghTree);
}

GomoryHuTree* gomory_hu_tree_build(FlowGraph* g) {
    int n = g->numVertices;
    GomoryHuTree* ghTree = gomory_hu_tree_create(n);

    int components[MAX_VERTICES];
    for (int i = 0; i < n; i++) components[i] = 0;

    // |V| - 1
    for (int v = 1; v < n; v++) {
        int u = components[v];
        printf("Computing max flow on path %d -> %d", u, v);

        FlowGraph* tempG = flow_graph_copy(g);
        flow_graph_reset_flow(g);

        int maxFlow = edmonds_karp(tempG, u, v);
        printf("  Max flow value: %d\n", maxFlow);

        int reachable[MAX_VERTICES];
        flow_graph_find_reachable_vertices(tempG, u, reachable);

        ghTree->tree[u][v] = ghTree->tree[v][u] = 1;
        ghTree->capacity[u][v] = ghTree->capacity[v][u] = maxFlow;
        printf("Added tree edge {%d,%d} with capacity %d\n", u, v, maxFlow);

        printf("Component update: ");
        for (int i = 0; i < n; i++) {
            if (components[i] != components[v] || reachable[i]) continue;
            components[i] = v;
            printf("%d->comp_%d ", i, v);
        }

        printf("\n");
        flow_graph_free(tempG);
    }

    printf("Gomory-Hu tree construction complete\n");
    return ghTree;
}

#pragma endregion Gomory-Hu utils

#pragma region Escape problem

int grid_to_vertex(int row, int col, int n) {
    return row * n + col;
}

int is_boundary(int row, int col, int n) {
    return (row == 0 || row == n - 1 || col == 0 || col == n - 1);
}

FlowGraph* create_escape_flow_network(int n, int startingPoints[][2], int m) {
    const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int totalVertices = 2 * n * n + 2;
    int src = totalVertices - 2;
    int sink = totalVertices - 1;
    int i, j;

    FlowGraph* g = flow_graph_create(totalVertices);

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            int vertexIdx = grid_to_vertex(i, j, n);
            int vIn = 2 * vertexIdx;
            int vOut = 2 * vertexIdx + 1;
            flow_graph_add_edge(g, vIn, vOut, 1);
        }
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            int vertexIdx = grid_to_vertex(i, j, n);
            int vOut = 2 * vertexIdx + 1;

            for (int d = 0; d < 4; d++) {
                int ni = i + dirs[d][0]; 
                int nj = j + dirs[d][1];
                
                if (ni < 0 || ni >= n || nj < 0 || nj >= n) continue;

                int neiIdx = grid_to_vertex(ni, nj, n);
                int neiIn = 2 * neiIdx;

                flow_graph_add_edge(g, vOut, neiIn, 1);
            }
        }
    }

    // src to starting points
    for (i = 0; i < m; i++) {
        int startRow = startingPoints[i][0];
        int startCol = startingPoints[i][1];
        int vertexIdx = grid_to_vertex(startRow, startCol, n);
        int vIn = 2 * vertexIdx;
        flow_graph_add_edge(g, src, vIn, 1);
    }

    // boundary to sink
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (!is_boundary(i, j, n)) continue;
            int vertexIdx = grid_to_vertex(i, j, n);
            int vOut = 2 * vertexIdx + 1;
            flow_graph_add_edge(g, vOut, sink, 1);
        }
    }

    return g;
}

int can_escape(int n, int startingPoints[][2], int m) {
    FlowGraph* g = create_escape_flow_network(n, startingPoints, m);
    int src = g->numVertices - 2;
    int sink = g->numVertices - 1;

    int maxFlow = edmonds_karp(g, src, sink);

    printf("Maximum flow found: %d\n", maxFlow);
    printf("Number of starting points: %d\n", m);

    int canEscape = (maxFlow == m);
    flow_graph_free(g);

    return canEscape;
}

#pragma endregion Escape problem

#pragma region Minimum path cover

int find_minimum_path_cover(FlowGraph* g) {
    /*
        O(VE), only works for DAGS
    */
    if (!is_dag(g)) {
        printf("Passed graph is not a DAG");
        return -1;
    }
    int n = g->numVertices;
    int totalVertices = 2 * (n + 1);
    FlowGraph* flowGraph = flow_graph_create(totalVertices);

    int src = 0;
    int sink = n + 1;

    // to src
    for (int i = 1; i <= n; ++i) flow_graph_add_edge(flowGraph, src, i, 1);

    // to sink
    for (int i = 1; i <= n; ++i) {
        int yi = n + 1 + i;
        flow_graph_add_edge(flowGraph, yi, sink, 1);
    }

    // connect both parts
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (g->adjMat[i][j] <= 0) continue;
            int xi = (i + 1);
            int yj = n + 1 + (j + 1);
            flow_graph_add_edge(flowGraph, xi, yj, 1);
        }
    }

    int maxFlow = edmonds_karp(flowGraph, src, sink);

    printf("Maximum flow found: %d\n", maxFlow);
    printf("Number of vertices: %d\n", n);

    int minPathCoverSize = n - maxFlow;
    printf("Minimum path cover size: %d\n", minPathCoverSize);

    printf("\nPath cover paths:\n");

    int* inPath = calloc(n + 1, sizeof(int));
    int pathCnt = 0;

    for (int i = 1; i <= n; ++i) {
        if (inPath[i]) continue;
        
        int hasIncoming = 0;
        for (int j = 1; j <= n; ++j) {
            int xj = j;
            int yi = n + 1 + i;
            if (flowGraph->flow[xj][yi] == 1) {
                hasIncoming = 1;
                break;
            }
        }

        if (hasIncoming) continue;
        printf("Path %d: ", ++pathCnt);
        int curr = i;

        while (curr != -1) {
            printf("%d ", curr);
            inPath[curr] = 1;
            int next = -1;

            for (int j = 1; j <= n; ++j) {
                int xi = curr;
                int yj = n + 1 + j;
                if (flowGraph->flow[xi][yj] == 1) {
                    next = j;
                    break;
                }
            }
            curr = next;
        }
        printf("\n");
    }

    // isolated vertices
    for (int i = 1; i <= n; i++) {
        if (inPath[i]) continue;
        printf("Path %d: %d\n", ++pathCnt, i);
    }

    flow_graph_free(flowGraph);
    return minPathCoverSize;
}

#pragma endregion Minimum path cover

#pragma region Algorithmic consulting

typedef struct {
    int profit;
    int numExperts;
    int experts[MAX_VERTICES];
} Job;

FlowGraph* create_consulting_flow_network(
    Job jobs[], 
    int numJobs, 
    int expertCosts[], 
    int numExperts
) {
    // src, edges, sink
    int totalVertices = 1 + numJobs + numExperts + 1;
    int src = 0;
    int sink = totalVertices - 1;

    FlowGraph* g = flow_graph_create(totalVertices);

    // src to experts
    for (int i = 0; i < numExperts; i++) {
        int expertVertex = i + 1;
        flow_graph_add_edge(g, src, expertVertex, expertCosts[i]);
        printf("Edge: source -> expert %d (capacity %d)\n", i + 1, expertCosts[i]);
    }

    // jobs to sink
    for (int i = 0; i < numJobs; i++) {
        int jobVertex = i + numExperts + 1;
        flow_graph_add_edge(g, jobVertex, sink, jobs[i].profit);
        printf("Edge: job %d -> sink (capacity %d)\n", i + 1, jobs[i].profit);
    }

    // experts to jobs
    for (int i = 0; i < numJobs; i++) {
        int jobVertex = i + numExperts + 1;
        for (int j = 0; j < jobs[i].numExperts; j++) {
            int expertVertex = jobs[i].experts[j];
            flow_graph_add_edge(g, expertVertex, jobVertex, INF);
            printf("Edge: expert %d -> job %d (capacity infinity)\n", expertVertex, i + 1);
        }
    }

    return g;
}

void solve_consulting_problem(
    Job jobs[],
    int numJobs,
    int expertCosts[],
    int numExperts
) {
    /*
        O(VE^2) with assumptions
    */
    FlowGraph* g = create_consulting_flow_network(
        jobs, numJobs, expertCosts, numExperts);

    int src = 0;
    int sink = g->numVertices - 1;

    int maxFlow = edmonds_karp(g, src, sink);
    printf("\nMaximum flow in consulting network: %d\n", maxFlow);

    int totalPossibleProfit = 0;
    for (int i = 0; i < numJobs; i++) totalPossibleProfit += jobs[i].profit;
    printf("Total possible profit: %d\n", totalPossibleProfit);

    int maxNetRevenue = totalPossibleProfit - maxFlow;
    printf("Max netto revenue: %d\n", maxNetRevenue);

    // reconstruct
    int visited[MAX_VERTICES] = {0};
    int queue[MAX_VERTICES];
    int front = 0;
    int rear = 0;

    queue[rear++] = src;
    visited[src] = 1;

    while (front != rear) {
        int src = queue[front++];
        for (int v = 0; v < g->numVertices; v++) {
            if (visited[v] || (g->adjMat[src][v] - g->flow[src][v]) <= 0) continue;
            visited[v] = 1;
            queue[rear++] = v; 
        }
    }

    printf("Accepted jobs: ");
    int acceptedJobsCnt = 0;
    for (int i = 0; i < numJobs; i++) {
        int jobVertex = 1 + numExperts + i;
        if (visited[jobVertex]) continue;
        printf("%d ", i + 1);
        acceptedJobsCnt++;
    }
    if (acceptedJobsCnt == 0) printf("none");
    printf("\n");

    printf("Experts to hire: ");
    int hiredExpertsCnt = 0;
    for (int i = 0; i < numExperts; i++) {
        int expertVertex = 1 + i;
        if (visited[expertVertex]) continue;
        printf("%d ", i + 1);
        hiredExpertsCnt++;
    }
    if (hiredExpertsCnt == 0) printf("none");

    flow_graph_free(g);
}

#pragma endregion Algorithmic consulting

#pragma region Updating maximum flow

int update_capacity(FlowGraph* g, int src, int v, int u, int sink, int delta) {
    int originalFlow = 0;
    for (int i = 0; i < g->numVertices; i++) originalFlow += g->flow[src][i];

    g->adjMat[src][v] += delta;

    int newFlow = edmonds_karp(g, src, sink);
    
    return newFlow - originalFlow;
}

#pragma endregion Updating maximum flow

#pragma region Maximum flow by scaling

int dfs_with_scale(
    FlowGraph* g,
    int src,
    int sink,
    int parent[],
    int visited[],
    int scale
) {
    if (src == sink) return 1;
    visited[src] = 1;
    
    for (int v = 0; v < g->numVertices; v++) {
        if (visited[v]) continue;
        
        int residualCapacity = g->adjMat[src][v] - g->flow[src][v];
        if (residualCapacity < scale) continue;

        parent[v] = src;
        if (dfs_with_scale(g, v, sink, parent, visited, scale)) return 1;
    }

    return 0;
}

int dfs_augmenting_path(
    FlowGraph* g,
    int src,
    int sink,
    int parent[],
    int scale
) {
    int visited[MAX_VERTICES] = {0};
    parent[src] = -1;
    return dfs_with_scale(g, src, sink, parent, visited, scale);
}

int max_flow_by_scaling(FlowGraph* g, int src, int sink) {
    // init flow
    for (int u = 0; u < g->numVertices; u++)
        for (int v = 0; v < g->numVertices; v++)
            g->flow[u][v] = 0;

    // max capacity
    int maxCapacity = 0;
    for (int u = 0; u < g->numVertices; u++)
        for (int v = 0; v < g->numVertices; v++)
            maxCapacity = fmax(g->adjMat[u][v], maxCapacity);
    
    if (maxCapacity == 0) return 0;

    // scale = 2^⌊log₂(maxCapacity)⌋
    int scale = (int)pow(2, floor(log2(maxCapacity)));
    printf("Initial scale: %d\n", scale);

    int totalFlow = 0;

    while (scale >= 1) {
        printf("Scale = %d\n", scale);
        int pathFound = 0;
        int parent[MAX_VERTICES];

        while (dfs_augmenting_path(g, src, sink, parent, scale)) {
            int pathFlow = INT_MAX;
            for (int v = sink; v != src; v = parent[v]) {
                int u = parent[v];
                int residual = g->adjMat[u][v] - g->flow[u][v];
                pathFlow = fmin(pathFlow, residual);
            }

            for (int v = sink; v != src; v = parent[v]) {
                int u = parent[v];
                g->flow[u][v] += pathFlow;
                g->flow[v][u] -= pathFlow;
            }

            totalFlow += pathFlow;
            pathFound++;
            printf("Found augmenting path with flow %d\n", pathFlow);
        }
        printf("Found %d paths using scale of %d\n", pathFound, scale);
        scale >>= 1;
    }

    return totalFlow;
}

#pragma endregion Maximum flow by scaling

#pragma region The widest augmenting path

int dijkstra_widest_path(FlowGraph* g, int src, int sink, int parent[]) {
    int maxCapacity[MAX_VERTICES];
    int visited[MAX_VERTICES] = {0};

    // init
    for (int i = 0; i < g->numVertices; i++) {
        maxCapacity[i] = 0;
        parent[i] = -1;
    }
    maxCapacity[src] = INT_MAX;

    for (int cnt = 0; cnt < g->numVertices - 1; cnt++) {
        int maxCap = 0;
        int u = -1;

        for (int i = 0; i < g->numVertices; i++) {
            if (visited[i] || maxCapacity[i] < maxCap) continue;
            maxCap = maxCapacity[i];
            u = i;
        }

        if (u == -1 || maxCap == 0) break;
        visited[u] = 1;

        if (u == sink) return maxCapacity[sink];

        for (int v = 0; v < g->numVertices; v++) {
            if (visited[v]) continue;

            int residualCap = g->adjMat[u][v] - g->flow[u][v];
            if (residualCap <= 0) continue;

            int newCap = fmin(maxCapacity[u], residualCap);
            if (newCap > maxCapacity[v]) {
                maxCapacity[v] = newCap;
                parent[v] = u;
            }
        }
    }

    return maxCapacity[sink];
} 

int widest_augmenting_path(FlowGraph* g, int src, int sink) {
    /*
        O(EV^2 log(|f*|))
    */
    
    // init flows
    for (int u = 0; u < g->numVertices; u++)
        for (int v = 0; v < g->numVertices; v++)
            g->flow[u][v] = 0;

    int totalFlow = 0;
    int parent[MAX_VERTICES];
    int iteration = 0;

    while (1) {
        int pathCapacity = dijkstra_widest_path(g, src, sink, parent);
        if (pathCapacity == 0) break;
        iteration++;
        printf("Iteration %d: Found path with capacity: %d\n",
            iteration, pathCapacity);

        // augment
        for (int v = sink; v != src; v = parent[v]) {
            int u = parent[v];
            g->flow[u][v] += pathCapacity;
            g->flow[v][u] -= pathCapacity;
        }

        totalFlow += pathCapacity;

        // reconstruct the path
        printf("Path: ");
        int path[MAX_VERTICES];
        int pathLen = 0;
        for (int v = sink; v != src; v = parent[v]) path[pathLen++] = v;
        for (int i = pathLen - 1; i >= 0; i--) {
            printf("%d", path[i]);
            if (i > 0) printf(" -> ");
        }
        printf(" (flow: %d)\n", pathCapacity);
    }

    printf("Total iterations: %d\n", iteration);
    return totalFlow;
}

#pragma endregion The widest augmenting path

#pragma region Minimum global cut

int find_min_global_cut_all_pairs(FlowGraph* g) {
    /*
        Check every pair of vertices as
        source and sink.

        Edmonds-Karp: O(VE^2)
        V over 2 = O(V^2)

        Overall O(V^3*E^2) I believe.
    */
    int n = g->numVertices;
    int minGlobalCut = INT_MAX;
    int bestSrc = -1;
    int bestSink = -1;
    int pairCnt = 0;

    FlowGraph* tmepG = flow_graph_create(n);

    // all pairs
    for (int s = 0; s < n; s++) {
        for (int t = 0; t < n; t++) {
            if (s == t) continue;
            pairCnt++;

            FlowGraph* tempG = flow_graph_copy(g);
            flow_graph_reset_flow(tempG);

            int maxFlow = edmonds_karp(tempG, s, t);
            printf("Pair (%d, %d): max flow = %d\n",
                s, t, maxFlow);

            if (maxFlow >= minGlobalCut) continue;

            minGlobalCut = maxFlow;
            bestSrc = s;
            bestSink = t;
            printf("New minimum found\n");

            flow_graph_free(tempG);
        }
    }

    printf("Results: \n");
    printf("Tested %d pairs\n", pairCnt);
    printf("Minimum global cut value mi(G) = %d\n", minGlobalCut);
    printf("Best pair: (%d,%d)\n", bestSrc, bestSink);

    return minGlobalCut;
}

int find_min_global_cut_fixed_src(FlowGraph* g) {
    /*
        Check every possible source against
        a fixed sink.

        Edmonds-Karp: O(VE^2)
        V possible pairs = |V| - 1 comparisons = O(V)

        Overall O(V^2*E^2) I believe.
    */
    int n = g->numVertices;
    int minGlobalCut = INT_MAX;
    int src = 0;
    int bestSink = -1;
    int pairCnt = 0;

    for (int t = 1; t < n; t++) {
        pairCnt++;

        FlowGraph* tempG = flow_graph_copy(g);
        flow_graph_reset_flow(tempG);

        int maxFlow = edmonds_karp(tempG, src, t);
        printf("Pair (%d, %d): max flow = %d\n",
            src, t, maxFlow);

        if (maxFlow >= minGlobalCut) continue;

        minGlobalCut = maxFlow;
        bestSink = t;
        printf("New minimum found\n");

        flow_graph_free(tempG);

    }

    printf("Results: \n");
    printf("Tested %d pairs\n", pairCnt);
    printf("Minimum global cut value mi(G) = %d\n", minGlobalCut);
    printf("Best pair: (%d,%d)\n", src, bestSink);

    return minGlobalCut;
}

int find_min_global_cut_gomory_hu(FlowGraph* g) {
    /*
        |V| - 1 iterations of O(VE^2)
        Overall: O(V^2*E^2)
    */
    GomoryHuTree* ghTree = gomory_hu_tree_build(g);
    int minGlobalCut = INT_MAX; 

    for (int u = 0; u < ghTree->n; u++) {
        for (int v = u + 1; v < ghTree->n; v++) {
            if (!ghTree->tree[u][v] 
                || ghTree->capacity[u][v] >= minGlobalCut) continue;
            minGlobalCut = ghTree->capacity[u][v];
            printf("New minimum: edge {%d,%d} capacity %d\n", u, v, ghTree->capacity[u][v]);
        }
    }

    printf("Results: \n");
    printf("Minimum global cut value mi(G) = %d\n", minGlobalCut);

    return minGlobalCut;
}

int karger_single_run(FlowGraph* g) {
    /*
        Contract random edges until
        only 2 remain.
    */
    int n = g->numVertices;
    int activeEdges[MAX_VERTICES];
    int vertexCnt = n;

    for (int i = 0; i < n; i++) activeEdges[i] = 1;

    while (vertexCnt > 2) {
        int u, v;
        if (!flow_graph_get_random_edge(g, activeEdges, &u, &v)) 
            return INT_MAX;
        flow_graph_contract_edge(g, u, v, activeEdges);
        activeEdges[v] = 0;
        vertexCnt--;
    }

    int remaining[2];
    int cnt = 0;

    for (int i = 0; i < n && cnt < 2; i++) {
        if (activeEdges[i]) remaining[cnt++] = i;
    }

    if (cnt != 2) return INT_MAX;

    int minGlobalCut = g->adjMat[remaining[0]][remaining[1]];
    return minGlobalCut;
}

int karger_unique(FlowGraph* g) {
    /*
        Assuming there's only one
        global minimum cut.

        O(V^2)
    */
    srand(time(NULL));

    int n = g->numVertices;
    if (n < 2) return 0;

    int iterations = n * n;
    printf("Running %d iterations\n", iterations);

    int minGlobalCut = INT_MAX;
    
    for (int iter = 0; iter < iterations; iter++) {
        FlowGraph* tempG = flow_graph_copy(g);
        int cutValue = karger_single_run(tempG);

        if (cutValue < minGlobalCut) {
            minGlobalCut = cutValue;
            printf("Iteration %d: New minimum cut found = %d\n", iter + 1, cutValue);
        }

        flow_graph_free(tempG);
    }

    return minGlobalCut;
}

int karger(FlowGraph* g) {
    /*
        O(V^2*log(V)) iterations of
        Karger's algorithm.

        Overall: O(V^4*log(V))
    */

    srand(time(NULL));

    int n = g->numVertices;
    if (n < 2) return 0;

    int iterations = n * n * (int)log(n) * 2;
    printf("Running %d iterations\n", iterations);

    int minGlobalCut = INT_MAX;

    for (int iter = 0; iter < iterations; iter++) {
        FlowGraph* tempG = flow_graph_copy(g);
        int cutValue = karger_single_run(tempG);

        if (cutValue < minGlobalCut) {
            minGlobalCut = cutValue;
            printf("Iteration %d: New minimum cut found = %d\n", iter + 1, cutValue);
        } 

        flow_graph_free(tempG);
    }

    return minGlobalCut;
}

#pragma endregion Minimum global cut

int main(void) {
    switch (TASK)
    {
        case 1: {
            // Escape problem
            int n1 = 6;
            int m1 = 10;
            int startingPoints1[][2] = {
                {0, 2},
                {1, 1},
                {1, 2},
                {1, 3},
                {3, 1},
                {3, 2},
                {3, 3},
                {5, 1},
                {5, 2}, 
                {5, 3}
            };

            printf("Example A. Expected to succeed.\n");

            int result1 = can_escape(n1, startingPoints1, m1);
            if (result1) printf("Escape is possible\n");
            else printf("Escape is impossible.\n");

            printf("\n");

            int n2 = 6;
            int m2 = 11;
            int startingPoints2[][2] = {
                {0, 2},
                {1, 1},
                {1, 2},
                {1, 3},
                {3, 1},
                {3, 2},
                {3, 3},
                {4, 2},
                {5, 1},
                {5, 2}, 
                {5, 3}
            };
            
            printf("Example B. Expected to fail.\n");

            int result2 = can_escape(n2, startingPoints2, m2);      
            if (result2) printf("Escape is possible\n");
            else printf("Escape is impossible.\n");

            break;
        }

        case 2: {
            // Minimum path cover
            int n = 5;
            FlowGraph* g = flow_graph_create(n);
            int edges[][3] = {
                {0, 1, 1},
                {0, 2, 1},
                {1, 3, 1},
                {2, 3, 1},
                {2, 3, 1}
            };

            for (int i = 0; i < 5; i++) 
                flow_graph_add_edge(g, edges[i][0], edges[i][1], edges[i][2]);

            find_minimum_path_cover(g);

            flow_graph_free(g);
            break;
        }

        case 3: {
            // Algorithmic consulting
            int m = 3;
            int n = 4;

            // profit, number of experts, experts' ids
            Job jobs[3] = {
                {100, 2, {1, 2}},
                {200, 2, {2, 3}},
                {150, 3, {1, 3, 4}}
            };

            int expertCosts[4] = {80, 70, 60, 90};

            solve_consulting_problem(jobs, m, expertCosts, n);
            break;
        }

        case 4 : {
            // Updating maximum flow
            int n = 6;
            FlowGraph* g = flow_graph_create(n);
            int edges[][3] = {
                {0,1,10}, 
                {0,2,8}, 
                {1,3,5}, 
                {2,3,3}, 
                {1,4,8}, 
                {3,5,10}, 
                {4,5,10}
            };
            for (int i = 0; i < 7; i++) {
                flow_graph_add_edge(g, edges[i][0], edges[i][1], edges[i][2]);
            }

            int src = 0;
            int sink = 5;
            int initialFlow = edmonds_karp(g, src, sink);
            printf("Initial maximum flow: %d\n", initialFlow);

            // increase 
            printf("Testing capacity increase on edge (0,1)\n");
            int flowIncrease = update_capacity(g, 0, 1, src, sink, 1);
            printf("Flow increased by: %d\n", flowIncrease);

            // decrease
            printf("Testing capacity decrease on edge (0,1)\n");
            int flowDecrease = update_capacity(g, 0, 1, src, sink, -1);
            printf("Flow decreased by: %d\n", -flowDecrease);

            flow_graph_free(g);
            break;
        }

        case 5: {
            // Maximum flow by scaling
            int n = 6;
            FlowGraph* g = flow_graph_create(n);
            int edges[][3] = {
                {0,1,16}, 
                {0,2,13}, 
                {1,2,10}, 
                {1,3,12}, 
                {2,1,4}, 
                {2,4,14}, 
                {3,2,9}, 
                {3,5,20}, 
                {4,3,7}, 
                {4,5,4}
            };

            for (int i = 0; i < 10; i++)
                flow_graph_add_edge(g, edges[i][0], edges[i][1], edges[i][2]);

            int src = 0;
            int sink = 5;

            int maxFlow = max_flow_by_scaling(g, src, sink);
            printf("Max flow: %d\n", maxFlow);

            flow_graph_free(g);
            break;
        }

        case 6: {
            // The widest augmenting path
            int n = 6;
            FlowGraph* g = flow_graph_create(n);
            int edges[][3] = {
                {0,1,16}, 
                {0,2,13}, 
                {1,2,10}, 
                {1,3,12}, 
                {2,1,4}, 
                {2,4,14}, 
                {3,2,9}, 
                {3,5,20}, 
                {4,3,7}, 
                {4,5,4}
            };

            for (int i = 0; i < 10; i++)
                flow_graph_add_edge(g, edges[i][0], edges[i][1], edges[i][2]);

            int src = 0;
            int sink = 5;

            int widestFlow = widest_augmenting_path(g, src, sink);
            printf("Widest augmenting path result: %d\n", widestFlow);

            for (int u = 0; u < g->numVertices; u++)
                for (int v = 0; v < g->numVertices; v++)
                    g->flow[u][v] = 0;

            int edmondsFlow = edmonds_karp(g, src, sink);
            printf("Edmonds-Karp result: %d\n", edmondsFlow);

            printf("Do results match? %d\n", widestFlow == edmondsFlow);

            flow_graph_free(g);
            break;
        }

        case 7: {
            // Minimum global cut
            int n = 5;
            FlowGraph* g = flow_graph_create(n); 

            int edges[][3] = {
                {0, 1, 2}, 
                {1, 0, 2},
                {1, 2, 3},  
                {2, 1, 3},
                {2, 3, 1},  
                {3, 2, 1},
                {3, 4, 4},  
                {4, 3, 4},
                {0, 4, 1}, 
                {4, 0, 1}
            };

            int numEdges = sizeof(edges) / sizeof(edges[0]);
            
            for (int i = 0; i < numEdges; i += 2) {
                flow_graph_add_edge(g, edges[i][0], edges[i][1], edges[i][2]);
                flow_graph_add_edge(g, edges[i + 1][0], edges[i + 1][1], edges[i + 1][2]);
                printf("  {%d,%d} capacity %d\n", edges[i][0], edges[i][1], edges[i][2]);
            }
            printf("\n");

            printf("ALGORITHMS COMPARISON\n");

            struct {
                int (*func)(FlowGraph*);
                const char* name;
                const char* complexity;
            } algos[] = {
                {
                    find_min_global_cut_all_pairs, 
                    "All pairs algorithm", 
                    "O(V^3*E^2)"
                },
                {
                    find_min_global_cut_fixed_src, 
                    "Fixed source algorithm", 
                    "O(V^2*E^2)"
                },
                {
                    find_min_global_cut_gomory_hu,
                    "Gomory-Hu tree algorithm", 
                    "O(V^2*E^2)"
                },
                {
                    karger_unique,
                    "Karger's algorithm for unique minimum global cuts", 
                    "O(V^2)"
                },
                {
                    karger,
                    "Karger's algorithm", 
                    "O(V^4*log(V))"
                }
            };

            int algoCnt = sizeof(algos) / sizeof(algos[0]);
            int results[algoCnt];
            
            for (int i = 0; i < algoCnt; i++) {
                printf("%d. %s (%s):\n", 
                    i + 1, algos[i].name, algos[i].complexity);
                FlowGraph* tempG = flow_graph_copy(g);
                results[i] = algos[i].func(tempG);
                flow_graph_free(tempG);
                printf("\n");
            }

            printf("VERIFICATION\n");
            for (int i = 0; i < algoCnt; i++) 
                printf("  %s: %d\n", algos[i].name, results[i]);

            int allMatch = 1;
            int refRes = results[0];

            for (int i = 1; i < algoCnt; i++) {
                if (results[i] == refRes) continue;
                allMatch = 0;
                printf("Result mismatch between %s (%d) and %s (%d)\n",
                    algos[0].name, results[0], algos[i].name, results[i]);
            }

            if (allMatch) 
                printf("All algorithms produce the same result: %d\n", refRes);

            flow_graph_free(g);
            break;
        }
        
        default:
            break;
    }

    return 0;
}