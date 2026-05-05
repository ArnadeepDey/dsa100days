#include <stdbool.h>
#include <stdlib.h>

/**
 * A graph is bipartite if it can be colored using two colors such that
 * no two adjacent nodes have the same color.
 * We can use BFS or DFS to traverse the graph and assign colors (0 and 1).
 */

bool isBipartite(int** graph, int graphSize, int* graphColSize) {
    int* colors = (int*)malloc(graphSize * sizeof(int));
    for (int i = 0; i < graphSize; i++) {
        colors[i] = -1; // -1 means uncolored
    }

    int* queue = (int*)malloc(graphSize * sizeof(int));

    for (int i = 0; i < graphSize; i++) {
        if (colors[i] == -1) {
            int front = 0, rear = 0;
            colors[i] = 0;
            queue[rear++] = i;

            while (front < rear) {
                int curr = queue[front++];

                for (int j = 0; j < graphColSize[curr]; j++) {
                    int neighbor = graph[curr][j];

                    if (colors[neighbor] == -1) {
                        colors[neighbor] = 1 - colors[curr];
                        queue[rear++] = neighbor;
                    } else if (colors[neighbor] == colors[curr]) {
                        free(colors);
                        free(queue);
                        return false;
                    }
                }
            }
        }
    }

    free(colors);
    free(queue);
    return true;
}