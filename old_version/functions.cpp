#include "functions.h"
using namespace std;

// Inputting information of student's programs.
// flag is used to decide whether user want to keep inputting other program
// return pointer of program to update the linked list of program
Program* insert_csv_program(int &flag) {
    char choice[5] = "";
    cin.clear();
    cin.sync();
    Program *temp = new Program;
    cout << "Then, please input the name of the program(e.g. Bachelor Degree in School of Engineering): ";
    cin.getline(temp->program, 50);
    cout << "Please input the name of the major(If it does not have, please input NA)(e.g. Computer Science): ";
    cin.getline(temp->major, 40);
    cout << "Please input the semester that you changed the program(e.g. 2022-23 Fall): ";
    cin.getline(temp->change_date, 100);
    temp->next = nullptr;

    // To make sure the input is valid.
    cout << "Do you still want to continue to input other program(yes/no): ";
    cin.getline(choice, 5);
    while (1) {
        if (strcmp(choice, "no") == 0) {
            flag = 1;
            break;
        } else if (strcmp(choice, "yes") != 0) {
            cout << "It is an invalid input.";
            cout << "Please input again: ";
            cin.clear();
            cin.sync();
            cin.getline(choice, 5);
        }
        break;
    }
    return temp;
}

// To obtain index of year from admit date(e.g. 1 September 2021)
int find_index_year(const char *str) {
    int count_white_space = 0;
    for (int i = 0; i < strlen(str); i++) 
        if (str[i] == ' ') {
            count_white_space++;
            if (count_white_space == 2)
                return i+1;
        }
}

// To obtain index of month from admit date(e.g. 1 September 2021)
int find_index_month(const char *str) {
    int count_white_space = 0;
    for (int i = 0; i < strlen(str); i++) 
        if (str[i] == ' ') {
            count_white_space++;
            if (count_white_space == 1)
                return i+1;
        }
}

// To obtain the year and "season" of semester from temp
// temp[]: To store the "name" of semester (e.g. 2021-22 Fall)
// years: To store the year of semester (e.g. 2021)
// season: To store the "season" of the semester (e.g. Fall)
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

// To generate the "name" of the semester
// semester: the head pointer of semester linked list
// student: the pointer of student dynamic struct object
// start_year: string of year of admit date
// i: number of year
// j: number of "season" of semester, 0 for fall semester, 1 for winter semester, 2 for spring semester, 3 for summer semester
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

// Inputting course into linked list of semester in alphabetical order
// semester: head pointer of linked list of semester
// course: pointer of dynamic struct object
void insert_course(Semester *&semester, Course *&course) {
    Semester *ptr = semester;
    while (ptr != nullptr) { // Let ptr be the pointer of next address of last node
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

// To obtain string form of grade and return float form of grade
// grade[]: the string form of grade
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

// To update the data of cce, tga and gpa of all semesters
// First, reset all data into 0. Then, calculate all data again
// student: pointer of dynamic student struct object
// semester: head pointer of linked list of semester 
void update_gpa(Student *&student, Semester *&semester) {
    Semester *p_sem = semester;
    while (p_sem != nullptr) {
        p_sem->tga = p_sem->cga = p_sem->cce = 0;
        int total_credit = 0;
        Course *p = p_sem->courses;
        while (p != nullptr) {
            if (strcmp(p->grade, "**") != 0) 
                total_credit += p->credit;
            p = p->next;
        }

        // calculate tga
        p = p_sem->courses;
        while (p != nullptr) {
            if (strcmp(p->grade, "**") != 0) 
                p_sem->tga += obtain_grade(p->grade)*p->credit;
            p = p->next;
        }
        p_sem->tga /= total_credit;

        // calculate cce
        Semester *ptr = semester;
        while (ptr != p_sem) {
            p = ptr->courses;
            while (p != nullptr) {
                if (strcmp(p->grade, "**") != 0)
                    p_sem->cce += p->credit;
                p = p->next;
            }
            ptr = ptr->next;
        }
        p = ptr->courses;
        while (p != nullptr) {
            if (strcmp(p->grade, "**") != 0) 
                p_sem->cce += p->credit;
            p = p->next;
        }

        // calculate cga
        ptr = semester;
        while (ptr != p_sem) {
            p = ptr->courses;
            while (p != nullptr) {
                if (strcmp(p->grade, "**") != 0)
                    p_sem->cga += obtain_grade(p->grade)*p->credit;
                p = p->next;
            }
            ptr = ptr->next;
        }
        p = ptr->courses;
        while (p != nullptr) {
            if (strcmp(p->grade, "**") != 0)
                p_sem->cga += obtain_grade(p->grade)*p->credit;
            p = p->next;
        }
        p_sem->cga /= p_sem->cce;
        p_sem = p_sem->next;
    }
}

// Separate one long string into two string
void separate_long_into_two(const char original[], char first[], char second[]) {
    int index = 0;
    for (int i = 0; i < 40; i++)
        if (original[i] == ' ')
            index = i;
    strncpy(first, original, index);
    strcpy(second, original+index+1);
}

// According to different types of data, performing operation of inserting data by different methods
// option: the chosen type of data
// student: head pointer of dynamic struct student object
// program: head pointer of dynamic struct program object
// semester: head pointer of dynamic struct semester object
void insert_data(const int option, Student *&student, Program *&program, Semester *&semester) {
    cout << endl;
    switch (option) {
        case 2: { // Inserting information of student's program
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
                cin.getline(new_admit_date, 20);
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
        case 3: { // Inputting data of semester
            cin.clear();
            cin.sync();
            Semester *temp = new Semester;
            cout << "Reminder: You need to input a semester that is consecutive with existing semester." << endl;
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
                                    cout << "That semester will be shown after you insert a course into that semester." << endl << endl;
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
        case 4: { // Inputting information of course in specific semester
            cin.clear();
            cin.sync();
            Course *temp = new Course;
            char credit;
            cout << "Please input the course code(e.g. COMP1021): ";
            cin.getline(temp->code, 10);
            cout << "Please input the course title(e.g. Introduction to Computer Science): ";
            cin.getline(temp->title, 100);
            cout << "Please input the credit of this course: ";
            cin >> credit;
            while (!isdigit(credit)) {
                cout << "Please input number: ";
                cin >> credit;
            }
            temp->credit = credit-48;
            cin.clear();
            cin.sync();
            cout << "Please input the enrolled semester(e.g. 2021-22 Fall): ";
            cin.getline(temp->enrolled_semester, 20);
            cout << "Please input the grade in capital letter(if it has not released yet, just input **): ";
            cin.getline(temp->grade, 3);
            Semester *p = semester;
            while (p != nullptr && strcmp(p->period, temp->enrolled_semester) != 0) 
                p = p->next;

            if (p == nullptr) {
                cout << "Please insert the semester before inserting course to that semester." << endl;
                delete temp;
                temp = nullptr;
            } else {
                Course *ptr = p->courses;
                while (ptr != nullptr) {
                    if (strcmp(ptr->code, temp->code) == 0) {
                        cout << "There is a course that have the same code with the the latest input course." << endl;
                        cout << "Therefore, it is an invalid input." << endl << endl;
                        delete temp;
                        temp = nullptr;
                        return;
                    }
                    ptr = ptr->next;
                }
                insert_course(p, temp);
            }
            cout << endl;
            break;
        }
    }
}

// According to different types of data, performing operation of changing data by different methods
// Changing some data, such as number of credit of a course, requires update other data, such as calculation of cga and tga
// option: the chosen type of data
// student: head pointer of dynamic struct student object
// program: head pointer of dynamic struct program object
// semester: head pointer of dynamic struct semester object
void change_data(const int option, Student *&student, Program *&program, Semester *&semester) {
    // show the original one before changing its content
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
            cin.clear();
            cin.sync();
            switch(option_data) {
                case 1: { // Name of student
                    char new_name[30] = "";
                    cout << "The original name of student is " << student->student_name << "." << endl;
                    cout << "Please input the name of student: ";
                    cin.getline(new_name, 30);
                    strcpy(student->student_name, new_name);
                    break;
                }
                case 2: { // Name of advisor
                    char new_name[30] = "";
                    cout << "The original name of advisor is " << student->advisor_name << "." << endl;
                    cout << "Please input the name of advisor: ";
                    cin.getline(new_name, 30);
                    strcpy(student->advisor_name, new_name);
                    break;
                }
                case 3: { // Admit Date
                    char new_admit_date[30] = "";
                    cout << "The original admit date is " << student->admit_date << "." << endl;
                    cout << "Please input admit date: ";
                    cin.getline(new_admit_date, 30);
                    strcpy(student->admit_date, new_admit_date);
                    break;
                }
                case 4: { // Student ID
                    int new_sid;
                    cout << "The original student ID is " << student->sid << "." << endl;
                    cout << "Please input student ID: ";
                    cin >> new_sid;
                    student->sid = new_sid;
                    break;
                }
                case 5: { // Year of study
                    int new_year;
                    cout << "The original year of study is " << student->year << "." << endl;
                    cout << "Please input year of study: ";
                    cin >> new_year;
                    student->year = new_year;
                    int num_year = 0;
                    Semester *p = semester;
                    while (p != nullptr) {
                        num_year++;
                        p = p->next;
                    }
                    break;
                    char start_year[5] = "";
                    strcpy(start_year, (student->admit_date+(find_index_year(student->admit_date))));
                    for (int i = num_year; i < student->year; i++) 
                        for (int j = 0; j < 4 ; j++) {
                            Semester *temp = new Semester;
                            Semester *p = semester;
                            temp->next = nullptr;
                            temp->courses = nullptr;
                            temp->tga = temp->cga = temp->cce = 0;
                            generate_semester_period(temp, student, start_year, i, j);
                            while (p->next != nullptr)
                                p = p->next;
                            p->next = temp;
                        }
                }
            }
            cout << endl;
            break;
        } 
        case 2: { // program
            cin.clear();
            cin.sync();
            char semester_change[100] = "";
            cout << "Reminder: Please input NA if you want to change content in your first program." << endl;
            cout << "Please input the semester of changing program(e.g. 2022-23 Fall): ";
            cin.getline(semester_change, 100);
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
                while (option_data > 3 || option_data < 1) {
                    cout << "Please input valid option: ";
                    cin >> option_data;
                } 
                cin.clear();
                cin.sync();
                switch (option_data) {
                    case 1: { // Name of program
                        char new_name[50] = "";
                        cout << "The original name of program is " << p->program << "." << endl;
                        cout << "Please input new name of program: ";
                        cin.getline(new_name, 50);
                        strcpy(p->program, new_name);
                        break;
                    }
                    case 2: { // Date of changine program
                        char new_change_date[100] = "";
                        cin.clear();
                        cin.sync();
                        cout << "If you want it to be the first program that you had, please input NA." << endl;
                        cout << "The original semester of changing program is " << p->change_date << "." << endl;
                        cout << "Please input new semester of changing program: ";
                        cin.getline(new_change_date, 100);
                        Program *check = program;
                        while (check->next != nullptr) {
                            if (strcmp(check->change_date, new_change_date) == 0) {
                                cout << "You cannot change the program twice in the same semester." << endl;
                                cout << "Therefore, it is an invalid input." << endl << endl;
                                return;
                            }
                            check = check->next;
                        }
                        Program *temp = new Program;
                        strcpy(temp->change_date, new_change_date);
                        strcpy(temp->major, p->major);
                        strcpy(temp->program, p->program);
                        temp->next = nullptr;
                        char years1[8] = "";
                        int season1;
                        if (strcmp(temp->change_date, "NA") != 0)
                            generate_compare_period(temp->change_date, years1, season1);
                        else
                            strcpy(years1, "NA");
                        if (strcmp(semester_change, "NA") == 0) {
                            Program *delete_program = program;
                            program = program->next;
                            delete delete_program;
                            delete_program = nullptr;
                            Program *find = program;
                            char years2[8] = "";
                            int season2;
                            while (find->next != nullptr)
                                find = find->next;
                            generate_compare_period(find->change_date, years2, season2);
                            if (strcmp(years1, years2) > 0 || strcmp(years1, years2) == 0 && season2 < season1) 
                                find->next = temp;
                            else {
                                find = program;
                                while (find != nullptr) {
                                    char years3[8] = "";
                                    int season3;
                                    generate_compare_period(p->change_date, years2, season2);
                                    generate_compare_period(p->next->change_date, years3, season3);
                                    if (strncmp(years1, years2, 7) > 0 && strncmp(years1, years3, 7) < 0 || // Be the middle
                                        (strncmp(years1, years2, 7) == 0 && strncmp(years1, years3, 7) < 0 && season1 > season2) ||
                                        (strncmp(years1, years2, 7) > 0 && strncmp(years1, years3, 7) == 0 && season1 < season3) ||
                                        (strncmp(years1, years2, 7) == 0 && strncmp(years1, years3, 7) == 0 && season1 > season2 && season1 < season3)) {
                                        temp->next = find->next;
                                        find->next = temp;
                                        break;
                                    }
                                    find = find->next;
                                }
                            }
                            strcpy(program->change_date, "NA");
                        } else {
                            Program *find = program;
                            while (find->next != p) 
                                find = find->next;
                            Program *delete_program = find->next;
                            find->next = find->next->next;
                            delete delete_program;
                            delete_program = nullptr;
                            if (strcmp(years1, "NA") == 0) {
                                temp->next = program;
                                program = temp;
                            } else {
                                if (program->next == nullptr) {
                                    program->next = temp;
                                } else {
                                    find = program->next;
                                    char years2[8] = "";
                                    int season2;
                                    generate_compare_period(find->change_date, years2, season2);
                                    if (strcmp(years2, years1) > 0 || strcmp(years1, years2) == 0 && season1 < season2) {
                                        temp->next = program->next;
                                        program->next = temp;
                                    } else {
                                        while (find->next != nullptr)
                                            find = find->next;
                                        generate_compare_period(find->change_date, years2, season2);
                                        if (strcmp(years2, years1) < 0 || strcmp(years1, years2) == 0 && season1 > season2) 
                                            find->next = temp;
                                        else {
                                            find = program;
                                            while (find != nullptr) {
                                                char years3[8] = "";
                                            int season3;
                                            generate_compare_period(p->change_date, years2, season2);
                                            generate_compare_period(p->next->change_date, years3, season3);
                                            if (strncmp(years1, years2, 7) > 0 && strncmp(years1, years3, 7) < 0 || // Be the middle
                                                (strncmp(years1, years2, 7) == 0 && strncmp(years1, years3, 7) < 0 && season1 > season2) ||
                                                (strncmp(years1, years2, 7) > 0 && strncmp(years1, years3, 7) == 0 && season1 < season3) ||
                                                (strncmp(years1, years2, 7) == 0 && strncmp(years1, years3, 7) == 0 && season1 > season2 && season1 < season3)) {
                                                    temp->next = find->next;
                                                    find->next = temp;
                                                    break;
                                                }
                                                find = find->next;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        cout << endl;
                        break;
                    }
                    case 3: { // Name of major
                        char new_name[40] = "";
                        cout << "The original name of major is " << p->major << "." << endl;
                        cout << "Please input new name of major: ";
                        cin.getline(new_name, 40);
                        strcpy(p->major, new_name);
                        break;
                    }
                }
            }
            cout << endl;
            break;
        }
        case 4: { // course
            cin.clear();
            cin.sync();
            char semester_period[20] = "", course_code[10] = "";
            cout << "Please input the semester(e.g. 2022-23 Fall): ";
            cin.getline(semester_period, 20);
            Semester *p = semester;
            while (p != nullptr && strcmp(p->period, semester_period) != 0)
                p = p->next;
            if (p == nullptr) {
                cout << "There is no a semester of " << semester_period << "." << endl << endl;
                return;
            }
            Course *ptr = p->courses;
            cout << "Please input the course code(e.g. COMP1021): ";
            cin.getline(course_code, 10);
            while(ptr != nullptr && strcmp(ptr->code, course_code) != 0)
                ptr = ptr->next;
            if (ptr == nullptr) {
                cout << endl << "There is no course with the course code(" << course_code << ")." << endl << endl;
                return;
            }
            int option_course;
            cout << endl << "There are 5 types of content that you can change about course." << endl;
            cout << "1: Course Code" << endl;
            cout << "2: Course Title" << endl;
            cout << "3: Number of Credit" << endl;
            cout << "4: Grade" << endl;
            cout << "5: Enrolled Semester" << endl;
            cout << "Which type of content that you want to change: ";
            cin >> option_course;
            while (option_course > 5 || option_course < 1) {
                cout << "Please input valid option: ";
                cin >> option_course;
            }
            cout << endl;
            cin.clear();
            cin.sync();
            switch (option_course) {
                case 1: { // Course code
                    char new_course_code[10] = "";
                    cout << "The original course code is " << ptr->code << "." << endl;
                    cout << "Please input new course code: ";
                    cin.getline(new_course_code, 10);
                    Course *temp = new Course;
                    strcpy(temp->code, new_course_code);
                    temp->credit = ptr->credit;
                    strcpy(temp->enrolled_semester, ptr->enrolled_semester);
                    strcpy(temp->grade, ptr->grade);
                    strcpy(temp->title, ptr->title);
                    temp->next = nullptr;
                    ptr = p->courses;
                    if (strcmp(ptr->code, course_code) == 0) {
                        p->courses = ptr->next;
                        delete ptr;
                        ptr = nullptr;
                    } else {
                        while (strcmp(ptr->next->code, course_code) != 0) 
                            ptr = ptr->next;
                        Course *delete_course = ptr->next;
                        ptr->next = ptr->next->next;
                        delete delete_course;
                        delete_course = nullptr;
                    }
                    ptr = p->courses;
                    if (strcmp(ptr->code, temp->code) > 0) {
                        temp->next = ptr;
                        p->courses = temp;
                    } else {
                        while (ptr->next != nullptr) 
                            ptr = ptr->next;
                        if (strcmp(ptr->code, temp->code) < 0)
                            ptr->next = temp;
                        else {
                            ptr = p->courses;
                            while (ptr->next != nullptr && !(strcmp(ptr->code, temp->code) < 0 && strcmp(ptr->next->code, temp->code) > 0))
                                ptr = ptr->next;
                            temp->next = ptr->next;
                            ptr->next = temp;
                        }
                    }
                    break;
                }
                case 2: { // Course title
                    char new_course_title[100] = "";
                    cout << "The original couse title is " << ptr->title << "." << endl;
                    cout << "Please input new course title: ";
                    cin.getline(new_course_title, 100); 
                    strcpy(ptr->title, new_course_title);
                    break;
                }
                case 3: { // Number of credit
                    unsigned int new_course_credit = 0;
                    cout << "The original number of credit is " << ptr->credit << "." << endl;
                    cout << "Please input new number of credit: ";
                    cin >> new_course_credit;
                    ptr->credit = new_course_credit;
                    update_gpa(student, semester);
                    break;
                }
                case 4: { // Grade
                    char new_grade[3] = "";
                    cout << "The original grade is " << ptr->grade << "." << endl;
                    cout << "Please input new grade: ";
                    cin.getline(new_grade, 3);
                    strcpy(ptr->grade, new_grade);
                    update_gpa(student, semester);
                    break;
                }
                case 5: { // Enrolled semester
                    char new_semester[20] = "";
                    cout << "The original enrolled semester is " << ptr->enrolled_semester << "." << endl;
                    cout << "Please input new enrolled semester: ";
                    cin.getline(new_semester, 20);
                    Semester *find_semester = semester;
                    while (strcmp(find_semester->period, new_semester) != 0 && find_semester != nullptr)
                        find_semester = find_semester->next;
                    if (find_semester == nullptr) {
                        cout << "There is no such semester." << endl;
                        cout << "Therefore, it is an invalid input." << endl;
                    } else {
                        Course *find_course = p->courses;
                        if (find_course == ptr) {
                            p->courses = p->courses->next;
                            delete find_course;
                            find_course = nullptr;
                        } else {
                            while (find_course->next != ptr)
                                find_course = find_course->next;
                            Course *delete_course = find_course->next;
                            find_course->next = find_course->next->next;
                            delete delete_course;
                            delete_course = nullptr;
                        }
                        Course *temp = new Course;
                        strcpy(temp->code, ptr->code);
                        temp->credit = ptr->credit;
                        strcpy(temp->grade, ptr->grade);
                        strcpy(temp->title, ptr->title);
                        temp->next = nullptr;
                        strcpy(temp->enrolled_semester, new_semester);
                        delete ptr;
                        ptr = nullptr;
                        insert_course(find_semester, temp);
                        update_gpa(student, semester);
                    }
                    break;
                }
            }
            cout << endl;
            break;
        }
    }
}

// To delete some data
// option: the chosen type of data
// program: head pointer of dynamic struct program object
// semester: head pointer of dynamic struct semester object
void delete_data(const int option, Program *&program, Semester *&semester) {
    cin.clear();
    cin.sync();
    switch (option) {
        case 2: { // Program
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

                // Find the target program
                while (strcmp(p->next->change_date, change_date_delete) != 0)
                    p = p->next;
                if (p->next->next == nullptr) { // delete middle one
                    delete p->next;
                    p->next = nullptr;
                } else { // delete the last one
                    Program *ptr = p->next;
                    p->next = p->next->next;
                    delete ptr;
                    ptr = nullptr;
                }
            }
            cout << endl;
            break;
        }
        case 3: { // delete semester
            char semester_period[20] = "";
            cout << "Reminder: Deleting the semester will delete all courses that are enrolled in that semester too" << endl;
            cout << "Please input the semester(e.g. 2021-22 Fall): ";
            cin.getline(semester_period, 20);
            cout << endl;
            Semester *p = semester;
            while (p != nullptr && strcmp(p->period, semester_period) != 0) 
                p = p->next;
            if (p == nullptr) {
                cout << "There is no such that semester." << endl;
                cout << "Therefore, it is an invalid input." << endl;
            } else {
                delete_whole_course(p->courses);
                if (p == semester) { // delete the first one 
                    semester = p->next;
                    delete p;
                    p = nullptr;
                } else {
                    p = semester;
                    while (strcmp(p->next->period, semester_period) != 0)
                        p = p->next;
                    if (p->next->next == nullptr) { // delete last
                        delete p->next;
                        p->next = nullptr;
                    } else { // delete middle
                        Semester *ptr = p->next->next;
                        delete p->next;
                        p->next = ptr;
                    }
                }
                
            }
            break;
        }
        case 4: { // delete course
            char semester_period[20] = "";
            cout << "Please input the semester(e.g. 2021-22 Fall): ";
            cin.getline(semester_period, 20);
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
                        while (ptr->next != nullptr && strcmp(ptr->code, course_code) != 0) 
                            ptr = ptr->next;
                        if (ptr->next == nullptr) { // delete the last one 
                            Course *temp = p->courses;
                            while (temp->next != ptr)
                                temp = temp->next;
                            temp->next = nullptr;
                            delete ptr;
                            ptr = nullptr;
                        } else { // delete the middle one
                            Course *temp = p->courses;
                            while (temp->next != ptr)
                                temp = temp->next;
                            temp->next = ptr->next;
                            delete ptr;
                            ptr = nullptr;
                        }
                    }
                }
            }
            cout << endl;
            break;
        } 
    }
}

// To delete dynamic struct program object
// Using recursion technique to achieve that
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

// To delete dynamic struct course object
// Using recursion technique to achieve that
void delete_whole_course(Course *&course) {
    if (course == nullptr)
        return;
    else if (course->next == nullptr) {
        delete course;
        course = nullptr;
    } else {
        delete_whole_course(course->next);
        delete course;
        course = nullptr;
    }
}

// To delete dynamic struct semester object
// Need to delete all courses that being in semester struc object before deleting dynamic struct semester object
// Using recursion technique to achieve that
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

// Generate interface of the menu and return option.
int menu() {
    cin.clear();
    cin.sync();
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

// User uses this function to insert data into this program and generate csv file.
// First, inputting student's personal information. Then, inputting data of student's program. At last, inputting course information.
// Personal Information: Name of Student, Name of Advisor, Admit Date, Student ID and Number of years of study
// Program: Name of Program, Semester of changing program and Name of Major
// Course: Course Code, Course Title, Number of Credits, Grade and Enrolled Semester
void insert_csv() {
    char address[100] = "", choice[5] = "";
    int flag = 0;
    Student *temp_student = new Student;
    Program *head_program = new Program;
    Semester *head_semester = new Semester;
    cin.clear();
    cin.sync();
    cout << "Please input the address of new csv file(e.g. ./csvfile/data1.csv): ";
    cin.getline(address, 100);

    // Inputting student's personal information
    cout << endl << "First, please input the information about you." << endl;
    cout << "Please input your name: ";
    cin.getline(temp_student->student_name, 30);
    cout << "Please input your advisor's name: ";
    cin.getline(temp_student->advisor_name, 30);
    cout << "Please input your admit date(e.g. 1 September 2020): ";
    cin.getline(temp_student->admit_date, 20);
    cout << "Please input your student id: ";
    cin >> temp_student->sid;
    cout << "Please input your number of years of study: ";
    cin >> temp_student->year;
    
    // Inputting data of student's programs
    cin.clear();
    cin.sync();
    cout << endl << "Then, please input the name of the program(e.g. Bachelor Degree in School of Engineering): ";
    cin.getline(head_program->program, 50);
    cout << "Please input the name of the major(Input NA if it does not have)(e.g. Computer Science): ";
    cin.getline(head_program->major, 40);
    strcpy(head_program->change_date, "NA");
    head_program->next = nullptr;

    // To make sure the input is valid.
    cout << "Do you still want to continue to input other program(yes/no): ";
    cin.getline(choice, 5);
    while (1) {
        if (strcmp(choice, "no") == 0) {
            flag = 1;
            break;
        } else if (strcmp(choice, "yes") != 0) {
            cout << "It is an invalid input.";
            cout << "Please input again: ";
            cin.clear();
            cin.sync();
            cin.getline(choice, 5);
        }
        break;
    }
    // When the value of flag equal to 0, it means user want to keep inputting data of other programs
    while (flag == 0) {
        cin.clear();
        cin.sync();
        cout << endl;
        if (head_program->next == nullptr)
            head_program->next = insert_csv_program(flag);
        else {
            Program *temp_program = head_program;
            while (temp_program != nullptr)
                temp_program = temp_program->next;
            temp_program = insert_csv_program(flag);
        }
    }

    // Initialize the semester
    // Inputting the "name" of semester by using function of generate_semester_period()
    // Initialize the value of cce, cga tga as 0
    cin.clear();
    cin.sync();
    strcpy(choice, "");
    flag = 0;
    char start_year[5] = "";
    strcpy(start_year, (temp_student->admit_date+(find_index_year(temp_student->admit_date))));
    for (int i = 0; i < temp_student->year; i++)
        for (int j = 0; j < 4; j++) 
            if (i == 0 && j == 0) {
                head_semester->next = nullptr;
                generate_semester_period(head_semester, temp_student, start_year, i, j);
            } else {
                Semester *temp = new Semester;
                Semester *p = head_semester;
                temp->next = nullptr;
                generate_semester_period(temp, temp_student, start_year, i, j);
                while (p->next != nullptr)
                    p = p->next;
                p->next = temp;
            }
    Semester *p = head_semester;
    while (p != nullptr) {
        p->courses = nullptr;
        p->cce = p->cga = p->tga = 0;
        p = p->next;
    }

    // Inputting course information.
    cout << endl << "Next, do you want to insert course to some semesters(yes/no): ";
    cin.getline(choice, 5);
    while (strcmp(choice, "yes") != 0 && strcmp(choice, "no") != 0) {
        cout << "Please input yes or no: ";
        cin.getline(choice, 5);
    }
    while (strcmp(choice, "yes") == 0) {
        cin.clear();
        cin.sync();
        char semester_period[20] = "";
        cout << "In which semester that you enrolled that course(e.g. 2021-22 Fall): ";
        cin.getline(semester_period, 20);
        Semester *find_semester = head_semester;
        while (find_semester != nullptr && strcmp(find_semester->period, semester_period) != 0)
            find_semester = find_semester->next;
        if (find_semester == nullptr) {
            cout << "There is no such a semester." << endl;
            cout << "It is invalid input." << endl;
            break; // go back to menu
        } else {
            cin.clear();
            cin.sync();
            Course *temp = new Course;
            cout << "Next, please input the course code(e.g. COMP1021): ";
            cin.getline(temp->code, 10);
            Course *find_course = find_semester->courses;
            while (find_course != nullptr && strcmp(find_course->code, temp->code) != 0) {
                find_course = find_course->next;
                cout << "." << endl;
            }
            if (find_course != nullptr) {
                delete temp;
                temp = nullptr;
                cout << "This course code has already existed." << endl;
                cout << "Therefore, it is an invalid input." << endl;
                break; // go back to menu
            } else {
                cout << "Please input the title of the course(e.g. Introduction to Computer Science): ";
                cin.getline(temp->title, 100);
                cout << "Please input number of credits of this course: ";
                cin >> temp->credit;
                cin.clear();
                cin.sync();
                cout << "Please input the grade of this course(If it hasn't released yet, you can just input **): ";
                cin.getline(temp->grade, 3);
                strcpy(temp->enrolled_semester, find_semester->period);
                insert_course(find_semester, temp);
                temp->next = nullptr;
            }
            cout << endl << "Do you still want to continue to input other program(yes/no): ";
            cin.getline(choice, 5);
            while (strcmp(choice, "yes") != 0 && strcmp(choice, "no") != 0) {
                cout << "Please input yes or no: ";
                cin.getline(choice, 5);
            }
        } 
    }

    // Create csv file and inputting all inputted data into that csv file
    // all data are separated by comma
    cout << endl;
    ofstream ofs;
    ofs.open(address, ios::out | ios::trunc);
    Student *p_student = temp_student;
    Program *p_program = head_program;
    Semester *p_semester = head_semester;
    // Inputting data of student's programs
    ofs << endl << "student" << ","
                << p_student->student_name << ","
                << p_student->advisor_name << ","
                << p_student->sid << ","
                << p_student->year << ","
                << p_student->admit_date;
    // Inputting data of student's programs
    while (p_program != nullptr) {
        ofs << endl << "program" << ","
                    << p_program->program << ","
                    << p_program->major << ","
                    << p_program->change_date;
        p_program = p_program->next;
    }
    // Inputting data of course
    Semester *last = head_semester;
    while (last->next != nullptr)
        last = last->next;
    while (p_semester != last) {
        Course *p_course = p_semester->courses;
        while (p_course != nullptr) {
            ofs << endl << "course" << ","
                        << p_course->code << ","
                        << p_course->title << ","
                        << p_course->credit << ","
                        << p_course->grade << ","
                        << p_course->enrolled_semester;
            p_course = p_course->next;
        }
        p_semester = p_semester->next;
    }
    // Inputting data of course in the last semester
    Course *p_course = last->courses;
    while (p_course != nullptr) {
        ofs << endl << "course" << ","
                    << p_course->code << ","
                    << p_course->title << ","
                    << p_course->credit << ","
                    << p_course->grade << ","
                    << p_course->enrolled_semester;
        p_course = p_course->next;
    }
    ofs.close();
    delete_all_dynamic(temp_student, head_program, head_semester);
}

// To obtain data from csv file and store them into dynamic struct object for further processing
void read_csv(Student *&student, Program *&program, Semester *&semester, char address[]) {
    // read csv file
    string input_path;
    cout << "The path for the CSV file (e.g. ./files/student1.csv): ";
    cin >> input_path;
    ifstream fin(input_path);
    if (!fin) {
        cout << "Cannot open " << input_path << endl;
        cout << "Therefore, it is an invalid input." << endl << endl;
        return;
    }
    strcpy(address, input_path.c_str());
    cin.clear();
    cin.sync();
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
    update_gpa(student, semester);
}

// To generate transcript
// The format is following the format of unofficial transcript that generated in HKUST Student Intranet
// It can be separated into 3 parts: student's personal information, acadmic record
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

// To modify data in csv file
// Need read csv file before using this function
// First, choosing the types of data
// Then, choosing the operation that perform on that data
// Next, perform the operation to the data
// At last, over-write the original csv file by latest data
// Different types of data and different operations have different methods to do
void modify_csv(Student *&student, Program *&program, Semester *&semester, char address[]) {
    int option_data, option_modify;
    cout << endl << "Here are four types of data that you can modify:" << endl;
    cout << "1: Personal Information of Student" << endl;
    cout << "2: Information about Program" << endl;
    cout << "3: Semester" << endl;
    cout << "4: Course" << endl;
    cout << "What type of data that you want to modify(1-4): ";
    cin >> option_data;
    // To ensure the input is valid
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
    // To ensure the input is valid
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
            if (option_data != 3)
                change_data(option_data, student, program, semester);
            else {
                cout << endl << "You cannot do any changes on the contents of semester." << endl;
                cout << "If you want to do changes on the contents of courses, you should change the contents of course directly." << endl << endl;
            }
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

    // over-write the original csv file
    update_gpa(student, semester);
    ofstream ofs;
    ofs.open(address, ios::out | ios::trunc);
    Student *p_student = student;
    Program *p_program = program;
    Semester *p_semester = semester;
    ofs << endl << "student" << ","
                << p_student->student_name << ","
                << p_student->advisor_name << ","
                << p_student->sid << ","
                << p_student->year << ","
                << p_student->admit_date;
    while (p_program != nullptr) {
        ofs << endl << "program" << ","
                    << p_program->program << ","
                    << p_program->major << ","
                    << p_program->change_date;
        p_program = p_program->next;
    }
    while (p_semester != nullptr) {
        Course *p_course = p_semester->courses;
        while (p_course != nullptr) {
            ofs << endl << "course" << ","
                        << p_course->code << ","
                        << p_course->title << ","
                        << p_course->credit << ","
                        << p_course->grade << ","
                        << p_course->enrolled_semester;
            p_course = p_course->next;
        }
        p_semester = p_semester->next;
    }
    ofs.close();
}

// To delete all dynamic struct object
// First, delete dynamic struct student object
// Then, delete dynamic struct program object
// At last, delete dynamic struct semester object
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