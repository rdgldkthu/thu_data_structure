#include <iostream>
#include <algorithm>
using namespace std;

//struct for binary search tree node
struct BSTNode {
    int data;
    BSTNode* left;
    BSTNode* right;
    int height;
    BSTNode() : data(NULL), left(NULL), right(NULL), height(NULL) {}
    BSTNode(int d) : data(d), left(NULL), right(NULL), height(1) {}
};

//function to get the height of a node
int getHeight(BSTNode* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

//function to update the height of a node based on its children's heights
void updateHeight(BSTNode* node) {
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
}

//function for right rotation
BSTNode* rightRotate(BSTNode* y) {
    BSTNode* x = y->left;
    BSTNode* T2 = x->right;

    //rotation
    x->right = y;
    y->left = T2;

    //update heights
    updateHeight(y);
    updateHeight(x);

    return x;
}

//function for a left rotation
BSTNode* leftRotate(BSTNode* x) {
    BSTNode* y = x->right;
    BSTNode* T2 = y->left;

    //rotation
    y->left = x;
    x->right = T2;

    //update heights
    updateHeight(x);
    updateHeight(y);

    return y;
}

//function to get the balance factor of a node
int getBalanceFactor(BSTNode* node) {
    if (node == NULL) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

//function to insert a data into the AVL tree
BSTNode* insert(BSTNode* root, int d) {
    //standard BST insert
    if (root == NULL) { return new BSTNode(d); }
    if (d < root->data) { root->left = insert(root->left, d); }
    else if (d > root->data) { root->right = insert(root->right, d); }
    else { return root; } //duplicate not allowed

    //update height of current node
    updateHeight(root);

    //get the balance factor to check if the node became unbalanced
    int balance = getBalanceFactor(root);

    //left-left Case
    if (balance > 1 && d < root->left->data) { return rightRotate(root); }

    //right-right Case
    if (balance < -1 && d > root->right->data) { return leftRotate(root); }

    //left-right Case
    if (balance > 1 && d > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    //right-left Case
    if (balance < -1 && d < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    //if no rotation needed just return
    return root;
}

//function to search for a data
BSTNode* search(BSTNode* root, int d) {
    if (root == NULL || root->data == d) { return root; }
    if (root->data < d) { return search(root->right, d); }
    return search(root->left, d);
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
    int d;
    BSTNode* root = NULL;
    while (N--) {
        cin >> d;
        root = insert(root, d);
    }
    //search for the lowest common ancestor of each node pair
    int p, q;
    while (M--) {
        cin >> p >> q;
        BSTNode* pnode = search(root, p);
        BSTNode* qnode = search(root, q);
        cout << lowestCommonAncestor(root, pnode, qnode)->data << endl;
    }
    return 0;
}