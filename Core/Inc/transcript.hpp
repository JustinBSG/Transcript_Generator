#ifndef INC_TRANSCRIPT_HPP
#define INC_TRANSCRIPT_HPP

#include <string>

#include "../Inc/bst.hpp"
#include "person.hpp"
#include "program.hpp"
#include "semester.hpp"

class Transcript {
  private:
    Student *user;
    Professor *advisor;
    BST<Semester> *semesters;
    string print_date;

  public:
    Transcript(Student *user = nullptr, Professor *advisor = nullptr,
               BST<Semester> *semesters = nullptr);
    ~Transcript();

    /**
     * @brief Get the user object
     *
     * @return Student*
     */
    Student *get_student() const;

    /**
     * @brief Get the advisor object
     *
     * @return Professor*
     */
    Professor *get_professor() const;

    /**
     * @brief Get the semesters object
     *
     * @return BST<Semester>*
     */
    BST<Semester> *get_semesters() const;

    /**
     * @brief Get the print_date object
     *
     * @return string
     */
    string get_print_date() const;

    /**
     * @brief Insert other_student
     *
     * @param other_student
     */
    void insert_student(Student *other_student);

    /**
     * @brief Insert other_professor
     *
     * @param other_professor
     */
    void insert_professor(Professor *other_professor);

    /**
     * @brief Insert other_semester into semesters
     *
     * @param other_semester
     */
    void insert_semesters(BST<Semester> *other_semester);

    /**
     * @brief Update print_date
     *
     */
    void update_print_date();

    /**
     * @brief Update CGA inside student class object
     *
     */
    void calculate_CGA();

    /**
     * @brief Updata MCGA inside student class object
     *
     */
    void calculate_MCGA();

    void print() const;
};

#endif