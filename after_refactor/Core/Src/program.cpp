#include "../Inc/program.hpp"

#include <iostream>

Program::Program(std::string program_name, std::string change_date)
    : program_name{program_name}, change_date{change_date} {}

std::string Program::get_program_name() const { return program_name; }

std::string Program::get_change_date() const { return change_date; }

void Program::change_program_name(const std::string& other_program_name) {
  program_name = other_program_name;
}

void Program::change_change_date(const std::string& other_change_date) {
  change_date = other_change_date;
}

bool Program::operator<(const Program& other) { return change_date < other.change_date; }

bool Program::operator>(const Program& other) { return change_date > other.change_date; }

bool Program::operator<=(const Program& other) { return change_date <= other.change_date; }

bool Program::operator>=(const Program& other) { return change_date >= other.change_date; }

bool Program::operator==(const Program& other) { return change_date == other.change_date; }

Major::Major(std::string program_name, std::string change_date, std::string major_name)
    : Program{program_name, change_date}, major_name{major_name} {}

std::string Major::get_major_name() const { return major_name; }

void Major::change_major_name(const std::string& other_major_name) {
  major_name = other_major_name;
}

bool Major::operator<(const Major& other) { return Program::operator<(other); }

bool Major::operator>(const Major& other) { return Program::operator>(other); }

bool Major::operator<=(const Major& other) { return Program::operator<=(other); }

bool Major::operator>=(const Major& other) { return Program::operator>=(other); }

bool Major::operator==(const Major& other) { return Program::operator==(other); }

void Major::print_test() const {
  std::cout << "Major class object:" << std::endl;
  std::cout << "std::string program_name: " << program_name << std::endl;
  std::cout << "std::string change_date: " << change_date << std::endl;
  std::cout << "std::string major_name: " << major_name << std::endl;
}

Minor::Minor(std::string program_name, std::string change_date, std::string minor_name)
    : Program{program_name, change_date}, minor_name{minor_name} {}

std::string Minor::get_minor_name() const { return minor_name; }

void Minor::change_minor_name(const std::string& other_minor_name) {
  minor_name = other_minor_name;
}

bool Minor::operator<(const Minor& other) { return Program::operator<(other); }

bool Minor::operator>(const Minor& other) { return Program::operator>(other); }

bool Minor::operator<=(const Minor& other) { return Program::operator<=(other); }

bool Minor::operator<=(const Minor& other) { return Program::operator>=(other); }

bool Minor::operator==(const Minor& other) { return Program::operator==(other); }

void Minor::print_test() const {
  std::cout << "Minor class object:" << std::endl;
  std::cout << "std::string program_name: " << program_name << std::endl;
  std::cout << "std::string change_date: " << change_date << std::endl;
  std::cout << "std::string minor_name: " << minor_name << std::endl;
}