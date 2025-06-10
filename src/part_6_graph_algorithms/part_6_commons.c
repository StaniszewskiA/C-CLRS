#include "../../include/part_6_graph_algorithms/part_6_commons.h"

Node* create_node(int vertex) {
    Node* newNode = safe_malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

ListGraph* list_graph_create(int numVertices) {
    ListGraph* g = safe_malloc(sizeof(ListGraph));
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
    Node* newNode = create_node(v);
    newNode->next = g->adjList[u];
    g->adjList[u] = newNode;
}

MatGraph* mat_graph_create(int numVertices) {
    MatGraph* g = safe_malloc(sizeof(MatGraph));
    g->numVertices = numVertices;

    for (int i = 0; i < numVertices; i++)
        for (int j = 0; j < numVertices; j++) g->adjMat[i][j] = INF;
    return g;
}

void mat_graph_free(MatGraph* g) {
    free(g);
}

void list_graph_add_undirected_edge(ListGraph* g, int u, int v) {
    Node* node1 = create_node(v); 
    if (!node1) return; 
    node1->next = g->adjList[u];
    g->adjList[u] = node1;

    Node* node2 = create_node(u);
    if (!node2) { free(node1); return; } 
    node2->next = g->adjList[v];
    g->adjList[v] = node2;
}

void mat_graph_add_directed_edge(MatGraph* g, int u, int v) {
    g->adjMat[u][v] = 1;
}

void mat_graph_add_undirected_edge(MatGraph* g, int u, int v) {
    g->adjMat[u][v] = 1;
    g->adjMat[v][u] = 1;
}

int mat_graph_has_cycle(MatGraph* g, int v, int visited[], int recursionStack[]) {
    if (!visited[v]) {
        visited[v] = 1;
        recursionStack[v] = 1;
        for (int i = 0; i < g->numVertices; i++) {
            if (g->adjMat[v][i]) {
                if (!visited[i] && mat_graph_has_cycle(g, i, visited, recursionStack)) return 1;
                else if (recursionStack[i]) return 1;
            }
        }
    }
    recursionStack[v] = 0;
    return 0;
}

int mat_graph_is_dag(MatGraph* g) {
    int visited[MAX_GRAPH_VERTICES] = {0};
    int recursionStack[MAX_GRAPH_VERTICES] = {0};

    for (int i = 0; i < g->numVertices; i++) 
        if (mat_graph_has_cycle(g, i, visited, recursionStack)) return 0;
    return 1;
}

void mat_graph_dfs(MatGraph* g, int v, int visited[], int stack[], int* stackIdx) {
    visited[v] = 1;
    for (int u = 0; u < g->numVertices; u++) {
        if (g->adjMat[v][u] && !visited[u]) 
            mat_graph_dfs(g, u, visited, stack, stackIdx);
    }
    stack[(*stackIdx)++] = v;
}

MatGraph* transpose_mat_graph(MatGraph* g) {
    MatGraph* gt = mat_graph_create(g->numVertices);
    for (int u = 0; u < g->numVertices; u++) {
        for (int v = 0; v < g->numVertices; v++) {
            if (g->adjMat[u][v]) mat_graph_add_directed_edge(gt, v, u);
        }
    }
    return gt;
}

void assign_scc(
    MatGraph* gt, 
    int v, 
    int visited[], 
    int component[], 
    int compId
) {
    visited[v] = 1;
    component[v] = compId;
    for (int u = 0; u < gt->numVertices; u++) {
        if (gt->adjMat[v][u] && !visited[u])
            assign_scc(gt, u, visited, component, compId);
    } 
}

int kosaraju(MatGraph* g, int component[]) {
    int stack[MAX_GRAPH_VERTICES];
    int stackIdx = 0;
    int visited[MAX_GRAPH_VERTICES] = {0};

    // mat_graph_dfs
    for (int v = 0; v < g->numVertices; v++) {
        if (!visited[v]) mat_graph_dfs(g, v, visited, stack, &stackIdx);
    }

    // Transposition
    MatGraph* gt = transpose_mat_graph(g);

    // Assignment
    memset(visited, 0, sizeof(visited));
    int compId = 0;
    for (int i = stackIdx - 1; i >= 0; i--) {
        int v = stack[i];
        if (!visited[v]) {
            assign_scc(gt, v, visited, component, compId);
            compId++;
        }
    }

    mat_graph_free(gt);
    return compId;
}

void mat_graph_remove_undirected_edge(MatGraph* g, int u, int v) {
    g->adjMat[u][v] = 0;
    g->adjMat[v][u] = 0;
}

void mat_graph_add_undirected_weighted_edge(MatGraph* g, int u, int v, int weight) {
    g->adjMat[u][v] = weight;
    g->adjMat[v][u] = weight;
}


void mat_graph_print(MatGraph* g) {
    printf("Graph with %d vertices:\n", g->numVertices);
    for (int i = 0; i < g->numVertices; i++) {
        printf("Vertex %d is connected to: ", i);
        for (int j = 0; j < g->numVertices; j++) {
            if (g->adjMat[i][j] > 0) printf("%d(w:%d) ", j, g->adjMat[i][j]);
        }
        printf("\n");
    }
}

int mat_graph_is_connected(MatGraph* g) {
    int visited[MAX_GRAPH_VERTICES] = {0};
    int stack[MAX_GRAPH_VERTICES];
    int stackTop = -1;
    int startVertex = 0;
    int visitedCnt = 0;

    stack[++stackTop] = startVertex;
    visited[startVertex] = 1;
    visitedCnt++;

    while (stackTop >= 0) {
        int u = stack[stackTop--];
        for (int v = 0; v < g->numVertices; v++) {
            if (g->adjMat[u][v] > 0 && !visited[v]) {
                stack[++stackTop] = v;
                visited[v] = 1;
                visitedCnt++;
            }
        }
    }

    return (visitedCnt == g->numVertices);
}

int mat_graph_check_if_path_exists(MatGraph* g, int source, int target) {
    int visited[MAX_GRAPH_VERTICES] = {0};
    int stack[MAX_GRAPH_VERTICES];
    int stackTop = -1;

    stack[++stackTop] = source;
    visited[source] = 1;

    while (stackTop >= 0) {
        int u = stack[stackTop--];
        if (u == target) return 1;
        for (int v = 0; v < g->numVertices; v++) {
            if (g->adjMat[u][v] >0 && !visited[v]) {
                stack[++stackTop] = v;
                visited[v] = 1;
            }
        }
    }

    return 0;
}

WeightedNode* create_weighted_node(int vertex, int weight) {
    WeightedNode* newNode = malloc(sizeof(WeightedNode));
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

WeightedNodeListGraph* weighted_node_list_graph_create(int numVertices) {
    WeightedNodeListGraph* g = malloc(sizeof(WeightedNodeListGraph));
    g->numVertices = numVertices;
    for (int i = 0; i < numVertices; i++) g->adjList[i] = NULL;
    return g;
}

void weighted_node_list_graph_free(WeightedNodeListGraph* g) {
    for (int i = 0; i < g->numVertices; i++) {
        WeightedNode* temp = g->adjList[i];
        while (temp) {
            WeightedNode* toDelete = temp;
            temp = temp->next;
            free(toDelete);
        }
    }
    free(g);
}

void weighted_node_list_graph_add_edge(
    WeightedNodeListGraph* g, 
    int u, 
    int v, 
    int weight
) {
    WeightedNode* newNode = create_weighted_node(v, weight);
    newNode->next = g->adjList[u];
    g->adjList[u] = newNode;
}

void relax_edge(int u, int v, int weight, int dist[], int pred[]) {
    if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
        dist[v] = dist[u] + weight;
        pred[v] = u;
    }
}

void print_path(int pred[], int dest) {
    if (dest == -1) return;
    if (pred[dest] != -1) {
        print_path(pred, pred[dest]);
        printf(" -> ");
    }
    printf("%d", dest);
}

void modified_relax(int u, int v, int weight, int dist[], int pred[]) {
    int pathThroughU = (dist[u] == INT_MAX) ? INT_MAX : dist[u] + weight;
    int minVal = fmin(weight, pathThroughU);

    if (dist[v] > minVal) {
        dist[v] = minVal;
        pred[v] = (pathThroughU < weight) ? pred[u] : u;
    }
}

int find_negative_cycle_dfs(
    WeightedNodeListGraph* g,
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

    WeightedNode* tmp = g->adjList[curr];
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
                WeightedNode* edge = g->adjList[u];
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

void mat_graph_add_directed_weighted_edge(
    MatGraph* g, 
    int u, 
    int v, 
    int weight
) {
    g->adjMat[u][v] = weight;
}

void init_single_source(int dist[], int pred[], int numVertices, int src) {
    for (int i = 0; i < numVertices; i++) {
        dist[i] = INT_MAX;
        pred[i] = -1;
    }
    dist[src] = 0;
}

void safe_relax_edge(int u, int v, int weight, int dist[], int pred[]) {
    if (dist[u] != INF && dist[u] + weight < dist[v]) {
        dist[v] = dist[u] + weight;
        pred[v] = u;
    }
}

void mat_graph_remove_undirected_weighted_edge(MatGraph* g, int u, int v) {
    g->adjMat[u][v] = 0;
    g->adjMat[v][u] = 0;
}

void mat_graph_remove_directed_weighted_edge(
    MatGraph* g, 
    int u, 
    int v
) {
    g->adjMat[u][v] = INF;
}


FibNode* fib_node_create(int vertex, int key) {
    FibNode* node = (FibNode*)malloc(sizeof(FibNode));
    node->vertex = vertex;
    node->key = key;
    node->parent = node->child = NULL;
    node->left = node->right = node;
    node->degree = 0;
    node->mark = 0;
    return node;
}

FibHeap* fib_heap_create() {
    FibHeap* heap = (FibHeap*)malloc(sizeof(FibHeap));
    heap->min = NULL;
    heap->size = 0;
    return heap;
}

void fib_insert(FibHeap* heap, FibNode* node) {
    if (!heap->min) {
        heap->min = node;
        node->left = node->right = node;
    } else {
        node->left = heap->min;
        node->right = heap->min->right;
        heap->min->right->left = node;
        heap->min->right = node;
        if (node->key < heap->min->key) heap->min = node;
    }
    heap->size++;
}

void fib_link(FibNode* y, FibNode* x) {
    y->left->right = y->right;
    y->right->left = y->left;
    y->parent = x;
    if (!x->child) {
        x->child = y;
        y->left = y->right = y;
    } else {
        y->left = x->child;
        y->right = x->child->right;
        x->child->right->left = y;
        x->child->right = y;
    }
    x->degree++;
    y->mark = 0;
}

void fib_consolidate(FibHeap* heap) {
    int D = 16;
    FibNode* A[16] = {0};
    FibNode* w = heap->min;
    if (!w) return;
    int rootCnt = 0;
    FibNode* x = w;

    do {
        rootCnt++;
        x = x->right;
    } while (x != w);

    while (rootCnt--) {
        x = heap->min;
        FibNode* next = x->right;
        int d = x->degree;
        while (A[d]) {
            FibNode* y = A[d];
            if (x->key > y->key) {
                FibNode* temp = x;
                x = y;
                y = temp;
            }
            fib_link(y, x);
            A[d] = NULL;
            d++;
        }
        A[d] = x;
        heap->min = next;
    }
    heap->min = NULL;
    for (int i = 0; i < D; i++) {
        if (!A[i]) continue;
        if (!heap->min) {
            heap->min = A[i];
            A[i]->left = A[i]->right = A[i];
        } else {
            A[i]->left = heap->min;
            A[i]->right = heap->min->right;
            heap->min->right->left = A[i];
            heap->min->right = A[i];
            if (A[i]->key < heap->min->key)
                heap->min = A[i];
        }
    }
}

FibNode* fib_extract_min(FibHeap* heap) {
    FibNode* z = heap->min;
    if (!z) return NULL;
    if (z->child) {
        FibNode* x = z->child;
        do {
            FibNode* next = x->right;
            x->left = heap->min;
            x->right = heap->min->right;
            heap->min->right->left = x;
            heap->min->right = x;
            x->parent = NULL;
            x = next;
        } while (x != z->child);
    }
    z->left->right = z->right;
    z->right->left = z->left;
    if (z == z->right) heap->min = NULL;
    else {
        heap->min = z->right;
        fib_consolidate(heap);
    }
    heap->size--;

    return z;
}

void fib_cut(FibHeap* heap, FibNode* x, FibNode* y) {
    if (y->child == x) {
        if (x->right != x) y->child = x->right;
        else y->child = NULL;
    }
     x->left->right = x->right;
    x->right->left = x->left;
    y->degree--;
    x->left = heap->min;
    x->right = heap->min->right;
    heap->min->right->left = x;
    heap->min->right = x;
    x->parent = NULL;
    x->mark = 0;
}

void fib_cascading_cut(FibHeap* heap, FibNode* y) {
    FibNode* z = y->parent;
    if (!z) return;
    if (!y->mark) y->mark = 1;
    else {
        fib_cut(heap, y, z);
        fib_cascading_cut(heap, z);
    }
}

void fib_dec_key(FibHeap* heap, FibNode* x, int k) {
    if (k > x->key) return;
    x->key = k;
    FibNode* y = x->parent;
    if (!y || x->key >= y->key) return;
    fib_cut(heap, x, y);
    fib_cascading_cut(heap, y);
    if (x->key < heap->min->key) heap->min = x;
}

void fib_free(FibNode* node) {
    if (!node) return;
    FibNode* start = node;
    do {
        FibNode* next = node->right;
        if (node->child) fib_free(node->child);
        free(node);
        node = next;
    } while (node != start);
}

FlowMatGraph* flow_mat_graph_create(int numVertices) {
    FlowMatGraph* g = malloc(sizeof(FlowMatGraph));
    g->numVertices = numVertices;
    for (int i = 0; i < numVertices; i++)
        for (int j = 0; j < numVertices; j++) {
            g->adjMat[i][j] = 0;
            g->flow[i][j] = 0;
        }
    return g;
}

void flow_mat_graph_free(FlowMatGraph* g) {
    free(g);
}

void flow_mat_graph_add_directed_edge(
    FlowMatGraph* g, 
    int u, 
    int v, 
    int capacity
) {
    g->adjMat[u][v] = capacity;
}

void flow_mat_graph_add_undirected_edge(FlowMatGraph* g, int u, int v) {
    g->adjMat[u][v] = 1;
    g->adjMat[v][u] = 1; 
}

void print_flow_matrix(FlowMatGraph* g, const char* name) {
    printf("%s", name);
    int n = g->numVertices;
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            printf("%d ", g->flow[u][v]);
        }
        printf("\n");
    }    
}

void flow_graph_copy(FlowMatGraph* dest, FlowMatGraph* src, int copyFlow) {
    for (int u = 0; u < src->numVertices; u++) {
        for (int v = 0; v < src->numVertices; v++) {
            if (copyFlow) dest->adjMat[u][v] = src->flow[u][v];
            else dest->adjMat[u][v] = src->adjMat[u][v];
        }
    }
}

FlowMatGraph* flow_mat_graph_copy(FlowMatGraph* original) {
    int n = original->numVertices;
    FlowMatGraph* copy = flow_mat_graph_create(n);

    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            copy->adjMat[u][v] = original->adjMat[u][v];
            copy->flow[u][v] = original->flow[u][v];
        }
    }

    return copy;
}

void flow_mat_graph_reset_flow(FlowMatGraph* g) {
    int n = g->numVertices;

    for (int u = 0; u < n; u++)
        for (int v = 0; v < n; v++) g->flow[u][v] = 0;
}