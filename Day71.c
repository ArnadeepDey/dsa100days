#include <stdio.h>
#include <stdlib.h>

#define EMPTY -1

// Insert using quadratic probing
void insert(int table[], int m, int key) {
    int i = 0;
    int index;

    while (i < m) {
        index = (key % m + i * i) % m;

        if (table[index] == EMPTY) {
            table[index] = key;
            return;
        }
        i++;
    }

    printf("Hash table is full, cannot insert %d\n", key);
}

// Display hash table
void display(int table[], int m) {
    printf("Index\tValue\n");
    for (int i = 0; i < m; i++) {
        if (table[i] == EMPTY)
            printf("%d\t-\n", i);
        else
            printf("%d\t%d\n", i, table[i]);
    }
}

int main() {
    int m, n;

    scanf("%d", &m);  // size of table
    scanf("%d", &n);  // number of keys

    int table[m];

    // Initialize table
    for (int i = 0; i < m; i++)
        table[i] = EMPTY;

    int key;

    // Insert keys
    for (int i = 0; i < n; i++) {
        scanf("%d", &key);
        insert(table, m, key);
    }

    // Display table
    display(table, m);

    return 0;
}