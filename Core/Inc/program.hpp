#ifndef INC_PROGRAM_HPP
#define INC_PROGRAM_HPP

#include <string>

class Program {
    private:
        string name;
        string change_date;
        string major;

    public:
        Program(string name = "", string change_date = "", string major = "");
        Program(const Program &other);

        void GetName() const;
        void GetChangeDate() const;
        void GetMajor() const;
};

#endif