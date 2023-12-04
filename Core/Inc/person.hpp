#ifndef INC_PERSON_HPP
#define INC_PERSON_HPP

#include "../Inc/program.hpp"
#include "../Inc/semester.hpp"
#include <string>

class Person {
    protected:
        string name;
        string admit_date;
        string department;
        int ust_card_num;

    public:
        Person(int ust_card_num = 0);
        ~Person() = default;

        string GetName() const;
        string GetAdmit_date() const;
        string GetDepartment() const;
        int GetUst_card_num() const;

        void ChangeName(string);
        void ChangeAdmit_date(string);
        void ChangeDepartment(string);
        void ChangeUst_card_num(int);

        virtual void print_info() const;
};

class Professor : public Person {
    private:
    public:
        Professor(int ust_card_num = 0);
        ~Professor() = default;

        void print_info() const override;
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
        Student(int ust_card_num = 0, int year = 0, float cga = 0., float mcga = 0., Program **program = nullptr, int total_num_program = 0);
        ~Student() = default;

        int GetYear() const;
        float GetCga() const;
        float GetMcga() const;
        string GetStatus() const;
        Program* GetProgram(int) const;
        int GetTotal_num_program() const;

        void change_year(int);
        void calculate_CGA(Semester*);
        void calculate_MCGA(Semester*);
        void change_status(string);
        void add_new_program(Program*);
        void change_total_num_program(int);

        void print_info() const override;
};

#endif