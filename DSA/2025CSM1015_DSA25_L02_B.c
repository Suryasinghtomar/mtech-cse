#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Insert a node at the head
Node* insertHead(Node* head, int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = val;
    newNode->next = head;
    return newNode;
}

// Initialize a linked list with the first value 1
Node* initializeLL() {
    Node *head = (Node*)malloc(sizeof(Node));
    if (!head) {
        exit(1);
    }
    head->data = 1;
    head->next = NULL;
    return head;
}

// Reverse a linked list
Node* reverseLinkedList(Node* head) {
    Node *prev = NULL, *curr = head, *next = NULL;
    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

// Multiply linked list number by integer b
Node* multiplyListByInt(Node* a, int b) {
    a = reverseLinkedList(a);
    Node* result = NULL;
    int carry = 0;
    Node* temp = a;

    while (temp) {
        int prod = temp->data * b + carry;
        result = insertHead(result, prod % 10);
        carry = prod / 10;
        temp = temp->next;
    }

    while (carry) {
        result = insertHead(result, carry % 10);
        carry /= 10;
    }

    // Free the old list
    while (a) {
        Node* t = a;
        a = a->next;
        free(t);
    }

    return result;
}

// Convert linked list to string
void linkedListToString(Node* head, char* str) {
    int i = 0;
    while (head) {
        str[i++] = head->data + '0';
        head = head->next;
    }
    str[i] = '\0';
}

// Count pattern occurrences in string
int countPatterns(const char* text, const char* pattern) {
    int count = 0;
    int n = strlen(text);
    int m = strlen(pattern);
    for (int i = 0; i <= n - m; i++) {
        int match = 1;
        for (int j = 0; j < m; j++) {
            if (text[i + j] != pattern[j]) {
                match = 0;
                break;
            }
        }
        if (match){
             count++;
        }
    }
    return count;
}

// Print linked list
void printLinkedList(Node* head) {
    Node* temp = head;
    while (temp) {
        printf("%d", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    int NumOfTestCases;
    scanf("%d", &NumOfTestCases);

    for (int t = 0; t < NumOfTestCases; t++) {
        int n, k;
        scanf("%d %d", &n, &k);

        Node* list = initializeLL();

        for (int i = 2; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                list = multiplyListByInt(list, i);
            }
        }

        // No final reverse here
        char numStr[5000]; // Adjust size if needed
        linkedListToString(list, numStr);

        char kStr[10];
        sprintf(kStr, "%d", k);

        int trailingZeros = 0;
        for (int i = strlen(numStr) - 1; i >= 0; i--) {
            if (numStr[i] == '0') trailingZeros++;
            else break;
        }

        int patternCount = countPatterns(numStr, kStr);

        printf("%d %d %s\n", trailingZeros, patternCount, numStr);

        // Free memory
        Node* tmp;
        while (list) {
            tmp = list;
            list = list->next;
            free(tmp);
        }
    }

    return 0;
}

