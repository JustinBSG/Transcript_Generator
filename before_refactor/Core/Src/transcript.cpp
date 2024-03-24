#include "../Inc/transcript.hpp"

#include <ctime>

using namespace std;

Transcript::Transcript(Student *user, Professor *advisor, BST<Semester> *semesters)
    : user{user}, advisor{advisor}, semesters{semesters} {
  update_print_date();
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
  if (user == nullptr)
    user = other_student;
}

void Transcript::insert_professor(Professor *other_professor) {
  if (advisor == nullptr)
    advisor = other_professor;
}

void Transcript::insert_semesters(BST<Semester> *other_semester) {
  if (semesters == nullptr)
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

void Transcript::calculate_CGA() { user->calculate_CGA(semesters); }

void Transcript::calculate_MCGA() { user->calculate_MCGA(semesters); }

void Transcript::print() const {
  cout << "Here is the transcript." << endl << endl;
  cout << "                    Unofficial Transcript of Academic Record" << endl;
  cout << "-------------------------------------------------------------------------"
          "----------"
       << endl
       << endl;
  cout << "Personal Information" << endl << endl;
  cout << "Name:\t\t" << user->get_name() << endl;
  cout << "Student ID:\t" << user->get_ust_card_num() << endl;
  cout << "Year of Study:\t" << user->get_year() << endl;
  cout << "Advisor:\t" << advisor->get_name() << endl << endl;
  cout << "-------------------------------------------------------------------------"
          "----------"
       << endl
       << endl;
  cout << "Academic Program" << endl << endl;
  cout << "Admit Date:\t" << user->get_admit_date() << endl;
  cout << "Program:\t" << user->get_majors().find_min().get_name();
  
  cout << *user << endl;
}