#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

template <typename T>
class Node {
public:
    T data;
    Node* next;
    Node* prev;

    Node(const T& value) : data(value), next(nullptr), prev(nullptr) 
    {}
    //These are to handle warnings that were annoying me. 
    //They shouldn't be necessary here as we won't need to copy 
    //the linked list
    Node(const Node&) = delete;
    Node& operator=(const Node&) = delete;
};

template <typename T>
class CircularLinkedList {
private:
    Node<T>* tail;
    Node<T>* current;

    void clear() {
        if (!tail) return;
        Node<T>* temp = tail->next;
        Node<T>* nextNode;
        do {
            nextNode = temp->next;
            delete temp;
            temp = nextNode;
        } while (temp != tail->next);
        tail = nullptr;
    }

public:
    CircularLinkedList() : tail(nullptr), current(nullptr) {
        srand(static_cast<unsigned>(time(nullptr))); 
        // Seed for dice rolls
    }

    //These also help mitigate the warnings
    CircularLinkedList(const CircularLinkedList& other) : 
        tail(nullptr), current(nullptr) {
        if (!other.tail) return;
        Node<T>* temp = other.tail->next;
        do {
            append(temp->data);
            temp = temp->next;
        } while (temp != other.tail->next);
    }

    CircularLinkedList& operator=(const CircularLinkedList& other) {
        if (this == &other) return *this;
        clear();
        if (!other.tail) return *this;
        Node<T>* temp = other.tail->next;
        do {
            append(temp->data);
            temp = temp->next;
        } while (temp != other.tail->next);
        return *this;
    }

    ~CircularLinkedList() {
        clear();
    }


    void prepend(const T& value) {
        insertAt(value, 0);
    }

    void append(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (!tail) {
            tail = newNode;
            tail->next = tail;
            tail->prev = tail;
        } else {
            newNode->next = tail->next;
            newNode->prev = tail;
            tail->next->prev = newNode;
            tail->next = newNode;
            tail = newNode;
        }
        current = tail->next;
    }

    void insertAt(const T& value, int position) {
        Node<T>* newNode = new Node<T>(value);
        if (!tail) {
            tail = newNode;
            tail->next = tail;
            tail->prev = tail;
        } else {
            Node<T>* temp = tail->next;
            for (int i = 0; i < position && temp != tail; i++) {
                temp = temp->next;
            }
            newNode->next = temp;
            newNode->prev = temp->prev;
            temp->prev->next = newNode;
            temp->prev = newNode;
            if (temp == tail->next && position == 0) {
                tail->next = newNode;
            }
            if (temp == tail) {
                tail = newNode;
            }
        }
        current = tail->next;
    }

    void deleteAt(int position) {
        if (!tail) return;
        Node<T>* temp = tail->next;
        for (int i = 0; i < position && temp != tail; i++) {
            temp = temp->next;
        }
        if (temp == tail->next && temp == tail) {
            tail = nullptr;
        } else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            if (temp == tail->next) {
                tail->next = temp->next;
            }
            if (temp == tail) {
                tail = temp->prev;
            }
        }
        delete temp;
        current = tail ? tail->next : nullptr;
    }

    int size() {
        if (!tail) return 0;
        int count = 0;
        Node<T>* temp = tail->next;
        do {
            count++;
            temp = temp->next;
        } while (temp != tail->next);
        return count;
    }

    T getCurrentData() {
        return current ? current->data : T();
    }

    void stepForward() {
        if (current) {
            current = current->next;
        }
    }

    void stepBackward() {
        if (current) {
            current = current->prev;
        }
    }

    void rollDiceAndMove() {
        int roll1 = (rand() % 6) + 1;
        int roll2 = (rand() % 6) + 1;
        int steps = roll1 + roll2;
        cout << "Rolled: " << roll1 << " + " << roll2 << " = " << 
            steps << "\n";
        for (int i = 0; i < steps; ++i) {
            stepForward();
        }
    }

    void display() {
        if (!tail) return;
        Node<T>* temp = tail->next;
        do {
            cout << temp->data << " -> ";
            temp = temp->next;
        } while (temp != tail->next);
        cout << "(Back to " << tail->next->data << ")" << endl;
    }
};

int main() {
    CircularLinkedList<string> board;
    string monopolySpaces[] = {"GO", "Mediterranean Avenue", 
        "Community Chest", "Baltic Avenue",
        "Income Tax", "Reading Railroad", "Oriental Avenue", "Chance",
        "Vermont Avenue", "Connecticut Avenue", "Jail", 
        "St. CharlesPlace","Electric Company", "States Avenue", 
        "Virginia Avenue", "Pennsylvania Railroad",
        "St. James Place", "Community Chest", "Tennessee Avenue", 
        "New York Avenue","Free Parking", "Kentucky Avenue", 
        "Chance", "Indiana Avenue", "Illinois Avenue",
        "B&O Railroad", "Atlantic Avenue", "Ventnor Avenue",
        "Water Works", "Marvin Gardens", "Go to Jail",
        "Pacific Avenue", "North Carolina Avenue", "Community Chest", 
        "Pennsylvania Avenue", "Short Line Railroad",
        "Chance", "Park Place", "Luxury Tax", "Boardwalk"};
        //This allows for them to be in a more compact space than
        //writing all of them on separate lines
    for (const auto& space : monopolySpaces) {
        board.append(space);
    }

    board.display();

    cout << "\nRolling dice and moving:" << endl;
    for (int i = 0; i < 5; ++i) {
        board.rollDiceAndMove();
        cout << "Landed on: " << board.getCurrentData() << "\n";
    }

    return 0;
}
