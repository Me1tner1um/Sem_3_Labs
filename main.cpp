#include "polynomial.hpp"

int main() {

    Polynomial* poly1 = new Polynomial();
    Polynomial* poly2 = new Polynomial();
    Polynomial* result = new Polynomial();
    
    int parameter;
    int index;

    std::cout << "Enter polynomial 1:\n";
    poly1->polynomial_in();

    std::cout << "\nEnter polynomial 2:\n";
    poly2->polynomial_in();

    std::cout << "\nPolynomials:\n";
    std::cout << "1. ";
    poly1->polynomial_out();

    std::cout << "2. ";
    poly2->polynomial_out();

    std::cout << "\nEnter the parameter:\n";
    std::cin >> parameter;

    std::cout << "\nPolynomial value with parameter: " << (*poly1)(parameter) << '\n';
    std::cout << "\nPolynomial value with parameter: " << (*poly2)(parameter) << '\n';

    std::cout << "\nSum:\n";
    *result = *poly1 + *poly2;
    result->polynomial_out();

    std::cout << "\nSub:\n";
    *result = *poly1 - *poly2;
    result->polynomial_out();

    std::cout << "\nEnter index for first polynomial:\n";
    std::cin >> index;

    std::cout << "Value of level: " << (*poly1)[index] << '\n';

    std::cout << "\nIncrementation:\n"; 
    std::cout << "1. ";
    (++(*poly1)).polynomial_out();
    std::cout << "2. ";
    (++(*poly2)).polynomial_out();

    std::cout << "\nDecrementation:\n";
    std::cout << "1. ";
    (--(*poly1)).polynomial_out();
    std::cout << "2. ";
    (--(*poly2)).polynomial_out();

    delete poly1;
    delete poly2;
    delete result;
}