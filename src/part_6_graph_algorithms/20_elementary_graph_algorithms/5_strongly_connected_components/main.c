#include "part_6_graph_algorithms/20_elementary_graph_algorithms/elementary_graph_algorithms.h"

#define TASK 4

int main(void) {
    switch (TASK)
    {
        case 1: {
            // 20.5-5
            int numVertices = 8;
            MatGraph* g = mat_graph_create(numVertices);

            mat_graph_add_directed_edge(g, 0, 1);
            mat_graph_add_directed_edge(g, 1, 2);
            mat_graph_add_directed_edge(g, 2, 0);
            mat_graph_add_directed_edge(g, 3, 4);
            mat_graph_add_directed_edge(g, 4, 5);
            mat_graph_add_directed_edge(g, 5, 3);
            mat_graph_add_directed_edge(g, 6, 7);
            mat_graph_add_directed_edge(g, 7, 6);
            mat_graph_add_directed_edge(g, 2, 3);
            mat_graph_add_directed_edge(g, 5, 6);

            int component[MAX_VERTICES];
            int numComponents = kosaraju(g, component);

            printf("Number of strongly connected components: %d\n", numComponents);
            for (int v = 0; v < numVertices; v++) {
                printf("Vertex %d is in component %d\n", v, component[v]);
            }

            MatGraph* cg = build_component_graph(g, component, numComponents);
            printf("Component graph adjacency matrix:\n");
            for (int u = 0; u < numComponents; u++) {
                for (int v = 0; v < numComponents; v++) {
                    printf("%d ", cg->adjMat[u][v]);
                }
                printf("\n");
            }

            mat_graph_free(g);
            mat_graph_free(cg);
            break;
        }

        case 2: {
            // 20.5-6
            int numVertices = 8;
            MatGraph* g = mat_graph_create(numVertices);

            mat_graph_add_directed_edge(g, 0, 1);
            mat_graph_add_directed_edge(g, 1, 2);
            mat_graph_add_directed_edge(g, 2, 0);
            mat_graph_add_directed_edge(g, 3, 4);
            mat_graph_add_directed_edge(g, 4, 5);
            mat_graph_add_directed_edge(g, 5, 3);
            mat_graph_add_directed_edge(g, 6, 7);
            mat_graph_add_directed_edge(g, 7, 6);
            mat_graph_add_directed_edge(g, 2, 3);
            mat_graph_add_directed_edge(g, 5, 6);

            int component[MAX_VERTICES];
            int numComponents = kosaraju(g, component);

            MatGraph* gPrime = create_minimal_scc_graph(g, component, numComponents);

            printf("Minimal SCC graph adjacency matrix:\n");
            for (int u = 0; u < g->numVertices; u++) {
                for (int v = 0; v < g->numVertices; v++) {
                    printf("%d ", gPrime->adjMat[u][v]);
                }
                printf("\n");
            }

            mat_graph_free(g);
            mat_graph_free(gPrime);
            break;
        }

        case 3: {
            // 20.5-7
            int numVertices = 8;
            MatGraph* g = mat_graph_create(numVertices);

            mat_graph_add_directed_edge(g, 0, 1);
            mat_graph_add_directed_edge(g, 1, 2);
            mat_graph_add_directed_edge(g, 2, 0);
            mat_graph_add_directed_edge(g, 3, 4);
            mat_graph_add_directed_edge(g, 4, 5);
            mat_graph_add_directed_edge(g, 5, 3);
            mat_graph_add_directed_edge(g, 6, 7);
            mat_graph_add_directed_edge(g, 7, 6);
            mat_graph_add_directed_edge(g, 2, 3);
            mat_graph_add_directed_edge(g, 5, 6);

            printf("The graph is %ssemiconnected.\n", 
                mat_graph_is_semiconnected(g) ? "" : "not ");

            mat_graph_free(g);
            break;
        }

        case 4: {
            // 20.5-8
            int numVertices = 8;
            MatGraph* g = mat_graph_create(numVertices);

            mat_graph_add_directed_edge(g, 0, 1);
            mat_graph_add_directed_edge(g, 1, 2);
            mat_graph_add_directed_edge(g, 2, 0);
            mat_graph_add_directed_edge(g, 3, 4);
            mat_graph_add_directed_edge(g, 4, 5);
            mat_graph_add_directed_edge(g, 5, 3);
            mat_graph_add_directed_edge(g, 6, 7);
            mat_graph_add_directed_edge(g, 7, 6);
            mat_graph_add_directed_edge(g, 2, 3);
            mat_graph_add_directed_edge(g, 5, 6);

            double labels[] = {1.5, 2.3, 0.7, 4.8, 3.1, 5.6, 2.0, 6.4};

            find_max_delta_l(g, labels);

            mat_graph_free(g);
            break;
        }
        
        default:
            break;
    }

    return 0;
}