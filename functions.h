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
    char *student_name;
    char *advisor_name;
    int sid;
    int year;
    char *admit_date;
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
    Course *next;
};

// array of semesters
struct Semester {
    Course *courses;
    char *period;
    float tga;
    float cga;
    float cce;
    Semester *next;
};

enum Semester_name {Fall, Winter, Spring, Summer, END};

const int MAX_NUM_COURSE_SEMESTER = 10;

int find_index_year(const char*);
void generate_semester_period(Semester*&, const Student*, char [], const int, const int);
void insert_course(Semester*&, Course*&);
void calculate_gpa(const Student *&, Semester*&);
float obtain_grade(const char []);

int menu();
void read_csv(Student*&, Program*&, Semester*&);
void modify_csv();
void delete_all_dynamic(Student*&, Program*&, Course*&, Semester*&);