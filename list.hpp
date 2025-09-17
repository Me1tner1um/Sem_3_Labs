#ifndef LIST_H
#define LIST_H


class Node {
    public:
        // Elements

        double value;
        Node* next;
        int index;

        // Constructor
        Node();
        Node(double value);
        Node(double value, unsigned int index);

        // Basic methods
        void add_node(double value);
        Node* insert_node(double value, int position);
        int get_length();
        Node* delete_node(int position);
        
        // Operators
        double operator[](int index);

        // Destructor
        ~Node();

};


#endif
