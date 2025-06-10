#include "part_6_graph_algorithms/21_minimum_spanning_trees/minimum_spanning_trees.h"

#define TASK 4

#pragma region 21-1 Second best MST

int parent[MAX_VERTICES], depth[MAX_VERTICES];
int maxEdge[MAX_VERTICES][MAX_VERTICES];

void mat_graph_dfs_set_p_d(MatGraph* g, int u, int p, int d) {
    parent[u] = p;
    depth[u] = d;
    for (int v = 0; v < g->numVertices; v++) {
        if (g->adjMat[u][v] && v != p) mat_graph_dfs_set_p_d(g, v, u, d + 1);
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
    mat_graph_dfs_set_p_d(g, 0, -1, 0);
    for (int u = 0; u < g->numVertices; u++) {
        for (int v = 0; v < g->numVertices; v++) {
            if (u == v) maxEdge[u][v] = 0;
            else maxEdge[u][v] = max_on_path(g, u, v);
        }
    }
}

int compare_edges(const void* a, const void* b) {
    Edge* ea = (Edge*)a;
    Edge* eb = (Edge*)b;
    return ea->weight - eb->weight;
}

int mst_kruskal(MatGraph* g, Edge* edges, int edgeCnt, MatGraph* mst) {
    make_set(g->numVertices, 1);
    qsort(edges, edgeCnt, sizeof(Edge), compare_edges);

    int mstWeight = 0;
    int mstEdges = 0;

    for (int i = 0; i < edgeCnt; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].weight;
        if (!is_same_component(u, v)) {
            union_sets(u, v);
            mat_graph_add_undirected_weighted_edge(mst, u, v, w);
            mstWeight += w;
            mstEdges++;
            printf("MST edge: %d - %d (weight %d)\n", u, v, w);
            if (mstEdges == g->numVertices - 1) break;
        }
    }

    return mstWeight;
}

int find_second_best_mst_weight(
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

#pragma endregion 21-1 Second best MST

#pragma region 21-2 Minimum spanning tree in sparse graphs

void mst_reduce(MatGraph* g, MatGraph** gPrimePtr, Edge* t, int* tSize) {
    int n = g->numVertices;
    int marked[MAX_VERTICES] = {0};

    make_set(n, 1);

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
        int rep = find(v);
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
                int repU = find(u);
                int repV = find(v);

                if (repU != repV) {
                    int uIdx = rep2idx[repU];
                    int vIdx = rep2idx[repV];

                    if (gPrime->adjMat[uIdx][vIdx] == 0 ||
                        g->adjMat[u][v] == gPrime->adjMat[uIdx][vIdx]) 
                        mat_graph_add_undirected_weighted_edge(
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
                            mat_graph_add_undirected_weighted_edge(
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

#pragma endregion 21-2 Minimum spanning tree in sparse graphs

#pragma region 21-3 Alternative minimum-spanning-tree algorithms

int compare_edges_descending(const void* a, const void* b) {
    Edge* ea = (Edge*)a;
    Edge* eb = (Edge*)b;
    return eb->weight - ea->weight;
}

void print_maybe_mst_edges(Edge* edges, int size) {
    printf("\nMST edges from a maybe-mst:\n");
    int totalW = 0;
    for (int i = 0; i < size; i++) {
        printf("(%d, %d) weight: %d\n", edges[i].u, edges[i].v, edges[i].weight);
        totalW += edges[i].weight;
    }
    printf("Total MST weight: %d\n", totalW);
}

void maybe_mst_a(MatGraph* g, Edge* resultEdges, int* resultSize) {
    /*
        Returns the MST.
        Time complexity: O(E^2).
    */
    Edge edges[MAX_EDGES];
    int edgeCnt = 0;

    for (int u = 0; u < g->numVertices; u++) {
        for (int v = u + 1; v < g->numVertices; v++) {
            if (g->adjMat[u][v] > 0) {
                edges[edgeCnt].u = u;
                edges[edgeCnt].v = v;
                edges[edgeCnt].weight = g->adjMat[u][v];
                edgeCnt++;
            }
        }
    }

    qsort(edges, edgeCnt, sizeof(Edge), compare_edges_descending);

    MatGraph* T = mat_graph_create(g->numVertices);
    for (int i = 0; i < edgeCnt; i++) {
        mat_graph_add_undirected_weighted_edge(T, edges[i].u, edges[i].v, edges[i].weight);
    }

    printf("Starting with all %d edges\n", edgeCnt);

    for (int i = 0; i < edgeCnt; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].weight;

        mat_graph_remove_undirected_edge(T, u, v);

        if (mat_graph_is_connected(T)) 
            printf("Removed edge (%d, %d) with weight %d\n", u, v, w);
        else {
            mat_graph_add_undirected_weighted_edge(T, u, v, w);
            printf("Kept edge (%d, %d) with weight %d\n", u, v, w);
        }
    }

    *resultSize = 0;
    for (int u = 0; u < T->numVertices; u++) {
        for (int v = u + 1; v < T->numVertices; v++) {
            if (T->adjMat[u][v] > 0) {
                resultEdges[*resultSize].u = u;
                resultEdges[*resultSize].v = v;
                resultEdges[*resultSize].weight = T->adjMat[u][v];
                (*resultSize)++;
            }
        }
    }

    mat_graph_free(T);
}

void maybe_mst_b(MatGraph* g, Edge* resultEdges, int* resultSize) {
    /*
        Does not return the MST.
        Time complexity: O(E*α(V)), 
        where α is the inverse Ackermann function.
    */
    int n = g->numVertices;
    make_set(n, 1);

    *resultSize = 0;
    Edge edges[MAX_EDGES];
    int edgeCnt = 0;

    for (int u = 0; u < n; u++) {
        for (int v = u + 1; v < n; v++) {
            if (g->adjMat[u][v] > 0) {
                edges[edgeCnt].u = u;
                edges[edgeCnt].v = v;
                edges[edgeCnt].weight = g->adjMat[u][v];
                edgeCnt++;
            }
        }
    }
    
    printf("Processing %d edges in arbitrary order\n", edgeCnt); 

    for (int i = 0; i < edgeCnt; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].weight;

        if (!is_same_component(u, v)) {
            union_sets(u, v);
            resultEdges[*resultSize] = edges[i];
            (*resultSize)++;
            printf("Added edge (%d, %d) with weight %d\n", u, v, w);
        } else printf("Skipped edge (%d, %d) with weight %d\n", u, v, w);
    }
} 

void find_cycle_and_max_edge(
    MatGraph* g, 
    int u, 
    int v, 
    int* uMax, 
    int* vMax, 
    int* weightMax
) {
    int origWeight = g->adjMat[u][v];
    g->adjMat[u][v] = 0;
    g->adjMat[v][u] = 0;

    int visited[MAX_VERTICES] = {0};

    for (int i = 0; i < g->numVertices; i++) parent[i] = -1;

    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    queue[rear++] = u;
    visited[u] = 1;

    while (front < rear) {
        int curr = queue[front++];
        if (curr == v) break;
        for (int adj = 0; adj < g->numVertices; adj++) {
            if (g->adjMat[curr][adj] > 0 && !visited[adj]) {
                queue[rear++] = adj;
                visited[adj] = 1;
                parent[adj] = curr;
            }
        }
    }

    g->adjMat[u][v] = origWeight;
    g->adjMat[v][u] = origWeight;

    *weightMax = origWeight;
    *uMax = u;
    *vMax = v;

    int curr = v;
    while (curr != u) {
        int prev = parent[curr];
        if (g->adjMat[prev][curr] > *weightMax) {
            *weightMax = g->adjMat[prev][curr];
            *uMax = prev;
            *vMax = curr;
        }
        curr = prev;
    }
}

void maybe_mst_c(MatGraph* g, Edge* resultEdges, int* resultSize) {
    /*
        Return the MST.
        Time complexity: O(E*V).
    */
    int n = g->numVertices;
    *resultSize = 0;

    MatGraph* T = mat_graph_create(n);

    Edge edges[MAX_EDGES];
    int edgeCnt = 0;

    for (int u = 0; u < n; u++) {
        for (int v = u + 1; v < n; v++) {
            if (g->adjMat[u][v] > 0) {
                edges[edgeCnt].u = u;
                edges[edgeCnt].v = v;
                edges[edgeCnt].weight = g->adjMat[u][v];
                edgeCnt++;
            }
        }
    }   
    printf("Processing %d edges in arbitrary order\n", edgeCnt);
    for (int i = 0; i < edgeCnt; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].weight;
        
        printf("Considering edge (%d, %d) with weight %d\n", u, v, w);

        int hasPath = mat_graph_check_if_path_exists(T, u, v);
        if (!hasPath) {
            mat_graph_add_undirected_weighted_edge(T, u, v, w);
            printf("Added edge (%d, %d) with weight %d\n", u, v, w);
        } else {
            mat_graph_add_undirected_weighted_edge(T, u, v, w);
            int uMax = -1, vMax = -1, weightMax = -1;
            find_cycle_and_max_edge(T, u, v, &uMax, &vMax, &weightMax);
            mat_graph_remove_undirected_edge(T, uMax, vMax);
            if (uMax == u && vMax == v) 
                printf("Skipped edge (%d, %d) with weight %d\n", u, v, w);
            else {
                printf("Added edge (%d, %d) with weight %d\n", u, v, w);
                printf("Removed edge (%d, %d) with weight %d (max weight on cycle)\n", 
                       uMax, vMax, weightMax);
            }
        }
    }

    for (int u = 0; u < n; u++) {
        for (int v = u + 1; v < n; v++) {
            if (T->adjMat[u][v] > 0) {
                resultEdges[*resultSize].u = u;
                resultEdges[*resultSize].v = v;
                resultEdges[*resultSize].weight = T->adjMat[u][v];
                (*resultSize)++;
            }
        }
    }

    mat_graph_free(T);
}

#pragma endregion 21-3 Alternative minimum-spanning-tree algorithms

#pragma region 21-4 Bottleneck spanning tree

int mat_graph_has_bottleneck_spanning_tree(MatGraph* g, int b) {
    MatGraph* filtered = mat_graph_create(g->numVertices);

    for (int u = 0; u < g->numVertices; u++) {
        for (int v = u + 1; v < g->numVertices; v++) {
            if (g->adjMat[u][v] > 0 && g->adjMat[u][v] <= b)
                mat_graph_add_undirected_weighted_edge(filtered, u, v, g->adjMat[u][v]);
        }
    } 

    int isConnected = mat_graph_is_connected(filtered);
    mat_graph_free(filtered);
    return isConnected;
}

void mat_graph_contract_edges(
    MatGraph* g, 
    int threshold, 
    MatGraph** contractedGraph
) {
    int n = g->numVertices;
    int components[MAX_VERTICES];
    for (int i = 0; i < n; i++) components[i] = i;

    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (g->adjMat[u][v] > 0 && g->adjMat[u][v] <= threshold) {
                int uComp = components[u];
                int vComp = components[v];

                if (uComp != vComp) {
                    for (int i = 0; i < n; i++) {
                        if (components[i] == vComp) components[i] = uComp;
                    }
                }
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
    *contractedGraph = gPrime;

    for (int u = 0; u < n; u++) {
        for (int v = u + 1; v < n; v++) {
            if (g->adjMat[u][v] > threshold) {
                int uComp = components[u];
                int vComp = components[v];
                if (uComp != vComp) {
                    int uIdx = comp2idx[uComp];
                    int vIdx = comp2idx[vComp];
                    if (gPrime->adjMat[uIdx][vIdx] == 0 ||
                        g->adjMat[u][v] < gPrime->adjMat[uIdx][vIdx])
                            mat_graph_add_undirected_weighted_edge(
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

int find_bottleneck_spanning_tree(MatGraph* g) {
    int n = g->numVertices;
    int edgeCnt = 0;
    int edgeWeights[MAX_EDGES];

    for (int u = 0; u < n; u++) {
        for (int v = u + 1; v < n; v++) {
            if (g->adjMat[u][v] > 0) edgeWeights[edgeCnt++] = g->adjMat[u][v];
        }
    }

    if (edgeCnt == 0) return -1;
    if (edgeCnt == 1) return edgeWeights[0];

    int medianIdx = edgeCnt / 2;
    int median = select_kth(edgeWeights, 0, edgeCnt - 1, medianIdx);

    printf("Median edge weight: %d\n", median);

    if (mat_graph_has_bottleneck_spanning_tree(g, median)) {
        printf("Found botteleneck spanning tree weight weight <= %d\n", median);
        MatGraph* filtered = mat_graph_create(n);
        for (int u = 0; u < n; u++) {
            for (int v = u + 1; v < n; v++) {
                if (g->adjMat[u][v] > 0 && g->adjMat[u][v] <= median)
                    mat_graph_add_undirected_weighted_edge(filtered, u, v, g->adjMat[u][v]);
            }
        }
        int result = find_bottleneck_spanning_tree(filtered);
        mat_graph_free(filtered);
        return result;
    } else {
        printf("No bottleneck spanning tree with weight <= %d\n", median);

        MatGraph* contracted;
        mat_graph_contract_edges(g, median, &contracted);

        printf("Contracted graph has %d vertices\n", contracted->numVertices);
        
        int result = find_bottleneck_spanning_tree(contracted);
        mat_graph_free(contracted);
        return result == -1 ? median + 1 : result;
    }
}

#pragma endregion 21-4 Bottleneck spanning tree

int main(void) {
    switch (TASK)
    {
        case 1: {
            // 21-1
            MatGraph* g = mat_graph_create(5);

            mat_graph_add_undirected_weighted_edge(g, 0, 1, 4);
            mat_graph_add_undirected_weighted_edge(g, 1, 2, 3);
            mat_graph_add_undirected_weighted_edge(g, 2, 3, 5);
            mat_graph_add_undirected_weighted_edge(g, 3, 4, 6);
            mat_graph_add_undirected_weighted_edge(g, 1, 4, 7);

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
            int mst_weight = mst_kruskal(g, edges, edgeCnt, mst);

            printf("MST weight: %d\n", mst_weight);

            int second_best = find_second_best_mst_weight(mst, edges, edgeCnt, mst_weight);
            if (second_best != -1) printf("Second-best MST weight: %d\n", second_best);
            else printf("No second-best MST exists.\n");

            mat_graph_free(mst);
            mat_graph_free(g);
            break;
        }

        case 2: {
            // 21.2
            MatGraph* g = mat_graph_create(6);

            mat_graph_add_undirected_weighted_edge(g, 0, 1, 4);
            mat_graph_add_undirected_weighted_edge(g, 0, 2, 3);
            mat_graph_add_undirected_weighted_edge(g, 1, 2, 5);
            mat_graph_add_undirected_weighted_edge(g, 1, 3, 2);
            mat_graph_add_undirected_weighted_edge(g, 2, 3, 6);
            mat_graph_add_undirected_weighted_edge(g, 2, 4, 2);
            mat_graph_add_undirected_weighted_edge(g, 3, 4, 3);
            mat_graph_add_undirected_weighted_edge(g, 3, 5, 4);
            mat_graph_add_undirected_weighted_edge(g, 4, 5, 5);

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

        case 3: {
            // 21-3 
            printf("Testing alternative MST algorithms:\n");
            MatGraph* g = mat_graph_create(6);
            
            mat_graph_add_undirected_weighted_edge(g, 0, 1, 4);
            mat_graph_add_undirected_weighted_edge(g, 0, 2, 3);
            mat_graph_add_undirected_weighted_edge(g, 1, 2, 5);
            mat_graph_add_undirected_weighted_edge(g, 1, 3, 2);
            mat_graph_add_undirected_weighted_edge(g, 2, 3, 6);
            mat_graph_add_undirected_weighted_edge(g, 2, 4, 2);
            mat_graph_add_undirected_weighted_edge(g, 3, 4, 3);
            mat_graph_add_undirected_weighted_edge(g, 3, 5, 4);
            mat_graph_add_undirected_weighted_edge(g, 4, 5, 5);

            printf("Original graph: \n");
            mat_graph_print(g);

            // Maybe MST a
            printf("\nRunning MAYBE-MST-A algorithm:\n");
            Edge resultEdgesA[MAX_EDGES];
            int resultSizeA = 0;
            maybe_mst_a(g, resultEdgesA, &resultSizeA);
            printf("\nMST edges from MAYBE-MST-A:\n");
            print_maybe_mst_edges(resultEdgesA, resultSizeA);

            // Maybe MST b
            printf("\nRunning MAYBE-MST-B algorithm:\n");
            Edge resultEdgesB[MAX_EDGES];
            int resultSizeB = 0;
            maybe_mst_b(g, resultEdgesB, &resultSizeB);
            printf("\nMST edges from MAYBE-MST-B:\n");
            print_maybe_mst_edges(resultEdgesB, resultSizeB);

            // Maybe MST c
            printf("\nRunning MAYBE-MST-C algorithm:\n");
            Edge resultEdgesC[MAX_EDGES];
            int resultSizeC = 0;
            maybe_mst_c(g, resultEdgesC, &resultSizeC);
            print_maybe_mst_edges(resultEdgesC, resultSizeC);

            mat_graph_free(g);
            break;
        }

        case 4: {
            // 21-4
            MatGraph* g = mat_graph_create(6);
        
            mat_graph_add_undirected_weighted_edge(g, 0, 1, 4);
            mat_graph_add_undirected_weighted_edge(g, 0, 2, 3);
            mat_graph_add_undirected_weighted_edge(g, 1, 2, 5);
            mat_graph_add_undirected_weighted_edge(g, 1, 3, 2);
            mat_graph_add_undirected_weighted_edge(g, 2, 3, 6);
            mat_graph_add_undirected_weighted_edge(g, 2, 4, 2);
            mat_graph_add_undirected_weighted_edge(g, 3, 4, 3);
            mat_graph_add_undirected_weighted_edge(g, 3, 5, 4);
            mat_graph_add_undirected_weighted_edge(g, 4, 5, 5);

            printf("Original graph:\n");
            mat_graph_print(g);

            int bottleneck = find_bottleneck_spanning_tree(g);
            printf("Bottleneck spanning tree value: %d\n", bottleneck);

            mat_graph_free(g);
            break;
        }

        default:
            break;
    }

    return 0;
}