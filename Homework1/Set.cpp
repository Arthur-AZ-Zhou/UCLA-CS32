#include "Set.h"
#include <iostream>

Set::Set() {
    length = 0;
}

// Set::Set(const Set &src) {
//     length = src.length;
//     for (int i = 0; i < length; i++) {
//         array[i] = src.array[i];
//     }
// }


// Set &Set::operator= (const Set &src) {
//     length = src.length;
//     for (int i = 0; i < length; i++) {
//         array[i] = src.array[i];
//     }
//     return *this;
// }


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
    if (!contains(value) && size() < DEFAULT_MAX_ITEMS) {
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
    ItemType oldArray[DEFAULT_MAX_ITEMS]; //old original array
    int oldSize = size();
    int oldOtherSize = other.size();

    for (int i = 0; i < size(); i++) { //populate oldArray[]
        get(i, oldArray[i]);
    }

    //change original set
    for (int j = 0; j < oldSize; j++) {
        // std::cerr << "j: " << j << " | ";
        erase(array[0]); //J WILL KEEP INCREASING AND WONT DO PROPERLY
        // dump();
    }
    // dump();
    for (int k = 0; k < other.size(); k++) {
        ItemType temp;
        other.get(k, temp);
        insert(temp);
    }

    // dump();

    //change other set
    // std::cerr << "other.size(): " << other.size() << std::endl;
    for (int l = 0; l < oldOtherSize; l++) {
        // std::cerr << "array[1]: " << array[l] << std::endl;
        other.erase(array[l]); //erase every value of the other array
    }
    // other.dump();
    for (int m = 0; m < oldSize; m++) {
        other.insert(oldArray[m]); //should take care of other.length
    }

    // other.dump();
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