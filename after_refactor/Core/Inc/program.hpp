#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <string>

class Program {
  protected:
    std::string program_name;
    std::string change_date;

  public:
    Program(std::string program_name = "", std::string change_date = "");

    std::string get_program_name() const;
    std::string get_change_date() const;
    void change_program_name(const std::string& other_program_name);
    void change_change_date(const std::string& other_change_date);

    bool operator<(const Program& other);
    bool operator>(const Program& other);
    bool operator<=(const Program& other);
    bool operator>=(const Program& other);
    bool operator==(const Program& other);

    virtual void print_test() const = 0;
};

class Major : public Program {
  private:
    std::string major_name;

  public:
    Major(std::string program_name = "", std::string change_date = "", std::string major_name = "");

    std::string get_major_name() const;
    void change_major_name(const std::string& other_major_name);

    bool operator<(const Major& other);
    bool operator>(const Major& other);
    bool operator<=(const Major& other);
    bool operator>=(const Major& other);
    bool operator==(const Major& other);

    void print_test() const override;
};

class Minor : public Program {
  private:
    std::string minor_name;

  public:
    Minor(std::string program_name = "", std::string change_date = "", std::string minor_name = "");

    std::string get_minor_name() const;
    void change_minor_name(const std::string& other_minor_name);

    bool operator<(const Minor& other);
    bool operator>(const Minor& other);
    bool operator<=(const Minor& other);
    bool operator>=(const Minor& other);
    bool operator==(const Minor& other);

    void print_test() const override;
};

#endif  // PROGRAM_HPP