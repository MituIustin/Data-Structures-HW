#include <iostream>

using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int value) {
        data = value;
        next = nullptr;
    }
};

class CircularList {
private:
    Node* head;

public:
    CircularList() {
        head = nullptr;
    }

    ~CircularList() {
    }

    void insert(int value) {
        Node* newNode = new Node(value);

        if (head == nullptr) {
            head = newNode;
            head->next = head;
        } else {
            Node* current = head;
            while (current->next != head) {
                current = current->next;
            }
            current->next = newNode;
            newNode->next = head;
        }
    }

    void print() {
        if (head == nullptr) {
            cout << "List is empty." << endl;
            return;
        }

        Node* current = head;
        do {
            cout << current->data << " ";
            current = current->next;
        } while (current != head);
        cout << endl;
    }

    void remove(Node* node) {
        if (head == nullptr) {
            return;
        }

        Node* current = head;
        while (current->next != node) {
            current = current->next;
        }

        if (head == node) {
            if (head->next == head) {
                delete head;
                head = nullptr;
            } else {
                current->next = head->next;
                delete head;
                head = current->next;
            }
        } else {
            current->next = node->next;
            delete node;
        }
    }

    void findThird(Node* node) {
        for (int i = 0; i < 3; i++) {
            node = node->next;
        }
    }

    Node* findLastSurvivor(int startNode) {
        if (head == nullptr) {
            return nullptr;
        }

        Node* current = head;
        Node* prev = nullptr;

        while (current->data != startNode) {
            prev = current;
            current = current->next;
        }

        while (current->next != current) {
            Node* thirdNode = current;
            findThird(thirdNode);

            if (prev != nullptr) {
                prev->next = current->next;
            } else {
                head = current->next;
            }

            Node* temp = current;
            current = current->next;
            delete temp;

            prev = thirdNode;
        }

        return current;
    }

};
int main() {
    CircularList clist;

    clist.insert(1);
    clist.insert(2);
    clist.insert(3);
    clist.insert(4);
    clist.insert(5);

    cout << "Initial List: ";
    clist.print();

    Node* lastSurvivor = clist.findLastSurvivor(1);
    cout << "Last survivor: " << lastSurvivor->data << endl;

}
