#include <algorithm>
#include <cstdio>

// The struct for nodes in AVL.
struct Node {
    int size, height;
    int s, sum;
    Node *parent, *child[2];
    ~Node();
} dummy{0, -1, 0, 0, nullptr, nullptr, nullptr};

// We can handle fewer boundary conditions if we implement AVL with a dummy node.
Node* dummyptr = &dummy;

// Node destructor.
Node::~Node() {
    if (this == dummyptr)
        return;
    if (child[0] != dummyptr)
        delete child[0];
    if (child[1] != dummyptr)
        delete child[1];
}

// The struct for an AVL tree.
struct Tree {
    Node* root;
    ~Tree() {
        if (root != dummyptr)
            delete root;
    }
} tree{dummyptr};

// Update size, height and sum of node u.
void update(Node* u) {
    u->size = 1 + u->child[0]->size + u->child[1]->size;
    u->height = 1 + std::max(u->child[0]->height, u->child[1]->height);
    u->sum = u->s + u->child[0]->sum + u->child[1]->sum;
}

// Perform a single rotation on node u.
void rotate(Node* u) {
    // Your code here
}

// Check and correct imbalances from u to root.
// If an imbalance is Case 1 (LL or RR), Perform the single rotation once.
// If an imbalance is Case 2 (LR or RL), Perform the single rotation twice.
// If an imbalance is Case 3 (L- or R-), Perform the single rotation once.
void update_and_balance(Node* u) {
    // Your code here
}

// Subtask 1: Insert x into the AVL, and maintain the balance.
// Insertion is stable. In other words, the last inserted node should be the last node in in-order traversal among those who have the same value.
void insert(int x) {
    // Your code here
}

// Subtask 2: Find x in the AVL.
// If x not found, return dummyptr.
// If there are multiple nodes with node.s==x, return the node with the smallest depth.
Node* find(int x) {
    // Your code here
}

// Subtask 3: Erase x from the AVL, and maintain the balance.
// If x not found, just do nothing and return.
// If there are multiple nodes with node.s==x, erase the node with the smallest depth.
// If the erased node has two children, replace it with the first node of in-order traversal of its right subtree.
void erase(int x) {
    // Your code here
}

// Subtask 4: Query the k-th node in the AVL.
int kth(int k) {
    // Your code here
}

// Subtask 5: Return the minimum ans, as described in problem statement.
int ans(int k) {
    // Your code here
}

// Print the pre-order of AVL to check whether you maintain the tree structure correctly.
void preorder(Node* u) {
    if (u == dummyptr)
        return;
    printf("%d %d %d %d\n", u->s, u->parent->s, u->child[0]->s, u->child[1]->s);
    preorder(u->child[0]);
    preorder(u->child[1]);
}

// YOU DON'T NEED AND SHOULD NOT MODIFY main()!
int main() {
#ifndef ONLINE_JUDGE
    freopen("avl.in", "r", stdin);
    freopen("avl.out", "w", stdout);
#endif
    int n, opt;
    int x;
    Node* u;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d %d", &opt, &x);
        printf("----------#%d: %d %d----------\n", i, opt, x);
        switch (opt) {
            case 1:
                insert(x);
                preorder(tree.root);
                break;
            case 2:
                u = find(x);
                if (u == dummyptr)
                    printf("Not found!\n");
                else
                    printf("%d\n", u->height);
                break;
            case 3:
                erase(x);
                preorder(tree.root);
                break;
            case 4:
                if (x < 1 or x > tree.root->size)
                    printf("Invalid query!\n");
                else
                    printf("%d\n", kth(x));
                break;
            case 5:
                if (tree.root->size == 0)
                    printf("Invalid query!\n");
                else
                    printf("%d\n", ans(x));
        }
    }
    return 0;
}
