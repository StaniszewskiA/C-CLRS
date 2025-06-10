#include "part_6_graph_algorithms/24_maximum_flow/maximum_flow.h"

int main(void) {
    int leftSize = 3;
    int rightSize = 3;
    int edges[][2] = {
        {0, 0}, {0, 1}, 
        {1, 1}, {1, 2}, 
        {2, 0}, {2, 2} 
    };
    int numEdges = 6;

    FlowMatGraph* g = create_bipartite_flow_graph(
        leftSize, rightSize, edges, numEdges);

    int src = 0;
    int sink = g->numVertices - 1;

    int maxMatching = edmonds_karp(g, src, sink);

    printf("Maximum matching size: %d\n", maxMatching);
    print_bipartite_matching(g, leftSize, rightSize);

    flow_mat_graph_free(g);
    return 0;
}