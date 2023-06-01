#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <string>

// semester->courses->different informations of the courses at specific semester
// csv file can be out of order
// all data that is inputted should be ordered by semesters->acrobatic order in course code

// Personal Information of student
struct Student {
    std::string student_name;
    std::string advisor_name;
    int sid;
    int year;
};

// Information that is about the program
struct Program {
    std::string program;
    std::string change_date;
    std::string major;
    Program *next;
};

// all courses
struct Course {
    std::string code;
    std::string title;
    int credit;
    std::string grade;
    std::string enrolled_semester;
};

// array of semesters
struct Semester {
    Course **courses;
    int tga;
    int cga;
    int cce;
};

int menu();
void readcsv();
void modifycsv();