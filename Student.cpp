#include "Student.h"

Student::Student (const Student& unit) {
    this->number = unit.number;
    this->first_name = unit.first_name;
    this->middle_name = unit.middle_name;
    this->last_name = unit.last_name;
    this->year = unit.year;
    this->birthday = unit.birthday;
    this->faculty = unit.faculty;
    this->department = unit.department;
    this->group = unit.group;
    this->gender = unit.gender;
    this->grades = unit.grades;
}

Student::Student (const std::string number, const std::string first_name, const std::string middle_name, const std::string last_name, const unsigned short year, const std::string birthday, const std::string faculty, const std::string department, const std::string group, const std::string gender, const List <grade> grades) {
    this->number = number;
    this->first_name = first_name;
    this->middle_name = middle_name;
    this->last_name = last_name;
    this->year = year;
    this->birthday = birthday;
    this->faculty = faculty;
    this->department = department;
    this->group = group;
    this->gender = gender;
    this->grades = grades;
}

Student& Student::operator= (const Student& unit) {
    this->number = unit.number;
    this->first_name = unit.first_name;
    this->middle_name = unit.middle_name;
    this->last_name = unit.last_name;
    this->year = unit.year;
    this->birthday = unit.birthday;
    this->faculty = unit.faculty;
    this->department = unit.department;
    this->group = unit.group;
    this->gender = unit.gender;
    this->grades = unit.grades;
    return *this;
}

bool Student::operator== (const Student& unit1) const {
    return (this->number == unit1.getNumber());
}
