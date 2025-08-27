#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void selectionSort(int arr[], int n) {
    clock_t start = clock();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }
        swap(&arr[i], &arr[minIndex]);
    }
    clock_t end = clock();
    printf("Selection Sort took %f seconds.\n", (double)(end - start) / CLOCKS_PER_SEC);
    printArray(arr, n);
}

void insertionSort(int arr[], int n) {
    clock_t start = clock();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
    clock_t end = clock();
    printf("Insertion Sort took %f seconds.\n", (double)(end - start) / CLOCKS_PER_SEC);
    printArray(arr, n);
}

void bubbleSort(int arr[], int n) {
    clock_t start = clock();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
        }
    }
    clock_t end = clock();
    printf("Bubble Sort took %f seconds.\n", (double)(end - start) / CLOCKS_PER_SEC);
    printArray(arr, n);
}

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void mergeSortCaller(int arr[], int n) {
    clock_t start = clock();
    mergeSort(arr, 0, n - 1);
    clock_t end = clock();
    printf("Merge Sort took %f seconds.\n", (double)(end - start) / CLOCKS_PER_SEC);
    printArray(arr, n);
}

int partition(int A[], int low, int high) {
    int pivot = A[low];
    int i = low + 1;
    int j = high;

    while (i <= j) {
        while (i <= high && A[i] <= pivot) i++;
        while (A[j] > pivot) j--;

        if (i < j) {
            swap(&A[i], &A[j]);
        }
    }
    swap(&A[low], &A[j]);
    return j;
}

void quickSort(int A[], int low, int high) {
    if (low < high) {
        int partitionIndex = partition(A, low, high);
        quickSort(A, low, partitionIndex - 1);
        quickSort(A, partitionIndex + 1, high);
    }
}

void quickSortCaller(int arr[], int n) {
    clock_t start = clock();
    quickSort(arr, 0, n - 1);
    clock_t end = clock();
    printf("Quick Sort took %f seconds.\n", (double)(end - start) / CLOCKS_PER_SEC);
    printArray(arr, n);
}

int main() {
    // Hardcoded Input
    int algorithmChoice = 1; // Bubble Sort
    int testCases = 2;

    int sizes[] = {5, 3};
    int data1[] = {1, 5, 9, 6, 7};
    int data2[] = {20, 30, 15};

    for (int t = 0; t < testCases; t++) {
        int size = sizes[t];
        int *arr = (int *)malloc(size * sizeof(int));
        if (!arr) {
            printf("Memory allocation failed.\n");
            return 1;
        }

        // Copy hardcoded test case data
        if (t == 0) {
            for (int i = 0; i < size; i++) arr[i] = data1[i];
        } else {
            for (int i = 0; i < size; i++) arr[i] = data2[i];
        }

        switch (algorithmChoice) {
            case 1:
                bubbleSort(arr, size);
                break;
            case 2:
                selectionSort(arr, size);
                break;
            case 3:
                mergeSortCaller(arr, size);
                break;
            case 4:
                insertionSort(arr, size);
                break;
            case 5:
                quickSortCaller(arr, size);
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }

        free(arr);
    }

    return 0;
}
