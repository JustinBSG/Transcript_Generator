#ifndef INC_SEMESTER_HPP
#define INC_SEMESTER_HPP

#include "course.hpp"
#include <string>

using namespace std;

class Semester {
    friend class student;

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
        Semester();
        ~Semester();

        string GetPeriod() const;
        float GetTGA() const;
        float GetCGA() const;
        int GetCCE() const;
        Semester* GetNext() const;
        Semester* GetPrev() const;
        Course *GetCourses() const;
        int GetTotal_num_courses() const;
};

#endif