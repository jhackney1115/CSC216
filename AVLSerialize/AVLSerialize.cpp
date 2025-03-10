#include <iostream>
#include <string>
#include <cmath>
#include <queue>
#include <sstream>

using namespace std;

struct Node {
    int data;
    int height;
    Node* left;
    Node* right;
    Node(int value) : data(value), left(nullptr), right(nullptr),
        height(1) {}
};

class AVL {
public:
    Node* root;

    AVL() : root(nullptr) {}

    ~AVL() {
        destroyTree(root);
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

    string serialize() {
        return serializeRecursive(root);
    }

    void deserialize(string serial) {
        //Can only be done on an empty AVL
        if(root == nullptr){
        queue<string> nodeQueue=split(serial, ',');
        root=deserializeRecursive(nodeQueue);
        }
    }

private:

    void destroyTree(Node* node) {
        if (node == nullptr) return;
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;      
    }

    int getHeight(Node* node) { return node ? node->height : 0; }
    int getBalanceFactor(Node* node) { return node ? 
            getHeight(node->left) - getHeight(node->right) : 0; }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        return y;
    }

    Node* balance(Node* node) {
        int balanceFactor = getBalanceFactor(node);
        if (balanceFactor > 1) {
            if (getBalanceFactor(node->left) < 0) node->left = 
                rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balanceFactor < -1) {
            if (getBalanceFactor(node->right) > 0) node->right = 
                rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }


    Node* insertRecursive(Node* node, int data) {
        if (node == nullptr) {
            return new Node(data);
        }

        if (data < node->data) {
            node->left = insertRecursive(node->left, data);
        } else if (data > node->data) {
            node->right = insertRecursive(node->right, data);
        } else return node;

        node->height = 1 + max(getHeight(node->left), 
            getHeight(node->right));
        return balance(node);
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
        node->height = 1 + max(getHeight(node->left), 
            getHeight(node->right));
        return balance(node);
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

    string serializeRecursive(Node* node) {
        if (node == nullptr) {
           return "X";
        }
        return  to_string(node->data) + "," + 
            serializeRecursive(node->left) + "," + 
            serializeRecursive(node->right);
    }

    Node* deserializeRecursive(queue<string>& nodeQueue) {
        if (nodeQueue.empty()) return nullptr;
        string nodeValue = nodeQueue.front(); nodeQueue.pop();
        
        if (nodeValue == "X") return nullptr;
        Node* newNode = new Node(stoi(nodeValue));
        
        newNode->left = deserializeRecursive(nodeQueue);
        newNode->right = deserializeRecursive(nodeQueue);
        
        newNode->height = 1 + max(getHeight(newNode->left), 
            getHeight(newNode->right));
        return balance(newNode);
    }

    queue<string> split(const string& str, char delimiter) {
        queue<string> tokens;
        stringstream ss(str);
        string token;
        while (getline(ss, token, delimiter)) {
            tokens.push(token);
        }
        return tokens;
    }
    
};

int main() {
    AVL avl;
    avl.insert(50);
    avl.insert(30);
    avl.insert(20);
    avl.insert(40);
    avl.insert(70);
    avl.insert(60);
    avl.insert(80);

    string firstAVL=avl.serialize();
    cout << "Serialized AVL: " << firstAVL << endl;

    AVL newAVL;
    newAVL.deserialize(firstAVL);
    cout << "Re-serialized AVL after deserialization: " << 
        newAVL.serialize() << endl;

    return 0;
}
