#include "../Inc/person.hpp"

using namespace std;

Person::Person(string name, string admit_date, string department, int ust_card_num) :
                name{name}, admit_date{admit_date}, department{department}, ust_card_num{ust_card_num} {}

string Person::GetName() const {
    return name;
}

string Person::GetAdmit_date() const {
    return admit_date;
}

string Person::GetDepartment() const {
    return department;
}

int Person::GetUst_card_num() const {
    return ust_card_num;
}

void Person::ChangeName(string new_name) {
    name = new_name;
}

void Person::ChangeAdmit_date(string new_admit_date) {
    admit_date = new_admit_date;
}

void Person::ChangeDepartment(string new_department) {
    department = new_department;
}

void Person::ChangeUst_card_num(int new_ust_card_num) {
    ust_card_num = new_ust_card_num;
}

void Person::print_info() const {

}

Professor::Professor(string name, string admit_date, string department, int ust_card_num) : 
                    Person{name, admit_date, department, ust_card_num} {}

void Professor::print_info() const {

}

Student::Student(string name, string admit_date, string department, int ust_card_num, int year, float cga, float mcga, 
                    string status, Program *program, int total_num_program) :
                    Person{name, admit_date, department, ust_card_num}, year{year}, cga{cga}, mcga{mcga}, status{status},
                    program{program}, total_num_program{total_num_program} {}

Student::~Student() {
    if (program == nullptr)
        return;
    
    while (program != program->last_program()) 
        delete program->last_program();
    
    delete program;
}

int Student::GetYear() const {
    return year;
}

float Student::GetCga() const {
    return cga;
}
float Student::GetMcga() const {
    return mcga;
}

string Student::GetStatus() const {
    return status;
}

Program* Student::GetProgram(int index) const {
    if (total_num_program == 0 || total_num_program <= index)
        return nullptr;

    Program *ptr_program = program;
    int count = 0;
    while (count != index) {
        ptr_program = ptr_program->GetNext();
        count++;
    }

    return ptr_program;
}

int Student::GetTotal_num_program() const {
    return total_num_program;
}

void Student::change_year(int year) {
    this->year = year;
}

void Student::calculate_CGA(Semester *head) {
    Semester *ptr_sem = head;
    float result = 0.;
    int total_num_credit = 0;

    while (ptr_sem != nullptr) {
        // find grade*weight
        Course *ptr_course = ptr_sem->GetCourses();
        while (ptr_course != nullptr) {
            switch (ptr_course->GetGrade()[0]) {
                case 'A': 
                    result += ptr_course->GetCredits() * (grade::A + ptr_course->find_decimal_place_grade());
                    break;
                case 'B': 
                    result += ptr_course->GetCredits() * (grade::B + ptr_course->find_decimal_place_grade());
                    break;
                case 'C': 
                    result += ptr_course->GetCredits() * (grade::C + ptr_course->find_decimal_place_grade());
                    break;
                case 'D':
                    result += ptr_course->GetCredits();
                    break;
                default:
                    break;
            }
            ptr_course = ptr_course->GetNext();
        }
        
        // find total number of credit
        total_num_credit += ptr_sem->GetCCE();

        ptr_sem = ptr_sem->GetNext();
    }

    cga = result / total_num_credit;
}

void Student::calculate_MCGA(Semester *head) {
    
}

void Student::change_status(string latest_status) {
    status = latest_status;
}

void Student::change_total_num_program(int new_total_num_program) {
    total_num_program = new_total_num_program;
}

void Student::print_info() const{

}