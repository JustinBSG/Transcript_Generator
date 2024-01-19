#ifndef INC_SEMESTER_HPP
#define INC_SEMESTER_HPP

#include <string>

#include "../Inc/bst.hpp"
#include "../Inc/course.hpp"

using namespace std;

enum Period_Semester { Fall, Winter, Spring, Summer };

class Semester {
    friend ostream& operator<<(ostream& os, const Semester& data);

  private:
    string period;
    float tga;
    int total_num_credits;
    int total_num_courses;
    BST<Course> courses;

  public:
    Semester(string period = "", float tga = .0, int total_num_credits = 0,
             int total_num_courses = 0);
    ~Semester() = default;

    /**
     * @brief Get the period object
     *
     * @return string
     */
    string get_period() const;

    /**
     * @brief Get the tga object
     *
     * @return float
     */
    float get_tga() const;

    /**
     * @brief Get the total_num_credits object
     *
     * @return int
     */
    int get_total_num_credits() const;

    /**
     * @brief Get the total_num_courses object
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
     * @brief Change period to other_period
     *
     * @param other_period
     */
    void change_period(const string& other_period);

    void calculate_tga();
    void calculate_total_num_credits();
    void update_total_num_courses();

    /**
     * @brief Insert other Course object to BST<Course>
     *
     * @param other
     */
    void insert_course(const Course& other);

    /**
     * @brief Remove course with same code
     *
     * @param code
     */
    void remove_course(const string& code);

    /**
     * @brief Convert period_semester from string to int/
     *
     * @param period_semester
     * @return int
     */
    int convert_period(const string& period_semester);

    Semester& operator=(const Semester& other);
    bool operator<(const Semester& other);
    bool operator>(const Semester& other);
    bool operator==(const Semester& other);
};

#endif