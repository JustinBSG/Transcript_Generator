#ifndef INC_COURSE_HPP
#define INC_COURSE_HPP

#include <string>
#include "../Inc/semester.hpp"

using namespace std;

class Course
{
private:
    string code;
    string title;
    string grade;
    int credits;

public:
    Course();
    ~Course();

};

#endif