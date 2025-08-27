#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;   
} Node;

// utilities
int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

Node* newNode(int key) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->key = key;
    n->left = NULL;
    n->right = NULL;
    n->height = 1;
    return n;
}

void freeTree(Node* r) {
    if (!r) return;
    freeTree(r->left);
    freeTree(r->right);
    free(r);
}

// BST Insert
Node* insertBST(Node* root, int key) {
    if (key <= 0) return root; 
    if (!root) return newNode(key);
    if (key < root->key){
         root->left = insertBST(root->left, key);
    }
    else if (key > root->key){
         root->right = insertBST(root->right, key);
    }
    return root;
}

Node* maxNode(Node* r) {
    if (!r) return NULL;
    while (r->right){
         r = r->right;
    }
    return r;
}

Node* deleteBST(Node* root, int key) {
    if (!root) return root;
    if (key < root->key){
         root->left = deleteBST(root->left, key);
        }
    else if (key > root->key){
         root->right = deleteBST(root->right, key);
    }
    else {
        if (!root->left) {
            Node* t = root->right;
            free(root);
            return t;
        } else if (!root->right) {
            Node* t = root->left;
            free(root);
            return t;
        } else {
            // prefer predecessor from left subtree
            Node* pred = maxNode(root->left);
            root->key = pred->key;
            root->left = deleteBST(root->left, pred->key);
        }
    }
    return root;
}

//Node Height
int heightNode(Node *n) 
{
    if (n != NULL) 
    {
        return n->height;
    } 
    else 
    {
        return 0;
    }
}

void updateHeight(Node *n) 
{
    if (n != NULL) 
    {
        int leftH = heightNode(n->left);
        int rightH = heightNode(n->right);
        if (leftH > rightH) 
        {
            n->height = leftH + 1;
        } 
        else 
        {
            n->height = rightH + 1;
        }
    }
}
//Right rotate
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}
//left rotate
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}

int getBalance(Node *n) 
{
    if (n == NULL) 
    {
        return 0;
    }
    else 
    {
        int leftHeight = heightNode(n->left);
        int rightHeight = heightNode(n->right);
        int balance = leftHeight - rightHeight;
        return balance;
    }
}

//Insertions in AVL tree
Node* insertAVL(Node* node, int key) {
    if (key <= 0) return node;
    if (!node) return newNode(key);
    if (key < node->key){
         node->left = insertAVL(node->left, key);
    }
    else if (key > node->key){
         node->right = insertAVL(node->right, key);}

    else return node;

    updateHeight(node);
    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key){
         return rightRotate(node);     
          } // LL
    if (balance < -1 && key > node->right->key){
         return leftRotate(node); 
             } // RR
    if (balance > 1 && key > node->left->key) {
         node->left = leftRotate(node->left);
          return rightRotate(node); 
        } // LR
    if (balance < -1 && key < node->right->key) {
         node->right = rightRotate(node->right); 
         return leftRotate(node);
         } // RL

    return node;
}

Node* deleteAVL(Node* root, int key) {
    if (!root) return root;
    if (key < root->key) root->left = deleteAVL(root->left, key);
    else if (key > root->key) root->right = deleteAVL(root->right, key);
    else {
        if (!root->left) {
            Node* t = root->right; free(root); return t;
        } else if (!root->right) {
            Node* t = root->left; free(root); return t;
        } else {
            Node* pred = maxNode(root->left);
            root->key = pred->key;
            root->left = deleteAVL(root->left, pred->key);
        }
    }

    updateHeight(root);
    int balance = getBalance(root);
    if (balance > 1 && getBalance(root->left) >= 0){
     return rightRotate(root);
     } // LL
    if (balance > 1 && getBalance(root->left) < 0) {
         root->left = leftRotate(root->left);
          return rightRotate(root);
         } // LR
    if (balance < -1 && getBalance(root->right) <= 0){
     return leftRotate(root);
     } // RR
    if (balance < -1 && getBalance(root->right) > 0) {
         root->right = rightRotate(root->right);
          return leftRotate(root);
         } // RL

    return root;
}

// traversals
// Non-recursive preorder
void preorderIter(Node *root)
{
    if (root == NULL)
    {
        return;
    }

    Node *stack[10000];
    int top = -1;

    top = top + 1;
    stack[top] = root;

    while (top >= 0)
    {
        Node *current = stack[top];
        top = top - 1;

        printf("%d ", current->key);

        if (current->right != NULL)
        {
            top = top + 1;
            stack[top] = current->right;
        }

        if (current->left != NULL)
        {
            top = top + 1;
            stack[top] = current->left;
        }
    }
}

//Inorder recursive
void inorderRec(Node* r) {
    if (!r) return;
    inorderRec(r->left);
    printf("%d ", r->key);
    inorderRec(r->right);
}

// Postorder recursive
void postorderRec(Node* r) {
    if (!r) return;
    postorderRec(r->left);
    postorderRec(r->right);
    printf("%d ", r->key);
}

// Level order (L) 
void levelOrder(Node* root) {
    if (!root) return;
    Node* q[4096];
    int f = 0, b = 0;
    q[b++] = root;
    while (f < b) {
        Node* cur = q[f++];
        printf("%d ", cur->key);
        if (cur->left) q[b++] = cur->left;
        if (cur->right) q[b++] = cur->right;
    }
}

//Height
int heightEdges(Node* r) {
    if (!r) return -1; // empty => -1 edges
    int lh = heightEdges(r->left);
    int rh = heightEdges(r->right);
    return 1 + maxInt(lh, rh);
}

//Diameter
int bestDiaNodes;
int diameterDFS_nodes(Node* r, int* outHeight) {
    if (!r) { *outHeight = 0; return 0; }
    int lh = 0, rh = 0;
    int ldia = diameterDFS_nodes(r->left, &lh);
    int rdia = diameterDFS_nodes(r->right, &rh);
    int curNodes = lh + rh + 1;
    if (curNodes > bestDiaNodes) bestDiaNodes = curNodes;
    *outHeight = 1 + maxInt(lh, rh);
    return bestDiaNodes;
}

bool isLeaf(Node* n) {
     return n && !n->left && !n->right;
     }

void addRightBoundary(Node* root, int out[], int *k) {
    Node* cur = root->right;
    while (cur) {
        if (!isLeaf(cur)) out[(*k)++] = cur->key;
        if (cur->right) cur = cur->right;
        else cur = cur->left;
    }
}

void addLeavesRightToLeft(Node* root, int out[], int *k) {
    if (!root) return;
    addLeavesRightToLeft(root->right, out, k);
    if (isLeaf(root)){
         out[(*k)++] = root->key;
        }
    addLeavesRightToLeft(root->left, out, k);
}

void addLeftBoundaryBottomUp(Node* root, int out[], int *k) {
    Node* cur = root->left;
    int stackVals[1024];
    int top = -1;
    while (cur) {
        if (!isLeaf(cur)) stackVals[++top] = cur->key;
        if (cur->left) cur = cur->left;
        else cur = cur->right;
    }
    while (top >= 0) out[(*k)++] = stackVals[top--];
}

void queryY(Node* root) {
    if (!root) {
         printf("0\n"); 
         return; 
        }
    int out[5000]; int k = 0;
    out[k++] = root->key;
    addRightBoundary(root, out, &k);
    addLeavesRightToLeft(root, out, &k);
    addLeftBoundaryBottomUp(root, out, &k);
    long long sum = 0;
    for (int i = 0; i < k; ++i){
         sum += out[i];
    }
    printf("%lld ", sum);
    for (int i = 0; i < k; ++i){
         printf("%d ", out[i]);
    }
    printf("\n");
}

//Width 
int treeWidth(Node* root) {
    if (!root){
         return 0;
    }
    Node* q[5000]; 
    int f=0,b=0; 
    q[b++] = root;
    int maxw = 0;
    while (f < b) {
        int cnt = b - f;
        if (cnt > maxw){
             maxw = cnt;
        }
        for (int i = 0; i < cnt; ++i) {
            Node* cur = q[f++];
            if (cur->left) {
                q[b++] = cur->left;
            }
            if (cur->right) {
                q[b++] = cur->right;
            }
        }
    }
    return maxw;
}

bool findExist(Node* root, int key) {
    if (!root){
         return false;
    }
    if (root->key == key){
         return true;
        }
    if (key < root->key) {
        return findExist(root->left, key);
    }
    return findExist(root->right, key);
}

// LCA array
int lcaBST(Node* root, int a, int b) {
    Node* cur = root;
    while (cur) {
        if (a < cur->key && b < cur->key){
             cur = cur->left;}

        else if (a > cur->key && b > cur->key){
             cur = cur->right;
        }
        else return cur->key;
    }
    return -1;
}

bool buildRootToNodePath(Node* root, int target, int arr[], int *len) {
    if (!root) return false;
    arr[(*len)++] = root->key;
    if (root->key == target) return true;
    if (target < root->key) {
        if (buildRootToNodePath(root->left, target, arr, len)) return true;
    } else {
        if (buildRootToNodePath(root->right, target, arr, len)) return true;
    }
    (*len)--;
    return false;
}

int parseInts(char* line, int arr[]) {
    int cnt = 0;
    char *tok = strtok(line, " \t\r\n");
    while (tok) {
        arr[cnt++] = atoi(tok);
        tok = strtok(NULL, " \t\r\n");
    }
    return cnt;
}

int main() {
    int Z;
    if (scanf("%d", &Z) != 1) return 0;
    getchar(); 

    Node* root = NULL;
    bool lastIsAVL = false;

    while (Z--) {
        char cmd;
        if (scanf(" %c", &cmd) != 1) {
        break;
        }

        char rest[5000];
        rest[0] = '\0';
        fgets(rest, sizeof(rest), stdin);

        char *p = rest;
        while (*p == ' ' || *p == '\t') ++p;

        if (cmd == 'T' || cmd == 'H') {
            // construct new tree: delete previous fully
            freeTree(root);
            root = NULL;
            lastIsAVL = (cmd == 'H');

            // parse integers
            int vals[1500];
            int n = parseInts(p, vals);
            for (int i = 0; i < n; ++i) {
                int v = vals[i];
                if (v > 0) {
                    if (lastIsAVL) root = insertAVL(root, v);
                    else root = insertBST(root, v);
                } else if (v < 0) {
                    int t = -v;
                    if (lastIsAVL) root = deleteAVL(root, t);
                    else root = deleteBST(root, t);
                }
            }
        }
        else if (cmd == 'A') {
            int vals[1500], n = parseInts(p, vals);
            for (int i = 0; i < n; ++i) {
                int v = vals[i];
                if (v <= 0) continue;
                if (lastIsAVL) root = insertAVL(root, v);
                else root = insertBST(root, v);
            }
        }
        else if (cmd == 'U') {
            int vals[1500], n = parseInts(p, vals);
            for (int i = 0; i < n; ++i) {
                int v = vals[i];
                if (v <= 0) continue;
                if (lastIsAVL) root = deleteAVL(root, v);
                else root = deleteBST(root, v);
            }
        }
        else if (cmd == 'F') {
            int x = atoi(p);
            if (x <= 0) { printf("No\n"); }
            else printf(findExist(root, x) ? "Yes\n" : "No\n");
        }
        else if (cmd == 'Q') { // leaves
            printf("%d\n", root ? ( (root->left==NULL && root->right==NULL) ? 1 : 0 ) : 0);
        }
        else if (cmd == 'N') { 
            // count nodes recursively
            int cnt=0;
            Node* stack[5000];
            int top=-1;
            if (root) stack[++top]=root;
            while(top>=0) {
                Node* cur=stack[top--];
                cnt++;
                if (cur->right) stack[++top]=cur->right;
                if (cur->left) stack[++top]=cur->left;
            }
            printf("%d\n", cnt);
        }
        else if (cmd == 'P') { 
            preorderIter(root);
             printf("\n");
             }
        else if (cmd == 'I') {
             inorderRec(root);
              printf("\n");
             }
        else if (cmd == 'S') { 
            postorderRec(root);
             printf("\n"); 
            }
        else if (cmd == 'L') {
             levelOrder(root);
              printf("\n"); 
            }
        else if (cmd == 'D') {
            if (!root) printf("0\n");
            else {
                int e = heightEdges(root);
                printf("%d\n", e);
            }
        }
        else if (cmd == 'X') {
            if (!root) { printf("0\n"); }
            else {
                bestDiaNodes = 0;
                int tmp=0;
                diameterDFS_nodes(root, &tmp);
                printf("%d\n", bestDiaNodes);
            }
        }
        else if (cmd == 'Y') {
            queryY(root);
        }
        else if (cmd == 'W') {
            printf("%d\n", treeWidth(root));
        }
        else if (cmd == 'C') {
            int a,b;
            if (sscanf(p, "%d %d", &a, &b) != 2) {
                 printf("-1\n"); continue; 
                }
            if (!findExist(root, a) || !findExist(root, b)) { 
                printf("-1\n"); 
            }
            else if (a==b) printf("%d\n", a);
            else printf("%d\n", lcaBST(root, a, b));
        }
        else if (cmd == 'R') {
            int a,b;
            if (sscanf(p, "%d %d", &a, &b) != 2) { 
                printf("Unreachable\n"); 
                continue;
             }
            if (!findExist(root, a)) { 
                printf("Source does not exist\n"); 
                continue; 
            }
            if (!findExist(root, b)) { 
                printf("Destination does not exist\n"); 
                continue; 
            }
            if (a == b) { printf("%d\n", a);
                 continue;
                 }
            int path[5000], len = 0;
            buildRootToNodePath(root, b, path, &len);
            int idxA = -1;
            for (int i = 0; i < len; ++i) if (path[i] == a) { idxA = i; break; }
            if (idxA == -1) { printf("Unreachable\n"); continue; }
            // print route from a to b using L/R steps
            printf("%d", a);
            for (int i = idxA; i+1 < len; ++i) {
                int cur = path[i];
                int nxt = path[i+1];
                if (nxt < cur) printf(" L %d", nxt);
                else printf(" R %d", nxt);
            }
            printf("\n");
        }
        else {
            
        }
    }

    freeTree(root);
    return 0;
}
