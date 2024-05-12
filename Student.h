#ifndef TOLKACH_STUD
#define TOLKACH_STUD


#include "List.h"
#include <string>
#include <ostream>


struct grade {
    std::string subject;
    std::string date;
    unsigned short mark;
};


class Student {
private:
    std::string number;
    std::string first_name;
    std::string middle_name;
    std::string last_name;
    unsigned short year;
    std::string birthday;
    std::string faculty;
    std::string department;
    std::string group;
    std::string gender;
    List <grade> grades;

public:
    Student () {};
    Student (const Student& unit);
    Student (
        const std::string number, const std::string first_name, const std::string middle_name, const std::string last_name,
        const unsigned short year, const std::string birthday, const std::string faculty, const std::string department,
        const std::string group, const std::string gender, const List <grade> grades
    );
    Student& operator= (const Student& unit);
    bool operator== (const Student& unit1) const;
    std::string getNumber () const { return this->number; }
    std::string getFirstName () const { return this->first_name; }
    std::string getMiddleName () const { return this->middle_name; }
    std::string getLastName () const { return this->last_name; }
    unsigned short getYear () const { return this->year; }
    std::string getBirthday () const { return this->birthday; }
    std::string getFaculty () const { return this->faculty; }
    std::string getDepartment () const { return this->department; }
    std::string getGroup () const { return this->group; }
    std::string getGender () const { return this->gender; }
    List <grade> getGrades () const { return this->grades; }
    void setNumber (const std::string data) { this->number = data; }
    void setFirstName (const std::string data) { this->first_name = data; }
    void setMiddleName (const std::string data) { this->middle_name = data; }
    void setLastName (const std::string data) { this->last_name = data; }
    void setYear (const unsigned short data) { this->year = data; }
    void setBirthday (const std::string data) { this->birthday = data; }
    void setFaculty (const std::string data) { this->faculty = data; }
    void setDepartment (const std::string data) { this->department = data; }
    void setGroup (const std::string data) { this->group = data; }
    void setGender (const std::string data) { this->gender = data; }
    void appendGrade (grade data) { this->grades.append(data); }
};


#endif