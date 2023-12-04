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
        Semester semesters; 
        string print_date;
        int total_num_semesters;

    public:
        Transcript();
        ~Transcript();

        /*  Print whole transcript on terminal in specific format
        */
        void print() const;
};

#endif