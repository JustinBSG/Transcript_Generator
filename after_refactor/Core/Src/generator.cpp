#include "../Inc/generator.hpp"

#include <iostream>
#include <stdexcept>

Generator::~Generator() {
  for (Transcript* ptr : transcripts)
    delete ptr;

  transcripts.clear();
}

void Generator::start() {
  std::cout << TERMINAL_TITLE << std::endl;
  Transcript* current = nullptr;

  while (1) {
    std::cout << SPLIT_LINE << std::endl << std::endl;
    int option;
    std::cout << "Here are 8 operations that you can choose:" << std::endl;
    std::cout << "1.\tInput data by yourself" << std::endl;
    std::cout << "2.\tInput data from CSV file" << std::endl;
    std::cout << "3.\tGenerate CSV file" << std::endl;
    std::cout << "4.\tModify data that inside CSV file" << std::endl;
    std::cout << "5.\tGenerate transcript into terminal" << std::endl;
    std::cout << "6.\tSave the current transcript" << std::endl;
    std::cout << "7.\tMake a new transcript" << std::endl;
    std::cout << "8.\tSwitch to another transcript" << std::endl;
    std::cout << "9.\tLeave" << std::endl;
    std::cout << "Which operation that you want to choose(1-8): ";
    std::cin >> option;
    while (option > 11 || option < 1) {
      std::cout << "Please input valid choice(1-8): ";
      std::cin >> option;
    }
    std::cout << std::endl << SPLIT_LINE << std::endl;

    switch (option) {
      case 1:
        std::cout << std::endl;
        insert_data(current);
        std::cout << std::endl;
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
        std::cout << std::endl;
        save_transcript(current);
        std::cout << std::endl;
        break;
      case 7:
        std::cout << std::endl;
        restart(current);
        std::cout << std::endl;
        break;
      case 8:
        std::cout << std::endl;
        switch_transcript(current);
        std::cout << std::endl;
        break;
      case 9:
        std::cout << std::endl;
        end(current);
        std::cout << std::endl << SPLIT_LINE << std::endl;
        return;
      case 10:
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

  // Input data of user
  std::cout << "First, please input the information about you." << std::endl;
  std::cout << "Please input your full name(e.g. CHAN Da Man): ";
  std::string student_name;
  getline(std::cin, student_name);
  std::cout << "Please input your admit date(e.g. 1 September 2020): ";
  std::string student_admit_date;
  getline(std::cin, student_admit_date);
  std::cout << "Please input which department that you belong to(e.g. CSE)" << std::endl;
  std::cout
    << "If you haven't had a major yet, please input the school that you belongs to(e.g. SENG): ";
  std::string student_department;
  getline(std::cin, student_department);
  std::cout << "Please input your student ID card number(e.g. 12345678): ";
  int student_id;
  std::cin >> student_id;
  std::cout << "Please input your years of study(e.g. 3): ";
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
  Student temp_student{student_name,       student_admit_date,
                       student_department, student_id,
                       student_year,       static_cast<Status_Program>(student_status)};

  // Input data of Major and Minor
  std::cout << "Then, please input the information about your academic program." << std::endl;
  std::cout << "Please input the information about your first major program." << std::endl;
  std::cout
    << "Please input the name of first program(e.g. Bachelor Degree in School of Engineering): ";
  std::string first_program_name;
  getline(std::cin, first_program_name);
  std::cout << "Please input the name of major(e.g. Computer Science)(if you haven't had major "
               "yet, please input NA): ";
  std::string first_major_name;
  getline(std::cin, first_major_name);
  Major first_major{first_program_name, "NA", first_major_name};
  while (1) {
    std::cout << "Do you still have another Major Program?(yes/no): ";
    std::string input_choice;
    getline(std::cin, input_choice);
    while (input_choice != "yes" && input_choice != "no") {
      std::cout << "Please valid choice(yes/no): ";
      getline(std::cin, input_choice);
    }
    if (input_choice == "no")
      break;
    std::cout << "Please input the name of program(e.g. Bachelor Degree of Engineering): ";
    std::string temp_program_name;
    std::cout << "Please input the name of Major Program(e.g. Computer Science): ";
    std::string temp_major_name;
    getline(std::cin, temp_major_name);
    std::cout << "Please input the semester that you change program(e.g. 2022-23 Fall): ";
    std::string temp_change_date;
    getline(std::cin, temp_change_date);
    Major temp_major{temp_program_name, temp_change_date, temp_major_name};
    temp_student.insert_major(temp_major);
  }
  while (1) {
    std::cout << "Do you declare any Minor Program?(yes/no): ";
    std::string input_choice;
    while (input_choice != "yes" && input_choice != "no") {
      std::cout << "Please valid choice(yes/no): ";
      getline(std::cin, input_choice);
    }
    if (input_choice == "no")
      break;
    std::cout << "Please the name of Minor Program(e.g. Smart City): ";
    std::string temp_minor_name;
    getline(std::cin, temp_minor_name);
    std::cout
      << "Please input the semester that you declare this Minor program(e.g. 2022-23 Fall): ";
    std::string temp_change_period;
    getline(std::cin, temp_change_period);
    Minor temp_minor{"NA", temp_change_period, temp_minor_name};
    temp_student.insert_minor(temp_minor);
  }

  // Input data of advisor
  std::cout << "Next, please input the information about your advisor." << std::endl;
  std::cout << "Please input the name of your advisor(e.g. CHAN Da Man): ";
  std::string advisor_name;
  getline(std::cin, advisor_name);
  Professor temp_advisor{advisor_name, "NA", temp_student.get_department()};

  // Input data of semester
  BST<Semester> temp_semesters;
  auto_input_period_semesters(temp_semesters, temp_student.get_year(),
                              temp_student.get_admit_date());
  std::cout << "After that, please input the information of each semester." << std::endl;
  if (temp_semesters.size() != 0) {
    for (int i = 1; i <= temp_student.get_year() * 4; i++) {
      std::cout << std::endl;
      Semester* temp_semester = &(temp_semesters.find_kth_smallest_node(i)->data);
      std::cout << "Please input the course code of one course that you have enrolled in "
                << temp_semester->get_period()
                << "(you can type NA if there is no remaining course left): ";
      std::string temp_course_code;
      getline(std::cin, temp_course_code);
      if (temp_course_code == "NA")
        continue;
      std::cout << "Please input the course title of this course: ";
      std::string temp_course_title;
      getline(std::cin, temp_course_title);
      std::cout << "Please input the number of credits of this course: ";
      int temp_course_num_credit;
      std::cin >> temp_course_num_credit;
      std::cin.ignore();
      std::cout << "Please input the grade that you got in this course: ";
      std::string temp_course_grade;
      getline(std::cin, temp_course_grade);

      Course temp_course{temp_course_code, temp_course_title, temp_course_grade,
                         temp_course_num_credit};
      temp_semester->insert_course(temp_course);
    }
  }
  current = new Transcript{};
  current->change_user(&temp_student);
  current->change_advisor(&temp_advisor);
  current->change_semesters(&temp_semesters);
}

void Generator::read_csv(Transcript*& current) {}

void Generator::generate_csv(Transcript*& current) {}

void Generator::modify_csv(Transcript*& current) {}

void Generator::print_terminal(Transcript*& current) {}

void Generator::save_transcript(Transcript*& current) {
  if (current == nullptr) {
    std::cout << "Make sure you have created a new transcript and input data into the system."
              << std::endl;
    return;
  }

  std::cout << "Saved~" << std::endl;
  for (int i = 0; i < transcripts.size(); i++) {
    if (transcripts[i] == current)
      return;
  }

  transcripts.push_back(current);
}

void Generator::restart(Transcript*& current) { 
  if (current != nullptr && !contain(current)) {
    std::cout << "Make sure you have saved the current transcript first before switching to "
                 "another transcript."
              << std::endl;
    return;
  }

  current = nullptr; 
}

void Generator::switch_transcript(Transcript*& current) {
  if (transcripts.size() == 0) {
    std::cout << "There is no saved transcript." << std::endl;
    std::cout << "Make sure you have created and saved a new transcript before switching to "
                 "another transcript."
              << std::endl;
    return;
  }

  if (current != nullptr && !contain(current)) {
    std::cout << "Make sure you have saved the current transcript first before switching to "
                 "another transcript."
              << std::endl;
    return;
  }

  std::cout << "There " << (transcripts.size() == 1 ? "is " : "are ") << transcripts.size() << " "
            << (transcripts.size() == 1 ? "transcript" : "transcripts") << "." << std::endl;
  for (int i = 0; i < transcripts.size(); i++)
    std::cout << i + 1 << ": " << transcripts[i]->get_print_date() << std::endl;
  std::cout << "Which transcript that you want to switch to?" << std::endl;
  std::cout << "Please input the index number(e.g. 1): ";
  int index;
  std::cin >> index;
  while (index <= 0 || index > transcripts.size()) {
    std::cout << "Please input a valid index number in range of 1 - " << transcripts.size() << ": ";
    std::cin >> index;
  }
  std::cin.ignore();
  current = transcripts[index];
}

void Generator::end(Transcript*& current) {
  std::cout << "BYE~" << std::endl;

  /**
   * x Case 1: current == nullptr && transcript is empty
   * x Case 2: current == nullptr && transcript is not empty
   * x Case 3: current != nullptr && transcript is empty
   * x Case 4: current != nullptr && transcript is not empty && transcript does not contain current
   * x Case 5: current != nullptr && transcript is not empty && transcript contains current
   *
   */

  bool current_exist = false;
  if (current != nullptr) {
    delete current;
    current_exist = true;
    if (transcripts.size() == 0)
      return;
  }

  while (transcripts.size() != 0) {
    if (current_exist && transcripts[0] == current)
      transcripts.erase(transcripts.begin());
    else
      remove_transcript(0);
  }
}

void Generator::remove_transcript(int index) {
  if (transcripts.size() >= index) {
    std::cout << "Index = " << index << " is not found." << std::endl;
    return;
  }

  delete transcripts[index];
  transcripts[index] = nullptr;
  transcripts.erase(transcripts.begin() + index);
}

void Generator::auto_input_period_semesters(BST<Semester>& semesters, int num_year,
                                            std::string admit_date) {
  std::vector<std::string> result;
  std::string temp;
  std::istringstream iss{admit_date};
  while (getline(iss, temp, ' '))
    result.push_back(temp);
  int year = stoi(result[2]);
  for (int i = 0; i < num_year * 4; i++) {
    std::string temp_period;
    if (i > 3 && i % 4 == 0)
      year++;
    temp_period += std::to_string(year);
    temp_period += "-";
    temp_period += std::to_string(year % 1000 % 100 + 1);
    temp_period += " ";
    switch (i % 4) {
      case 0:
        temp_period += "Fall";
        break;
      case 1:
        temp_period += "Winter";
        break;
      case 2:
        temp_period += "Spring";
        break;
      case 3:
        temp_period += "Summer";
        break;
    }
    Semester temp_semester{temp_period};
    semesters.insert(temp_semester);
  }
}

bool Generator::contain(Transcript* current) {
  std::vector<Transcript*>::iterator check_saved =
    std::find(transcripts.begin(), transcripts.end(), current);
  return (check_saved != transcripts.end());
}