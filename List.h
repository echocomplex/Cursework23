#ifndef LIST_H
#define LIST_H


#include <string>
#include <sstream>
#include <iostream>
#include <fstream>


template <typename T> struct Node {
    T unit;
    unsigned int index;
    Node<T>* next;
};


template <typename T> class List {
private:
    Node<T>* first;
    Node<T>* last;

public:
    List ();
    List (const List& unit);
    List& operator= (const List& unit);
    T& operator[] (const unsigned int index);
    bool operator== (List& unit) const;
    ~List ();
    void append (const T newData);
    void remove (const unsigned int index);
    unsigned int find (T data);
    unsigned int length ();
    bool isExists (T data);
};




template <typename T> List<T>::List () {
    this->first = nullptr;
    this->last = nullptr;
}

template <typename T> List<T>::List (const List<T>& unit) {
    if (unit.first == nullptr) {
        this->first = nullptr;
        this->last = nullptr;
    }
    else {
        Node<T>* thisNode = new Node <T>;
        this->first = thisNode;
        Node<T>* unitNode = unit.first;
        while (true) {
            thisNode->unit = unitNode->unit;
            thisNode->index = unitNode->index;
            if (unitNode->next == nullptr) {
                thisNode->next = nullptr;
                this->last = thisNode;
                break;
            }
            else {
                thisNode->next = new Node <T>;
                unitNode = unitNode->next;
                thisNode = thisNode->next;
            }
        }
    }
}

template <typename T> List<T>& List<T>::operator= (const List<T>& unit) {
    if (this != &unit) {
        while (this->first != nullptr) {
            Node<T>* temp = this->first;
            this->first = this->first->next;
            delete temp;
        }

        if (unit.first == nullptr) {
            this->first = nullptr;
            this->last = nullptr;
        }
        else {
            Node<T>* thisNode = new Node <T>;
            this->first = thisNode;
            Node<T>* unitNode = unit.first;
            while (true) {
                thisNode->unit = unitNode->unit;
                thisNode->index = unitNode->index;
                if (unitNode->next == nullptr) {
                    thisNode->next = nullptr;
                    this->last = thisNode;
                    break;
                }
                else {
                    thisNode->next = new Node <T>;
                    unitNode = unitNode->next;
                    thisNode = thisNode->next;
                }
            }
        }
    }
    return *this;
}

template <typename T> T& List<T>::operator[] (const unsigned int index) {
    if (this->first == nullptr) {
        throw std::logic_error("List is empty");
    }
    else if (index < 0 || index > this->last->index) {
        throw std::out_of_range("Index is out of range");
    }
    else {
        Node<T>* thisNode = this->first;
        while (thisNode->index != index) {
            thisNode = thisNode->next;
        }
        return thisNode->unit;
    }
}

template <typename T> bool List<T>::operator== (List& unit) const {
    return ((unit.first == this->first) and (unit.last == this->last));
} 

template <typename T> List<T>::~List () {
    if (this->first == nullptr) {
        return;
    }
    Node<T>* toDelete;
    while (this->first->next != nullptr) {
        toDelete = this->first;
        this->first = this->first->next;
        delete toDelete;
    }
    this->first = nullptr;
}

template <typename T> void List<T>::append (const T newData) {
    Node<T>* newNode = new Node <T>;
    newNode->unit = newData;
    newNode->next = nullptr;
    if (this->first == nullptr) {
        newNode->index = 0;
        this->first = newNode;
    }
    else {
        newNode->index = this->last->index + 1;
        this->last->next = newNode;
    }
    this->last = newNode;
}

template <typename T> void List<T>::remove (const unsigned int index) {
    if (this->first == nullptr) {
        throw std::logic_error("List is empty");
    }
    else if (index < 0 || index > this->last->index) {
        throw std::out_of_range("Index is out of range");
    }
    else if (index == 0) {
        if (this->first->next == nullptr) {
            delete this->first;
            this->first = nullptr;
            this->last = nullptr;
        }
        else {
            Node<T>* thisNode = this->first->next;
            delete this->first;
            this->first = thisNode;
            while (thisNode != nullptr) {
                thisNode->index = thisNode->index - 1;
                thisNode = thisNode->next;
            }
        }
    }
    else {
        Node<T>* thisNode = this->first;
        if (this->last->index == index) {
            while (thisNode->next->next != nullptr) {
                thisNode = thisNode->next;
            }
            delete thisNode->next;
            thisNode->next = nullptr;
            this->last = thisNode;
        }
        else {
            Node<T>* lastNode = nullptr;
            Node<T>* toDelete = nullptr;
            bool changeIndex = false;
            while (thisNode->next != nullptr) {
                if (changeIndex) {
                    thisNode->index = thisNode->index - 1;
                    thisNode = thisNode->next;
                }
                else {
                    if (thisNode->next->index == index) {
                        lastNode = thisNode;
                        toDelete = thisNode->next;
                        changeIndex = true;
                    }
                    thisNode = thisNode->next;
                }
            }
            thisNode->index = thisNode->index - 1; 
            lastNode->next = toDelete->next;
            delete toDelete;
        }
    }
}

template <typename T> unsigned int List<T>::find (T data) {
    if (this->first == nullptr) {
        throw std::logic_error("List is empty");
    }
    else {
        Node<T>* thisNode = this->first;
        while (thisNode != nullptr) {
            if (thisNode->unit == data) {
                return thisNode->index;
            }
            else {
                thisNode = thisNode->next;
            }
        }
        throw std::logic_error("DATA HAS NOT FOUND");
    }
}

template <typename T> unsigned int List<T>::length () {
    if (this->last == nullptr) {
        return 0;
    }
    else {
        return this->last->index + 1;
    }    
}

template <typename T> bool List<T>::isExists (T data) {
    if (this->first == nullptr) {
        return false;
    }
    else {
        Node<T>* thisNode = this->first;
        while (thisNode != nullptr) {
            if (thisNode->unit == data) {
                return true;
            }
            else {
                thisNode = thisNode->next;
            }
        }
        return false;
    }
}

#endif