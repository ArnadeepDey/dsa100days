#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m, i, u, v, type;

    // Input number of vertices and edges
    scanf("%d", &n);
    scanf("%d", &m);

    // 0 = undirected, 1 = directed
    printf("Enter 0 for Undirected, 1 for Directed: ");
    scanf("%d", &type);

    // Allocate adjacency matrix
    int adj[n][n];

    // Initialize matrix with 0
    for (i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adj[i][j] = 0;

    // Input edges
    for (i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);

        adj[u][v] = 1;

        if (type == 0)  // undirected
            adj[v][u] = 1;
    }

    // Print adjacency matrix
    printf("Adjacency Matrix:\n");
    for (i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", adj[i][j]);
        }
        printf("\n");
    }

    return 0;
}