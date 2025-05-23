#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define TASK 3
#define MAX_VERTICES 20

#pragma region List graph utils

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

#pragma endregion List graph utils

#pragma region Topo sort utils

void topo_sort_helper(
    ListGraph* g, 
    int v, 
    int visited[], 
    int* stack, 
    int* stackIdx
) {
    visited[v] = 1;
    Node* tmp = g->adjList[v];
    while (tmp) {
        if (!visited[tmp->vertex]) {
            topo_sort_helper(g, tmp->vertex, visited, stack, stackIdx);
        }
        tmp = tmp->next;
    }
    stack[(*stackIdx)++] = v;
}

void topo_sort(ListGraph* g, int* stack) {
    int visited[MAX_VERTICES] = {0};
    int stackIdx = 0;

    for (int i = 0; i < g->numVertices; i++) {
        if (!visited[i]) topo_sort_helper(g, i, visited, stack, &stackIdx);
    }

    for (int i = 0; i < stackIdx / 2; i++) {
        int temp = stack[i];
        stack[i] = stack[stackIdx - i - 1];
        stack[stackIdx - i - 1] = temp;
    }
}

#pragma endregion Topo sort utils

void init_single_source(int dist[], int pred[], int numVertices, int src) {
    for (int i = 0; i < numVertices; i++) {
        dist[i] = INT_MAX;
        pred[i] = -1;
    }
    dist[src] = 0;
}

void relax(int u, int v, int weight, int dist[], int pred[]) {
    if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
        dist[v] = dist[u] + weight;
        pred[v] = u;
    }
}

void dag_shortest_path(ListGraph* g, int src, int dist[], int pred[]) {
    int numVertices = g->numVertices;
    int stack[MAX_VERTICES];
    topo_sort(g, stack);
    init_single_source(dist, pred, numVertices, src);

    for (int i = 0; i < numVertices; i++) {
        int u = stack[i];
        Node* tmp = g->adjList[u];
        while (tmp) {
            relax(u, tmp->vertex, tmp->weight, dist, pred);
            tmp = tmp->next;
        }
    }
}

void print_solution(int dist[], int pred[], int numVertices, int src) {
    printf("Shortest paths from source %d:\n", src);
    for (int i = 0; i < numVertices; i++) {
        printf("To vertex %d: ", i);
        if (dist[i] == INT_MAX) printf("No path exists\n");
        else {
            printf("Distance = %d", dist[i]);
            if (pred[i] != -1) printf(", Predecessor = %d", pred[i]);
            printf("\n");
        }
    }
}

#pragma region 22.2-3

void split_vertices(
    ListGraph* g, 
    ListGraph* transformed, 
    int vertexWeights[]
) {
    int offset = g->numVertices;
    for (int v = 0; v < g->numVertices; v++) {
        printf("Creating a new vertex with weight %d\n", vertexWeights[v]);
        list_graph_add_edge(transformed, v, v + offset, vertexWeights[v]);
        Node* tmp = g->adjList[v];
        while (tmp) {
            list_graph_add_edge(transformed, v + offset, tmp->vertex, tmp->weight);
            tmp = tmp->next;
        }
        
    }
}

#pragma endregion 22.2-3

#pragma region 22.2-4

int count_paths(ListGraph* g) {
    /*
        Time complexity: O(V + E)
    */
    int stack[MAX_VERTICES];
    int paths[MAX_VERTICES] = {0};

    topo_sort(g, stack);

    for (int i = 0; i < g->numVertices; i++) {
        int u = stack[i];
        Node* tmp = g->adjList[u];
        while (tmp) {
            int v = tmp->vertex;
            paths[v] += paths[u] + 1;
            tmp = tmp->next;
        }
    }
    int res = 0;
    for (int i = 0; i < g->numVertices; i++) res += paths[i];
    return res;
}

#pragma endregion 22.2-4

int main(void) {
    switch (TASK)
    {
        case 1: {
            // DAG shorted paths
            int numVertices = 6;
            ListGraph* g = list_graph_create(numVertices);

            list_graph_add_edge(g, 0, 1, 5);
            list_graph_add_edge(g, 0, 2, 3);
            list_graph_add_edge(g, 1, 3, 6);
            list_graph_add_edge(g, 1, 2, 2);
            list_graph_add_edge(g, 2, 4, 4);
            list_graph_add_edge(g, 2, 5, 2);
            list_graph_add_edge(g, 2, 3, 7);
            list_graph_add_edge(g, 3, 4, -1);
            list_graph_add_edge(g, 4, 5, -2);

            int dist[MAX_VERTICES];
            int pred[MAX_VERTICES];
            int src = 1;

            dag_shortest_path(g, src, dist, pred);
            print_solution(dist, pred, numVertices, src);

            list_graph_free(g);
            break;
        }

        case 2: {
            // 22.2-3
            int numVertices = 6;
            ListGraph* g = list_graph_create(numVertices);
            int vertexWeights[] = {2, 3, 6, 1, 4, 5};

            list_graph_add_edge(g, 0, 1, 0);
            list_graph_add_edge(g, 0, 2, 0);
            list_graph_add_edge(g, 1, 3, 0);
            list_graph_add_edge(g, 1, 2, 0);
            list_graph_add_edge(g, 2, 4, 0);
            list_graph_add_edge(g, 2, 5, 0);
            list_graph_add_edge(g, 3, 4, 0);
            list_graph_add_edge(g, 4, 5, 0);

            ListGraph* gPrime = list_graph_create(2 * numVertices);
            split_vertices(g, gPrime, vertexWeights);

            int dist[MAX_VERTICES];
            int pred[MAX_VERTICES];
            int src = 1;

            dag_shortest_path(g, src, dist, pred);
            print_solution(dist, pred, numVertices, src);

            list_graph_free(g);
            break;
        }

        case 3: {
            // 22.2-4
            int numVertices = 6;
            ListGraph* g = list_graph_create(numVertices);

            list_graph_add_edge(g, 0, 1, 0);
            list_graph_add_edge(g, 0, 2, 0);
            list_graph_add_edge(g, 1, 3, 0);
            list_graph_add_edge(g, 1, 2, 0);
            list_graph_add_edge(g, 2, 4, 0);
            list_graph_add_edge(g, 2, 5, 0);
            list_graph_add_edge(g, 3, 4, 0);
            list_graph_add_edge(g, 4, 5, 0);

            int totalPaths = count_paths(g);
            printf("Total number of paths in the DAG: %d\n", totalPaths);

            list_graph_free(g);
            break;
        }
        
        default:
            break;
    }
}