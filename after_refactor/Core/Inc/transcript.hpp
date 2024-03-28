#ifndef TRANSCRIPT_HPP
#define TRANSCRIPT_HPP

#include <string>

#include "../Inc/bst.hpp"
#include "../Inc/person.hpp"
#include "../Inc/semester.hpp"

class Transcript {
  private:
    Student* user;
    Professor* advisor;
    BST<Semester>* semesters;
    std::string print_date;

  public:
    Transcript(Student* user = nullptr, Professor* advisor = nullptr,
               BST<Semester>* semesters = nullptr);
    Transcript(const Transcript& other);
    Transcript(Transcript&& other);
    ~Transcript();

    Student* get_user() const;
    Professor* get_advisor() const;
    BST<Semester>* get_semesters() const;
    std::string get_print_date() const;
    void change_user(Student* other_user);
    void change_advisor(Professor* other_advisor);
    void change_semesters(BST<Semester>* other_semesters);
    void update_print_date();

    bool operator<(const Transcript& other);
    bool operator>(const Transcript& other);
    bool operator<=(const Transcript& other);
    bool operator>=(const Transcript& other);
    bool operator==(const Transcript& other);

    Transcript& operator=(const Transcript& other);
    Transcript& operator=(Transcript&& other);
    void print_test() const;
};

#endif  // TRANSCRIPT_HPP