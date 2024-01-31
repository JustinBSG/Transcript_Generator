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
    while (option > 9 || option < 1) {
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
      case 8:
        cout << *(current->get_student()) << endl;
        break;
    }
  }
}

// TODO: many bugs
void Generator::insert_data(Transcript*& current) {
  if (current == nullptr) {
    Student* temp_student = new Student;
    Professor* temp_advisor = new Professor;
    current = new Transcript;

    // Input data of student class object
    cout << "First, please input the information about you." << endl;
    cout << "Please input your name: ";
    cin.ignore();
    string student_name;
    getline(cin, student_name);
    cout << "Please input your admit date(e.g. 1 September 2020): ";
    string student_admit_date;
    getline(cin, student_admit_date);
    cout << "Please input your student id: ";
    int student_id;
    cin >> student_id;
    cout << "Please input your years of study: ";
    int student_year;
    cin >> student_year;
    cout << "Please choose your status of study:" << endl;
    cout << "1. Active in Program" << endl;
    cout << "2. Withdraw Program" << endl;
    cout << "3. Suspend Program" << endl;
    cout << "Please input your choose in number: ";
    int student_status_int;
    string student_status_string;
    cin >> student_status_int;
    while (student_status_int > 3 || student_status_int < 1) {
      cout << "Please input a valid number: ";
      cin >> student_status_int;
    }
    switch (student_status_int) {
      case 1:
        student_status_string = "Active in Program";
        break;
      case 2:
        student_status_string = "Withdraw Program";
        break;
      case 3:
        student_status_string = "Suspend Program";
        break;
    }
    temp_student->change_name(student_name);
    temp_student->change_admit_date(student_admit_date);
    temp_student->change_ust_card_num(student_id);
    temp_student->change_year(student_year);
    temp_student->change_status(student_status_string);

    // // Input data of advisor
    cout << "Then please input the information about your advisor." << endl;
    cout << "Please input name of your advisor(e.g. CHAN, Da Man): ";
    string advisor_name;
    getline(cin, advisor_name);
    temp_advisor->change_name(advisor_name);

    // Input data of Major or Minor
    cout << "Next, please input the information about your academics program."
         << endl;
    cout << "Please input name of first program(e.g. Bachelor Degree in School of "
            "Engineering): ";
    string first_program_name;
    getline(cin, first_program_name);
    cout << "Please input its name of major(e.g. Computer Science)(if you haven't "
            "had major yet, please input NA): ";
    string first_major_name;
    getline(cin, first_major_name);
    Major first_major{first_program_name, "NA", first_major_name};
    BST<Major>* temp_semesters = new BST<Major>;
    temp_semesters->insert(first_major);
    while (1) {
      cout << "Do you still have another Major Program?(yes/no): ";
      string input_continue;
      getline(cin, input_continue);
      if (input_continue == "yes") {
        cout
          << "Please input name of program(e.g. Bachelor Degree of Engineering): ";
        string temp_major_name;
        getline(cin, temp_major_name);
        cout << "Please input name of major(e.g. Computer Science): ";
        string temp_name_major_name;
        getline(cin, temp_name_major_name);
        cout << "Please input the semester that you change program(e.g. 2022-23 "
                "Fall): ";
        string temp_change_date;
        getline(cin, temp_change_date);
        Major temp_major{temp_major_name, temp_change_date, temp_name_major_name};
        temp_student->get_majors().insert(temp_major);
      } else
        break;
    }
    while (1) {
      cout << "Do you declare any Minor Program?(yes/no): ";
      string input_continue;
      getline(cin, input_continue);
      if (input_continue == "yes") {
        cout << "Please input name of Minor Program(e.g. Smart City): ";
        string temp_minor_name;
        getline(cin, temp_minor_name);
        cout << "Please input the semester that you declare this minor program(e.g. "
                "2022-23 Fall): ";
        string temp_minor_date;
        getline(cin, temp_minor_date);
        Minor temp_minor{"NA", temp_minor_date, temp_minor_name};
        temp_student->get_minors().insert(temp_minor);
      } else
        break;
    }

    // // Input data of semesters
    // // Insert period of all semesters automatically
    // BST<Semester>* semesters = new BST<Semester>;
    // int index_year = 0, count_space = 0, index = 0;
    // while (count_space != 2) {
    //   if (student_admit_date[index] == ' ')
    //     count_space++;
    //   index++;
    // }
    // index_year = index;
    // for (int i = 0; i < 16; i++) {
    //   Semester temp;
    //   string temp_year;
    //   for (int k = 0; k < 4; k++)
    //     if (k == 3)
    //       temp_year.push_back(student_admit_date[index_year + k] + i / 4);
    //     else
    //       temp_year.push_back(student_admit_date[index_year + k]);
    //   temp_year.push_back('-');
    //   temp_year.push_back(student_admit_date[index_year + 2]);
    //   if (student_admit_date[index_year + 3] == '9')
    //     temp_year.push_back('0');
    //   else
    //     temp_year.push_back(student_admit_date[index_year + 3] + i / 4 + 1);
    //   temp_year.push_back(' ');
    //   switch (i % 4) {
    //     case 0:
    //       temp_year.append("Fall");
    //       break;
    //     case 1:
    //       temp_year.append("Winter");
    //       break;
    //     case 2:
    //       temp_year.append("Spring");
    //       break;
    //     case 3:
    //       temp_year.append("Summer");
    //   }
    //   temp.change_period(temp_year);
    //   semesters->insert(temp);
    // }

    // // Input courses of each semester
    // if (semesters->size() != 0) {
    //   int count_semester = 0;
    //   while (count_semester < semesters->size()) {
    //     cout << "Please input the course code of one course that you have taken in
    //     "; cout
    //       << semesters->find_kth_largest_node(semesters->size() -
    //       count_semester)->data
    //       << "(you can type NA if there is no remaining course left): ";
    //     string temp_course_code;
    //     cin >> temp_course_code;
    //     if (temp_course_code == "NA") {
    //       count_semester++;
    //       continue;
    //     }
    //     cout << "Please input the course title of this course: ";
    //     string temp_course_title;
    //     cin >> temp_course_title;
    //     cout << "Please input the number of credit of this course: ";
    //     int temp_course_num_credit;
    //     cin >> temp_course_num_credit;
    //     cout << "Please input the grade that you got in this course: ";
    //     string temp_course_grade;
    //     cin >> temp_course_grade;
    //     // data validation

    //     Course temp_course{temp_course_code, temp_course_title, temp_course_grade,
    //                       temp_course_num_credit};
    //     semesters->find_kth_largest_node(semesters->size() - count_semester)
    //       ->data.insert_course(temp_course);
    //     cout << endl;
    //   }

    //   // Calculate CGA of user
    //   current->calculate_CGA();
    //   // Calculate MCGA of user
    //   // current->calculate_MCGA();
    // }

    // current->insert_semesters(semesters);
    // temp_student->insert_semesters(semesters);
    current->insert_student(temp_student);
    current->insert_professor(temp_advisor);
    transcripts.push_back(current);
  } else {
    cout << "Please choose option 5 to generate another transcript." << endl;
    return;
  }
}

void Generator::read_csv(Transcript* current) {}

void Generator::generate_csv(Transcript* current) {}

void Generator::modify_csv(Transcript* current) {}

void Generator::print_all(Transcript* current) { current->print(); }

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