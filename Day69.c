#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 1000

// Node for adjacency list
struct Node {
    int vertex, weight;
    struct Node* next;
};

// Graph
struct Graph {
    int numVertices;
    struct Node** adjLists;
};

// Min Heap Node
struct MinHeapNode {
    int vertex, dist;
};

// Min Heap
struct MinHeap {
    int size;
    struct MinHeapNode heap[MAX];
};

// Create graph
struct Graph* createGraph(int n) {
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = n;
    graph->adjLists = malloc(n * sizeof(struct Node*));

    for (int i = 0; i < n; i++)
        graph->adjLists[i] = NULL;

    return graph;
}

// Create adjacency node
struct Node* createNode(int v, int w) {
    struct Node* node = malloc(sizeof(struct Node));
    node->vertex = v;
    node->weight = w;
    node->next = NULL;
    return node;
}

// Add edge (directed)
void addEdge(struct Graph* graph, int u, int v, int w) {
    struct Node* node = createNode(v, w);
    node->next = graph->adjLists[u];
    graph->adjLists[u] = node;
}

// Swap heap nodes
void swap(struct MinHeapNode* a, struct MinHeapNode* b) {
    struct MinHeapNode temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify
void heapify(struct MinHeap* h, int i) {
    int smallest = i;
    int l = 2*i + 1, r = 2*i + 2;

    if (l < h->size && h->heap[l].dist < h->heap[smallest].dist)
        smallest = l;

    if (r < h->size && h->heap[r].dist < h->heap[smallest].dist)
        smallest = r;

    if (smallest != i) {
        swap(&h->heap[i], &h->heap[smallest]);
        heapify(h, smallest);
    }
}

// Extract min
struct MinHeapNode extractMin(struct MinHeap* h) {
    struct MinHeapNode root = h->heap[0];
    h->heap[0] = h->heap[--h->size];
    heapify(h, 0);
    return root;
}

// Insert into heap
void insertHeap(struct MinHeap* h, int v, int dist) {
    int i = h->size++;
    h->heap[i].vertex = v;
    h->heap[i].dist = dist;

    while (i && h->heap[(i-1)/2].dist > h->heap[i].dist) {
        swap(&h->heap[i], &h->heap[(i-1)/2]);
        i = (i-1)/2;
    }
}

// Dijkstra
void dijkstra(struct Graph* graph, int src) {
    int dist[MAX];
    for (int i = 0; i < graph->numVertices; i++)
        dist[i] = INT_MAX;

    struct MinHeap heap;
    heap.size = 0;

    dist[src] = 0;
    insertHeap(&heap, src, 0);

    while (heap.size > 0) {
        struct MinHeapNode minNode = extractMin(&heap);
        int u = minNode.vertex;

        struct Node* temp = graph->adjLists[u];

        while (temp) {
            int v = temp->vertex;
            int weight = temp->weight;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                insertHeap(&heap, v, dist[v]);
            }
            temp = temp->next;
        }
    }

    // Print distances
    printf("Vertex\tDistance from Source\n");
    for (int i = 0; i < graph->numVertices; i++)
        printf("%d\t%d\n", i, dist[i]);
}

int main() {
    int n, m, u, v, w, src;

    scanf("%d", &n);  // vertices
    scanf("%d", &m);  // edges

    struct Graph* graph = createGraph(n);

    // Input edges: u v weight
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &u, &v, &w);
        addEdge(graph, u, v, w);
    }

    scanf("%d", &src);

    dijkstra(graph, src);

    return 0;
}