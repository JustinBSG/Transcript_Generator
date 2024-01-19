#include "../Inc/person.hpp"

using namespace std;

ostream& operator<<(ostream& os, const Person& data) {
  return os << "Name: " << data.name << endl
            << "Admit Date: " << data.admit_date << endl
            << "Department: " << data.department << endl
            << "UST Card Number: " << data.ust_card_num;
}

Person::Person(string name, string admit_date, string department, int ust_card_num)
    : name{name},
      admit_date{admit_date},
      department{department},
      ust_card_num{ust_card_num} {}

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
  return os << dynamic_cast<const Person&>(data);
}

Professor::Professor(string name, string admit_date, string department,
                     int ust_card_num)
    : Person{name, admit_date, department, ust_card_num} {}

ostream& operator<<(ostream& os, const Student& data) {
  os << "Student: " << endl
     << dynamic_cast<const Person&>(data) << endl
     << "Year: " << data.year << endl
     << "CGA: " << data.cga << endl
     << "MCGA: " << data.mcga << endl
     << "Status: " << data.status << endl
     << endl;
  int count_majors = 0, count_minors = 0;
  while (count_majors < data.majors.size()) {
    os << "Major" << count_majors + 1 << ":" << endl;
    Major temp =
      data.majors.find_kth_largest_node(data.majors.size() - count_majors)->data;
    os << temp << endl;
    count_majors++;
  }
  os << endl;
  while (count_minors < data.minors.size()) {
    os << "Minor" << count_minors + 1 << ":" << endl;
    Minor temp =
      data.minors.find_kth_largest_node(data.minors.size() - count_minors)->data;
    os << temp << endl;
    count_minors++;
  }
  os << endl;
  os << "Semesters:" << endl;
  if (data.semesters != nullptr) {
    int count_semester = 0;
    while (count_semester < data.get_semesters()->size()) {
      Semester temp =
        data.get_semesters()
          ->find_kth_largest_node(data.get_semesters()->size() - count_semester)
          ->data;
      os << temp.get_period() << ":" << endl;
      int count_course = 0;
      while (count_course < temp.get_courses().size()) {
        Course temp_course = temp.get_courses().find_kth_largest_node(
          temp.get_courses().size() - count_course)->data;
        os << "Course Code: " << temp_course.get_code() << endl
           << "Course Title:" << temp_course.get_title() << endl
           << "No. of Credit: " << temp_course.get_credits()
           << endl
           << "Grade: " << temp_course.get_grade_str() << endl;
        count_course++;
      }
      os << "TGA: " << temp.get_tga() << endl;
      os << endl;
      count_semester++;
    }
    os << "CGA: " << data.cga << endl;
  } else
    os << "Semesters are nullptr" << endl;
  return os;
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

BST<Semester>* Student::get_semesters() const { return semesters; }

void Student::change_year(const int& other_year) { year = other_year; }

void Student::calculate_CGA(BST<Semester>* semesters) {
  float result = 0;
  int count_semester = 0, sum_of_credits = 0;
  while (count_semester < semesters->size()) {  // each semester
    int count_course = 0;
    while (count_course <
           semesters->find_kth_largest_node(semesters->size() - count_semester)
             ->data.get_total_num_courses()) {  // each course
      Course& temp =
        semesters->find_kth_largest_node(semesters->size() - count_semester)
          ->data.get_courses()
          .find_kth_largest_node(count_course+1)
          ->data;
      result += temp.get_grade_num() * temp.get_credits();
      sum_of_credits += temp.get_credits();
      count_course++;
    }
    count_semester++;
  }
  cga = result / sum_of_credits;
}

void Student::calculate_MCGA(BST<Semester>* semesters) {}

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