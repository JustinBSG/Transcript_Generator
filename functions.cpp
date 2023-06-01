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

void readcsv() {
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
    string fields[5] = "";
    while (getline(fin, line)) {
        int i = 0;
        size_t pos = 0;
        while ((pos = line.find(',')) != string::npos) {
            fields[i++] = line.substr(0, pos);
            line.erase(0, pos+1);
        }
        fields[i] = line;
        for (int i = 0; i < 6; i++)
            cout << fields[i] << "||";
        cout << endl;
    }
}

void modifycsv() {
    
}