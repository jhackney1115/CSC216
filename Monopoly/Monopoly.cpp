#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

class Node {
public:
    std::string data;
    Node* next;

    Node(const std::string& value) : data(value), next(nullptr) {}
};

class CircularLinkedList {
private:
    Node* tail;
    Node* current;

public:
    CircularLinkedList() : tail(nullptr), current(nullptr) {
        std::srand(std::time(nullptr)); // Seed for dice rolls
    }

    void append(const std::string& value) {
        Node* newNode = new Node(value);
        if (!tail) {
            tail = newNode;
            tail->next = tail; // Point to itself
        } else {
            newNode->next = tail->next;
            tail->next = newNode;
            tail = newNode;
        }
        current = tail->next; // Ensure current starts at the first node
    }

    std::string getCurrentData() {
        return current ? current->data : "List is empty";
    }

    void stepForward() {
        if (current) {
            current = current->next;
        }
    }

    void rollDiceAndMove() {
        int roll1 = (std::rand() % 6) + 1;
        int roll2 = (std::rand() % 6) + 1;
        int steps = roll1 + roll2;
        std::cout << "Rolled: " << roll1 << " + " << roll2 << " = " << steps << "\n";
        for (int i = 0; i < steps; ++i) {
            stepForward();
        }
    }

    void display() {
        if (!tail) return;
        Node* temp = tail->next;
        do {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        } while (temp != tail->next);
        std::cout << "(Back to " << tail->next->data << ")" << std::endl;
    }

    ~CircularLinkedList() {
        if (!tail) return;
        Node* temp = tail->next;
        Node* nextNode;
        do {
            nextNode = temp->next;
            delete temp;
            temp = nextNode;
        } while (temp != tail->next);
        tail = nullptr;
    }
};

int main() {
    CircularLinkedList board;
    std::string monopolySpaces[] = {"GO", "Mediterranean Avenue", "Community Chest", "Baltic Avenue",
                                    "Income Tax", "Reading Railroad", "Oriental Avenue", "Chance",
                                    "Vermont Avenue", "Connecticut Avenue", "Jail", "St. Charles Place",
                                    "Electric Company", "States Avenue", "Virginia Avenue", "Pennsylvania Railroad",
                                    "St. James Place", "Community Chest", "Tennessee Avenue", "New York Avenue",
                                    "Free Parking", "Kentucky Avenue", "Chance", "Indiana Avenue",
                                    "Illinois Avenue", "B&O Railroad", "Atlantic Avenue", "Ventnor Avenue",
                                    "Water Works", "Marvin Gardens", "Go to Jail", "Pacific Avenue",
                                    "North Carolina Avenue", "Community Chest", "Pennsylvania Avenue", "Short Line Railroad",
                                    "Chance", "Park Place", "Luxury Tax", "Boardwalk"};

    for (const auto& space : monopolySpaces) {
        board.append(space);
    }

    board.display();

    std::cout << "\nStepping through the board:" << std::endl;
    for (int i = 0; i < 44; ++i) {  // More than 40 to ensure looping
        std::cout << board.getCurrentData() << std::endl;
        board.stepForward();
    }

    std::cout << "\nRolling dice and moving:" << std::endl;
    for (int i = 0; i < 5; ++i) {  // Roll dice a few times
        board.rollDiceAndMove();
        std::cout << "Landed on: " << board.getCurrentData() << "\n";
    }

    return 0;
}
