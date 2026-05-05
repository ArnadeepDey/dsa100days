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

// Search in inorder
int search(int inorder[], int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (inorder[i] == value)
            return i;
    }
    return -1;
}

// Build tree
struct Node* buildTree(int inorder[], int postorder[], int start, int end, int* postIndex) {
    if (start > end)
        return NULL;

    // Pick current root from postorder
    int curr = postorder[*postIndex];
    (*postIndex)--;

    struct Node* node = createNode(curr);

    // If leaf node
    if (start == end)
        return node;

    // Find index in inorder
    int pos = search(inorder, start, end, curr);

    // Build right first, then left
    node->right = buildTree(inorder, postorder, pos + 1, end, postIndex);
    node->left = buildTree(inorder, postorder, start, pos - 1, postIndex);

    return node;
}

// Preorder print (to verify)
void printPreorder(struct Node* root) {
    if (root == NULL)
        return;

    printf("%d ", root->data);
    printPreorder(root->left);
    printPreorder(root->right);
}

int main() {
    int n;
    scanf("%d", &n);

    int inorder[n], postorder[n];

    for (int i = 0; i < n; i++)
        scanf("%d", &inorder[i]);

    for (int i = 0; i < n; i++)
        scanf("%d", &postorder[i]);

    int postIndex = n - 1;

    struct Node* root = buildTree(inorder, postorder, 0, n - 1, &postIndex);

    // Print preorder to verify
    printPreorder(root);

    return 0;
}