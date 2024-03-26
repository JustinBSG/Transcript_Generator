#ifndef SEMESTER_HPP
#define SEMESTER_HPP

#include <string>

#include "bst.hpp"
#include "course.hpp"

class Semester {
  private:
    std::string period;
    double tga;
    int total_num_credits;
    int total_num_courses;
    BST<Course> courses;

  public:
    Semester(std::string period = "", double tga = 0., int total_num_credits = 0,
             int total_num_courses = 0);

    std::string get_period() const;
    double get_tga() const;
    int get_total_num_credits() const;
    int get_total_num_courses() const;
    BST<Course>& get_courses();
    void change_period(const std::string& other_period);
    void calculate_tga();
    void update_total_num_credits();
    void update_total_num_courses();
    void change_courses(const BST<Course>& other_courses);
    void insert_course(const Course& other_course);
    void remove_course(const Course& other_course);

    bool operator<(const Semester& other);
    bool operator>(const Semester& other);
    bool operator<=(const Semester& other);
    bool operator>=(const Semester& other);
    bool operator==(const Semester& other);
};

#endif  // SEMESTER_HPP