#include <iostream>

using namespace std;

namespace avl {
  void option() {
    int option;
    cout << "For testing AVL Tree, please input a testcase (1-10): ";
    cin >> option;
    switch (option) {
      case 1:
        testcase1();
        break;
      case 2:
        testcase2();
        break;
      case 3:
        testcase3();
        break;
      case 4:
        testcase4();
        break;
      case 5:
        testcase5();
        break;
      case 6:
        testcase6();
        break;
      case 7:
        testcase7();
        break;
      case 8:
        testcase8();
        break;
      case 9:
        testcase9();
        break;
      case 10:
        testcase10();
        break;
      default:
        break;
    }
  }

  // test constructor and destructor
  void testcase1() {}

  // test insert(), remove()
  void testcase2() {}

  // test print()
  void testcase3() {}

  // test is_empty(), contain(), find_min(), find_max()
  void testcase4() {}

  // test find_node(), find_kth_largest_node()
  void testcase5() {}
  void testcase6() {}
  void testcase7() {}
  void testcase8() {}
  void testcase9() {}
  void testcase10() {}
};  // namespace avl

void option() {
  int option;
  cout << "What do you want to test?" << endl;
  cout << "1. AVL Tree" << endl;
  cout << "Please input your choice: ";
  cin >> option;
  switch (option) {
    case 1:
      avl::option();
      break;
    default:
      break;
  }
  cout << "This is the end of the testing part. BYE~" << endl;
}