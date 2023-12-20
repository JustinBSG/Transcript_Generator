#include "../Inc/course.hpp"

ostream& operator<<(ostream& os, const Course& data) {
  // TODO: following format of old version
}

Course::Course(string code, string title, string grade, int credits)
    : code{code}, title{title}, grade{grade}, credits{credits} {}

Course::Course(const Course& other) { *this = other; }

string Course::get_code() const { return code; }

string Course::get_title() const { return title; }

string Course::get_grade_str() const { return grade; }

int Course::get_credits() const { return credits; }

float Course::get_grade_num() const {
  float result = .0;
  if (grade.size() > 0)
    switch (grade[0]) {
      case 'A':
        result = 4;
        break;
      case 'B':
        result = 3;
        break;
      case 'C':
        result = 2;
        break;
      case 'D':
        result = 1;
        break;
    }

  if (grade.size() == 2)
    switch (grade[1]) {
      case '+':
        result += 0.3;
        break;
      case '-':
        result -= 0.3;
        break;
    }

  return result;
}

void Course::change_code(const string& other_code) { code = other_code; }

void Course::change_title(const string& other_title) { title = other_title; }

void Course::change_grade(const string& other_grade) { grade = other_grade; }

void Course::change_credits(const int& other_credits) { credits = other_credits; }

Course& Course::operator=(const Course& other) {
  if (this != &other) {
    code = other.code;
    title = other.title;
    grade = other.grade;
    credits = other.credits;
  }
  return *this;
}

bool Course::operator<(const Course& other) {
  if (code >= other.code)
    return false;
  else
    return true;
}

bool Course::operator>(const Course& other) {
  if (code <= other.code)
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