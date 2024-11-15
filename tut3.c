#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the doubly linked list
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of the doubly linked list
void insertNode(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }
    printf("Node with data %d inserted successfully.\n", data);
}

// Function to find and print nodes with even data values
void findEvenNodes(struct Node* head) {
    struct Node* temp = head;
    printf("Nodes with even values: ");
    int found = 0;

    while (temp != NULL) {
        if (temp->data % 2 == 0) {
            printf("%d ", temp->data);
            found = 1;
        }
        temp = temp->next;
    }

    if (!found) {
        printf("No nodes with even values found.");
    }
    printf("\n");
}

// Function to display the menu and handle user choices
int main() {
    struct Node* head = NULL;
    int choice, data;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert node\n");
        printf("2. Find nodes with even values\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                insertNode(&head, data);
                break;
            case 2:
                findEvenNodes(head);
                break;
            case 3:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
