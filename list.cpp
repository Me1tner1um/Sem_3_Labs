#include "list.hpp"
#include <stdexcept>

// Constructors
Node::Node(double value, unsigned int index) : value(value), next(nullptr), index(index) {}

Node::Node(double value) : Node(value, 0) {};

Node::Node() : Node(0, 0) {}

//Basic methods
void Node::add_node(double value) {
    Node* current = this;
    Node* new_node = new Node(value);

    while (current->next != nullptr) current = current->next;

    current->next = new_node;
    new_node->index = current->index + 1;
}

int Node::get_length() {
    int length = 0;
    Node* current = this;
    while (current != nullptr) {
        current = current->next;
        length++;
    }
    return length;
}

Node* Node::insert_node(double value, int position) {
    if (position < 0) {
        throw std::out_of_range("Position cannot be negative");
    }

    if (position == 0) {
        Node* new_head = new Node(value, 0);
        new_head->next = this;

        Node* current = new_head->next;
        int idx = 1;
        while (current != nullptr) {
            current->index = idx++;
            current = current->next;
        }
        return new_head;
    }

    Node* current = this;
    int current_index = 0;

    while (current_index < position - 1 && current->next != nullptr) {
        current = current->next;
        current_index++;
    }

    if (current->next == nullptr) {
        current->add_node(value);
        return this;
    }

    Node* new_node = new Node(value, position);
    new_node->next = current->next;
    current->next = new_node;

    Node* temp = new_node->next;
    int idx = position + 1;
    while (temp != nullptr) {
        temp->index = idx++;
        temp = temp->next;
    }

    return this;
}

Node* Node::delete_node(int position) {
    if (position < 0) {
        throw std::out_of_range("Position cannot be negative");
    }

    if (position == 0) {
        Node* new_head = this->next;
        this->next = nullptr;

        Node* current = new_head;
        int new_index = 0;
        while (current != nullptr) {
            current->index = new_index++;
            current = current->next;
        }

        delete this;
        return new_head;
    }

    Node* current = this;
    int current_index = 0;

    while (current_index < position - 1 && current->next != nullptr) {
        current = current->next;
        current_index++;
    }

    if (current->next == nullptr) {
        throw std::out_of_range("Position out of range");
    }

    Node* node_to_delete = current->next;
    current->next = node_to_delete->next;
    node_to_delete->next = nullptr;

    Node* temp = current->next;
    while (temp != nullptr) {
        temp->index = (current_index + 1);
        current_index++;
        temp = temp->next;
    }

    delete node_to_delete;
    return this;
}

// Operatrors
double Node::operator[](int index) {
    if (index < 0 || index >= this->get_length()) throw std::out_of_range("Position out of range");

    Node* temp = this;
    while (temp != nullptr) {
        if (temp->index == index) {
            return temp->value;
        }
        temp = temp->next;
    }
    throw std::out_of_range("Position not found"); 
}

// Destructor (оставляем, но он будет корректно работать после инициализации next)
Node::~Node() {
    Node* current = next;
    while (current != nullptr) {
        Node* next_node = current->next;
        current->next = nullptr;
        delete current;
        current = next_node;
    }
}