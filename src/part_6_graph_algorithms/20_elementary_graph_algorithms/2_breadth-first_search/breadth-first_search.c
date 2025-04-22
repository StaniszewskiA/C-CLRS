#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TASK 3
#define MAX_VERTICES 50

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct ListGraph {
    int numVertices;
    Node* adjList[MAX_VERTICES];
} ListGraph;

Node* create_node(int vertex) {
    Node* new_node = malloc(sizeof(Node));
    new_node->vertex = vertex;
    new_node->next = NULL;
    return new_node;
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

void list_graph_add_edge(ListGraph* g, int u, int v) {
    Node* new_node = create_node(v);
    new_node->next = g->adjList[u];
    g->adjList[u] = new_node;
}

void list_graph_bfs(ListGraph* g, int source) {
    int visited[MAX_VERTICES] = {0};
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    visited[source] = 1;
    queue[rear++] = source;

    while (front != rear) {
        source = queue[front++];
        printf("%d ", source);

        Node* temp = g->adjList[source];
        while(temp) {
            int adjacent = temp->vertex;
            if (!visited[adjacent]) {
                visited[adjacent] = 1;
                queue[rear++] = adjacent;
            }
            temp = temp->next;
        }
    }
}

#pragma region 20.2-4

typedef struct MatGraph {
    int numVertices;
    int adjMat[MAX_VERTICES][MAX_VERTICES];
} MatGraph;

MatGraph* mat_graph_create(int numVertices) {
    MatGraph* g = malloc(sizeof(MatGraph));
    g->numVertices = numVertices;

    for (int i = 0; i < numVertices; i++) 
        for (int j = 0; j < numVertices; j++) g->adjMat[i][j] = 0;
    return g;
}

void mat_graph_free(MatGraph* g) {
    free(g);
}

void mat_graph_add_edge(MatGraph* g, int u, int v) {
    g->adjMat[u][v] = 1;
}

void mat_graph_bfs(MatGraph* g, int source) {
    int visited[MAX_VERTICES];
    for (int i = 0; i < g->numVertices; i++) visited[i] = 0;
    
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    visited[source] = 1;
    queue[rear++] = source;

    while (front != rear) {
        source = queue[front++];
        printf("%d ", source);
        for (int adjacent = 0; adjacent < g->numVertices; adjacent++) {
            if (g->adjMat[source][adjacent] && !visited[adjacent]) {
                visited[adjacent] = 1;
                queue[rear++] = adjacent;
            }
        }
    }
}

#pragma endregion 20.2-4

#pragma region 20.2-7

typedef enum { UNCOLORED = -1, BABYFACE = 0, HEEL = 1} Role;

int check_wrestlers(ListGraph* g, Role* roles, int source) {
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    roles[source] = BABYFACE;
    queue[rear++] = source;

    while (front != rear) {
        source = queue[front++];
        Role currRole = roles[source];
        Node* adjacent = g->adjList[source];

        while (adjacent) {
            int v = adjacent->vertex;
            if (roles[v] == UNCOLORED) {
                roles[v] = (currRole == BABYFACE) ? HEEL : BABYFACE;
                queue[rear++] = v;
            } else if (roles[v] == currRole) return 0;
            adjacent = adjacent->next;
        }
    }

    return 1;
}

int can_assign_wrestlers(ListGraph* g, Role* roles) {
    for (int i = 0; i < g->numVertices; i++) {
        if (roles[i] == UNCOLORED) {
            if (!check_wrestlers(g, roles, i)) return 0;
        }
    }
    return 1;
}

#pragma endregion 20.2-7

#pragma region 20.2-8

int bfs_furthest_node(ListGraph* g, int source, int* outDist) {
    int visited[MAX_VERTICES], dist[MAX_VERTICES];
    memset(visited, 0, sizeof(visited));
    memset(dist, 0, sizeof(dist));

    int queue[MAX_VERTICES], front = 0, rear = 0;
    queue[rear++] = source;
    visited[source] = 1;
    int furthestNode = source;

    while (front != rear) {
        int u = queue[front++];
        Node* adjacent = g->adjList[source];
        while(adjacent) {
            int v = adjacent->vertex;
            if (!visited[v]) {
                visited[v] = 1;
                dist[v] = dist[u] + 1;
                queue[rear++] = v;
                if (dist[v] > dist[furthestNode]) furthestNode = v;
            }
            adjacent = adjacent->next;
        }
    }

    if (outDist) *outDist = dist[furthestNode];
    return furthestNode;
}

int tree_diameter(ListGraph* g) {
    int farthestFromSource = bfs_furthest_node(g, 0, NULL);
    int diameter = 0;
    bfs_furthest_node(g, farthestFromSource, &diameter);
    return diameter;
}

#pragma endregion 20.2-8

int main(void) {
    // ListGraph* listG = list_graph_create(4);
    // list_graph_add_edge(listG, 0, 1);
    // list_graph_add_edge(listG, 0, 2);
    // list_graph_add_edge(listG, 1, 2);
    // list_graph_add_edge(listG, 2, 0);
    // list_graph_add_edge(listG, 2, 3);
    // list_graph_add_edge(listG, 3, 3);

    // printf("BFS with source 2\n");
    // list_graph_bfs(listG, 2);
    // list_graph_free(listG);

    switch (TASK)
    {
        case 1: {
            // 20.2-4
            MatGraph* matG = mat_graph_create(4);
            mat_graph_add_edge(matG, 0, 1);
            mat_graph_add_edge(matG, 0, 2);
            mat_graph_add_edge(matG, 1, 2);
            mat_graph_add_edge(matG, 2, 0);
            mat_graph_add_edge(matG, 2, 3);
            mat_graph_add_edge(matG, 3, 3);

            printf("BFS with source 2\n");
            mat_graph_bfs(matG, 2);
            mat_graph_free(matG);

            break;
        }

        case 2: {
            // 20.2-7
            int n = 6;
            int rivalries[][2] = {
                {0, 1},
                {1, 2},
                {2, 3},
                {3, 4},
                {4, 5},
                {5, 0}
            };
            int r = sizeof(rivalries) / sizeof(rivalries[0]);

            ListGraph* g = list_graph_create(n);
            Role roles[MAX_VERTICES];
            for (int i = 0; i < n; i++) roles[i] = UNCOLORED;

            for (int i = 0; i < r; i++) 
                list_graph_add_edge(g, rivalries[i][0], rivalries[i][1]);

            if (can_assign_wrestlers(g, roles)) printf("Wrestlers can be assigned");
            else printf("Wrestlers can't be assigned.");
            
            list_graph_free(g);

            break;
        }

        case 3: {
            // 20.2-8
            ListGraph* g = list_graph_create(6);
            list_graph_add_edge(g, 0, 1);
            list_graph_add_edge(g, 1, 2);
            list_graph_add_edge(g, 1, 3);
            list_graph_add_edge(g, 3, 4);
            list_graph_add_edge(g, 4, 5);

            int diameter = tree_diameter(g);
            printf("Diameter of the tree: %d\n", diameter);

            break;
        }
        
        default:
            break;
    }

    return 0;
}