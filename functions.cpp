#include "functions.h"
using namespace std;

int menu () {
    int option;
    cout << "************************* Transcript Generator ************************" << endl;
    cout << "=======================================================================" << endl;
    cout << "Here are operations that you can choose:" << endl;
    cout << "1: Input data by yourself and form a CSV file." << endl;
    cout << "2: Input data from CSV file." << endl;
    cout << "3: Modify data that inside CSV file." << endl;
    cout << "4: Generate transcript into terminal." << endl;
    cout << "5: Leave." << endl;
    cout << "What operation that you want to choose: ";
    cin >> option;
    while (option > 5 || option < 1) {
        cout << "Please input valid choice: ";
        cin >> option;
    }
    return option;
}