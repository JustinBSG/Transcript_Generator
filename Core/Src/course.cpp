#include "../Inc/course.hpp"

ostream& operator<<(ostream& os, const Course& data) {
  // following format of old version
}

Course::Course(string code, string title, string grade, int credits)
    : code{code}, title{title}, grade{grade}, credits{credits} {}

Course::Course(const Course& other) { *this = other; }

string Course::get_code() const { return code; }

string Course::get_title() const { return title; }

string Course::get_grade() const { return grade; }

int Course::get_credits() const { return credits; }

float Course::find_decimal_place_grade() const {
  // TODO: calculate CGA will use this function
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