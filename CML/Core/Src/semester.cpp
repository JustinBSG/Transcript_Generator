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

bool Semester::operator<(const Semester& other) {
  std::vector<std::string> self_seg = separate_string_period();
  std::vector<std::string> other_seg = other.separate_string_period();

  if (self_seg.size() < 2 && other_seg.size() < 2)  // "" < ""
    return false;

  if (self_seg.size() < 2)  // "" < "something something"
    return true;
  else if (other_seg.size() < 2)  // "something something" < ""
    return false;

  if (self_seg[0] < other_seg[0])  // "2023-24" < "2024-25"
    return true;
  else if (self_seg[0] == other_seg[0])  // "2023-24" == "2023-24"
    // Fall < Winter < Spring < Summer
    return compare_semester_period(self_seg[1]) < compare_semester_period(other_seg[1]);
  else
    return false;
}

bool Semester::operator>(const Semester& other) {
  std::vector<std::string> self_seg = separate_string_period();
  std::vector<std::string> other_seg = other.separate_string_period();

  if (self_seg.size() < 2 && other_seg.size() < 2)  // "" > ""
    return false;

  if (self_seg.size() < 2)  // "" > "something something"
    return false;
  else if (other_seg.size() < 2)  // "something something" > ""
    return true;

  if (self_seg[0] > other_seg[0])  // "2025-26" > "2024-25"
    return true;
  else if (self_seg[0] == other_seg[0])  // "2023-24" == "2023-24"
    // Fall < Winter < Spring < Summer
    return compare_semester_period(self_seg[1]) > compare_semester_period(other_seg[1]);
  else
    return false;
}

bool Semester::operator<=(const Semester& other) {
  std::vector<std::string> self_seg = separate_string_period();
  std::vector<std::string> other_seg = other.separate_string_period();

  if (self_seg.size() < 2 && other_seg.size() < 2) // "" < ""
    return false;

  if (self_seg.size() < 2) // "" < "something something"
    return true;
  else if (other_seg.size() < 2) // "something something" < ""
    return false;

  if (self_seg[0] < other_seg[0]) // "2023-24" < "2024-25"
    return true;
  else if (self_seg[0] == other_seg[0]) // "2023-24" == "2023-24"
    // Fall < Winter < Spring < Summer
    return compare_semester_period(self_seg[1]) <= compare_semester_period(other_seg[1]);
  else
    return false;
}

bool Semester::operator>=(const Semester& other) {
  std::vector<std::string> self_seg = separate_string_period();
  std::vector<std::string> other_seg = other.separate_string_period();

  if (self_seg.size() < 2 && other_seg.size() < 2)  // "" > ""
    return false;

  if (self_seg.size() < 2)  // "" > "something something"
    return false;
  else if (other_seg.size() < 2)  // "something something" > ""
    return true;

  if (self_seg[0] > other_seg[0])  // "2025-26" > "2024-25"
    return true;
  else if (self_seg[0] == other_seg[0])  // "2023-24" == "2023-24"
    // Fall < Winter < Spring < Summer
    return compare_semester_period(self_seg[1]) >= compare_semester_period(other_seg[1]);
  else
    return false;
}

bool Semester::operator==(const Semester& other) {
  return period == other.period;
}

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

std::vector<std::string> Semester::separate_string_period() const {
  try {
    std::vector<std::string> result;
    std::string temp;
    std::istringstream iss{period};

    while (std::getline(iss, temp, ' '))
      result.push_back(temp);

    if (result.size() > 2)
      throw std::invalid_argument("There are more than 2 segments of string in period!");

    return result;
  } catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << std::endl;
    std::cerr << "Function: std::vector<std::string> Semester::separate_string_period() const"
              << std::endl;
    std::cerr << "Internal variable: std::string period = " << period << std::endl;
    throw;
  }
}

int Semester::compare_semester_period(const std::string& semester_period) const {
  if (semester_period == "Fall")
    return 0;
  else if (semester_period == "Winter")
    return 1;
  else if (semester_period == "Spring")
    return 2;
  else if (semester_period == "Summer")
    return 3;
  else
    return -1;
}