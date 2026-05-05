#include <stdio.h>
#include <string.h>

#define MAX 1000
#define LEN 100

int main() {
    int n;
    scanf("%d", &n);

    char votes[MAX][LEN];
    for (int i = 0; i < n; i++) {
        scanf("%s", votes[i]);
    }

    char names[MAX][LEN];
    int count[MAX] = {0};
    int unique = 0;

    // Count votes
    for (int i = 0; i < n; i++) {
        int found = 0;

        for (int j = 0; j < unique; j++) {
            if (strcmp(votes[i], names[j]) == 0) {
                count[j]++;
                found = 1;
                break;
            }
        }

        if (!found) {
            strcpy(names[unique], votes[i]);
            count[unique] = 1;
            unique++;
        }
    }

    // Find winner
    int maxVotes = -1;
    char winner[LEN];

    for (int i = 0; i < unique; i++) {
        if (count[i] > maxVotes) {
            maxVotes = count[i];
            strcpy(winner, names[i]);
        }
        else if (count[i] == maxVotes) {
            if (strcmp(names[i], winner) < 0) {
                strcpy(winner, names[i]);
            }
        }
    }

    printf("%s\n", winner);

    return 0;
}