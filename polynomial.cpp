#include "polynomial.hpp"


//Constuctors
Polynomial::Polynomial(int level, Node* coefficients) {
    _level = level;
    _coefficients = coefficients;

    if (_coefficients != nullptr) {
        Node* current = _coefficients;
        int index = 0;
        while (current != nullptr) {
            current->index = index++;
            current = current->next;
        }
    }
}



Polynomial::Polynomial() : Polynomial(0, nullptr){}



Polynomial::Polynomial(const Polynomial& other) : _level(other._level), _coefficients(nullptr) {
    if (other._coefficients != nullptr) {
        Node* current_other = other._coefficients;
        Node* current_this = nullptr;
        
        while (current_other != nullptr) {
            if (_coefficients == nullptr) {
                _coefficients = new Node(current_other->value);
                _coefficients->index = current_other->index;
                current_this = _coefficients;
            } else {
                current_this->next = new Node(current_other->value);
                current_this->next->index = current_other->index;
                current_this = current_this->next;
            }
            current_other = current_other->next;
        }
    }
}





// Getters & Setters
void Polynomial::set_level(int level) {
    _level = level;
}



int Polynomial::get_level() {
    return _level;
}



void Polynomial::set_coefficients(Node* coeff) {
    _coefficients = coeff;
}



Node* Polynomial::get_coefficient() {
    return _coefficients;
}



int Polynomial::get_coefficients_length() {
    if (_coefficients == nullptr) return 0;
    return _coefficients->get_length();
}





// Basic methods
double Polynomial::calc_polynomial_value(double parameter){
    Node* head = _coefficients;
    double polynomial_value = 0;
    while (head != nullptr) {
        polynomial_value += pow(parameter, head->index) * head->value;
        head = head->next;
    } 

    return polynomial_value;
}



void Polynomial::polynomial_in() {
    Polynomial* polynomial = this;
    int level = 0;
    double coefficient = 0;

    std::cout << "Enter the level of polynomial:\n";
    std::cin >> level;

    polynomial->set_level(level);

    std::cout << "\nEnter coefficients:\n";
    for (int i = 0; i <= level; i++) {
        std::cin >> coefficient;
        polynomial->add_coeficient(coefficient);
    }
    
    if (_coefficients != nullptr && _coefficients->get_length() != level + 1) {
        _level = _coefficients->get_length() - 1;
    }
}



void Polynomial::polynomial_out() {
    Node* head = _coefficients;
    bool first = true;
    while (head != nullptr) {
        if (head->value != 0) {
            if (!first && head->value > 0) std::cout << '+';
            std::cout << head->value;
            if (head->index > 0) std::cout << "x^" << head->index;
            first = false;
        }
        head = head->next;
    }
    std::cout << std::endl;
}



void Polynomial::add_coeficient(double value) {
    if (_coefficients == nullptr) {
        _coefficients = new Node(value, 0);
    } else {
        _coefficients->add_node(value);
        if (_coefficients->get_length() - 1 > _level) {
            _level = _coefficients->get_length() - 1;
        }
    }
}





// Destructor
Polynomial::~Polynomial() {
    delete _coefficients;
    _coefficients = nullptr;
}


// Operatros
// Sum
Polynomial Polynomial::operator + (Polynomial& polynomial) {
    int max_level = std::max(_level, polynomial.get_level());
    Polynomial result;
    result.set_level(max_level);
    
    Node* p1 = _coefficients;
    Node* p2 = polynomial.get_coefficient();
    
    for (int i = 0; i <= max_level; i++) {
        double coeff1 = 0, coeff2 = 0;
        
        if (p1 != nullptr && p1->index == i) {
            coeff1 = p1->value;
            p1 = p1->next;
        }
        if (p2 != nullptr && p2->index == i) {
            coeff2 = p2->value;
            p2 = p2->next;
        }
        
        result.add_coeficient(coeff1 + coeff2);
    }
    
    return result;
}



// Sub
Polynomial Polynomial::operator - (Polynomial& polynomial) {
    int max_level = std::max(_level, polynomial.get_level());
    Polynomial result;
    result.set_level(max_level);
    
    Node* p1 = _coefficients;
    Node* p2 = polynomial.get_coefficient();
    
    for (int i = 0; i <= max_level; i++) {
        double coeff1 = 0, coeff2 = 0;
        
        if (p1 != nullptr && p1->index == i) {
            coeff1 = p1->value;
            p1 = p1->next;
        }
        
        if (p2 != nullptr && p2->index == i) {
            coeff2 = p2->value;
            p2 = p2->next;
        }
        
        result.add_coeficient(coeff1 - coeff2);
    }
    
    return result;
}

// Method
double Polynomial::operator()(double x) {
    return this->calc_polynomial_value(x);
}



// Index
double Polynomial::operator [] (int index) {
    if (_coefficients == nullptr) throw std::out_of_range("Polynomial has no coefficients");
    return (*_coefficients)[index];
}



// Equel
Polynomial& Polynomial::operator = (const Polynomial& polynomial) {
    if (this != &polynomial) {
        if (_coefficients != nullptr) {
            delete _coefficients;
            _coefficients = nullptr;
        }
        
        _level = polynomial._level;
        
        if (polynomial._coefficients != nullptr) {
            Node* current_other = polynomial._coefficients;
            Node* current_this = nullptr;
            
            while (current_other != nullptr) {
                if (_coefficients == nullptr) {
                    _coefficients = new Node(current_other->value);
                    _coefficients->index = current_other->index;
                    current_this = _coefficients;
                } else {
                    current_this->next = new Node(current_other->value);
                    current_this->next->index = current_other->index;
                    current_this = current_this->next;
                }
                current_other = current_other->next;
            }
        }
    }
    return *this;
}


// Increment
Polynomial& Polynomial::operator ++ () {
    if (_coefficients == nullptr) {
        _coefficients = new Node(0.0, 0);
        _level = 0;
    } else {
        _coefficients = _coefficients->insert_node(0.0, 0);
        _level++;
    }
    return *this;
}



// Decrement
Polynomial& Polynomial::operator -- () {
    if (_coefficients == nullptr || _level == 0) {
        return *this;
    }
    _coefficients = _coefficients->delete_node(0);
    _level--;
    return *this;
}