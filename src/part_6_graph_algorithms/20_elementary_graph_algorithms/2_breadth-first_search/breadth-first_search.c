#include "part_6_graph_algorithms/20_elementary_graph_algorithms/elementary_graph_algorithms.h"

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
