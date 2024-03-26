#include "../Inc/course.hpp"

Course::Course(std::string code, std::string title, std::string grade, int credits)
    : code{code}, title{title}, grade{grade}, credits{credits} {}

std::string Course::get_code() const { return code; }

std::string Course::get_title() const { return title; }

std::string Course::get_grade_str() const { return grade; }

int Course::get_credits() const { return credits; }

double Course::get_grade_num() const {
  double result;
  switch (grade[0]) {
    case 'A':
      result = 4.;
      break;
    case 'B':
      result = 3.;
      break;
    case 'C':
      result = 2.;
      break;
    case 'D':
      result = 1.;
      break;
    default:
      result = 0.;
  }

  // deal with calculation of subgrade
  if (result != 0. && result != 1. && grade.length() == 2) {
    switch (grade[1]) {
      case '+':
        result += 0.3;
        break;
      case '-':
        result -= 0.3;
        break;
    }
  }

  return result;
}

void Course::change_code(const std::string& other_code) { code = other_code; }

void Course::change_title(const std::string& other_title) { title = other_title; }

void Course::change_grade(const std::string& other_grade) { grade = other_grade; }

void Course::change_credits(const int& other_credits) { credits = other_credits; }

bool Course::operator<(const Course& other) {
  if (code < other.code)
    return true;
  else
    return false;
}

bool Course::operator>(const Course& other) {
  if (code > other.code)
    return true;
  else
    return false;
}

bool Course::operator<=(const Course& other) {
  if (code <= other.code)
    return true;
  else
    return false;
}

bool Course::operator>=(const Course& other) {
  if (code >= other.code)
    return true;
  else
    return false;
}

bool Course::operator==(const Course& other) {
  if (code == other.code)
    return true;
  else
    return false;
}