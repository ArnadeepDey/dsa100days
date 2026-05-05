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

// Stack
struct Stack {
    int items[1000];
    int top;
};

void initStack(struct Stack* s) {
    s->top = -1;
}

void push(struct Stack* s, int value) {
    s->items[++s->top] = value;
}

int pop(struct Stack* s) {
    return s->items[s->top--];
}

int isEmpty(struct Stack* s) {
    return s->top == -1;
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

// DFS for topo sort
void topoDFS(struct Graph* graph, int v, int visited[], struct Stack* s) {
    visited[v] = 1;

    struct Node* temp = graph->adjLists[v];

    while (temp) {
        int adj = temp->vertex;
        if (!visited[adj])
            topoDFS(graph, adj, visited, s);
        temp = temp->next;
    }

    // push after visiting all neighbors
    push(s, v);
}

// Topological sort function
void topologicalSort(struct Graph* graph) {
    int visited[1000] = {0};
    struct Stack s;
    initStack(&s);

    for (int i = 0; i < graph->numVertices; i++) {
        if (!visited[i])
            topoDFS(graph, i, visited, &s);
    }

    printf("Topological Order: ");
    while (!isEmpty(&s)) {
        printf("%d ", pop(&s));
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