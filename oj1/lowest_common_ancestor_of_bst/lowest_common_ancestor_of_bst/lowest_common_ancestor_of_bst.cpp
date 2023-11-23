#include <iostream>
using namespace std;

//struct for binary search tree node
struct BSTNode {
    int data;
    BSTNode* left;
    BSTNode* right;
    BSTNode() : data(NULL), left(NULL), right(NULL) {}
};

//function to insert an element to bst
void insert(int x, BSTNode*& p) {
    if (p == NULL) {
        p = new BSTNode;
        p->data = x;
        p->left = NULL;
        p->right = NULL;
    }
    else if (x < p->data) { insert(x, p->left); }
    else if (x > p->data) { insert(x, p->right); }
}

//function to search a node in bst based on data and return the node
BSTNode* search(int x, BSTNode* p) {
    if (p == NULL) { return NULL; }
    else if (x < p->data) { return search(x, p->left); }
    else if (x > p->data) { return search(x, p->right); }
    else { return p; }
}

//function to search for the lowest common ancestor of two nodes in bst
BSTNode* lowestCommonAncestor(BSTNode* root, BSTNode* p, BSTNode* q) {
    if (!root) return NULL;
    if (root->data > max(p->data, q->data))
        return lowestCommonAncestor(root->left, p, q);
    else if (root->data < min(p->data, q->data))
        return lowestCommonAncestor(root->right, p, q);
    else return root;
}

int main() {
    //input the number of nodes in bst, and the number of searches to do
    int N, M;
    cin >> N >> M;

    //construct a bst based on the input data
    int x;
    BSTNode* root = NULL;
    while (N--) {
        cin >> x;
        insert(x, root);
    }

    //search for the lowest common ancestor of each node pair
    int p, q;
    while (M--) {
        cin >> p >> q;
        BSTNode* pnode = search(p, root);
        BSTNode* qnode = search(q, root);
        cout << lowestCommonAncestor(root, pnode, qnode)->data << endl;
    }
}