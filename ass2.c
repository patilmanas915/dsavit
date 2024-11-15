#include <stdio.h>
#include <ctype.h>

#define MAX 100

typedef struct {
    char items[MAX];
    int top;
} Stack;

// Stack functions
void init(Stack *s) { s->top = -1; }
int isEmpty(Stack *s) { return s->top == -1; }
void push(Stack *s, char c) { if (s->top < MAX - 1) s->items[++s->top] = c; }
char pop(Stack *s) { return isEmpty(s) ? '\0' : s->items[s->top--]; }
char peek(Stack *s) { return isEmpty(s) ? '\0' : s->items[s->top]; }

// Check matching parentheses
int isMatchingParenthesis(const char *exp) {
    Stack s; init(&s);
    for (int i = 0; exp[i]; i++) {
        if (exp[i] == '(' || exp[i] == '{' || exp[i] == '[') push(&s, exp[i]);
        else if (exp[i] == ')' || exp[i] == '}' || exp[i] == ']') {
            if (isEmpty(&s) || (exp[i] == ')' && pop(&s) != '(') ||
                (exp[i] == '}' && pop(&s) != '{') || (exp[i] == ']' && pop(&s) != '['))
                return 0;
        }
    }
    return isEmpty(&s);
}

// Convert infix to postfix
void infixToPostfix(const char *infix, char *postfix) {
    Stack s; init(&s); int j = 0;
    for (int i = 0; infix[i]; i++) {
        if (isalnum(infix[i])) postfix[j++] = infix[i];
        else if (infix[i] == '(') push(&s, infix[i]);
        else if (infix[i] == ')') {
            while (!isEmpty(&s) && peek(&s) != '(') postfix[j++] = pop(&s);
            pop(&s); // Discard the '('
        } else {
            while (!isEmpty(&s) && peek(&s) != '(') postfix[j++] = pop(&s);
            push(&s, infix[i]);
        }
    }
    while (!isEmpty(&s)) postfix[j++] = pop(&s);
    postfix[j] = '\0';
}

// Evaluate postfix expression
int evaluatePostfix(const char *postfix) {
    Stack s; init(&s);
    for (int i = 0; postfix[i]; i++) {
        if (isdigit(postfix[i])) push(&s, postfix[i] - '0');
        else {
            int b = pop(&s), a = pop(&s);
            if (postfix[i] == '+') push(&s, a + b);
            else if (postfix[i] == '-') push(&s, a - b);
            else if (postfix[i] == '*') push(&s, a * b);
            else if (postfix[i] == '/') push(&s, a / b);
        }
    }
    return pop(&s);
}

// Main function with menu
int main() {
    int choice;
    char expression[MAX], postfix[MAX];

    do {
        printf("\nMenu\n1. Check Parentheses\n2. Infix to Postfix\n3. Evaluate Postfix\n4. Exit\nChoose: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter expression: ");
            scanf("%s", expression);
            printf(isMatchingParenthesis(expression) ? "Matching\n" : "Not Matching\n");
        } else if (choice == 2) {
            printf("Enter infix: ");
            scanf("%s", expression);
            infixToPostfix(expression, postfix);
            printf("Postfix: %s\n", postfix);
        } else if (choice == 3) {
            printf("Enter postfix: ");
            scanf("%s", expression);
            printf("Result: %d\n", evaluatePostfix(expression));
        } else if (choice != 4) {
            printf("Invalid choice!\n");
        }
    } while (choice != 4);

    printf("Exiting...\n");
    return 0;
}
