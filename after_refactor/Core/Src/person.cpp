#include "../Inc/person.hpp"

#include <stdexcept>

Person::Person(std::string name, std::string admit_date, std::string department, int ust_card_num)
    : name{name}, admit_date{admit_date}, department{department}, ust_card_num{ust_card_num} {}

std::string Person::get_name() const { return name; }

std::string Person::get_admit_date() const { return admit_date; }

std::string Person::get_department() const { return department; }

int Person::get_ust_card_num() const { return ust_card_num; }

void Person::change_name(const std::string& other_name) { name = other_name; }

void Person::change_admit_date(const std::string& other_admit_date) {
  admit_date = other_admit_date;
}

void Person::change_department(const std::string& other_department) {
  department = other_department;
}

void Person::change_ust_card_num(const int& other_ust_card_num) {
  ust_card_num = other_ust_card_num;
}

Professor::Professor(std::string name, std::string admit_date, std::string department,
                     int ust_card_num)
    : Person{name, admit_date, department, ust_card_num} {}

void Professor::print_test() const {
  std::cout << "Professor class object:" << std::endl;
  std::cout << "std::string name: " << name << std::endl;
  std::cout << "std::string admit_date: " << admit_date << std::endl;
  std::cout << "std::string department: " << department << std::endl;
  std::cout << "int ust_card_num: " << ust_card_num << std::endl;
}

Student::Student(std::string name, std::string admit_date, std::string department, int ust_card_num,
                 int year, Status_Program status)
    : Person{name, admit_date, department, ust_card_num}, year{year}, status{status} {}

int Student::get_year() const { return year; }

std::string Student::get_status() const {
  switch (status) {
    case Active_In_Program:
      return "Active In Program";
    case Withdraw_Program:
      return "Withdraw Program";
    case Suspend_Program:
      return "Suspend Program";
    default:
      return "Unknown Status";
  }
}

BST<Major>& Student::get_majors() { return majors; }

BST<Minor>& Student::get_minors() { return minors; }

void Student::change_year(const int& other_year) { year = other_year; }

void Student::change_status(const Status_Program& other_status) { status = other_status; }

void Student::insert_major(const Major& other_major) { majors.insert(other_major); }

void Student::remove_major(const std::string& other_major_name) {
  majors.remove(majors.find_BSTnode(other_major_name)->data);
}

void Student::insert_minor(const Minor& other_minor) { minors.insert(other_minor); }

void Student::remove_minor(const std::string& other_minor_name) {
  minors.remove(minors.find_BSTnode(other_minor_name)->data);
}

void Student::print_test() const {
  std::cout << "Student class object:" << std::endl;
  std::cout << "std::string name: " << name << std::endl;
  std::cout << "std::string admit_date: " << admit_date << std::endl;
  std::cout << "std::string department: " << department << std::endl;
  std::cout << "int ust_card_num: " << ust_card_num << std::endl;
  std::cout << "int year: " << year << std::endl;
  std::cout << "Status_Program: " << get_status() << std::endl;
  std::cout << "BST<Major> majors: " << std::endl;
  std::cout << "the number of majors: " << majors.size() << std::endl;
  for (int i = 1; i <= majors.size(); i++) {
    std::cout << "This is " << i << "th largest node." << std::endl;
    Major* temp = &(majors.find_kth_largest_node(i)->data);
    temp->print_test();
    std::cout << std::endl;
  }
  std::cout << "BST<Minor> minors: " << std::endl;
  std::cout << "the number of minors: " << minors.size() << std::endl;
  for (int i = 1; i <= minors.size(); i++) {
    std::cout << "This is " << i << "th largest node." << std::endl;
    Minor* temp = &(minors.find_kth_largest_node(i)->data);
    temp->print_test();
    if (i != minors.size())
      std::cout << std::endl;
  }
}