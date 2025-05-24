#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>

class HashTable {
private:
    struct Node {
        double value;
        Node* next;
        Node(double val = -1) : value(val), next(nullptr) {}
    };

    static const int SIZE = 32;
    Node* table[SIZE];
    int count;
    int operations;
    bool isEmpty;

    int hash(double value) {
        std::string key = std::to_string(value);
        if (key.find('.') == std::string::npos) {
            key += ".0000";
        } else {
            while (key.length() < 10) key += '0';
        }

        int k1 = std::stoi(key.substr(1, 2)) * 2037;
        int k2 = std::stoi(key.substr(3, 2)) * 1249;
        int k3 = std::stoi(key.substr(6, 2)) * 2174;
        int k4 = std::stoi(key.substr(8)) * 1393;
        return (k1 + k2 + k3 + k4) % SIZE;
    }

public:
    HashTable() : count(0), isEmpty(true) {
        for (int i = 0; i < SIZE; ++i) {
            table[i] = new Node();
        }
    }

    ~HashTable() {
        clear();
        for (int i = 0; i < SIZE; ++i) {
            delete table[i];
        }
    }

    void insert(double key) {
        operations++;
        int index = hash(key);
        Node* current = table[index];
        // while (current->next) {
        //     if (current->next->value == key) return;
        //     current = current->next;
        //     operations++;
        // }
        Node* newNode = new Node(key);
        newNode->next = current->next;
        current->next = newNode;
        count++;
        isEmpty = false;
    }

    bool search(double key, Node** prevOut = nullptr) {
        operations++;
        int index = hash(key);
        Node* temp = table[index];
        Node* current = temp->next;
        while (current) {
            if (current->value == key) {
                if (prevOut) *prevOut = temp;
                return true;
            }
            temp = current;
            current = current->next;
            operations++;
        }
        return false;
    }

    void remove(double key) {
        operations++;
        if (isEmpty) return;
        Node* prev = nullptr;
        if (!search(key, &prev)) return;

        Node* toDelete = prev->next;
        prev->next = toDelete->next;
        delete toDelete;

        count--;
        isEmpty = (count == 0);
    }

    int Count() const { return count; }

    bool IsEmpty() const { return isEmpty; }

    int Operations() const { return operations; }

    void print() const {
        for (int i = 0; i < SIZE; ++i) {
            std::cout << i << ": ";
            Node* current = table[i];
            while (current) {
                std::cout << current->value << " -> ";
                current = current->next;
            }
            std::cout << "nullptr\n";
        }
    }

    void clear() {
        for (int i = 0; i < SIZE; ++i) {
            Node* current = table[i]->next;
            while (current) {
                Node* next = current->next;
                delete current;
                current = next;
            }
            table[i]->next = nullptr;
        }
        count = 0;
        isEmpty = true;
    }
};
