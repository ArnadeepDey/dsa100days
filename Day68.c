#include <stdio.h>
#include <stdlib.h>

// Node for adjacency list
struct Node {
    int vertex;
    struct Node* next;
};

// Graph structure
struct Graph {
    int numVertices;
    struct Node** adjLists;
};

// Queue
struct Queue {
    int items[1000];
    int front, rear;
};

void initQueue(struct Queue* q) {
    q->front = q->rear = 0;
}

int isEmpty(struct Queue* q) {
    return q->front == q->rear;
}

void enqueue(struct Queue* q, int value) {
    q->items[q->rear++] = value;
}

int dequeue(struct Queue* q) {
    return q->items[q->front++];
}

// Create node
struct Node* createNode(int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Create graph
struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    graph->adjLists = (struct Node**)malloc(vertices * sizeof(struct Node*));

    for (int i = 0; i < vertices; i++)
        graph->adjLists[i] = NULL;

    return graph;
}

// Add directed edge
void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
}

// Kahn's Algorithm
void topologicalSort(struct Graph* graph) {
    int indegree[1000] = {0};

    // Calculate in-degree
    for (int i = 0; i < graph->numVertices; i++) {
        struct Node* temp = graph->adjLists[i];
        while (temp) {
            indegree[temp->vertex]++;
            temp = temp->next;
        }
    }

    struct Queue q;
    initQueue(&q);

    // Enqueue vertices with indegree 0
    for (int i = 0; i < graph->numVertices; i++) {
        if (indegree[i] == 0)
            enqueue(&q, i);
    }

    int count = 0;

    printf("Topological Order: ");

    while (!isEmpty(&q)) {
        int u = dequeue(&q);
        printf("%d ", u);
        count++;

        struct Node* temp = graph->adjLists[u];

        while (temp) {
            indegree[temp->vertex]--;

            if (indegree[temp->vertex] == 0)
                enqueue(&q, temp->vertex);

            temp = temp->next;
        }
    }

    // Check for cycle
    if (count != graph->numVertices) {
        printf("\nCycle detected! Topological sort not possible.\n");
    }
}

int main() {
    int n, m, u, v;

    scanf("%d", &n);  // vertices
    scanf("%d", &m);  // edges

    struct Graph* graph = createGraph(n);

    // Input edges (directed)
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        addEdge(graph, u, v);
    }

    topologicalSort(graph);

    return 0;
}