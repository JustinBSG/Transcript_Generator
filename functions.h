#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <string>

struct Student {
    char *student_name;
    char *advisor_name;
    int sid;
    int year;
};

struct Program {
    char *program;
    char *change_date;
    char *major;
    Program *next;
};

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