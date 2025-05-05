#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TASK 6
#define MAX_VERTICES 10

typedef struct Node {
    int vertex;
    int weight;
    struct Node* next;
} Node;

typedef struct ListGraph {
    int numVertices;
    Node* adjList[MAX_VERTICES];
} ListGraph;

Node* create_node(int vertex, int weight) {
    Node* newNode = malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

ListGraph* list_graph_create(int numVertices) {
    ListGraph* g = malloc(sizeof(ListGraph));
    g->numVertices = numVertices;
    for (int i = 0; i < numVertices; i++) g->adjList[i] = NULL;
    return g;
}

void list_graph_free(ListGraph* g) {
    for (int i = 0; i < g->numVertices; i++) {
        Node* temp = g->adjList[i];
        while (temp) {
            Node* toDelete = temp;
            temp = temp->next;
            free(toDelete);
        }
    }
    free(g);
}

void list_graph_add_edge(ListGraph* g, int u, int v, int weight) {
    Node* newNode = create_node(v, weight);
    newNode->next = g->adjList[u];
    g->adjList[u] = newNode;
}

void relax_edge(int u, int v, int weight, int dist[], int pred[]) {
    if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
        dist[v] = dist[u] + weight;
        pred[v] = u;
    }
}

int bellman_ford(ListGraph* g, int src, int dist[], int pred[]) {
    int numVertices = g->numVertices;
    for (int i = 0; i < numVertices; i++) {
        dist[i] = INT_MAX;
        pred[i] = -1;
    }
    dist[src] = 0;

    // Relax the edges |V| - 1 times
    for (int i = 0; i < numVertices - 1; i++) {
        for (int u = 0; u < numVertices; u++) {
            Node* tmp = g->adjList[u];
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
        Node* tmp = g->adjList[u];
        while (tmp) {
            int v = tmp->vertex;
            int weight = tmp->weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) return 0;
            tmp = tmp->next;
        }
    }

    return 1;
}

void print_path(int pred[], int dest) {
    if (dest == -1) return;
    if (pred[dest] != -1) {
        print_path(pred, pred[dest]);
        printf(" -> ");
    }
    printf("%d", dest);
}

void print_solution(int dist[], int pred[], int numVertices, int src) {
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

int early_stopped_bellman_ford(ListGraph* g, int src, int dist[], int pred[]) {
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
            Node* tmp = g->adjList[u];
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
        Node* tmp = g->adjList[u];
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

#define NEG_INF INT_MIN

void dfs_mark(ListGraph* g, int u, int dist[], int visited[]) {
    if (visited[u] || dist[u] == NEG_INF) return;
    dist[u] = NEG_INF;
    visited[u] = 1;

    Node* tmp = g->adjList[u];
    while (tmp)
    {
       dfs_mark(g, tmp->vertex, dist, visited);
       tmp = tmp->next;
    }
}

int bellman_ford_negative_mark(ListGraph* g, int src, int dist[], int pred[]) {
    int numVertices = g->numVertices;
    int hasNegCycle = 0;
    int marked[MAX_VERTICES] = {0};

    for (int i = 0; i < numVertices; i++) {
        dist[i] = INT_MAX;
        pred[i] = -1;
    }
    dist[src] = 0;

    // Relax edges |V| - 1 times
    for (int i = 0; i < numVertices - 1; i++) {
        for (int u = 0; u < numVertices; u++) {
            Node* tmp = g->adjList[u];
            while (tmp) {
                int v = tmp->vertex;
                int weight = tmp->weight;
                relax_edge(u, v, weight, dist, pred);
                tmp = tmp->next;
            }
        }
    } 

    for (int u = 0; u < numVertices; u++) {
        Node* tmp = g->adjList[u];
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
        int visited[MAX_VERTICES] = {0};
        for (int u = 0; u < numVertices; u++) {
            if (marked[u]) {
                dfs_mark(g, u, dist, visited);
            }
        }
    }

    return !hasNegCycle;
}

void print_modified_solution(int dist[], int numVertices, int src) {
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

int bellman_ford_optimized(ListGraph* g, int src, int dist[], int pred[]) {
    int numVertices = g->numVertices;
    int marked[MAX_VERTICES] = {0};

    for (int i = 0; i < numVertices; i++) {
        dist[i] = INT_MAX;
        pred[i] = -1;
    }
    dist[src] = 0;
    int inQueue[MAX_VERTICES] = {0};
    int queue[MAX_VERTICES * MAX_VERTICES];
    int front = 0, rear = 0;

    queue[rear++] = src;
    inQueue[src] = 1;

    int relaxCnt[MAX_VERTICES] = {0};

    while (front != rear) {
        int u = queue[front++];
        inQueue[u] = 0;
        Node* tmp = g->adjList[u];
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

void modified_relax(int u, int v, int weight, int dist[], int pred[]) {
    int pathThroughU = (dist[u] == INT_MAX) ? INT_MAX : dist[u] + weight;
    int minVal = fmin(weight, pathThroughU);

    if (dist[v] > minVal) {
        dist[v] = minVal;
        pred[v] = (pathThroughU < weight) ? pred[u] : u;
    }
}

int modified_relax_bellman_ford(ListGraph* g, int src, int dist[], int pred[]) {
    int numVertices = g->numVertices;
    
    for (int i = 0; i < numVertices; i++) {
        dist[i] = INT_MAX;
        pred[i] = -1;
    }
    
    for (int u = 0; u < numVertices; u++) {
        Node* tmp = g->adjList[u];
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
            Node* tmp = g->adjList[u];
            while (tmp) {
                int v = tmp->vertex;
                int weight = tmp->weight;
                modified_relax(u, v, weight, dist, pred);
                tmp = tmp->next;
            }
        }
    }
    
    for (int u = 0; u < numVertices; u++) {
        Node* tmp = g->adjList[u];
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

void print_modified_solution_prim(int dist[], int pred[], int numVertices) {
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

#pragma region 22.1-7

int find_negative_cycle_dfs(
    ListGraph* g,
    int source,
    int curr,
    int* path,
    int pathIdx,
    int* visited,
    int* onPath,
    int* cycleStart,
    int* weights
) {
    onPath[curr] = 1;
    visited[curr] = 1;
    path[pathIdx] = curr;

    Node* tmp = g->adjList[curr];
    while (tmp) {
        int v = tmp->vertex;
        int w = tmp->weight;
        if (onPath[v]) {
            int cycleW = 0;
            int i;
            for (i = 0; i <= pathIdx; i++) {
                if (path[i] == v) {
                    *cycleStart = i;
                    break;
                }
            }
            for (i = *cycleStart; i < pathIdx; i++) {
                int u = path[i];
                int next = path[i + 1];
                Node* edge = g->adjList[u];
                while (edge && edge->vertex != next) edge = edge->next;
                if (edge) cycleW += edge->weight;
            }
            cycleW += w;
            if (cycleW < 0) return 1;
        } else if (!visited[v]) {
            weights[pathIdx] = w;
            if (find_negative_cycle_dfs(g, source, v, path, pathIdx + 1, 
                visited, onPath, cycleStart, weights)) return 1;
        }
        tmp = tmp->next;
    }
    onPath[curr] = 0;
    return 0;
}

void print_negative_cycle(ListGraph* g) {
    int numVertices = g->numVertices;
    int dist[MAX_VERTICES];
    int pred[MAX_VERTICES];
    
    if (bellman_ford(g, 0, dist, pred)) {
        printf("No negative-weight cycle detected\n");
        return;
    }

    printf("Negative-weight cycle detected\n");
    
    int cycleVertex = -1;
    for (int u = 0; u < g->numVertices; u++) {
        Node* tmp = g->adjList[u];
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

    int visited[MAX_VERTICES] = {0};
    printf("Vertices in the negative-weight cycle: ");

    int inCycle[MAX_VERTICES] = {0};
    int curr = cycleVertex;
    int cnt = 0;

    for (int i = 0; i < numVertices; i++) curr = pred[curr];

    int startVertex = curr;

    do {
        printf("%d ", curr);
        inCycle[curr] = 1;
        curr = pred[curr];
    } while (curr != startVertex);

    printf("\n");

    int cycleW = 0;
    curr = startVertex;

    do {
        int next = pred[curr];
        Node* edge = g->adjList[next];
        while (edge && edge->vertex != curr) edge = edge->next;
        if (edge) cycleW += edge->weight;
        curr = next;
    } while (curr != startVertex);
    printf("Total cycle weight: %d\n", cycleW);
}

#pragma endregion 22.1-7

int main(void) {
    switch (TASK)
    {
        case 1: {
            // Basic Bellman-Ford
            int numVertices = 5;
            ListGraph* g = list_graph_create(numVertices);

            list_graph_add_edge(g, 0, 1, 6);
            list_graph_add_edge(g, 0, 3, 7);
            list_graph_add_edge(g, 1, 2, 5);
            list_graph_add_edge(g, 1, 3, 8);
            list_graph_add_edge(g, 1, 4, -4);
            list_graph_add_edge(g, 2, 1, -2);
            list_graph_add_edge(g, 3, 2, -3);
            list_graph_add_edge(g, 3, 4, 9);
            list_graph_add_edge(g, 4, 0, 2);
            list_graph_add_edge(g, 4, 2, 7);

            int dist[MAX_VERTICES];
            int pred[MAX_VERTICES];

            int src = 4;
            if (bellman_ford(g, src, dist, pred)) {
                printf("No negative weight cycle detected\n");
                print_solution(dist, pred, numVertices, src);
            } else printf("Graph contains a negative weight cycle\n");
            
            list_graph_free(g);
            break;
        }

        case 2: {
            // 22.1-3
            int numVertices = 5;
            ListGraph* g = list_graph_create(numVertices);

            list_graph_add_edge(g, 0, 1, 6);
            list_graph_add_edge(g, 0, 3, 7);
            list_graph_add_edge(g, 1, 2, 5);
            list_graph_add_edge(g, 1, 3, 8);
            list_graph_add_edge(g, 1, 4, -4);
            list_graph_add_edge(g, 2, 1, -2);
            list_graph_add_edge(g, 3, 2, -3);
            list_graph_add_edge(g, 3, 4, 9);
            list_graph_add_edge(g, 4, 0, 2);
            list_graph_add_edge(g, 4, 2, 7);

            int dist[MAX_VERTICES];
            int pred[MAX_VERTICES];

            int src = 4;
            if (early_stopped_bellman_ford(g, src, dist, pred)) {
                printf("No negative weight cycle detected\n");
                print_solution(dist, pred, numVertices, src);
            } else printf("Graph contains a negative weight cycle\n");
            
            
            list_graph_free(g);
            break;
        }

        case 3: {
            // 22.1-4
            int numVertices = 6;
            ListGraph* g = list_graph_create(numVertices);
            
            list_graph_add_edge(g, 0, 1, 6);
            list_graph_add_edge(g, 0, 3, 7);
            list_graph_add_edge(g, 1, 2, 5);
            list_graph_add_edge(g, 1, 3, 8);
            list_graph_add_edge(g, 1, 4, -4);
            list_graph_add_edge(g, 2, 1, -2);
            list_graph_add_edge(g, 3, 2, -3);
            list_graph_add_edge(g, 3, 4, 9);
            list_graph_add_edge(g, 4, 0, 2);
            list_graph_add_edge(g, 4, 2, 7);

            int dist[MAX_VERTICES];
            int pred[MAX_VERTICES];

            int src = 4;
            if (bellman_ford_negative_mark(g, src, dist, pred)) 
                printf("No negative weight cycle detected\n");
            else printf("Graph contains negative weight cycle(s)\n");
            
            print_modified_solution(dist, numVertices, src);
            
            list_graph_free(g);
            break;
        }

        case 4: {
            // 22.1-5
            int numVertices = 6;
            ListGraph* g = list_graph_create(numVertices);
            
            list_graph_add_edge(g, 0, 1, 6);
            list_graph_add_edge(g, 0, 3, 7);
            list_graph_add_edge(g, 1, 2, 5);
            list_graph_add_edge(g, 1, 3, 8);
            list_graph_add_edge(g, 1, 4, -4);
            list_graph_add_edge(g, 2, 1, -2);
            list_graph_add_edge(g, 3, 2, -3);
            list_graph_add_edge(g, 3, 4, 9);
            list_graph_add_edge(g, 4, 0, 2);
            list_graph_add_edge(g, 4, 2, 7);

            int dist[MAX_VERTICES];
            int pred[MAX_VERTICES];

            int src = 4;
            if (bellman_ford_optimized(g, src, dist, pred)) 
                printf("No negative weight cycle detected\n");
            else printf("Graph contains negative weight cycle(s)\n");
            
            print_solution(dist, pred, numVertices, src);
            
            list_graph_free(g);
            break;
        }

        case 5: {
            // 22.1-6
            int numVertices = 5;
            ListGraph* g = list_graph_create(numVertices);

            list_graph_add_edge(g, 0, 1, 6);
            list_graph_add_edge(g, 0, 3, 7);
            list_graph_add_edge(g, 1, 2, 5);
            list_graph_add_edge(g, 1, 3, 8);
            list_graph_add_edge(g, 1, 4, -4);
            list_graph_add_edge(g, 2, 1, -2);
            list_graph_add_edge(g, 3, 2, -3);
            list_graph_add_edge(g, 3, 4, 9);
            list_graph_add_edge(g, 4, 0, 2);
            list_graph_add_edge(g, 4, 2, 7);

            int dist[MAX_VERTICES];
            int pred[MAX_VERTICES];

            int src = 4;
            if (modified_relax_bellman_ford(g, src, dist, pred)) {
                printf("No negative weight cycle detected\n");
                print_modified_solution_prim(dist, pred, numVertices);
            } else printf("Graph contains a negative weight cycle\n");
            
            list_graph_free(g);
            break;
        }

        case 6: {
            // 22.1-7
            int numVertices = 6;
            ListGraph* g = list_graph_create(numVertices);
            
            list_graph_add_edge(g, 0, 1, 6);
            list_graph_add_edge(g, 0, 3, 7);
            list_graph_add_edge(g, 1, 2, 5);
            list_graph_add_edge(g, 1, 3, 8);
            list_graph_add_edge(g, 1, 4, -4);
            list_graph_add_edge(g, 2, 1, -2);
            list_graph_add_edge(g, 3, 2, -3);
            list_graph_add_edge(g, 3, 4, 9);
            list_graph_add_edge(g, 4, 0, -5);
            list_graph_add_edge(g, 4, 2, 7);


            int dist[MAX_VERTICES];
            int pred[MAX_VERTICES];

            print_negative_cycle(g);
            
            list_graph_free(g);
            break;
        }
        
        default:
            break;
    }
}