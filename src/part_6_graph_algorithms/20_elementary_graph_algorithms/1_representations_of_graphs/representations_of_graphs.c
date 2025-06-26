#include "part_6_graph_algorithms/20_elementary_graph_algorithms/elementary_graph_algorithms.h"

#pragma region utils

Node* create_node(int vertex) {
    Node* newNode = (Node*)safe_malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

void insert_edge(Node** adjList, int vertex) {
    Node* newNode = create_node(vertex);
    newNode->next = *adjList;
    *adjList = newNode;
}

void insert_edges(Node** adjList, int edges[][2], int numEdges) {
    for (int i = 0; i < numEdges; i++) 
        insert_edge(&adjList[edges[i][0]], edges[i][1]);
}

void print_adj_list(Node** adjList, int numVertices) {
    for (int i = 0; i < numVertices; i++) {
        Node* temp = adjList[i];
        printf("Vertex %d: ", i);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

void graph_print_matrix(int** matrix, int numVertices) {
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) printf("%d ", matrix[i][j]);
        printf("\n");
    }
}

void init_adj_list(Node** adjList, int numVertices) {
    for (int i = 0; i < numVertices; i++) adjList[i] = NULL;   
}

void init_matrix(int** matrix, int numVertices) {
    for (int i = 0; i < numVertices; i++) 
        for (int j = 0; j < numVertices; j++) matrix[i][j] = 0;
}

void free_adj_list(Node** adjList, int numVertices) {
    for (int i = 0; i < numVertices; i++) {
        Node* temp;
        while (adjList[i]) {
            temp = adjList[i];
            adjList[i] = adjList[i]->next;
            free(temp);
        }
    }
}

void graph_free_matrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) free(matrix[i]);
    free(matrix);
}

int** graph_allocate_matrix(int size) {
    int** matrix = (int**)safe_malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) 
        matrix[i] = (int*)safe_malloc(size * sizeof(int));
    return matrix;
}

void mat_set_edges(int** matrix) {
    matrix[0][1] = 1;
    matrix[0][2] = 1;
    matrix[1][2] = 1;
    matrix[2][0] = 1;
    matrix[3][4] = 1;
}

#pragma endregion utils

#pragma region 20.1-3 

void list_graph_transpose(Node** adjList, Node** adjListT, int numVertices) {
    for (int u = 0; u < numVertices; u++) {
        Node* temp = adjList[u];
        while (temp) {
            insert_edge(&adjListT[temp->vertex], u);
            temp = temp->next;
        }
    }
}

void mat_graph_transpose(int** matrix, int** matrixT, int numVertices) {
    for (int i = 0; i < numVertices; i++)
        for (int j = 0; j < numVertices; j++) matrixT[i][j] = matrix[j][i];
}

#pragma endregion 20.1-3 

#pragma region 20.1-4

void demultify_graph(Node** adjList, Node** result, int numVertices) {
    int* A = (int*)safe_calloc(numVertices, sizeof(int));

    for (int u = 0; u < numVertices; u++) {
        Node* temp = adjList[u];
        while (temp) {
            int v = temp->vertex;
            if (v != u && A[v] != u + 1) {
                A[v] = u + 1;
                insert_edge(&result[u], v);
                insert_edge(&result[v], u);
            }
            temp = temp->next;
        }
    }

    free(A);
}

#pragma endregion 20.1-4

#pragma region 20.1-5

void adj_square_graph(Node** adjList, Node** result, int numVertices) {
    int* visited = (int*)safe_calloc(numVertices, sizeof(int));

    for (int u = 0; u < numVertices; u++) {
        Node* vNode = adjList[u];
        while (vNode) {
            int v = vNode->vertex;

            if (!visited[v]) {
                visited[v] = 1;
                insert_edge(&result[u], v);
            }

            Node* wNode = adjList[v];
            while (wNode) {
                int w = wNode->vertex;

                if (!visited[v]) {
                    visited[w] = 1;
                    insert_edge(&result[u], w);
                }

                wNode = wNode->next;
            }
            vNode = vNode->next;
        }
        Node* temp = result[u];
        while (temp) {
            visited[temp->vertex] = 0;
            temp = temp->next;
        }
    }

    free(visited);
}

void add_mat(int** A, int** B, int** C, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void sub_mat(int** A, int** B, int** C, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void mat_square_graph(int** matrix, int** result, int n) {
    int m = next_power_of_two(n);
    int** A = graph_allocate_matrix(m);
    int** C = graph_allocate_matrix(m);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            A[i][j] = matrix[i][j];

    strassen_algorithm(A, A, C, m);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[i][j] = C[i][j] ? 1 : 0;

    graph_free_matrix(A, m);
    graph_free_matrix(C, m);
}

#pragma endregion 20.1-5

#pragma region 20.1-6

int is_universal_sink(int** matrix, int numVertices, int candidate) {
    for (int j = 0; j < numVertices; j++) 
        if (matrix[candidate][j] != 0 && candidate != j) return 0;
    for (int i = 0; i < numVertices; i++)
        if (matrix[i][candidate] != 1 && i != candidate) return 0;
    return 1;
}

void find_universal_sink(int** matrix, int numVertices) {
    int i = 0, j = 0;

    while (i < numVertices && j < numVertices) {
        if (matrix[i][j] == 1) i++;
        else j++;
    }

    if (i >= numVertices)  
        printf("No universal sink found!\n");
    if (is_universal_sink(matrix, numVertices, i))
        printf("Vertex %d is the universal sink!\n", i);
    printf("No universal sink found!\n");
}

#pragma endregion 20.1-6
