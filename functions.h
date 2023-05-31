#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <string>

// Personal Information of student
struct Student {
    char *student_name;
    char *advisor_name;
    int sid;
    int year;
};

// Information that is about the program
struct Program {
    char *program;
    char *change_date;
    char *major;
    Program *next;
};

// all courses
struct Course {
    char *code;
    char *title;
    int credit;
    char *grade;
    char *enrolled_semester;
};

// array of semesters
struct Semester {
    Course **courses;
    int tga;
    int cga;
    int cce;
};

// semester->courses->different informations of the courses at specific semester

int menu();