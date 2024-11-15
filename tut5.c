#include <stdio.h>
#include <limits.h>

#define MAX 100
#define INF INT_MAX

int graph[MAX][MAX];
int vertices;

// Function to find the vertex with the minimum distance
int minDistance(int dist[], int sptSet[]) {
    int min = INF, min_index;

    for (int v = 0; v < vertices; v++)
        if (sptSet[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }

    return min_index;
}

// Dijkstra's algorithm to find shortest path from a source
void dijkstra(int src) {
    int dist[vertices]; // Holds the shortest distance from source to each vertex
    int sptSet[vertices]; // True if vertex is in shortest path tree

    // Initialize all distances as INF and sptSet as false
    for (int i = 0; i < vertices; i++) {
        dist[i] = INF;
        sptSet[i] = 0;
    }

    dist[src] = 0;

    for (int count = 0; count < vertices - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = 1;

        for (int v = 0; v < vertices; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INF
                && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
    }

    printf("Vertex\tDistance from Source %d\n", src);
    for (int i = 0; i < vertices; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

// Function to take input for graph
void createGraph() {
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    printf("Enter the adjacency matrix (use %d for infinity):\n", INF);
    for (int i = 0; i < vertices; i++)
        for (int j = 0; j < vertices; j++) {
            scanf("%d", &graph[i][j]);
            if (graph[i][j] == INF)
                graph[i][j] = 0; // Treat INF as no edge between i and j
        }

    printf("Graph created successfully.\n");
}

// Menu function
int main() {
    int choice, src;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Create Graph\n");
        printf("2. Find Shortest Path using Dijkstra's Algorithm\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createGraph();
                break;
            case 2:
                printf("Enter the source vertex: ");
                scanf("%d", &src);
                if (src >= 0 && src < vertices) {
                    dijkstra(src);
                } else {
                    printf("Invalid source vertex.\n");
                }
                break;
            case 3:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
