#include "part_6_graph_algorithms/25_bipartite_matching/bipartite_matching.h"

#define TASK 6

#pragma region Perfect matching in regular bipartite graphs

static void dfs_connected(MatGraph* g, int u, int* visited) {
    visited[u] = 1;
    for (int v = 0; v < g->numVertices; ++v) {
        if (g->adjMat[u][v] && !visited[v]) {
            dfs_connected(g, v, visited);
        }
    }
}

static int mat_graph_is_connected_and_nontrivial(MatGraph* g) {
    int visited[MAX_GRAPH_VERTICES] = {0};
    int startingNode = -1;
    int i, j, deg;

    // Find the starting node
    for (i = 0; i < g->numVertices; ++i) {
        deg = 0;
        for (j = 0; j < g->numVertices; ++j) deg += g->adjMat[i][j];
        if (deg > 0) {
            startingNode = i;
            break;
        }
    }

    if (startingNode == -1) return 0;
    dfs_connected(g, startingNode, visited);

    // Verify connectivity
    for (i = 0; i < g->numVertices; ++i) {
        deg = 0;
        for (j = 0; j < g->numVertices; ++j) deg += g->adjMat[i][j];
        if (deg > 0 && ! visited[i]) return 0;
    }

    return 1;
}

static int all_degs_even(MatGraph* g) {
    int i, j, deg;
    for (i = 0; i < g->numVertices; ++i) {
        deg = 0;
        for (j = 0; j < g->numVertices; ++j) deg += g->adjMat[i][j];
        if (deg & 1) return 0;
    }
    return 1;
}

void hierholzer_euler_cycle(MatGraph* g, int start) {
    MatGraph temp = *g;
    Stack stack;
    Stack circuit;

    stack_init(&stack);
    stack_init(&circuit);

    stack_push(&stack, start);

    while (!stack_is_empty(&stack)) {
        int v = stack_peek(&stack);
        int found = 0;
            for (int u = 0; u < temp.numVertices; ++u) {
                if (!temp.adjMat[v][u]) continue;

                temp.adjMat[v][u]--;
                temp.adjMat[u][v]--;
                stack_push(&stack, u);
                found = 1;
                break;
            }

        if (found) continue;
        
        stack_pop(&stack);
        stack_push(&circuit, v);
    }

    printf("Euler circuit: ");
    while (!stack_is_empty(&circuit)) 
        printf("%d ", stack_pop(&circuit));
    printf("\n");
}

void test_hierholzer_algorithm(void) {
    int edges[][2] = {
        {0, 1}, 
        {1, 2}, 
        {2, 3}, 
        {3, 0}, 
    };
    int n = ARRAY_SIZE(edges);
    MatGraph* g = mat_graph_create(n, 0);

    for (int i = 0; i < n; ++i)
        mat_graph_add_undirected_edge(g, edges[i][0], edges[i][1]);

    if (mat_graph_is_connected_and_nontrivial(g) && all_degs_even(g)) {
        hierholzer_euler_cycle(g, 0);
    } else {
        printf("Graph does not contain an euler cycle");
    }

    mat_graph_free(g);
}

BipartiteGraph* bipartite_graph_copy(BipartiteGraph* target) {
    BipartiteGraph* copy = bipartite_graph_init(
        target->leftSize, target->rightSize);

    for (int u = 1; u <= target->leftSize; ++u) {
        copy->adjSize[u] = target->adjSize[u];
        for (int i = 0; i < target->adjSize[u]; ++i) {
            copy->adj[u][i] = target->adj[u][i];
        }
    }

    return copy;
}

void extract_perfect_matching(BipartiteGraph* g, int* matching) {
    for (int u = 1; u <= g->leftSize; ++u) {
        if (g->adjSize[u] > 0) matching[u] = g->adj[u][0];
        else matching[u] = -1;
    }
}

void split_bipartite_graph(
    BipartiteGraph* g,
    BipartiteGraph* g1,
    BipartiteGraph* g2
) {
    for (int u = 1; u <= g->leftSize; ++u) {
        for (int i = 0; i < g->adjSize[u]; ++i) {
            int v = g->adj[u][i];
            if (i & 1) bipartite_graph_add_edge(g1, u, v);
            else bipartite_graph_add_edge(g2, u, v);
        }
    }
}

void find_d_perfect_matchings(
    BipartiteGraph* g,
    int d,
    int leftSize,
    int rightSize,
    int** matchings,
    int* matchingIdx
) {
    if (d == 1) {
        extract_perfect_matching(g, matchings[*matchingIdx]);
        (*matchingIdx)++;
        return;
    }

    BipartiteGraph* g1 = bipartite_graph_init(leftSize, rightSize);
    BipartiteGraph* g2 = bipartite_graph_init(leftSize, rightSize);

    split_bipartite_graph(g, g1, g2);

    find_d_perfect_matchings(g1, d / 2, leftSize, rightSize, matchings, matchingIdx);
    find_d_perfect_matchings(g2, d / 2, leftSize, rightSize, matchings, matchingIdx);

    free(g1);
    free(g2);
}

void test_perfect_matching_decomposition(void) {
    int d = 4;
    int leftSize = d;
    int rightSize = d;

    BipartiteGraph* g = bipartite_graph_init(leftSize, rightSize);

    for (int u = 1; u <= leftSize; ++u)
        for (int v = 1; v <= rightSize; ++v)
        bipartite_graph_add_edge(g, u, v);

    int** matchings = (int**)safe_malloc(d * sizeof(int*));
    for (int i = 0; i < d; ++i)
        matchings[i] = (int*)safe_malloc((leftSize + 1) * sizeof(int));
    int matchingIdx = 0;

    find_d_perfect_matchings(g, d, leftSize, rightSize, matchings, &matchingIdx);

    printf("Found %d disjoint perfect matchings:\n", d);
    for (int i = 0; i < d; ++i) {
        printf("Matching %d: ", i+1);
        for (int u = 1; u <= leftSize; ++u) {
            printf("(U%d-V%d) ", u, matchings[i][u]);
        }
        printf("\n");
    }

    for (int i = 0; i < d; ++i) safe_free(matchings[i]);
    safe_free(matchings);
    safe_free(g);
}

#pragma endregion Perfect matching in regular bipartite graphs

#pragma region Reducing the running time of the Hungarian algorithm to O(n^3)

HungarianInstance* hungarian_init(int n) {
    HungarianInstance* instance = (HungarianInstance*)safe_malloc(sizeof(HungarianInstance));
    instance->n = n;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            instance->cost[i][j] = 0;

    return instance;
}

void hungarian_set_cost(HungarianInstance* instance, int i, int j, int cost) {
    instance->cost[i][j] = cost;
}

void hungarian_free(HungarianInstance* instance) {
    if (instance) safe_free(instance);
}

int hungarian_solve(HungarianInstance* instance, int* matching) {
    int n = instance->n;
    int leftPotential[NMAX + 1] = {0};
    int rightPotential[NMAX + 1] = {0};
    int rightAssignment[NMAX + 1] = {0}; 
    int left, right;

    for (left = 1; left <= n; ++left) {
        leftPotential[left] = 0;
        for (right = 1; right <= n; ++right) {
            if (instance->cost[left - 1][right - 1] > leftPotential[left]) {
                leftPotential[left] = instance->cost[left - 1][right - 1];
            }
        }
    }

    for (left = 1; left <= n; ++left) {  
        rightAssignment[0] = left;
        int sigma[NMAX + 1];
        int leftSigma[NMAX + 1];
        int previousRight[NMAX + 1] = {0};
        char rightVisited[NMAX + 1] = {0};
        char leftVisited[NMAX + 1] = {0};
        int currRight = 0;

        // Initialize sigmas 
        for (right = 1; right <= n; ++right) {
            sigma[right] = leftPotential[left] + rightPotential[right] - instance->cost[left - 1][right - 1];
            leftSigma[right] = left;
        }

        do {
            rightVisited[currRight] = 1;
            int leftIdx = rightAssignment[currRight];
            leftVisited[leftIdx] = 1;
            int delta = INF;
            int nextRight = -1;

            for (right = 1; right <= n; ++right) {
                if (rightVisited[right]) continue;
                if (sigma[right] >= delta) continue;
                delta = sigma[right];
                nextRight = right;
            }

            for (int l = 1; l <= n; ++l) 
                if (leftVisited[l]) leftPotential[l] -= delta;
            
            for (int r = 0; r <= n; ++r) {
                if (rightVisited[r]) rightPotential[r] += delta;
                else sigma[r] -= delta;
            }

            for (right = 1; right <= n; ++right) {
                if (!rightVisited[right] && sigma[right] == 0) {
                    for (int l = 1; l <= n; ++l) {
                        if (!leftVisited[l]) continue;
                        int cost = instance->cost[l - 1][right - 1];
                        if (leftPotential[l] + rightPotential[right] - cost == 0) {
                            leftSigma[right] = l;
                            break;
                        }
                    }
                }
            }

            currRight = nextRight;
            previousRight[currRight] = leftSigma[currRight];

        } while (rightAssignment[currRight] != 0);

        do {
            int prevLeft = previousRight[currRight];
            int temp = rightAssignment[currRight];
            rightAssignment[currRight] = prevLeft;
            currRight = temp;
        } while (currRight != 0);
    }

    int totalCost = 0;
    for (right = 1; right <= n; ++right) {
        left = rightAssignment[right];
        if (left <= 0) continue; 
        matching[left - 1] = right - 1;
        totalCost += instance->cost[left - 1][right - 1];
    }

    return totalCost;
}

void test_hungarian_algorithm_n3(void) {
    int n = 4;
    int i, j;
    int costMat[4][4] = {
        {54, 54, 51, 53},
        {51, 57, 52, 52},
        {50, 53, 54, 56},
        {56, 54, 55, 53}
    };

    HungarianInstance* instance = hungarian_init(n);
    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
            hungarian_set_cost(instance, i, j, -costMat[i][j]);

        

    int matching[4];
    int minCost = hungarian_solve(instance, matching);

    printf("Optimal assignmeneted:\n");
    for (i = 0; i < n; ++i)
        printf(" %d -> %d (cost %d)\n", i, matching[i], costMat[i][matching[i]]);
    printf("Minimum cost: %d\n", -minCost);
    hungarian_free(instance);
}

#pragma endregion Reducing the running time of the Hungarian algorithm to O(n^3)

#pragma region Other matching-related problems

void hungarian_non_full_graph(
    BipartiteGraph* g,
    int costs[MAX_GRAPH_VERTICES][MAX_GRAPH_VERTICES],
    int leftSize,
    int rightSize,
    int* matching,
    int dummyEdgeMarker
) {
    int n = (leftSize > rightSize) ? leftSize : rightSize;
    AssignmentInstance* instance = assignment_init(n);

    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            if (u > leftSize || v > rightSize) {
                assignment_set_cost(instance, u, v, dummyEdgeMarker);
                continue;
            }
            char found = 0;

            for (int i = 0; i < g->adjSize[u]; ++i) {
                if (g->adj[u][i] == v) {
                    found = 1;
                    break;
                }
            }
            
            if (found) assignment_set_cost(instance, u, v, costs[u][v]);
            else assignment_set_cost(instance, u, v, dummyEdgeMarker);
        }
    } 

    int* tempMatching = assignment_solver(instance);

    // Reconstruct
    for (int u = 0; u < leftSize; ++u) {
        int v = tempMatching[u];
        if (v >= 0 && rightSize && costs[u][v] != INF) matching[u] = v;
        else matching[u] = -1;
    }

    safe_free(tempMatching);
    assignment_free(instance);
}

void test_hungarian_non_full(void) {
    int leftSize = 3;
    int rightSize = 4;
    BipartiteGraph* g = bipartite_graph_init(leftSize, rightSize);
    
    int edges[][2] = {
        {0, 0},
        {0, 1},
        {1, 1},
        {1, 2},
        {2, 0},
        {2, 3}
    };
    int n = ARRAY_SIZE(edges);
    for (int i = 0; i < n; ++i)
        bipartite_graph_add_edge(g, edges[i][0], edges[i][1]);

    int costs[MAX_GRAPH_VERTICES][MAX_GRAPH_VERTICES] = {{0}};
    costs[0][0] = 5; costs[0][1] = 8;
    costs[1][1] = 7; costs[1][2] = 6;
    costs[2][0] = 4; costs[2][3] = 9;

    int matching[MAX_GRAPH_VERTICES];
    hungarian_non_full_graph(g, costs, leftSize, rightSize, matching, 0);
    printf("Max weight matching:\n");
    int total = 0;

    for (int u = 0; u < leftSize; ++u) {
        if (matching[u] != -1) {
            printf("%d -> %d (w=%d)\n", u, matching[u], costs[u][matching[u]]);
            total += costs[u][matching[u]];
        } else printf("%d -> -\n", u);
    }

    printf("Total weight: %d\n", total);
    safe_free(g);
}

void hungarian_vertex_cycle_cover(MatGraph* g) {
    int n = g->numVertices;
    HungarianInstance* instance = hungarian_init(n);

    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            if (g->adjMat[u][v] > 0) hungarian_set_cost(instance, u, v, -g->adjMat[u][v]);
            else hungarian_set_cost(instance, u, v, INF);
        }
    }

    int* matching = (int*)safe_malloc(n * sizeof(int));
    hungarian_solve(instance, matching);
    char* visited = (char*)safe_calloc(n, sizeof(char));

    printf("Cycle cover:\n");
    for (int i = 0; i < n; ++i) {
        if (visited[i]) continue;
        int v = i;
        printf("Cycle: ");
        do {
            printf("%d ", v);
            visited[v] = 1;
            v = matching[v];
        } while (v != i && !visited[v]);
        printf("\n");
    } 

    int total = 0;
    for (int u = 0; u < n; ++u) {
        int v = matching[u];
        if (g->adjMat[u][v] != INF) total += g->adjMat[u][v];
    }

    printf("Total weight: %d\n", total);
    safe_free(matching);
    safe_free(visited);
    hungarian_free(instance);
}

void test_hungarian_vertex_cycle_cover(void) {
    int weightedEdges[][3] = {
        {0, 1, 10},
        {1, 2, 20},
        {2, 0, 30},
        {3, 1, 40},
        {1, 3, 50},
        {2, 3, 60},
        {3, 0, 70}
    };
    int numEdges = ARRAY_SIZE(weightedEdges);
    int n = 0;

    for (int i = 0; i < numEdges; ++i) {
        if (weightedEdges[i][0] > n) n = weightedEdges[i][0];
        if (weightedEdges[i][1] > n) n = weightedEdges[i][1];
    }
    n++;

    MatGraph* g = mat_graph_create(n, 0);

    for (int i = 0; i < numEdges; i++)
        mat_graph_add_directed_weighted_edge(g, weightedEdges[i][0], 
            weightedEdges[i][1], weightedEdges[i][2]);

    printf("Directed weighted graph adjacency matrix:\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) printf("%3d ", g->adjMat[i][j]);
        printf("\n");
    }

    hungarian_vertex_cycle_cover(g);

    mat_graph_free(g);
}

#pragma endregion Other matching-related problems

#pragma region Fractional matching

void fractional_to_matching(
    BipartiteGraph* g,
    float costs[MAX_GRAPH_VERTICES][MAX_GRAPH_VERTICES],
    int matching[MAX_GRAPH_VERTICES]
) {
    char usedU[MAX_GRAPH_VERTICES] = {0};
    char usedV[MAX_GRAPH_VERTICES] = {0};
    for (int u = 1; u <= g->leftSize; ++u) matching[u] = -1;

    while (1) {
        float maxVal = 0.0f;
        int maxU = -1;
        int maxV = -1;
        
        for (int u = 1; u <= g->leftSize; ++u) {
            if (usedU[u]) continue;
            for (int i = 0; i < g->adjSize[u]; ++i) {
                int v = g->adj[u][i];
                if (usedV[v]) continue;
                if (costs[u][v] <= maxVal) continue;
                maxVal = costs[u][v];
                maxU = u;
                maxV = v;
            }
        } 

        if (maxVal < 1e-6) break;
        matching[maxU] = maxV;
        usedU[maxU] = 1;
        usedV[maxV] = 1;
    }
}

void test_fractional_to_matching(void) {
    int n = 3;
    BipartiteGraph* g = bipartite_graph_init(n, n);

    int edges[][2] = {
        {1, 1},
        {1, 2},
        {2, 2},
        {2, 3},
        {3, 1},
        {3, 3}
    };
    int numEdges = ARRAY_SIZE(edges);

    for (int i = 0; i < numEdges; ++i) 
        bipartite_graph_add_edge(g, edges[i][0], edges[i][1]);
    
    float costs[MAX_GRAPH_VERTICES][MAX_GRAPH_VERTICES] = {{0}};
    costs[1][1] = 0.5; costs[1][2] = 0.5;
    costs[2][2] = 1.0; costs[2][3] = 0.5;
    costs[3][1] = 0.5; costs[3][3] = 0.5;

    printf("Initial fractional matching:\n");
    for (int u = 1; u <= n; ++u) {
        for (int v = 1; v <= n; ++v) {
            if (costs[u][v] < 1e-6) continue; 
            printf("  U%d -- V%d : %.2f\n", u, v, costs[u][v]);
        }
    }

    int matching[MAX_GRAPH_VERTICES];
    fractional_to_matching(g, costs, matching);
    printf("Casting fractional matching to a {0, 1} matching:\n");
    for (int u = 1; u <= n; ++u) {
        if (matching[u] != -1) printf("  U%d -- V%d\n", u, matching[u]);
        else printf("  U%d -- None\n", u);
    }

    safe_free(g);
}

#pragma endregion Fractional matching

#pragma region Computing vertex labels

#pragma endregion Computing vertex labels

int main(void) {
    switch(TASK) {
        case 1: {
            // The Hierholzer's algorithm
            test_hierholzer_algorithm();
            break;
        }

        case 2: {
            // Perfect matching decomposition
            test_perfect_matching_decomposition();
            break;
        }

        case 3: {
            // O(n^3) hungarian algorithm
            test_hungarian_algorithm_n3();
            break;
        }

        case 4: {
            // The hungarian method for non-full graphs
            test_hungarian_non_full();
            break;
        }

        case 5: {
            /*
                The vertex cycle cover problem
                reduced to perfect matching.
            */
            test_hungarian_vertex_cycle_cover();
            break;
        }

        case 6: {
            /*
                Cast fractional matching into
                {0, 1} values.
            */
            test_fractional_to_matching();
            break;
        }
    }

    return 0;
}