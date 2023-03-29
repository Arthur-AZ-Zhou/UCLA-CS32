#include "newSet.h"
#include <iostream>

Set::Set() {
    length = 0;
    capacity = DEFAULT_MAX_ITEMS;
    array = new ItemType[capacity];
}

Set::Set(int len) {
    length = 0; //set it to 0, although there are len values you have to insert them
    capacity = len;
    array = new ItemType[capacity]; //allocate array
}

Set::Set(const Set &src) {
    length = src.length;
    capacity = src.capacity;
    array = new ItemType[capacity];

    for (int i = 0; i < length; i++) {
        array[i] = src.array[i];
    }
}


Set::~Set() {
    delete [] array;
}


Set &Set::operator= (const Set &src) {
    if (&src == this) {
        return *this;
    }

    delete [] array;
    length = src.length;
    capacity = src.capacity;
    array = new ItemType[capacity];

    for (int i = 0; i < length; i++) {
        array[i] = src.array[i];
    }
    return *this;
}


bool Set::empty() const {
    return (length == 0)? true : false;
} 

int Set::size() const {
    return length;
}
    
bool Set::get(int i, ItemType& value) const {
    if (0 <= i && i < size()) {
        value = array[i]; //ASSIGNMENT OPERATOR???
        return true;
    }
    
    return false;
}

bool Set::contains(const ItemType& value) const {
    for (int i = 0; i < size(); i++) {
        if (value == array[i]) {
            return true;
        }
    }

    return false;
}
    
void Set::dump() const {
    for (int i = 0; i < size(); i++) {
        std::cerr << array[i] << " ";
    }
    std::cerr << "| size(): " << size() << std::endl;
}


bool Set::insert(const ItemType value) {
    if (!contains(value) && size() < capacity) {
        array[size()] = value; //ASSIGNMENT OPERATOR???
        length++;        
        sort();

        return true;
    }

    return false;
}

bool Set::erase(const ItemType& value) {
    int valueAt;

    if (contains(value)) {
        // std::cerr << "value: " << value << std::endl;
        for (int i = 0; i < size(); i++) {
            if (value == array[i]) {
                valueAt = i;
            }
        }

        for (int j = valueAt; j < size() - 1; j++) {
            get(j + 1, array[j]);
        }
        length--; //you don't have to worry about last index edge case

        return true;
    }

    return false;
}

void Set::swap(Set& other) {
    Set oldSet(*this);
    *this = other;
    other = oldSet;
}

void Set::sort() {
    for (int i = 0; i < size(); i++) {
        for (int j = 0; j < size(); j++) {
            if (array[i] < array[j]) {
                ItemType temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
}