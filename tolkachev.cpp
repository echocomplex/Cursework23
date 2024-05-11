#include "tolkachev.h"

tolkachev::tolkachev (const tolkachev& unit) {
    this->database = unit.database;
}

tolkachev::tolkachev (const std::string filename) {
    std::ifstream file (filename, std::ios::in);
    if (file.is_open()) {
        std::string row;
        while (std::getline(file, row)) {
            std::istringstream iss(row);
            std::string word;
            Student unit;
            int count = 0;
            grade g;
            while (iss >> word) {
                if (count == 0) { unit.setNumber(word); }
                else if (count == 1) { unit.setFirstName(word); }
                else if (count == 2) { unit.setMiddleName(word); }
                else if (count == 3) { unit.setLastName(word); }
                else if (count == 4) { unit.setYear(std::stoi(word)); }
                else if (count == 5) { unit.setBirthday(word); }
                else if (count == 6) { unit.setFaculty(word); }
                else if (count == 7) { unit.setDepartment(word); }
                else if (count == 8) { unit.setGroup(word); }
                else if (count == 9) { unit.setGender(word); }
                else if (count == 10) { g.subject = word; }
                else if (count == 11) { g.date = word; }
                else if (count == 12) { g.mark = std::stoi(word); }
                ++count;
            }
            if (this->database.isExists(unit)) {
                this->database[this->database.find(unit)].appendGrade(g);
            }
            else {
                unit.appendGrade(g);
                this->database.append(unit);
            }
        }
    }
    else {
        throw std::runtime_error("File does not exist");
    }
    file.close();
}

tolkachev& tolkachev::operator= (const tolkachev& unit) {
    this->database = unit.database;
    return *this;
}

std::ostream& operator<< (std::ostream& os, tolkachev& unit) {
    std::string toOut;
    for (int i = 0; i < unit.database.length(); ++i) {
        List <grade> grades = unit.database[i].getGrades();
        for (int b = 0; b < grades.length(); ++b) {
            std::string row = 
                unit.database[i].getNumber() + " " + 
                unit.database[i].getFirstName() + " " + 
                unit.database[i].getMiddleName() + " " + 
                unit.database[i].getLastName() + " " + 
                std::to_string(unit.database[i].getYear()) + " " + 
                unit.database[i].getBirthday() + " " + 
                unit.database[i].getFaculty() + " " + 
                unit.database[i].getDepartment() + " " + 
                unit.database[i].getGroup() + " " + 
                unit.database[i].getGender() + " " + 
                grades[b].subject + " " + 
                grades[b].date + " " + 
                std::to_string(grades[b].mark) + "\n";
            toOut += row;
        }
    }
    os << toOut;
    return os;
}

void tolkachev::toFile (const std::string filename) {
    std::string toOut;
    for (int i = 0; i < this->database.length(); ++i) {
        List <grade> grades = this->database[i].getGrades();
        for (int j = 0; j < grades.length(); ++j) {
            std::string row = 
                this->database[i].getNumber() + " " + 
                this->database[i].getFirstName() + " " + 
                this->database[i].getMiddleName() + " " + 
                this->database[i].getLastName() + " " + 
                std::to_string(this->database[i].getYear()) + " " + 
                this->database[i].getBirthday() + " " + 
                this->database[i].getFaculty() + " " + 
                this->database[i].getDepartment() + " " + 
                this->database[i].getGroup() + " " + 
                this->database[i].getGender() + " " + 
                grades[j].subject + " " + 
                grades[j].date + " " + 
                std::to_string(grades[j].mark) + "\n";
            toOut += row;
        }
    }
    std::ofstream file(filename.c_str(), std::ios::trunc);
    file << toOut;
    file.close();
}

void tolkachev::append (const Student unit) {
    this->database.append(unit);
}

void tolkachev::remove (const unsigned int index) {
    this->database.remove(index);
} 

unsigned int tolkachev::find (const Student unit) {
    return this->database.find(unit);
}

bool tolkachev::isExists (const Student unit) {
    return this->database.isExists(unit);
}

Student tolkachev::get (const unsigned int index) {
    return this->database[index];
}

std::pair <List <Student>, List <Student>> tolkachev::split (std::string group) {
    List <std::string> added;
    std::map <unsigned short, unsigned short> count;
    for (int i = 0; i < this->database.length(); ++i) {
        if (this->database[i].getGroup() == group) {
            if (count.find(this->database[i].getYear()) == count.end()) {
                count[this->database[i].getYear()] = 1;
                added.append(this->database[i].getNumber());
            }
            else {
                if (!added.isExists(this->database[i].getNumber())) {
                    ++count[this->database[i].getYear()];
                    added.append(this->database[i].getNumber());
                }
            }
        }
    }
    if (added.length() == 0) {
        throw std::logic_error("Group does not exist!");
    }
    unsigned short max = count.begin()->first;
    for (std::map<unsigned short, unsigned short>::iterator it = count.begin(); it != count.end(); ++it) {
        if (it->second > count[max]) {
            max = it->first;
        }
    }
    List <Student> main, other;
    List <std::string> addedFinally;
    for (int i = 0; i < this->database.length(); ++i) {
        if (this->database[i].getGroup() == group) {
            if (!addedFinally.isExists(this->database[i].getNumber())) {
                if (this->database[i].getYear() == max) {
                    main.append(this->database[i]);
                }
                else {
                    other.append(this->database[i]);
                }
                addedFinally.append(this->database[i].getNumber());
            }
        }
    }
    return std::make_pair(main, other);
}

List <Student> tolkachev::sort (List <Student> unit) const {
    List <Student> result;
    std::map <std::string, int> good, normal, bad;
    for (int i = 0; i < unit.length(); ++i) {
        List <grade> grades = unit[i].getGrades();
        int five = 0, four = 0, three = 0, two = 0;
        for (int j = 0; j < grades.length(); ++j) {
            if (grades[j].mark == 5) {
                ++five;
            }
            else if (grades[j].mark == 4) {
                ++four;
            }
            else if (grades[j].mark == 3) {
                ++three;
            }
            else {
                ++two;
            }
        }
        if (two != 0) {
            bad[unit[i].getNumber()] = three;
        }
        else if (three != 0) {
            normal[unit[i].getNumber()] = four;
        }
        else if (four != 0) {
            good[unit[i].getNumber()] = five;
        }
        else {
           result.append(unit[i]);
        }
    }
    this->sortMap(bad);
    for (std::map<std::string, int>::iterator it = bad.begin(); it != bad.end(); ++it) {
        Student u;
        u.setNumber(it->first);
        result.append(unit[unit.find(u)]);
    }
    this->sortMap(normal);
    for (std::map<std::string, int>::iterator it = normal.begin(); it != normal.end(); ++it) {
        Student u;
        u.setNumber(it->first);
        result.append(unit[unit.find(u)]);
    }
    this->sortMap(good);
    for (std::map<std::string, int>::iterator it = good.begin(); it != good.end(); ++it) {
        Student u;
        u.setNumber(it->first);
        result.append(unit[unit.find(u)]);
    }
    return result;
}

void tolkachev::sortMap (std::map <std::string, int>& unit) const {
    if (unit.size() == 0) {
        return;
    }
    std::pair <std::string, int>* sortedArr = new std::pair <std::string, int>[unit.size()];
    int index = 0;
    for (std::map<std::string, int>::iterator it = unit.begin(); it != unit.end(); ++it) {
        sortedArr[index++] = *it;
    }
    for (int i = 0; i < unit.size() - 1; ++i) {
        for (int j = 0; j < unit.size() - i - 1; ++j) {
            if (sortedArr[j].second > sortedArr[j + 1].second) {
                std::pair <std::string, int> temp = sortedArr[j];
                sortedArr[j] = sortedArr[j + 1];;
                sortedArr[j + 1] = temp;
            }
        }
    }
    std::map <std::string, int> ready;
    for (int i = 0; i < unit.size() - 1; ++i) {
        ready.insert(sortedArr[i]);
    }
    delete[] sortedArr;
    unit = ready;
}

void tolkachev::encrypt (const std::string filenameIn, const std::string filenameOut) {
    std::string key;
    char alphabet[63] = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz1234567890";
    srand(time(NULL));
    for (int i = 0; i < 16; ++i) {
        key += alphabet[rand() % 62];
    }
    std::ofstream file("key.txt", std::ios::trunc);
    file << key;
    file.close();
    std::string commandAES = "openssl aes-128-cbc -salt -in " + filenameIn + " -out " + filenameOut + " -pass pass:" + key;
    std::system(commandAES.c_str());
    if (std::remove(filenameIn.c_str()) != 0) {
        std::cerr << "CANNOT DELETE >>> " + filenameIn << std::endl;
    }
    std::string commandRSA = "openssl rsautl -encrypt -inkey rsa.public -pubin -in key.txt -out key.txt.enc";
    std::system(commandRSA.c_str());
    if (std::remove("key.txt") != 0) {
        std::cerr << "CANNOT DELETE >>> key.txt" << std::endl;
    }
}

void tolkachev::decrypt (std::string filenameIn, std::string filenameOut) {
    std::string commandRSA = "openssl rsautl -decrypt -inkey rsa.private -in key.txt.enc -out key.txt";
    std::system(commandRSA.c_str());
    std::string key;
    std::ifstream file("key.txt", std::ios::in);
    file >> key;
    file.close();
    if (std::remove("key.txt.enc") != 0) {
        std::cerr << "CANNOT DELETE >>> key.txt.enc" << std::endl;
    }
    std::string commandAES = "openssl aes-128-cbc -d -in " + filenameIn + " -out " + filenameOut + " -pass pass:" + key;
    std::system(commandAES.c_str());
    if (std::remove(filenameIn.c_str()) != 0) {
        std::cerr << "CANNOT DELETE >>> " + filenameIn << std::endl;
    }
}