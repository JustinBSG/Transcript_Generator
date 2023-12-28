#include "../Inc/transcript.hpp"

#include <ctime>

using namespace std;

Transcript::Transcript(Student *user, Professor *advisor)
    : user{user}, advisor{advisor} {
  update_print_date();
  // TODO: rethink about how to deal with the pointer of semester
}

Transcript::~Transcript() {
  delete user;
  user = nullptr;
  delete advisor;
  advisor = nullptr;
  semesters = nullptr;
  // semester is deleted in user
}

Student *Transcript::get_student() const { return user; }

Professor *Transcript::get_professor() const { return advisor; }

BST<Semester> *Transcript::get_semesters() const { return semesters; }

string Transcript::get_print_date() const { return print_date; }

void Transcript::insert_student(Student *other_student) {
  if (user != nullptr)
    user = other_student;
}

void Transcript::insert_professor(Professor *other_professor) {
  if (advisor != nullptr)
    advisor = other_professor;
}

void Transcript::insert_semester(BST<Semester> *other_semester) {
  if (semesters != nullptr)
    semesters = other_semester;
}

void Transcript::update_print_date() {
  time_t rawtime;
  struct tm *timeinfo;
  string buffer;
  char temp[100];

  time(&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(temp, 100, "%d %B %Y\n", timeinfo);
  buffer.append(temp);
  strftime(temp, 100, "%X", timeinfo);
  buffer.append(temp);

  print_date = buffer;
}

void Transcript::calculate_CGA() {

}

void Transcript::calculate_MCGA() {
  
}

void Transcript::print() const {}