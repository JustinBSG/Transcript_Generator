#ifndef SEMESTER_HPP
#define SEMESTER_HPP

#include <string>

#include "bst.hpp"
#include "course.hpp"

class Semester {
  private:
    std::string period;
    double tga;
    double cga;
    int total_num_credits;
    int total_num_courses;
    BST<Course> courses;

  public:
    Semester(std::string period = "", double tga = 0., double cga = 0., int total_num_credits = 0,
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
     * @brief Get the cga object
     *
     * @return double
     */
    double get_cga() const;

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
     * @brief Calculate CGA and update cga object
     * 
     */
    void calculate_cga();

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
     * @brief Change courses to other_courses
     *
     * @param other_courses
     */
    void change_courses(const BST<Course>& other_courses);

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

    bool operator<(const Semester& other);
    bool operator>(const Semester& other);
    bool operator<=(const Semester& other);
    bool operator>=(const Semester& other);
    bool operator==(const Semester& other);

    /**
     * @brief Print content of all member variables in testing purpose
     *
     */
    void print_test() const;
};

#endif  // SEMESTER_HPP