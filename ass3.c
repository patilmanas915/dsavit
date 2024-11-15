#include <stdio.h>
#include <stdlib.h>

#define MAX 5

// Circular Queue structure
typedef struct {
    int items[MAX];
    int front, rear;
} CircularQueue;

// Initialize the circular queue
void initQueue(CircularQueue *q) {
    q->front = q->rear = -1;
}

// Check if the queue is full
int isFull(CircularQueue *q) {
    return (q->rear + 1) % MAX == q->front;
}

// Check if the queue is empty
int isEmpty(CircularQueue *q) {
    return q->front == -1;
}

// Enqueue an element
void enqueue(CircularQueue *q, int value) {
    if (isFull(q)) {
        printf("Queue is full\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % MAX;
    }
    q->items[q->rear] = value;
    printf("%d enqueued to queue\n", value);
}

// Dequeue an element
int dequeue(CircularQueue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    int value = q->items[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX;
    }
    return value;
}

// Display the circular queue
void displayQueue(CircularQueue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue: ");
    int i = q->front;
    do {
        printf("%d ", q->items[i]);
        i = (i + 1) % MAX;
    } while (i != (q->rear + 1) % MAX);
    printf("\n");
}

// Stack structure
typedef struct {
    int items[MAX];
    int top;
} Stack;

// Initialize the stack
void initStack(Stack *s) {
    s->top = -1;
}

// Check if the stack is empty
int isStackEmpty(Stack *s) {
    return s->top == -1;
}

// Push an element onto the stack
void push(Stack *s, int value) {
    if (s->top == MAX - 1) {
        printf("Stack is full\n");
        return;
    }
    s->items[++s->top] = value;
}

// Pop an element from the stack
int pop(Stack *s) {
    if (isStackEmpty(s)) {
        printf("Stack is empty\n");
        return -1;
    }
    return s->items[s->top--];
}

// Reverse a stack using a queue
void reverseStackUsingQueue(Stack *s) {
    CircularQueue q;
    initQueue(&q);

    // Transfer elements from stack to queue
    while (!isStackEmpty(s)) {
        enqueue(&q, pop(s));
    }

    // Transfer elements back from queue to stack
    while (!isEmpty(&q)) {
        push(s, dequeue(&q));
    }
}

// Main function with menu
int main() {
    int choice, value;
    CircularQueue q;
    Stack s;
    initQueue(&q);
    initStack(&s);

    do {
        printf("\nMenu\n");
        printf("1. Enqueue to Circular Queue\n");
        printf("2. Dequeue from Circular Queue\n");
        printf("3. Display Circular Queue\n");
        printf("4. Reverse Stack using Queue\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                enqueue(&q, value);
                break;
            case 2:
                value = dequeue(&q);
                if (value != -1) {
                    printf("%d dequeued from queue\n", value);
                }
                break;
            case 3:
                displayQueue(&q);
                break;
            case 4:
                printf("Enter elements to push to stack (enter -1 to stop):\n");
                while (1) {
                    scanf("%d", &value);
                    if (value == -1) break;
                    push(&s, value);
                }
                reverseStackUsingQueue(&s);
                printf("Stack reversed using queue. Popped elements: ");
                while (!isStackEmpty(&s)) {
                    printf("%d ", pop(&s));
                }
                printf("\n");
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 5);

    return 0;
}
