#include "../Inc/generator.hpp"

#include <iostream>

using namespace std;

Generator::~Generator() {
  for (int i = 0; i < transcripts.size(); i++) {
    delete transcripts[i];
    transcripts[i] = nullptr;
  }
  transcripts.clear();
}

void Generator::start() {
  cout << TERMINAL_TITLE << endl;
  Transcript* current = nullptr;
  while (1) {
    int option;
    cout << endl;
    cout << "Here are operations that you can choose:" << endl;
    cout << "1: Input data by yourself" << endl;
    cout << "2: Input data from CSV file" << endl;
    cout << "3: Generate CSV file" << endl;
    cout << "4: Modify data that inside CSV file" << endl;
    cout << "5: Generate transcript into terminal" << endl;
    cout << "6: Make another transcript" << endl;
    cout << "7: Leave" << endl << endl;
    cout << "What operation that you want to choose(1-7): ";
    std::cin >> option;
    while (option > 8 || option < 1) {
      cout << "Please input valid choice: ";
      std::cin >> option;
    }
    cout << endl << SPLIT_LINE << endl;

    switch (option) {
      case 1:
        insert_data(current);
        break;
      case 2:
        read_csv(current);
        break;
      case 3:
        generate_csv(current);
        break;
      case 4:
        modify_csv(current);
        break;
      case 5:
        print_all(current);
        break;
      case 6:
        restart(current);
        break;
      case 7:
        end(current);
        return;
    }
  }
}

void Generator::insert_data(Transcript* current) {
  if (current == nullptr)
    Transcript* current = new Transcript;
  else {
    cout << "Please choose option 5 to generate another transcript." << endl;
    return;
  }

  // Input data of student class object
  cout << "First, please input the information about you." << endl;
  cout << "Please input your name: " << endl;
  // cin
  cout << "Please input your advisor's name: " << endl;
  // cin
  cout << "Please input your admit date(e.g. 1 September 2020): " << endl;
  // cin
  cout << "Please input your student id: " << endl;
  // cin
  cout << "Please input your number of years of study: " << endl;
  // cin

  // Input data of advisor
  cout << "Thenm please input the information about your advisor." << endl;
  cout << "Please input name of advisor(e.g. CHAN, Da Man): " << endl;
  // cin

  // Input data of Major or Minor
  cout << "Next, please input the information about your academics program." << endl;
  cout << "Please input name of first program(e.g. Bachelor Degree in School of "
          "Engineering): "
       << endl;
  // cin
  while (1) {
    cout << "Do you still have another Major Program?(yes/no): " << endl;
    string input_continue;
    // cin
    if (input_continue == "yes") {
      cout << "Please input name of program(e.g. Bachelor Degree of Engineering): "
           << endl;
      // cin
      cout << "Please input name of major(e.g. Computer Science): " << endl;
      // cin
      cout
        << "Please input the semester that you change program(e.g. 2022-23 Fall): "
        << endl;
      // cin
    } else
      break;
  }
  while (1) {
    cout << "Do you declare any Minor Program?(yes/no): " << endl;
    string input_continue;
    // cin
    if (input_continue == "yes") {
      cout << "Please input name of Minor Program(e.g. Smart City): " << endl;
      // cin
      cout << "Please input the semester that you declare this minor program(e.g. "
              "2022-23 Fall): "
           << endl;
      // cin
    } else
      break;
  }

  // generate semesters automatically
  BST<Semester> *temp = new BST<Semester>;
  

  transcripts.push_back(current);
}

void Generator::read_csv(Transcript* current) {}

void Generator::generate_csv(Transcript* current) {}

void Generator::modify_csv(Transcript* current) {}

void Generator::print_all(Transcript* current) {}

void Generator::restart(Transcript* current) {
  if (current != nullptr) {
    transcripts.push_back(current);
    current = nullptr;
  }
}

void Generator::end(Transcript* current) {
  cout << endl << "BYE~" << endl << endl << SPLIT_LINE << endl;

  if (current != nullptr) {
    bool contain = false;
    for (int i = 0; i < transcripts.size(); i++)
      if (transcripts[i] == current) {
        contain = true;
        break;
      }

    if (!contain) {
      delete current;
      current = nullptr;
    }
  }
}

int Generator::get_num_transcript() const { return transcripts.size(); }

void Generator::insert_transcript(Transcript* other_transcript) {
  if (other_transcript != nullptr)
    transcripts.push_back(other_transcript);
}

void Generator::remove_transcript(int index) {
  if (transcripts.size() >= index)
    return;

  delete transcripts[index];
  transcripts[index] = nullptr;
  clear_nullptr();
}

void Generator::clear_nullptr() {
  bool do_smth = false;
  for (int i = 0; i < transcripts.size(); i++)
    if (transcripts[i] == nullptr) {
      do_smth = true;
      break;
    }

  if (do_smth) {
    vector<Transcript*> temp;
    for (int i = 0; i < transcripts.size(); i++)
      if (transcripts[i] != nullptr)
        temp.push_back(transcripts[i]);
    transcripts.clear();
    transcripts = temp;
  }
}