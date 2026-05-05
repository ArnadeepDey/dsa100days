#include <stdio.h>
#include <limits.h>

#define MAX 100

int minKey(int key[], int visited[], int n) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < n; v++) {
        if (visited[v] == 0 && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int graph[MAX][MAX];

    // Initialize graph with 0
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;

    // Input edges
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = w;
        graph[v][u] = w; // undirected graph
    }

    int key[n];       
    int visited[n];   

    // Initialize all keys as infinite and visited as false
    for (int i = 0; i < n; i++) {
        key[i] = INT_MAX;
        visited[i] = 0;
    }

    key[0] = 0;  // Start from vertex 0

    int totalWeight = 0;

    for (int count = 0; count < n; count++) {
        int u = minKey(key, visited, n);
        visited[u] = 1;

        totalWeight += key[u];

        // Update adjacent vertices
        for (int v = 0; v < n; v++) {
            if (graph[u][v] && visited[v] == 0 && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
            }
        }
    }

    printf("%d\n", totalWeight);

    return 0;
}