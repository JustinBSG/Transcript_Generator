#include "functions.h"

int main() {
    Student *student = nullptr;
    Program *program = nullptr;
    Semester *semester = nullptr;
    char address[100] = "";
    while (1) {
        int option = menu();
        switch (option) {
            case 1:
                insert_csv();
                break;
            case 2:
                read_csv(student, program, semester, address);
                break;
            case 3:
                modify_csv(student, program, semester, address);
                break;
            case 4:
                print_all(student, program, semester);
                break;
            case 5:
                delete_all_dynamic(student, program, semester);
                std::cout << "Bye!!" << std::endl;
                return 0;
            case 6:
                testing(student, program, semester);
                return 0;
        }
    }
}