#include <iostream>
#include <string>

#include "../Inc/generator.hpp"

int main() {
  // the problem is datatype Major
  // insert problem, can only asending order
  BST<Major> majors;
  Major major1{"major1", "2020-21 Fall", "major_name_1"};
  Major major2{"major2", "2021-22 Fall", "major_name_2"};
  Major major3{"major3", "2022-23 Fall", "major_name_3"};

  majors.insert(major3);
  majors.insert(major1);
  majors.insert(major2);

  int count_major = 0;
  cout << majors.size() << endl;
  while (count_major < majors.size()) {
    cout << majors.find_kth_largest_node(majors.size() - count_major)->data << endl;
    count_major++;
  }

  // BST<string> tests;
  // string test1{"2020-21 Spring"};
  // string test2{"2021-22 Spring"};
  // string test3{"2022-23 Spring"};

  // tests.insert(test3);
  // tests.insert(test2);
  // tests.insert(test1);

  // int count_test = 0;
  // cout << tests.size() << endl;
  // while (count_test < tests.size()) {
  //   cout << tests.find_kth_largest_node(tests.size() - count_test)->data << endl;
  //   count_test++;
  // }
  return 0;
}