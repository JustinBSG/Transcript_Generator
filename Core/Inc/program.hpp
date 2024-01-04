#ifndef INC_PROGRAM_HPP
#define INC_PROGRAM_HPP

#include <string>

using namespace std;

class Program {
  protected:
    string name;
    string change_date;

  public:
    Program(string name = "", string change_date = "");
    Program(const Program& other);
    ~Program() = default;

    /**
     * @brief Get the name object
     * 
     * @return string 
     */
    string get_name() const;

    /**
     * @brief Get the change_date object
     * 
     * @return string 
     */
    string get_change_date() const;

    /**
     * @brief Change name to other_name
     * 
     * @param other_name 
     */
    void change_name(const string& other_name);

    /**
     * @brief Change change_date to other_change_date
     * 
     * @param other_change_date 
     */
    void change_change_date(const string& other_change_date);

    Program& operator=(const Program& other);
    bool operator<(const Program& other);
    bool operator>(const Program& other);
    bool operator==(const Program& other);
};

class Major : public Program {
    friend ostream& operator<<(ostream& os, const Major& data);

  private:
    string name_major;

  public:
    Major(string name = "", string change_date = "", string name_major = "");
    Major(const Major& other);
    ~Major() = default;

    /**
     * @brief Get the name_major object
     * 
     * @return string 
     */
    string get_name_major() const;

    /**
     * @brief Change name_major to other_name_major
     * 
     * @param other_name_major 
     */
    void change_name_major(const string& other_name_major);

    Major& operator=(const Major& other);
    bool operator<(const Major& other);
    bool operator>(const Major& other);
    bool operator==(const Major& other);
};

class Minor : public Program {
    friend ostream& operator<<(ostream& os, const Minor& data);

  private:
    string name_minor;

  public:
    Minor(string name = "", string change_date = "", string name_minor = "");
    Minor(const Minor& other);
    ~Minor() = default;

    /**
     * @brief Get the name_minor object
     * 
     * @return string 
     */
    string get_name_minor() const;

    /**
     * @brief Change name_minor to other_name_minor
     * 
     * @param other_name_minor 
     */
    void change_name_minor(const string& other_name_minor);

    Minor& operator=(const Minor& other);
    bool operator<(const Minor& other);
    bool operator>(const Minor& other);
    bool operator==(const Minor& other);
};

#endif