#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Create node
struct Node* createNode(int val) {
    struct Node* n = (struct Node*)malloc(sizeof(struct Node));
    n->data = val;
    n->left = n->right = NULL;
    return n;
}

// Build tree from level order
struct Node* buildTree(int arr[], int n) {
    if (n == 0)
        return NULL;

    struct Node* root = createNode(arr[0]);

    struct Node* queue[1000];
    int front = 0, rear = 0;

    queue[rear++] = root;

    int i = 1;
    while (i < n && front < rear) {
        struct Node* curr = queue[front++];

        // Left child
        if (i < n) {
            curr->left = createNode(arr[i]);
            queue[rear++] = curr->left;
            i++;
        }

        // Right child
        if (i < n) {
            curr->right = createNode(arr[i]);
            queue[rear++] = curr->right;
            i++;
        }
    }

    return root;
}

// Check Min Heap
int isMinHeap(struct Node* root) {
    if (root == NULL)
        return 1;

    struct Node* queue[1000];
    int front = 0, rear = 0;

    queue[rear++] = root;

    int nullSeen = 0;

    while (front < rear) {
        struct Node* curr = queue[front++];

        // Left child
        if (curr->left) {
            if (nullSeen) return 0; // Not complete
            if (curr->data > curr->left->data) return 0; // Heap violation
            queue[rear++] = curr->left;
        } else {
            nullSeen = 1;
        }

        // Right child
        if (curr->right) {
            if (nullSeen) return 0;
            if (curr->data > curr->right->data) return 0;
            queue[rear++] = curr->right;
        } else {
            nullSeen = 1;
        }
    }

    return 1;
}

int main() {
    int n;
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    struct Node* root = buildTree(arr, n);

    if (isMinHeap(root))
        printf("Yes, it is a Min-Heap\n");
    else
        printf("No, it is not a Min-Heap\n");

    return 0;
}