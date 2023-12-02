#ifndef INC_PERSON_HPP
#define INC_PERSON_HPP

#include "../Inc/program.hpp"
#include <string>

using namespace std;

class Person {
    protected:
        string name;
        string admit_date;
        string department;
        int ust_card_num;

    public:
        Person();
        ~Person();

        string GetName() const;
        string GetAdmit_date() const;
        string GetDepartment() const;
        int GetUst_card_num() const;
};

class Professor : public Person {
    private:
    public:
        Professor();
        ~Professor();
};

class Student : public Person {
    private:
        int year;
        float cga;
        float mcga;
        string status;
        Program **program;
        int total_num_program;

    public:
        Student();
        ~Student();

        int GetYear() const;
        float GetCga() const;
        float GetMcga() const;
        string GetStatus() const;
        Program *GetProgram() const;
        int GetTotal_num_program() const;

        void increment_year();
        void calculate_CGA();
        void calculate_MCGA();
        void change_status(string latest_stats);
        void add_new_program(Program *latest_program);
        void increment_num_program();
};

#endif