#include <iostream>
#include <cstdlib>
#include <string>
#include <list>
#include <utility>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>

using namespace std;

template <typename E>
class Tree {
  protected:
    //------ nested Node class ------
    class Node {
      public:                   
      // members public for convenience, as Node class is protected
        E element;
        Node* parent;
        Node* left{nullptr};
        Node* right{nullptr};

        Node(E e, Node* p = nullptr) : element{e}, parent{p} {}
    };  // end of Node class

    //------ data members of Tree ------
    Node* rt{nullptr};
    int sz{0};

  public:
    //------ nested Position class ------
    class Position {
      private:
        Node* node;
        friend class Tree;    
        // allow outer class access to node pointer
        
      public:
        Position(Node* nd = nullptr) : node{nd} {}
                 
        bool operator==(Position other) const { return node == other.node; }
        bool operator!=(Position other) const { return node != other.node; }

        bool is_null() const { return node == nullptr; }
        bool is_root() const { return node->parent == nullptr; }
        bool is_external() const { return node->left == nullptr && node->right == nullptr; }
        
        E& element() { return node->element; }                 // will allow element to be edited
        const E& element() const { return node->element; }
        Position parent() const { return Position(node->parent); }
        Position left() const { return Position(node->left); }
        Position right() const { return Position(node->right); }
        
        vector<Position> children() const {
            vector<Position> result;
            if (node->left != nullptr) result.push_back(Position(node->left));
            if (node->right != nullptr) result.push_back(Position(node->right));
            return result;
        }
        
        int num_children() const {
            int result{0};
            if (node->left != nullptr) result++;
            if (node->right != nullptr) result++;
            return result;
        }
    };  // end of Position class

    //------ member functions of Tree ------

    Tree() {}                           // Constructs a tree with zero nodes

    int size() const { return sz; }                 // Returns the number of elements in the tree
    bool empty() const { return sz == 0; }          // True if the tree has size 0

    Position root() const { return Position(rt); }  // Returns a Position for the root (possibly null)

    vector<Position> positions() const {            // Returns an inorder sequence of positions
        vector<Position> gather;
        if (rt) inorder(Position(rt), gather);      // (the inorder function is defined in later section)
        return gather;
    }

    void add_root(const E& e = E()) {               // add root to (presumed) empty tree
        rt = new Node(e);
        sz = 1;
    }

    void add_left(Position p, const E& e) {        
        p.node->left = new Node{e, p.node};        
        sz++;
    }
    
    void add_right(Position p, const E& e) {       
        p.node->right = new Node{e, p.node};       
        sz++;
    }
    
    void erase(Position p) {                      
        Node* nd = p.node;
        Node* child{nd->left == nullptr ? nd->right : nd->left};  
        
        if (child != nullptr)
            child->parent = nd->parent;           

        if (nd == rt)
            rt = child;                             
        else if (nd->parent->left == nd)            
            nd->parent->left = child;
        else                                       
            nd->parent->right = child;
        sz--;
        delete nd;
    }

    void attach(Position p, Tree& left, Tree& right) {
        Node* nd = p.node;
        nd->left = left.rt;
        nd->right = right.rt;
        sz += left.sz + right.sz;

        if (left.rt) left.rt->parent = nd;
        if (right.rt) right.rt->parent = nd;

        left.sz = right.sz = 0;
        left.rt = right.rt = nullptr;
    }

    void get_codes(Position p, string str, unordered_map<char,string>& huffmanCode)
    {
        if (p == nullptr)
        {
            return;
        }

        if (p.left().is_null() && p.right().is_null())
        {
            huffmanCode[p.element()] = str;
        }

        get_codes(p.left(), str + "0", huffmanCode);
        get_codes(p.right(), str + "1", huffmanCode);
    }

  // ------------- Rule-of-five support ----------------
  private:
    void tear_down(Node* nd) {
        if (nd != nullptr) {
            tear_down(nd->left);
            tear_down(nd->right);
            delete nd;
        }
    }

    // Create cloned structure of model and return pointer to the new structure
    static Node* clone(Node* model) {
        if (model == nullptr) return nullptr;       // trivial clone
        Node* new_root = new Node(model->element);
        new_root->left = clone(model->left);
        if (new_root->left) new_root->left->parent = new_root;
        new_root->right = clone(model->right);
        if (new_root->right) new_root->right->parent = new_root;
        return new_root;
    }
    
  public:
    // destructor
    ~Tree() { tear_down(rt); }

    // copy constructor
    Tree(const Tree& other) : sz{other.sz}, rt{clone(other.rt)} {}

    // copy assignment
    Tree& operator=(const Tree& other) {
        if (this != &other) {                       // bypass self-assignment
            tear_down(rt);
            rt = clone(other.rt);
            sz = other.sz;
        }
        return *this;
    }

    // move constructor
    Tree(Tree&& other) : sz{other.sz}, rt{other.rt} {
        // reset other to empty
        other.sz = 0;
        other.rt = nullptr;
    }

    Tree& operator=(Tree&& other) {
        if (this != &other) {                       // bypass self-assignment
            using std::swap;
            swap(sz, other.sz);
            swap(rt, other.rt);                     // old structure will be destroyed by other
        }
        return *this;
    }

    bool operator<(Tree const& other) const
    {
        return false; //only so PQueue class works
    }
};

template <typename Entry, typename Compare=less<Entry>>
class PQueue {
  protected:
    typename std::list<Entry> data;                        
    Compare less_than;                              

  public:
    PQueue() {}                    

    int size() const { return data.size(); }
    bool empty() const { return data.empty(); }
    void insert(const Entry& e) { data.push_back(e); }
    const Entry& min() const { return *find_min(); }  
    void remove_min() { data.erase(find_min());  }   
    
  private:    
    typedef typename list<Entry>::const_iterator const_iterator;

    
    const_iterator find_min() const {
        const_iterator small{data.begin()};
        const_iterator walk{++data.begin()};
        while (walk != data.end()) {
            if (less_than(*walk, *small))  
                small = walk;
            ++walk;
        }
        return small;
    }
};

unordered_map<char,int> str_to_vec(string text)
{
    unordered_map<char,int> ret_vec;
    for(string::size_type i = 0; i < text.length(); i++)
    {
        char temp_char = text[i];
        ret_vec[temp_char]++;
    }
    return ret_vec;
}

Tree<char> huffman_encode(unordered_map<char,int> text_vec)
{
    PQueue<pair<int,Tree<char>>> pqueue;

    for(auto pair : text_vec)
    {
        Tree<char> temp_tree;
        temp_tree.add_root(pair.first);
        pqueue.insert(make_pair(pair.second,temp_tree));
    }
    while(pqueue.size() > 1)
    {
        pair<int,Tree<char>> p1 = pqueue.min();
        pqueue.remove_min();
        pair<int,Tree<char>> p2 = pqueue.min();
        pqueue.remove_min();
        Tree<char> new_tree;
        new_tree.add_root();
        new_tree.attach(new_tree.root(),p1.second,p2.second);
        pqueue.insert(make_pair(p1.first + p2.first,new_tree));
    }
    pair<int,Tree<char>> ret_p = pqueue.min();
    return ret_p.second;
}

string decompress(const string& text, unordered_map<char,string> code)
{
    bool decoded = false, failed = false;
    int n(text.size());
    int pos = 0;
    string dec_str;
    do{
        int pos_og = pos;
        for (auto pair : code) { 
            int k{0};
            string curr = pair.second;
            while (k < curr.size() && text[pos+k] == curr[k])
            {
                k++;
            }
            if (k == curr.size())
            {
                dec_str+= pair.first;
                pos+= k;
                break;
            }
        }
        if(pos_og == pos)
        {
            decoded = true;
            failed = true;
        }
        if(pos >= n)
        {
            decoded = true;
        }
    }while(!decoded);
    if(failed)
    {
        return "ERROR"; 
    }
    else
    {
        return dec_str;
    }
}

string decompressFromFile(const string& tableFileName)
{
    ifstream inFile(tableFileName);
    if (!inFile) return "ERROR: cannot open file";

    unordered_map<char,string> code;
    string line;
    bool inTable = true;
    string bits;

    while (getline(inFile, line)) {
        if (inTable) {
            // test for separator line
            if (line == "---") {
                inTable = false;
            }
            else {
                // parse a table entry: "<int> <bitstring>"
                istringstream iss(line);
                int ci; 
                string bitstr;
                if (iss >> ci >> bitstr) {
                    code[char(ci)] = bitstr;
                }
                // else malformed line: silently ignore
            }
        }
        else {
            //getting the encoded text
            if (bits.empty()) {
                bits = line;
            }
            // any further lines would be ignored
        }
    }

    inFile.close();

    if(code.empty()||bits.empty()) 
    {
        return "ERROR: invalid file format";
    }

    // use existing decompress
    return decompress(bits, code);
}

string compress(string text)
{
    unordered_map<char,int> freq_vec = str_to_vec(text);
    Tree<char> comp_tree = huffman_encode(freq_vec);
    string ret_str, enc_str;

    unordered_map<char,string> huffman_codes;
    comp_tree.get_codes(comp_tree.root(),"",huffman_codes);

    for(auto pair : huffman_codes)
    {
        cout << pair.first << " " << freq_vec.at(pair.first) << " " << pair.second << endl;
    }

    for(char i : text)
    {
        enc_str += huffman_codes.at(i);
    }
    ret_str += enc_str + "\n" + decompress(enc_str,huffman_codes);
    return ret_str;
}

string compressToFile(string text)
{
    const string tableFilename = "EncodedTable.txt";
    ofstream outFile(tableFilename);
    if (!outFile) {
        cerr << "Failed to open output file." << endl;
        return "Failed to open file";
    }
    unordered_map<char,int> freq_vec = str_to_vec(text);
    Tree<char> comp_tree = huffman_encode(freq_vec);
    string ret_str, enc_str;

    unordered_map<char,string> huffman_codes;
    comp_tree.get_codes(comp_tree.root(),"",huffman_codes);

    //Display table to user
    for(auto pair : huffman_codes)
    {
        cout << pair.first << " " << freq_vec.at(pair.first) 
        << " " << pair.second << endl;
    }
    // Write out the table: character <space> code
    // Use e.g. ASCII integer for non-printables (whitespace, etc)
    for (auto& kv : huffman_codes) {
        unsigned char c = kv.first;
        outFile << int(c) << " " << kv.second << "\n";
    }
    // Separator
    outFile << "---\n";

    for(char i : text)
    {
        enc_str += huffman_codes.at(i);
    }
    // Write and display the bitstring
    cout << enc_str << "\n";
    outFile << enc_str << "\n";
    outFile.close();
    return decompressFromFile("EncodedTable.txt");
}

int main(void)
{
    string in_str;
    cout << "Please type a string: ";
    getline(cin,in_str);

    //Non file:
    //cout << "\n\nCompressed String: \n" << compress(in_str);

    //File:
    cout << "\n\nCompressed String: \n" << compressToFile(in_str);

    //From file (No new input):
    //cout << "String: \n" << decompressFromFile("EncodedTable.txt");
    return 0;
}
