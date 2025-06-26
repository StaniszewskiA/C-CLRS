#include "part_6_graph_algorithms/24_maximum_flow/maximum_flow.h"

#define TASK 5

int main(void) {
    switch (TASK)
    {
        case 1: {
            // Basic Ford-Fulkerson
            int n = 3;
            FlowMatGraph* g = flow_mat_graph_create(n);
            flow_mat_graph_add_directed_edge(g, 0, 1, 3);
            flow_mat_graph_add_directed_edge(g, 1, 2, 2);
            flow_mat_graph_add_directed_edge(g, 0, 2, 1);

            int maxFlow = ford_fulkerson(g, 0, 2);
            printf("Maximum flow: %d\n", maxFlow);

            flow_mat_graph_free(g);
            break;
        }

        case 2: {
            // Edmonds-Karp
            int n = 3;
            FlowMatGraph* g = flow_mat_graph_create(n);
            flow_mat_graph_add_directed_edge(g, 0, 1, 3);
            flow_mat_graph_add_directed_edge(g, 1, 2, 2);
            flow_mat_graph_add_directed_edge(g, 0, 2, 1);

            int maxFlow = edmonds_karp(g, 0, 2);
            printf("Maximum flow: %d\n", maxFlow);

            flow_mat_graph_free(g);
            break;
        }

        case 3: {
            // 24.2-10
            int n = 3;
            FlowMatGraph* g = flow_mat_graph_create(n);
            flow_mat_graph_add_directed_edge(g, 0, 1, 3);
            flow_mat_graph_add_directed_edge(g, 1, 2, 2);
            flow_mat_graph_add_directed_edge(g, 0, 2, 1);

            int maxFlow = edmonds_karp(g, 0, 2);
            printf("Maximum flow: %d\n", maxFlow);

            decompose_flow(g, 0, 2);

            flow_mat_graph_free(g);

            break;
        }

        case 4: {
            // 24.2-11
            int n = 5;
            FlowMatGraph* g = flow_mat_graph_create(n);
            flow_mat_graph_add_undirected_edge(g, 0, 1);
            flow_mat_graph_add_undirected_edge(g, 1, 2);
            flow_mat_graph_add_undirected_edge(g, 2, 3);
            flow_mat_graph_add_undirected_edge(g, 3, 4);
            flow_mat_graph_add_undirected_edge(g, 4, 0); // cycle

            int k = flow_graph_edge_connectivity(g);
            printf("Edge connectivity of the passed graph: %d\n", k);

            flow_mat_graph_free(g);
            break;
        }

        case 5: {
            // 24.2-12
            int n = 4;
            FlowMatGraph* g = flow_mat_graph_create(n);
            
            flow_mat_graph_add_directed_edge(g, 0, 1, 3);
            flow_mat_graph_add_directed_edge(g, 1, 2, 2);
            flow_mat_graph_add_directed_edge(g, 2, 3, 2);
            flow_mat_graph_add_directed_edge(g, 2, 0, 1);

            int maxFlow = edmonds_karp(g, 0, 3);
            printf("Maximum flow: %d\n", maxFlow);

            printf("Adding artificial inflow to source for testing...\n");
            g->flow[2][0] = 1;
            g->flow[0][1] = 1;

            print_flow_matrix(g, "Flow matrix before cancelling the source inflow:\n");

            cancel_out_src_inflow(g, 0);

            print_flow_matrix(g, "Flow matrix after cancelling the source inflow:\n");

            flow_mat_graph_free(g);
            break;
        }
        
        default:
            break;
    }
    
    return 0;
}
