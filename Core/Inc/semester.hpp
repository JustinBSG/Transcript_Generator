#ifndef INC_SEMESTER_HPP
#define INC_SEMESTER_HPP

#include <string>

using namespace std;

class Semester
{
private:
    string period;
    float tga;
    float cga;
    int cce;
    Semester *next;
    Semester *prev;
    Course **courses;
    int total_num_courses;

public:
};

#endif