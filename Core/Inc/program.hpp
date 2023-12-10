#ifndef INC_PROGRAM_HPP
#define INC_PROGRAM_HPP

#include <string>

class Program {
  private:
    string name;
    string change_date;
    string major;
    Program* next;
    Program* prev;

  public:
    Program();
    Program(const Program& other);
    ~Program();

    void GetName() const;
    void GetChangeDate() const;
    void GetMajor() const;
    Program* GetNext() const;
    Program* GetPrev() const;

    void changeName(string);
    void changeChange_date(string);
    void changeMajor(string);
    void changeNext(Program*);
    void changePrev(Program*);

    Program* last_program() const;
    void add_program(Program*);
    void sort_program();
};

#endif