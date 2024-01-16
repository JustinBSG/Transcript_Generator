#include <iostream>
#include <string>

#include "../Inc/generator.hpp"

int main() {
  // Course test_course{"course_code", "course_title", "course_grade", 3};
  // Major test_major{"major_name", "major_change_date", "major_name_major"};
  // Minor test_minor{"minor_name", "minor_change_date", "minor_name_minor"};
  Student test_student{
    "student_name",  "student_admit_date", "student_department", 777, 3, 3.1, 3.3,
    "student_status"};
  BST<Major> majors;
  BST<Minor> minors;
  Major major1{"major_program1", "2020-21 Spring", "CS"};
  Major major3{"major_program3", "2022-23 Spring", "MATH"};
  Major major2{"major_program2", "2021-22 Fall", "EE"};
  Minor minor1{"NA", "2021-22 Spring", "Minor1"};
  Minor minor2{"NA", "2022-23 Fall", "Minor2"};
  test_student.insert_major(major1);
  test_student.insert_major(major2); 
  test_student.insert_major(major3);
  test_student.insert_minor(minor1);
  test_student.insert_minor(minor2);
  cout << test_student.get_majors().size() << endl;
  cout << test_student.get_minors().size() << endl;
  int count_majors = 0;
  while (count_majors < test_student.get_majors().size()) {
    Major temp =
      test_student.get_majors()
        .find_kth_largest_node(count_majors+1)
        ->data;
    cout << temp.get_name() << endl;
    count_majors++;
  }
  return 0;
}