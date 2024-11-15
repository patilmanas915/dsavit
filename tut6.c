#include <stdio.h>
#include <stdlib.h>

#define MAX_TABLE_SIZE 11  // Size of the hash tables
#define MAX_ITERATIONS 5   // Maximum iterations to avoid infinite loops during insertion

int table1[MAX_TABLE_SIZE];
int table2[MAX_TABLE_SIZE];

// Hash functions
int hash1(int key) {
    return key % MAX_TABLE_SIZE;
}

int hash2(int key) {
    return (key / MAX_TABLE_SIZE) % MAX_TABLE_SIZE;
}

// Initialize hash tables
void initialize() {
    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        table1[i] = -1;  // -1 represents an empty slot
        table2[i] = -1;
    }
}

// Insert a key using Cuckoo Hashing
void insert(int key) {
    int pos1, pos2, temp, i = 0;
    while (i < MAX_ITERATIONS) {
        // Insert in table1 if the position is free
        pos1 = hash1(key);
        if (table1[pos1] == -1) {
            table1[pos1] = key;
            printf("Inserted %d into table1 at position %d\n", key, pos1);
            return;
        }
        
        // Kick out the existing key in table1
        temp = table1[pos1];
        table1[pos1] = key;
        printf("Kicked out %d from table1 at position %d, placed %d\n", temp, pos1, key);

        // Insert the displaced key into table2
        key = temp;
        pos2 = hash2(key);
        if (table2[pos2] == -1) {
            table2[pos2] = key;
            printf("Inserted %d into table2 at position %d\n", key, pos2);
            return;
        }

        // Kick out the existing key in table2
        temp = table2[pos2];
        table2[pos2] = key;
        printf("Kicked out %d from table2 at position %d, placed %d\n", temp, pos2, key);
        
        // Continue the cycle with the displaced key
        key = temp;
        i++;
    }
    
    printf("Failed to insert %d after %d iterations. Table needs resizing.\n", key, MAX_ITERATIONS);
}

// Search for a key in the hash tables
void search(int key) {
    int pos1 = hash1(key);
    int pos2 = hash2(key);

    if (table1[pos1] == key) {
        printf("Key %d found in table1 at position %d\n", key, pos1);
    } else if (table2[pos2] == key) {
        printf("Key %d found in table2 at position %d\n", key, pos2);
    } else {
        printf("Key %d not found\n", key);
    }
}

// Display the hash tables
void display() {
    printf("\nTable1:\n");
    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        if (table1[i] != -1)
            printf("Position %d: %d\n", i, table1[i]);
        else
            printf("Position %d: Empty\n", i);
    }

    printf("\nTable2:\n");
    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        if (table2[i] != -1)
            printf("Position %d: %d\n", i, table2[i]);
        else
            printf("Position %d: Empty\n", i);
    }
}

// Menu function
int main() {
    int choice, key;
    initialize();

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                insert(key);
                break;
            case 2:
                printf("Enter key to search: ");
                scanf("%d", &key);
                search(key);
                break;
            case 3:
                display();
                break;
            case 4:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
