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
    cout << "1: Input data by yourself and form a CSV file" << endl;
    cout << "2: Input data from CSV file" << endl;
    cout << "3: Modify data that inside CSV file" << endl;
    cout << "4: Generate transcript into terminal" << endl;
    cout << "5: Make another transcript" << endl;
    cout << "6: Leave" << endl << endl;
    cout << "What operation that you want to choose(1-6): ";
    std::cin >> option;
    while (option > 7 || option < 1) {
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
      case 7:
        // cout << get_num_transcript() << endl;

        break;
    }
  }
}

void Generator::insert_csv(Transcript* current) {}

void Generator::read_csv(Transcript* current) {}

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