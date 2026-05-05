#include <stdio.h>
#include <limits.h>

#define MAX 1000

// Edge structure
struct Edge {
    int u, v, w;
};

int main() {
    int n, m;

    scanf("%d", &n);  // vertices
    scanf("%d", &m);  // edges

    struct Edge edges[MAX];

    // Input edges
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    int src;
    scanf("%d", &src);

    int dist[MAX];

    // Initialize distances
    for (int i = 0; i < n; i++)
        dist[i] = INT_MAX;

    dist[src] = 0;

    // Relax edges (n-1 times)
    for (int i = 1; i <= n - 1; i++) {
        for (int j = 0; j < m; j++) {
            int u = edges[j].u;
            int v = edges[j].v;
            int w = edges[j].w;

            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    // Check for negative cycle
    int hasCycle = 0;
    for (int j = 0; j < m; j++) {
        int u = edges[j].u;
        int v = edges[j].v;
        int w = edges[j].w;

        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            hasCycle = 1;
            break;
        }
    }

    if (hasCycle) {
        printf("Negative weight cycle detected\n");
    } else {
        printf("Vertex\tDistance from Source\n");
        for (int i = 0; i < n; i++) {
            printf("%d\t%d\n", i, dist[i]);
        }
    }

    return 0;
}