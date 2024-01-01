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

    /**
     * @brief Get the code object
     * 
     * @return string 
     */
    string get_code() const;

    /**
     * @brief Get the title object
     * 
     * @return string 
     */
    string get_title() const;

    /**
     * @brief Get the grade object in string
     * 
     * @return string 
     */
    string get_grade_str() const;

    /**
     * @brief Get the credits object
     * 
     * @return int 
     */
    int get_credits() const;

    /**
     * @brief Get the grade object in float
     * 
     * @return float 
     */
    float get_grade_num() const;

    /**
     * @brief Change content of code to other_code
     * 
     * @param other_code 
     */
    void change_code(const string& other_code);

    /**
     * @brief Change content of title to other_title
     * 
     * @param other_title 
     */
    void change_title(const string& other_title);

    /**
     * @brief Change content of grade to other_grade
     * 
     * @param other_grade 
     */
    void change_grade(const string& other_grade);

    /**
     * @brief Change content of credits to other_credits
     * 
     * @param other_credits 
     */
    void change_credits(const int& other_credits);

    Course& operator=(const Course& other);
    bool operator<(const Course& other);
    bool operator>(const Course& other);
    bool operator==(const Course& other);
};

#endif