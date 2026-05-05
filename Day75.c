#include <stdio.h>

#define MAX 10000

int main() {
    int n;
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    int prefixSum = 0;
    int maxLen = 0;

    // Simple hash map using arrays
    int sum[MAX];
    int index[MAX];

    int size = 0;

    for (int i = 0; i < n; i++) {
        prefixSum += arr[i];

        // Case 1: sum = 0 from start
        if (prefixSum == 0) {
            maxLen = i + 1;
        }

        // Check if prefixSum seen before
        int found = 0;
        for (int j = 0; j < size; j++) {
            if (sum[j] == prefixSum) {
                int length = i - index[j];
                if (length > maxLen)
                    maxLen = length;
                found = 1;
                break;
            }
        }

        // Store first occurrence
        if (!found) {
            sum[size] = prefixSum;
            index[size] = i;
            size++;
        }
    }

    printf("%d\n", maxLen);

    return 0;
}