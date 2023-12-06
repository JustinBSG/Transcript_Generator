#ifndef INC_TRANSCRIPT_HPP
#define INC_TRANSCRIPT_HPP

#include <string>

#include "person.hpp"
#include "program.hpp"
#include "semester.hpp"

class Transcript {
    private:
        Student *user;
        Professor *advisor;
        Semester *semesters; 
        string print_date;
        int total_num_semesters;

    public:
        Transcript();
        ~Transcript();

        Student* create_user();
        Professor* create_prof();
        Semester* create_semesters();
        string createPrint_date();

        int GetTotal_num_semesters() const;

        void print() const;
};

#endif