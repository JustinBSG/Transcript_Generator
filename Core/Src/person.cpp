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
                    string status, Program **program, int total_num_program) :
                    Person{name, admit_date, department, ust_card_num}, year{year}, cga{cga}, mcga{mcga}, status{status},
                    program{program}, total_num_program{total_num_program} {}

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
    return program[index];
}

int Student::GetTotal_num_program() const {
    return total_num_program;
}

void Student::change_year(int year) {
    this->year = year;
}

void Student::calculate_CGA(Semester *head) {
    
}

void Student::calculate_MCGA(Semester *head) {
    
}

void Student::change_status(string latest_status) {
    status = latest_status;
}

void Student::add_new_program(Program *latest_program) {
    Program **temp = new Program*[++total_num_program];
    for (int i = 0; i < total_num_program-1; i++) 
        temp[i] = new Program(*program[i]);
    temp[total_num_program-1] = new Program(*latest_program);
    for (int i = 0; i < total_num_program-1; i++) 
        delete program[i];
    delete program;
    program = temp;
}

void Student::change_total_num_program(int new_total_num_program) {
    total_num_program = new_total_num_program;
}

void Student::print_info() const{

}