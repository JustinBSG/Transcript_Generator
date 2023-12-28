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

    string get_name() const;
    string get_admit_date() const;
    string get_department() const;
    int get_ust_card_num() const;

    void change_name(const string& other_name);
    void change_admit_date(const string& other_admit_date);
    void change_department(const string& other_department);
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
    BST<Semester> *semesters; 

  public:
    Student(string name = "", string admit_date = "", string department = "",
            int ust_card_num = 0, int year = 0, float cga = 0., float mcga = 0.,
            string status = "", BST<Semester> *semesters = nullptr);
    Student(const Student& other) = delete;
    ~Student();

    int get_year() const;
    float get_CGA() const;
    float get_MCGA() const;
    string get_status() const;
    BST<Major>& get_majors();
    BST<Minor>& get_minors();

    void change_year(const int& other_year);
    void change_status(const string& other_status);

    void insert_major(const Major& other);
    void remove_major(const string& name_major);
    void insert_minor(const Minor& other);
    void remove_minor(const string& name_minor);
    void insert_semesters(BST<Semester> *other_semesters);
};

#endif