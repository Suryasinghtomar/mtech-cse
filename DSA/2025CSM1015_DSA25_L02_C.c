#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *arr;
    int top;
    int capacity;
} Stack;

Stack* createStack(int capacity) {
    Stack *st = (Stack*)malloc(sizeof(Stack));
    st->arr = (int*)malloc(capacity * sizeof(int));
    st->top = -1;
    st->capacity = capacity;
    return st;
}

bool isEmpty(Stack *st) {
    return st->top == -1;
}

void push(Stack *st, int val) {
    if (st->top + 1 >= st->capacity) {
        st->capacity *= 2;
        st->arr = realloc(st->arr, st->capacity * sizeof(int));
    }
    st->arr[++st->top] = val;
}

int pop(Stack *st) {
    if (isEmpty(st)) return -1;
    return st->arr[st->top--];
}

int peek(Stack *st) {
    if (isEmpty(st)) return -1;
    return st->arr[st->top];
}

void freeStack(Stack *st) {
    free(st->arr);
    free(st);
}


int main(void) {
    int testCases;
    if (scanf("%d", &testCases) != 1) return 0;

    while (testCases--) {
        int N;
        unsigned long long k;
        if (scanf("%d %llu", &N, &k) != 2) return 0;

        // dynamic allocation for DP table
        unsigned long long **dp = malloc((N + 2) * sizeof(*dp));
        for (int i = 0; i <= N + 1; i++) {
            dp[i] = calloc(N + 1, sizeof(**dp));
        }

        // base case
        for (int s = 0; s <= N; s++) {
            dp[N + 1][s] = 1ULL;
        }

        // filling DP table
        for (int a = N; a >= 1; a--) {
            for (int s = 0; s <= N; s++) {
                unsigned long long countWays = 0ULL;
                if (s + 1 <= N) countWays += dp[a + 1][s + 1];
                if (s > 0) countWays += dp[a][s - 1];
                dp[a][s] = countWays;
            }
        }

        unsigned long long totalPermutations = dp[1][0];
        printf("%llu ", totalPermutations);

        if (k == 0 || k > totalPermutations) {
            printf("-1\n");
            for (int i = 0; i <= N + 1; i++) free(dp[i]);
            free(dp);
            continue;
        }

        bool *isUsed = calloc(N + 1, sizeof(bool));
        Stack *stack = createStack(N);   // use stack structure
        int *result = malloc(N * sizeof(int));
        int nextNum = 1, resultIndex = 0;

        // constructing the k-th permutation
        for (int pos = 0; pos < N; pos++) {
            bool found = false;
            for (int num = 1; num <= N; num++) {
                if (isUsed[num]) continue;

                unsigned long long waysHere = 0ULL;
                int stackSize = stack->top + 1;

                if (!isEmpty(stack) && peek(stack) == num) {
                    waysHere = dp[nextNum][stackSize - 1];
                } else if (num >= nextNum) {
                    int nextAfterPush = num + 1;
                    int newStackSize = stackSize + (num - nextNum);
                    waysHere = dp[nextAfterPush][newStackSize];
                } else {
                    continue;
                }

                if (waysHere < k) {
                    k -= waysHere;
                    continue;
                }

                if (!isEmpty(stack) && peek(stack) == num) {
                    pop(stack);
                } else {
                    for (int p = nextNum; p <= num; p++) {
                        push(stack, p);
                    }
                    nextNum = num + 1;
                    pop(stack);
                }

                isUsed[num] = true;
                result[resultIndex++] = num;
                found = true;
                break;
            }
            if (!found) break;
        }

        // print result
        for (int i = 0; i < resultIndex; i++) {
            printf("%d", result[i]);
            if (i + 1 < resultIndex) printf(" ");
        }
        printf("\n");

        free(isUsed);
        free(result);
        freeStack(stack);
        for (int i = 0; i <= N + 1; i++) free(dp[i]);
        free(dp);
    }
    return 0;
}
