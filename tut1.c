#include <stdio.h>

void fibonacciWithoutRecursion(int n) {
    int a = 0, b = 1, next;
    printf("Fibonacci series without recursion: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", a);
        next = a + b;
        a = b;
        b = next;
    }
    printf("\n");
}

int fibonacciWithRecursion(int n) {
    if (n <= 1)
        return n;
    return fibonacciWithRecursion(n - 1) + fibonacciWithRecursion(n - 2);
}

void displayFibonacciWithRecursion(int n) {
    printf("Fibonacci series with recursion: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", fibonacciWithRecursion(i));
    }
    printf("\n");
}

int main() {
    int choice, n;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Print Fibonacci series without recursion\n");
        printf("2. Print Fibonacci series with recursion\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 3) {
            printf("Exiting program.\n");
            break;
        }

        printf("Enter the number of terms: ");
        scanf("%d", &n);

        switch (choice) {
            case 1:
                fibonacciWithoutRecursion(n);
                break;
            case 2:
                displayFibonacciWithRecursion(n);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
