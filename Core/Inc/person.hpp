#ifndef INC_PERSON_HPP
#define INC_PERSON_HPP

#include <string>
#include "../Inc/program.hpp"

using namespace std;

class Person
{
protected:
    string name;
    string admit_date;
    string department;
    int ust_card_num;

public:
    Person(string name = "", string admit_date = "", string department = "", int ust_card_num = 0);
    Person(const Person &other);
};

class Prof : public Person
{
private:
};

class Student : public Person
{
private:
    int year;
    float cga;
    float mcga;
    string status;
    Program **program;
    int total_num_program;

public:
    Student(int year = 0, float cga = 0., float mcga = 0., string status = "", Program **program = nullptr, int total_num_program = 0);

    int GetYear() const;
    float GetCga() const;
    float GetMcga() const;
    string GetStatus() const;
    Program *GetProgram(int index) const;
    int GetTotal_num_program() const;

    void increment_year();
    void calculate_CGA();
    void calculate_MCGA();
    void change_status(string latest_stats);
    void add_new_program(Program *latest_program);
    void increment_num_program();
};

#endif