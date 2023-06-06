#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <string>

// semester->courses->different informations of the courses at specific semester
// csv file can be out of order
// all data that is inputted should be ordered by semesters->acrobatic order in course code

const int MAX_NUM_COURSE_SEMESTER = 10;

// Personal Information of student
struct Student {
    char student_name[30] = "";
    char advisor_name[30]= "";
    char admit_date[20] = "";
    int sid;
    int year;
};

// Information that is about the program
struct Program {
    char program[50] = "";
    char change_date[100] = "";
    char major[40] = "";
    Program *next;
};

// all courses
struct Course {
    char code[10] = "";
    char title[100] = "";
    int credit;
    char grade[3] = "";
    char enrolled_semester[20] = "";
    Course *next;
};

// array of semesters
struct Semester {
    Course *courses;
    char period[20] = "";
    float tga;
    float cga;
    int cce;
    Semester *next;
};

enum Semester_name {Fall, Winter, Spring, Summer, END};

int find_index_year(const char*);
void generate_semester_period(Semester*&, const Student*, char [], const int, const int);
void insert_course(Semester*&, Course*&);
void calculate_gpa(Student *&, Semester*&, Semester*&);
float obtain_grade(const char []);
void separate_long_into_two(const char [], char [], char []);
void delete_program(Program *&);
void delete_course(Course *&);
void delete_semester(Semester *&);

int menu();
void read_csv(Student*&, Program*&, Semester*&);
void print_all(Student*&, Program*&, Semester*&);
void modify_csv();
void delete_all_dynamic(Student*&, Program*&, Course*&, Semester*&);
void testing(Student*&, Program*&, Course*&, Semester*&);