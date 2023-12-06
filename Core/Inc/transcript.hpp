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
        Transcript(Student*, Professor*, Semester*);
        ~Transcript();

        int GetTotal_num_semesters() const;

        void changeStudent(Student*);
        void changeProfessor(Professor*);
        void changeSemester(Semester*);
        void updatePrint_date();
        void updateTotal_num_semesters();

        void print() const;
};

#endif