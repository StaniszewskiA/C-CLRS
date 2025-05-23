#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 10
#define INF INT_MAX 

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
        Node* tmp = g->adjList[i];
        while (tmp) {
            Node* toDelete = tmp;
            tmp = tmp->next;
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
    if (dist[u] != INF && dist[u] + weight < dist[v]) {
        dist[v] = dist[u] + weight;
        pred[v] = u;
    }
}

void init_single_source(int dist[], int pred[], int numVertices, int src) {
    for (int i = 0; i < numVertices; i++) {
        dist[i] = INF;
        pred[i] = -1;
    }
    dist[src] = 0;
}

int bellman_ford(ListGraph* g, int src, int dist[], int pred[]) {
    int numVertices = g->numVertices;
    init_single_source(dist, pred, numVertices, src);

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
            if (dist[u] != INF && dist[u] + weight < dist[v]) return 0;
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
            printf("to vertex %d: ", i);
            if (dist[i] == INF) printf("No path exists\n");
            else {
                printf("Distance = %d, Path: ", dist[i]);
                print_path(pred, i);
                printf("\n");
            }
        }
    }
}

int main(void) {
    int numVertices = 4;
    ListGraph* g = list_graph_create(numVertices);

    list_graph_add_edge(g, 1, 2, 4);  // x1 - x2 <= 4
    list_graph_add_edge(g, 2, 3, 3);  // x2 - x3 <= 3
    list_graph_add_edge(g, 3, 1, -2); // x3 - x1 <= -2
    list_graph_add_edge(g, 1, 4, 5);  // x1 - x4 <= 5
    list_graph_add_edge(g, 4, 3, 1);  // x4 - x3 <= 1

    for (int i = 1; i <= numVertices; i++) list_graph_add_edge(g, 0, i, 0);

    int dist[MAX_VERTICES];
    int pred[MAX_VERTICES];

    int src = 0;
    if (bellman_ford(g, src, dist, pred)) {
        printf("No negative weight cycle detected\n");
        print_solution(dist, pred, numVertices, src);
    } else {
        printf("Graph contains a negative weight cycle\n");
    }

    list_graph_free(g);
    return 0;
}