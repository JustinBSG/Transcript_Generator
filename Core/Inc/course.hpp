#ifndef INC_COURSE_HPP
#define INC_COURSE_HPP

#include <string>

using namespace std;

enum grade { F, D, C, B, A };

class Course {
    friend ostream& operator<<(ostream& os, const Course& data);

  private:
    string code;
    string title;
    string grade;
    int credits;

  public:
    Course(string code = "", string title = "", string grade = "F", int credits = 0);
    Course(const Course& other);
    ~Course() = default;

    string get_code() const;
    string get_title() const;
    string get_grade_str() const;
    int get_credits() const;
    float get_grade_num() const;

    void change_code(const string& other_code);
    void change_title(const string& other_title);
    void change_grade(const string& other_grade);
    void change_credits(const int& other_credits);

    Course& operator=(const Course& other);
    bool operator<(const Course& other);
    bool operator>(const Course& other);
    bool operator==(const Course& other);
};

#endif