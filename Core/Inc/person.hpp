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
    /**
     * @brief Construct a new Person object, default constructor
     * 
     * @param name 
     * @param admit_date 
     * @param department 
     * @param ust_card_num 
     */
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

    /**
     * @brief Changing name to other_name
     * 
     * @param other_name 
     */
    void change_name(const std::string& other_name);
    
    /**
     * @brief Changing admit_date to other_admit_date
     * 
     * @param other_admit_date 
     */
    void change_admit_date(const std::string& other_admit_date);
    
    /**
     * @brief Changing department to other_department
     * 
     * @param other_department 
     */
    void change_department(const std::string& other_department);
    
    /**
     * @brief Changing ust_card_num to other_ust_card_num
     * 
     * @param other_ust_card_num 
     */
    void change_ust_card_num(const int& other_ust_card_num);
};

class Professor : public Person {
  public:
    /**
     * @brief Construct a new Professor object, default constructor
     * 
     * @param name 
     * @param admit_date 
     * @param department 
     * @param ust_card_num 
     */
    Professor(std::string name = "", std::string admit_date = "", std::string department = "",
              int ust_card_num = 0);

    /**
     * @brief Print content of all member variables in testing purpose
     * 
     */
    void print_test() const;
};

class Student : public Person {
  private:
    int year;
    Status_Program status;
    BST<Major> majors;
    BST<Minor> minors;

  public:
    /**
     * @brief Construct a new Student object, default constructor
     * 
     * @param name 
     * @param admit_date 
     * @param department 
     * @param ust_card_num 
     * @param year 
     * @param status 
     */
    Student(std::string name = "", std::string admit_date = "", std::string department = "",
            int ust_card_num = 0, int year = 0, Status_Program status = Active_In_Program);
    
    /**
     * @brief Destroy the Student object
     * 
     */
    ~Student() = default;

    /**
     * @brief Get the year object
     * 
     * @return int 
     */
    int get_year() const;

    /**
     * @brief Get the status object
     * 
     * @return std::string 
     */
    std::string get_status() const;
    
    /**
     * @brief Get the majors object
     * 
     * @return BST<Major>& 
     */
    BST<Major>& get_majors();
    
    /**
     * @brief Get the minors object
     * 
     * @return BST<Minor>& 
     */
    BST<Minor>& get_minors();

    /**
     * @brief Changing year to other_year
     * 
     * @param other_year 
     */
    void change_year(const int& other_year);
    
    /**
     * @brief Changing status to other_status
     * 
     * @param other_status 
     */
    void change_status(const Status_Program& other_status);
    
    /**
     * @brief Insert other_major to majors
     * 
     * @param other_major 
     */
    void insert_major(const Major& other_major);
    
    /**
     * @brief Remove major from majors indicated by other_major_name
     * 
     * @param other_major_name 
     */
    void remove_major(const std::string& other_major_name);

    /**
     * @brief Insert other_minor to minors
     * 
     * @param other_minor 
     */
    void insert_minor(const Minor& other_minor);
    
    /**
     * @brief Remove minor from minors indicated by other_minor_name
     * 
     * @param other_minor_name 
     */
    void remove_minor(const std::string& other_minor_name);

    /**
     * @brief Print content of all member variables in testing purpose
     * 
     */
    void print_test() const;

    /**
     * @brief Converting std::string to Status_Program
     * 
     * @param status_string 
     * @return Status_Program 
     */
    Status_Program convert_string_status(const std::string& status_string) const;
};

#endif  // PERSON_HPP