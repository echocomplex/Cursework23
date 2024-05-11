#ifndef TOLKACHEV
#define TOLKACHEV


#include "List.hpp"
#include <sstream>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <map>
#include "Student.hpp"
#include <ctime>


class tolkachev {
private:
    List <Student> database;
public:
    tolkachev () {}
    tolkachev (const tolkachev& unit);
    tolkachev (const std::string filename);
    tolkachev& operator= (const tolkachev& unit);
    friend std::ostream& operator<< (std::ostream& os, tolkachev& unit);
    ~tolkachev () {}
    void toFile (const std::string filename);
    void append (const Student unit);
    void remove (const unsigned int index);
    unsigned int find (const Student unit);
    Student get (const unsigned int index);
    bool isExists (const Student unit);
    std::pair <List <Student>, List <Student>> split (std::string group);
    List <std::pair <Student, float>> sort (List <Student> unit) const; 
    void sortMap (List <std::pair <std::string, float>>& unit) const;
    static void encrypt (const std::string filenameIn, const std::string filenameOut);
    static void decrypt (const std::string filenameIn, const std::string filenameOut);
};

#endif