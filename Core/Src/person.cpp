#include "../Inc/person.hpp"

using namespace std;

ostream& operator<<(ostream& os, const Person& data) {
  // TODO: following format of old version
}

Person::Person(string name, string admit_date, string department, int ust_card_num)
    : name{name}, admit_date{admit_date}, department{department} {}

string Person::get_name() const { return name; }

string Person::get_admit_date() const { return admit_date; }

string Person::get_department() const { return department; }

int Person::get_ust_card_num() const { return ust_card_num; }

void Person::change_name(const string& other_name) { name = other_name; }

void Person::change_admit_date(const string& other_admit_date) {
  admit_date = other_admit_date;
}

void Person::change_department(const string& other_department) {
  department = other_department;
}

void Person::change_ust_card_num(const int& other_ust_card_num) {
  ust_card_num = other_ust_card_num;
}

ostream& operator<<(ostream& os, const Professor& data) {
  // TODO: following format of old version
}

Professor::Professor(string name, string admit_date, string department,
                     int ust_card_num)
    : Person{name, admit_date, department, ust_card_num} {}

ostream& operator<<(ostream& os, const Student& data) {
  // TODO: following format of old version
}

Student::Student(string name, string admit_date, string department, int ust_card_num,
                 int year, float cga, float mcga, string status,
                 BST<Semester>* semesters)
    : Person{name, admit_date, department, ust_card_num},
      year{year},
      cga{cga},
      mcga{mcga},
      status{status},
      semesters{semesters} {}

Student::~Student() { delete semesters; }

int Student::get_year() const { return year; }

float Student::get_CGA() const { return cga; }

float Student::get_MCGA() const { return mcga; }

string Student::get_status() const { return status; }

BST<Major>& Student::get_majors() { return majors; }

BST<Minor>& Student::get_minors() { return minors; }

BST<Semester>* Student::get_semesters() { return semesters; }

void Student::change_year(const int& other_year) { year = other_year; }

void Student::change_status(const string& other_status) { status = other_status; }

void Student::insert_major(const Major& other) { majors.insert(other); }

void Student::remove_major(const string& name_major) {
  Major temp{name_major};
  majors.remove(temp);
}

void Student::insert_minor(const Minor& other) { minors.insert(other); }

void Student::remove_minor(const string& name_minor) {
  Minor temp{name_minor};
  minors.remove(temp);
}

void Student::insert_semesters(BST<Semester>* other_semesters) {
  if (other_semesters == nullptr)
    return;
  else
    semesters = other_semesters;
}