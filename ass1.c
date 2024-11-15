#include <stdio.h>

// Function prototypes
void insertionSort(int arr[], int n);
void bubbleSort(int arr[], int n);
void quickSort(int arr[], int low, int high);
void mergeSort(int arr[], int left, int right);
void merge(int arr[], int left, int mid, int right);
int binarySearch(int arr[], int n, int x);
int fibonacciSearch(int arr[], int n, int x);
void printArray(int arr[], int size);
void getArray(int arr[], int n);

int main() {
    int choice, n, x, result;
    int arr[100];

    printf("Enter number of elements: ");
    scanf("%d", &n);
    getArray(arr, n);

    do {
        printf("\nMenu:\n");
        printf("1. Insertion Sort\n2. Bubble Sort\n3. Quick Sort\n4. Merge Sort\n5. Binary Search\n6. Fibonacci Search\n7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                insertionSort(arr, n);
                printf("Array after Insertion Sort: ");
                printArray(arr, n);
                break;
            case 2:
                bubbleSort(arr, n);
                printf("Array after Bubble Sort: ");
                printArray(arr, n);
                break;
            case 3:
                quickSort(arr, 0, n - 1);
                printf("Array after Quick Sort: ");
                printArray(arr, n);
                break;
            case 4:
                mergeSort(arr, 0, n - 1);
                printf("Array after Merge Sort: ");
                printArray(arr, n);
                break;
            case 5:
                printf("Enter element to search (Binary Search): ");
                scanf("%d", &x);
                result = binarySearch(arr, n, x);
                if (result != -1)
                    printf("Element found at index %d\n", result);
                else
                    printf("Element not found\n");
                break;
            case 6:
                printf("Enter element to search (Fibonacci Search): ");
                scanf("%d", &x);
                result = fibonacciSearch(arr, n, x);
                if (result != -1)
                    printf("Element found at index %d\n", result);
                else
                    printf("Element not found\n");
                break;
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice, please try again.\n");
        }
    } while (choice != 7);

    return 0;
}

// Get array from user
void getArray(int arr[], int n) {
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
}

// Print the array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Insertion Sort
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Bubble Sort
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Quick Sort with partition function
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;

        int pi = i + 1;
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Merge Sort
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Merge function to combine sorted halves
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Binary Search
int binarySearch(int arr[], int n, int x) {
    int l = 0, r = n - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (arr[mid] == x) return mid;
        if (arr[mid] < x)
            l = mid + 1;
        else
            r = mid - 1;
    }
    return -1;
}

// Fibonacci Search
int fibonacciSearch(int arr[], int n, int x) {
    int fib2 = 0;  
    int fib1 = 1;  
    int fibM = fib2 + fib1;  

    while (fibM < n) {
        fib2 = fib1;
        fib1 = fibM;
        fibM = fib2 + fib1;
    }

    int offset = -1;

    while (fibM > 1) {
        int i = (offset + fib2 < n - 1) ? offset + fib2 : n - 1;

        if (arr[i] < x) {
            fibM = fib1;
            fib1 = fib2;
            fib2 = fibM - fib1;
            offset = i;
        } else if (arr[i] > x) {
            fibM = fib2;
            fib1 -= fib2;
            fib2 = fibM - fib1;
        } else {
            return i;
        }
    }

    if (fib1 && arr[offset + 1] == x) return offset + 1;

    return -1;
}
