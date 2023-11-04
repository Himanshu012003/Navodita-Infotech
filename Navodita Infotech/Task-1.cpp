#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
};

class LinkedList {
public:
    LinkedList() : head(nullptr) {}

    // Insert a node at the beginning of the linked list
    void insert(int data) {
        Node* newNode = new Node;
        newNode->data = data;
        newNode->next = head;
        head = newNode;
    }

    // Print the linked list
    void print() {
        Node* current = head;
        while (current) {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "nullptr" << endl;
    }

private:
    Node* head;
};

int main() {
    LinkedList myList;

    // Insert some data into the linked list
    myList.insert(5);
    myList.insert(10);
    myList.insert(15);

    // Visualize the linked list
    myList.print();

    return 0;
}
