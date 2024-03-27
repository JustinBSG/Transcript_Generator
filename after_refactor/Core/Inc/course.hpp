#ifndef COURSE_HPP
#define COURSE_HPP

#include <string>

class Course {
  private:
    std::string code;
    std::string title;
    std::string grade;
    int credits;

  public:
    Course(std::string code = "", std::string title = "", std::string grade = "F", int credits = 0);

    /**
     * @brief Get the code object
     * 
     * @return std::string 
     */
    std::string get_code() const;

    /**
     * @brief Get the title object
     * 
     * @return std::string 
     */
    std::string get_title() const;

    /**
     * @brief Get the grade object in string
     * 
     * @return std::string 
     */
    std::string get_grade_str() const;

    /**
     * @brief Get the credits object
     * 
     * @return int 
     */
    int get_credits() const;

    /**
     * @brief Get the grade object in double
     * 
     * @return double 
     */
    double get_grade_num() const;

    /**
     * @brief Change content of code object to that of other_code
     * 
     * @param other_code 
     */
    void change_code(const std::string& other_code);
    
    /**
     * @brief Change content of title object to that of other_title
     * 
     * @param other_title 
     */
    void change_title(const std::string& other_title);

    /**
     * @brief Change content of grade object to that of other_grade
     * 
     * @param other_grade 
     */
    void change_grade(const std::string& other_grade);

    /**
     * @brief Change content of credits object to that of other_credits
     * 
     * @param other_credits 
     */
    void change_credits(const int& other_credits);
    
    bool operator<(const Course& other);
    bool operator>(const Course& other);
    bool operator<=(const Course& other);
    bool operator>=(const Course& other);
    bool operator==(const Course& other);

    /**
     * @brief Print content of all member variables in testing purpose
     * 
     */
    void print_test() const;
};

#endif  // COURSE_HPP