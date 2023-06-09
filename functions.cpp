#include "functions.h"
using namespace std;

int find_index_year(const char *str) {
    int count_white_space = 0;
    for (int i = 0; i < strlen(str); i++) 
        if (str[i] == ' ') {
            count_white_space++;
            if (count_white_space == 2)
                return i+1;
        }
}

int find_index_month(const char *str) {
    int count_white_space = 0;
    for (int i = 0; i < strlen(str); i++) 
        if (str[i] == ' ') {
            count_white_space++;
            if (count_white_space == 1)
                return i+1;
        }
}

void generate_compare_period(char temp[], char years[], int &season) {
    char season_char[10] = "";
    strcpy(season_char, temp+find_index_month(temp));
    if (strcmp(season_char, "Fall") == 0)
        season = 1;
    else if (strcmp(season_char, "Winter") == 0)
        season = 2;
    else if (strcmp(season_char, "Spring") == 0)
        season = 3;
    else if (strcmp(season_char, "Summer") == 0)
        season = 4;
    else 
        season = 0;
    strncpy(years, temp, find_index_month(temp));
}

void generate_semester_period(Semester *&semester, const Student *student, char start_year[], const int i, const int j) {
    char sem[7] = "";
    switch(j) {
        case 0:
            strcpy(sem, "Fall");
            break;
        case 1:
            strcpy(sem, "Winter");
            break;
        case 2:
            strcpy(sem, "Spring");
            break;
        case 3:
            strcpy(sem, "Summer");
            break;
        default:
            break;
    }
    char temp_start[5];
    strcpy(temp_start, start_year);
    temp_start[3] = temp_start[3]+i;
    strcpy(semester->period, temp_start);
    strcat(semester->period, "-");
    char temp[3];
    strcpy(temp, (student->admit_date+(find_index_year(student->admit_date))+2));
    temp[1] = temp_start[3]+1;
    strcat(semester->period, temp);
    strcat(semester->period, " ");
    strcat(semester->period, sem);
}

void insert_course(Semester *&semester, Course *&course) {
    Semester *ptr = semester;
    while (ptr != nullptr) {
        if (strcmp(ptr->period, course->enrolled_semester) == 0)
            break;
        ptr = ptr->next;
    }

    if (ptr->courses == nullptr) // if it is empty
        ptr->courses = course;
    else {
        if (strcmp(ptr->courses->code, course->code) > 0) { // Be the first element
            course->next = ptr->courses;
            ptr->courses = course;
        } else {
            // Be the last element
            Course *p = ptr->courses;
            while (p->next != nullptr) {
                p = p->next;
            }
            if (strcmp(p->code, course->code) < 0) 
                p->next = course;
            else { // Be the middle element
                p = ptr->courses;
                while (p->next != nullptr && !(strcmp(p->code, course->code) < 0 && strcmp(p->next->code, course->code) > 0)) 
                    p = p->next;
                course->next = p->next;
                p->next = course;
            }
        }
    }
}

float obtain_grade(const char grade[]) {
    float grade_float = 0;
    for (int i = 0; i < 2; i++) 
            switch(grade[i]) {
                case 'A':
                    grade_float += 4.0;
                    break;
                case 'B':
                    grade_float += 3.0;
                    break;
                case 'C':
                    grade_float += 2.0;
                    break;
                case 'D':
                    grade_float += 1.0;
                    break;
                case '+':
                    grade_float += 0.3;
                    break;
                case '-':
                    grade_float += -0.3;
                    break;
                default:
                    return grade_float;
            }
    return grade_float;
}

void calculate_gpa(Student *&student, Semester *&semester, Semester *&semester_head) {
    int total_credit = 0;
    Course *p = semester->courses;
    while (p != nullptr) {
        if (strcmp(p->grade, "**") != 0) 
            total_credit += p->credit;
        p = p->next;
    }
    // calculate tga
    p = semester->courses;
    while (p != nullptr) {
        if (strcmp(p->grade, "**") != 0) 
            semester->tga += obtain_grade(p->grade)*p->credit;
        p = p->next;
    }
    semester->tga /= total_credit;
    // calculate cce
    Semester *ptr = semester_head;
    while (ptr != semester) {
        p = ptr->courses;
        while (p != nullptr) {
            if (strcmp(p->grade, "**") != 0)
                semester->cce += p->credit;
            p = p->next;
        }
        ptr = ptr->next;
    }
    p = ptr->courses;
    while (p != nullptr) {
        if (strcmp(p->grade, "**") != 0) 
            semester->cce += p->credit;
        p = p->next;
    }
    // calculate cga
    ptr = semester_head;
    while (ptr != semester) {
        p = ptr->courses;
        while (p != nullptr) {
            if (strcmp(p->grade, "**") != 0)
                semester->cga += obtain_grade(p->grade)*p->credit;
            p = p->next;
        }
        ptr = ptr->next;
    }
    p = ptr->courses;
    while (p != nullptr) {
        if (strcmp(p->grade, "**") != 0)
            semester->cga += obtain_grade(p->grade)*p->credit;
        p = p->next;
    }
    semester->cga /= semester->cce;
}

void update_calculation_data(Student *&student, Semester *&semester) {

}

void separate_long_into_two(const char original[], char first[], char second[]) {
    int index = 0;
    for (int i = 0; i < 40; i++)
        if (original[i] == ' ')
            index = i;
    strncpy(first, original, index);
    strcpy(second, original+index+1);
}

void insert_data(const int option, Student *&student, Program *&program, Semester *&semester) {
    cout << endl;
    switch (option) {
        case 2: {
            cin.clear();
            cin.sync();
            Program *temp = new Program;
            cout << "Please input the name of the program: ";
            cin.getline(temp->program, 50);
            cout << "Please input the period of changing program (e.g. 2020-21 Fall)(Input NA if it is the first program): ";
            cin.getline(temp->change_date, 100);
            cout << "Please input the name of the major (Input NA if it is board-based program): ";
            cin.getline(temp->major, 40);
            temp->next = nullptr;

            if (strcmp(temp->change_date, "NA") == 0) {
                char new_admit_date[20] = "";
                cout << "Please input new admit date (e.g.1 September 2021): ";
                cin.getline(new_admit_date, 19);
                strcpy(student->admit_date, new_admit_date);
                temp->next = program;
                program = temp;
                cout << endl;
                return;
            } else {
                char years1[8] = "";
                int season1;
                generate_compare_period(temp->change_date, years1, season1);
                if (program == nullptr) 
                    program = temp;
                else {
                    Program *p = program->next;
                    char years2[8] = "";
                    int season2;
                    generate_compare_period(p->change_date, years2, season2);
                    if (strncmp(years1, years2, 7) < 0 || strncmp(years1, years2, 7) == 0 && season1 < season2) { // Be the first
                        temp->next = p;
                        program->next = temp;
                    } else {
                        p = program;
                        while (p->next != nullptr)
                            p = p->next;
                        generate_compare_period(p->change_date, years2, season2);
                        if (strncmp(years1, years2, 7) > 0 || strncmp(years1, years2, 7) == 0 && season1 > season2) // Be the last
                            p->next = temp;
                        else if (strncmp(years1, years2, 7) == 0 && season1 == season2) {
                            cout << "You cannot change the program twice in the same semester." << endl;
                            cout << "Therefore, this input is invalid." << endl;
                            delete temp;
                            temp = nullptr;
                        } else {
                            p = program->next;
                            while (p->next != nullptr) {
                                char years3[8] = "";
                                int season3;
                                generate_compare_period(p->change_date, years2, season2);
                                generate_compare_period(p->next->change_date, years3, season3);
                                if (strncmp(years1, years2, 7) > 0 && strncmp(years1, years3, 7) < 0 || // Be the middle
                                    (strncmp(years1, years2, 7) == 0 && strncmp(years1, years3, 7) < 0 && season1 > season2) ||
                                    (strncmp(years1, years2, 7) > 0 && strncmp(years1, years3, 7) == 0 && season1 < season3) ||
                                    (strncmp(years1, years2, 7) == 0 && strncmp(years1, years3, 7) == 0 && season1 > season2 && season1 < season3)) {
                                        temp->next = p->next;
                                        p->next = temp;
                                        cout << endl;
                                        return;
                                    }
                                p = p->next;
                            }
                        }
                    }
                }
                cout << endl;
                break;
            }
        }
        case 3: {
            cin.clear();
            cin.sync();
            Semester *temp = new Semester;
            cout << "Please input the semester(e.g. 2022-23 Fall): ";
            cin.getline(temp->period, 20);
            Semester *p = semester;
            while (p != nullptr) {
                if (strcmp(p->period, temp->period) == 0) {
                    cout << "It has already existed." << endl;
                    cout << "Therefore, this input is invalid." << endl;
                    delete temp;
                    temp = nullptr;
                    return;
                }
                p = p->next;
            }
            p = semester;
            while (p->next != nullptr)
                p = p->next;
            temp->cce = p->cce;
            temp->tga = 0;
            temp->cga = p->cga;
            temp->next = nullptr;
            temp->courses = nullptr;
            if (semester == nullptr) {
                semester = temp;
            } else {
                char years1[8] = "", years2[8] = "";
                int season1, season2;
                generate_compare_period(temp->period, years1, season1);
                generate_compare_period(semester->period, years2, season2);
                if (strncmp(years1, years2, 7) < 0 || strncmp(years1, years2, 7) == 0 && season1 < season2) { // Be the first
                    temp->next = semester;
                    semester = temp;
                } else {
                    p = semester;
                    while (p->next != nullptr)
                        p = p->next;
                    generate_compare_period(p->period, years2, season2);
                    if (strncmp(years1, years2, 7) > 0 || strncmp(years1, years2, 7) == 0 && season1 < season2) // Be the last
                        p->next = temp;
                    else {
                        p = semester;
                        while (p->next != nullptr) {
                            char years3[8] = "";
                            int season3;
                            generate_compare_period(p->period, years2, season2);
                            generate_compare_period(p->next->period, years3, season3);
                            if (strncmp(years1, years2, 7) > 0 && strncmp(years1, years3, 7) < 0 || // Be the middle
                                (strncmp(years1, years2, 7) == 0 && strncmp(years1, years3, 7) < 0 && season1 > season2) ||
                                (strncmp(years1, years2, 7) > 0 && strncmp(years1, years3, 7) == 0 && season1 < season3) ||
                                (strncmp(years1, years2, 7) == 0 && strncmp(years1, years3, 7) == 0 && season1 > season2 && season1 < season3)) {
                                    temp->next = p->next;
                                    p->next = temp;
                                    cout << "Reminder: It is a normal situation that the latest inserted semester is hidden after generating transcipt." << endl;
                                    cout << "It is because there is no any course in that semester." << endl;
                                    cout << "That semester will be shown after you insert a course into that semester." << endl;
                                    return;
                                }
                            p = p->next;
                        }
                    }
                }
            }
            cout << endl;
            break;
        }
        case 4: {
            cin.clear();
            cin.sync();
            Course *temp = new Course;
            char credit;
            cout << "Please input the course code(e.g. COMP1021): ";
            cin.getline(temp->code, 9);
            cout << "Please input the course title(e.g. Introduction to Computer Science): ";
            cin.getline(temp->title, 99);
            cin.clear();
            cin.sync();
            cout << "Please input the credit of this course: ";
            cin >> credit;
            while (!isdigit(credit)) {
                cout << "Please input number: ";
                cin >> credit;
            }
            temp->credit = credit-48;
            cout << "Please input the enrolled semester(e.g. 2021-22 Fall): ";
            cin.getline(temp->enrolled_semester, 19);
            cout << "Please input the grade in capital letter(if it has not released yet, just input **): ";
            cin.getline(temp->grade, 2);
            Semester *p = semester;
            while (p != nullptr && strcmp(p->period, temp->enrolled_semester) != 0) 
                p = p->next;
            if (p == nullptr) {
                cout << "Please insert the semester before inserting course to that semester." << endl;
                delete temp;
                temp = nullptr;
            } else {
                insert_course(p, temp);
                p = semester;
                while (p != nullptr && strcmp(p->period, temp->enrolled_semester) != 0) {
                    p = p->next;
                }
                calculate_gpa(student, p, semester);
            }
            cout << endl;
            break;
        }
    }
}

void change_data(const int option, Student *&student, Program *&program, Semester *&semester) {
    // show the original one before changing its content
    cin.clear();
    cin.sync();
    switch (option) {
        case 1: { // students
            int option_data;
            cout << "There are 5 types of content that you can change about student's personal information." << endl;
            cout << "1: Name of Student" << endl;
            cout << "2: Name of Advisor" << endl;
            cout << "3: Admit Date" << endl;
            cout << "4: Student ID" << endl;
            cout << "5: Year of Study" << endl;
            cout << "Which type of content that you want to change: ";
            cin >> option_data;
            while (option_data > 5 || option_data < 1) {
                cout << "Please input a valid option: ";
                cin >> option_data;
            }
            cout << endl;
            switch(option_data) {
                case 1: {
                    char new_name[30] = "";
                    cout << "The original name of student is " << student->student_name << "." << endl;
                    cout << "Please input the name of student: ";
                    cin.getline(new_name, 29);
                    strcpy(student->student_name, new_name);
                    break;
                }
                case 2: {
                    char new_name[30] = "";
                    cout << "The original name of advisor is " << student->advisor_name << "." << endl;
                    cout << "Please input the name of advisor: ";
                    cin.getline(new_name, 29);
                    strcpy(student->advisor_name, new_name);
                    break;
                }
                case 3: {
                    char new_admit_date[30] = "";
                    cout << "The original admit date is " << student->admit_date << "." << endl;
                    cout << "Please input admit date: ";
                    cin.getline(new_admit_date, 29);
                    strcpy(student->admit_date, new_admit_date);
                    break;
                }
                case 4: {
                    int new_sid;
                    cout << "The original student ID is " << student->sid << "." << endl;
                    cout << "Please input student ID: ";
                    cin >> new_sid;
                    student->sid = new_sid;
                    break;
                }
                case 5: {
                    int new_year;
                    cout << "The original year of study is " << student->year << "." << endl;
                    cout << "Please input year of study: ";
                    cin >> new_year;
                    student->year = new_year;
                    break;
                }
            }
            break;
        } 
        case 2: { // program
            char semester_change[100] = "";
            cout << "Reminder: Please input NA if you want to change content in your first program." << endl;
            cout << "Please input the semester(e.g. 2022-23 Fall): ";
            Program *p = program;
            while (p != nullptr && strcmp(p->change_date, semester_change) != 0) 
                p = p->next;
            if (p == nullptr) {
                cout << "There is no program with that semester of changing program." << endl;
                cout << "Therefore, it is an invalid input." << endl;
            } else {
                cin.clear();
                cin.sync();
                int option_data;
                cout << endl << "There are 3 types of content that you can change about program." << endl;
                cout << "1: Name of Program" << endl;
                cout << "2: Date of Changing Program" << endl;
                cout << "3: Name of Major" << endl;
                cout << "Which type of content that you want to change: ";
                cin >> option_data;
                switch (option_data) {
                    case 1: {
                        char new_name[50] = "";
                        cout << "The original name of program is " << p->program << "." << endl;
                        cout << "Please input name of program: ";
                        cin.getline(new_name, 49);
                        strcpy(p->program, new_name);
                        break;
                    }
                    case 2:{
                        char new_date[100] = "", years1[8] = "";
                        int season1;
                        cout << "The original date of changing program is " << p->change_date << "." << endl;
                        cout << "Please input date of changing program: ";
                        cin.getline(new_date, 99);
                        Program *test = program;
                        int flag = 0;
                        while (test != nullptr && strcmp(test->change_date, new_date) != 0) 
                            test = test->next;
                        if (test != nullptr) { // check if it is same with some programs
                            cout << "You cannot change the program twice in the same semester." << endl;
                            cout << "Therefore, this input is invalid." << endl;
                        } else {                     
                            Program *temp = new Program;
                            strcpy(temp->change_date, new_date);
                            strcpy(temp->major, p->major);
                            strcpy(temp->program, p->program);
                            temp->next = nullptr;
                            if (program->next == p) { // delete first
                                program->next = p->next;
                                delete p;
                                p = nullptr;
                            } else {
                                if (p->next == nullptr) { // delete last
                                    delete p;
                                    p = nullptr;
                                } else { // delete middle
                                    Program *ptr = program;
                                    while (ptr->next == p) {
                                        ptr = ptr->next;
                                    }
                                    ptr->next = p->next;
                                    delete p;
                                    p = nullptr;
                                }
                            }
                            // check whether insert_data have bug before un// it 
                            // char years1[8] = "";
                            // int season1;
                            // generate_compare_period(temp->change_date, years1, season1);
                            // if (program == nullptr) 
                            //     program = temp;
                            // else {
                            //     Program *p = program->next;
                            //     char years2[8] = "";
                            //     int season2;
                            //     generate_compare_period(p->change_date, years2, season2);
                            //     if (strcmp(years1, years2) < 0 || strcmp(years1, years2) == 0 && season1 < season2) { // Be the first
                            //         temp->next = p;
                            //         program->next = temp;
                            //     } else {
                            //         p = program;
                            //         while (p->next != nullptr)
                            //             p = p->next;
                            //         generate_compare_period(p->change_date, years2, season2);
                            //         if (strcmp(years1, years2) > 0 || strcmp(years1, years2) == 0 && season1 > season2) // Be the last
                            //             p->next = temp;
                            //         else {
                            //             p = program;
                            //             while (p->next != nullptr) {
                            //                 char years3[8] = "";
                            //                 int season3;
                            //                 generate_compare_period(p->change_date, years2, season2);
                            //                 generate_compare_period(p->next->change_date, years3, season3);
                            //                 if (strcmp(years1, years2) > 0 && strcmp(years1, years3) < 0 || // Be the middle
                            //                     (strcmp(years1, years2) == 0 && strcmp(years1, years3) < 0 && season1 > season2) ||
                            //                     (strcmp(years1, years2) > 0 && strcmp(years1, years3) == 0 && season1 < season3) ||
                            //                     (strcmp(years1, years2) == 0 && strcmp(years1, years3) == 0 && season1 > season2 && season1 < season3)) {
                            //                         temp->next = p->next;
                            //                         p->next = temp;
                            //                         cout << endl;
                            //                         return;
                            //                     }
                            //                 p = p->next;
                            //             }
                            //         }
                            //     }
                            // }
                        }
                    }
                    case 3: {
                        char new_name[40] = "";
                        cout << "The original name of major is " << p->major << "." << endl;
                        cout << "Please input name of major: ";
                        cin.getline(new_name, 39);
                        strcpy(p->major, new_name);
                        break;
                    }
                }
            }
            break;
        }
        case 3: { // semester
            cout << "Please input the semester(e.g. 2022-23 Fall): ";

            cout << "There is 1 type of content that you can change about semester which is period of the semester." << endl;
            cout << "Reminder: Changing the period of semester will affect all courses that are enrolled in that semester, calculation of CGA and CCE." << endl;
            cout << "Do you still want to continue(yes/no)? ";

            break;
        }
        case 4: { // course
            cout << "Please input the semester(e.g. 2022-23 Fall): ";

            cout << "There are 5 types of content that you can change about course." << endl;
            cout << "1: Course Code" << endl;
            cout << "2: Course Title" << endl;
            cout << "3: Number of Credit" << endl;
            cout << "4: Grade" << endl;
            cout << "5: Enrolled Semester" << endl;
            cout << "Which type of content that you want to change: ";

            break;
        }
    }
}

void delete_data(const int option, Program *&program, Semester *&semester) {
    cin.clear();
    cin.sync();
    switch (option) {
        case 2: {
            char change_date_delete[100] = "";
            cout << "Reminder: You cannot delete the first program that you have." << endl;
            cout << "You can only change its content." << endl;
            cout << "Please input the semester of changing the program that you want to delete(e.g. 2021-22 Fall): ";
            cin.getline(change_date_delete, 100);
            Program *p = program;
            while (p != nullptr && strcmp(p->change_date, change_date_delete) != 0) 
                p = p->next;
            if (p == nullptr) {
                cout << "There is no program with that semester of changing program." << endl;
                cout << "Therefore, it is an invalid input." << endl;
            } else {
                p = program;
                while (strcmp(p->next->change_date, change_date_delete) != 0)
                    p = p->next;
                if (p->next->next == nullptr) {
                    delete p->next;
                    p->next = nullptr;
                } else {
                    Program *ptr = p->next;
                    p->next = p->next->next;
                    delete ptr;
                    ptr = nullptr;
                }
            }
            break;
        }
        case 3: {
            char semester_period[20] = "";
            cout << "Reminder: Deleting the semester will delete all courses that are enrolled in that semester too" << endl;
            cout << "Please input the semester(e.g. 2021-22 Fall): ";
            cin.getline(semester_period, 19);
            Semester *p = semester;
            while (p != nullptr && strcmp(p->period, semester_period) != 0) 
                p = p->next;
            if (p == nullptr) {
                cout << "There is no such that semester." << endl;
                cout << "Therefore, it is an invalid input." << endl;
            } else {
                delete_whole_course(p->courses);
                p = semester;
                while (strcmp(p->next->period, semester_period) != 0)
                    p = p->next;
                if (p->next->next == nullptr) {
                    delete p->next;
                    p->next = nullptr;
                } else {
                    Semester *ptr = p->next;
                    p->next = p->next->next;
                    delete ptr;
                    ptr = nullptr;
                }
            }
            break;
        }
        case 4: {
            char semester_period[20] = "";
            cout << "Please input the semester(e.g. 2021-22 Fall): ";
            cin.getline(semester_period, 19);
            Semester *p = semester;
            while (p != nullptr && strcmp(p->period, semester_period) != 0) 
                p = p->next;
            if (p == nullptr) {
                cout << "There is no such that semester." << endl;
                cout << "Therefore, it is an invalid input." << endl;
            } else {
                char course_code[10] = "";
                cout << "Please input the course code(e.g. COMP1021): ";
                cin.clear();
                cin.sync();
                cin.getline(course_code, 10);
                Course *ptr = p->courses;
                while (ptr != nullptr && strcmp(ptr->code, course_code) != 0) 
                    ptr = ptr->next;
                if (ptr == nullptr) {
                    cout << "There is no such that course." << endl;
                    cout << "Therefore, it is an invalid input." << endl;
                } else {
                    if (ptr == p->courses) { // delete the first one
                        p->courses = ptr->next;
                        delete ptr;
                        ptr = nullptr;
                    } else {
                        ptr = p->courses;
                        while (ptr->next != nullptr) 
                            p = p->next;
                        if (ptr->next->next == nullptr) { // delete the last one 
                            delete ptr->next;
                            ptr->next = nullptr;
                        } else { // delete the middle one
                            Course *temp = ptr->next;
                            ptr->next = ptr->next->next;
                            delete temp;
                            temp = nullptr;
                        }
                    }
                }
            }
            break;
        } 
    }
}

void delete_whole_program(Program *&program) {
    if (program->next == nullptr) {
        delete program;
        program = nullptr;
    } else {
        delete_whole_program(program->next);
        delete program;
        program = nullptr;
    }
}

void delete_whole_course(Course *&course) {
    if (course->next == nullptr) {
        delete course;
        course = nullptr;
    } else {
        delete_whole_course(course->next);
        delete course;
        course = nullptr;
    }
}

void delete_whole_semester(Semester *&semester) {
    if (semester->next == nullptr) {
        delete_whole_course(semester->courses);
        delete semester;
        semester = nullptr;
    } else {
        delete_whole_semester(semester->next);
        delete_whole_course(semester->courses);
        delete semester;
        semester = nullptr;
    }
}

int menu() {
    int option;
    cout << "******************************* Transcript Generator ******************************" << endl;
    cout << "===================================================================================" << endl;
    cout << "Here are operations that you can choose:" << endl;
    cout << "1: Input data by yourself and form a CSV file" << endl;
    cout << "2: Input data from CSV file" << endl;
    cout << "3: Modify data that inside CSV file" << endl;
    cout << "4: Generate transcript into terminal" << endl;
    cout << "5: Leave" << endl;
    cout << "What operation that you want to choose(1-5): ";
    cin >> option;
    while (option > 6 || option < 1) {
        cout << "Please input valid choice: ";
        cin >> option;
    }
    return option;
}

void insert_csv(Student *&student, Program *&program, Semester *&semester) {

}

void read_csv(Student *&student, Program *&program, Semester *&semester) {
    string input_path;
    cout << "The path for the CSV file (e.g. ./files/student1.csv): ";
    cin >> input_path;
    ifstream fin(input_path);
    while (!fin) {
        input_path = "";
        cout << "Cannot open " << input_path << endl;
        cout << "Please input a valid path." << endl;
        cout << "The path for the CSV file (e.g. ./files/student1.csv): ";
        cin >> input_path;
    }
    cout << endl;
    if (student != nullptr)
        delete_all_dynamic(student, program, semester);

    string line;
    string fields[5];
    int count = 0, count_semester = 0;
    while (getline(fin, line)) {
        int i = 0;
        size_t pos = 0;
        while ((pos = line.find(',')) != string::npos) {
            fields[i++] = line.substr(0, pos);
            line.erase(0, pos+1);
        }
        fields[i] = line;
        if (count++ != 0) // To prevent read the first line of csv file
            if (fields[0].compare("student") == 0) {
                student = new Student;
                strcpy(student->student_name, fields[1].c_str());
                strcpy(student->advisor_name, fields[2].c_str());
                student->sid = stoi(fields[3]);
                student->year = stoi(fields[4]);
                strcpy(student->admit_date, fields[5].c_str());
            } else if (fields[0].compare("program") == 0) {
                if (strcmp(fields[3].c_str(), "NA") == 0) {
                    program = new Program;
                    strcpy(program->program, fields[1].c_str());
                    strcpy(program->major, fields[2].c_str());
                    strcpy(program->change_date, fields[3].c_str());
                    program->next = nullptr;
                } else {
                    Program *temp = new Program;
                    Program *ptr = program;
                    strcpy(temp->program, fields[1].c_str());
                    strcpy(temp->major, fields[2].c_str());
                    strcpy(temp->change_date, fields[3].c_str());
                    temp->next = nullptr;
                    while (ptr->next != nullptr) 
                        ptr = ptr->next;
                    ptr->next = temp;
                }
            } else if (fields[0].compare("course") == 0) {
                if (count_semester++ == 0) { // To initalize the struct semester
                    char start_year[5] = "";
                    strcpy(start_year, (student->admit_date+(find_index_year(student->admit_date))));
                    // input the name of semester (semester->period)
                    for (int i = 0; i < student->year; i++)
                        for (int j = 0; j < 4; j++) 
                            if (i == 0 && j == 0) {
                                semester = new Semester;
                                semester->next = nullptr;
                                generate_semester_period(semester, student, start_year, i, j);
                            } else {
                                Semester *temp = new Semester;
                                Semester *p = semester;
                                temp->next = nullptr;
                                generate_semester_period(temp, student, start_year, i, j);
                                while (p->next != nullptr)
                                    p = p->next;
                                p->next = temp;
                            }
                    // initialize other informations in struct semester without inputting informations into courses
                    Semester *p = semester;
                    while (p != nullptr) {
                        p->courses = nullptr;
                        p->cce = p->cga = p->tga = 0;
                        p = p->next;
                    }
                }
                // Input course information into semester
                Course *temp = new Course;
                strcpy(temp->code, fields[1].c_str());
                strcpy(temp->title, fields[2].c_str());
                temp->credit = stoi(fields[3]);
                strcpy(temp->grade, fields[4].c_str());
                strcpy(temp->enrolled_semester, fields[5].c_str());
                temp->next = nullptr;
                insert_course(semester, temp);
            }
    }
    Semester *p = semester;
    while (p != nullptr) {
        calculate_gpa(student, p, semester);
        p = p->next;
    }
}

void print_all(Student *&student, Program *&program, Semester *&semester) {
    cout << "Here is the transcript." << endl << endl;
    cout << "                    Unofficial Transcript of Academic Record" << endl;
    cout << "-----------------------------------------------------------------------------------" << endl << endl;
    cout << "Personal Information" << endl << endl;
    cout << "Name:\t\t" << student->student_name << endl;
    cout << "Student ID:\t" << student->sid << endl;
    cout << "Year of Study:\t" << student->year << endl;
    cout << "Advisor:\t" << student->advisor_name << endl << endl;
    cout << "-----------------------------------------------------------------------------------" << endl << endl;
    cout << "Academic Program" << endl << endl;
    cout << "Admit Date:\t" << student->admit_date << endl;
    cout << "Program:\t" << program->program << endl;
    if (strcmp(program->major, "NA") != 0)
        cout << "Major:\t\t" << program->major << endl << endl;
    else 
        cout << endl;
    Program *p = program;
    while (p->next != nullptr) {
        cout << "Program Change:\t" << p->next->change_date << endl;
        cout << "Program:\t" << p->next->program << endl;
        cout << "Major:\t\t" << p->next->major << endl << endl;
        p = p->next;
    }
    cout << "-----------------------------------------------------------------------------------" << endl << endl;
    Semester *ptr = semester;
    do {
        if (ptr->courses != nullptr) {
            cout << "Academic Records" << endl << endl;
            cout << ptr->period << endl;
            printf("%-15s%-40s%-13s%-10s%-10s\n", "", "", "Credit", "Credit","");
            printf("%-15s%-40s%-13s%-10s%-10s\n", "Course Code", "Course Title", "Attempted", "Earned", "Grade");
            Course *course = ptr->courses;
            while (course != nullptr) {
                if (strlen(course->title) <= 40) {
                    printf("%-15s%-40s%-13d", course->code, course->title, course->credit);
                    if (course->credit == 0)
                        printf("%-10c", '-');
                    else
                        printf("%-10d", course->credit);
                    printf("%-10s\n", course->grade);
                } else {
                    char first[38] = "", second[40] = "";
                    separate_long_into_two(course->title, first, second);
                    printf("%-15s%-40s%-13d",course->code, first, course->credit);
                    if (course->credit == 0)
                        printf("%-10c", '-');
                    else
                        printf("%-10d", course->credit);
                    printf("%-10s\n", course->grade);
                    printf("%-15s%-40s\n", "", second);
                }
                course = course->next;
            }
            cout << endl << endl;
            int flag = 0;
            Course *temp = ptr->courses;
            while (temp != nullptr) {
                if (temp->credit != 0)
                    flag = 1;
                temp = temp->next;
            }
            if (flag != 1) 
                printf("%-4s\t%s\n", "TGA:", "**");
            else
                printf("%-4s\t%0.3f\n", "TGA:", ptr->tga);
            printf("%-4s\t%0.3f\n", "CGA:", ptr->cga);
            cout << "Cumulative Credits Earned:\t" << ptr->cce << endl << endl;
            cout << "-----------------------------------------------------------------------------------" << endl << endl;
        }
        ptr = ptr->next;
    } while (ptr != nullptr);
}

void modify_csv(Student *&student, Program *&program, Semester *&semester) {
    int option_data, option_modify;
    cout << endl << "Here are four types of data that you can modify:" << endl;
    cout << "1: Personal Information of Student" << endl;
    cout << "2: Information about Program" << endl;
    cout << "3: Semester" << endl;
    cout << "4: Course" << endl;
    cout << "What type of data that you want to modify(1-4): ";
    cin >> option_data;
    while (option_data > 4 || option_data < 1) {
        cout << "Please input valid choice: ";
        cin >> option_data;
    }
    cout << endl << "Here are three operations to the data:" << endl;
    cout << "1: Insert new data" << endl;
    cout << "2: Change value of existing data" << endl;
    cout << "3: Delete exisitng data" << endl;
    cout << "What operation do you to want to perform(1-3): ";
    cin >> option_modify;
    while (option_modify > 3|| option_modify < 1) {
        cout << "Please input valid choice: ";
        cin >> option_modify;
    }

    switch (option_modify) {
        case 1:
            if (option_data != 1)
                insert_data(option_data, student, program, semester);
            else {
                cout << endl << "There is no missing field of student's personal information." << endl;
                cout << "You can only change students's personal information." << endl << endl;
            } 
            break;
        case 2:
            change_data(option_data, student, program, semester);
            break;
        case 3:
            if (option_data != 1)
                    delete_data(option_data, program, semester);
            else {
                cout << "You cannot delete any student's personal information specificly." << endl;
                cout << "You can only change students's personal information." << endl;
            } 
            break;
    }

    // change data in csv file
}

void delete_all_dynamic(Student *&student, Program *&program, Semester *&semester) {
    delete student;
    student = nullptr;
    delete_whole_program(program);
    delete_whole_semester(semester);
}

void testing(Student *&student, Program *&program, Semester *&semester) {
    Semester *p = semester;
    cout << "TGA:" << endl;
    while (p != nullptr) {
        cout << p->period << "\t" << p->tga << endl;
        p = p->next;
    }
    p = semester;
    cout << "CGA:" << endl;
    while (p != nullptr) {
        cout << p->period << "\t" << p->cga << endl;
        p = p->next;
    }
    p = semester;
    cout << "CCE:" << endl;
    while (p != nullptr) {
        cout << p->period << "\t" << p->cce << endl;
        p = p->next;
    }
    cout << "Obtain grade:" << endl;

    // Semester *p = semester;
    // while (p != nullptr) {
    //     Course *ptr = p->courses;
    //     cout << p->period << ":" << endl;
    //     while (ptr != nullptr) {
    //         cout << ptr->code << endl;
    //         ptr = ptr->next;
    //     }
    //     cout << endl;
    //     p = p->next;
    // }
}