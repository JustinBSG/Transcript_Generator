#include "functions.h"

int main() {
    Student *student = nullptr;
    Program *program = nullptr;
    Course *course = nullptr;
    Semester *semester = nullptr;
    
    while (1) {
        int option = menu();
        switch (option) {
            case 1:
                
                break;
            case 2:
                read_csv(student, program, semester);
                break;
            case 3:
                modify_csv(student, program, semester);
                break;
            case 4:
                print_all(student, program, semester);
                break;
            case 5:
                delete_all_dynamic(student, program, semester);
                std::cout << "Bye!!" << std::endl;
                return 0;
            case 6:
                testing(student, program, course, semester);
                return 0;
        }
    }
}