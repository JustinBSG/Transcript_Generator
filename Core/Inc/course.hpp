#ifndef INC_COURSE_HPP
#define INC_COURSE_HPP

#include <string>

using namespace std;

enum grade { F, D, C, B, A };

class Course {
  private:
    string code;
    string title;
    string grade;
    // Course* next;
    // Course* prev;
    int credits;

  public:
    Course();
    ~Course();

    string GetCode() const;
    string GetTitle() const;
    string GetGrade() const;
    // Course* GetNext() const;
    // Course* GetPrev() const;
    int GetCredits() const;

    float find_decimal_place_grade() const;

    // Course* last_course() const;
    // void add_course(Course*);
    // void sort_course();
};

#endif