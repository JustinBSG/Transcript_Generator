#include "../Inc/generator.hpp"

#include <iostream>

using namespace std;

Generator::~Generator() {}

void Generator::start() {
  cout << TERMINAL_TITLE << endl;
  Transcript* current = nullptr;
  while (1) {
    int option;
    cout << endl;
    cout << "Here are operations that you can choose:" << endl;
    cout << "1: Input data by yourself and form a CSV file" << endl;
    cout << "2: Input data from CSV file" << endl;
    cout << "3: Modify data that inside CSV file" << endl;
    cout << "4: Generate transcript into terminal" << endl;
    cout << "5: Make another transcript" << endl;
    cout << "6: Leave" << endl << endl;
    cout << "What operation that you want to choose(1-6): ";
    std::cin >> option;
    while (option > 6 || option < 1) {
      cout << "Please input valid choice: ";
      std::cin >> option;
    }
    cout << endl << SPLIT_LINE << endl;

    switch (option) {
      case 1:
        insert_csv(current);
        break;
      case 2:
        read_csv(current);
        break;
      case 3:
        modify_csv(current);
        break;
      case 4:
        print_all(current);
        break;
      case 5:
        restart(current);
        break;
      case 6:
        end(current);
        return;
    }
  }
}

void Generator::insert_csv(Transcript* current) {}

void Generator::read_csv(Transcript* current) {}

void Generator::modify_csv(Transcript* current) {}

void Generator::print_all(Transcript* current) {}

void Generator::restart(Transcript* current) {}

void Generator::end(Transcript* current) {}

void Generator::insert_transcript(Transcript* other_transcript) {}

void Generator::remove_transcript(int index) {}