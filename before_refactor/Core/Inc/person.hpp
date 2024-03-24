#ifndef INC_PERSON_HPP
#define INC_PERSON_HPP

#include <string>

#include "../Inc/bst.hpp"
#include "../Inc/program.hpp"
#include "../Inc/semester.hpp"

class Person {
    friend ostream& operator<<(ostream& os, const Person& data);

  protected:
    string name;
    string admit_date;
    string department;
    int ust_card_num;

  public:
    Person(string name = "", string admit_date = "", string department = "",
           int ust_card_num = 0);
    Person(const Person& other) = delete;
    ~Person() = default;

    /**
     * @brief Get the name object
     *
     * @return string
     */
    string get_name() const;

    /**
     * @brief Get the admit date object
     *
     * @return string
     */
    string get_admit_date() const;

    /**
     * @brief Get the department object
     *
     * @return string
     */
    string get_department() const;

    /**
     * @brief Get the ust card number object
     *
     * @return int
     */
    int get_ust_card_num() const;

    /**
     * @brief Change the name to other_name
     *
     * @param other_name
     */
    void change_name(const string& other_name);

    /**
     * @brief Change admit_date to other_admit_date
     *
     * @param other_admit_date
     */
    void change_admit_date(const string& other_admit_date);

    /**
     * @brief Change department to other_department
     *
     * @param other_department
     */
    void change_department(const string& other_department);

    /**
     * @brief Change ust_card_num to other_ust_card_num
     *
     * @param other_ust_card_num
     */
    void change_ust_card_num(const int& other_ust_card_num);
};

class Professor : public Person {
    friend ostream& operator<<(ostream& os, const Professor& data);

  private:
  public:
    Professor(string name = "", string admit_date = "", string department = "",
              int ust_card_num = 0);
    Professor(const Professor& other) = delete;
    ~Professor() = default;
};

class Student : public Person {
    friend ostream& operator<<(ostream& os, const Student& data);

  private:
    int year;
    float cga;
    float mcga;
    string status;
    BST<Major> majors;
    BST<Minor> minors;
    BST<Semester>* semesters;

  public:
    Student(string name = "", string admit_date = "", string department = "",
            int ust_card_num = 0, int year = 0, float cga = 0., float mcga = 0.,
            string status = "", BST<Semester>* semesters = nullptr);
    Student(const Student& other) = delete;
    ~Student();

    /**
     * @brief Get the year object
     *
     * @return int
     */
    int get_year() const;

    /**
     * @brief Get the CGA object
     *
     * @return float
     */
    float get_CGA() const;

    /**
     * @brief Get the MCGA object
     *
     * @return float
     */
    float get_MCGA() const;

    /**
     * @brief Get the status object
     *
     * @return string
     */
    string get_status() const;

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
     * @brief Get the semesters object
     *
     * @return BST<Semester>*
     */
    BST<Semester>* get_semesters() const;

    /**
     * @brief Change year to other_year
     *
     * @param other_year
     */
    void change_year(const int& other_year);

    void calculate_CGA(BST<Semester>* semesters);
    void calculate_MCGA(BST<Semester>* semesters);

    /**
     * @brief Chnage status to other_status
     *
     * @param other_status
     */
    void change_status(const string& other_status);

    /**
     * @brief Insert other major
     *
     * @param other
     */
    void insert_major(const Major& other);

    /**
     * @brief Remove given name_major
     *
     * @param name_major
     */
    void remove_major(const string& name_major);

    /**
     * @brief Insert other minor
     *
     * @param other
     */
    void insert_minor(const Minor& other);

    /**
     * @brief Remove given name_minor
     *
     * @param name_minor
     */
    void remove_minor(const string& name_minor);

    /**
     * @brief Insert given semesters with shallow copy
     *
     * @param other_semesters
     */
    void insert_semesters(BST<Semester>* other_semesters);
};

#endif