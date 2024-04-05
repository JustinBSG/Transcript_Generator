#ifndef SEMESTER_HPP
#define SEMESTER_HPP

#include <sstream>
#include <string>
#include <vector>

#include "bst.hpp"
#include "course.hpp"

class Semester {
  private:
    std::string period;
    double tga;
    int total_num_credits;
    int total_num_courses;
    BST<Course> courses;

  public:
    /**
     * @brief Construct a new Semester object, default constructor
     * 
     * @param period 
     * @param tga 
     * @param total_num_credits 
     * @param total_num_courses 
     */
    Semester(std::string period = "", double tga = 0., int total_num_credits = 0,
             int total_num_courses = 0);

    /**
     * @brief Get the period object
     *
     * @return std::string
     */
    std::string get_period() const;

    /**
     * @brief Get the tga object
     *
     * @return double
     */
    double get_tga() const;

    /**
     * @brief Get the total number of credits object
     *
     * @return int
     */
    int get_total_num_credits() const;

    /**
     * @brief Get the total number of courses object
     *
     * @return int
     */
    int get_total_num_courses() const;

    /**
     * @brief Get the courses object
     *
     * @return BST<Course>&
     */
    BST<Course>& get_courses();

    /**
     * @brief Change content of period object to that of other_period
     *
     * @param other_period
     */
    void change_period(const std::string& other_period);

    /**
     * @brief Calculate TGA of this semester and update tga object
     *
     */
    void calculate_tga();

    /**
     * @brief Update total number of credits
     *
     */
    void update_total_num_credits();

    /**
     * @brief Update total number of courses
     *
     */
    void update_total_num_courses();

    /**
     * @brief Copy other_courses to courses
     *
     * @param other_courses
     */
    void copy_courses(const BST<Course>& other_courses);

    /**
     * @brief Insert other_course into courses
     *
     * @param other_course
     */
    void insert_course(const Course& other_course);

    /**
     * @brief Remove specific other_course from courses
     *
     * @param other_course
     */
    void remove_course(const Course& other_course);

    /**
     * @brief Comparing by using std::string period
     * 
     * @param other 
     * @return true 
     * @return false 
     */
    bool operator<(const Semester& other);

    /**
     * @brief Comparing by using std::string period
     * 
     * @param other 
     * @return true 
     * @return false 
     */
    bool operator>(const Semester& other);
    
    /**
     * @brief Comparing by using std::string period
     * 
     * @param other 
     * @return true 
     * @return false 
     */
    bool operator<=(const Semester& other);
    
    /**
     * @brief Comparing by using std::string period
     * 
     * @param other 
     * @return true 
     * @return false 
     */
    bool operator>=(const Semester& other);
    
    /**
     * @brief Comparing by using std::string period
     * 
     * @param other 
     * @return true 
     * @return false 
     */
    bool operator==(const Semester& other);

    /**
     * @brief Print content of all member variables in testing purpose
     *
     */
    void print_test() const;

    std::vector<std::string> separate_string_period() const;
    int compare_semester_period(const std::string& semester_period) const;
};

#endif  // SEMESTER_HPP