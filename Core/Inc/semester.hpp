#ifndef INC_SEMESTER_HPP
#define INC_SEMESTER_HPP

#include <string>

#include "../Inc/bst.hpp"
#include "../Inc/course.hpp"

using namespace std;

class Semester {
    friend ostream& operator<<(ostream& os, const Semester& data);

  private:
    string period;
    float tga;
    int total_num_credits;
    int total_num_courses;
    BST<Course> courses;

  public:
    Semester(string period = "", float tga = .0, int total_num_credits = 0,
             int total_num_courses = 0);
    ~Semester() = default;

    string get_period() const;
    float get_tga() const;
    int get_total_num_credits() const;
    int get_total_num_courses() const;
    BST<Course>& get_courses();

    void change_period(const string& other_period);
    void calculate_tga();
    void calculate_total_num_credits();
    void update_total_num_courses();

    void insert_course(const Course& other);
    void remove_course(const string& code);

    Semester& operator=(const Semester& other);
    bool operator<(const Semester& other);
    bool operator>(const Semester& other);
    bool operator==(const Semester& other);
};

#endif