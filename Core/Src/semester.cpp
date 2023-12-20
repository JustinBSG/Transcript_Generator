#include "../Inc/semester.hpp"

using namespace std;

ostream& operator<<(ostream& os, const Semester& data) {
  // TODO: following format of old version
}

Semester::Semester(string period, float tga, int total_num_credits,
                   int total_num_courses)
    : period{period},
      tga{tga},
      total_num_credits{total_num_credits},
      total_num_courses{} {}

string Semester::get_period() const { return period; }

float Semester::get_tga() const { return tga; }

int Semester::get_total_num_credits() const { return total_num_credits; }

int Semester::get_total_num_courses() const { return total_num_courses; }

void Semester::change_period(const string& other_period) { period = other_period; }

void Semester::calculate_tga() {
  float result = 0;
  for (int i = 0; i < courses.size(); i++) {
    result += courses.find_kth_largest_node(i + 1)->data.get_grade_num() *
              courses.find_kth_largest_node(i + 1)->data.get_credits();
  }
  result /= total_num_credits;

  tga = result;
}

void Semester::calculate_total_num_credits() {
  int temp = 0;
  for (int i = 0; i < courses.size(); i++)
    temp += courses.find_kth_largest_node(i + 1)->data.get_credits();
  total_num_credits = temp;
}

void Semester::update_total_num_courses() { total_num_courses = courses.size(); }

void Semester::insert_course(const Course& other) {
  courses.insert(other);
  update_total_num_courses();
  calculate_tga();
  calculate_total_num_credits();
}

void Semester::remove_course(const string& code) {
  Course temp{code};
  courses.remove(temp);
  update_total_num_courses();
  calculate_tga();
  calculate_total_num_credits();
}

Semester& Semester::operator=(const Semester& other) {
  if (this != &other) {
    period = other.period;
    tga = other.tga;
    total_num_courses = other.total_num_courses;
    courses = other.courses;
  }
  return *this;
}

bool Semester::operator<(const Semester& other) {
  if (period >= other.period)
    return false;
  else
    return true;
}

bool Semester::operator>(const Semester& other) {
  if (period <= other.period)
    return false;
  else
    return true;
}

bool Semester::operator==(const Semester& other) {
  if (period == other.period)
    return true;
  else
    return false;
}