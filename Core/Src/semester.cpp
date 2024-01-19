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
      total_num_courses{total_num_courses} {}

string Semester::get_period() const { return period; }

float Semester::get_tga() const { return tga; }

int Semester::get_total_num_credits() const { return total_num_credits; }

int Semester::get_total_num_courses() const { return total_num_courses; }

BST<Course>& Semester::get_courses() { return courses; }

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

int Semester::convert_period(const string& period_semester) {
  if (period_semester == "Fall")
    return Fall;
  else if (period_semester == "Winter")
    return Winter;
  else if (period_semester == "Spring")
    return Spring;
  else if (period_semester == "Summer")
    return Summer;
  else
    return -1;
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
  string period_year[2] = {period.substr(0, 8), other.period.substr(0, 8)};
  if (period_year[0] < period_year[1])
    return true;
  else if (period_year[0] == period_year[1]) {
    string period_semester[2] = {period.substr(8, period.length()),
                                 other.period.substr(8, other.period.length())};
    int period_semester_int[2] = {convert_period(period_semester[0]),
                                  convert_period(period_semester[1])};
    if (period_semester_int[0] < period_semester_int[1])
      return true;
    else
      return false;
  } else
    return false;
}

bool Semester::operator>(const Semester& other) {
  string period_year[2] = {period.substr(0, 8), other.period.substr(0, 8)};
  if (period_year[0] > period_year[1])
    return true;
  else if (period_year[0] == period_year[1]) {
    string period_semester[2] = {period.substr(8, period.length()),
                                 other.period.substr(8, other.period.length())};
    int period_semester_int[2] = {convert_period(period_semester[0]),
                                  convert_period(period_semester[1])};
    if (period_semester_int[0] > period_semester_int[1])
      return true;
    else
      return false;
  } else
    return false;
}

bool Semester::operator==(const Semester& other) {
  if (period == other.period)
    return true;
  else
    return false;
}