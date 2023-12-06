#include "../Inc/transcript.hpp"
#include <ctime>

using namespace std;

Transcript::Transcript() : user{create_user()}, advisor{create_prof()}, semesters{create_semesters()},
                            print_date{createPrint_date()}, total_num_semesters{0} {
                                Semester *ptr_sem = semesters;
                                while (ptr_sem != nullptr) {
                                    if (ptr_sem->GetTotal_num_courses() != 0)
                                        total_num_semesters++;
                                    ptr_sem = ptr_sem->GetNext();
                                }
                            }

Transcript::~Transcript() {
    delete user;
    delete advisor;
    delete semesters;
}

Student* Transcript::create_user() {
    Student *user;
    return user;
}

Professor* Transcript::create_prof() {
    Professor *prof;
    return prof;
}

Semester* Transcript::create_semesters() {
    Semester *sem;
    return sem;
}

string Transcript::createPrint_date() {
    time_t rawtime;
    struct tm * timeinfo;
    string buffer;
    char temp[100];

    time (&rawtime);
    timeinfo = localtime (&rawtime);

    strftime(temp,100,"%d %B %Y\n",timeinfo);
    buffer.append(temp);
    strftime(temp,100,"%X",timeinfo);
    buffer.append(temp);

    return buffer;
}

int Transcript::GetTotal_num_semesters() const {
    return total_num_semesters;
}

void Transcript::print() const {
    
}