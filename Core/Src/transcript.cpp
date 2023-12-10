#include "../Inc/transcript.hpp"

#include <ctime>

using namespace std;

Transcript::Transcript()
    : user{nullptr},
      advisor{nullptr},
      semesters{nullptr},
      print_date{""},
      total_num_semesters{0} {}

Transcript::Transcript(Student *user, Professor *prof, Semester *sem)
    : user{user},
      advisor{prof},
      semesters{sem},
      print_date{""},
      total_num_semesters{0} {
  // initializa total_num_semesters
  Semester *ptr_sem = semesters;
  while (ptr_sem != nullptr) {
    if (ptr_sem->GetTotal_num_courses() != 0) total_num_semesters++;
    ptr_sem = ptr_sem->GetNext();
  }

  // calculate CGA and MCGA
  user->calculate_CGA(semesters);
  user->calculate_MCGA(semesters);

  // update print date
  updatePrint_date();
}

Transcript::~Transcript() {
  delete user;
  delete advisor;
  delete semesters;
}

void Transcript::updatePrint_date() {
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

int Transcript::GetTotal_num_semesters() const { return total_num_semesters; }

void Transcript::print() const {}