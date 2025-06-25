#include "part_6_graph_algorithms/25_bipartite_matching/bipartite_matching.h"

#define TASK 3

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

#pragma endregion Other matching-related problems

#pragma region Fractional matching

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
    }

    return 0;
}