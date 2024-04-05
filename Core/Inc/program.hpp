#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <string>

class Program {
  protected:
    std::string program_name;
    std::string change_date;

  public:
    /**
     * @brief Construct a new Program object, default constructor
     * 
     * @param program_name 
     * @param change_date 
     */
    Program(std::string program_name = "", std::string change_date = "");

    /**
     * @brief Get the program_name object
     * 
     * @return std::string 
     */
    std::string get_program_name() const;

    /**
     * @brief Get the change_date object
     * 
     * @return std::string 
     */
    std::string get_change_date() const;

    /**
     * @brief Changing program_name to other_program_name
     * 
     * @param other_program_name 
     */
    void change_program_name(const std::string& other_program_name);
    
    /**
     * @brief Changint change_date to other_change_date
     * 
     * @param other_change_date 
     */
    void change_change_date(const std::string& other_change_date);

    /**
     * @brief Comparing by using std::string change_date
     * 
     * @param other 
     * @return true 
     * @return false 
     */
    bool operator<(const Program& other);

    /**
     * @brief Comparing by using std::string change_date
     * 
     * @param other 
     * @return true 
     * @return false 
     */
    bool operator>(const Program& other);
    
    /**
     * @brief Comparing by using std::string change_date
     * 
     * @param other 
     * @return true 
     * @return false 
     */
    bool operator<=(const Program& other);
    
    /**
     * @brief Comparing by using std::string change_date
     * 
     * @param other 
     * @return true 
     * @return false 
     */
    bool operator>=(const Program& other);
    
    /**
     * @brief Comparing by using std::string change_date
     * 
     * @param other 
     * @return true 
     * @return false 
     */
    bool operator==(const Program& other);

    /**
     * @brief Print content of all member variables in testing purpose
     * 
     */
    virtual void print_test() const = 0;
};

class Major : public Program {
  private:
    std::string major_name;

  public:
    /**
     * @brief Construct a new Major object, default constructor
     * 
     * @param program_name 
     * @param change_date 
     * @param major_name 
     */
    Major(std::string program_name = "", std::string change_date = "", std::string major_name = "");

    /**
     * @brief Get the major_name object
     * 
     * @return std::string 
     */
    std::string get_major_name() const;

    /**
     * @brief Changing major_name to other_major_name
     * 
     * @param other_major_name 
     */
    void change_major_name(const std::string& other_major_name);

    /**
     * @brief Comparing by using std::string change_date
     * 
     * @param other 
     * @return true 
     * @return false 
     */
    bool operator<(const Major& other);
    
    /**
     * @brief Comparing by using std::string change_date
     * 
     * @param other 
     * @return true 
     * @return false 
     */
    bool operator>(const Major& other);
    
    /**
     * @brief Comparing by using std::string change_date
     * 
     * @param other 
     * @return true 
     * @return false 
     */
    bool operator<=(const Major& other);
    
    /**
     * @brief Comparing by using std::string change_date
     * 
     * @param other 
     * @return true 
     * @return false 
     */
    bool operator>=(const Major& other);
    
    /**
     * @brief Comparing by using std::string change_date
     * 
     * @param other 
     * @return true 
     * @return false 
     */
    bool operator==(const Major& other);

    /**
     * @brief Print content of all member variables in testing purpose
     * 
     */
    void print_test() const override;
};

class Minor : public Program {
  private:
    std::string minor_name;

  public:
    /**
     * @brief Construct a new Minor object, default constructor
     * 
     * @param program_name 
     * @param change_date 
     * @param minor_name 
     */
    Minor(std::string program_name = "", std::string change_date = "", std::string minor_name = "");

    /**
     * @brief Get the minor name object
     * 
     * @return std::string 
     */
    std::string get_minor_name() const;
    
    /**
     * @brief Chanaging minor_name to other_minor_name
     * 
     * @param other_minor_name 
     */
    void change_minor_name(const std::string& other_minor_name);

    /**
     * @brief Comparing by using std::string change_date
     * 
     * @param other 
     * @return true 
     * @return false 
     */
    bool operator<(const Minor& other);
    
    /**
     * @brief Comparing by using std::string change_date
     * 
     * @param other 
     * @return true 
     * @return false 
     */
    bool operator>(const Minor& other);
    
    /**
     * @brief Comparing by using std::string change_date
     * 
     * @param other 
     * @return true 
     * @return false 
     */
    bool operator<=(const Minor& other);
    
    /**
     * @brief Comparing by using std::string change_date
     * 
     * @param other 
     * @return true 
     * @return false 
     */
    bool operator>=(const Minor& other);
    
    /**
     * @brief Comparing by using std::string change_date
     * 
     * @param other 
     * @return true 
     * @return false 
     */
    bool operator==(const Minor& other);

    /**
     * @brief Print content of all member variables in testing purpose
     * 
     */
    void print_test() const override;
};

#endif  // PROGRAM_HPP