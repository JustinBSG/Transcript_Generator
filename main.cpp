#include "functions.h"

int main() {
    while (1) {
        int option = menu();
        switch (option) {
            case 1:
                
                break;
            case 2:
                readcsv();
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                std::cout << "Bye!!" << std::endl;
                return 0;
        }
    }
}