#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#define TASK 6
#define MAX_VERTICES 10
#define INF INT_MAX

#pragma region Matrix graph utils

typedef struct MatGraph {
    int adjMat[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
} MatGraph;

MatGraph* mat_graph_create(int numVertices) {
    MatGraph* g = malloc(sizeof(MatGraph));
    g->numVertices = numVertices;

    for (int i = 0; i < numVertices; i++)
        for (int j = 0; j < numVertices; j++) g->adjMat[i][j] = INF; 
    return g;
}

void mat_graph_free(MatGraph* g) {
    free(g);
}

void mat_graph_add_directed_edge(MatGraph* g, int u, int v, int weight) {
    g->adjMat[u][v] = weight;
}

#pragma region Matrix graph utils

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

void dijkstra(MatGraph* g, int src, int dist[], int pred[]) {
    int visited[MAX_VERTICES] = {0};
    init_single_source(dist, pred, g->numVertices, src);

    for (int iters = 0; iters < g->numVertices - 1; iters++) {
        int minDist = INF;
        int u = -1;

        for (int i = 0; i < g->numVertices; i++) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                u = i;
            }
        }

        if (u == -1) break;
        visited[u] = 1;


        for (int v = 0; v < g->numVertices; v++) {
            if (!visited[v] && g->adjMat[u][v] != INF)
                relax(u, v, g->adjMat[u][v], dist, pred);
        }
    }
}

void print_solution(int dist[], int pred[], int numVertices, int src) {
    printf("Shortest paths from source %d:\n", src);
    for (int i = 0; i < numVertices; i++) {
        printf("To vertex %d: ", i);
        if (dist[i] == INF) printf("No path exists\n");
        else {
            printf("Distance = %d", dist[i]);
            if (pred[i] != -1) printf(", Predecessor = %d", pred[i]);
            printf("\n");
        }
    }
}

#pragma region 22.3-4

typedef struct PriorityQueueNode {
    int vertex;
    int distance;
} PriorityQueueNode;

typedef struct PriorityQueue {
    PriorityQueueNode nodes[MAX_VERTICES];
    int size;
} PriorityQueue;

void pq_init(PriorityQueue* pg) {
    pg->size = 0;
}

void pq_push(PriorityQueue* pq, int vertex, int dist) {
    int i = pq->size++;
    while (i > 0 && pq->nodes[(i - 1) / 2].distance > dist) {
        pq->nodes[i] = pq->nodes[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    pq->nodes[i].vertex = vertex;
    pq->nodes[i].distance = dist;
}

PriorityQueueNode pq_pop(PriorityQueue* pq) {
    PriorityQueueNode minNode = pq->nodes[0];
    PriorityQueueNode lastNode = pq->nodes[--pq->size];

    int i = 0, child;
    while ((child = 2 * i + 1) < pq->size) {
        if (child + 1 < pq->size &&
            pq->nodes[child + 1].distance < pq->nodes[child].distance)
            child++;
        if (lastNode.distance <= pq->nodes[child].distance) break;
        pq->nodes[i] = pq->nodes[child];
        i = child;
    }
    pq->nodes[i] = lastNode;
    return minNode;
}

int pq_is_empty(PriorityQueue* pq) {
    return pq->size == 0;
}

void pq_relax(int u, int v, int weight, int dist[], int pred[], PriorityQueue* pq) {
    if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
        dist[v] = dist[u] + weight;
        pred[v] = u;
        pq_push(pq, v, dist[v]);
    }
}


void pq_dijkstra(MatGraph* g, int src, int dist[], int pred[]) {
    PriorityQueue pq;
    pq_init(&pq);

    int visited[MAX_VERTICES] = {0};
    init_single_source(dist, pred, g->numVertices, src);
    pq_push(&pq, src, 0);

    while (!pq_is_empty(&pq)) {
        PriorityQueueNode node = pq_pop(&pq);
        int u = node.vertex;
        if (visited[u]) continue;
        visited[u] = 1;
        for (int v = 0; v < g->numVertices; v++) {
            if (!visited[v] && g->adjMat[u][v] != INF)
                pq_relax(u, v, g->adjMat[u][v], dist, pred, &pq);
        }
    }
}

#pragma endregion 22.3-4

#pragma region 22.3-5

int verify_dijkstra_output(MatGraph* g, int dist[], int pred[], int src) {
    if (dist[src] != 0 || pred[src] != -1) return 0;

    // Check relaxations along the path
    for (int u = 0; u < g->numVertices; u++) {
        for (int v = 0; v < g->numVertices; v++) {
            if (g->adjMat[u][v] != INF) {
                if (dist[v] > dist[u] + g->adjMat[u][v]) return 0;
                if (pred[v] == u && dist[v] > dist[u] + g->adjMat[u][v]) return 0;
            }
        }
    }

    return 1;
}

#pragma endregion 22.3-5

#pragma region 22.3-7

void mat_graph_add_directed_reliability_edge(
    MatGraph* g, 
    int u, 
    int v, 
    double reliability
) {
    g->adjMat[u][v] = -log(reliability);
}

#pragma endregion 22.3-8

#pragma region 22.3-9

#define MAX_WEIGHT 10

typedef struct BucketNode {
    int vertex;
    struct BucketNode* next;
} BucketNode;

typedef struct Bucket {
    BucketNode* head;
} Bucket;

void bucket_add(Bucket* bucket, int vertex) {
    BucketNode* newNode = malloc(sizeof(BucketNode));
    newNode->vertex = vertex;
    newNode->next = bucket->head;
    bucket->head = newNode;
}

int bucket_pop(Bucket* bucket) {
    if (!bucket->head) return -1;
    BucketNode* tmp = bucket->head;
    int vertex = tmp->vertex;
    bucket->head = tmp->next;
    free(tmp);
    return vertex;
}

int is_bucket_empty(Bucket* bucket) {
    return bucket->head == NULL;
}

void dial(MatGraph* g, int src, int dist[], int pred[]) {
    /*
        Variant of Dijkstra's algorithm for small integer weights.
        O(WV + E)
    */
    int maxDistance = MAX_WEIGHT * g->numVertices;
    Bucket buckets[maxDistance + 1];

    for (int i = 0; i <= maxDistance; i++) buckets[i].head = NULL;

    init_single_source(dist, pred, g->numVertices, src);
    bucket_add(&buckets[0], src);

    for (int i = 0; i <= maxDistance; i++) {
        while (!is_bucket_empty(&buckets[i])) {
            int u = bucket_pop(&buckets[i]);
            for (int v = 0; v < g->numVertices; v++) {
                if (g->adjMat[u][v] != INF) {
                    int oldDist = dist[v];
                    relax(u, v, g->adjMat[u][v], dist, pred);
                    if (dist[v] < oldDist) bucket_add(&buckets[dist[v]], v);
                }
            }
        }
    }
}

#pragma endregion 22.3-9

#pragma region 22.3-10

typedef struct BinaryHeapNode {
    int vertex;
    int distance;
} BinaryHeapNode;

typedef struct BinaryHeap {
    BinaryHeapNode* nodes;
    int size;
    int capacity;
} BinaryHeap;

BinaryHeap* binary_heap_create(int capacity) {
    BinaryHeap* heap = malloc(sizeof(BinaryHeap));
    heap->nodes = malloc(sizeof(BinaryHeapNode) * capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void binary_heap_free(BinaryHeap* heap) {
    free(heap->nodes);
    free(heap);
}

void binary_heap_push(BinaryHeap* heap, int vertex, int distance) {
    int i = heap->size++;
    while (i > 0 && heap->nodes[(i - 1) / 2].distance > distance) {
        heap->nodes[i] = heap->nodes[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap->nodes[i].vertex = vertex;
    heap->nodes[i].distance = distance;
}

BinaryHeapNode binary_heap_pop(BinaryHeap* heap) {
    BinaryHeapNode minNode = heap->nodes[0];
    BinaryHeapNode lastNode = heap->nodes[--heap->size];

    int i = 0, child;
    while ((child = 2 * i + 1) < heap->size) {
        if (child + 1 < heap->size &&
            heap->nodes[child + 1].distance < heap->nodes[child].distance) 
            child++;
        if (lastNode.distance <= heap->nodes[child].distance) break;
        heap->nodes[i] = heap->nodes[child];
        i = child;
    } 
    heap->nodes[i] = lastNode;
    return minNode;
}

int is_binary_heap_empty(BinaryHeap* heap) {
    return heap->size == 0;
}

void heap_dial(MatGraph* g, int src, int dist[], int pred[]) {
    int maxDist = MAX_WEIGHT * g->numVertices;
    BinaryHeap* heap = binary_heap_create(maxDist + 1);

    init_single_source(dist, pred, g->numVertices, src);
    binary_heap_push(heap, src, 0);

    while (!is_binary_heap_empty(heap)) {
        BinaryHeapNode node = binary_heap_pop(heap);
        int u = node.vertex;
        for (int v = 0; v < g->numVertices; v++) {
            if (g->adjMat[u][v] != INF) {
                int oldDist = dist[v];
                relax(u, v, g->adjMat[u][v], dist, pred);
                if (dist[v] < oldDist) binary_heap_push(heap, v, dist[v]);
            }
        }
    }

    binary_heap_free(heap);
}

#pragma endregion 22.3-10

#pragma region 22.3-12

void bucket_dijkstra(MatGraph* g, int src, int dist[], int pred[], int C) {
    int numBuckets = g->numVertices + 1;
    Bucket buckets[numBuckets];
    for (int i = 0; i < numBuckets; i++) buckets[i].head = NULL;

    init_single_source(dist, pred, g->numVertices, src);
    bucket_add(&buckets[0], src);

    for (int i = 0; i < numBuckets; i++) {
        while (!is_bucket_empty(&buckets[i])) {
            int u = bucket_pop(&buckets[i]);
            for (int v = 0; v < g->numVertices; v++) {
                if (g->adjMat[u][v] != INF) {
                    int oldDist = dist[v];
                    relax(u, v, g->adjMat[u][v], dist, pred);
                    if (dist[v] < oldDist) {
                        int bucketIdx = dist[v] / C;
                        bucket_add(&buckets[bucketIdx], v);
                    }
                }
            }
        }
    }
}

#pragma endregion 22.3-12

int main(void) {
    switch (TASK)
    {
        case 1: {
            // Basic Dijkstra's
            int numVertices = 6;
            MatGraph* g = mat_graph_create(numVertices);

            mat_graph_add_directed_edge(g, 0, 1, 4);
            mat_graph_add_directed_edge(g, 0, 2, 1);
            mat_graph_add_directed_edge(g, 2, 1, 2);
            mat_graph_add_directed_edge(g, 1, 3, 1);
            mat_graph_add_directed_edge(g, 2, 3, 5);
            mat_graph_add_directed_edge(g, 3, 4, 3);
            mat_graph_add_directed_edge(g, 4, 5, 2);

            int dist[MAX_VERTICES];
            int pred[MAX_VERTICES];
            int src = 0;

            dijkstra(g, src, dist, pred);
            print_solution(dist, pred, numVertices, src);

            mat_graph_free(g);
            break;
        }

        case 2: {
            // 22.3-4 and 22.3-5
            int numVertices = 6;
            MatGraph* g = mat_graph_create(numVertices);

            mat_graph_add_directed_edge(g, 0, 1, 4);
            mat_graph_add_directed_edge(g, 0, 2, 1);
            mat_graph_add_directed_edge(g, 2, 1, 2);
            mat_graph_add_directed_edge(g, 1, 3, 1);
            mat_graph_add_directed_edge(g, 2, 3, 5);
            mat_graph_add_directed_edge(g, 3, 4, 3);
            mat_graph_add_directed_edge(g, 4, 5, 2);

            int dist[MAX_VERTICES];
            int pred[MAX_VERTICES];
            int src = 0;

            pq_dijkstra(g, src, dist, pred);
            print_solution(dist, pred, numVertices, src);

            if (verify_dijkstra_output(g, dist, pred, src)) 
                printf("The output is valid");
            else printf("The output is invalid");

            mat_graph_free(g);
            break;
        }

        case 3: {
            // 22.3-7
            int numVertices = 6;
            MatGraph* g = mat_graph_create(numVertices);

            mat_graph_add_directed_reliability_edge(g, 0, 1, 0.4);
            mat_graph_add_directed_reliability_edge(g, 0, 2, 0.1);
            mat_graph_add_directed_reliability_edge(g, 2, 1, 0.2);
            mat_graph_add_directed_reliability_edge(g, 1, 3, 0.1);
            mat_graph_add_directed_reliability_edge(g, 2, 3, 0.5);
            mat_graph_add_directed_reliability_edge(g, 3, 4, 0.3);
            mat_graph_add_directed_reliability_edge(g, 4, 5, 0.2);

            int dist[MAX_VERTICES];
            int pred[MAX_VERTICES];
            int src = 0;

            pq_dijkstra(g, src, dist, pred);
            print_solution(dist, pred, numVertices, src);

            if (verify_dijkstra_output(g, dist, pred, src)) 
                printf("The output is valid");
            else printf("The output is invalid");

            mat_graph_free(g);
            break;
        }

        case 4: {
            // 22.3-9
            int numVertices = 6;
            MatGraph* g = mat_graph_create(numVertices);

            mat_graph_add_directed_reliability_edge(g, 0, 1, 0.4);
            mat_graph_add_directed_reliability_edge(g, 0, 2, 0.1);
            mat_graph_add_directed_reliability_edge(g, 2, 1, 0.2);
            mat_graph_add_directed_reliability_edge(g, 1, 3, 0.1);
            mat_graph_add_directed_reliability_edge(g, 2, 3, 0.5);
            mat_graph_add_directed_reliability_edge(g, 3, 4, 0.3);
            mat_graph_add_directed_reliability_edge(g, 4, 5, 0.2);

            int dist[MAX_VERTICES];
            int pred[MAX_VERTICES];
            int src = 0;

            dial(g, src, dist, pred);
            print_solution(dist, pred, numVertices, src);

            if (verify_dijkstra_output(g, dist, pred, src)) 
                printf("The output is valid");
            else printf("The output is invalid");

            break;
        }

        case 5: {
            // 22.3.10
            int numVertices = 6;
            MatGraph* g = mat_graph_create(numVertices);

            mat_graph_add_directed_reliability_edge(g, 0, 1, 0.4);
            mat_graph_add_directed_reliability_edge(g, 0, 2, 0.1);
            mat_graph_add_directed_reliability_edge(g, 2, 1, 0.2);
            mat_graph_add_directed_reliability_edge(g, 1, 3, 0.1);
            mat_graph_add_directed_reliability_edge(g, 2, 3, 0.5);
            mat_graph_add_directed_reliability_edge(g, 3, 4, 0.3);
            mat_graph_add_directed_reliability_edge(g, 4, 5, 0.2);

            int dist[MAX_VERTICES];
            int pred[MAX_VERTICES];
            int src = 0;

            heap_dial(g, src, dist, pred);
            print_solution(dist, pred, numVertices, src);

            if (verify_dijkstra_output(g, dist, pred, src)) 
                printf("The output is valid");
            else printf("The output is invalid");

            break;
        }

        case 6: {
            // 22.3.12
            int numVertices = 6;
            MatGraph* g = mat_graph_create(numVertices);

            mat_graph_add_directed_reliability_edge(g, 0, 1, 0.4);
            mat_graph_add_directed_reliability_edge(g, 0, 2, 0.1);
            mat_graph_add_directed_reliability_edge(g, 2, 1, 0.2);
            mat_graph_add_directed_reliability_edge(g, 1, 3, 0.1);
            mat_graph_add_directed_reliability_edge(g, 2, 3, 0.5);
            mat_graph_add_directed_reliability_edge(g, 3, 4, 0.3);
            mat_graph_add_directed_reliability_edge(g, 4, 5, 0.2);

            int dist[MAX_VERTICES];
            int pred[MAX_VERTICES];
            int src = 0;
            int C = 2;

            bucket_dijkstra(g, src, dist, pred, C);
            print_solution(dist, pred, numVertices, src);

            if (verify_dijkstra_output(g, dist, pred, src)) 
                printf("The output is valid");
            else printf("The output is invalid");

            break;
        }
        
        default:
            break;
    }
    return 0;
}