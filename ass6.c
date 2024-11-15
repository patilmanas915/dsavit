#include <stdio.h>
#include <stdbool.h>

#define SIZE 5          // Define graph size for a 5x5 adjacency matrix
#define HASH_SIZE 11    // Define hash table size for mod 11 hashing

// Adjacency matrix representation of the graph
int graph[SIZE][SIZE] = {
    {0, 1, 1, 0, 0},
    {1, 0, 1, 1, 0},
    {1, 1, 0, 0, 1},
    {0, 1, 0, 0, 1},
    {0, 0, 1, 1, 0}
};

// Visited array for DFS and BFS
bool visited[SIZE];

// Queue structure for BFS
typedef struct {
    int items[SIZE];
    int front, rear;
} Queue;

void initQueue(Queue *q) { q->front = -1; q->rear = -1; }
bool isEmptyQueue(Queue *q) { return q->rear == -1; }
void enqueue(Queue *q, int value) {
    if (q->rear == SIZE - 1) return; // Queue overflow check
    if (isEmptyQueue(q)) q->front = 0;
    q->items[++q->rear] = value;
}
int dequeue(Queue *q) {
    if (isEmptyQueue(q)) return -1;
    int item = q->items[q->front];
    if (q->front >= q->rear) q->front = q->rear = -1;
    else q->front++;
    return item;
}

// BFS traversal
void bfs(int start) {
    Queue q;
    initQueue(&q);
    for (int i = 0; i < SIZE; i++) visited[i] = false;

    enqueue(&q, start);
    visited[start] = true;

    printf("BFS Traversal: ");
    while (!isEmptyQueue(&q)) {
        int vertex = dequeue(&q);
        printf("%d ", vertex);
        for (int i = 0; i < SIZE; i++) {
            if (graph[vertex][i] && !visited[i]) {
                enqueue(&q, i);
                visited[i] = true;
            }
        }
    }
    printf("\n");
}

// DFS traversal
void dfs(int vertex) {
    visited[vertex] = true;
    printf("%d ", vertex);
    for (int i = 0; i < SIZE; i++) {
        if (graph[vertex][i] && !visited[i]) {
            dfs(i);
        }
    }
}

// Hash table with linear probing
int hashTable[HASH_SIZE];

void initHashTable() {
    for (int i = 0; i < HASH_SIZE; i++) hashTable[i] = -1;  // -1 indicates empty slot
}

int hash(int key) {
    return key % HASH_SIZE;
}

void insert(int key) {
    int index = hash(key);
    int start = index;
    while (hashTable[index] != -1) {
        index = (index + 1) % HASH_SIZE;
        if (index == start) {  // Table is full
            printf("Hash table is full\n");
            return;
        }
    }
    hashTable[index] = key;
}

void displayHashTable() {
    printf("Hash Table:\n");
    for (int i = 0; i < HASH_SIZE; i++) {
        printf("[%d] -> %d\n", i, hashTable[i]);
    }
}

// Main function with menu
int main() {
    int choice, startVertex, key;

    do {
        printf("\nMenu\n");
        printf("1. Graph Traversal - BFS\n");
        printf("2. Graph Traversal - DFS\n");
        printf("3. Hashing with Linear Probing (Insert)\n");
        printf("4. Display Hash Table\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter starting vertex for BFS (0-%d): ", SIZE - 1);
                scanf("%d", &startVertex);
                bfs(startVertex);
                break;
            case 2:
                printf("Enter starting vertex for DFS (0-%d): ", SIZE - 1);
                scanf("%d", &startVertex);
                for (int i = 0; i < SIZE; i++) visited[i] = false;
                printf("DFS Traversal: ");
                dfs(startVertex);
                printf("\n");
                break;
            case 3:
                printf("Enter key to insert into hash table: ");
                scanf("%d", &key);
                insert(key);
                break;
            case 4:
                displayHashTable();
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}
