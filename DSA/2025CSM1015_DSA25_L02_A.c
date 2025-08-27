#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

// inserting the elements at the starting.
static Node* insertAtFirst(Node* head, int value) {
    Node* p = (Node*)malloc(sizeof(Node));
    if (!p) return head;
    p->data = value;
    p->next = head;
    return p;
}

//inserting the elements at the end.
static Node* insertAtEnd(Node* head, int value) {
    Node* p = (Node*)malloc(sizeof(Node));
    if (!p) return head;
    p->data = value;
    p->next = NULL;
    if (!head) return p;
    Node* cur = head;
    while (cur->next) cur = cur->next;
    cur->next = p;
    return head;
}

//delete the starting node.
static Node* deleteTheStart(Node* head, int *err) {
    if (!head) { if (err) *err = 1; return NULL; }
    Node* tmp = head;
    head = head->next;
    free(tmp);
    return head;
}

//deleting the ending node.
static Node* deleteTheEnd(Node* head, int *err) {
    if (!head) { if (err) *err = 1; return NULL; }
    if (!head->next) { free(head); return NULL; }
    Node* cur = head;
    while (cur->next->next) cur = cur->next;
    free(cur->next);
    cur->next = NULL;
    return head;
}

// delete the value of the node.
static Node* deleteByValue(Node* head, int x, int *notfound) {
    if (!head) { if (notfound) *notfound = 1; return NULL; }
    if (head->data == x) {
        Node* tmp = head;
        head = head->next;
        free(tmp);
        return head;
    }
    Node* cur = head;
    while (cur->next && cur->next->data != x) cur = cur->next;
    if (!cur->next) { if (notfound) *notfound = 1; return head; }
    Node* tmp = cur->next;
    cur->next = tmp->next;
    free(tmp);
    return head;
}

static int size(Node* head) {
    int c = 0;
    while (head) { ++c; head = head->next; }
    return c;
}

static void display(Node* head) {
    if (!head) { printf("E "); return; }  
    printf("[");
    for (Node* cur = head; cur; cur = cur->next) {
        printf("%d", cur->data);
        if (cur->next) printf("-");
    }
    printf("] ");
}

static void freeList(Node **head) {
    Node* cur = *head;
    while (cur) {
        Node* nxt = cur->next;
        free(cur);
        cur = nxt;
    }
    *head = NULL;
}

//finding the element
static void findAndPrint(Node* head, int target, int step_size) {
    int position = 1;
    for (Node* current = head; current != NULL; current = current->next, position++) {
        if (current->data == target) {
            int logical_diff = (position - 1) * step_size;
            printf("%d (%d) ", position, logical_diff);
            return;
        }
    }
    printf("N ");
}

int main(void) {
    int T;
    if (scanf("%d", &T) != 1) return 0;

    for (int tc = 1; tc <= T; ++tc) {
        int X;
        if (scanf("%d", &X) != 1) return 0;

        Node* start = NULL;
        int stepCount = 0;  // to show currently empty

        printf("#%d ", tc);

        for (int i = 0; i < X; ++i) {
            int choice;
            if (scanf("%d", &choice) != 1) { freeList(&start); return 0; }

            if (choice == 0) {            /* immediate termination */
                freeList(&start);
                return 0;
            }

            int val, nf = 0, err = 0;

            switch (choice) {
                case 1: // insert at beginning
                    if (scanf("%d", &val) != 1) { freeList(&start); return 0; }
                    start = insertAtFirst(start, val);
                    stepCount = -4;
                    break;

                case 2: // insert at end
                    if (scanf("%d", &val) != 1) { freeList(&start); return 0; }
                    start = insertAtEnd(start, val);
                    stepCount = 2;
                    break;

                case 3: // delete first
                    start = deleteTheStart(start, &err);
                    if (err) printf("E ");
                    break;

                case 4: // delete last
                    start = deleteTheEnd(start, &err);
                    if (err) printf("E ");
                    break;

                case 5: // delete value; print N if absent
                    if (scanf("%d", &val) != 1) { freeList(&start); return 0; }
                    start = deleteByValue(start, val, &nf);
                    if (nf) printf("N ");
                    break;

                case 6: // find the value
                    if (scanf("%d", &val) != 1) { freeList(&start); return 0; }
                    findAndPrint(start, val, stepCount);
                    break;

                case 7: /* size */
                    printf("%d ", size(start));
                    break;

                case 8: //  display the string
                    display(start);
                    break;

                default: // wrong choice
                    printf("W ");
                    break;
            }
        }
        printf("\n");
        freeList(&start);
    }
    return 0;
}
