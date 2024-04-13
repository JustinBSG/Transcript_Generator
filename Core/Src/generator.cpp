#include "../Inc/generator.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace fs = std::__fs::filesystem;

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
    std::cout << "3.\tGenerate CSV file by using current transcript" << std::endl;
    std::cout << "4.\tModify data that inside CSV file" << std::endl;
    std::cout << "5.\tGenerate transcript into terminal" << std::endl;
    std::cout << "6.\tSave the current transcript" << std::endl;
    std::cout << "7.\tMake a new transcript" << std::endl;
    std::cout << "8.\tSwitch to another transcript" << std::endl;
    std::cout << "9.\tLeave" << std::endl;
    std::cout << "Which operation that you want to choose(1-9): ";
    std::cin >> option;
    while (option > 11 || option < 1) {
      std::cout << "Please input valid choice(1-8): ";
      std::cin >> option;
    }
    std::cin.ignore();
    std::cout << std::endl << SPLIT_LINE << std::endl;

    switch (option) {
      case 1:
        std::cout << std::endl;
        insert_data(current);
        std::cout << std::endl;
        break;
      case 2:
        std::cout << std::endl;
        read_csv(current);
        std::cout << std::endl;
        break;
      case 3:
        std::cout << std::endl;
        generate_csv(current);
        std::cout << std::endl;
        break;
      case 4:
        std::cout << std::endl;
        modify_csv(current);
        std::cout << std::endl;
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
        std::cout << std::endl;
        print_test(current);
        std::cout << std::endl;
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
    std::cout << "You should switch to the another transcript first before inputting data."
              << std::endl;
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
    getline(std::cin, temp_program_name);
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
    getline(std::cin, input_choice);
    while (input_choice != "yes" && input_choice != "no") {
      std::cout << "Please valid choice(yes/no): ";
      getline(std::cin, input_choice);
    }
    if (input_choice == "no")
      break;
    std::cout << "Please input the name of Minor Program(e.g. Smart City): ";
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
      i--;
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

void Generator::read_csv(Transcript*& current, std::string file_path) {
  if (current != nullptr) {
    std::cout << "Please save the current transcript and make a new transcript before inserting "
                 "data from CSV file."
              << std::endl;
    return;
  }

  if (file_path.size() == 0) {
    std::cout << "Please input the file path of the CSV file: ";
    getline(std::cin, file_path);
  }

  std::ifstream csv_file{file_path};
  while (!csv_file.is_open()) {
    std::cout << "Failed to open CSV file." << std::endl;
    return;
  }

  std::vector<std::vector<std::string>> data;
  std::string line;
  while (getline(csv_file, line)) {
    std::istringstream each_line{line};
    std::vector<std::string> fields;
    std::string field;
    while (getline(each_line, field, ','))
      fields.push_back(field);
    data.push_back(fields);
  }
  csv_file.close();

  Student* temp_student = new Student;
  Professor* temp_advisor = new Professor;
  BST<Semester>* temp_semesters = new BST<Semester>;
  current = new Transcript{temp_student, temp_advisor, temp_semesters};

  for (int i = 0; i < data.size(); i++) {
    if (data[i][0] == "transcript")
      current->change_print_date(data[i][1]);
    else if (data[i][0] == "student") {
      temp_student->change_name(data[i][1]);
      temp_student->change_admit_date(data[i][2]);
      temp_student->change_department(data[i][3]);
      temp_student->change_ust_card_num(std::stoi(data[i][4]));
      temp_student->change_year(std::stoi(data[i][5]));
      temp_student->change_status(temp_student->convert_string_status(data[i][6]));
    } else if (data[i][0] == "advisor") {
      temp_advisor->change_name(data[i][1]);
      temp_advisor->change_department(data[i][2]);
    } else if (data[i][0] == "major") {
      Major temp_major{data[i][1], data[i][2], data[i][3]};
      temp_student->insert_major(temp_major);
    } else if (data[i][0] == "minor") {
      Minor temp_minor{data[i][1], data[i][2], data[i][3]};
      temp_student->insert_minor(temp_minor);
    } else if (data[i][0] == "course") {
      Semester* temp_semester = nullptr;
      for (int j = 1; j <= temp_semesters->size(); j++)
        if (temp_semesters->find_kth_smallest_node(j)->data.get_period() == data[i][5])
          temp_semester = &(temp_semesters->find_kth_smallest_node(j)->data);
      Course temp_course{data[i][1], data[i][2], data[i][3], std::stoi(data[i][4])};
      temp_semester->insert_course(temp_course);
    } else if (data[i][0] == "semester") {
      Semester temp_semester{data[i][1]};
      temp_semesters->insert(temp_semester);
    }
  }

  std::cout << "Read~" << std::endl;
}

void Generator::generate_csv(Transcript*& current, std::string file_path) {
  if (current == nullptr) {
    std::cout << "Please input data to current transcript first before generating CSV file."
              << std::endl;
    return;
  }
  if (current == nullptr) {
    std::cout << "Please input data to current transcript first before generating CSV file."
              << std::endl;
    return;
  }

  if (file_path.size() == 0) {
    file_path = "Output/output";
    std::string format = "output";
    int count = 0;
    for (const auto& entry : fs::directory_iterator("Output")) {
      if (fs::is_regular_file(entry) &&
          entry.path().filename().string().find(format) != std::string::npos) {
        count++;
      }
    }
    file_path += std::to_string(count);
    file_path += ".csv";
  }

  std::ofstream output_file{file_path};
  if (!output_file.is_open()) {
    std::cout << "Failed to open output file." << std::endl;
    std::cout << output_file.rdstate() << std::endl;
    return;
  }

  std::vector<std::vector<std::string>> data;
  // input data of transcript
  std::vector<std::string> vector_transcript;
  vector_transcript.push_back("transcript");
  vector_transcript.push_back(current->get_print_date());
  data.push_back(vector_transcript);

  // input data of student
  std::vector<std::string> vector_student;
  Student* temp_student = current->get_user();
  vector_student.push_back("student");
  vector_student.push_back(temp_student->get_name());
  vector_student.push_back(temp_student->get_admit_date());
  vector_student.push_back(temp_student->get_department());
  vector_student.push_back(std::to_string(temp_student->get_ust_card_num()));
  vector_student.push_back(std::to_string(temp_student->get_year()));
  vector_student.push_back(temp_student->get_status());
  data.push_back(vector_student);

  // input data of major
  for (int i = 0; i < temp_student->get_majors().size(); i++) {
    std::vector<std::string> vector_major;
    Major* temp_major = &(temp_student->get_majors().find_kth_smallest_node(i + 1)->data);
    vector_major.push_back("major");
    vector_major.push_back(temp_major->get_program_name());
    vector_major.push_back(temp_major->get_change_date());
    vector_major.push_back(temp_major->get_major_name());
    data.push_back(vector_major);
  }

  // input data of minor
  for (int i = 0; i < temp_student->get_minors().size(); i++) {
    std::vector<std::string> vector_minor;
    Minor* temp_minor = &(temp_student->get_minors().find_kth_smallest_node(i + 1)->data);
    vector_minor.push_back("minor");
    vector_minor.push_back(temp_minor->get_program_name());
    vector_minor.push_back(temp_minor->get_change_date());
    vector_minor.push_back(temp_minor->get_minor_name());
    data.push_back(vector_minor);
  }

  // input data of advisor
  std::vector<std::string> vector_advisor;
  Professor* temp_advisor = current->get_advisor();
  vector_advisor.push_back("advisor");
  vector_advisor.push_back(temp_advisor->get_name());
  vector_advisor.push_back(temp_advisor->get_department());
  data.push_back(vector_advisor);

  // input data of semesters
  for (int i = 0; i < current->get_semesters()->size(); i++) {
    Semester* temp_semester = &(current->get_semesters()->find_kth_smallest_node(i + 1)->data);
    std::vector<std::string> vector_semester;
    vector_semester.push_back("semester");
    vector_semester.push_back(temp_semester->get_period());
    data.push_back(vector_semester);

    // input data of courses in this semester
    for (int i = 0; i < temp_semester->get_courses().size(); i++) {
      Course* temp_course = &(temp_semester->get_courses().find_kth_smallest_node(i + 1)->data);
      std::vector<std::string> vector_course;
      vector_course.push_back("course");
      vector_course.push_back(temp_course->get_code());
      vector_course.push_back(temp_course->get_title());
      vector_course.push_back(temp_course->get_grade_str());
      vector_course.push_back(std::to_string(temp_course->get_credits()));
      vector_course.push_back(temp_semester->get_period());
      data.push_back(vector_course);
    }
  }

  // write data into the CSV file
  for (const std::vector<std::string>& row : data) {
    for (const std::string& field : row)
      output_file << field << ',';
    output_file << "\n";
  }

  output_file.close();
  std::cout << "Generated~" << std::endl;
}

// TODO: Check for empty data before performing any operation
void Generator::modify_csv(Transcript*& current, std::string file_path) {
  if (current != nullptr) {
    std::cout << "Please save the current transcript first before modifying the CSV file."
              << std::endl;
    return;
  }

  if (file_path.size() == 0) {
    if (file_path.size() == 0) {
      std::cout << "Please input the file path of the CSV file: ";
      getline(std::cin, file_path);
    }
  }

  std::cout << std::endl;
  read_csv(current, file_path);
  if (current == nullptr)
    return;
  std::cout << std::endl;

  std::cout << "Which operation that you want to perform?" << std::endl;
  std::cout << "1.\tAdding new data" << std::endl;
  std::cout << "2.\tRemoving existing data" << std::endl;
  std::cout << "3.\tEditing existing data" << std::endl;
  std::cout << "Please input the index number of the choice: ";
  int choice;
  std::cin >> choice;
  std::cin.ignore();
  while (choice < 1 || choice > 3) {
    std::cout << "Please input valid choice: ";
    std::cin >> choice;
    std::cin.ignore();
  }
  std::cout << std::endl;

  switch (choice) {
    // add
    case 1: {
      std::cout << "Which data that you want to add?" << std::endl;
      std::cout << "1.\tStudent" << std::endl;
      std::cout << "2.\tSemester" << std::endl;
      std::cout << "3.\tCourse" << std::endl;
      std::cout << "Please input the index number of the choice: ";
      int choice_data;
      std::cin >> choice_data;
      std::cin.ignore();
      while (choice_data < 1 || choice_data > 3) {
        std::cout << "Please input valid choice: ";
        std::cin >> choice_data;
        std::cin.ignore();
      }
      std::cout << std::endl;

      switch (choice_data) {
        // student
        case 1: {
          if (current->get_user() == nullptr) {
            std::cout << "There is no any data about Student in that CSV file." << std::endl;
            std::cout << "Therefore, you can only add all data about Student here." << std::endl;
            std::cout << "First, please input the information about you." << std::endl;
            std::cout << "Please input your full name(e.g. CHAN Da Man): ";
            std::string student_name;
            getline(std::cin, student_name);
            std::cout << "Please input your admit date(e.g. 1 September 2020): ";
            std::string student_admit_date;
            getline(std::cin, student_admit_date);
            std::cout << "Please input which department that you belong to(e.g. CSE)" << std::endl;
            std::cout << "If you haven't had a major yet, please input the school that you belongs "
                         "to(e.g. SENG): ";
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
            std::cout << "Then, please input the information about your academic program."
                      << std::endl;
            std::cout << "Please input the information about your first major program."
                      << std::endl;
            std::cout << "Please input the name of first program(e.g. Bachelor Degree in School of "
                         "Engineering): ";
            std::string first_program_name;
            getline(std::cin, first_program_name);
            std::cout
              << "Please input the name of major(e.g. Computer Science)(if you haven't had major "
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
              std::cout
                << "Please input the name of program(e.g. Bachelor Degree of Engineering): ";
              std::string temp_program_name;
              getline(std::cin, temp_program_name);
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
              getline(std::cin, input_choice);
              while (input_choice != "yes" && input_choice != "no") {
                std::cout << "Please valid choice(yes/no): ";
                getline(std::cin, input_choice);
              }
              if (input_choice == "no")
                break;
              std::cout << "Please input the name of Minor Program(e.g. Smart City): ";
              std::string temp_minor_name;
              getline(std::cin, temp_minor_name);
              std::cout << "Please input the semester that you declare this Minor program(e.g. "
                           "2022-23 Fall): ";
              std::string temp_change_period;
              getline(std::cin, temp_change_period);
              Minor temp_minor{"NA", temp_change_period, temp_minor_name};
              temp_student.insert_minor(temp_minor);
            }
            current->change_user(&temp_student);
          } else {
            std::cout << "Which data that you want to add?" << std::endl;
            std::cout << "1.\tMajor" << std::endl;
            std::cout << "2.\tMinor" << std::endl;
            std::cout << "Please input the index number of the choice: ";
            std::cin >> choice;
            std::cin.ignore();
            while (choice < 1 || choice > 2) {
              std::cout << "Please input valid choice: ";
              std::cin >> choice;
              std::cin.ignore();
            }
            std::cout << std::endl;

            switch (choice) {
              // major
              case 1: {
                std::cout
                  << "Please input the name of program(e.g. Bachelor Degree of Engineering): ";
                std::string temp_program_name;
                getline(std::cin, temp_program_name);
                std::cout << "Please input the name of Major Program(e.g. Computer Science): ";
                std::string temp_major_name;
                getline(std::cin, temp_major_name);
                std::cout
                  << "Please input the semester that you change program(e.g. 2022-23 Fall): ";
                std::string temp_change_date;
                getline(std::cin, temp_change_date);
                Major temp_major{temp_program_name, temp_change_date, temp_major_name};
                current->get_user()->insert_major(temp_major);
                break;
              }
              // minor
              case 2: {
                std::cout << "Please input the name of Minor Program(e.g. Smart City): ";
                std::string temp_minor_name;
                getline(std::cin, temp_minor_name);
                std::cout << "Please input the semester that you declare this Minor program(e.g. "
                             "2022-23 Fall): ";
                std::string temp_change_period;
                getline(std::cin, temp_change_period);
                Minor temp_minor{"NA", temp_change_period, temp_minor_name};
                current->get_user()->insert_minor(temp_minor);
                break;
              }
            }
          }
          break;
        }
        // semester
        case 2: {
          std::cout << "Please input the period of semester(e.g. 2022-23 Fall: ";
          std::string temp_period;
          getline(std::cin, temp_period);
          if (current->get_semesters() == nullptr) {
            BST<Semester>* temp_semesters = new BST<Semester>;
            temp_semesters->insert(Semester{temp_period});
            current->change_semesters(temp_semesters);
            return;
          }

          while (current->get_semesters()->contain(Semester{temp_period})) {
            std::cout << "semester of " << temp_period << "has already existed." << std::endl;
            std::cout << "Please input the period of semester again(e.g. 2022-23 Fall): ";
            std::string temp_period;
            getline(std::cin, temp_period);
          }
          current->get_semesters()->insert(Semester{temp_period});
          break;
        }
        // course
        case 3: {
          if (current->get_semesters() == nullptr || current->get_semesters()->size() == 0) {
            std::cout << "There is no semester in the CSV file." << std::endl;
            std::cout << "Please input a new semester before adding a new course." << std::endl;
            return;
          }
          std::cout << "Which semester that the new course belongs to?" << std::endl;
          for (int i = 1; i <= current->get_semesters()->size(); i++)
            std::cout << i << ".\t"
                      << current->get_semesters()->find_kth_smallest_node(i)->data.get_period()
                      << std::endl;
          std::cout << current->get_semesters()->size() + 1 << ".\tOther" << std::endl;
          std::cout << "Please input the index number of your choice: ";
          std::cin >> choice;
          std::cin.ignore();
          while (choice < 1 || choice > current->get_semesters()->size() + 1) {
            std::cout << "Please input valid choice: ";
            std::cin >> choice;
            std::cin.ignore();
          }
          std::cout << std::endl;

          if (choice == current->get_semesters()->size() + 1) {
            std::cout << "Please add that semester first." << std::endl;
            return;
          }
          Semester* temp_semester =
            &(current->get_semesters()->find_kth_smallest_node(choice)->data);
          std::cout << "Please input the Course Code(e.g. COMP1021): ";
          std::string temp_code;
          getline(std::cin, temp_code);
          while (temp_semester->get_courses().contain(Course{temp_code})) {
            std::cout << "That Course Code has already existed." << std::endl;
            std::cout << "Please enter another one: ";
            getline(std::cin, temp_code);
          }
          std::cout << "Please input the Course Title of this course: ";
          std::string temp_course_title;
          getline(std::cin, temp_course_title);
          std::cout << "Please input the Number of Credits of this course: ";
          int temp_course_num_credit;
          std::cin >> temp_course_num_credit;
          std::cin.ignore();
          std::cout << "Please input the Grade that you got in this course: ";
          std::string temp_course_grade;
          getline(std::cin, temp_course_grade);
          temp_semester->insert_course(
            Course{temp_code, temp_course_title, temp_course_grade, temp_course_num_credit});
          current->update_CGAs();
          break;
        }
      }
      break;
    }
    // remove
    case 2: {
      std::cout << "Which data that you want to remove?" << std::endl;
      std::cout << "1.\tStudent" << std::endl;
      std::cout << "2.\tSemester" << std::endl;
      std::cout << "3.\tCourse" << std::endl;
      std::cout << "Please input the index number of the choice: ";
      std::cin >> choice;
      std::cin.ignore();
      while (choice < 1 || choice > 3) {
        std::cout << "Please input valid choice: ";
        std::cin >> choice;
        std::cin.ignore();
      }
      std::cout << std::endl;

      switch (choice) {
        // student
        case 1: {
          if (current->get_user() == nullptr) {
            std::cout << "There is no any data about Student in the CSV file." << std::endl;
            std::cout << "Please input a new Student before removing data in Student." << std::endl;
            return;
          }

          std::cout << "Which data in Student that you want to remove?" << std::endl;
          std::cout << "1.\tMajor" << std::endl;
          std::cout << "2.\tMinor" << std::endl;
          std::cout << "Please input the index number of the choice: ";
          std::cin >> choice;
          std::cin.ignore();
          while (choice < 1 || choice > 2) {
            std::cout << "Please input valid choice: ";
            std::cin >> choice;
            std::cin.ignore();
          }
          std::cout << std::endl;

          switch (choice) {
            // major
            case 1: {
              if (current->get_user()->get_majors().size() == 0) {
                std::cout << "There is no taken Major." << std::endl;
                std::cout << "Please make sure there is a Major before removing it." << std::endl;
                return;
              }

              BST<Major>* temp_majors = &(current->get_user()->get_majors());
              std::cout << "There is " << temp_majors->size() << "Major in that CSV file."
                        << std::endl;
              std::cout << "Which Major that you want to remove?" << std::endl;
              for (int i = 1; i <= temp_majors->size(); i++)
                std::cout << i << ".\t"
                          << temp_majors->find_kth_smallest_node(1)->data.get_major_name()
                          << std::endl;
              std::cout << "Please input the index nubmer of the choice: ";
              std::cin >> choice;
              std::cin.ignore();
              while (choice < 1 || choice > temp_majors->size()) {
                std::cout << "Please input valid choice: ";
                std::cin >> choice;
                std::cin.ignore();
              }
              std::cout << std::endl;

              temp_majors->remove(temp_majors->find_kth_smallest_node(choice)->data);
              break;
            }
            // minor
            case 2: {
              if (current->get_user()->get_minors().size() == 0) {
                std::cout << "There is no taken Minor." << std::endl;
                std::cout << "Please make sure there is a Minor before removing it." << std::endl;
                return;
              }

              BST<Minor>* temp_minors = &(current->get_user()->get_minors());
              std::cout << "There is " << temp_minors->size() << "Minor in that CSV file."
                        << std::endl;
              std::cout << "Which Minor that you want to remove?" << std::endl;
              for (int i = 1; i <= temp_minors->size(); i++)
                std::cout << i << ".\t"
                          << temp_minors->find_kth_smallest_node(1)->data.get_minor_name()
                          << std::endl;
              std::cout << "Please input the index nubmer of the choice: ";
              std::cin >> choice;
              std::cin.ignore();
              while (choice < 1 || choice > temp_minors->size()) {
                std::cout << "Please input valid choice: ";
                std::cin >> choice;
                std::cin.ignore();
              }
              std::cout << std::endl;

              temp_minors->remove(temp_minors->find_kth_smallest_node(choice)->data);
              break;
            }
          }
          break;
        }
        // semester
        case 2: {
          BST<Semester>* temp_semesters = current->get_semesters();
          if (temp_semesters == nullptr || temp_semesters->size() == 0) {
            std::cout << "There is no any semester in the CSV file." << std::endl;
            std::cout << "Please input a semester before removing it." << std::endl;
            return;
          }
          std::cout << "There is " << temp_semesters->size() << "Semesters in the CSV file."
                    << std::endl;
          std::cout << "Which Semester that you want to remove?" << std::endl;
          for (int i = 1; i <= temp_semesters->size(); i++)
            std::cout << i << ".\t" << temp_semesters->find_kth_smallest_node(i)->data.get_period()
                      << std::endl;
          std::cout << "Please input the index nubmer of the choice: ";
          std::cin >> choice;
          std::cin.ignore();
          while (choice < 1 || choice > temp_semesters->size()) {
            std::cout << "Please input valid choice: ";
            std::cin >> choice;
            std::cin.ignore();
          }
          std::cout << std::endl;

          temp_semesters->remove(temp_semesters->find_kth_smallest_node(choice)->data.get_period());
          break;
        }
        // course
        case 3: {
          if (current->get_semesters() == nullptr || current->get_semesters()->size() == 0) {
            std::cout << "There is no any semester and course in the CSV file." << std::endl;
            std::cout << "Please add a new semester and course before removing course."
                      << std::endl;
            return;
          }

          std::cout << "Please choose the semester that the course belongs to." << std::endl;
          for (int i = 1; i <= current->get_semesters()->size(); i++)
            std::cout << i << ".\t"
                      << current->get_semesters()->find_kth_smallest_node(i)->data.get_period()
                      << std::endl;
          std::cout << "Please input your choice in number: ";
          std::cin >> choice;
          std::cin.ignore();
          while (choice < 1 || choice > current->get_semesters()->size()) {
            std::cout << "Please input a valid choice: ";
            std::cin >> choice;
            std::cin.ignore();
          }

          Semester* temp_semester =
            &(current->get_semesters()->find_kth_smallest_node(choice)->data);
          if (temp_semester->get_courses().size() == 0) {
            std::cout << "There is no any course in this semester." << std::endl;
            std::cout << "Please add a new course into this semester before removing course."
                      << std::endl;
            return;
          }

          std::cout << "Please choose the course that you want to remove." << std::endl;
          for (int i = 1; i <= temp_semester->get_courses().size(); i++)
            std::cout << i << ".\t"
                      << temp_semester->get_courses().find_kth_smallest_node(i)->data.get_code()
                      << std::endl;
          std::cout << "Please input your choice in number: ";
          std::cin >> choice;
          std::cin.ignore();
          while (choice < 1 || choice > temp_semester->get_courses().size()) {
            std::cout << "Please input a valid choice: ";
            std::cin >> choice;
            std::cin.ignore();
          }

          temp_semester->remove_course(
            temp_semester->get_courses().find_kth_smallest_node(choice)->data);
          break;
        }
      }
      break;
    }
    // edit
    case 3: {
      std::cout << "Which data that you want to edit?" << std::endl;
      std::cout << "1.\tStudent" << std::endl;
      std::cout << "2.\tAdvisor" << std::endl;
      std::cout << "3.\tSemester" << std::endl;
      std::cout << "4.\tCourse" << std::endl;
      std::cout << "Please input the index number of the choice: ";
      std::cin >> choice;
      std::cin.ignore();
      while (choice < 1 || choice > 4) {
        std::cout << "Please input valid choice: ";
        std::cin >> choice;
        std::cin.ignore();
      }
      std::cout << std::endl;

      switch (choice) {
        // student
        case 1: {
          Student* temp_student = current->get_user();
          if (temp_student == nullptr) {
            std::cout << "There is no any data of student." << std::endl;
            std::cout << "Please add a new data of student first." << std::endl;
            return;
          }

          std::cout << "Which data in Student that you want to edit?" << std::endl;
          std::cout << "1.\tName" << std::endl;
          std::cout << "2.\tAdmit Date" << std::endl;
          std::cout << "3.\tDepartment" << std::endl;
          std::cout << "4.\tUST ID Card Number" << std::endl;
          std::cout << "5.\tYear of Study" << std::endl;
          std::cout << "6.\tStatus of Study" << std::endl;
          std::cin >> choice;
          std::cin.ignore();
          while (choice < 1 || choice > 6) {
            std::cout << "Please input valid choice: ";
            std::cin >> choice;
            std::cin.ignore();
          }
          std::cout << std::endl;

          switch (choice) {
            // name
            case 1: {
              std::cout << "The original value of Name is " << temp_student->get_name()
                        << std::endl;
              std::cout << "Please input new value of Name: ";
              std::string new_name;
              getline(std::cin, new_name);
              temp_student->change_name(new_name);
              break;
            }
            // admit data
            case 2: {
              std::cout << "The original value of Admit Date is " << temp_student->get_admit_date()
                        << std::endl;
              std::cout << "Please input new value of Admit Date: ";
              std::string new_admit_date;
              getline(std::cin, new_admit_date);
              temp_student->change_admit_date(new_admit_date);
              break;
            }
            // department
            case 3: {
              std::cout << "The original value of Department is " << temp_student->get_department()
                        << std::endl;
              std::cout << "Please input new value of Department: ";
              std::string new_department;
              getline(std::cin, new_department);
              temp_student->change_department(new_department);
              break;
            }
            // use id card number
            case 4: {
              std::cout << "The original value of UST ID Card Number is "
                        << temp_student->get_ust_card_num() << std::endl;
              std::cout << "Please input new value of UST ID Card Number: ";
              int new_ust_id_num;
              std::cin >> new_ust_id_num;
              std::cin.ignore();
              temp_student->change_ust_card_num(new_ust_id_num);
              break;
            }
            // year of study
            case 5: {
              std::cout << "The original value of Year of Study is " << temp_student->get_year()
                        << std::endl;
              std::cout << "Please input new value of Year of Study: ";
              int new_year;
              std::cin >> new_year;
              std::cin.ignore();
              temp_student->change_year(new_year);
              break;
            }
            // status of study
            case 6: {
              std::cout << "The original value of Status of Study is " << temp_student->get_status()
                        << std::endl;
              std::cout << "Please choose the new valule of Status of Study:" << std::endl;
              std::cout << "1.\tActive in Program" << std::endl;
              std::cout << "2.\tWithdraw Program" << std::endl;
              std::cout << "3.\tSuspend Program" << std::endl;
              std::cout << "Please input your choose in number: ";
              int new_status;
              std::cin >> new_status;
              std::cin.ignore();
              while (new_status < 1 || new_status > 3) {
                std::cout << "Please input a valid choice: ";
                std::cin >> new_status;
                std::cin.ignore();
              }
              temp_student->change_status(static_cast<Status_Program>(new_status));
              break;
            }
          }
          break;
        }
        // advisor
        case 2: {
          Professor* temp_advisor = current->get_advisor();
          if (temp_advisor == nullptr) {
            std::cout << "There is no any data of advisor." << std::endl;
            std::cout << "Please add a data of advisor first." << std::endl;
            return;
          }
          std::cout << "Which data in Advisor that you want to edit?" << std::endl;
          std::cout << "1.\tName" << std::endl;
          std::cout << "2.\tDepartment" << std::endl;
          std::cout << "Please input your choose in number: ";
          std::cin >> choice;
          std::cin.ignore();
          while (choice < 1 || choice > 2) {
            std::cout << "Please input valid choice: ";
            std::cin >> choice;
            std::cin.ignore();
          }
          std::cout << std::endl;

          switch (choice) {
            // name
            case 1: {
              std::cout << "The original value of Name is " << temp_advisor->get_name()
                        << std::endl;
              std::cout << "Please input new value of Name: ";
              std::string new_name;
              getline(std::cin, new_name);
              temp_advisor->change_name(new_name);
              break;
            }
            // department
            case 2: {
              std::cout << "The original value of Department is " << temp_advisor->get_department()
                        << std::endl;
              std::cout << "Please input new value of Department: ";
              std::string new_department;
              getline(std::cin, new_department);
              temp_advisor->change_department(new_department);
              break;
            }
          }
          break;
        }
        // semester
        case 3: {
          BST<Semester>* temp_semesters = current->get_semesters();
          if (temp_semesters == nullptr || temp_semesters->size() == 0) {
            std::cout << "There is no any semester." << std::endl;
            std::cout << "Please add a new semester first." << std::endl;
            return;
          }

          std::cout << "There " << (temp_semesters->size() == 1 ? "is " : "are ")
                    << temp_semesters->size() << " "
                    << (temp_semesters->size() == 1 ? "semester" : "semesters") << "." << std::endl;
          for (int i = 1; i <= temp_semesters->size(); i++)
            std::cout << i << ".\t" << temp_semesters->find_kth_smallest_node(i)->data.get_period()
                      << std::endl;
          std::cout << "Which semester that you want to edit?" << std::endl;
          std::cout << "Please input your choice in number: ";
          std::cin >> choice;
          std::cin.ignore();
          while (choice < 1 || choice > temp_semesters->size()) {
            std::cout << "Please input a valid choice: ";
            std::cin >> choice;
            std::cin.ignore();
          }

          Semester* temp_semester = &(temp_semesters->find_kth_smallest_node(choice)->data);
          std::cout << "You can only edit Period in Semester." << std::endl;
          std::cout << "The origin value fo Period is" << temp_semester->get_period() << std::endl;
          std::cout << "Please input new value of Period: ";
          std::string new_period;
          getline(std::cin, new_period);

          Semester new_semester{new_period};
          for (int i = 1; i <= temp_semester->get_courses().size(); i++)
            new_semester.insert_course(
              temp_semester->get_courses().find_kth_smallest_node(i)->data);
          temp_semesters->remove(*temp_semester);
          temp_semesters->insert(new_semester);
          break;
        }
        // course
        case 4: {
          if (current->get_semesters() == nullptr || current->get_semesters()->size() == 0) {
            std::cout << "There is no any semester and course." << std::endl;
            std::cout << "Please add a new semester and course first." << std::endl;
            return;
          }

          std::cout << "Please choose the semester that the course belongs to." << std::endl;
          for (int i = 1; i <= current->get_semesters()->size(); i++)
            std::cout << i << ".\t"
                      << current->get_semesters()->find_kth_smallest_node(i)->data.get_period()
                      << std::endl;
          std::cout << "Please input your choice in number: ";
          std::cin >> choice;
          std::cin.ignore();
          while (choice < 1 || choice > current->get_semesters()->size()) {
            std::cout << "Please input a valid choice: ";
            std::cin >> choice;
            std::cin.ignore();
          }

          Semester* temp_semester =
            &(current->get_semesters()->find_kth_smallest_node(choice)->data);
          if (temp_semester->get_courses().size() == 0) {
            std::cout << "There is no any course in this semester." << std::endl;
            std::cout << "Please add a new course into this semester first." << std::endl;
            return;
          }

          std::cout << "Please choose the course that you want to edit." << std::endl;
          for (int i = 1; i <= temp_semester->get_courses().size(); i++)
            std::cout << i << ".\t"
                      << temp_semester->get_courses().find_kth_smallest_node(i)->data.get_code()
                      << std::endl;
          std::cout << "Please input your choice in number: ";
          std::cin >> choice;
          std::cin.ignore();
          while (choice < 1 || choice > temp_semester->get_courses().size()) {
            std::cout << "Please input a valid choice: ";
            std::cin >> choice;
            std::cin.ignore();
          }

          Course* temp_course =
            &(temp_semester->get_courses().find_kth_smallest_node(choice)->data);
          std::cout << "Which data that you want to edit?" << std::endl;
          std::cout << "1.\tCourse Code" << std::endl;
          std::cout << "2.\tCourse Title" << std::endl;
          std::cout << "3.\tGrade" << std::endl;
          std::cout << "4.\tNumber of Credits" << std::endl;
          std::cout << "Please input your choice in number: ";
          std::cin >> choice;
          std::cin.ignore();
          while (choice < 1 || choice > 4) {
            std::cout << "Please input a valid choice: ";
            std::cin >> choice;
            std::cin.ignore();
          }

          switch (choice) {
            // course code
            case 1: {
              std::cout << "The original value of Course Code is " << temp_course->get_code()
                        << std::endl;
              std::cout << "Please input new value of Course Code: ";
              std::string new_code;
              getline(std::cin, new_code);
              temp_course->change_code(new_code);
              break;
            }
            // course title
            case 2: {
              std::cout << "The original value of Course Title is " << temp_course->get_title()
                        << std::endl;
              std::cout << "Please input new value of Course Title: ";
              std::string new_title;
              getline(std::cin, new_title);
              temp_course->change_title(new_title);
              break;
            }
            // grade
            case 3: {
              std::cout << "The original value of Grade is " << temp_course->get_grade_str()
                        << std::endl;
              std::cout << "Please input new value of Grade: ";
              std::string new_grade;
              getline(std::cin, new_grade);
              temp_course->change_grade(new_grade);
              break;
            }
            // number of credits
            case 4: {
              std::cout << "The original value of Number of Credits is "
                        << temp_course->get_credits() << std::endl;
              std::cout << "Please input new value of Number of Credits: ";
              int new_credits;
              std::cin >> new_credits;
              std::cin.ignore();
              while (new_credits < 0) {
                std::cout << "Number of Credits should not be negative number." << std::endl;
                std::cout << "Please input again: ";
                std::cin >> new_credits;
                std::cin.ignore();
              }
              temp_course->change_credits(new_credits);
              break;
            }
          }
          break;
        }
      }
      break;
    }
  }
  // create csv file with same name

  std::cout << std::endl;
  generate_csv(current, file_path);
  std::cout << std::endl;
  std::cout << "Modified~" << std::endl;
}

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

  std::cout << "Made~" << std::endl;
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
  std::cout << std::endl;
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
  if (index >= transcripts.size() || index < 0) {
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

void Generator::print_test(const Transcript* const current) const {
  std::cout << "Generator class object:" << std::endl;
  if (current != nullptr) {
    current->print_test();
    std::cout << std::endl;
  } else
    std::cout << "Transcript* current: nullptr" << std::endl;
  std::cout << "There " << (transcripts.size() == 1 ? "is " : "are ") << transcripts.size() << " "
            << (transcripts.size() == 1 ? "transcript" : "transcripts") << "." << std::endl;
  for (int i = 0; i < transcripts.size(); i++) {
    transcripts[i]->print_test();
    if (i != transcripts.size() - 1)
      std::cout << std::endl;
  }
}