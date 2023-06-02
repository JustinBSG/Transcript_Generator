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
    strcpy(temp, (student->admit_date+(find_index_year(student->admit_date))));
    temp[1] = temp_start[3]+1;
    strcat(semester->period, temp);
    strcat(semester->period, " ");
    strcat(semester->period, sem);
}

int menu() {
    int option;
    cout << "************************* Transcript Generator ************************" << endl;
    cout << "=======================================================================" << endl;
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

void read_csv(Student *&student, Program *&program, Course *&course, Semester *&semester) {
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
    char *semester_period = nullptr;
    int count = 0, count_semester = 0;
    while (getline(fin, line)) {
        int i = 0;
        size_t pos = 0;
        while ((pos = line.find(',')) != string::npos) {
            fields[i++] = line.substr(0, pos);
            line.erase(0, pos+1);
        }
        fields[i] = line;
        if (count++ != 0)
            if (fields[0].compare("student") == 0) {
                // fields[1]: string, fields[2]: string, fields[3]: int, fields[4]: int
                student = new Student;
                strcpy(student->student_name, fields[1].c_str());
                strcpy(student->advisor_name, fields[2].c_str());
                student->sid = stoi(fields[3]);
                student->year = stoi(fields[4]);
                strcpy(student->admit_date, fields[5].c_str());
            } else if (fields[0].compare("program") == 0) {
                // fields[1]: string, fields[2]: string, fields[3]: string
                if (strcmp(fields[3].c_str(), "NA") == 0) {
                    program = new Program;
                    strcpy(program->program, fields[1].c_str());
                    strcpy(program->major, fields[2].c_str());
                    strcpy(program->change_date, fields[3].c_str());
                    program->next = nullptr;
                } else {
                    Program *temp = new Program;
                    Program *p = program;
                    strcpy(temp->program, fields[1].c_str());
                    strcpy(temp->major, fields[2].c_str());
                    strcpy(temp->change_date, fields[3].c_str());
                    temp->next = nullptr;
                    while (p != nullptr)
                        p = p->next;
                    p = temp;
                }
            } else if (fields[0].compare("course") == 0) {
                if (count_semester == 0) {
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
                                temp->next = nullptr;
                                generate_semester_period(temp, student, start_year, i, j);
                                Semester *p = semester;
                                while (p != nullptr)
                                    p = p->next;
                                p = temp;
                            }
                }
                // fields[1]: string, fields[2]: string, fields[3]: int, fields[4]: string, fields[5]: string 
                // course = new Course;
                // strcpy(course->code, fields[1].c_str());
                // strcpy(course->title, fields[2].c_str());
                // course->credit = stoi(fields[3]);
                // strcpy(course->grade, fields[4].c_str());
                // strcpy(course->enrolled_semester, fields[5].c_str());    
            }
    }
}

void modify_csv() {
    
}

void calculate_gpa(Semester *&semester) {

}