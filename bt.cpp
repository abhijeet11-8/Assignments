#include <iostream>
#include <vector>
#include <queue>
using namespace std;

template <class T>
class Binarytree {
private:
    // Define the Node class
    class Node {
    public:
        T data;
        Node* left;
        Node* right;

        // Constructor to initialize the node
        Node(const T& val) {
            data = val;
            left = nullptr;
            right = nullptr;
        }
    };

    Node* root; // Root of the binary tree

    // Helper function for pre-order traversal
    void preorderHelper(Node* node) {
        if (node == nullptr) return;
        cout << node->data << " ";
        preorderHelper(node->left);
        preorderHelper(node->right);
    }

    // Helper function for in-order traversal
    void inorderHelper(Node* node) {
        if (node == nullptr) return;
        inorderHelper(node->left);
        cout << node->data << " ";
        inorderHelper(node->right);
    }

    // Helper function for post-order traversal
    void postorderHelper(Node* node) {
        if (node == nullptr) return;
        postorderHelper(node->left);
        postorderHelper(node->right);
        cout << node->data << " ";
    }

public:
    // Constructor for tree
    Binarytree() : root(nullptr) {}

    // Function to insert a value into the binary tree
    void insert(const T& value) {
        if (!root) {
            root = new Node(value);
            return;
        }
        Node* current = root;
        while (true) { // Fixed `True` to `true`
            if (value < current->data) {
                if (!current->left) {
                    current->left = new Node(value);
                    return;
                }
                current = current->left;
            } else {
                if (!current->right) {
                    current->right = new Node(value);
                    return;
                }
                current = current->right;
            }
        }
    }

    // Public traversal methods
    void inorder() {
        inorderHelper(root);
        cout << endl;
    }

    void preorder() {
        preorderHelper(root);
        cout << endl;
    }

    void postorder() {
        postorderHelper(root);
        cout << endl;
    }

    vector<T> toArray() {
        if (!root) return {}; // If the tree is empty, return an empty array

        // Use a queue for level-order traversal
        queue<pair<Node*, int>> q;
        q.push({root, 0}); // Start with the root at index 0

        // Determine the maximum possible size of the array
        int maxIndex = 0;
        vector<T> result;

        while (!q.empty()) {
            Node* current = q.front().first;
            int index = q.front().second;
            q.pop();

            // Resize the array if necessary
            if (index >= result.size()) {
                result.resize(index + 1, -1); // Fill with a placeholder value (-1)
            }

            // Place the current node's data at the correct index
            result[index] = current->data;

            // Add the left and right children to the queue
            if (current->left) {
                q.push({current->left, 2 * index + 1});
            }
            if (current->right) {
                q.push({current->right, 2 * index + 2});
            }
        }

        return result;
    }
};

int main() {
    Binarytree<int> tree;

    // Insert nodes into the binary tree
    tree.insert(10);
    tree.insert(3);
    tree.insert(35);
    tree.insert(4);
    tree.insert(22);

    // Perform traversals
    cout << "preorder: ";
    tree.preorder();

    cout << "inorder: ";
    tree.inorder();

    cout << "postorder: ";
    tree.postorder();

    // Convert the tree to an array
    vector<int> arr = tree.toArray();
    cout << "Tree as array (level-order): ";
    for (int val : arr) {
        if (val != -1) { // Ignore placeholder values
            cout << val << " ";
        }
    }
    cout << endl;

    return 0;
}
