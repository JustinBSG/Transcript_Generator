#ifndef TRANSCRIPT_HPP
#define TRANSCRIPT_HPP

#include <string>

#include "../Inc/bst.hpp"
#include "../Inc/person.hpp"
#include "../Inc/semester.hpp"

class Transcript {
  private:
    Student user;
    Professor advisor;
    BST<Semester> *semesters;
    std::string print_date;

  public:
};

#endif  // TRANSCRIPT_HPP