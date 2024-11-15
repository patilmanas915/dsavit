#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Stack structure
typedef struct Stack {
    char* items[MAX];
    int top;
} Stack;

// Function to initialize the stack
void initialize(Stack* s) {
    s->top = -1;
}

// Function to check if the stack is empty
int isEmpty(Stack* s) {
    return s->top == -1;
}

// Function to push an element onto the stack
void push(Stack* s, char* item) {
    if (s->top < MAX - 1) {
        s->items[++(s->top)] = item;
    } else {
        printf("Stack overflow.\n");
    }
}

// Function to pop an element from the stack
char* pop(Stack* s) {
    if (!isEmpty(s)) {
        return s->items[(s->top)--];
    } else {
        printf("Stack underflow.\n");
        return NULL;
    }
}

// Function to check if a character is an operator
int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

// Function to convert postfix to prefix
void postfixToPrefix(char* postfix) {
    Stack s;
    initialize(&s);

    int length = strlen(postfix);

    for (int i = 0; i < length; i++) {
        // If operand, push it to the stack
        if (isalnum(postfix[i])) {
            char* operand = (char*)malloc(2 * sizeof(char));
            operand[0] = postfix[i];
            operand[1] = '\0';
            push(&s, operand);
        }
        // If operator, pop two elements, concatenate them with the operator in prefix form, and push back to the stack
        else if (isOperator(postfix[i])) {
            char* op1 = pop(&s);
            char* op2 = pop(&s);

            char* expr = (char*)malloc(strlen(op1) + strlen(op2) + 2);
            expr[0] = postfix[i];
            expr[1] = '\0';
            strcat(expr, op2);
            strcat(expr, op1);

            push(&s, expr);

            // Free the memory of operands as they are no longer needed
            free(op1);
            free(op2);
        }
    }

    // The result will be the only element left in the stack
    printf("Prefix expression: %s\n", pop(&s));
}

// Main function with a menu
int main() {
    int choice;
    char postfix[MAX];

    while (1) {
        printf("\nMenu:\n");
        printf("1. Convert Postfix to Prefix\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 2) {
            printf("Exiting program.\n");
            break;
        }

        switch (choice) {
            case 1:
                printf("Enter a postfix expression: ");
                scanf("%s", postfix);
                postfixToPrefix(postfix);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
