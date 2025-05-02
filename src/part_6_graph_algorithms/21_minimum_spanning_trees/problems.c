#include <stdio.h>
#include <stdlib.h>

#define TASK 2

#pragma region Graph utils

#define MAX_VERTICES 10
#define MAX_EDGES 100

typedef struct MatGraph {
    // Graph represented by adjacency matrix
    int adjMat[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
} MatGraph;

typedef struct Edge {
    int u, v, weight;
} Edge;


MatGraph* mat_graph_create(int numVertices) {
    MatGraph* g = malloc(sizeof(MatGraph));
    g->numVertices = numVertices;

    for (int i = 0; i < numVertices; i++) 
        for (int j = 0; j < numVertices; j++) g->adjMat[i][j] = 0;

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

void mat_graph_print(MatGraph* g) {
    printf("Graph with %d vertices:\n", g->numVertices);
    for (int i = 0; i < g->numVertices; i++) {
        printf("Vertex %d is connected to: ", i);
        for (int j = 0; j < g->numVertices; j++) {
            if (g->adjMat[i][j] > 0) printf("%d(w:%d) ", j, g->adjMat[i][j]);
        }
        printf("\n");
    }
}

#pragma endregion Graph utils

#pragma region 21-1 Second best MST

int parent[MAX_VERTICES], depth[MAX_VERTICES];
int maxEdge[MAX_VERTICES][MAX_VERTICES];

void dfs(MatGraph* g, int u, int p, int d) {
    parent[u] = p;
    depth[u] = d;
    for (int v = 0; v < g->numVertices; v++) {
        if (g->adjMat[u][v] && v != p) dfs(g, v, u, d + 1);
    }
}

int find_lca(int u, int v) {
    while (depth[u] > depth[v]) u = parent[u];
    while (depth[v] > depth[u]) v = parent[v];
    while (u != v) {
        u = parent[u];
        v = parent[v];
    }
    return u;
}

int max_on_path(MatGraph* g, int u, int v) {
    int lca = find_lca(u, v);
    int maxW = 0;
    int x = u;
    while (x != lca) {
        int p = parent[x];
        if (g->adjMat[x][p] > maxW) maxW = g->adjMat[x][p];
        x = p;
    }
    x = v;
    while (x != lca) {
        int p = parent[x];
        if (g->adjMat[x][p] > maxW) maxW = g->adjMat[x][p];
        x = p;
    }
    return maxW;
}

void compute_max_edges(MatGraph* g) {
    dfs(g, 0, -1, 0);
    for (int u = 0; u < g->numVertices; u++) {
        for (int v = 0; v < g->numVertices; v++) {
            if (u == v) maxEdge[u][v] = 0;
            else maxEdge[u][v] = max_on_path(g, u, v);
        }
    }
}

int parents[MAX_VERTICES], ranks[MAX_VERTICES];

void make_set(int n) {
    for (int i = 0; i < n; i++) {
        parents[i] = i;
        ranks[i] = 1;
    }
}

int find_set(int u) {
    if (u != parents[u]) parents[u] = find_set(parents[u]);
    return parents[u];
}

int same_component(int u, int v) {
    return find_set(u) == find_set(v);
}

void union_sets(int u, int v) {
    int uRoot = find_set(u);
    int vRoot = find_set(v);

    if (ranks[uRoot] < ranks[vRoot]) parents[uRoot] = vRoot;
    else if (ranks[uRoot] > ranks[vRoot]) parents[vRoot] = uRoot;
    else {
        parents[vRoot] = uRoot;
        ranks[uRoot]++;
    }
}

int compare_edges(const void* a, const void* b) {
    Edge* ea = (Edge*)a;
    Edge* eb = (Edge*)b;
    return ea->weight - eb->weight;
}

int kruskal(MatGraph* g, Edge* edges, int edgeCnt, MatGraph* mst) {
    make_set(g->numVertices);
    qsort(edges, edgeCnt, sizeof(Edge), compare_edges);

    int mstWeight = 0;
    int mstEdges = 0;

    for (int i = 0; i < edgeCnt; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].weight;
        if (!same_component(u, v)) {
            union_sets(u, v);
            mat_graph_add_undirected_edge(mst, u, v, w);
            mstWeight += w;
            mstEdges++;
            printf("MST edge: %d - %d (weight %d)\n", u, v, w);
            if (mstEdges == g->numVertices - 1) break;
        }
    }

    return mstWeight;
}

int find_second_best_mst_weight(
    MatGraph* g, 
    MatGraph* mst, 
    Edge* edges, 
    int edgeCnt, 
    int mstW
) {
    compute_max_edges(mst);
    int secondBestW = -1;

    for (int i = 0; i < edgeCnt; i++) {
        int u = edges[i].u, v = edges[i].v, w = edges[i].weight;
        if (mst->adjMat[u][v] == 0) {
            int candidate = mstW + w - maxEdge[u][v];
            if (candidate > mstW && (secondBestW == -1 || candidate < secondBestW)) {
                secondBestW = candidate;
            }
        }
    }

    return secondBestW;
}

#pragma region 21-1 Second best MST

#pragma region 21-2

typedef struct {
    int u;
    int v;
    int weight;
} OrigEdge;

void mst_reduce(MatGraph* g, MatGraph** gPrimePtr, Edge* t, int* tSize) {
    int n = g->numVertices;
    int marked[MAX_VERTICES] = {0};

    make_set(n);

    *tSize = 0;
    for (int u = 0; u < n; u++) {
        if (marked[u] == 0) {
            int minV = -1;
            int minW = INT_MAX;
            // Adj with min weight
            for (int v = 0; v < n; v++) {
                if (g->adjMat[u][v] > 0 && g->adjMat[u][v] < minW) {
                    minW = g->adjMat[u][v];
                    minV = v;
                }
            }
            if (minV != -1) {
                union_sets(u, minV);
                t[*tSize].u = u;
                t[*tSize].v = minV;
                t[*tSize].weight = minW;
                (*tSize)++;
                marked[u] = marked[minV] = 1;
            }
        }
    }

    // Find reps
    int repMap[MAX_VERTICES];
    int repCnt = 0;
    int rep2idx[MAX_VERTICES];

    for (int v = 0; v < n; v++) {
        int rep = find_set(v);
        int i;

        for (i = 0; i <repCnt; i++) if (repMap[i] == rep) break;

        if (i == repCnt) {
            repMap[repCnt] = rep;
            rep2idx[rep] = repCnt;
            repCnt++;
        }
    }

    // Create reduced graph
    MatGraph* gPrime = mat_graph_create(repCnt);
    *gPrimePtr = gPrime;

    for (int u = 0; u < n; u++) {
        for (int v = u + 1; v < n; v++) {
            if (g->adjMat[u][v] > 0) {
                int repU = find_set(u);
                int repV = find_set(v);

                if (repU != repV) {
                    int uIdx = rep2idx[repU];
                    int vIdx = rep2idx[repV];

                    if (gPrime->adjMat[uIdx][vIdx] == 0 ||
                        g->adjMat[u][v] == gPrime->adjMat[uIdx][vIdx]) 
                        mat_graph_add_undirected_edge(
                                gPrime, 
                                uIdx, 
                                vIdx, 
                                g->adjMat[u][v]
                            ); 
                }
            }
        }
    }
}

void print_mst_edges(Edge* t, int tSize) {
    printf("MST edges:\n");
    int totalW = 0;
    for (int i = 0; i < tSize; i++) {
        printf("(%d, %d) weight: %d\n", t[i].u, t[i].v, t[i].weight);
        totalW += t[i].weight;
    }
    printf("Total MST weight: %d\n", totalW);
}

void mst_reduce_optimized(MatGraph* g, MatGraph** gPrimePtr, Edge* t, int* tSize) {
    int n = g->numVertices;
    int marked[MAX_VERTICES] = {0};
    int components[MAX_EDGES]; // replacement for a disjoint set

    for (int i = 0; i < n; i++) components[i] = i;

    *tSize = 0;
    for (int u = 0; u < n; u++) {
        if (marked[u] == 0) {
            int minV = -1;
            int minW = INT_MAX;
            // Adj with min weight
            for (int v = 0; v < n; v++) {
                if (g->adjMat[u][v] > 0 && g->adjMat[u][v] < minW) {
                    minW = g->adjMat[u][v];
                    minV = v;
                }
            }
            if (minV != -1) {
                int compU = components[u];
                int compV = components[minV];

                for (int i = 0; i < n; i++) 
                    if (components[i] == compV) components[i] = compU;
                
                t[*tSize].u = u;
                t[*tSize].v = minV;
                t[*tSize].weight = minW;
                (*tSize)++;
                marked[u] = marked[minV] = 1;
            }
        }
    }

    int uniqueComps[MAX_VERTICES];
    int compCnt = 0;
    int comp2idx[MAX_VERTICES];

    for (int v = 0; v < n; v++) {
        int comp = components[v];
        int i;

        for (i = 0; i < compCnt; i++) if (uniqueComps[i] == comp) break;

        if (i == compCnt) {
            uniqueComps[compCnt] = comp;
            comp2idx[comp] = compCnt;
            compCnt++; 
        }
    }

    MatGraph* gPrime = mat_graph_create(compCnt);
    *gPrimePtr = gPrime;

    for (int u = 0; u < n; u++) {
        for (int v = u + 1; v < n; v++) {
            if (g->adjMat[u][v] > 0) {
                int compU = components[u];
                int compV = components[v];

                if (compU != compV) {
                    int uIdx = comp2idx[compU];
                    int vIdx = comp2idx[compV];

                    if (gPrime->adjMat[uIdx][vIdx] != 0 ||
                        g->adjMat[u][v] < gPrime->adjMat[uIdx][vIdx]) {
                            mat_graph_add_undirected_edge(
                                gPrime,
                                uIdx,
                                vIdx,
                                g->adjMat[u][v]
                            );
                    }
                }
            }
        }
    }
}

#pragma endregion 21-2

int main(void) {
    switch (TASK)
    {
        case 1: {
            // 21-1
            MatGraph* g = mat_graph_create(5);

            mat_graph_add_undirected_edge(g, 0, 1, 4);
            mat_graph_add_undirected_edge(g, 1, 2, 3);
            mat_graph_add_undirected_edge(g, 2, 3, 5);
            mat_graph_add_undirected_edge(g, 3, 4, 6);
            mat_graph_add_undirected_edge(g, 1, 4, 7);

            // compute_max_edges(g);

            // for (int u = 0; u < g->numVertices; u++) {
            //     for (int v = u + 1; v < g->numVertices; v++) {
            //         printf("maxEdge[%d][%d] = %d\n", u, v, maxEdge[u][v]);
            //     }
            // }

            Edge edges[MAX_EDGES];
            int edgeCnt = 0;
            for (int u = 0; u < g->numVertices; u++) {
                for (int v = u + 1; v < g->numVertices; v++) {
                    if (g->adjMat[u][v]) {
                        edges[edgeCnt].u = u;
                        edges[edgeCnt].v = v;
                        edges[edgeCnt].weight = g->adjMat[u][v];
                        edgeCnt++;
                    }
                }
            }

            MatGraph* mst = mat_graph_create(g->numVertices);
            int mst_weight = kruskal(g, edges, edgeCnt, mst);

            printf("MST weight: %d\n", mst_weight);

            int second_best = find_second_best_mst_weight(g, mst, edges, edgeCnt, mst_weight);
            if (second_best != -1) printf("Second-best MST weight: %d\n", second_best);
            else printf("No second-best MST exists.\n");

            mat_graph_free(mst);
            mat_graph_free(g);
            break;
        }

        case 2: {
            // 21.2
            MatGraph* g = mat_graph_create(6);

            mat_graph_add_undirected_edge(g, 0, 1, 4);
            mat_graph_add_undirected_edge(g, 0, 2, 3);
            mat_graph_add_undirected_edge(g, 1, 2, 5);
            mat_graph_add_undirected_edge(g, 1, 3, 2);
            mat_graph_add_undirected_edge(g, 2, 3, 6);
            mat_graph_add_undirected_edge(g, 2, 4, 2);
            mat_graph_add_undirected_edge(g, 3, 4, 3);
            mat_graph_add_undirected_edge(g, 3, 5, 4);
            mat_graph_add_undirected_edge(g, 4, 5, 5);

            printf("Original graph:\n");
            mat_graph_print(g);

            MatGraph* gPrime = NULL;
            Edge T[MAX_VERTICES];
            int T_size = 0; 

            // mst_reduce(g, &gPrime, T, &T_size);
            mst_reduce_optimized(g, &gPrime, T, &T_size);

            printf("Reduced graph:\n");
            mat_graph_print(gPrime);

            printf("\n");
            print_mst_edges(T, T_size);

            mat_graph_free(gPrime);
            mat_graph_free(g);
            break;
        }
        
        default:
            break;
    }

    return 0;
}