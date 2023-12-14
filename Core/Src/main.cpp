#include <iomanip>
#include <iostream>
#include <string>

#include "../Inc/transcript.hpp"

namespace menu {
#define TERMINAL_MAX_WIDTH 84

  const std::string SPLIT_LINE =
      "====================================================================================";

  void insert_csv(Transcript *transcript) {}

  void read_csv(Transcript *transcript) {}

  void modify_csv(Transcript *transcript) {}

  void print_all(Transcript *transcript) {}

  void restart(Transcript *transcript) {}

  void end(Transcript *transcript) {}

  void title() {
    std::cout << "******************************* Transcript Generator "
                 "*******************************"
              << std::endl;
    std::cout << SPLIT_LINE << std::endl;
  }

  void option(Transcript *transcript) {
    while (1) {
      int option;
      std::cout << std::endl;
      std::cout << "Here are operations that you can choose:" << std::endl;
      std::cout << "1: Input data by yourself and form a CSV file" << std::endl;
      std::cout << "2: Input data from CSV file" << std::endl;
      std::cout << "3: Modify data that inside CSV file" << std::endl;
      std::cout << "4: Generate transcript into terminal" << std::endl;
      std::cout << "5: Make another transcript" << std::endl;
      std::cout << "6: Leave" << std::endl << std::endl;
      std::cout << "What operation that you want to choose(1-6): ";
      std::cin >> option;
      while (option > 7 || option < 1) {
        std::cout << "Please input valid choice: ";
        std::cin >> option;
      }
      std::cout << std::endl << SPLIT_LINE << std::endl;

      switch (option) {
        case 1:
          insert_csv(transcript);
          break;
        case 2:
          read_csv(transcript);
          break;
        case 3:
          modify_csv(transcript);
          break;
        case 4:
          print_all(transcript);
          break;
        case 5:
          restart(transcript);
          break;
        case 6:
          end(transcript);
          return;
      }
    }
  }

  void start() {
    title();
    Transcript *transcript = nullptr;
    while (1) {
      option(transcript);
      break;
    }
  }
};  // namespace menu

int main() {
  menu::start();
  return 0;
}