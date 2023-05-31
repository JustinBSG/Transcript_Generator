#include "functions.h"

int menu () {
    int option;
    std::cout << "************************* Transcript Generator ************************" << std::endl;
    std::cout << "=======================================================================" << std::endl;
    std::cout << "Here are operations that you can choose:" << std::endl;
    std::cout << "1: Input data by yourself and form a CSV file." << std::endl;
    std::cout << "2: Input data from CSV file." << std::endl;
    std::cout << "3: Modify data that inside CSV file." << std::endl;
    std::cout << "4: Generate transcript into terminal." << std::endl;
    std::cout << "5: Leave." << std::endl;
    std::cout << "What operation that you want to choose(1-5): ";
    std::cin >> option;
    while (option > 5 || option < 1) {
        std::cout << "Please input valid choice: ";
        std::cin >> option;
    }
    return option;
}