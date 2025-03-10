#include <iostream>
#include <string>
#include <cmath>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BST {
public:
    Node* root;

    BST() : root(nullptr) {}

    ~BST() {
        destroyTree(root);
    }

    void destroyTree(Node* node) {
        if (node == nullptr) return;
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;      
    }

    void insert(int data) {
        root = insertRecursive(root, data);
    }

    void remove(int data) {
        root = removeRecursive(root, data);
    }

    bool search(int data) {
        return searchRecursive(root, data);
    }

    void inorderTraversal() {
        inorderRecursive(root);
        cout << endl;
    }

private:
    Node* insertRecursive(Node* node, int data) {
        if (node == nullptr) {
            return new Node(data);
        }

        if (data < node->data) {
            node->left = insertRecursive(node->left, data);
        } else if (data > node->data) {
            node->right = insertRecursive(node->right, data);
        }

        return node;
    }

   Node* removeRecursive(Node* node, int data) {
        if (node == nullptr) {
            return nullptr;
        }

        if (data < node->data) {
            node->left = removeRecursive(node->left, data);
        } else if (data > node->data) {
            node->right = removeRecursive(node->right, data);
        } else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = findMin(node->right);
            node->data = temp->data;
            node->right = removeRecursive(node->right, temp->data);
        }
        return node;
    }

    Node* findMin(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node* findMax(Node* node) {
        while (node->right != nullptr) {
            node = node->right;
        }
        return node;
    }

    bool searchRecursive(Node* node, int data) {
        if (node == nullptr) {
            return false;
        }

        if (data == node->data) {
            return true;
        } else if (data < node->data) {
            return searchRecursive(node->left, data);
        } else {
            return searchRecursive(node->right, data);
        }
    }

    void inorderRecursive(Node* node) {
        if (node != nullptr) {
            inorderRecursive(node->left);
            cout << node->data << " ";
            inorderRecursive(node->right);
        }
    }
};

int main() {
    BST bst;
    bst.insert(50);
    bst.insert(30);
    bst.insert(20);
    bst.insert(40);
    bst.insert(70);
    bst.insert(60);
    bst.insert(80);

    cout << "Inorder traversal: ";
    bst.inorderTraversal();

    cout << "Search for 40: " << (bst.search(40) ? "Found" :
     "Not Found") << endl;
    cout << "Search for 90: " << (bst.search(90) ? "Found" :
     "Not Found") << endl;

    bst.remove(20);
    cout << "Inorder traversal after deleting 20: ";
    bst.inorderTraversal();

    bst.remove(50);
     cout << "Inorder traversal after deleting 50: ";
    bst.inorderTraversal();
    return 0;
}
