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

// Find index in inorder array
int search(int inorder[], int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (inorder[i] == value)
            return i;
    }
    return -1;
}

// Build tree function
struct Node* buildTree(int preorder[], int inorder[], int start, int end, int* preIndex) {
    if (start > end)
        return NULL;

    // Pick current root from preorder
    int curr = preorder[*preIndex];
    (*preIndex)++;

    struct Node* node = createNode(curr);

    // If leaf node
    if (start == end)
        return node;

    // Find index in inorder
    int pos = search(inorder, start, end, curr);

    // Build left and right subtrees
    node->left = buildTree(preorder, inorder, start, pos - 1, preIndex);
    node->right = buildTree(preorder, inorder, pos + 1, end, preIndex);

    return node;
}

// Inorder print (to verify)
void printInorder(struct Node* root) {
    if (root == NULL)
        return;

    printInorder(root->left);
    printf("%d ", root->data);
    printInorder(root->right);
}

int main() {
    int n;
    scanf("%d", &n);

    int preorder[n], inorder[n];

    for (int i = 0; i < n; i++)
        scanf("%d", &preorder[i]);

    for (int i = 0; i < n; i++)
        scanf("%d", &inorder[i]);

    int preIndex = 0;

    struct Node* root = buildTree(preorder, inorder, 0, n - 1, &preIndex);

    // Print inorder to verify
    printInorder(root);

    return 0;
}