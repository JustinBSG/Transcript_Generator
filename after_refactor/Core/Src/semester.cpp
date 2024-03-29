#include "../Inc/semester.hpp"

#include <iostream>

Semester::Semester(std::string period, double tga, int total_num_credits, int total_num_courses)
    : period{period},
      tga{tga},
      total_num_credits{total_num_credits},
      total_num_courses{total_num_courses} {}

std::string Semester::get_period() const { return period; }

double Semester::get_tga() const { return tga; }

int Semester::get_total_num_credits() const { return total_num_credits; }

int Semester::get_total_num_courses() const { return total_num_courses; }

BST<Course>& Semester::get_courses() { return courses; }

void Semester::change_period(const std::string& other_period) { period = other_period; }

void Semester::calculate_tga() {
  tga = 0;
  for (int i = 1; i <= courses.size(); i++) {
    Course* temp = &(courses.find_kth_largest_node(i)->data);
    tga += temp->get_grade_num() * temp->get_credits();
  }
  update_total_num_credits();
  tga /= total_num_credits;
}

void Semester::update_total_num_credits() {
  total_num_credits = 0;
  for (int i = 1; i <= courses.size(); i++)
    total_num_credits += courses.find_kth_largest_node(i)->data.get_credits();
}

void Semester::update_total_num_courses() { total_num_courses = courses.size(); }

void Semester::copy_courses(const BST<Course>& other_courses) {
  courses = other_courses;
  update_total_num_courses();
  update_total_num_credits();
  calculate_tga();
}

void Semester::insert_course(const Course& other_course) {
  courses.insert(other_course);
  update_total_num_courses();
  update_total_num_credits();
  calculate_tga();
}

void Semester::remove_course(const Course& other_course) {
  courses.remove(other_course);
  update_total_num_courses();
  update_total_num_credits();
  calculate_tga();
}

// TODO
bool Semester::operator<(const Semester& other) { return period < other.period; }

// TODO
bool Semester::operator>(const Semester& other) { return period > other.period; }

// TODO
bool Semester::operator<=(const Semester& other) { return period <= other.period; }

// TODO
bool Semester::operator>=(const Semester& other) { return period >= other.period; }

// TODO
bool Semester::operator==(const Semester& other) { return period == other.period; }

void Semester::print_test() const {
  std::cout << "Semester class object:" << std::endl;
  std::cout << "std::string period: " << period << std::endl;
  std::cout << "double tga: " << tga << std::endl;
  std::cout << "int total_num_credits: " << total_num_credits << std::endl;
  std::cout << "int total_num_courses: " << total_num_courses << std::endl;
  std::cout << "BST<Course> courses: " << std::endl;
  std::cout << "the number of courses: " << courses.size() << std::endl;
  for (int i = 1; i <= courses.size(); i++) {
    std::cout << "This is " << i << "th largest node." << std::endl;
    Course* temp = &(courses.find_kth_largest_node(i)->data);
    temp->print_test();
    if (i != courses.size())
      std::cout << std::endl;
  }
}