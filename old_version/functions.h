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

Program* insert_csv_program(int&);
int find_index_year(const char*);
int find_index_month(const char*);
void generate_compare_period(char [], char [], int&);
void generate_semester_period(Semester*&, const Student*, char [], const int, const int);
void insert_course(Semester*&, Course*&);
float obtain_grade(const char []);
void calculate_gpa(Student*&, Semester*&, Semester*&);
void update_gpa(Student*&, Semester*&);
void separate_long_into_two(const char [], char [], char []);
void insert_data(const int, Student*&, Program*&, Semester*&);
void change_data(const int, Student*&, Program*&, Semester*&);
void delete_data(const int, Program*&, Semester*&);
void delete_whole_program(Program *&);
void delete_whole_course(Course *&);
void delete_whole_semester(Semester *&);

int menu();
void insert_csv();
void read_csv(Student*&, Program*&, Semester*&, char []);
void print_all(Student*&, Program*&, Semester*&);
void modify_csv(Student*&, Program*&, Semester*&, char []);
void delete_all_dynamic(Student*&, Program*&, Semester*&);
void testing(Student*&, Program*&, Semester*&);