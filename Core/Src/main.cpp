#include <iostream>
#include <string>

#include "../Inc/generator.hpp"

int main() {
  Transcript test;
  Student test_student{"student_name", "1 September 2021", "CSE", 20856261, 3, 3.1, 3.2, "Active in Program"};
  Major major1{"program_major1", "2020-21 Spring", "name_major1"};
  Major major2{"program_major2", "2021-22 Spring", "name_major2"};
  Major major3{"program_major3", "2022-23 Spring", "name_major3"};
  test_student.insert_major(major2);
  test_student.insert_major(major1);
  test_student.insert_major(major3);
  Minor minor1{"NA", "2021-22 Spring", "IT"};
  Minor minor2{"NA", "2022-23 Spring", "Robotics"};
  test_student.insert_minor(minor1);
  test_student.insert_minor(minor2);
  BST<Semester> *semesters = new BST<Semester>;
  string student_admit_date = test_student.get_admit_date();
  int index_year = 0, count_space = 0, index = 0;
  while (count_space != 2) {
    if (student_admit_date[index] == ' ')
      count_space++;
    index++;
  }
  index_year = index;
  for (int i = 0; i < 16; i++) {
    Semester temp;
    string temp_year;
    for (int k = 0; k < 4; k++)
      if (k == 3)
        temp_year.push_back(student_admit_date[index_year + k] + i / 4);
      else
        temp_year.push_back(student_admit_date[index_year + k]);
    temp_year.push_back('-');
    temp_year.push_back(student_admit_date[index_year + 2]);
    if (student_admit_date[index_year + 3] == '9')
      temp_year.push_back('0');
    else
      temp_year.push_back(student_admit_date[index_year + 3] + i / 4 + 1);
    temp_year.push_back(' ');
    switch (i % 4) {
      case 0:
        temp_year.append("Fall");
        break;
      case 1:
        temp_year.append("Winter");
        break;
      case 2:
        temp_year.append("Spring");
        break;
      case 3:
        temp_year.append("Summer");
    }
    temp.change_period(temp_year);
    semesters->insert(temp);
  }
  Course course1{"COMP2011", "test1", "B+", 4};
  Course course2{"COMP2012", "test2", "A", 4};
  Course course3{"COMP2013", "test3", "A", 4};
  Course course4{"COMP2014", "test4", "B+", 3};
  Course course5{"COMP2015", "test5", "B-", 3};
  semesters->find_kth_largest_node(semesters->size())->data.insert_course(course1);
  semesters->find_kth_largest_node(semesters->size())->data.insert_course(course2);
  semesters->find_kth_largest_node(semesters->size())->data.insert_course(course3);
  semesters->find_kth_largest_node(semesters->size())->data.calculate_tga();
  semesters->find_kth_largest_node(1)->data.insert_course(course4);
  semesters->find_kth_largest_node(1)->data.insert_course(course5);
  semesters->find_kth_largest_node(1)->data.calculate_tga();
  // Professor test_professor{"professor_name", "NA", "CSE", 0};
  
  // test.insert_student(&test_student);
  // test.insert_professor(&test_professor);
  cout << semesters->find_kth_largest_node(semesters->size())->data.get_total_num_courses() << endl;
  cout << semesters->find_kth_largest_node(1)->data.get_total_num_courses() << endl;
  test_student.insert_semesters(semesters);
  test_student.calculate_CGA(semesters);
  cout << test_student << endl;
  
  return 0;
}