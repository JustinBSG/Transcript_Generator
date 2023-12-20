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

    string get_name() const;
    string get_change_date() const;
    string get_major() const;

    void change_name(const string& other_name);
    void change_change_date(const string& other_change_date);
    void change_major(const string& other_major);

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

    string get_name_major() const;

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

    string get_name_minor() const;

    void change_name_minor(const string& other_name_minor);

    Minor& operator=(const Minor& other);
    bool operator<(const Minor& other);
    bool operator>(const Minor& other);
    bool operator==(const Minor& other);
};

#endif