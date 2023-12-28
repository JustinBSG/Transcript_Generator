#ifndef INC_TRANSCRIPT_HPP
#define INC_TRANSCRIPT_HPP

#include <string>

#include "../Inc/bst.hpp"
#include "person.hpp"
#include "program.hpp"
#include "semester.hpp"

class Transcript {
  private:
    Student *user;
    Professor *advisor;
    BST<Semester> *semesters;
    string print_date;

  public:
    Transcript(Student *user = nullptr, Professor *advisor = nullptr);
    ~Transcript();

    Student *get_student() const;
    Professor *get_professor() const;
    BST<Semester> *get_semesters() const;
    string get_print_date() const;

    void insert_student(Student *other_student);
    void insert_professor(Professor *other_professor);
    void insert_semester(BST<Semester> *other_semester);
    void update_print_date();

    void calculate_CGA();
    void calculate_MCGA();

    void print() const;
};

#endif