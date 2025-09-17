#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "list.hpp"
#include <iostream> 
#include <cmath>

class Polynomial {
    int _level;
    Node* _coefficients;

    public:
        // Consturctors
        Polynomial();
        Polynomial(int level, Node* coefficients);
        Polynomial(const Polynomial& other);

        // Getters & Setters
        void set_level(int level);
        int get_level();

        void set_coefficients(Node* coeff);
        Node* get_coefficient();

        int get_coefficients_length();

        // Basic mathods
        double calc_polynomial_value(double parameter);
        void add_coeficient(double value);
        
        void polynomial_in();
        void polynomial_out();

        // Operators
        Polynomial operator + (Polynomial& polynomial);
        Polynomial operator - (Polynomial& polynomial);
        double operator()(double x);
        double operator [] (int index);
        Polynomial& operator = (const Polynomial& polynomial);
        Polynomial& operator ++ ();
        Polynomial& operator -- ();

        ~Polynomial();
};


#endif