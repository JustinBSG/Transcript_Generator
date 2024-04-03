#include "../Inc/generator.hpp"

#include <iostream>

Generator::~Generator() {
  for (Transcript* ptr : transcripts)
    delete ptr;

  transcripts.clear();
}

void Generator::start() {
  std::cout << TERMINAL_TITLE << std::endl;
  Transcript* current = nullptr;

  while (1) {
    std::cout << SPLIT_LINE << std::endl;
    int option;
    std::cout << std::endl;
    std::cout << "Here are 8 operations that you can choose:" << std::endl;
    std::cout << "1.\tInput data by yourself" << std::endl;
    std::cout << "2.\tInput data from CSV file" << std::endl;
    std::cout << "3.\tGenerate CSV file" << std::endl;
    std::cout << "4.\tModify data that inside CSV file" << std::endl;
    std::cout << "5.\tGenerate transcript into terminal" << std::endl;
    std::cout << "6.\tSave and make a new transcript" << std::endl;
    std::cout << "7.\tSave and switch to another transcript" << std::endl;
    std::cout << "8.\tLeave" << std::endl;
    std::cout << "Which operation that you want to choose(1-8): ";
    std::cin >> option;
    while (option > 10 || option < 1) {
      std::cout << "Please input valid choice(1-8): ";
      std::cin >> option;
    }
    std::cout << std::endl << SPLIT_LINE << std::endl;

    switch (option) {
      case 1:
        std::cout << option << std::endl;
        break;
      case 2:
        std::cout << option << std::endl;
        break;
      case 3:
        std::cout << option << std::endl;
        break;
      case 4:
        std::cout << option << std::endl;
        break;
      case 5:
        std::cout << option << std::endl;
        break;
      case 6:
        std::cout << option << std::endl;
        break;
      case 7:
        std::cout << option << std::endl;
        break;
      case 8:
        std::cout << option << std::endl;
        break;
      case 9:
        std::cout << option << std::endl;
        break;
    }
  }
}

void Generator::insert_data(Transcript*& current) {
  /**
   * 1. check current whether current is nullptr
   *    1.1. if not, tell user to save first and return
   *    1.2. if yes, continue
   * 2. input data in Student
   *    2.1. string name (CHAN Da Man)
   *    2.2. string admit_date (1 September 2021)
   *    2.3. string department (CSE)
   *    2.4. int ust_card_num (12345678)
   *    2.5. int year (3)
   *    2.6. Status_Program status
   *      - list out all choices and let user to choose
   *    2.7. BST<Major> majors
   *      2.7.1. string program_name (Bachelor of Engineering)
   *      2.7.2. string change_date (2022-23 Fall)
   *      2.7.3. string major_name (Electronic Engineering)
   *      - 1st time, just input 2.7.1. and 2.7.3., 2.7.2. is same as admit_date
   *      - next time, ask user whether he has majors left
   *        - yes then input 2.7.1. - 2.7.3.
   *        - no then go to 2.8.
   *      - before inputting major_name, ask user if he has the major_name
   *        - no then input "NA"
   *    2.8. BST<Minor> minors
   *      2.8.1. string change_date (2022-23 Fall)
   *      2.8.2. string minor_name (Robotics)
   *      - ask user whether he has minors left
   *        - yes then input 2.8.1. - 2.8.2.
   *        - no then go to 3.
   * 3. input data in Professor
   *    3.1. string name (CHAN Da Man)
   *    3.2. string department (CSE)
   * 4. input data in Semester
   *    4.1. According to year, generating that 4*year numbers of semester with period and save them
   * into BST<Semester*> semesters 4.2. ask user whether he has registered course in that semester
   *      4.2.1. yes then
   *        4.2.1.1. ask user whether he has input data of all courses in that semester
   *          - no then go to 4.2.1.2
   *          - yes then go to 4.3.
   *        4.2.1.2. input data of course
   *          4.2.1.2.1. string code
   *          4.2.1.2.2. string title
   *          4.2.1.2.1. string grade
   *          4.2.1.2.1. int credits
   *      4.2.2. no then go to 4.3.
   *    4.3. check whether all semesters are inputed data
   *      4.3.1. yes then return
   *      4.3.2. no then go to 4.2.
   *
   */

  if (current != nullptr) {
    std::cout << "You should save the current transcript first before inputting data." << std::endl;
    return;
  }

  std::cout << "First, please input the information about you." << std::endl;
  std::cout << "Please input your full name: ";
  std::string student_name;
  getline(std::cin, student_name);
  std::cout << "Please input your admit date(e.g. 1 September 2020): ";
  std::string student_admit_date;
  getline(std::cin, student_admit_date);
  std::cout << "Please input which department that you belong to(e.g. CSE)" << std::endl;
  std::cout << "If you haven't had a major yet, please input the school that you belongs to(e.g. SENG): ";
  std::string student_department;
  getline(std::cin, student_department);
  std::cout << "Please input your student ID card number: ";
  int student_id;
  std::cin >> student_id;
  std::cout << "Please input your years of study: ";
  int student_year;
  std::cin >> student_year;
  std::cout << "Please choose your status of study:" << std::endl;
  std::cout << "1. Active in Program" << std::endl;
  std::cout << "2. Withdraw Program" << std::endl;
  std::cout << "3. Suspend Program" << std::endl;
  std::cout << "Please input your choose in number: ";
  int student_status;
  std::cin >> student_status;
  while (student_status > 3 || student_status < 1) {
    std::cout << "Please input a valid number: ";
    std::cin >> student_status;
  }
  std::cin.ignore();
  Student* temp_student;
  temp_student = new Student{student_name, student_admit_date, student_department, student_id, student_year, static_cast<Status_Program>(student_status)};
}

void Generator::read_csv(Transcript*& current) {}

void Generator::generate_csv(Transcript*& current) {}

void Generator::modify_csv(Transcript*& current) {}

void Generator::print_terminal(Transcript*& current) {}

void Generator::save_transcript(Transcript*& current) {}

void Generator::restart(Transcript*& current) {}

void Generator::switch_transcript(Transcript*& current) {}

void Generator::end(Transcript*& current) {}