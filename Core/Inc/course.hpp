#ifndef INC_COURSE_HPP
#define INC_COURSE_HPP

#include "../Inc/semester.hpp"
#include <string>

using namespace std;

class Course {
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