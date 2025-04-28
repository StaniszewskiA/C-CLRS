#include <stdio.h>
#include <stdlib.h>

#define TASK 6

#pragma region utils

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

Node* create_node(int vertex) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->vertex = vertex;
    new_node->next = NULL;
    return new_node;
}

void insert_edge(Node** adjList, int vertex) {
    Node* new_node = create_node(vertex);
    new_node->next = *adjList;
    *adjList = new_node;
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

void print_matrix(int** matrix, int numVertices) {
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

void free_matrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) free(matrix[i]);
    free(matrix);
}

int** allocate_matrix(int size) {
    int** matrix = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) 
        matrix[i] = (int*)malloc(size * sizeof(int));
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
    int* A = (int*)calloc(numVertices, sizeof(int));

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
    int* visited = (int*)calloc(numVertices, sizeof(int));

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

int next_power_of_two(int n) {
    int power = 1;
    while (power < n) power <<= 1;
    return power;
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

void strassen_multiply(int** A, int** B, int** C, int size) {
    if (size == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = size / 2;
    int **A11 = allocate_matrix(newSize);
    int **A12 = allocate_matrix(newSize);
    int **A21 = allocate_matrix(newSize);
    int **A22 = allocate_matrix(newSize);
    int **B11 = allocate_matrix(newSize);
    int **B12 = allocate_matrix(newSize);
    int **B21 = allocate_matrix(newSize);
    int **B22 = allocate_matrix(newSize);

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    int **M1 = allocate_matrix(newSize);
    int **M2 = allocate_matrix(newSize);
    int **M3 = allocate_matrix(newSize);
    int **M4 = allocate_matrix(newSize);
    int **M5 = allocate_matrix(newSize);
    int **M6 = allocate_matrix(newSize);
    int **M7 = allocate_matrix(newSize);
    int **temp1 = allocate_matrix(newSize);
    int **temp2 = allocate_matrix(newSize);

    add_mat(A11, A22, temp1, newSize);   
    add_mat(B11, B22, temp2, newSize);    
    strassen_multiply(temp1, temp2, M1, newSize);

    add_mat(A21, A22, temp1, newSize);  
    strassen_multiply(temp1, B11, M2, newSize);

    sub_mat(B12, B22, temp2, newSize);  
    strassen_multiply(A11, temp2, M3, newSize);

    sub_mat(B21, B11, temp2, newSize);   
    strassen_multiply(A22, temp2, M4, newSize);

    add_mat(A11, A12, temp1, newSize);  
    strassen_multiply(temp1, B22, M5, newSize);

    sub_mat(A21, A11, temp1, newSize);  
    add_mat(B11, B12, temp2, newSize);    
    strassen_multiply(temp1, temp2, M6, newSize);

    sub_mat(A12, A22, temp1, newSize);   
    add_mat(B21, B22, temp2, newSize);  
    strassen_multiply(temp1, temp2, M7, newSize);

    int **C11 = allocate_matrix(newSize);
    int **C12 = allocate_matrix(newSize);
    int **C21 = allocate_matrix(newSize);
    int **C22 = allocate_matrix(newSize);

    add_mat(M1, M4, temp1, newSize);       
    sub_mat(temp1, M5, temp2, newSize);    
    add_mat(temp2, M7, C11, newSize);    

    add_mat(M3, M5, C12, newSize);      
    add_mat(M2, M4, C21, newSize);       

    add_mat(M1, M3, temp1, newSize);
    sub_mat(temp1, M2, temp2, newSize);
    add_mat(temp2, M6, C22, newSize);     

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }

    free_matrix(A11, newSize); free_matrix(A12, newSize);
    free_matrix(A21, newSize); free_matrix(A22, newSize);
    free_matrix(B11, newSize); free_matrix(B12, newSize);
    free_matrix(B21, newSize); free_matrix(B22, newSize);
    free_matrix(C11, newSize); free_matrix(C12, newSize);
    free_matrix(C21, newSize); free_matrix(C22, newSize);
    free_matrix(M1, newSize);  free_matrix(M2, newSize); 
    free_matrix(M3, newSize);  free_matrix(M4, newSize);
    free_matrix(M5, newSize);  free_matrix(M6, newSize);
    free_matrix(M7, newSize);
    free_matrix(temp1, newSize); free_matrix(temp2, newSize);
}

void mat_square_graph(int** matrix, int** result, int n) {
    int m = next_power_of_two(n);
    int** A = allocate_matrix(m);
    int** C = allocate_matrix(m);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            A[i][j] = matrix[i][j];

    strassen_multiply(A, A, C, m);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[i][j] = C[i][j] ? 1 : 0;

    free_matrix(A, m);
    free_matrix(C, m);
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

int main(void) {
    int numVertices = 5;
 
    switch (TASK)
    {
        case 1: {
            // 20.1-3 with adjList
            Node* adjList[numVertices];
            init_adj_list(adjList, numVertices);

            int edges[][2] = {
                {0, 1},
                {0, 2},
                {1, 2},
                {2, 0},
                {3, 4}
            };
            int numEdges = sizeof(edges) / sizeof(edges[0]);

            insert_edges(adjList, edges, numEdges);

            printf("Original Graph (Adjacency List):\n");
            print_adj_list(adjList, numVertices);

            Node* adjListT[numVertices];
            init_adj_list(adjListT, numVertices);

            list_graph_transpose(adjList, adjListT, numVertices);

            printf("Transposed Graph (Adjacency List):\n");
            print_adj_list(adjListT, numVertices);

            free_adj_list(adjList, numVertices);
            free_adj_list(adjListT, numVertices);

            break;
        }

        case 2: {
            // 20.1-3 with adjMat
            int** matrix = allocate_matrix(numVertices);
            init_matrix(matrix, numVertices);
            mat_set_edges(matrix);

            printf("\nOriginal Graph (Adjacency Matrix):\n");
            print_matrix(matrix, numVertices);

            int** matrixT = allocate_matrix(numVertices);
            mat_graph_transpose(matrix, matrixT, numVertices);

            printf("\nTransposed Graph (Adjacency Matrix):\n");
            print_matrix(matrixT, numVertices);


            free_matrix(matrix, numVertices);
            free_matrix(matrixT, numVertices);

            break;
        }

        case 3:{
            // 20.1-4
            Node* adjList[numVertices];
            init_adj_list(adjList, numVertices);

            int edges[][2] = {
                {0, 1},
                {0, 2},
                {1, 2},
                {0, 2}, // duplicate
                {3, 4},
                {3, 4}, // duplicate
                {1, 1}  // self-loop
            };
            int numEdges = sizeof(edges) / sizeof(edges[0]);

            insert_edges(adjList, edges, numEdges);

            printf("Original Graph (Adjacency List):\n");
            print_adj_list(adjList, numVertices);

            Node* result[numVertices];
            init_adj_list(result, numVertices);

            demultify_graph(adjList, result, numVertices);
            printf("Demultified Graph (Adjacency List):\n");
            print_adj_list(result, numVertices);

            free_adj_list(adjList, numVertices);
            free_adj_list(result, numVertices);

            break;
        }

        case 4: {
            // 20.1-5 with adjList
            Node* adjList[numVertices];
            init_adj_list(adjList, numVertices);

            int edges[][2] = {
                {0, 1},
                {0, 2},
                {1, 2},
                {2, 4},
                {0, 4}
            };
            int numEdges = sizeof(edges) / sizeof(edges[0]);

            insert_edges(adjList, edges, numEdges);

            printf("Original Graph (Adjacency List):\n");
            print_adj_list(adjList, numVertices);

            Node* result[numVertices];
            init_adj_list(result, numVertices);

            adj_square_graph(adjList, result, numVertices);
            printf("Squared Graph (Adjacency List):\n");
            print_adj_list(result, numVertices);

            free_adj_list(adjList, numVertices);
            free_adj_list(result, numVertices);

            break;
        }

        case 5: {
            // 20.1-5 with adjMat
            int** matrix = allocate_matrix(numVertices);
            init_matrix(matrix, numVertices);
            mat_set_edges(matrix);

            printf("\nOriginal Graph (Adjacency Matrix):\n");
            print_matrix(matrix, numVertices);

            int** res = allocate_matrix(numVertices);

            mat_square_graph(matrix, res, numVertices);
            printf("\nSquared Graph (Adjacency Matrix):\n");
            print_matrix(res, numVertices);

            free_matrix(matrix, numVertices);
            free_matrix(res, numVertices);

            break;
        }

        case 6: {
            // 20.1-6
            int** matrix = allocate_matrix(numVertices);
            init_matrix(matrix, numVertices);
            mat_set_edges(matrix);

            find_universal_sink(matrix, numVertices);
            free_matrix(matrix, numVertices);

            break;
        }
        
        default:
            break;
    }

    return 0;
}