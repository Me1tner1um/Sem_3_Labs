#include "polynomial.hpp"
#include <iostream>

const int MAX_POLYNOMIALS = 100;

int main() {
    Polynomial* polynomials[MAX_POLYNOMIALS] = {nullptr};
    int polynomialCount = 0;
    int choice;

    do {
        std::cout << "\n=== Polynomial Calculator ===" << std::endl;
        std::cout << "1. Create new polynomial" << std::endl;
        std::cout << "2. Show all polynomials" << std::endl;
        std::cout << "3. Perform operations" << std::endl;
        std::cout << "4. Save to text file" << std::endl;
        std::cout << "5. Load from text file" << std::endl;
        std::cout << "6. Save to binary file" << std::endl;
        std::cout << "7. Load from binary file" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                if (polynomialCount >= MAX_POLYNOMIALS) {
                    std::cout << "Maximum number of polynomials reached (" << MAX_POLYNOMIALS << ")." << std::endl;
                    break;
                }
                
                Polynomial* poly = new Polynomial();
                std::cin >> *poly;
                polynomials[polynomialCount] = poly;
                polynomialCount++;
                std::cout << "Polynomial created: " << *poly << std::endl;
                break;
            }
            
            case 2: {
                if (polynomialCount == 0) {
                    std::cout << "No polynomials created yet." << std::endl;
                } else {
                    for (int i = 0; i < polynomialCount; i++) {
                        std::cout << i + 1 << ". " << *polynomials[i] << std::endl;
                    }
                }
                break;
            }
            
            case 3: {
                if (polynomialCount < 2) {
                    std::cout << "Need at least 2 polynomials for operations." << std::endl;
                    break;
                }
                
                int idx1, idx2;
                std::cout << "Select first polynomial (1-" << polynomialCount << "): ";
                std::cin >> idx1;
                std::cout << "Select second polynomial (1-" << polynomialCount << "): ";
                std::cin >> idx2;
                
                if (idx1 < 1 || idx1 > polynomialCount || idx2 < 1 || idx2 > polynomialCount) {
                    std::cout << "Invalid selection." << std::endl;
                    break;
                }
                
                Polynomial* poly1 = polynomials[idx1 - 1];
                Polynomial* poly2 = polynomials[idx2 - 1];
                Polynomial result;
                
                double parameter;
                std::cout << "Enter parameter value: ";
                std::cin >> parameter;
                
                std::cout << "\nPolynomial 1 value: " << (*poly1)(parameter) << std::endl;
                std::cout << "Polynomial 2 value: " << (*poly2)(parameter) << std::endl;
                
                std::cout << "\nSum: " << (*poly1 + *poly2) << std::endl;
                std::cout << "Difference: " << (*poly1 - *poly2) << std::endl;

                std::cout << "\nIncrementation:\n" << (++(*poly1)) << '\n' << (++(*poly2)) << std::endl;
                std::cout << "Decrementation:\n" << (--(--(*poly1))) << '\n' << (--(--(*poly2))) << std::endl;
                
                int index;
                std::cout << "Enter index for coefficient access: ";
                std::cin >> index;
                try {
                    std::cout << "Coefficient at index " << index << ": " << (*poly1)[index] << std::endl;
                } catch (const std::out_of_range& e) {
                    std::cout << "Error: " << e.what() << std::endl;
                }
                
                break;
            }
            
            case 4: {
                if (polynomialCount == 0) {
                    std::cout << "No polynomials to save." << std::endl;
                    break;
                }
                
                std::string filename;
                std::cout << "Enter filename: ";
                std::cin >> filename;
                
                std::ofstream file(filename);
                if (!file.is_open()) {
                    std::cout << "Cannot open file." << std::endl;
                    break;
                }
                
                // Save count first
                file << polynomialCount << std::endl;
                
                // Save each polynomial
                for (int i = 0; i < polynomialCount; i++) {
                    file << polynomials[i]->get_level() << std::endl;
                    
                    // Save coefficients
                    for (int j = 0; j <= polynomials[i]->get_level(); j++) {
                        try {
                            double coeff = (*polynomials[i])[j];
                            file << coeff << " ";
                        } catch (const std::out_of_range& e) {
                            file << "0 ";
                        }
                    }
                    file << std::endl;
                }
                
                std::cout << "Saved " << polynomialCount << " polynomials to " << filename << std::endl;
                break;
            }
            
            case 5: {
                std::string filename;
                std::cout << "Enter filename: ";
                std::cin >> filename;
                
                std::ifstream file(filename);
                if (!file.is_open()) {
                    std::cout << "Cannot open file." << std::endl;
                    break;
                }
                
                for (int i = 0; i < polynomialCount; i++) {
                    delete polynomials[i];
                    polynomials[i] = nullptr;
                }
                polynomialCount = 0;
                
                int count;
                file >> count;
                
                for (int i = 0; i < count && polynomialCount < MAX_POLYNOMIALS; i++) {
                    int level;
                    file >> level;
                    
                    Polynomial* poly = new Polynomial();
                    poly->set_level(level);
                    
                    for (int j = 0; j <= level; j++) {
                        double coeff;
                        file >> coeff;
                        poly->add_coeficient(coeff);
                    }
                    
                    polynomials[polynomialCount] = poly;
                    polynomialCount++;
                }
                
                std::cout << "Loaded " << polynomialCount << " polynomials from " << filename << std::endl;
                break;
            }
            
            case 6: {
                if (polynomialCount == 0) {
                    std::cout << "No polynomials to save." << std::endl;
                    break;
                }
                
                std::string filename;
                std::cout << "Enter filename: ";
                std::cin >> filename;
                
                std::ofstream file(filename, std::ios::binary);
                if (!file.is_open()) {
                    std::cout << "Cannot open file." << std::endl;
                    break;
                }
                
                // Save count first
                file.write(reinterpret_cast<const char*>(&polynomialCount), sizeof(polynomialCount));
                
                // Save each polynomial
                for (int i = 0; i < polynomialCount; i++) {
                    int level = polynomials[i]->get_level();
                    file.write(reinterpret_cast<const char*>(&level), sizeof(level));
                    
                    // Save coefficients
                    for (int j = 0; j <= level; j++) {
                        try {
                            double coeff = (*polynomials[i])[j];
                            file.write(reinterpret_cast<const char*>(&coeff), sizeof(coeff));
                        } catch (const std::out_of_range& e) {
                            double zero = 0.0;
                            file.write(reinterpret_cast<const char*>(&zero), sizeof(zero));
                        }
                    }
                }
                
                std::cout << "Saved " << polynomialCount << " polynomials to binary file " << filename << std::endl;
                break;
            }
            
            case 7: {
                std::string filename;
                std::cout << "Enter filename: ";
                std::cin >> filename;
                
                std::ifstream file(filename, std::ios::binary);
                if (!file.is_open()) {
                    std::cout << "Cannot open file." << std::endl;
                    break;
                }
                
                // Clear existing polynomials
                for (int i = 0; i < polynomialCount; i++) {
                    delete polynomials[i];
                    polynomials[i] = nullptr;
                }
                polynomialCount = 0;
                
                int count;
                file.read(reinterpret_cast<char*>(&count), sizeof(count));
                
                for (int i = 0; i < count && polynomialCount < MAX_POLYNOMIALS; i++) {
                    int level;
                    file.read(reinterpret_cast<char*>(&level), sizeof(level));
                    
                    Polynomial* poly = new Polynomial();
                    poly->set_level(level);
                    
                    for (int j = 0; j <= level; j++) {
                        double coeff;
                        file.read(reinterpret_cast<char*>(&coeff), sizeof(coeff));
                        poly->add_coeficient(coeff);
                    }
                    
                    polynomials[polynomialCount] = poly;
                    polynomialCount++;
                }
                
                std::cout << "Loaded " << polynomialCount << " polynomials from binary file " << filename << std::endl;
                break;
            }
            
            case 0:
                std::cout << "Sayonara" << std::endl;
                break;
                
            default:
                std::cout << "Invalid choice." << std::endl;
        }
    } while (choice != 0);

    for (int i = 0; i < polynomialCount; i++) {
        delete polynomials[i];
    }

    return 0;
}