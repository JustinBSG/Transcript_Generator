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
    if (semester->courses == nullptr) // if it is empty
        semester->courses = course;
    else {
        if (strcmp(semester->courses->code, course->code) > 0) { // Be the first element
            course->next = semester->courses;
            semester->courses = course;
        } else {
            // Be the last element
            Course *p = semester->courses;
            while (p->next != nullptr) {
                p = p->next;
            }
            if (strcmp(semester->courses->code, course->code) < 0) 
                p->next = course;
            else { // Be the middle element
                p = semester->courses;
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
                    grade_float = 4.0;
                    break;
                case 'B':
                    grade_float = 3.0;
                    break;
                case 'C':
                    grade_float = 2.0;
                    break;
                case 'D':
                    grade_float = 1.0;
                    break;
                case '+':
                    grade_float = 0.3;
                    break;
                case '-':
                    grade_float = -0.3;
                    break;
                case 'P':
                    return 0;
                default:
                    break;
            }
    return grade_float;
}

// Calcalate tga, cga, cce in specific semester
void calculate_gpa(Student *&student, Semester *&semester, Semester *&semester_head) {
    int total_credit = 0;
    Course *p = semester->courses;
    while (p != nullptr) {
        if (strcmp(semester->courses->grade, "**") != 0)
            total_credit += semester->courses->credit;
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

int menu() {
    int option;
    cout << "****************************** Transcript Generator *****************************" << endl;
    cout << "=================================================================================" << endl;
    cout << "Here are operations that you can choose:" << endl;
    cout << "1: Input data by yourself and form a CSV file." << endl;
    cout << "2: Input data from CSV file." << endl;
    cout << "3: Modify data that inside CSV file." << endl;
    cout << "4: Generate transcript into terminal." << endl;
    cout << "5: Leave." << endl;
    cout << "What operation that you want to choose(1-5): ";
    cin >> option;
    while (option > 5 || option < 1) {
        cout << "Please input valid choice: ";
        cin >> option;
    }
    return option;
}

void read_csv(Student *&student, Program *&program, Semester *&semester) {
    string input_path;
    cout << "The path for the CSV file (e.g. ./files/student1.csv): ";
    cin >> input_path;
    ifstream fin(input_path);
    while (!fin) {
        cout << "Cannot open " << input_path << endl;
        cout << "Please input a valid path." << endl;
        cout << "The path for the CSV file (e.g. ./files/student1.csv): ";
        cin >> input_path;
    }

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
                // fields[1]: string, fields[2]: string, fields[3]: int, fields[4]: string, fields[5]: string 
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
    cout << "                    Unofficial Transcript of Academic Record" << endl;
    cout << "---------------------------------------------------------------------------------" << endl << endl;
    cout << "Personal Information" << endl << endl;
    cout << "Name:\t\t" << student->student_name << endl;
    cout << "Student ID:\t" << student->sid << endl;
    cout << "Year of Study:\t" << student->year << endl;
    cout << "Advisor:\t" << student->advisor_name << endl << endl;
    cout << "---------------------------------------------------------------------------------" << endl << endl;
    cout << "Academic Program" << endl << endl;
    cout << "Admit Date:\t" << student->admit_date << endl;
    cout << "Program:\t" << program->program << endl << endl;
    Program *p = program;
    while (p->next != nullptr) {
        cout << "Program Change:\t" << p->next->change_date << endl;
        cout << "Program:\t" << p->next->program << endl;
        cout << "Major:\t\t" << p->next->major << endl << endl;
        p = p->next;
    }
    cout << "---------------------------------------------------------------------------------" << endl << endl;
    Semester *ptr = semester;
    do {
        cout << "Academic Records" << endl << endl;
        cout << semester->period << endl;
        printf("%-15s%-38s%-13s%-10s%-10s\n","", "", "Credit", "Credit","");
        printf("%-15s%-38s%-13s%-10s%-10s\n","Course Code", "Course Title", "Attempted", "Earned", "Grade");
        cout << "---------------------------------------------------------------------------------" << endl << endl;
        ptr = ptr->next;
    } while (ptr != nullptr);
}

void modify_csv() {
    
}

void delete_all_dynamic(Student *&student, Program *&program, Course *&course, Semester *&semester) {

}