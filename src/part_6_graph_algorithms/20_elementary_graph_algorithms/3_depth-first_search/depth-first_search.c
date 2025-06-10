#include "part_6_graph_algorithms/20_elementary_graph_algorithms/elementary_graph_algorithms.h"

void dfs_visit(ListGraph* g, int vertex, int visited[]) {
    visited[vertex] = 1;
    printf("%d ", vertex);

    Node* currNode = g->adjList[vertex]; 
    while (currNode) {
        int adjacent = currNode->vertex; 
        if (!visited[adjacent]) dfs_visit(g, adjacent, visited);
        currNode = currNode->next;
    }
}

void dfs(ListGraph* g, int* order, int orderSize) {
    int* visited = (int*)safe_malloc(g->numVertices * sizeof(int));
    for (int i = 0; i < g->numVertices; i++) visited[i] = 0;
    for (int i = 0; i < orderSize; i++)
        if (order[i] < g->numVertices && !visited[order[i]]) dfs_visit(g, order[i], visited);
    free(visited);
}

#pragma region 20.3-6

void iterative_dfs_visit(ListGraph* g, int source, int visited[]) {
    int* stack = (int*)safe_malloc(g->numVertices * sizeof(int));
    int top = -1;
    
    if (source < g->numVertices) { 
        stack[++top] = source;
    }

    while (top != -1) {
        int vertex = stack[top--];
        if (vertex < g->numVertices && !visited[vertex]) {
            printf("%d ", vertex);

            Node* currNode = g->adjList[vertex]; 
            Node* prev = NULL;
            while(currNode) {
                Node* nextNode = currNode->next;
                currNode->next = prev;
                prev = currNode;
                currNode = nextNode;
            }
            currNode = prev; 

            while (currNode) {
                int adjacentNodeVertex = currNode->vertex; 
                if (adjacentNodeVertex < g->numVertices && !visited[adjacentNodeVertex]) {
                     if (top < g->numVertices - 1) { 
                        stack[++top] = adjacentNodeVertex;
                }
                currNode = currNode->next;
            }
        }
    }
    }
    free(stack);
}

void iterative_dfs(ListGraph* g, int* order, int orderSize) {
    int* visited = (int*)safe_malloc(g->numVertices * sizeof(int));
    for (int i = 0; i < g->numVertices; i++) visited[i] = 0;

    for (int i = 0; i < orderSize; i++)
        if (order[i] < g->numVertices && !visited[order[i]]) iterative_dfs_visit(g, order[i], visited);

    free(visited);
}

#pragma endregion 20.3-6

#pragma region 20.3-9

int coloredVertextime = 0;

void colored_dfs_visit_print(ColoredGraph* g, int u) {
    coloredVertextime++;
    g->vertices[u].d = coloredVertextime;
    g->vertices[u].color = GRAY;

    for (int v = 0; v < g->numVertices; v++) {
        if (g->adj[u][v]) {
            if (g->vertices[v].color == WHITE) {
                printf("(%d, %d) is a tree edge.\n", u, v);
                g->vertices[v].pi = u;
                colored_dfs_visit_print(g, v);
            } else if (g->vertices[v].color == GRAY) {
                printf("(%d, %d) is a back edge.\n", u, v);
            } else if (g->vertices[v].d > g->vertices[u].d) {
                printf("(%d, %d) is a forward edge.\n", u, v);
            } else {
                printf("(%d, %d) is a cross edge.\n", u, v);
            }
        }
    }

    g->vertices[u].color = BLACK;
    coloredVertextime++;
    g->vertices[u].f = coloredVertextime;
}

void colored_dfs_print(ColoredGraph* g) {
    for (int i = 0; i < g->numVertices; i++) {
        g->vertices[i].color = WHITE;
        g->vertices[i].pi = -1;
    }
    coloredVertextime = 0;
    for (int i = 0; i < g->numVertices; i++) {
        if (g->vertices[i].color == WHITE) colored_dfs_visit_print(g, i);
    }
}

ColoredGraph* colored_graph_create(int numVertices) {
    ColoredGraph* g = safe_malloc(sizeof(ColoredGraph));
    g->numVertices = numVertices;
    g->adj = safe_malloc(numVertices * sizeof(int *));
    g->vertices = safe_malloc(numVertices * sizeof(numVertices));
    for (int i = 0; i < numVertices; i++) {
        g->adj[i] = safe_calloc(numVertices, sizeof(int));
        g->vertices[i].id = i;
    }
    return g;
}

void colored_graph_add_edge(ColoredGraph* g, int u, int v) {
    g->adj[u][v] = 1;
}

void colored_graph_free(ColoredGraph* g) {
    for (int i = 0; i < g->numVertices; i++) free(g->adj[i]);
    free(g->adj);
    free(g->vertices);
    free(g);
}

#pragma endregion 20.3-9

#pragma region 20.3-11

void dfs_both_dirs(ListGraph* g) {
    int* visited = (int*)safe_calloc(g->numVertices, sizeof(int));
    for (int i = 0; i < g->numVertices; i++)
        if (!visited[i]) dfs_both_dirs(g);
    free(visited);
}

#pragma endregion 20.3-11

#pragma region 20.3-12

CCGraph* cc_graph_create(int numVertices) {
    CCGraph* g = (CCGraph*)safe_malloc(sizeof(CCGraph));
    g->numVertices = numVertices;
    g->array = (CCList*)safe_malloc(numVertices * sizeof(CCList));

    for (int i = 0; i < numVertices; i++) g->array[i].head = NULL;
    
    return g;
}

CCNode* cc_node_create(int cc) {
    CCNode* new_node = (CCNode*)safe_malloc(sizeof(CCNode));
    new_node->cc = cc;
    new_node->color = WHITE;
    new_node->pi = -1;
    new_node->d = -1;
    new_node->f = -1;
    return new_node;
}

void cc_graph_add_undirected_edge(CCGraph* g, int u, int v) {
    CCNode* node1 = cc_node_create(0);
    node1->pi = v;
    node1->next = g->array[u].head;
    g->array[u].head = node1;

    CCNode* node2 = cc_node_create(0);
    node2->pi = u;
    node2->next = g->array[v].head; 
    g->array[v].head = node2;
}

void cc_graph_free(CCGraph* g) {
    for (int i = 0; i < g->numVertices; i++) {
        CCNode* currNode = g->array[i].head;
        while (currNode) {
            CCNode* temp = currNode;
            currNode = currNode->next;
            free(temp);
        }
    }
    free(g->array);
    free(g);
}

void cc_visit_dfs(CCGraph* g, int u, int* time, int cc) {
    (*time)++;
    g->array[u].head->d = *time;
    g->array[u].head->color = GRAY;
    g->array[u].head->cc = cc;

    CCNode* currNode = g->array[u].head;
    while (currNode) {
        int v = currNode->pi;
        if (g->array[v].head->color == WHITE) {
            g->array[v].head->pi = u;
            cc_visit_dfs(g, v, time, cc);
        }
        currNode = currNode->next;
    }
    g->array[u].head->color = BLACK;
    (*time)++;
    g->array[u].head->f = *time;
}

void cc_dfs(CCGraph* g) {
    int time = 0;
    int cc = 1;

    for (int i = 0; i < g->numVertices; i++) {
        if (g->array[i].head == NULL || g->array[i].head->color == WHITE) {
            cc_visit_dfs(g, i, &time, cc);
            cc++;
        }
    }

    printf("Connected Components: \n");
    for (int i = 0; i < g->numVertices; i++) {
        if (g->array[i].head != NULL) 
            printf("Vertex %d: Component %d\n", i, g->array[i].head->cc);
    }
}

#pragma endregion 20.3-12

#pragma region 20.3-13

void topo_sort_helper(ListGraph* g, int v, int* visited, int* stack, int* stackIdx) {
    visited[v] = 1;

    Node* currNode = g->adjList[v]; 
    while (currNode) {
        int adjacent = currNode->vertex; 
        if (!visited[adjacent]) 
            topo_sort_helper(g, adjacent, visited, stack, stackIdx);
        currNode = currNode->next;
    }
    if (*stackIdx >= 0) { 
        stack[(*stackIdx)--] = v;
    }
}

int* topological_sort(ListGraph* g) {
    int* visited = (int*)safe_calloc(g->numVertices, sizeof(int));
    int* stack = (int*)safe_malloc(g->numVertices * sizeof(int));
    int stackIdx = g->numVertices - 1;

    for (int i = 0; i < g->numVertices; i++) {
        if (!visited[i]) topo_sort_helper(g, i, visited, stack, &stackIdx);
    }

    free(visited);
    return stack;
}

int list_graph_is_singly_connected(ListGraph* g) {
    int* topoOrder = topological_sort(g);

    if (!topoOrder) return 0; 
    for (int i = 0; i < g->numVertices; i++) {
        if (i >= g->numVertices || topoOrder[i] >= g->numVertices) continue; 
        int u = topoOrder[i];

        Node* currNode = g->adjList[u]; 
        while (currNode) {
            int v = currNode->vertex; 
            if (v >= g->numVertices) { currNode = currNode->next; continue; } 

            currNode = currNode->next;
        }
    }

    free(topoOrder);
    return 1;
}

#pragma endregion 20.3-13
