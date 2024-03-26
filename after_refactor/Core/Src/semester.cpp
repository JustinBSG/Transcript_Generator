#include "../Inc/semester.hpp"

Semester::Semester(std::string period, double tga, int total_num_credits, int total_num_courses)
    : period{period},
      tga{tga},
      total_num_credits{total_num_credits},
      total_num_courses{total_num_courses} {}

std::string Semester::get_period() const {
  return period;
}

double Semester::get_tga() const {
  return tga;
}

int Semester::get_total_num_credits() const {
  return total_num_credits;
}

int Semester::get_total_num_courses() const {
  return total_num_courses;
}

BST<Course>& Semester::get_courses() {
  return courses;
}

void Semester::change_period(const std::string& other_period) {
  period = other_period;
}

void Semester::calculate_tga() {}

void Semester::update_total_num_credits() {
  total_num_credits = 0;
  for (int i = 1; i <= courses.size(); i++) 
    total_num_credits += courses.find_kth_largest_node(i)->data.get_credits();
}

void Semester::update_total_num_courses() {
  total_num_courses = courses.size();
}

void Semester::change_courses(const BST<Course>& other_courses) {
  courses = std::move(other_courses);
}

void Semester::insert_course(const Course& other_course) {
  courses.insert(other_course);
}

void Semester::remove_course(const Course& other_course) {
  courses.remove(other_course);
}

bool Semester::operator<(const Semester& other) {
  return period < other.period;
}

bool Semester::operator>(const Semester& other) {
  return period > other.period;
}

bool Semester::operator<=(const Semester& other) {
  return period <= other.period;
}

bool Semester::operator>=(const Semester& other) {
  return period >= other.period;
}

bool Semester::operator==(const Semester& other) {
  return period == other.period;
}