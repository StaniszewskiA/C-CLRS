#include "part_6_graph_algorithms/25_bipartite_matching/bipartite_matching.h"

#define TASK 1

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


#pragma endregion Perfect matching in regular bipartite graphs

#pragma region Reducing the running time of the Hungarian algorithm to O(n^3)

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
    }

    return 0;
}