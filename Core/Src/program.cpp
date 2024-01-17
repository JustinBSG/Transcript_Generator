#include "../Inc/program.hpp"

#include <iostream>

using namespace std;

ostream& operator<<(ostream& os, const Program& data) {
  os << "Name of Program: " << data.name << " "
     << "Semester of changing program: " << data.change_date << " ";
  return os;
}

Program::Program(string name, string change_date)
    : name{name}, change_date{change_date} {}

Program::Program(const Program& other) { *this = other; }

string Program::get_name() const { return name; }

string Program::get_change_date() const { return change_date; }

void Program::change_name(const string& other_name) { name = other_name; }

void Program::change_change_date(const string& other_change_date) {
  change_date = other_change_date;
}

Program& Program::operator=(const Program& other) {
  if (this != &other) {
    name = other.name;
    change_date = other.change_date;
  }
  return *this;
}

bool Program::operator<(const Program& other) {
  if (change_date >= other.change_date)
    return false;
  else
    return true;
}

bool Program::operator>(const Program& other) {
  if (change_date <= other.change_date)
    return false;
  else
    return true;
}

bool Program::operator==(const Program& other) {
  if (change_date == other.change_date)
    return true;
  else
    return false;
}

ostream& operator<<(ostream& os, const Major& data) {
  os << dynamic_cast<const Program&>(data) << "Name of major: " << data.name_major << " ";
  return os;
}

Major::Major(string name, string change_date, string name_major)
    : Program{name, change_date}, name_major{name_major} {}

Major::Major(const Major& other) { *this = other; }

string Major::get_name_major() const { return name_major; }

void Major::change_name_major(const string& other_name_major) {
  name_major = other_name_major;
}

Major& Major::operator=(const Major& other) {
  if (this != &other) {
    name = other.name;
    change_date = other.change_date;
    name_major = other.name_major;
  }
  return *this;
}

bool Major::operator<(const Major& other) {
  if (other.change_date != "")
    return this->Program::operator<(other);
  else {
    if (name_major >= other.name_major)
      return false;
    else
      return true;
  }
}

bool Major::operator>(const Major& other) {
  if (other.change_date != "")
    return this->Program::operator>(other);
  else {
    if (name_major <= other.name_major)
      return false;
    else
      return true;
  }
}

bool Major::operator==(const Major& other) {
  if (other.change_date != "")
    return this->Program::operator==(other);
  else {
    if (name_major == other.name_major)
      return true;
    else
      return false;
  }
}

ostream& operator<<(ostream& os, const Minor& data) {
  os << dynamic_cast<const Program&>(data) << "Name of minor: " << data.name_minor;
  return os;
}

Minor::Minor(string name, string change_date, string name_minor)
    : Program{name, change_date}, name_minor{name_minor} {}

Minor::Minor(const Minor& other) { *this = other; }

string Minor::get_name_minor() const { return name_minor; }

void Minor::change_name_minor(const string& other_name_minor) {
  name_minor = other_name_minor;
}

Minor& Minor::operator=(const Minor& other) {
  if (this != &other) {
    name = other.name;
    change_date = other.change_date;
    name_minor = other.name_minor;
  }
  return *this;
}

bool Minor::operator<(const Minor& other) {
  if (other.change_date != "")
    return this->Program::operator<(other);
  else {
    if (name_minor >= other.name_minor)
      return false;
    else
      return true;
  }
}

bool Minor::operator>(const Minor& other) {
  if (other.change_date != "")
    return this->Program::operator>(other);
  else {
    if (name_minor <= other.name_minor)
      return false;
    else
      return true;
  }
}

bool Minor::operator==(const Minor& other) {
  if (other.change_date != "")
    return this->Program::operator==(other);
  else {
    if (name_minor == other.name_minor)
      return true;
    else
      return false;
  }
}