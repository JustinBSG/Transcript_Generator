#include "../Inc/transcript.hpp"

#include <ctime>
#include <stdexcept>

CGA_semester::CGA_semester(double cga, Semester* represent_semester)
    : cga{cga}, represent_semester{represent_semester} {}

// TODO
Transcript::Transcript(Student* user, Professor* advisor, BST<Semester>* semesters)
    : user{user}, advisor{advisor}, semesters{semesters} {
  update_print_date();
}

// TODO
Transcript::Transcript(const Transcript& other)
    : user{nullptr}, advisor{nullptr}, semesters{nullptr} {
  if (other.user == nullptr && other.advisor == nullptr && other.semesters == nullptr)
    return;

  if (other.user != nullptr)
    user = new Student{*other.user};
  if (other.advisor != nullptr)
    advisor = new Professor{*other.advisor};
  if (other.semesters != nullptr)
    semesters = new BST<Semester>{*other.semesters};
  print_date = other.print_date;
}

// TODO
Transcript::Transcript(Transcript&& other)
    : user{other.user},
      advisor{other.advisor},
      semesters{other.semesters},
      print_date{std::move(other.print_date)} {
  other.user = nullptr;
  other.advisor = nullptr;
  other.semesters = nullptr;
  other.print_date = "";
}

Transcript::~Transcript() {
  if (user != nullptr) {
    delete user;
    user = nullptr;
  }
  if (advisor != nullptr) {
    delete advisor;
    advisor = nullptr;
  }
  if (semesters != nullptr) {
    delete semesters;
    semesters = nullptr;
  }
}

Student* Transcript::get_user() const { return user; }

Professor* Transcript::get_advisor() const { return advisor; }

BST<Semester>* Transcript::get_semesters() const { return semesters; }

// TODO
double Transcript::get_CGA(const int& index) const {}

// TODO
std::vector<CGA_semester>& Transcript::get_CGAs() const {}

std::string Transcript::get_print_date() const { return print_date; }

void Transcript::change_user(Student* other_user) {
  if (user != nullptr) {
    delete user;
    user = nullptr;
  }

  if (other_user == nullptr)
    user = nullptr;
  else
    user = new Student{*other_user};
}

void Transcript::change_advisor(Professor* other_advisor) {
  if (advisor != nullptr) {
    delete advisor;
    advisor = nullptr;
  }

  if (other_advisor == nullptr)
    advisor = nullptr;
  else
    advisor = new Professor{*other_advisor};
}

// TODO
void Transcript::change_semesters(BST<Semester>* other_semesters) {}

// TODO
void Transcript::update_CGAs() {}

void Transcript::update_print_date() {
  time_t rawtime;
  struct tm* timeinfo;
  std::string buffer;
  char temp[100];

  time(&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(temp, 100, "%d %B %Y\n", timeinfo);
  buffer.append(temp);
  strftime(temp, 100, "%X", timeinfo);
  buffer.append(temp);

  print_date = buffer;
}

// TODO
bool Transcript::operator<(const Transcript& other) {}

// TODO
bool Transcript::operator>(const Transcript& other) {}

// TODO
bool Transcript::operator<=(const Transcript& other) {}

// TODO
bool Transcript::operator>=(const Transcript& other) {}

// TODO
bool Transcript::operator==(const Transcript& other) {}

// TODO
Transcript& Transcript::operator=(const Transcript& other) {}

// TODO
Transcript& Transcript::operator=(Transcript&& other) {}

// TODO
void Transcript::print_test() const {}