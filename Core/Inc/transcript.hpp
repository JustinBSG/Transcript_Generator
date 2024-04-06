#ifndef TRANSCRIPT_HPP
#define TRANSCRIPT_HPP

#include <string>
#include <vector>

#include "../Inc/bst.hpp"
#include "../Inc/person.hpp"
#include "../Inc/semester.hpp"

struct CGA_semester {
    double cga;
    Semester* represent_semester;
    CGA_semester(double cga = 0., Semester* represent_semester = nullptr);
    ~CGA_semester() = default;
};

class Transcript {
  private:
    Student* user;
    Professor* advisor;
    BST<Semester>* semesters;
    std::vector<CGA_semester> CGAs;
    std::string print_date;

  public:
    /**
     * @brief Construct a new Transcript object, default constructor
     *
     * @param user
     * @param advisor
     * @param semesters
     */
    Transcript(Student* user = nullptr, Professor* advisor = nullptr,
               BST<Semester>* semesters = nullptr);

    /**
     * @brief Construct a new Transcript object, copy constructor
     *
     * @param other
     */
    Transcript(const Transcript& other);

    /**
     * @brief Construct a new Transcript object, move constructor
     *
     * @param other
     */
    Transcript(Transcript&& other);

    /**
     * @brief Destroy the Transcript object
     *
     */
    ~Transcript();

    /**
     * @brief Get the user object
     *
     * @return Student*
     */
    Student* get_user() const;

    /**
     * @brief Get the advisor object
     *
     * @return Professor*
     */
    Professor* get_advisor() const;

    /**
     * @brief Get the semesters object
     *
     * @return BST<Semester>*
     */
    BST<Semester>* get_semesters() const;

    /**
     * @brief Get CGA of specific semester indicated by index
     *
     * @param index
     * @return double
     */
    double get_CGA(const int& index) const;

    /**
     * @brief Get CGA of specific semester indicated by pointer of that semester
     *
     * @param target_semester
     * @return double
     */
    double get_CGA(const Semester* const target_semester) const;

    /**
     * @brief Get the CGAs object
     *
     * @return std::vector<CGA_semester>&
     */
    std::vector<CGA_semester>& get_CGAs();

    /**
     * @brief Get the print date object
     *
     * @return std::string
     */
    std::string get_print_date() const;

    /**
     * @brief Change user object to other_user \
     * @brief Using copy constructor
     *
     * @param other_user
     */
    void change_user(Student* other_user);

    /**
     * @brief Change advisor object to other_advisor \
     * @brief Using copy constructor
     *
     * @param other_advisor
     */
    void change_advisor(Professor* other_advisor);

    /**
     * @brief Change semesters object to other_semesters \
     * @brief Using copy constructor
     *
     * @param other_semesters
     */
    void change_semesters(BST<Semester>* other_semesters);

    /**
     * @brief Change print_date object to other_print_date
     *
     * @param other_print_date
     */
    void change_print_date(const std::string& other_print_date);

    /**
     * @brief Update CGAs object
     *
     */
    void update_CGAs();

    /**
     * @brief Update print_data object
     *
     */
    void update_print_date();

    /**
     * @brief Comparing by using std::string print_date
     *
     * @param other
     * @return true
     * @return false
     */
    bool operator<(const Transcript& other);

    /**
     * @brief Comparing by using std::string print_date
     *
     * @param other
     * @return true
     * @return false
     */
    bool operator>(const Transcript& other);

    /**
     * @brief Comparing by using std::string print_date
     *
     * @param other
     * @return true
     * @return false
     */
    bool operator<=(const Transcript& other);

    /**
     * @brief Comparing by using std::string print_date
     *
     * @param other
     * @return true
     * @return false
     */
    bool operator>=(const Transcript& other);

    /**
     * @brief Comparing by using std::string print_date
     *
     * @param other
     * @return true
     * @return false
     */
    bool operator==(const Transcript& other);

    /**
     * @brief Copy operator
     *
     * @param other
     * @return Transcript&
     */
    Transcript& operator=(const Transcript& other);

    /**
     * @brief Move operator
     *
     * @param other
     * @return Transcript&
     */
    Transcript& operator=(Transcript&& other);

    /**
     * @brief Print content of all member variables in testing purpose
     *
     */
    void print_test() const;
};

#endif  // TRANSCRIPT_HPP