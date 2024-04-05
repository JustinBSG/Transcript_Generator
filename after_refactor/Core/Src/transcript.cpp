#include "../Inc/transcript.hpp"

#include <ctime>
#include <stdexcept>

CGA_semester::CGA_semester(double cga, Semester* represent_semester)
    : cga{cga}, represent_semester{represent_semester} {}

Transcript::Transcript(Student* user, Professor* advisor, BST<Semester>* semesters)
    : user{user}, advisor{advisor}, semesters{semesters} {
  update_CGAs();
  update_print_date();
}

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
  update_CGAs();
  print_date = other.print_date;
}

Transcript::Transcript(Transcript&& other)
    : user{other.user},
      advisor{other.advisor},
      semesters{other.semesters},
      CGAs{std::move(other.CGAs)},
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

double Transcript::get_CGA(const int& index) const {
  try {
    if (index < 0 || index >= CGAs.size())
      throw std::invalid_argument("index should be 0 <= index < CGAs.size()!");

    return CGAs[index].cga;
  } catch (const std::exception& e) {
    std::cout << "Exception: " << e.what() << std::endl;
    std::cout << "Function: double Transcript::get_CGA(const int& index) const" << std::endl;
    std::cout << "Parameter:  index = " << index << std::endl;
    std::cout << "Internal variable:  CGAs.size() = " << CGAs.size() << std::endl;
    throw;
  }
}

double Transcript::get_CGA(const Semester* const target_semester) const {
  try {
    if (target_semester == nullptr)
      throw std::invalid_argument("target_semester should not be nullptr!");

    if (CGAs.size() == 0)
      throw std::logic_error("CGAs is empty!");

    for (int i = 0; i < CGAs.size(); i++)
      if (CGAs[i].represent_semester == target_semester)
        return CGAs[i].cga;
    throw std::logic_error("Cannot find that target_semester!");
  } catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << std::endl;
    std::cerr << "Function: double Transcript::get_CGA(const Semester* const target_semester) const"
              << std::endl;
    std::cerr << "Parameter:  targe_semester = "
              << (target_semester == nullptr ? "nullptr"
                                             : static_cast<const void*>(target_semester))
              << std::endl;
    std::cerr << "Internal variable:  CGAs.size() = " << CGAs.size() << std::endl;
    for (int i = 0; i < CGAs.size(); i++)
      std::cerr << "                    CGAs[" << i
                << "].represent_semester = " << CGAs[i].represent_semester << std::endl;
    throw;
  }
}

std::vector<CGA_semester>& Transcript::get_CGAs() { return CGAs; }

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

void Transcript::change_semesters(BST<Semester>* other_semesters) {
  if (semesters != nullptr) {
    delete semesters;
    semesters = nullptr;
  }

  if (other_semesters == nullptr)
    semesters = nullptr;
  else
    semesters = new BST<Semester>{*other_semesters};
  update_CGAs();
}

void Transcript::update_CGAs() {
  CGAs.clear();

  if (semesters == nullptr)
    return;

  double cga_result = 0.;
  int credit_result = 0;
  for (int i = 1; i <= semesters->size(); i++) {
    Semester* temp_sem = &(semesters->find_kth_smallest_node(i)->data);
    temp_sem->update_total_num_courses();
    temp_sem->update_total_num_credits();
    credit_result += temp_sem->get_total_num_credits();
    for (int j = 1; j <= temp_sem->get_total_num_courses(); j++) {
      Course temp_course = temp_sem->get_courses().find_kth_smallest_node(j)->data;
      cga_result += temp_course.get_grade_num() * temp_course.get_credits();
    }
    CGAs.push_back(CGA_semester{cga_result / credit_result, temp_sem});
  }
}

void Transcript::update_print_date() {
  time_t rawtime;
  struct tm* timeinfo;
  std::string buffer;
  char temp[100];

  time(&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(temp, 100, "%d_%B_%Y_", timeinfo);
  buffer.append(temp);
  strftime(temp, 100, "%X", timeinfo);
  buffer.append(temp);

  print_date = buffer;
}

bool Transcript::operator<(const Transcript& other) { return print_date < other.print_date; }

bool Transcript::operator>(const Transcript& other) { return print_date > other.print_date; }

bool Transcript::operator<=(const Transcript& other) { return print_date <= other.print_date; }

bool Transcript::operator>=(const Transcript& other) { return print_date >= other.print_date; }

bool Transcript::operator==(const Transcript& other) { return print_date == other.print_date; }

Transcript& Transcript::operator=(const Transcript& other) {
  if (this != &other) {
    if (user != nullptr) {
      delete user;
      user = nullptr;
    }
    if (other.user != nullptr)
      user = new Student{*other.user};
    else
      user = nullptr;

    if (advisor != nullptr) {
      delete advisor;
      advisor = nullptr;
    }
    if (other.advisor != nullptr)
      advisor = new Professor{*other.advisor};
    else
      advisor = nullptr;

    if (semesters != nullptr) {
      delete semesters;
      semesters = nullptr;
    }
    if (other.semesters != nullptr)
      semesters = new BST<Semester>{*other.semesters};
    else
      semesters = nullptr;

    update_CGAs();
    print_date = other.print_date;
  }
  return *this;
}

Transcript& Transcript::operator=(Transcript&& other) {
  if (this != &other) {
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
    print_date = std::move(other.print_date);
    user = other.user;
    advisor = other.advisor;
    semesters = other.semesters;
    CGAs = std::move(other.CGAs);
    other.user = nullptr;
    other.advisor = nullptr;
    other.semesters = nullptr;
    other.print_date = "";
  }
  return *this;
}

void Transcript::print_test() const {
  std::cout << "Transcript class object:" << std::endl;
  std::cout << "Student* user: " << (user == nullptr ? "nullptr" : static_cast<const void*>(user))
            << std::endl;
  if (user != nullptr) {
    user->print_test();
    std::cout << std::endl;
  }
  std::cout << "Professor* advisor: "
            << (advisor == nullptr ? "nullptr" : static_cast<const void*>(advisor)) << std::endl;
  if (advisor != nullptr) {
    advisor->print_test();
    std::cout << std::endl;
  }
  std::cout << "BST<Semester>* semesters: "
            << (semesters == nullptr ? "nullptr" : static_cast<const void*>(semesters))
            << std::endl;
  if (semesters != nullptr) {
    std::cout << "the number of semesters: " << semesters->size() << std::endl;
    for (int i = 1; i <= semesters->size(); i++) {
      std::cout << "This is " << i << "th largest node." << std::endl;
      Semester* temp = &(semesters->find_kth_largest_node(i)->data);
      temp->print_test();
      if (i != semesters->size())
        std::cout << std::endl;
    }
  }
  std::cout << "std::vector<CGA_semester> CGAs: " << std::endl;
  std::cout << "the number of CGAs: " << CGAs.size() << std::endl;
  for (int i = 0; i < CGAs.size(); i++) {
    std::cout << "In semester " << CGAs[i].represent_semester->get_period() << ":" << std::endl;
    std::cout << "CGA: " << CGAs[i].cga << std::endl;
  }
  std::cout << "std::string print_date: " << print_date << std::endl;
}