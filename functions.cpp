#include "functions.h"
using namespace std;

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

void readcsv(Student *&student, Program *&program, Course *&course, Semester *&semester) {
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
    Program *program_ptr = nullptr;
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
            } else if (fields[0].compare("program") == 0) {
                // fields[1]: string, fields[2]: string, fields[3]: string
                if (strcmp(fields[3].c_str(), "NA") == 0) {
                    program = new Program;
                    strcpy(program->program, fields[1].c_str());
                    strcpy(program->major, fields[2].c_str());
                    strcpy(program->change_date, fields[3].c_str());
                    program->next = nullptr;
                    program_ptr = program->next;
                } else {
                    Program *temp = new Program;
                    strcpy(temp->program, fields[1].c_str());
                    strcpy(temp->major, fields[2].c_str());
                    strcpy(temp->change_date, fields[3].c_str());
                    temp->next = nullptr;
                    program_ptr = temp;
                    program_ptr = temp->next;
                }
            } else if (fields[0].compare("course") == 0) {
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

void modifycsv() {
    
}