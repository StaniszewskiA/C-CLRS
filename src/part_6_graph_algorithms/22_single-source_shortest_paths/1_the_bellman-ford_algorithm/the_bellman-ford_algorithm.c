#include "part_6_graph_algorithms/22_single-source_shortest_paths/single-source_shortest_paths.h"

int bellman_ford(WeightedNodeListGraph* g, int src, int dist[], int pred[]) {
    int numVertices = g->numVertices;
    for (int i = 0; i < numVertices; i++) {
        dist[i] = INT_MAX;
        pred[i] = -1;
    }
    dist[src] = 0;

    // Relax the edges |V| - 1 times
    for (int i = 0; i < numVertices - 1; i++) {
        for (int u = 0; u < numVertices; u++) {
            WeightedNode* tmp = g->adjList[u];
            while (tmp) {
                int v = tmp->vertex;
                int weight = tmp->weight;
                relax_edge(u, v, weight, dist, pred);
                tmp = tmp->next;
            }
        }
    }

    // Check for negative cycles
    for (int u = 0; u < numVertices; u++) {
        WeightedNode* tmp = g->adjList[u];
        while (tmp) {
            int v = tmp->vertex;
            int weight = tmp->weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) return 0;
            tmp = tmp->next;
        }
    }

    return 1;
}

void print_negative_cycle(WeightedNodeListGraph* g) {
    int numVertices = g->numVertices;
    int dist[MAX_GRAPH_VERTICES];
    int pred[MAX_GRAPH_VERTICES];
    
    if (bellman_ford(g, 0, dist, pred)) {
        printf("No negative-weight cycle detected\n");
        return;
    }

    printf("Negative-weight cycle detected\n");
    
    int cycleVertex = -1;
    for (int u = 0; u < g->numVertices; u++) {
        WeightedNode* tmp = g->adjList[u];
        while (tmp) {
            int v = tmp->vertex;
            int weight = tmp->weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                cycleVertex = v;
                break;
            }
            tmp = tmp->next;
        }
        if (cycleVertex != -1) break;
    }

    printf("Vertices in the negative-weight cycle: ");
    int curr = cycleVertex;

    for (int i = 0; i < numVertices; i++) curr = pred[curr];

    int startVertex = curr;

    do {
        printf("%d ", curr);
        curr = pred[curr];
    } while (curr != startVertex);

    printf("\n");

    int cycleW = 0;
    curr = startVertex;

    do {
        int next = pred[curr];
        WeightedNode* edge = g->adjList[next];
        while (edge && edge->vertex != curr) edge = edge->next;
        if (edge) cycleW += edge->weight;
        curr = next;
    } while (curr != startVertex);
    printf("Total cycle weight: %d\n", cycleW);
}

void bellman_ford_print_solution(
    int dist[], 
    int pred[], 
    int numVertices, 
    int src
) {
    printf("Shortest paths from source %d:\n", src);
    for (int i = 0; i < numVertices; i++) {
        if (i != src) {
            printf("To vertex %d: ", i);
            if (dist[i] == INT_MAX) {
                printf("No path exists\n");
            } else {
                printf("Distance = %d, Path: ", dist[i]);
                print_path(pred, i);
                printf("\n");
            }
        }
    }
}

#pragma region 22.1-3

int early_stopped_bellman_ford(
    WeightedNodeListGraph* g, 
    int src, 
    int dist[], 
    int pred[]
) {
    /*
        Stop the algorithm if no relaxation occur.
    */
    int numVertices = g->numVertices;
    for (int i = 0; i < numVertices; i++) {
        dist[i] = INT_MAX;
        pred[i] = -1;
    }
    dist[src] = 0;

    int changed = 1;
    int iterations = 0;

    // Relax the edges |V| - 1 times or until no changes occur
    for (int i = 0; i < numVertices - 1 && changed; i++) {
        changed = 0;
        iterations++;
        for (int u = 0; u < numVertices; u++) {
            WeightedNode* tmp = g->adjList[u];
            while (tmp) {
                int v = tmp->vertex;
                int weight = tmp->weight;
                if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pred[v] = u;
                    changed = 1; 
                }
                tmp = tmp->next;
            }
        }
    }

    printf("The algorithm terminated after %d iterations\n", iterations);

    // Check for negative cycles
    for (int u = 0; u < numVertices; u++) {
        WeightedNode* tmp = g->adjList[u];
        while (tmp) {
            int v = tmp->vertex;
            int weight = tmp->weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) return 0;
            tmp = tmp->next;
        }
    }

    return 1;
}

#pragma endregion 22.1-3

#pragma region 22.1-4

void dfs_mark(WeightedNodeListGraph* g, int u, int dist[], int visited[]) {
    if (visited[u] || dist[u] == NEG_INF) return;
    dist[u] = NEG_INF;
    visited[u] = 1;

    WeightedNode* tmp = g->adjList[u];
    while (tmp)
    {
       dfs_mark(g, tmp->vertex, dist, visited);
       tmp = tmp->next;
    }
}

int bellman_ford_negative_mark(
    WeightedNodeListGraph* g, 
    int src, 
    int dist[], 
    int pred[]
) {
    int numVertices = g->numVertices;
    int hasNegCycle = 0;
    int marked[MAX_GRAPH_VERTICES] = {0};

    for (int i = 0; i < numVertices; i++) {
        dist[i] = INT_MAX;
        pred[i] = -1;
    }
    dist[src] = 0;

    // Relax edges |V| - 1 times
    for (int i = 0; i < numVertices - 1; i++) {
        for (int u = 0; u < numVertices; u++) {
            WeightedNode* tmp = g->adjList[u];
            while (tmp) {
                int v = tmp->vertex;
                int weight = tmp->weight;
                relax_edge(u, v, weight, dist, pred);
                tmp = tmp->next;
            }
        }
    } 

    for (int u = 0; u < numVertices; u++) {
        WeightedNode* tmp = g->adjList[u];
        while (tmp) {
            int v = tmp->vertex;
            int weight = tmp->weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                hasNegCycle = 1;
                marked[v] = 1;
            }
            tmp = tmp->next;
        }
    }

    if (hasNegCycle) {
        int visited[MAX_GRAPH_VERTICES] = {0};
        for (int u = 0; u < numVertices; u++) {
            if (marked[u]) {
                dfs_mark(g, u, dist, visited);
            }
        }
    }

    return !hasNegCycle;
}

void bellman_ford_print_modified_solution(
    int dist[], 
    int numVertices, 
    int src
) {
    printf("Shortest paths from source %d (with negative cycle detection):\n", src);
    for (int i = 0; i < numVertices; i++) {
        if (i != src) {
            printf("To vertex %d: ", i);
            if (dist[i] == INT_MAX) printf("No path exists\n");
            else if (dist[i] == NEG_INF) printf("-∞ (affected by negative cycle)\n");
            else printf("Distance = %d\n", dist[i]);
        }
    }
}

#pragma endregion 22.1-4

#pragma region 22.1-5

int bellman_ford_optimized(
    WeightedNodeListGraph* g, 
    int src, 
    int dist[], 
    int pred[]
) {
    int numVertices = g->numVertices;

    for (int i = 0; i < numVertices; i++) {
        dist[i] = INT_MAX;
        pred[i] = -1;
    }
    dist[src] = 0;
    int inQueue[MAX_GRAPH_VERTICES] = {0};
    int queue[MAX_GRAPH_VERTICES * MAX_GRAPH_VERTICES];
    int front = 0, rear = 0;

    queue[rear++] = src;
    inQueue[src] = 1;

    int relaxCnt[MAX_GRAPH_VERTICES] = {0};

    while (front != rear) {
        int u = queue[front++];
        inQueue[u] = 0;
        WeightedNode* tmp = g->adjList[u];
        while (tmp)
        {
            int v = tmp->vertex;
            int weight = tmp->weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pred[v] = u;
                
                relaxCnt[v]++;
                if (relaxCnt[v] >= numVertices) {
                    return 0;
                }
                
                if (!inQueue[v]) {
                    queue[rear++] = v;
                    inQueue[v] = 1;
                }
            }
            tmp = tmp->next;
        }
        
    }

    return 1;
}

#pragma endregion 22.1-5

#pragma region 22.1-6

int modified_relax_bellman_ford(
    WeightedNodeListGraph* g, 
    int dist[], 
    int pred[]
) {
    int numVertices = g->numVertices;
    
    for (int i = 0; i < numVertices; i++) {
        dist[i] = INT_MAX;
        pred[i] = -1;
    }
    
    for (int u = 0; u < numVertices; u++) {
        WeightedNode* tmp = g->adjList[u];
        while (tmp) {
            int v = tmp->vertex;
            int weight = tmp->weight;
            
            if (weight < dist[v]) {
                dist[v] = weight;
                pred[v] = u;
            }
            tmp = tmp->next;
        }
    }
    
    // Relax edges |V|-1 times
    for (int i = 0; i < numVertices - 1; i++) {
        for (int u = 0; u < numVertices; u++) {
            WeightedNode* tmp = g->adjList[u];
            while (tmp) {
                int v = tmp->vertex;
                int weight = tmp->weight;
                modified_relax(u, v, weight, dist, pred);
                tmp = tmp->next;
            }
        }
    }
    
    for (int u = 0; u < numVertices; u++) {
        WeightedNode* tmp = g->adjList[u];
        while (tmp) {
            int v = tmp->vertex;
            int weight = tmp->weight;
            
            int path_through_u = (dist[u] == INT_MAX) ? INT_MAX : dist[u] + weight;
            int direct_weight = weight;
            int min_value = (direct_weight < path_through_u) ? direct_weight : path_through_u;
            
            if (dist[v] > min_value) return 0; 
            
            tmp = tmp->next;
        }
    }
    
    return 1;
}

void bellman_ford_print_modified_solution_prim(
    int dist[], 
    int pred[], 
    int numVertices
) {
    printf("Minimum distance to each vertex from any source:\n");
    for (int i = 0; i < numVertices; i++) {
        printf("To vertex %d: ", i);
        if (dist[i] == INT_MAX) {
            printf("No path exists\n");
        } else {
            printf("Distance = %d", dist[i]);
            if (pred[i] != -1) {
                printf(", Source vertex: %d", pred[i]);
            }
            printf("\n");
        }
    }
}

#pragma endregion 22.1-6
