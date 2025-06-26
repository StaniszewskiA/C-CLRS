#include "part_6_graph_algorithms/24_maximum_flow/maximum_flow.h"

#pragma region Maximum bipartite matching

FlowMatGraph* create_bipartite_flow_graph(
    int leftSize,
    int rightSize,
    int bipartiteEdges[][2],
    int numEdges
) {
    int totalVertices = 2 + leftSize + rightSize; // both parts, sink, source
    FlowMatGraph* g = flow_mat_graph_create(totalVertices);
    int src = 0;
    int sink = totalVertices - 1;

    // src to left
    for (int i = 0; i < leftSize; i++) {
        int leftVertex = i + 1;
        flow_mat_graph_add_directed_edge(g, src, leftVertex, 1);
    }

    // right to sink
    for (int i = 0; i < rightSize; i++) {
        int rightVertex = 1 + leftSize + i;
        flow_mat_graph_add_directed_edge(g, rightVertex, sink, 1);
    }

    for (int i = 0; i < numEdges; i++) {
        int leftIdx = bipartiteEdges[i][0];
        int rightIdx = bipartiteEdges[i][1];

        int leftVertex = 1 + leftIdx;
        int rightVertex = 1 + leftSize + rightIdx;

        flow_mat_graph_add_directed_edge(g, leftVertex, rightVertex, 1);
    }

    return g;
}

void print_bipartite_matching(FlowMatGraph* g, int leftSize, int rightSize) {
    printf("Maximum Bipartite Matching:\n");
    int matchingCnt = 0; 

    for (int i = 1; i <= leftSize; i++) { 
        for (int j = 1 + leftSize; j < 1 + leftSize + rightSize; j++) { 
            if (g->flow[i][j] == 1) { // 
                printf("Left vertex %d matched with Right vertex %d\n",
                    i - 1,        
                    j - (1 + leftSize)); 
                matchingCnt++;
            }
        }
    }
    printf("Total matching size: %d\n", matchingCnt);
}

#pragma endregion Maximum bipartite matching
