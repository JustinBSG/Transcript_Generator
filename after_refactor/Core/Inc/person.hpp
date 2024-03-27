#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>

#include "../Inc/bst.hpp"
#include "../Inc/course.hpp"
#include "../Inc/program.hpp"
#include "../Inc/semester.hpp"

enum Status_Program { Active_In_Program = 1, Withdraw_Program, Suspend_Program };

class Person {
  protected:
    std::string name;
    std::string admit_date;
    std::string department;
    int ust_card_num;

  public:
    Person(std::string name = "", std::string admit_date = "", std::string department = "",
           int ust_card_num = 0);

    /**
     * @brief Get the name object
     *
     * @return std::string
     */
    std::string get_name() const;

    /**
     * @brief Get the admit date object
     *
     * @return std::string
     */
    std::string get_admit_date() const;

    /**
     * @brief Get the department object
     *
     * @return std::string
     */
    std::string get_department() const;

    /**
     * @brief Get the ust card num object
     *
     * @return int
     */
    int get_ust_card_num() const;
    void change_name(const std::string& other_name);
    void change_admit_date(const std::string& other_admit_date);
    void change_department(const std::string& other_department);
    void change_ust_card_num(const int& other_ust_card_num);
};

class Professor : public Person {
  public:
    Professor(std::string name = "", std::string admit_date = "", std::string department = "",
              int ust_card_num = 0);
};

class Student : public Person {
  private:
    int year;
    double cga;
    double mcga;
    Status_Program status;
    BST<Major> majors;
    BST<Minor> minors;
    BST<Semester>* semesters;

  public:
    /**
     * @brief Construct a new Student object
     *
     * @param name
     * @param admit_date
     * @param department
     * @param ust_card_num
     * @param year
     * @param cga
     * @param mcga
     * @param status
     * @param semesters
     */
    Student(std::string name = "", std::string admit_date = "", std::string department = "",
            int ust_card_num = 0, int year = 0, double cga = 0., double mcga = 0.,
            Status_Program status = Active_In_Program, BST<Semester>* semesters = nullptr);

    /**
     * @brief Destroy the Student object \
     * @brief Destroy the BST<Semester>* semester while destroying Transcript object
     *
     */
    ~Student() = default;

    int get_year() const;
    double get_cga() const;
    double get_mcga() const;
    std::string get_status() const;
    BST<Major>& get_majors();
    BST<Minor>& get_minors();
    BST<Semester>* get_semesters();
    void change_year(const int& other_year);
    void calculate_cga();
    void calculate_mcga();
    void change_status(const Status_Program& other_status);
    void insert_major(const Major& other_major);
    void remove_major(const std::string& other_major_name);
    void insert_minor(const Minor& other_minor);
    void remove_minor(const std::string& other_minor_name);
    void insert_semester(BST<Semester>* other_semesters);

    bool check_semesters_nullptr() const;
};

#endif  // PERSON_HPP