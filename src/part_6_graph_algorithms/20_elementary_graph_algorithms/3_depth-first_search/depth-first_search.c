#include <stdio.h>
#include <stdlib.h>

#define TASK 6

typedef struct Node {
    int data;
    struct Node* next;
} Node;

struct List {
    struct Node* head;
};

struct Graph {
    int numVertices;
    struct List* array;
};

void graph_free(struct Graph* g) {
    for (int i = 0; i < g->numVertices; i++) {
        struct Node* current = g->array[i].head;
        while (current) {
            struct Node* temp = current;
            current = current->next;
            free(temp); 
        }
    }
    free(g->array);
    free(g);
}

struct Node* create_node(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

struct Graph* graph_create(int numVertices) {
    struct Graph* g = (struct Graph*)malloc(sizeof(struct Graph));
    g->numVertices = numVertices;
    g->array = (struct List*)malloc(numVertices * sizeof(struct List));

    for (int i = 0; i < numVertices; i++) g->array[i].head = NULL;

    return g;
}

void graph_add_edge(struct Graph* g, int src, int dest) {
    struct Node* newNode = create_node(dest);
    newNode->next = g->array[src].head;
    g->array[src].head = newNode;
}

void dfs_visit(struct Graph* g, int vertex, int visited[]) {
    visited[vertex] = 1;
    printf("%d ", vertex);

    struct Node* currNode = g->array[vertex].head;
    while (currNode) {
        int adjacent = currNode->data;
        if (!visited[adjacent]) dfs_visit(g, adjacent, visited);
        currNode = currNode->next;
    }
}

void dfs(struct Graph* g, int* order, int orderSize) {
    int* visited = (int*)malloc(g->numVertices * sizeof(int));
    for (int i = 0; i < g->numVertices; i++) visited[i] = 0;
    for (int i = 0; i < orderSize; i++)
        if (!visited[order[i]]) dfs_visit(g, order[i], visited);
    free(visited);
}

#pragma region 20.3-6

void iterative_dfs_visit(struct Graph* g, int source, int visited[]) {
    int* stack = (int*)malloc(g->numVertices * sizeof(int));
    int top = -1;
    stack[++top] = source;

    while (top != -1) {
        int vertex = stack[top--];
        if (!visited[vertex]) {
            visited[vertex] = 1;
            printf("%d ", vertex);

            struct Node* currNode = g->array[vertex].head;
            while (currNode) {
                if (!visited[currNode->data]) stack[++top] = currNode->data;
                currNode = currNode->next;
            }
        }
    }

    free(stack);
}

void iterative_dfs(struct Graph* g, int* order, int orderSize) {
    int* visited = (int*)malloc(g->numVertices * sizeof(int));
    for (int i = 0; i < g->numVertices; i++) visited[i] = 0;

    for (int i = 0; i < orderSize; i++)
        if (!visited[order[i]]) iterative_dfs_visit(g, order[i], visited);

    free(visited);
}

#pragma endregion 20.3-6

#pragma region 20.3-9

#define WHITE 0
#define GRAY 1
#define BLACK 2

typedef struct ColoredVertex {
    int id;
    int color;
    int d;
    int f;
    int pi;
} ColoredVertex;

typedef struct ColoredGraph {
    int numVertices;
    int** adj;
    ColoredVertex* vertices;
} ColoredGraph;

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
    ColoredGraph* g = malloc(sizeof(ColoredGraph));
    g->numVertices = numVertices;
    g->adj = malloc(numVertices * sizeof(int *));
    g->vertices = malloc(numVertices * sizeof(numVertices));
    for (int i = 0; i < numVertices; i++) {
        g->adj[i] = calloc(numVertices, sizeof(int));
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

void graph_add_undirected_edge(struct Graph* g, int u, int v) {
    struct Node* node1 = create_node(v);
    node1->next = g->array[u].head;
    g->array[u].head = node1;

    struct Node* node2 = create_node(u);
    node2->next = g->array[v].head;
    g->array[v].head = node2;
}

void dfs_visit_both_dirs(struct Graph* g, int u, int* visited) {
    visited[u] = 1;
    struct Node* currNode = g->array[u].head;

    while (currNode) {
        int v = currNode->data;
        printf("%d -> %d\n", u, v);
        if (!visited[u]) dfs_visit_both_dirs(g, v, visited);
        printf("%d -> %d\n", v, u);
        currNode = currNode->next;
    }
}

void dfs_both_dirs(struct Graph* g) {
    int* visited = (int*)calloc(g->numVertices, sizeof(int));
    for (int i = 0; i < g->numVertices; i++)
        if (!visited[i]) dfs_visit_both_dirs(g, i, visited);
    free(visited);
}

#pragma endregion 20.3-11

#pragma region 20.3-12

typedef struct CCNode {
    int cc;
    int color;
    int pi;
    int d;
    int f;
    struct CCNode* next;
} CCNode;

typedef struct CCList {
    struct CCNode* head;
} CCList;

typedef struct CCGraph {
    int numVertices;
    struct CCList* array;
} CCGraph;

CCGraph* cc_graph_create(int numVertices) {
    CCGraph* g = (CCGraph*)malloc(sizeof(CCGraph));
    g->numVertices = numVertices;
    g->array = (CCList*)malloc(numVertices * sizeof(CCList));

    for (int i = 0; i < numVertices; i++) g->array[i].head = NULL;
    
    return g;
}

CCNode* cc_node_create(int cc) {
    CCNode* new_node = (CCNode*)malloc(sizeof(CCNode));
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

void topo_sort_helper(struct Graph* g, int v, int* visited, int* stack, int* stackIdx) {
    visited[v] = 1;

    struct Node* currNode = g->array[v].head;
    while (currNode) {
        int adjacent = currNode->data;
        if (!visited[adjacent]) 
            topo_sort_helper(g, adjacent, visited, stack, stackIdx);
        currNode = currNode->next;
    }
    stack[(*stackIdx)--] = v;
}

int* topological_sort(struct Graph* g) {
    int* visited = (int*)calloc(g->numVertices, sizeof(int));
    int* stack = (int*)malloc(g->numVertices * sizeof(int));
    int stackIdx = g->numVertices - 1;

    for (int i = 0; i < g->numVertices; i++) {
        if (!visited[i]) topo_sort_helper(g, i, visited, stack, &stackIdx);
    }

    free(visited);
    return stack;
}

int is_singly_connected(struct Graph* g) {
    int* topoOrder = topological_sort(g);
    int** ancestors = (int**)malloc(g->numVertices * sizeof(int*));
    int* ancestorSizes = (int*)calloc(g->numVertices, sizeof(int));

    for (int i = 0; i < g->numVertices; i++) {
        ancestors[i] = (int*)calloc(g->numVertices, sizeof(int));
        ancestors[i][ancestorSizes[i]++] = i;
    }

    for (int i = 0; i < g->numVertices; i++) {
        int u = topoOrder[i];

        struct Node* currNode = g->array[u].head;
        while (currNode) {
            int v = currNode->data;

            for (int j = 0; j < ancestorSizes[u]; j++) {
                for (int k = 0; k < ancestorSizes[v]; k++) {
                    if (ancestors[u][j] == ancestors[v][k]) {
                        free(topoOrder);
                        for (int l = 0; l < g->numVertices; l++) free(ancestors[l]);
                        free(ancestors);
                        free(ancestorSizes);
                        return 0;
                    }
                }
            }

            for (int j = 0; j < ancestorSizes[u]; j++) {
                ancestors[v][ancestorSizes[v]++] = ancestors[u][j];
            }

            currNode = currNode->next;
        }
    }

    free(topoOrder);
    for (int i = 0; i < g->numVertices; i++) free(ancestors[i]);
    free(ancestors);
    free(ancestorSizes);

    return 1;
}

#pragma endregion 20.3-13

int main(void) {
    switch (TASK)
    {
        case 1: {
            int numVertices = 5;
            struct Graph* g = graph_create(numVertices);

            graph_add_edge(g, 2, 0);
            graph_add_edge(g, 0, 2);
            graph_add_edge(g, 1, 2);
            graph_add_edge(g, 0, 1);
            graph_add_edge(g, 3, 3);
            graph_add_edge(g, 1, 3);
            graph_add_edge(g, 3, 4);

            int order[] = {2, 0, 1, 3};
            int orderSize = sizeof(order) / sizeof(order[0]);

            printf("DFS: \n");
            dfs(g, order, orderSize);

            graph_free(g);

            break;
        }

        case 2: {
            // 20.3-6
            int numVertices = 5;
            struct Graph* g = graph_create(numVertices);

            graph_add_edge(g, 2, 0);
            graph_add_edge(g, 0, 2);
            graph_add_edge(g, 1, 2);
            graph_add_edge(g, 0, 1);
            graph_add_edge(g, 3, 3);
            graph_add_edge(g, 1, 3);
            graph_add_edge(g, 3, 4);

            int order[] = {2, 0, 1, 3};
            int orderSize = sizeof(order) / sizeof(order[0]);

            printf("DFS: \n");
            iterative_dfs(g, order, orderSize);

            graph_free(g);

            break;
        }

        case 3: {
            // 20.3-9
            int numVertices = 5;
            struct ColoredGraph* g = colored_graph_create(numVertices);

            colored_graph_add_edge(g, 2, 0);
            colored_graph_add_edge(g, 0, 2);
            colored_graph_add_edge(g, 1, 2);
            colored_graph_add_edge(g, 0, 1);
            colored_graph_add_edge(g, 3, 3);
            colored_graph_add_edge(g, 1, 3);
            colored_graph_add_edge(g, 3, 4);

            colored_dfs_print(g);
            colored_graph_free(g);

            break;
        }

        case 4: {
            // 20.3-11
            int numVertices = 5;
            struct Graph* g = graph_create(numVertices);

            graph_add_undirected_edge(g, 2, 0);
            graph_add_undirected_edge(g, 0, 2);
            graph_add_undirected_edge(g, 1, 2);
            graph_add_undirected_edge(g, 0, 1);
            graph_add_undirected_edge(g, 3, 3);
            graph_add_undirected_edge(g, 1, 3);
            graph_add_undirected_edge(g, 3, 4);

            dfs_both_dirs(g);

            graph_free(g);
            
            break;
        }

        case 5: {
            // 20.3-12
            int numVertices = 7;
            CCGraph* g = cc_graph_create(numVertices);

            cc_graph_add_undirected_edge(g, 0, 1);
            cc_graph_add_undirected_edge(g, 1, 2);
            cc_graph_add_undirected_edge(g, 3, 4);
            cc_graph_add_undirected_edge(g, 5, 6);

            cc_dfs(g);
            cc_graph_free(g);

            break;
        }

        case 6: {
            // 20.3.13
            int numVertices = 6;
            struct Graph* g = graph_create(numVertices);

            graph_add_edge(g, 0, 1);
            graph_add_edge(g, 0, 2);
            graph_add_edge(g, 1, 3);
            graph_add_edge(g, 2, 3);
            graph_add_edge(g, 3, 4);
            graph_add_edge(g, 4, 5);

            if (is_singly_connected(g)) printf("The graph is singly connected.\n");
            else printf("The graph is not singly connected.\n");

            graph_free(g);

            break;
        }
        
        default:
            break;
    }

    return 0;
}