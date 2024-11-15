#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define a structure for the tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Recursive Inorder Traversal
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Recursive Preorder Traversal
void preorder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// Recursive Postorder Traversal
void postorder(struct Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

// Function to count nodes in the tree
int countNodes(struct Node* root) {
    if (root == NULL)
        return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Function to create a mirror image of the tree
void mirror(struct Node* root) {
    if (root == NULL) return;

    struct Node* temp = root->left;
    root->left = root->right;
    root->right = temp;

    mirror(root->left);
    mirror(root->right);
}

// Non-Recursive Inorder Traversal
void nonRecursiveInorder(struct Node* root) {
    struct Node* stack[100];
    int top = -1;
    struct Node* current = root;

    while (current != NULL || top >= 0) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }
        current = stack[top--];
        printf("%d ", current->data);
        current = current->right;
    }
}

// Non-Recursive Preorder Traversal
void nonRecursivePreorder(struct Node* root) {
    struct Node* stack[100];
    int top = -1;
    stack[++top] = root;

    while (top >= 0) {
        struct Node* current = stack[top--];
        printf("%d ", current->data);

        if (current->right) stack[++top] = current->right;
        if (current->left) stack[++top] = current->left;
    }
}

// Non-Recursive Postorder Traversal
void nonRecursivePostorder(struct Node* root) {
    struct Node* stack1[100], *stack2[100];
    int top1 = -1, top2 = -1;

    stack1[++top1] = root;
    while (top1 >= 0) {
        struct Node* node = stack1[top1--];
        stack2[++top2] = node;

        if (node->left) stack1[++top1] = node->left;
        if (node->right) stack1[++top1] = node->right;
    }

    while (top2 >= 0) {
        printf("%d ", stack2[top2--]->data);
    }
}

// Main function to drive the menu
int main() {
    struct Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);

    int choice;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Inorder Traversal (Recursive)\n");
        printf("2. Preorder Traversal (Recursive)\n");
        printf("3. Postorder Traversal (Recursive)\n");
        printf("4. Count Nodes\n");
        printf("5. Mirror Tree\n");
        printf("6. Inorder Traversal (Non-Recursive)\n");
        printf("7. Preorder Traversal (Non-Recursive)\n");
        printf("8. Postorder Traversal (Non-Recursive)\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Inorder Traversal: ");
                inorder(root);
                printf("\n");
                break;
            case 2:
                printf("Preorder Traversal: ");
                preorder(root);
                printf("\n");
                break;
            case 3:
                printf("Postorder Traversal: ");
                postorder(root);
                printf("\n");
                break;
            case 4:
                printf("Total Nodes: %d\n", countNodes(root));
                break;
            case 5:
                mirror(root);
                printf("Tree mirrored.\n");
                break;
            case 6:
                printf("Inorder Traversal (Non-Recursive): ");
                nonRecursiveInorder(root);
                printf("\n");
                break;
            case 7:
                printf("Preorder Traversal (Non-Recursive): ");
                nonRecursivePreorder(root);
                printf("\n");
                break;
            case 8:
                printf("Postorder Traversal (Non-Recursive): ");
                nonRecursivePostorder(root);
                printf("\n");
                break;
            case 9:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}