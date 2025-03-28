#include <iostream>
using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;
    Node* parent;

    Node(int val) : value(val), left(NULL), right(NULL), parent(NULL) {}
};

class BST {
public:
    Node* root = NULL;

    // Insert a new value into the BST
    void Insert(int val) {
        Node* z = new Node(val);
        Node* y = NULL;
        Node* x = root;

        while (x != NULL) {
            y = x;
            if (z->value < x->value)
                x = x->left;
            else
                x = x->right;
        }

        z->parent = y;

        if (y == NULL)
            root = z;
        else if (z->value < y->value)
            y->left = z;
        else
            y->right = z;
    }

    // Search a value in the BST
    Node* Search(Node* node, int val) {
        if (node == NULL || node->value == val)
            return node;
        if (val < node->value)
            return Search(node->left, val);
        else
            return Search(node->right, val);
    }

    // Get the node with minimum value
    Node* GetMin(Node* node) {
        while (node && node->left != NULL)
            node = node->left;
        return node;
    }

    // Get the node with maximum value
    Node* GetMax(Node* node) {
        while (node && node->right != NULL)
            node = node->right;
        return node;
    }

    // Get the in-order successor of a given node
    Node* Successor(Node* x) {
        if (x->right != NULL)
            return GetMin(x->right);
        Node* y = x->parent;
        while (y != NULL && x == y->right) {
            x = y;
            y = y->parent;
        }
        return y;
    }

    // Transplant one subtree in place of another
    void Transplant(Node* u, Node* v) {
        if (u->parent == NULL)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        if (v != NULL)
            v->parent = u->parent;
    }

    // Delete a node with a given value
    void Delete(int val) {
        Node* z = Search(root, val);
        if (z == NULL) return;

        if (z->left == NULL) {
            Transplant(z, z->right);
        } else if (z->right == NULL) {
            Transplant(z, z->left);
        } else {
            Node* y = GetMin(z->right);
            if (y->parent != z) {
                Transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            Transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
        }

        delete z; // Free memory
    }

    // In-order traversal
    void InOrder(Node* node) {
        if (node == NULL) return;
        InOrder(node->left);
        cout << node->value << " ";
        InOrder(node->right);
    }
};

int main() {
    BST tree;

    // Insert elements
    tree.Insert(15);
    tree.Insert(6);
    tree.Insert(18);
    tree.Insert(3);
    tree.Insert(7);
    tree.Insert(17);
    tree.Insert(20);

    cout << "In-Order Traversal: ";
    tree.InOrder(tree.root);
    cout << endl;

    // Search
    int searchVal = 7;
    Node* found = tree.Search(tree.root, searchVal);
    cout << "Search " << searchVal << ": " << (found ? "Found" : "Not Found") << endl;

    // Min and Max
    cout << "Minimum: " << tree.GetMin(tree.root)->value << endl;
    cout << "Maximum: " << tree.GetMax(tree.root)->value << endl;

    // Successor
    Node* successor = tree.Successor(found);
    if (successor)
        cout << "Successor of " << found->value << ": " << successor->value << endl;
    else
        cout << "No successor for " << found->value << endl;

    // Delete
    tree.Delete(6);
    cout << "After Deleting 6: ";
    tree.InOrder(tree.root);
    cout << endl;

    return 0;
}