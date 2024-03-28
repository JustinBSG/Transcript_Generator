#include "../Inc/transcript.hpp"

#include <ctime>
#include <stdexcept>

Transcript::Transcript(Student* user, Professor* advisor, BST<Semester>* semesters)
    : user{user}, advisor{advisor}, semesters{semesters} {
  update_print_date();
}

Transcript::Transcript(const Transcript& other)
    : user{nullptr}, advisor{nullptr}, semesters{nullptr} {
  if (other.user == nullptr && other.advisor == nullptr && other.semesters == nullptr)
    return;

  user = new Student{*other.user};
  advisor = new Professor{*other.advisor};
  semesters = new BST<Semester>{*other.semesters};
  print_date = other.print_date;
}

Transcript::Transcript(Transcript&& other) {
  user = other.user;
  advisor = other.advisor;
  semesters = other.semesters;
  print_date = std::move(print_date);
  other.user = nullptr;
  other.advisor = nullptr;
  other.semesters = nullptr;
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

std::string Transcript::get_print_date() const { return print_date; }

void Transcript::change_user(Student* other_user) {
  if (user != nullptr) {
    delete user;
    user = nullptr;
  }
  user = new Student{*other_user};
}

void Transcript::change_advisor(Professor* other_advisor) {
  if (advisor != nullptr) {
    delete advisor;
    advisor = nullptr;
  }
  advisor = new Professor{*other_advisor};
}

// TODO: need to test it
void Transcript::change_semesters(BST<Semester>* other_semesters) {
  try {
    if (user == nullptr)
      throw std::invalid_argument("user should not be nullptr!");
    if (semesters != nullptr) {
      delete semesters;
      semesters = nullptr;
    }
    if (other_semesters != nullptr)
      semesters = new BST<Semester>{*other_semesters};
    user->change_semesters(semesters);
  } catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << std::endl;
    std::cerr << "Function: void Transcript::change_semesters(BST<Semester>* other_semesters)"
              << std::endl;
    std::cerr << "Parameter: other_semesters = "
              << (other_semesters == nullptr ? "nullptr"
                                             : static_cast<const void*>(other_semesters))
              << std::endl;
    std::cerr << "Internal variable:  semesters = "
              << (semesters == nullptr ? "nullptr" : static_cast<const void*>(semesters))
              << std::endl;
    std::cerr << "                    user = "
              << (user == nullptr ? "nullptr" : static_cast<const void*>(user)) << std::endl;
    throw;
  }
}

void Transcript::update_print_date() {
  time_t rawtime;
  struct tm *timeinfo;
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

bool Transcript::operator<(const Transcript& other) {}

bool Transcript::operator>(const Transcript& other) {}

bool Transcript::operator<=(const Transcript& other) {}

bool Transcript::operator>=(const Transcript& other) {}

bool Transcript::operator==(const Transcript& other) {}

Transcript& Transcript::operator=(const Transcript& other) {}

Transcript& Transcript::operator=(Transcript&& other) {}

void Transcript::print_test() const {}