#include <iostream>
#include <string>
#include <cmath>
#include <queue>
#include <sstream>

using namespace std;

class KeyValuePair{
private:
    string key, value;
public:
    KeyValuePair(string ky="", string val="") : key(ky), value(val) {}

    string getKey() const {
        return key;
    }

    string getValue() const {
        return value;
    }
    
    void setKey(string newKey) {
        key=newKey;
    }

    void setValue(string newValue) {
        value=newValue;
    }

    bool operator==(const KeyValuePair & otherKVP) const{
        return key.compare(otherKVP.getKey())==0;
    }
    bool operator>(const KeyValuePair & otherKVP) const{
        return key.compare(otherKVP.getKey())>0;
    }
    bool operator<(const KeyValuePair & otherKVP) const{
        return key.compare(otherKVP.getKey())<0;
    }

};

template <typename T>
class SplayTree{
    protected:
    class Node {
        public:
        T data;
        Node* parent;
        Node* left;
        Node* right;
        Node(T value, Node* p = nullptr, Node* l = nullptr,
            Node* r = nullptr) : data{value}, parent{p}, left{l},
            right{r} {}
    };

    Node* root{nullptr};
    int size {0};

    private:
    Node* createNode(Node* par, const T& obj){
        Node* newNode = new Node(obj, par);
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }
    public:
    SplayTree(){}

    SplayTree(const SplayTree& other) : root(copyTree(other.root)) {}

    ~SplayTree() {
        destroyTree(root);
    }

    SplayTree& operator=(const SplayTree& other) {
        if (this != &other) {
            destroyTree(root);
            root = copyTree(other.root);
        }
        return *this;
    }

    Node* copyTree(Node* node) {
        if (node == nullptr) return nullptr;
        Node* newNode = new Node(node->data);
        newNode->left = copyTree(node->left);
        newNode->right = copyTree(node->right);
        return newNode;
    }

    void destroyTree(Node* node) {
        if (node == nullptr) return;
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;      
    }

    //Insert (non-recursive) (wanted to test my knowledge and do this
    //lab non-recursive)
    Node* insert(const T& obj) {
        if (!root) {
            root = createNode(nullptr, obj);
            size++;
            return root;
        }

        Node* temp = root;
        while (true) {
            if (obj < temp->data) {
                if (!temp->left) {
                    temp->left = createNode(temp, obj);
                    size++;
                    splay(temp->left);
                    return temp->left;
                }
                temp = temp->left;
            } else if (obj > temp->data) {
                if (!temp->right) {
                    temp->right = createNode(temp, obj);
                    size++;
                    splay(temp->right);
                    return temp->right;
                }
                temp = temp->right;
            } else {
                temp->data.setValue(obj.getValue());
                splay(temp);
                return temp;
            }
        }
    }

    //Find (non-recursive)
    Node* find(T obj) {
        Node* temp = root;
        while (temp) {
            if (obj == temp->data) {
                splay(temp);
                return temp;
            }
            temp = (obj < temp->data) ? temp->left : temp->right;
        }
        return nullptr;
    }

    //Remove (non-recursive)
    void remove(T obj) {
        Node* node = find(obj);
        if (!node) return;
        
        //Splaying first allows for a more efficient process
        splay(node);
        if (!node->left) {
            root = node->right;
            if (root) root->parent = nullptr;
        } else {
            Node* maxLeft = findMax(node->left);
            splay(maxLeft);
            maxLeft->right = node->right;
            if (node->right) node->right->parent = maxLeft;
            root = maxLeft;
            root->parent = nullptr;
        }
        delete node;
        size--;
    }

    void splay(Node* n) {
        if (!n) return;
        while (n->parent) {
            if (!n->parent->parent) {
                if (n == n->parent->left) rotateRight(n->parent);
                else rotateLeft(n->parent);
            } else if (n == n->parent->left && n->parent == n->parent->parent->left) {
                rotateRight(n->parent->parent);
                rotateRight(n->parent);
            } else if (n == n->parent->right && n->parent == n->parent->parent->right) {
                rotateLeft(n->parent->parent);
                rotateLeft(n->parent);
            } else if (n == n->parent->left && n->parent == n->parent->parent->right) {
                rotateRight(n->parent);
                rotateLeft(n->parent);
            } else {
                rotateLeft(n->parent);
                rotateRight(n->parent);
            }
        }
        root = n;
    }

    void rotateRight(Node* x) {
        Node* y = x->left;
        if (!y) return;
        x->left = y->right;
        if (y->right) y->right->parent = x;
        y->parent = x->parent;
        if (!x->parent) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->right = x;
        x->parent = y;
    }

    void rotateLeft(Node* x) {
        Node* y = x->right;
        if (!y) return;
        x->right = y->left;
        if (y->left) y->left->parent = x;
        y->parent = x->parent;
        if (!x->parent) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
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

};

class TreeMap{
    private:
    SplayTree<KeyValuePair> tree;

    public:
    TreeMap() : tree(SplayTree<KeyValuePair>()){}

    void insert(string newKey, string newValue){
        tree.insert(KeyValuePair(newKey, newValue));
    }

    string find(string k){
        auto* node = tree.find(KeyValuePair(k, ""));
        return node ? node->data.getValue() : "Not found";
    }

    string remove(string k){
        if (!tree.find(KeyValuePair(k, ""))) return 
            "Key does not exist";
        tree.remove(KeyValuePair(k, ""));
        return "Removal Successful";
    }

};

int main() {
    TreeMap map;
 
  // Insert a number of key-value pairs into the tree map
    map.insert("keyOne", "valueOne");
    map.insert("keyTwo", "valueTwo");
    map.insert("keyThree", "valueThree");
  // Prints out valueOne
  cout << map.find("keyOne") << endl;
 
  // Prints out valueThree
  cout << map.find("keyThree") << endl;
 
  // Prints out an empty string or some default value of your choice
  cout << map.find("keyDoesNotExist") << endl;
 
  // Deletes the key-value pair from the tree map
  cout << map.remove("keyOne") << endl;
}
