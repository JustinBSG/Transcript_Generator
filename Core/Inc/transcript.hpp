#ifndef INC_TRANSCRIPT_HPP
#define INC_TRANSCRIPT_HPP

#include <string>

#include "person.hpp"
#include "program.hpp"
#include "semester.hpp"

class Transcript {
    private:
        Student user;
        Professor advisor;
        Semester semesters; // maybe use list
        string print_date;

    public:
        Transcript();
        ~Transcript();

        void print() const;
};

#endif