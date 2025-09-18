#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "list.hpp"
#include <iostream> 
#include <cmath>
#include <fstream>
#include <stdexcept>

class Polynomial {
    int _level;
    Node* _coefficients;

    public:
        // Constructors
        Polynomial();
        Polynomial(int level, Node* coefficients);
        Polynomial(const Polynomial& other);

        // Getters & Setters
        void set_level(int level);
        int get_level();

        void set_coefficients(Node* coeff);
        Node* get_coefficient();

        int get_coefficients_length();

        // Basic methods
        double calc_polynomial_value(double parameter);
        void add_coeficient(double value);
        
        void polynomial_in();
        void polynomial_out();

        // File operations
        void save_to_text_file(const std::string& filename) const;
        void load_from_text_file(const std::string& filename);
        void save_to_binary_file(const std::string& filename) const;
        void load_from_binary_file(const std::string& filename);

        // Operators
        Polynomial operator + (Polynomial& polynomial);
        Polynomial operator - (Polynomial& polynomial);
        double operator()(double x);
        double operator [] (int index);
        Polynomial& operator = (const Polynomial& polynomial);
        Polynomial& operator ++ ();
        Polynomial& operator -- ();

        friend std::ostream& operator << (std::ostream& os, const Polynomial& polynomial);
        friend std::istream& operator >> (std::istream& is, Polynomial& polynomial);

        ~Polynomial();
};

#endif