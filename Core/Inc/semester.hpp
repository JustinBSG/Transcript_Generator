#ifndef INC_SEMESTER_HPP
#define INC_SEMESTER_HPP

#include <string>

#include "../Inc/course.hpp"
#include "../Inc/avlt.hpp"

using namespace std;

class Semester {
  friend ostream& operator<<(ostream& os, const Semester& data);

  private:
    string period;
    float tga;
    float cga;
    int cce;
    AVL<Course> courses;
    int total_num_courses;

  public:
    Semester(string period = "", float tga = .0, float cga = .0, int cce = 0, int total_num_courses = 0);
    ~Semester();

    string get_period() const;
    float get_tga() const;
    float get_cga() const;
    int get_cce() const;
    AVL<Course> get_courses() const;
    int get_total_num_courses() const;

    void change_period(const string& other_period);
    void calculate_tga();
    void calculate_cga();
    void calculate_cce();
    void change_total_num_courses(const int& other_total_num_courses);
};

#endif